#ifndef includes_hpp
#define includes_hpp

#include <string>
#include <iostream>

#include <cgicc/Cgicc.h>
#include <cgicc/CgiEnvironment.h>
#include <cgicc/HTMLClasses.h>

#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTTPRedirectHeader.h>

namespace BitQA {
	
	class HTML
	{
	public:
		static const std::string HOST;
		static void displayHeader(std::string title = "Bit QA");
		static void displayFooter();
		static std::string spacer(int height);
		static void error(std::string title, std::string message);
		
		// HTML User Helpers
		static bool getLoggedInStatus();
		static std::string getDisplayName();
		static std::string getUsername();
	};
	
}
#endif
