#include <cv.h>
#include <highgui.h>
#include <iostream>

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
    Mat image = imread( "002.JPG" , 1 ) ;

    if( !image.data )                              // Check for invalid input
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }

    namedWindow( "Display window", CV_WINDOW_AUTOSIZE );// Create a window for display.
    imshow( "Display window", image );                   // Show our image inside it.

	Mat ycbcrImg ;

	cvtColor( image , ycbcrImg , CV_RGB2YCrCb ) ;

	for( int i = 0 ; i < image.rows ; i ++ )
	{
		for( int j = 0 ; j < image.cols ; j ++ )
		{
			if( ycbcrImg.at<Vec3b>( i , j )[ 1 ] > 110 && ycbcrImg.at<Vec3b>( i , j )[ 1 ] < 160 
				&& ycbcrImg.at<Vec3b>( i , j )[ 2 ] > 80 && ycbcrImg.at<Vec3b>( i , j )[ 2 ] < 140 )
			{
				image.at<Vec3b>( i , j )[ 0 ] = 0 ;
				image.at<Vec3b>( i , j )[ 1 ] = 0 ;
				image.at<Vec3b>( i , j )[ 2 ] = 0 ;
			}
		}
	}
	
	namedWindow( "Display window" , CV_WINDOW_AUTOSIZE ) ;
	imshow( "Display Skin Color" , image ) ;

    waitKey(0);                                          // Wait for a keystroke in the window
    return 0;
}