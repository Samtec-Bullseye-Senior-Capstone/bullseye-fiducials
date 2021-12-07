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

struct visualConfig {
    bool output = false;
	string output_file = "";
    bool borders = true;
    bool cornerArrows = false;
};

void draw_borders ( cv::Mat image,
					string output_file, 
					json fiducial_json ); 
void draw_corner_arrows ( cv::Mat image, 
						  string output_file, 
						  json fiducial_json ); 
void do_visual ( cv::Mat image, visualConfig visual_config, json fiducial_json );
void print_visual_config ( visualConfig visual_config );

#endif