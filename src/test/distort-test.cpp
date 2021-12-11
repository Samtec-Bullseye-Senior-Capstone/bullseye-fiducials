#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <nlohmann/json.hpp>

#include "undistort.hpp"

using json = nlohmann::json;
using string = std::string;

#define XSIZE = 9
#define YSIZE = 6

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
        for ( int j=0; j < XSIZE ; j++ )
        {
            objp.push_back( cv::Point3f( i, j, 0 ) );
        }
    } 

    for ( int i=1; i < argc ; i++ )
    {
        count ++;
        string image_path = argv[i];
        std::cout << "Processing " << image_path << std::endl;
        cv::Mat image = cv::imread( image_path );
        cv::Size patternSize ( XSIZE, YSIZE );

        cv::Mat gimage = get_grayscale ( image );
        
        std::vector<cv::Point2f> corners;
        // print_chessboard_corners ( corners ); 
        corners = get_chessboard_corners ( gimage,
                                           patternSize );

        if ( corners.size() > 0 ) {
            refine_pixel_coordinates ( gimage, corners ); 
            show_chessboard ( gimage, corners, patternSize );
            objpoints.push_back( objp );
            imgpoints.push_back( corners );
        } 
    }

    cv::Mat cameraMatrix, distCoeffs, rotation, translation;
    // cv::calibrateCamera 
    // see https://learnopencv.com/camera-calibration-using-opencv/
}