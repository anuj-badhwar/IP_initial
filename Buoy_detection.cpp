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
 Mat img;
    img= imread("check7.jpg",1);


    /*double alpha=0.5;
    int beta=50;

    img.convertTo(img, -1, alpha, beta);*/

vector<Mat> channels;
Mat img_h;

        cvtColor(img, img_h, CV_BGR2YCrCb); //change the color image from BGR to YCrCb format

       split(img_h,channels); //split the image into channels

       equalizeHist(channels[0], channels[0]); //equalize histogram on the 1st channel (Y)
        equalizeHist(channels[2], channels[2]);
   merge(channels,img_h); //merge 3 channels including the modified 1st channel into one image

      cvtColor(img_h, img_h, CV_YCrCb2BGR);


double alpha=0.5;
     int beta=50;

    Mat new_image = Mat::zeros( img_h.size(), img_h.type() );
    img_h.convertTo(new_image, -1, alpha, beta);

    resize(img_h,img_h,Size(500,500));
    resize(new_image,new_image,Size(500,500));

    namedWindow("MyWind",CV_WINDOW_AUTOSIZE);
    imshow("Mywind",new_image);

    namedWindow("Input",CV_WINDOW_AUTOSIZE);
    imshow("Input",img_h);
    waitKey(0);


return 0;
}

