#include "html.hpp"

using namespace cgicc;
using namespace std;

#if DEBUG
	const string BitQA::HTML::HOST = "http://csci222.local";
#else
	const string BitQA::HTML::HOST = "https://csci222.com";
#endif

bool BitQA::HTML::getLoggedInStatus(Cgicc cgicc)
{
	CgiEnvironment environment = cgicc.getEnvironment();
	const_cookie_iterator cci;
	
	for (cci = environment.getCookieList().begin();
		 cci != environment.getCookieList().end();
		 cci++) {
		if (cci->getName() == "username") {
			if (cci->getValue().length() > 0) {
				return true;
			} else {
				return false;
			}
		}
	}
	
	return false;
}

string BitQA::HTML::getDisplayName(Cgicc cgicc)
{
	CgiEnvironment environment = cgicc.getEnvironment();
	const_cookie_iterator cci;
	
	for (cci = environment.getCookieList().begin();
		 cci != environment.getCookieList().end();
		 cci++) {
		if (cci->getName() == "displayname") {
			return cci->getValue();
		}
	}
	
	return "";
}


//User BitQA::HTML::getUserObj(Cgicc cgi){
//	
//	User curUser;
//	
//	string currUsername = getUsername(cgi);
//	sql::Driver *driver;
//	sql::Connection *con;
//	sql::PreparedStatement *prep_stmt;
//	sql::ResultSet *res;
//	
//	driver = get_driver_instance();
//	con = driver->connect(BitQA::Database::HOST,
//						  BitQA::Database::USERNAME,
//						  BitQA::Database::PASSWORD
//						  );
//	
//	con->setSchema(BitQA::Database::SCHEMA);
//	prep_stmt = con->prepareStatement("SELECT *, (select tags from tblUserTags where id = A.id) as 'UserTag', (select reputation from tblUserReputation where username = A.username) as 'Reputation' from tblUser A where username = ?");
//	prep_stmt->setString(1, currUsername);
//	res = prep_stmt->executeQuery();
//	
//	if(res->next()){            //get user info and populate
//		curUser.setUsername(currUsername);
//		curUser.setLocation(res->getString("location"));
//		curUser.setDisplayName(res->getString("displayname"));
//		curUser.setAge(res->getInt("age"));
//		curUser.setEmail(res->getString("email"));
//		curUser.setTag(res->getString("UserTag"));
//		curUser.setReputation(res->getInt("Reputation"));
//		curUser.setID(res->getInt("id"));
//		curUser.setPassword(res->getString("passhash"));
//		
//	}
//	delete prep_stmt;
//	delete con;
//
//	return curUser;
//}



string BitQA::HTML::getUsername(Cgicc cgicc)
{
	CgiEnvironment environment = cgicc.getEnvironment();
	const_cookie_iterator cci;
	
	for (cci = environment.getCookieList().begin();
		 cci != environment.getCookieList().end();
		 cci++) {
		if (cci->getName() == "username") {
			return cci->getValue();
		}
	}
	
	return "";
}

void BitQA::HTML::displayHeader(std::string title, Cgicc cgicc)
{
	
	cout << HTTPHTMLHeader() << endl
		<< "<!DOCTYPE html>" << endl
		<< html() << endl
		<< head() << endl
		<< cgicc::title() << title << cgicc::title() << endl
	
		// Mobile 1st
		<< "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">" << endl
		<< "<link type=\"image/x-icon\" rel=\"shortcut icon\" href=\"/favicon.ico\" />" << endl
	
		// CSS
		<< "<link rel=\"stylesheet\" href=\"/includes/css/bootstrap.min.css\" />" << endl
		<< "<link rel=\"stylesheet\" href=\"/includes/css/style.css\" />" << endl
		<< "<link href=\"//netdna.bootstrapcdn.com/bootstrap/3.0.0/css/bootstrap-glyphicons.css\" rel=\"stylesheet\">" << endl
		<< "<link rel=\"stylesheet\" type=\"text/css\" href=\"https://cdn.datatables.net/u/bs/dt-1.10.12/datatables.min.css\"/>"
		// Scripts
		<< "<script type=\"text/javascript\" src=\"/includes/javascript/jquery.min.js\"></script>" << endl
		<< "<script type=\"text/javascript\" src=\"/includes/javascript/bootstrap.min.js\"></script>" << endl
		<< "<script type=\"text/javascript\" src=\"/includes/javascript/main.js\"></script>" << endl
		<< "<script type=\"text/javascript\" src=\"/includes/javascript/cookie.js\"></script>" << endl
		<< "<script type=\"text/javascript\" src=\"https://cdnjs.cloudflare.com/ajax/libs/Chart.js/2.1.4/Chart.min.js\"></script>"
	    << "<script type=\"text/javascript\" src=\"https://cdn.datatables.net/u/bs/dt-1.10.12/datatables.min.js\"></script>"
		//Google analytics
	<< "<script>(function(i,s,o,g,r,a,m {i['GoogleAnalyticsObject']=r;i[r]=i[r]||function( {(i[r].q=i[r].q||[]).push(arguments)},i[r].l=1*new Date();a=s.createElement(o), m=s.getElementsByTagName(o)[0];a.async=1;a.src=g;m.parentNode.insertBefore(a,m)})(window,document,'script','https://www.google-analytics.com/analytics.js','ga'); ga('create', 'UA-78499119-1', 'auto'); ga('send', 'pageview'); </script>"
	
		<< head() << endl;
	
	
	
	cout << body() << endl;
	
	// Navbar
	cout << "<nav class=\"navbar navbar-default navbar-fixed-top\">" << endl
		<< "<div class=\"container\">" << endl
		<< "<div class=\"navbar-header\">" << endl
			<< "<a class=\"navbar-brand\" style=\"padding:10px;\"><img width=\"30px\" src=\"/images/logo.png\"></a>" << endl
			<< "<a class=\"navbar-brand\" href=\"/\">Bit QA</a>" << endl
		<< "</div>";
	
	cout << "<div id=\"navbar\" class=\"navbar-collapse collapse\"><ul class=\"nav navbar-nav\"><!--<li><a style=\"padding:10px;\"><img width=\"30px\" src=\"/images/logo.png\"></a></li>--><li><a href=\"/post.html\">Post</a></li><li><a href=\"allquestions.html\">Browse</a></li><li><a href=\"report.html\">Report</a></li>";
	cout << "</ul>";
	
	cout << "<div class=\"col-sm-3 col-md-3 pull-right\"><form action=\"search.html\" method=\"post\" class=\"navbar-form\" role=\"search\"><div class=\"input-group\"><input type=\"text\" class=\"form-control\" placeholder=\"Search\" name=\"search\" id=\"search\"><div class=\"input-group-btn\"><button class=\"btn btn-default\" type=\"submit\"><i class=\"glyphicon glyphicon-search\"></i></button></div></div></form></div>";
	
	cout << "<ul class=\"nav navbar-nav navbar-right\">";
	
	if (BitQA::HTML::getLoggedInStatus(cgicc)) {
		/*cout << "<li><a href=\"/profile.html?username="			//old code
			<< BitQA::HTML::getUsername(cgicc)
			<< "\">Welcome, "
		    << BitQA::HTML::getDisplayName(cgicc) << "</a></li>" << endl;
		
        cout <<"<li><a href=\"/editprofile.html\">Edit profile</a></li>"
			<< "<li><a id=\"navBarLogout\" href=\"#\">Logout</a></li>";
		 */
		//try new dropdown toggle
	
		cout << "<li class=\"dropdown\">"
		<< "<a href=\"#\" class =\"dropdown-toggle\" data-toggle=\"dropdown\" role=\"button\" aria-haspopup=\"true\" aria-expanded=\"false\">"
		<< BitQA::HTML::getDisplayName(cgicc)
		<< "<span class=\"caret\"></span></a>"
		<< "<ul class=\"dropdown-menu\">"
		<< "<li><a href=\"/profile.html?username="
		<< BitQA::HTML::getUsername(cgicc) << "\">View profile</a></li>"
		<< "<li><a href=\"/editprofile.html\">Edit profile details</a></li>"
		<< "<li><a href=\"/editpassword.html\">Change password</a></li>"
		<< "<li><a href=\"/accdeactivate.html\">Account deactivation</a></li>"
		<< "<li><a name=\"btnLogout\" id=\"navBarLogout\" href=\"#\">Logout</a></li>"
		<<"</ul>"
		<<"</li>"
		<< endl;
		
	} else {
		cout << "<li><a href=\"login.html\">Login</a></li><li><a href=\"signup.html\">Signup</a></li>";
	}
	
	cout << "</ul>";
	
	cout << "</div></div></nav>";
	
	// Container
	cout << "<div class=\"bitqa-nav-spacer\"></div>"
		<< "<div class=\"container\">";
	cout << "<div style=\"display:none;\" class=\"loading\">Loading&#8230;</div>";
	
	cout << "<div style=\"display:none\" id=\"genericAlert\" class=\"alert alert-danger alert-dismissible\" role=\"alert\">";
	cout << "<button type=\"button\" class=\"close\" data-dismiss=\"alert\" aria-label=\"Close\">";
	cout << "<span aria-hidden=\"true\">&times;</span></button>";
	cout << "<strong>Error</strong>, <span id=\"genericErrorText\">Error Text</span></div>";
	
	// Generic Modal
	cout << "<div id=\"genericModal\" class=\"modal fade\" role=\"dialog\"><div class=\"modal-dialog\"><div class=\"modal-content\"><div class=\"modal-header\"><button type=\"button\" class=\"close\" data-dismiss=\"modal\">&times;</button><h4 class=\"modal-title\">Message</h4></div><div class=\"modal-body\"><div id=\"genericModalBoday\"></div></div><div class=\"modal-footer\"><button type=\"button\" class=\"btn btn-default\" data-dismiss=\"modal\">Close</button></div></div></div></div>";
}

void BitQA::HTML::displayFooter()
{
	cout << "</div>" << endl;
	// cout << "<br><br><div class=\"row\"><hr><br><footer>&copy; BitQA 2016</footer></div><br><br>";
	cout << "<script src=\"/includes/javascript/logout.js\" type=\"text/javascript\"></script>";
	cout << body() << endl
		<< html() << endl;
}

std::string BitQA::HTML::spacer(int height)
{
	return "<div style=\"margin-top: " + to_string(height) + "px;\"></div>";
}

void BitQA::HTML::error(std::string title, std::string message)
{
	cout << "<div class=\"modal fade\" id=\"errorModal\" tabindex=\"-1\" role=\"dialog\"><div class=\"modal-dialog\" role=\"document\"><div class=\"modal-content\"><div class=\"modal-header\"><h4 class=\"modal-title\">Error</h4></div>";
	
	cout << "<div class=\"modal-body\"><div class=\"panel panel-danger\">"
		<< "<div class=\"panel-heading\">" << title << "</div>"
		<< "<div class=\"panel-body\">" << message << "</div>"
		<< "</div>";
	
	cout << "</div><div class=\"modal-footer\"><button type=\"button\" class=\"btn btn-default\" data-dismiss=\"modal\">Close</button></div></div></div></div>";
	
	cout << "<script type=\"text/javascript\">$(document).ready(function(){showError()});</script>";
}
