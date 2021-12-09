#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <nlohmann/json.hpp>

#include "detection.hpp"
#include "visuals.hpp"

using std::cout;
using json = nlohmann::json;
using string = std::string;

struct arguments 
{
	string input_file = "";
	visualConfig visual_config;
	bool camera = false;
	bool camera_num = 0;
	bool debug = false;
};

void print_help_message() 
{
  cout << "Bullseye Fiducials\n";
  cout << "Usage: bullseye-fiducials [options]\n";
  cout << "Options:\n";
  cout << "  -h, --help\t\t\tPrint this help message\n";
  cout << "  -i, --input <path>\t\tPath to the image to process\n";
  cout << "  -c, --camera <camera>\t\tCamera to use (default: 0)\n";
  cout << "      # NOTE: only an image OR a camera will be used.\n";
  cout << "  -o, --output <path>\t\tPath to the output file\n";
  cout << "  -d, --debug <path>\t\tPath to the output file\n";
}

arguments parse_args( int argc, char* argv[] ) 
{
	arguments config;
	for ( int i = 1; i < argc; i++ ) 
	{
		// print help message
		if ( strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0 ) 
		{
			print_help_message();
			exit(0);
		} 
		// set input file
		if ( strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--input") == 0 ) 
		{
			config.input_file = argv[i+1];
			i++;
		} 
		// set output file
		if ( strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0 ) 
		{
			config.visual_config.output = true;
			config.visual_config.output_file = argv[i+1];
			i++;
		} 
		// set camera 
		if ( strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--camera") == 0 ) 
		{
			config.camera = true;
			config.camera_num = atoi(argv[i+1]);
			i++;
		} 
		// set debug 
		if ( strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--debug") == 0 ) 
		{
			config.debug = true;
		} 
	}
	return config;
}

void print_config( arguments config ) 
{
	cout << "Input File: " << config.input_file << "\n";
	cout << "Camera: " << config.camera << "\n";
	cout << "Camera Number: " << config.camera_num << "\n";
	print_visual_config ( config.visual_config );
}

int main( int argc, char* argv[] )
{
	if ( argc < 2 ) 
	{
		print_help_message();
		return 1;
	}
	arguments config = parse_args( argc, argv );
	// print arguments for debugging
	if ( config.debug == true ) print_config( config );

	json output_json;
	if ( config.input_file == "" && config.camera == false ) 
	{
		cout << "No input file/camera specified.\n";
		return 1;
	}
	else if ( config.camera == true ) 
	{
		output_json = detect_from_camera( config.camera_num, config.visual_config );
	}
	else 
	{
		output_json = detect_from_image( config.input_file, config.visual_config );
	}
	// print output
	if ( output_json.is_null() ) 
	{
		cout << "{}" << std::endl;
	}
	else 
	{ 
		std::cout << output_json << std::endl;
	}
    return 0;
}
