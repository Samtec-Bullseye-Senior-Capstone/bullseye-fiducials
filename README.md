# Bullseye Fiducials
Fiducial recognition using the [Chilitags](https://github.com/chili-epfl/chilitags) library.

### Getting Started
Clone this repository and it's submodules:
```
git clone git@github.com:Samtec-Bullseye-Senior-Capstone/bullseye-fiducials.git
cd bullseye-fiducials
git submodule update --init --recursive
```

Use cmake to configure build files:
```
mkdir build && cd build
cmake ..
make
```

### Usage:
```
Bullseye Fiducials
Usage: bullseye-fiducials [options]
Options:
  -h, --help                    Print this help message
  -i, --input <path>            Path to the image to process
  -c, --camera <camera>         Camera to use (default: 0)
      # NOTE: only an image OR a camera will be used.
  -o, --output <path>           Path to the output file
  -d, --debug <path>            Path to the output file`
```
Note that camera input is not yet supported.

