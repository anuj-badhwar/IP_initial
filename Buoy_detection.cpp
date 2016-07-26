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

//int main()
//{
   /* Mat detectedSquare;
    detectedSquare = imread("check.jpg",1);
 cv::Mat hsv_img;
 cvtColor(detectedSquare,hsv_img,CV_BGR2HSV);
    Vec3b pixel;
    float totalPixel=0; // to count the total number of pixels in an image---to get the Percentage later
    float totalClass[6];// because we want to test for 5 classes + a garbage class.{{ Class-0 -> Garbage, Class-1->Orange, Class-2->Green, Class-3->Red,
                        //  Class-4->Blue, Class-5->Yellow }}

    for(int i=0; i<hsv_img.rows; i++)
    {
        for (int j=0; j<hsv_img.cols; j++)
        {

            totalPixel++;
            pixel= hsv_img.at<Vec3b>(i,j);

           // if(  pixel[0]>0 &&  pixel[0]<1  )           totalClass[1]++;    // Class-1->Orange
             if (  pixel[0]>50 &&  pixel[0]<65  )   totalClass[1]++;    // To check Green class-2 //svmResult==2 &&
            else if (  pixel[0]>0 &&  pixel[0]<10  )        totalClass[2]++;    // Class-3->Red
            //else if (  pixel[0]>100 &&  pixel[0]<115  )     totalClass[4]++;    // Class-4->Blue
            else if (  pixel[0]>18 &&  pixel[0]<21  )       totalClass[3]++;    // Class-5->Yellow
        }

    }

    float percentage[5];
    totalClass[0]=0; //Putting zero to the Garbage class

    for (int i=0; i<=5; i++)
    {
        percentage[i] = (totalClass[i] / totalPixel )*100;
    }

    float max=0;
    int index =0;

    for(int i=1;i<=3;i++)
    {
        if(max<percentage[i])
        {
            max=percentage[i];
            index=i;
        }
    }

    //cout<<"\n Organge: "<<percentage[1]<<"  Green: "<<percentage[2]<<"  Red: "<<percentage[3]<<"  Blue: "<<percentage[4]<<"  Yellow: "<<percentage[5]<<"\n \n";

    cout<<"Index\t"<<index<<"\n\n\n";
 */

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

