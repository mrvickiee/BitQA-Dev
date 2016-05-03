#ifndef database_hpp
#define database_hpp

#include <string>
#include <iostream>

#include <mysql_connection.h>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

namespace BitQA {
	
	class Database {
		
	public:
		static const std::string HOST;
		static const std::string USERNAME;
		static const std::string PASSWORD;
		static const std::string SCHEMA;
		
	};
	
}

#endif
