#ifndef search
#define search

#include <string>


using std::string;

namespace BitQA
{
	class Search
	{
		public:
			Search();
			Search(string);
			bool getQuestion();
			bool getUser();
			std::string getSearchTerm();
		private:
			std::string searchTerm;
			
	};
}

#endif
