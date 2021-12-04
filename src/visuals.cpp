#include "visuals.hpp"

int line_thickness = 2;
cv::Scalar line_color = cv::Scalar(0, 0, 255);
float arrow_length = 30;
int arrow_thickness = 3;

void draw_borders ( string input_file, string output_file, json fiducial_json, bool debug) {
    cv::Mat image = cv::imread( input_file );
	if ( debug == true ) {
		cout << "Opened file " << input_file << std::endl;
	}
	for ( const auto& item : fiducial_json.items() ) {
		if ( debug == true ) {
			cout << "Drawing fiducial " << item.key() << std::endl;
		}
		cv::line(image, 
				cv::Point(item.value()["top_left"]["x"], item.value()["top_left"]["y"]),
				cv::Point(item.value()["top_right"]["x"], item.value()["top_right"]["y"]), 
				line_color, 
				line_thickness, 
				cv::LINE_4);
		cv::line(image, 
				cv::Point(item.value()["top_right"]["x"], item.value()["top_right"]["y"]),
				cv::Point(item.value()["bottom_right"]["x"], item.value()["bottom_right"]["y"]), 
				line_color, 
				line_thickness, 
				cv::LINE_4);
		cv::line(image, 
				cv::Point(item.value()["bottom_right"]["x"], item.value()["bottom_right"]["y"]),
				cv::Point(item.value()["bottom_left"]["x"], item.value()["bottom_left"]["y"]), 
				line_color, 
				line_thickness, 
				cv::LINE_4);
		cv::line(image, 
				cv::Point(item.value()["bottom_left"]["x"], item.value()["bottom_left"]["y"]),
				cv::Point(item.value()["top_left"]["x"], item.value()["top_left"]["y"]), 
				line_color, 
				line_thickness, 
				cv::LINE_4);
	}
	cv::imwrite( output_file, image );
}

void draw_corner_arrows ( string input_file, string output_file, json fiducial_json, bool debug) {
    cv::Mat image = cv::imread( input_file );
	if ( debug == true ) {
		cout << "Opened file " << input_file << std::endl;
	}
	for ( const auto& item : fiducial_json.items() ) {
		if ( debug == true ) {
			cout << "Drawing fiducial " << item.key() << std::endl;
		}
		cv::arrowedLine(image, 
				cv::Point((float)item.value()["top_left"]["x"] - arrow_length, (float)item.value()["top_left"]["y"] - arrow_length),
				cv::Point(item.value()["top_left"]["x"], item.value()["top_left"]["y"]),
				line_color, 
				arrow_thickness, 
				cv::LINE_4);
		cv::arrowedLine(image, 
				cv::Point((float)item.value()["top_right"]["x"] + arrow_length, (float)item.value()["top_right"]["y"] - arrow_length),
				cv::Point((float)item.value()["top_right"]["x"], item.value()["top_right"]["y"]),
				line_color, 
				arrow_thickness, 
				cv::LINE_4);
		cv::arrowedLine(image, 
				cv::Point((float)item.value()["bottom_right"]["x"] + arrow_length, (float)item.value()["bottom_right"]["y"] + arrow_length),
				cv::Point((float)item.value()["bottom_right"]["x"], item.value()["bottom_right"]["y"]),
				line_color, 
				arrow_thickness, 
				cv::LINE_4);
		cv::arrowedLine(image, 
				cv::Point((float)item.value()["bottom_left"]["x"] - arrow_length, (float)item.value()["bottom_left"]["y"] + arrow_length),
				cv::Point((float)item.value()["bottom_left"]["x"], item.value()["bottom_left"]["y"]),
				line_color, 
				arrow_thickness, 
				cv::LINE_4);
	}
	cv::imwrite( output_file, image );
}

