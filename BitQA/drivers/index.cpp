#include "../includes/html.hpp"
#include "../includes/database.hpp"

using namespace std;
using namespace cgicc;

string removeMarkup(string input)
{
	string res = input;
	replace( res.begin(), res.end(), '<', ' ');
	replace( res.begin(), res.end(), '>', ' ');
	//string res = "<xmp>" + input + "</xmp>";
	//string res = "<b href='sss'>hello</b>";
	//res = regex_replace(res, regex(" *\\<[^>]*\\> *"), "");
	//res = regex_replace(res, regex("(<[a-zA-Z]*>)|(<\/[a-zA-Z]*>)"), "");
	
	return res;
}

void showRecentQuestions(Cgicc cgicc)
{
	try {
		sql::Driver *driver;
		sql::Connection *con;
		sql::PreparedStatement *prep_stmt;
		sql::ResultSet *res;
		
		driver = get_driver_instance();
		con = driver->connect(BitQA::Database::HOST,
							  BitQA::Database::USERNAME,
							  BitQA::Database::PASSWORD
							  );
		
		con->setSchema(BitQA::Database::SCHEMA);
		
		prep_stmt = con->prepareStatement("SELECT * FROM BrowseQuestions ORDER BY utimestamp DESC LIMIT 25;");
		res = prep_stmt->executeQuery();
		
		cout << "<br><h3>Most Recently Posted Questions</h3>" << endl;
		//cout << "<br><br>" << endl;
		
		
		//print results
		while (res->next()) {
			cout << "<div class=\"panel panel-default\"><div class=\"panel-body\">" << endl;
			cout << "<h4><a href='question.html?id=" << res->getString("id") <<  "'>" <<  res->getString("questionTitle") << endl;
			cout << "</a></h4>" << removeMarkup(res->getString("content").substr(0,100)) << (res->getString("content").length()>100? "..." : "");
			
			cout << "<div><br><span>&#128129;: <a href='profile.html?username=" << res->getString("username") << "'>" << res->getString("displayname") << "</a>&nbsp;</span><span>&#128336;: " << res->getString("utimestamp") <<"&nbsp;</span><span>&#128077;: " << res->getString("votes") <<"&nbsp;</span></div>" << endl;
			
			
			cout<< "</div></div>" << endl;
			
		}
		
		cout << "<br>" << endl;
		
		delete prep_stmt;
		delete con;
		
		
	} catch (sql::SQLException &e) {
		
		string error(e.what());
		
		BitQA::HTML::error("There was an error with SQL",
						   "Please go <a href=\"/\">home</a><p>Details: " + error + "</p>"
						   );
		
	} catch (exception &e) {
		
		string error(e.what());
		
		BitQA::HTML::error("There was an error viewing questions",
						   "Please go <a href=\"/\">home</a><p>Details: " + error + "</p>"
						   );
		
	} catch (string e){
		BitQA::HTML::error("There was an error viewing questions",
						   "Please go <a href=\"/\">home</a><p></p>"
						   );
	}
}

void printKnownUser(Cgicc cgicc)
{
	cout << "<center><h5>Welcome back, <span>" << BitQA::HTML::getDisplayName(cgicc) << "</span></h5></center>" << endl;
	/*
	cout << "<br><br><iframe width=\"853\"  height=\"480\" src=\"https://www.youtube.com/embed/O-zpOMYRi0w?rel=0&amp;showinfo=0\" frameborder=\"0\" allowfullscreen></iframe>";
	 */
	
	showRecentQuestions(cgicc);
	
}

void printUnknownUser()
{
	cout << "<center><h5>The world's greatest StackOverflow clone.</h5>";
	cout << "<p><a href=\"/login.html\">Login</a> or <a href=\"/signup.html\">Signup</a> to get started</p>";
	cout << "<br><p>Watch the video below to discover more</p>";
	cout << "<iframe width=\"853\"  height=\"480\" src=\"https://www.youtube.com/embed/tD4HCZe-tew?rel=0&amp;showinfo=0\" frameborder=\"0\" allowfullscreen></iframe></center>";
}

int main()
{
	
	Cgicc cgicc;
	BitQA::HTML::displayHeader("Home", cgicc);
	
	cout << "<div class=\"row\">";
	cout << "<center><h1>Bit QA - The World's Questions</h1></center>";
	
	if (BitQA::HTML::getLoggedInStatus(cgicc)) {
		printKnownUser(cgicc);
	} else {
		printUnknownUser();
	}
	
	cout << "</div>" << endl;
	
	BitQA::HTML::displayFooter();
	
	return 0;
}
