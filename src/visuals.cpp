#include "visuals.hpp"

int line_thickness = 2;
cv::Scalar line_color = cv::Scalar(0, 0, 255);
float arrow_length = 30;
int arrow_thickness = 3;

void draw_borders ( cv::Mat image,
					string output_file, 
					json fiducial_json ) 
{
	for ( const auto& item : fiducial_json.items() ) 
	{
		cv::line( image, 
				  cv::Point(item.value()["top_left"]["x"], item.value()["top_left"]["y"]),
				  cv::Point(item.value()["top_right"]["x"], item.value()["top_right"]["y"]), 
				  line_color, 
				  line_thickness, 
				  cv::LINE_4 );
		cv::line( image, 
				  cv::Point(item.value()["top_right"]["x"], item.value()["top_right"]["y"]),
				  cv::Point(item.value()["bottom_right"]["x"], item.value()["bottom_right"]["y"]), 
				  line_color, 
				  line_thickness, 
				  cv::LINE_4 );
		cv::line( image, 
				  cv::Point(item.value()["bottom_right"]["x"], item.value()["bottom_right"]["y"]),
				  cv::Point(item.value()["bottom_left"]["x"], item.value()["bottom_left"]["y"]), 
				  line_color, 
				  line_thickness, 
				  cv::LINE_4 );
		cv::line( image, 
				  cv::Point(item.value()["bottom_left"]["x"], item.value()["bottom_left"]["y"]),
				  cv::Point(item.value()["top_left"]["x"], item.value()["top_left"]["y"]), 
				  line_color, 
				  line_thickness, 
				  cv::LINE_4 );
	}
	cv::imwrite( output_file, image );
}

void draw_corner_arrows ( cv::Mat image, 
						  string output_file, 
						  json fiducial_json ) 
{
	for ( const auto& item : fiducial_json.items() ) 
	{
		cv::arrowedLine( image, 
						 cv::Point((float)item.value()["top_left"]["x"] - arrow_length, (float)item.value()["top_left"]["y"] - arrow_length),
						 cv::Point(item.value()["top_left"]["x"], item.value()["top_left"]["y"]),
						 line_color, 
						 arrow_thickness, 
						 cv::LINE_4 );
		cv::arrowedLine( image, 
						 cv::Point((float)item.value()["top_right"]["x"] + arrow_length, (float)item.value()["top_right"]["y"] - arrow_length),
						 cv::Point((float)item.value()["top_right"]["x"], item.value()["top_right"]["y"]),
						 line_color, 
						 arrow_thickness, 
						 cv::LINE_4 );
		cv::arrowedLine( image, 
						 cv::Point((float)item.value()["bottom_right"]["x"] + arrow_length, (float)item.value()["bottom_right"]["y"] + arrow_length),
						 cv::Point((float)item.value()["bottom_right"]["x"], item.value()["bottom_right"]["y"]),
						 line_color, 
						 arrow_thickness, 
						 cv::LINE_4 );
		cv::arrowedLine( image, 
						 cv::Point((float)item.value()["bottom_left"]["x"] - arrow_length, (float)item.value()["bottom_left"]["y"] + arrow_length),
						 cv::Point((float)item.value()["bottom_left"]["x"], item.value()["bottom_left"]["y"]),
						 line_color, 
						 arrow_thickness, 
						 cv::LINE_4 );
	}
}

void do_visual ( cv::Mat image, visualConfig visual_config, json fiducial_json ) 
{
	if ( visual_config.output == true ) 
	{
		if ( visual_config.output_file == "" ) 
			return;

		if ( visual_config.borders == true ) 
			draw_borders( image, 
						  visual_config.output_file, 
						  fiducial_json );
		if ( visual_config.cornerArrows == true ) 
			draw_corner_arrows( image, 
						  		visual_config.output_file, 
						  		fiducial_json );

		cv::imwrite( visual_config.output_file, image );
	}
}

void print_visual_config ( visualConfig visual_config )
{
	cout << "Visual Config:" << std::endl;
	cout << "\tOutput: " << visual_config.output << std::endl;
	cout << "\tOutput File: " << visual_config.output_file << std::endl;
	cout << "\tBorders: " << visual_config.borders << std::endl;
	cout << "\tCorner Arrows: " << visual_config.cornerArrows << std::endl;
}