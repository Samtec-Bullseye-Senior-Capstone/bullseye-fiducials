#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <nlohmann/json.hpp>

#include "undistort.hpp"

using json = nlohmann::json;
using string = std::string;

// the pattern size to be used in the calibration images
#define XSIZE 9
#define YSIZE 6

// with the help of: https://learnopencv.com/camera-calibration-using-opencv/
// and https://docs.opencv.org/3.4/dc/dbb/tutorial_py_calibration.html
int main( int argc, char* argv[] )
{
    if ( argc < 2 )
    {
        std::cout << "Usage: " << argv[0] << " <image1> <image2> ... <imageN> " << std::endl;
        return 1;
    }

    // set up objpoints:
    std::vector<std::vector<cv::Point3f>> objpoints;
    // set up imgpoints:
    std::vector<std::vector<cv::Point2f>> imgpoints;

    std::vector<cv::Point3f> objp;
    for ( int i=0; i < XSIZE ; i++ )
    {
        for ( int j=0; j < YSIZE ; j++ )
        {
            objp.push_back( cv::Point3f( i, j, 0 ) );
        }
    } 

	cv::Mat image, gimage;

    for ( int i=1; i < argc ; i++ )
    {
        string image_path = argv[i];
        std::cout << "Processing " << image_path << std::endl;
        image = cv::imread( image_path );
        cv::Size patternSize ( XSIZE, YSIZE );

        gimage = get_grayscale ( image );
        
        std::vector<cv::Point2f> corners;
        // print_chessboard_corners ( corners ); 
        corners = get_chessboard_corners ( gimage,
                                           patternSize );

        if ( corners.size() > 0 ) {
            refine_pixel_coordinates ( gimage, corners ); 
			// uncomment below to see chessboard corners for image, this can be helpful
			// if we're getting weird results and want to see what the inputs are here
            // show_chessboard ( gimage, corners, patternSize, image_path );
            objpoints.push_back( objp );
            imgpoints.push_back( corners );
        } 
    }

    cv::Mat cameraMatrix, distCoeffs, rotation, translation;
    cv::calibrateCamera( objpoints,
						 imgpoints,
						 cv::Size( gimage.rows, gimage.cols),
						 cameraMatrix,
						 distCoeffs,
						 rotation, 
						 translation);

	std::cout << "cameraMatrix : " << cameraMatrix << std::endl;
	std::cout << "distCoeffs : " << distCoeffs << std::endl;
	std::cout << "Rotation vector : " << rotation << std::endl;
	std::cout << "Translation vector : " << translation << std::endl;

    for ( int i=1; i < argc ; i++ )
    {
        string image_path = argv[i];
		image = cv::imread( image_path );
		cv::Mat newCameraMatrix = cv::getOptimalNewCameraMatrix( cameraMatrix,
																 distCoeffs,
																 image.size(),
																 1,
																 image.size(),
			   													 0);
		cv::Mat undistorted;
		cv::undistort( image,
					   undistorted,
					   cameraMatrix,
					   distCoeffs,
					   newCameraMatrix );
		cv::imshow("original", image);
		cv::imshow("undistorted", undistorted);
		cv::waitKey();
	}
}
