#include "database.hpp"

using namespace std;

#if DEBUG
	const string BitQA::Database::HOST = "tcp://db.csci222.com:3306";
#else
	const string BitQA::Database::HOST = "tcp://db.csci222.com:3306";
#endif

const string BitQA::Database::USERNAME = "root";
const string BitQA::Database::PASSWORD = "password";
const string BitQA::Database::SCHEMA = "BitQA";
