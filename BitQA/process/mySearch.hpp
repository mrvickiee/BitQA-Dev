#ifndef mySearch
#define mySearch

#include <string>


using std::string;



class MySearch
{
	public:
		MySearch();
		MySearch(string);
		bool getQuestion();
		bool getUser();
		//string getSearchTerm();
	private:
		string searchTerm;
};




#endif
