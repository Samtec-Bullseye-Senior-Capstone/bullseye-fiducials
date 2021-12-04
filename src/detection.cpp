#include "detection.hpp"

json cornersJSON ( cv::Matx<float, 4, 2> corners ) {
	json j;
	j["top_left"] = { {"x", corners(0,0)}, {"y", corners(0,1)} };
	j["top_right"] = { {"x", corners(1,0)}, {"y", corners(1,1)} };
	j["bottom_left"] = { {"x", corners(3,0)}, {"y", corners(3,1)} };
	j["bottom_right"] = { {"x", corners(2,0)}, {"y", corners(2,1)} };
	return j;
}   

json detect_from_image ( string input_path ) {
    cv::Mat image = cv::imread(input_path);
	json j;
    if(image.data) {
        for (const auto &tag : chilitags::Chilitags().find(image)) {
			j[ std::to_string( tag.first ) ] = cornersJSON( tag.second );
		}
		cout << j << std::endl;
    }
	return j;
}