#ifndef mySearch
#define mySearch

#include <string>
using std::string;

class MySearch
{
	public:
		MySearch();
		MySearch(string);
		int getQuestion();
		int getUser();
		string getSearchTerm();
	private:
		string searchTerm;
};

#endif
