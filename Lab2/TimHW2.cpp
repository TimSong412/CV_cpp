#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
    Mat img = imread("./rice.png", IMREAD_COLOR);
    Mat edges;
    Canny(img, edges, 150, 250);
    imshow("img", edges);
    vector<vector<Point>> contours;
    findContours(edges, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE); 
    Mat cimage = Mat::zeros(edges.size(), CV_8UC3);
    for (size_t i = 0; i < contours.size(); i++)
    {
        //拟合的点集要求至少有6个点
        if (contours[i].size() < 6)
            continue;

        //椭圆拟合
        RotatedRect box = fitEllipse(contours[i]);

        // //如果长宽比大于30，则排除，不做拟合
        // if( MAX(box.size.width, box.size.height) > MIN(box.size.width, box.size.height)*30 )
        // 	continue;
        //画出追踪出的轮廓
        drawContours(cimage, contours, (int)i, Scalar::all(255), 1, 8);

        //画出拟合的椭圆
        ellipse(img, box, Scalar(0, 0, 255));
    }
    imshow("result", img);
    imwrite("./result.png", img);
    waitKey(0);
}
