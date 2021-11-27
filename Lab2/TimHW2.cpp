#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

bool FindCircle(Mat &conmask, Point start, vector<Point> &res);
Point TraceEdge(Mat &conmask, Point crnt, vector<Point> &res);

int main()
{
    Mat img = imread("./rice.png", IMREAD_GRAYSCALE);
    Mat edges;
    Canny(img, edges, 150, 250);
    imshow("img", img);
    waitKey(0);
    vector<vector<Point>> contours;
    findContours(edges, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);
	Mat cimage = Mat::zeros(edges.size(), CV_8UC3);
    for(size_t i = 0; i < contours.size(); i++)
	{
		//拟合的点至少为6
		size_t count = contours[i].size();
		if( count < 6 )
			continue;
 
		//椭圆拟合
		RotatedRect box = fitEllipse(contours[i]);
 
		// //如果长宽比大于30，则排除，不做拟合
		// if( MAX(box.size.width, box.size.height) > MIN(box.size.width, box.size.height)*30 )
		// 	continue;
		//画出追踪出的轮廓
		drawContours(cimage, contours, (int)i, Scalar::all(255), 1, 8);
		
		//画出拟合的椭圆
		ellipse(cimage, box, Scalar(0,0,255));
	}
	imshow("result", cimage);
	waitKey(0);

}

    // for (int i = 0; i < edges.cols; i++)
    //     for (int j = 0; j < edges.rows; j++)
    //         if (edges.at<uchar>(Point(i, j)) != 0)
    //         {
    //             vector<Point> res;
    //             if (FindCircle(edges, Point(i, j), res))
    //             {
    //                 RotatedRect mask = fitEllipse(res);
    //                 ellipse(img, mask, Scalar(255));
    //                 imshow("res", img);
    //                 waitKey(0);
    //                 break;
    //             }
    //         }

bool FindCircle(Mat &conmask, Point start, vector<Point> &res)
{
    Point pre = start;
    Point post = TraceEdge(conmask, start, res);
    if (post == start)
        return false;
    while (post != start || post != pre)
    {
        pre = post;
        post = TraceEdge(conmask, pre, res);
    }
    if (post == start)
        return true;
    else
        return false;
}

Point TraceEdge(Mat &conmask, Point crnt, vector<Point> &res)
{
    int i = -1;
    int j = 0;
    if (crnt.x + i >= 0 && crnt.x + i < conmask.cols && crnt.y + j > 0 && crnt.y + j < conmask.rows && conmask.at<uchar>(Point(crnt.x + i, crnt.y + j)) != 0)
    {
        res.push_back(Point(crnt.x + i, crnt.y + j));
        return Point(crnt.x + i, crnt.y + j);
    }
    i = -1;
    j = 1;
    if (crnt.x + i >= 0 && crnt.x + i < conmask.cols && crnt.y + j > 0 && crnt.y + j < conmask.rows && conmask.at<uchar>(Point(crnt.x + i, crnt.y + j)) != 0)
    {
        res.push_back(Point(crnt.x + i, crnt.y + j));
        return Point(crnt.x + i, crnt.y + j);
    }
    i = 0;
    j = 1;
    if (crnt.x + i >= 0 && crnt.x + i < conmask.cols && crnt.y + j > 0 && crnt.y + j < conmask.rows && conmask.at<uchar>(Point(crnt.x + i, crnt.y + j)) != 0)
    {
        res.push_back(Point(crnt.x + i, crnt.y + j));
        return Point(crnt.x + i, crnt.y + j);
    }
    i = 1;
    j = 1;
    if (crnt.x + i >= 0 && crnt.x + i < conmask.cols && crnt.y + j > 0 && crnt.y + j < conmask.rows && conmask.at<uchar>(Point(crnt.x + i, crnt.y + j)) != 0)
    {
        res.push_back(Point(crnt.x + i, crnt.y + j));
        return Point(crnt.x + i, crnt.y + j);
    }
    i = 1;
    j = 0;
    if (crnt.x + i >= 0 && crnt.x + i < conmask.cols && crnt.y + j > 0 && crnt.y + j < conmask.rows && conmask.at<uchar>(Point(crnt.x + i, crnt.y + j)) != 0)
    {
        res.push_back(Point(crnt.x + i, crnt.y + j));
        return Point(crnt.x + i, crnt.y + j);
    }
    i = 1;
    j = -1;
    if (crnt.x + i >= 0 && crnt.x + i < conmask.cols && crnt.y + j > 0 && crnt.y + j < conmask.rows && conmask.at<uchar>(Point(crnt.x + i, crnt.y + j)) != 0)
    {
        res.push_back(Point(crnt.x + i, crnt.y + j));
        return Point(crnt.x + i, crnt.y + j);
    }
    i = 0;
    j = -1;
    if (crnt.x + i >= 0 && crnt.x + i < conmask.cols && crnt.y + j > 0 && crnt.y + j < conmask.rows && conmask.at<uchar>(Point(crnt.x + i, crnt.y + j)) != 0)
    {
        res.push_back(Point(crnt.x + i, crnt.y + j));
        return Point(crnt.x + i, crnt.y + j);
    }
    i = -1;
    j = -1;
    if (crnt.x + i >= 0 && crnt.x + i < conmask.cols && crnt.y + j > 0 && crnt.y + j < conmask.rows && conmask.at<uchar>(Point(crnt.x + i, crnt.y + j)) != 0)
    {
        res.push_back(Point(crnt.x + i, crnt.y + j));
        return Point(crnt.x + i, crnt.y + j);
    }

    return crnt;
}