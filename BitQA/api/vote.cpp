#include "../includes/html.hpp"
#include "../includes/json.hpp"
#include "../includes/database.hpp"

using namespace cgicc;
using namespace std;

int main()
{
	Cgicc cgicc;
	
	BitQA::JSON::getLoggedInStatus(cgicc);
	
	BitQA::JSON::displayHeader("test", cgicc);
	BitQA::JSON::error("test", "test2");
	
	return 0;
}
