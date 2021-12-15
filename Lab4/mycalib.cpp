#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/calib3d/calib3d.hpp>


using std::vector;
using std::cout;
using std::cerr;
using std::endl;

void help(char **argv) {  // todo rewrite this
    cout << "\n\n"
         << "Example 18-1:\nReading a chessboard’s width and height,\n"
         << "              reading and collecting the requested number of views,\n" 
         << "              and calibrating the camera\n\n" 
         << "Call:\n" << argv[0] << " <board_width> <board_height> <number_of_boards> <if_video,_delay_between_framee_capture> <image_scaling_factor>\n\n"
         << "Example:\n" << argv[0] << " 9 6 15 500 0.5\n"
         << "-- to use the checkerboard9x6.png provided\n\n"
         << " * First it reads in checker boards and calibrates itself\n" 
         << " * Then it saves and reloads the calibration matricies\n"
         << " * Then it creates an undistortion map and finally\n"
         << " * It displays an undistorted image\n"
         << endl;
}

int main(int argc, char *argv[]) {
    int n_boards = 0;           // will be set by input list
    float image_sf = 0.5f;      // image scaling factor
    float delay = 1.f;
    int board_w = 0;
    int board_h = 0;


    board_w = 12;
    board_h = 12;
    n_boards = 1;

    int board_n = board_w * board_h;
    cv::Size board_sz = cv::Size(board_w, board_h);

    // ALLOCATE STORAGE
    //
    vector<vector<cv::Point2f> > image_points;
    vector<vector<cv::Point3f> > object_points;

    // Capture corner views: loop until we've got n_boards successful
    // captures (all corners on the board are found).
    //

    cv::Size image_size;
    while (image_points.size() < (size_t)n_boards) {
    cv::Mat image0, image;
    // capture >> image0;
    image0 = cv::imread(".\\HW4_images\\calibration\\IMG_0201.jpg", cv::IMREAD_COLOR);
    image_size = image0.size()/2;

    // Find the board
    //
    vector<cv::Point2f> corners;
    bool found = cv::findChessboardCorners(image0, board_sz, corners);

    // Draw it
    //
    drawChessboardCorners(image0, board_sz, corners, found);

    // If we got a good board, add it to our data
    //
    if (found ) {
        
        // image ^= cv::Scalar::all(255);
        cv::Mat mcorners(corners);

        // do not copy the data
        mcorners *= (1.0 / image_sf);

        // scale the corner coordinates
        image_points.push_back(corners);
        object_points.push_back(vector<cv::Point3f>());
        vector<cv::Point3f> &opts = object_points.back();

        opts.resize(board_n);
        for (int j = 0; j < board_n; j++) {
            opts[j] = cv::Point3f(static_cast<float>(j / board_w),
                                  static_cast<float>(j % board_w), 0.0f);
        }
        cout << "Collected our " << static_cast<uint>(image_points.size())
             << " of " << n_boards << " needed chessboard images\n" << endl;
    }

    cout << "\n\n*** CALIBRATING THE CAMERA...\n" << endl;

    // CALIBRATE THE CAMERA!
    //
    cv::Mat intrinsic_matrix, distortion_coeffs;
    double err = cv::calibrateCamera(
        object_points, image_points, image_size, intrinsic_matrix,
        distortion_coeffs, cv::noArray(), cv::noArray(),
        cv::CALIB_ZERO_TANGENT_DIST | cv::CALIB_FIX_PRINCIPAL_POINT);

    // SAVE THE INTRINSICS AND DISTORTIONS
    cout << " *** DONE!\n\nReprojection error is " << err;
    cout << "IntMat is " << intrinsic_matrix;
    cout << "coe is " << distortion_coeffs;



    cv::Mat undistimg;
    cv::undistort(image0, undistimg, intrinsic_matrix, distortion_coeffs);
    cv::resize(undistimg, undistimg, cv::Size(), 0.5, 0.5);
    cv::resize(image0, image0, cv::Size(), 0.5, 0.5);
    cv::imshow("undist", undistimg);
    cv::imshow("ori", image0);
    cv::waitKey(0);

    }

    return 0;
}
