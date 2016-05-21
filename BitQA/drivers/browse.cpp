#include "../includes/html.hpp"
#include "../includes/database.hpp"

using namespace cgicc;
using namespace std;

int main()
{
	
	Cgicc cgicc;
	
    BitQA::HTML::displayHeader("Browse", cgicc);
    BitQA::HTML::displayFooter();
    
    return 0;
}
