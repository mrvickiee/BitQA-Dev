#ifndef profile_hpp
#define profile_hpp

#include <string>
#include <iostream>

#include <cgicc/Cgicc.h>
#include <cgicc/CgiEnvironment.h>
#include <cgicc/HTMLClasses.h>

#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTTPRedirectHeader.h>

#include "database.hpp"

namespace BitQA
{
	class Profile
	{
	public:
		Profile(std::string userName);
		int getUserReputation();
		bool canDo(std::string action);
		
	private:
		std::string userName;
		int Reputation;
		
	};
}

#endif
