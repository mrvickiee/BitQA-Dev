#ifndef includes_hpp
#define includes_hpp

#include <string>
#include <iostream>

#include <mysql_connection.h>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include <cgicc/Cgicc.h>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h>

class Includes
{
public:
	static void displayHeader(std::string title = "Bit QA");
	static void displayFooter();
};

#endif
