#include <QCoreApplication>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv/ml.h>
#include<opencv2/photo/photo.hpp>

using namespace cv;
using namespace std;
cv::Mat image_clahe;
int erosion_elem = 0;
int erosion_size = 0;
int dilation_elem = 0;
int dilation_size = 0;

void Erosion( int, void* )
{
    Mat dst1;
  int erosion_type;
  namedWindow( "Erosion Demo", CV_WINDOW_AUTOSIZE );
  if( erosion_elem == 0 ){ erosion_type = MORPH_RECT; }
  else if( erosion_elem == 1 ){ erosion_type = MORPH_CROSS; }
  else if( erosion_elem == 2) { erosion_type = MORPH_ELLIPSE; }

  Mat element = getStructuringElement( erosion_type,
                                       Size( 2*erosion_size + 1, 2*erosion_size+1 ),
                                       Point( erosion_size, erosion_size ) );

  /// Apply the erosion operation
  erode( image_clahe, image_clahe, element,Point(0,0),3000 );
 // fastNlMeansDenoisingColored( image_clahe, dst1, 3, 3, 7, 21 );
 // imshow( "Erosion Demo", dst1);
  imwrite("/home/sukhad/main1.jpg",image_clahe);
}
/** @function Dilation */
void Dilation( int, void* )
{
  int dilation_type;
  namedWindow( "Dilation Demo", CV_WINDOW_AUTOSIZE );
  if( dilation_elem == 0 ){ dilation_type = MORPH_RECT; }
  else if( dilation_elem == 1 ){ dilation_type = MORPH_CROSS; }
  else if( dilation_elem == 2) { dilation_type = MORPH_ELLIPSE; }

  Mat element = getStructuringElement( dilation_type,
                                       Size( 2*dilation_size + 1, 2*dilation_size+1 ),
                                       Point( dilation_size, dilation_size ) );
  /// Apply the dilation operation
  dilate( image_clahe, image_clahe, element,Point(0,0),3000 );
  imshow( "Dilation Demo", image_clahe );
}

    int main(int argc, char** argv)
    {
        QCoreApplication a(argc, argv);
        // READ RGB color image and convert it to Lab
     /*   VideoCapture capture("/home/sukhad/abc.mp4");
          if(!capture.isOpened()){
            //error in opening the video input
            cerr << "Unable to open video file: " ;
            exit(EXIT_FAILURE);
         }*/


//for(;;){
        cv::Mat bgr_image;
        cv::Mat lab_image;
        bgr_image=imread("/home/sukhad/YDXJ0119.jpg");
            if(!bgr_image.data)
                    return 0;
            resize(bgr_image,bgr_image,Size(640,480));
        cv::cvtColor(bgr_image, lab_image, CV_BGR2Lab);
cv::Mat dst1;
        // Extract the L channel
        std::vector<cv::Mat> lab_planes(3);
        cv::split(lab_image, lab_planes);  // now we have the L image in lab_planes[0]

        // apply the CLAHE algorithm to the L channel
        cv::Ptr<cv::CLAHE> clahe = cv::createCLAHE();
        clahe->setClipLimit(4);
        cv::Mat dst;
        clahe->apply(lab_planes[0], dst);

        // Merge the the color planes back into an Lab image
        dst.copyTo(lab_planes[0]);
        cv::merge(lab_planes, lab_image);

       // convert back to RGB
       cv::cvtColor(lab_image, image_clahe, CV_Lab2BGR);
       namedWindow( "image original", CV_WINDOW_AUTOSIZE );
       namedWindow( "image CLAHE", CV_WINDOW_AUTOSIZE );


       // display the results  (you might also want to see lab_planes[0] before and after).

       Erosion( 0, 0 );
         Dilation( 0, 0 );


         imshow("image original", bgr_image);
  imshow("image CLAHE", image_clahe);
//}
       return a.exec();
    }
