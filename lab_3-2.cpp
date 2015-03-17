#include <cv.h>
#include <highgui.h>
#include <cvaux.h>
#include <iostream>

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
	VideoCapture cap( "S3.avi" ) ;
	if( !cap.isOpened( ) )
	{
		return -1 ;
	}
	
	int totalFrame = cap.get( CV_CAP_PROP_FRAME_COUNT ) ;
	Mat frame , foreground , background ;
	BackgroundSubtractorMOG2 mog ;
	
	for( int i = 1 ; i < totalFrame ; i ++ )
	{
		cap >> frame ;

		mog( frame , foreground , 0.05 ) ;
		threshold( foreground , foreground , 128 , 255 , THRESH_BINARY ) ;

		for( int i = 0 ; i < frame.rows ; i ++ )
		{
			for( int j = 0 ; j < frame.cols ; j ++ )
			{
				if( foreground.at<uchar>( i , j ) == 0 )
				{
					frame.at<Vec3b>( i , j )[ 0 ] = 0 ;
					frame.at<Vec3b>( i , j )[ 1 ] = 0 ;
					frame.at<Vec3b>( i , j )[ 2 ] = 0 ;
				}
			}
		}

		mog.getBackgroundImage( background ) ;

		namedWindow( "Background" , CV_WINDOW_AUTOSIZE ) ;
		imshow( "Background" , background ) ;

		mog( background , background , 0.01 ) ;
		threshold( background , background , 128 , 255 , THRESH_BINARY ) ;


		for( int i = 0 ; i < frame.rows ; i ++ )
		{
			for( int j = 0 ; j < frame.cols ; j ++ )
			{
				if( background.at<uchar>( i , j ) == 255 )
				{
					frame.at<Vec3b>( i , j )[ 0 ] = 0 ;
					frame.at<Vec3b>( i , j )[ 1 ] = 0 ;
					frame.at<Vec3b>( i , j )[ 2 ] = 0 ;
				}
			}
		}
		dilate( frame , background , NULL ) ;


		namedWindow( "Foreground" , CV_WINDOW_AUTOSIZE ) ;
		imshow( "Foreground" , frame ) ;

		if( waitKey( 30 ) >= 0 )
		{
			break ;
		}
	}
    return 0 ;
}