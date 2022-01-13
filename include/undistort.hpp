#ifndef UNDISTORT_HPP
#define UNDISTORT_HPP

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>

using std::string;

std::vector<cv::Point2f> get_chessboard_corners ( cv::Mat image, 
                                                  cv::Size patternSize );
void print_chessboard_corners ( std::vector<cv::Point2f> corners );
cv::Mat get_grayscale ( cv::Mat image );
void refine_pixel_coordinates ( cv::Mat image, 
                                std::vector<cv::Point2f> corners);
void show_chessboard ( cv::Mat image, 
                       std::vector<cv::Point2f> corners,
                       cv::Size size,
					   string image_path);

#endif
