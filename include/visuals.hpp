#ifndef VISUALS_HPP
#define VISUALS_HPP

#include <vector>
#include <string>

#include <opencv2/highgui/highgui.hpp> 
#include "opencv2/opencv.hpp"
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using string = std::string;
using std::cout;

void draw_borders ( string input_file, string output_file, json fiducial_json, bool debug );
void draw_corner_arrows ( string input_file, string output_file, json fiducial_json, bool debug );

#endif