# StackOverflow
CSCI222 Project Readme / Install

## Useful Links
- http://www.tutorialspoint.com/cplusplus/cpp_web_programming.htm
- https://www.gnu.org/software/cgicc/doc/index.html

## Custom Build Directories:
Make sure you output your build to correct path and name:

### Xcode instructions:
1. Prefrences
	-> locations -> advanced -> custom -> absolute

2. In Build Settings:

	a) Pre configuration build products path:
		CONFIGURATION_BUILD_DIR = /Users/james/Repos/StackOverflow/www

	b) Product Name
		PRODUCT_NAME = $(TARGET_NAME)

### Visual Studio instructions:
N/A ATM

## Install CGI CC:

Download from:
https://www.gnu.org/software/cgicc/index.html
v 3.2.16

### Xcode instructions:
1. Follow below
$ cd /Users/james/Desktop/cgicc-3.2.16
$ sudo ./configure --prefix=/usr/local/Cellar/cgicc
$ sudo make
$ sudo make install

-> need to make shortcuts etc in /usr/local/include/ and /usr/local/lib/

2. In Build Settings:

	a) Header Search Paths
		HEADER_SEARCH_PATHS = /usr/local/include/**

	b) Library Search Paths
		LIBRARY_SEARCH_PATHS = /usr/local/lib/**

	c) Add the .a / dylib file in /usr/local/lib/cgicc/lib/ to the Build Phases

### Visual Studio instructions:
N/A ATM

## Install MySQL
1. Download:
http://dev.mysql.com/downloads/connector/cpp/

2. Set up paths as above

OR

Use Brew:

brew install mysql-connector-c++
brew install boost
