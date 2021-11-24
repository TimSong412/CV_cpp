#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        cout << "please input correct dir!" << endl;
        return -1;
    }
    string dir = argv[1];

    VideoCapture inputVid;
    inputVid.open(dir + "/1.mp4");
    Mat frame;
    inputVid >> frame; //等价于cap.read(frame);
    Mat img1 = imread(dir + "/1.jpg", 1);
    Mat img2 = imread(dir + "/2.jpg", 1);
    Mat img3 = imread(dir + "/3.jpg", 1);
    Mat img4 = imread(dir + "/4.jpg", 1);
    Mat img5 = imread(dir + "/5.jpg", 1);
    Mat img6 = imread(dir + "/6.jpg", 1);
    Size s(frame.cols, frame.rows);
    VideoWriter writeVid;
    writeVid.open("./out.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), 25, s);

    Mat combine12;
    Mat back(s, CV_8UC3, Scalar(0, 0, 0));
    Mat mid(s, CV_8UC3, Scalar(0, 0, 0));

    putText(img1, "2019", Point(round(0.2 * img1.rows), round(0.8 * img1.cols)), FONT_HERSHEY_SIMPLEX, 2, Scalar(0, 0, 255), 5);
    putText(img2, "2021", Point(round(0.8 * img1.rows), round(0.8 * img1.cols)), FONT_HERSHEY_SIMPLEX, 2, Scalar(0, 0, 255), 5);
    hconcat(img1, img2, combine12);

    Mat head(s, CV_8UC3, Scalar(37, 193, 255)); // 创建片头图片并写入文字
    putText(head, "2021", Point(round(0.4 * head.cols), round(0.4 * head.rows)), QT_FONT_NORMAL, 2, Scalar(0, 0, 0), 5);
    putText(head, "\"Sanhao\" Tennis Championship", Point(round(0.05 * head.cols), round(0.6 * head.rows)), QT_FONT_NORMAL, 1.5, Scalar(0, 0, 0), 3);
    putText(head, "3190101087 Song Yunzhou", Point(round(0.8 * head.rows), round(0.55 * head.cols)), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 0), 2);
    // 将片头写入目标视频
    for (int i = 0; i < 50; i++)
    {
        writeVid << head;
    }

    // 图片缩放
    resize(combine12, combine12, s);
    resize(img5, img5, s);
    resize(img6, img6, s);

    for (int k = mid.cols - mid.cols % 100; k > 100; k -= 100) // 确定新旧图像分割位置
    {
        for (int i = 0; i < mid.rows; i++) // 对于补间动画的每一帧的每一个像素
            for (int j = 0; j < mid.cols; j++)
            {
                if (j < k) // 分别写入新旧图像的部分
                    mid.at<Vec3b>(Point(j, i)) = head.at<Vec3b>(Point(head.cols - k + j, i));
                else
                    mid.at<Vec3b>(Point(j, i)) = combine12.at<Vec3b>(Point(j - k, i));
            }
        putText(mid, "3190101087 Song Yunzhou", Point(round(0.8 * mid.rows), round(0.55 * mid.cols)), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 0), 2);
        writeVid << mid; // 打上标签后写入目标文件
    }

    putText(combine12, "3190101087 Song Yunzhou", Point(round(0.8 * combine12.rows), round(0.55 * combine12.cols)), FONT_HERSHEY_SIMPLEX, 1, Scalar(250, 250, 250), 2);
    for (int i = 0; i < 50; i++)
    {
        writeVid << combine12;
    }

    Size re(637, 478); // 按比例缩放图像
    Mat re3;
    resize(img3, re3, re);
    // 将较小的图像与黑色背景叠加
    for (int i = 0; i < re3.rows; i++)
        for (int j = 0; j < re3.cols; j++)
        {
            back.at<Vec3b>(Point(j + 100, i)) = re3.at<Vec3b>(Point(j, i));
        }

    for (int k = mid.cols - mid.cols % 100; k > 100; k -= 100)
    {
        for (int i = 0; i < mid.rows; i++)
            for (int j = 0; j < mid.cols; j++)
            {
                if (j < k)
                    mid.at<Vec3b>(Point(j, i)) = combine12.at<Vec3b>(Point(head.cols - k + j, i));
                else
                    mid.at<Vec3b>(Point(j, i)) = back.at<Vec3b>(Point(j - k, i));
            }
        putText(mid, "3190101087 Song Yunzhou", Point(round(0.8 * mid.rows), round(0.55 * mid.cols)), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 0), 2);
        writeVid << mid;
    }

    putText(back, "3190101087 Song Yunzhou", Point(round(0.8 * back.rows), round(0.55 * back.cols)), FONT_HERSHEY_SIMPLEX, 1, Scalar(250, 250, 250), 2);
    for (int i = 0; i < 50; i++)
    {
        writeVid << back;
    }
    Mat re4;
    resize(img4, re4, re);

    Mat temp(s, CV_8UC3);
    back.copyTo(temp);

    for (int i = 0; i < re4.rows; i++)
        for (int j = 0; j < re4.cols; j++)
        {
            // cout << "i= " << i << " j= " << j << endl;
            back.at<Vec3b>(Point(j + 100, i)) = re4.at<Vec3b>(Point(j, i));
        }

    for (int k = mid.cols - mid.cols % 100; k > 100; k -= 100)
    {
        for (int i = 0; i < mid.rows; i++)
            for (int j = 0; j < mid.cols; j++)
            {
                if (j < k)
                    mid.at<Vec3b>(Point(j, i)) = temp.at<Vec3b>(Point(head.cols - k + j, i));
                else
                    mid.at<Vec3b>(Point(j, i)) = back.at<Vec3b>(Point(j - k, i));
            }
        putText(mid, "3190101087 Song Yunzhou", Point(round(0.8 * mid.rows), round(0.55 * mid.cols)), FONT_HERSHEY_SIMPLEX, 1, Scalar(250, 250, 250), 2);
        writeVid << mid;
    }

    putText(back, "3190101087 Song Yunzhou", Point(round(0.8 * back.rows), round(0.55 * back.cols)), FONT_HERSHEY_SIMPLEX, 1, Scalar(250, 250, 250), 2);
    for (int i = 0; i < 50; i++)
    {
        writeVid << back;
    }

    for (int k = mid.cols - mid.cols % 100; k > 100; k -= 100)
    {
        for (int i = 0; i < mid.rows; i++)
            for (int j = 0; j < mid.cols; j++)
            {
                if (j < k)
                    mid.at<Vec3b>(Point(j, i)) = back.at<Vec3b>(Point(head.cols - k + j, i));
                else
                    mid.at<Vec3b>(Point(j, i)) = img5.at<Vec3b>(Point(j - k, i));
            }
        putText(mid, "3190101087 Song Yunzhou", Point(round(0.8 * mid.rows), round(0.55 * mid.cols)), FONT_HERSHEY_SIMPLEX, 1, Scalar(250, 250, 250), 2);
        writeVid << mid;
    }

    putText(img5, "3190101087 Song Yunzhou", Point(round(0.8 * img5.rows), round(0.55 * img5.cols)), FONT_HERSHEY_SIMPLEX, 1, Scalar(250, 250, 250), 2);
    for (int i = 0; i < 50; i++)
    {
        writeVid << img5;
    }

    for (int k = mid.cols - mid.cols % 100; k > 100; k -= 100)
    {
        for (int i = 0; i < mid.rows; i++)
            for (int j = 0; j < mid.cols; j++)
            {
                if (j < k)
                    mid.at<Vec3b>(Point(j, i)) = img5.at<Vec3b>(Point(head.cols - k + j, i));
                else
                    mid.at<Vec3b>(Point(j, i)) = img6.at<Vec3b>(Point(j - k, i));
            }
        writeVid << mid;
    }
    putText(img6, "3190101087 Song Yunzhou", Point(round(0.8 * img6.rows), round(0.55 * img6.cols)), FONT_HERSHEY_SIMPLEX, 1, Scalar(250, 250, 250), 2);
    for (int i = 0; i < 50; i++)
    {
        writeVid << img6;
    }

    for (int k = mid.cols - mid.cols % 100; k > 100; k -= 100)
    {
        for (int i = 0; i < mid.rows; i++)
            for (int j = 0; j < mid.cols; j++)
            {
                if (j < k)
                    mid.at<Vec3b>(Point(j, i)) = img6.at<Vec3b>(Point(head.cols - k + j, i));
                else
                    mid.at<Vec3b>(Point(j, i)) = frame.at<Vec3b>(Point(j - k, i));
            }
        putText(mid, "3190101087 Song Yunzhou", Point(round(0.8 * mid.rows), round(0.55 * mid.cols)), FONT_HERSHEY_SIMPLEX, 1, Scalar(250, 250, 250), 2);
        writeVid << mid;
    }

    while (!frame.empty())
    {
        putText(frame, "3190101087 Song Yunzhou", Point(round(0.8 * frame.rows), round(0.55 * frame.cols)), FONT_HERSHEY_SIMPLEX, 1, Scalar(250, 250, 250), 2);
        writeVid << frame;
        inputVid >> frame;
    }

    // namedWindow("Display Image", WINDOW_AUTOSIZE);
    // imshow("Display Image", combine12);
    // waitKey(0);
    writeVid.release();
    inputVid.release(); //释放资源
    return 0;
}