#ifndef CAPTURE_HPP
#define CAPTURE_HPP

#include <opencv2/core/core_c.h> 
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
#include <csignal>

using string = std::string;
using std::cout;

cv::Mat get_frame ( int cameraIndex, 
                    int width = 4065,
                    int height = 3040 );


#endif