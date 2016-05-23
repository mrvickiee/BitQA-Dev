#include "json.hpp"

using namespace std;
using namespace cgicc;

void BitQA::JSON::displayHeader(std::string title, Cgicc cgicc)
{
	cout << "Content-Type: application/json\n\r" << endl;
}

void BitQA::JSON::error(std::string title, std::string message)
{
	cout <<  "{"
		<< "\"errorMessage\": \"" << title << "\","
		<< "\"errorDetail\": \"" << message << "\""
		<< "}";
}
