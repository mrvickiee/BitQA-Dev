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
		static void displayHeader(std::string title, cgicc::Cgicc cgicc);
		static void displayFooter();
		static std::string spacer(int height);
		static void error(std::string title, std::string message);
		
		// HTML User Helpers
		static bool getLoggedInStatus(cgicc::Cgicc cgicc);
		static std::string getDisplayName(cgicc::Cgicc cgicc);
		static std::string getUsername(cgicc::Cgicc cgicc);
	};
	
}
#endif
