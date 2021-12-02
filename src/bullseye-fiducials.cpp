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

#include <iostream>
using std::cout;


int main(int argc, char* argv[])
{
    if (argc != 2) {
        cout
            << "Usage: chilitags-detect <image>\n\n"
            << "Returns the list of detected tag id's in the image, one per line.\n";
        return 1;
    }
	int thickness = 3;

    cv::Mat image = cv::imread(argv[1]);
    if(image.data) {
		cout << "Rows, Cols: " << image.rows << ", " << image.cols << std::endl;
        for (const auto &tag : chilitags::Chilitags().find(image)) {
            cout << tag.first << "\n";
			cout << "tag.second = " << "\n" << " "  << tag.second << "\n" << "\n";
			cv::line(image, 
					cv::Point(tag.second(0,0), tag.second(0,1)),
				   	cv::Point(tag.second(1,0), tag.second(1,1)), 
					cv::Scalar(255,0,0), 
					thickness, 
					cv::LINE_4);
			cv::line(image, 
					cv::Point(tag.second(0,0), tag.second(0,1)),
				   	cv::Point(tag.second(3,0), tag.second(3,1)), 
					cv::Scalar(255,0,0), 
					thickness, 
					cv::LINE_4);
			cv::line(image, 
					cv::Point(tag.second(1,0), tag.second(1,1)),
				   	cv::Point(tag.second(2,0), tag.second(2,1)), 
					cv::Scalar(255,0,0), 
					thickness, 
					cv::LINE_4);
			cv::line(image, 
					cv::Point(tag.second(2,0), tag.second(2,1)),
				   	cv::Point(tag.second(3,0), tag.second(3,1)), 
					cv::Scalar(255,0,0), 
					thickness, 
					cv::LINE_4);
		}
		cv::imwrite("out.png", image);
        return 0;
    }
	cout << "nah fam" << std::endl;
    return 1;
}
