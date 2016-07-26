#include<opencv/cv.h>
#include<iostream>
#include<math.h>
#include<opencv/highgui.h>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/core/core.hpp>
#include<math.h>
#include<opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;
#include <QCoreApplication>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Mat src,dst, color_dst;
//   VideoCapture cap;
//    cap.open(0);

    double angle = 0;
//    for(;;){

//    if(cap.isOpened())
//        return 0;
//    cap>>src;
    src=imread("/home/sukhad/abcd.jpg");
    resize(src,src,Size(640,480));
       if(!src.data)
            return -1;
    u_int8_t* pixels = (uchar*)(src.data);

 inRange(src, cv::Scalar(0, 0, 0), cv::Scalar(50, 50, 50), src);
    Canny(src,dst, 50, 200, 3 );

    vector<Point>Largest_contour;
            double max_area=0;
    vector<vector<Point> > contours;
    findContours(dst,contours,CV_RETR_LIST,CV_CHAIN_APPROX_SIMPLE);
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
                           drawContours(dst,tcontour,-1,Scalar(255,0,0),2);

    cvtColor( dst,color_dst, CV_GRAY2BGR );

   vector<Vec4i> lines;
    HoughLinesP( dst, lines, 1, CV_PI/180,80, 60, 0 );
     size_t i = 0;
     int l,max=0,s,li;
     for(i=0;i<lines.size();i++){
            s=(lines[i][2]-lines[i][0])*(lines[i][2]-lines[i][0])+(lines[i][3]-lines[i][1])*(lines[i][3]-lines[i][1]);
            l=sqrt(s);
            if(l>max){
                    max=l;
                    li=i;
            }
        }



        line( color_dst, Point(lines[li][0], lines[li][1]),
            Point(lines[li][2], lines[li][3]), Scalar(0,0,255), 3, 8 );


            angle = atan2((double)lines[li][3] - lines[li][1],
                            (double)lines[li][2] - lines[li][0])-angle;

    namedWindow( "Source", 1 );
    imshow( "Source", dst );

    namedWindow( "Detected Lines", 1 );
    imshow( "Detected Lines", color_dst );

    namedWindow("Source1",1);
    imshow("Source1",src);
    std::cout << angle * 180 / CV_PI << std::endl;
    cv::waitKey(0);
 //   }

    return a.exec();
}
