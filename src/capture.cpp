#include "capture.hpp"

cv::Mat get_frame ( int cameraIndex, 
                    int width,
                    int height ) 
{
    // open video capture
    cv::VideoCapture capture;
    capture.open(cameraIndex);    

    // check if video capture is open
    if ( !capture.isOpened() ) {
        std::cerr << "Error: Could not open video capture" << std::endl;   
        exit(1);
    }

    // @CONNOR: look at detect live example, do we need to check for
    //          OPENCV3 ?
    // set capture 
    capture.set(cv::CAP_PROP_FRAME_WIDTH, width);
    capture.set(cv::CAP_PROP_FRAME_HEIGHT, height);

    // pull a frame from the specified camera:
    cv::Mat frame;
    capture.read(frame);

    capture.release();

    return frame;
}

