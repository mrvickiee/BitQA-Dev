#ifndef mySearch
#define mySearch

#include <string>


using std::string;



class mySearch
{
	public:
		mySearch();
		mySearch(string);
		bool getQuestion();
		bool getUser();
		std::string getSearchTerm();
	private:
		std::string searchTerm;
		
};


#endif
