#ifndef post
#define post

#include <string>

using std::string;

class Post
{
public:
	Post();
    string getFirstName();
	void setFirstName(string Name = "John");
    
private:
    string FirstName;
};

#endif
