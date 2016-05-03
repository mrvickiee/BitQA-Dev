# BitQA 
CSCI222 Project Readme / Install

## Useful Links
- http://www.tutorialspoint.com/cplusplus/cpp_web_programming.htm
- https://www.gnu.org/software/cgicc/doc/index.html
- https://dev.mysql.com/doc/connector-cpp/en/connector-cpp-getting-started-examples.html

## Xcode instructions:
### Setup
1. Prefrences
	-> locations -> advanced -> custom -> absolute

2. In Build Settings:

	a) Pre configuration build products path:
		CONFIGURATION_BUILD_DIR = /Users/james/Repos/StackOverflow/www

	b) Product Name
		PRODUCT_NAME = $(TARGET_NAME)

### Install CGI CC:

Download from:
https://www.gnu.org/software/cgicc/index.html
v 3.2.16

1. Follow below
$ cd /Users/james/Desktop/cgicc-3.2.16
$ sudo ./configure --prefix=/usr/local/Cellar/cgicc
$ sudo make
$ sudo make install

-> need to make shortcuts etc in /usr/local/include/ and /usr/local/lib/

ln -s ~/Foo\ Bar/ Foo

2. In Build Settings:

	a) Header Search Paths
		HEADER_SEARCH_PATHS = /usr/local/include/**

	b) Library Search Paths
		LIBRARY_SEARCH_PATHS = /usr/local/lib/**

	c) Add the .a / dylib file in /usr/local/lib/cgicc/lib/ to the Build Phases


### Install MySQL
1. Download:
http://dev.mysql.com/downloads/connector/cpp/

2. Set up paths as above

OR

Use Brew:

brew install mysql-connector-c++
brew install boost

## Ubuntu Server

### Server
$ sudo a2enmod cgi
$ nano /etc/apache2/sites-available/000-default.conf

----------
<VirtualHost *:80>
	ServerName www.csci222.com

	ServerAdmin admin@csci222.com
	DocumentRoot /var/www/csci222.com/www

	ErrorLog ${APACHE_LOG_DIR}/error.log
	CustomLog ${APACHE_LOG_DIR}/access.log combined

	<Directory "/var/www/csci222.com/www">
		Options ExecCGI
		AddHandler cgi-script .html
		AllowOverride All
		Require all granted
		Allow from all
	</Directory>

</VirtualHost>
----------

### Libaries
$ apt-get install libcgicc5-dev
$ apt-get install libmysqlcppconn-dev

## Visual Studio

### CGICC
1. download latest tar.gz from site above
2. open win/cgicc.dsp
3. build with release configurations
3.5 copy *.lib to /usr/lib/ and all headers *.h too /usr/include/
4. project project properties -> vc++ dirs -> include -> add include / add lib
5. in settings too go linker/input/additional dep/ add cgicc.lib (no dir)
6. copy .dll into /usr/bin
7. config properties -> debugging -> environment ADD ->PATH=\usr\bin

### Install xampp, edit vhosts

----------

DocumentRoot "C:/Users/James/Repos/BitQA/www"
<Directory "C:/Users/James/Repos/BitQA/www">
    Options ExecCGI
    AddHandler cgi-script .html
    AllowOverride All
    Require all granted
    Allow from all
</Directory>

ServerName csci222.local:80

----------

### Edit hosts file
C:\Windows\System32\drivers\etc\hosts
127.0.0.1	csci222.local

to change output dir and targets
config -> general -> output dir && target name

### MySql:
http://dev.mysql.com/downloads/connector/cpp/
copy lib and .h into /usr, will install in program files

### Boost:
https://sourceforge.net/projects/boost/files/boost/1.55.0/boost_1_55_0.zip/download
http://www.boost.org/doc/libs/1_55_0/more/getting_started/windows.html
copy into /usr/

## Common Problems
1. recursive headers and libs in xcode
http://stackoverflow.com/questions/12573271/xcode-with-boost-semantic-issue-undeclared-identifier-va-start
2. Custom Build Directories:
Make sure you output your build to correct path and name:
