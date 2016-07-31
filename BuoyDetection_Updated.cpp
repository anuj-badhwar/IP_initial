#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include<iostream>

using namespace std;
using namespace cv;

//Default for Yellow Buoy Detection
int t1min = 23, t1max = 40, t2min = 41, t2max = 150, t3min = 133, t3max = 255;
Mat threshy;

Mat hsv;
Scalar hsv_min,hsv_max;

//Trackbar
void cb(int,void*){

hsv_min = cv::Scalar(t1min, t2min, t3min, 0);
hsv_max = cv::Scalar(t1max, t2max, t3max, 0);

inRange(hsv, hsv_min, hsv_max, threshy);
imshow("Output",threshy);
}

int main()
{
 Mat src;

 src=imread("check8.jpg",1);
    resize(src,src,Size(600,600));
 if(src.empty())
    {
        cout<<"Can't Read\n";
        return 0 ;
    }

namedWindow("Settings",CV_WINDOW_AUTOSIZE);

cvtColor(src, hsv, CV_BGR2HSV);

createTrackbar("t1min", "Settings", &t1min, 255, cb);
createTrackbar("t1max", "Settings", &t1max, 255, cb);
createTrackbar("t2min", "Settings", &t2min, 255, cb);
createTrackbar("t2max", "Settings", &t2max, 255, cb);
createTrackbar("t3min", "Settings", &t3min, 255, cb);
createTrackbar("t3max", "Settings", &t3max, 255, cb);

//imshow("Settings",src);

hsv_min = cv::Scalar(t1min, t2min, t3min, 0);
hsv_max = cv::Scalar(t1max, t2max, t3max, 0);
inRange(hsv, hsv_min, hsv_max, threshy);


namedWindow("Output",CV_WINDOW_AUTOSIZE);
//imshow("Output", threshy);

erode(threshy,threshy,MORPH_RECT);
dilate(threshy,threshy,MORPH_RECT);

//Split HSV to 3 frames
Mat thresholded_hsv[3];
split(hsv,thresholded_hsv);

inRange(thresholded_hsv[0], Scalar(t1min, 0, 0, 0), Scalar(t1max, 0, 0, 0), thresholded_hsv[0]);
inRange(thresholded_hsv[1], Scalar(t2min, 0, 0, 0), Scalar(t2max, 0, 0, 0), thresholded_hsv[1]);
inRange(thresholded_hsv[2], Scalar(t3min, 0, 0, 0), Scalar(t3max, 0, 0, 0), thresholded_hsv[2]);

GaussianBlur(threshy, threshy, cv::Size(9, 9), 0, 0, 0);


imshow("Output",thresholded_hsv[0]);

 std::vector<std::vector<cv::Point> > contours;
    cv::Mat thresholded_Mat;

threshy.copyTo(thresholded_Mat);
findContours(thresholded_Mat, contours, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);  // Find the contours

double largest_area = 0, largest_contour_index = 0;

for (int i = 0; i < contours.size(); i++)  // iterate through each contour.
      {
        double a = contourArea(contours[i], false);
        if (a > largest_area)
        {
          largest_area = a;
          largest_contour_index = i;
        }
      }

//Convex Hull
std::vector<std::vector<cv::Point> > hull(contours.size());
      convexHull(cv::Mat(contours[largest_contour_index]), hull[largest_contour_index], false);

      std::vector<cv::Point2f> center(1);
      std::vector<float> radius(1);
      minEnclosingCircle(contours[largest_contour_index], center[0], radius[0]);

      cv::Mat circles = src;
      cv::Point2f pt;
      pt.x = 600;  // size of screen //320
      pt.y = 600;                     //240
      float distance;
                                                // array to publish
      distance = pow(radius[0] / 7526.5, -.92678);  //StackOverflow //Experimental

      circle(circles, center[0], radius[0], cv::Scalar(0, 250, 0), 1, 8, 0);  // minenclosing circle
      circle(circles, center[0], 4, cv::Scalar(0, 250, 0), -1, 8, 0);         // center is made on the screen
      circle(circles, pt, 4, cv::Scalar(150, 150, 150), -1, 8, 0);


namedWindow("Circle",CV_WINDOW_AUTOSIZE);
namedWindow("Contours",CV_WINDOW_AUTOSIZE);

imshow("circle", circles);            // Original stream with detected ball overlay
imshow("Contours", thresholded_Mat);  // The stream after color filterin

waitKey(0);
return 0;
}

