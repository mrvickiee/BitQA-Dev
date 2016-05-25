#ifndef json_hpp
#define json_hpp

#include <string>
#include <iostream>

#include <cgicc/Cgicc.h>
#include <cgicc/CgiEnvironment.h>
#include <cgicc/HTMLClasses.h>

#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTTPRedirectHeader.h>

#include "html.hpp"

namespace BitQA {
	
	class JSON : public HTML
	{
	public:
		static void displayHeader();
		static void error(std::string title, std::string message);
	};
	
}
#endif
