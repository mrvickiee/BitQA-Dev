#ifndef mySearch
#define mySearch

#include <string>
#include <vector>
using std::string;

class MySearch
{
	public:
		MySearch();
		MySearch(string);
		void getQuestion(bool, int);
		int getUser();
		string getSearchTerm();
	private:
		string searchTerm;

};

#endif
