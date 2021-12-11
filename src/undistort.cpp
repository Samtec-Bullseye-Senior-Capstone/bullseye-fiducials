#include "undistort.hpp"

std::vector<cv::Point2f> get_chessboard_corners ( cv::Mat image, 
                                                  cv::Size patternSize ) 
{
    // Find the chessboard corners
    std::vector<cv::Point2f> corners;
    int flags = cv::CALIB_CB_ADAPTIVE_THRESH + cv::CALIB_CB_NORMALIZE_IMAGE;
    bool found = cv::findChessboardCorners( image, 
                                            patternSize, 
                                            corners,
                                            flags );

    if ( !found ) 
    {
        std::cout << "Could not find chessboard corners" << std::endl;
        return corners;
    }

    return corners;
}

void print_chessboard_corners ( std::vector<cv::Point2f> corners ) 
{
    for ( int i = 0; i < corners.size(); i++ ) 
    {
        std::cout << "(" << corners[i].x << ", " << corners[i].y << ")" << std::endl;
    }
}

cv::Mat get_grayscale ( cv::Mat image ) 
{
    cv::Mat gimage;
    cv::cvtColor ( image, gimage, CV_BGR2GRAY );

    return gimage;
}

void refine_pixel_coordinates ( cv::Mat image, 
                                std::vector<cv::Point2f> corners)
{
    cv::TermCriteria criteria ( CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 30, 0.001 );
    cv::Size winSize ( 11, 11 );
    cv::Size zeroSize ( 0, 0 );

    cv::cornerSubPix ( image, 
                       corners,
                       winSize,
                       zeroSize,
                       criteria );
}

void show_chessboard ( cv::Mat image, 
                       std::vector<cv::Point2f> corners,
                       cv::Size size )
{
    cv::drawChessboardCorners ( image, 
                                size,
                                corners,
                                true );

    cv::imshow ( "drawChessboardCorners", image );
    cv::waitKey(0);
    cv::destroyAllWindows();
}


