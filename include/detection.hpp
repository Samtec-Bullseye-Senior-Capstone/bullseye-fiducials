#ifndef DETECTION_HPP
#define DETECTION_HPP

#include <string>
#include <iostream>
#include <chilitags.hpp>

#include <opencv2/imgproc.hpp> 
#include <opencv2/imgcodecs.hpp> 
#include <nlohmann/json.hpp>

#include "visuals.hpp"

using json = nlohmann::json;
using string = std::string;
using std::cout;

json cornersJSON ( cv::Matx<float, 4, 2> corners );
json detect_from_image ( string input_path, visualConfig visual_config );
json detect_from_camera ( int cameraIndex, visualConfig visual_config );

#endif