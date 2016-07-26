#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include <opencv2/opencv.hpp>
#include<vector>

#include<iostream>
#include<stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

int erosion_elem = 0;
int erosion_size = 0;
int dilation_elem = 0;
int dilation_size = 0;

 Mat element = getStructuringElement( MORPH_RECT,
                                       Size( 2*erosion_size + 1, 2*erosion_size+1 ),
                                       Point( erosion_size, erosion_size ) );

int main()
{
 Mat detectedSquare;
    detectedSquare = imread("/home/sukhad/YDXJ0119.jpg");

 cv::Mat hsv_img,threshy;

    cvtColor(detectedSquare,hsv_img,CV_BGR2HSV);

    for(int i=0;i<10;i++)
    blur( detectedSquare,detectedSquare, Size(3,3) );

    cv::inRange(hsv_img,cv::Scalar(23,41,133),cv::Scalar(40,150,255),threshy);

    //threshy.convertTo(threshy, CV_32F);
    detectedSquare.convertTo(detectedSquare, CV_32F);

    resize(threshy,threshy,Size(500,500));
    resize(detectedSquare,detectedSquare,Size(500,500));

    int thresh = 100;
    Canny( threshy, threshy, thresh, thresh*2, 3 );

    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
vector<Point>Largest_contour;
    findContours( threshy, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
    //cvtColor(threshy,threshy,CV_HSV2BGR);

    Mat drawing = Mat::zeros( threshy.size(), CV_8UC3 );
  for( int i = 0; i< contours.size(); i++ )
     {
       //Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
       Scalar color = Scalar(255,0,0 );
       drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, Point() );
     }
  double max_area;
  for(unsigned int i=0; i < contours.size(); i++)
   {
       double area=contourArea(contours[i]);
       if(area>max_area)
       {
           max_area=area;
           Largest_contour=contours[i];
       }
   }
  vector<vector<Point> > tcontour;

  tcontour.push_back(Largest_contour);
 // drawContours(drawing,tcontour,-1,Scalar(255,0,0),2);

 vector<Moments> mu(contours.size() );
 mu[0]=moments(Largest_contour);
 float x,y;
 x=static_cast<float>(mu[0].m10/mu[0].m00);
 y=static_cast<float>(mu[0].m01/mu[0].m00);
 cout<<x<<endl;
 cout<<y<<endl;

    namedWindow( "MyWindow", WINDOW_AUTOSIZE );
    namedWindow( "Input", WINDOW_AUTOSIZE );

  //  bitwise_and(threshy, detectedSquare, dst);



   // erode(threshy,threshy);
    //8dilate(threshy,threshy);



    imshow("MyWindow",drawing);
    imshow("Input",detectedSquare);

    waitKey(0);
return 0;

}
