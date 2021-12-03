/*******************************************************************************
*   Copyright 2013-2014 EPFL                                                   *
*   Copyright 2013-2014 Quentin Bonnard                                        *
*                                                                              *
*   This file is part of chilitags.                                            *
*                                                                              *
*   Chilitags is free software: you can redistribute it and/or modify          *
*   it under the terms of the Lesser GNU General Public License as             *
*   published by the Free Software Foundation, either version 3 of the         *
*   License, or (at your option) any later version.                            *
*                                                                              *
*   Chilitags is distributed in the hope that it will be useful,               *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of             *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
*   GNU Lesser General Public License for more details.                        *
*                                                                              *
*   You should have received a copy of the GNU Lesser General Public License   *
*   along with Chilitags.  If not, see <http://www.gnu.org/licenses/>.         *
*******************************************************************************/

#include <chilitags.hpp>

#include <opencv2/highgui/highgui.hpp> // imread
#include <opencv2/imgproc.hpp> 
#include <nlohmann/json.hpp>

#include <iostream>
#include <string>
using std::cout;
using json = nlohmann::json;

json cornersJSON ( cv::Matx<float, 4, 2> corners ) {
	json j;
	j["top_left"] = { {"x", corners(0,0)}, {"y", corners(0,1)} };
	j["top_right"] = { {"x", corners(1,0)}, {"y", corners(1,1)} };
	j["bottom_left"] = { {"x", corners(3,0)}, {"y", corners(3,1)} };
	j["bottom_right"] = { {"x", corners(2,0)}, {"y", corners(2,1)} };
	return j;
}

void draw_on_image ( cv::Mat *image, cv::Matx<float, 4, 2> corners ) {
	int thickness = 3;
	cv::line(*image, 
			cv::Point(corners(0,0), corners(0,1)),
			cv::Point(corners(1,0), corners(1,1)), 
			cv::Scalar(255,0,0), 
			thickness, 
			cv::LINE_4);
	cv::line(*image, 
			cv::Point(corners(0,0), corners(0,1)),
			cv::Point(corners(3,0), corners(3,1)), 
			cv::Scalar(255,0,0), 
			thickness, 
			cv::LINE_4);
	cv::line(*image, 
			cv::Point(corners(1,0), corners(1,1)),
			cv::Point(corners(2,0), corners(2,1)), 
			cv::Scalar(255,0,0), 
			thickness, 
			cv::LINE_4);
	cv::line(*image, 
			cv::Point(corners(2,0), corners(2,1)),
			cv::Point(corners(3,0), corners(3,1)), 
			cv::Scalar(255,0,0), 
			thickness, 
			cv::LINE_4);
}

int main(int argc, char* argv[])
{
    if (argc != 2) {
        cout
            << "Usage: chilitags-detect <image>\n\n"
            << "Returns the list of detected tag id's in the image, one per line.\n";
        return 1;
    }

    cv::Mat image = cv::imread(argv[1]);
    if(image.data) {
		json j;
        for (const auto &tag : chilitags::Chilitags().find(image)) {
			j[ std::to_string( tag.first ) ] = cornersJSON( tag.second );
			draw_on_image( &image, tag.second );
		}
		cout << j << std::endl;
		cv::imwrite("out.png", image);
        return 0;
    }
    return 1;
}
