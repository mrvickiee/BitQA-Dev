#include "../process/question.hpp"
#include "../process/comment.hpp"
#include "../process/answer.hpp"
#include "../includes/html.hpp"
#include "../includes/database.hpp"
#include "../process/vote.hpp"
#include "../includes/profile.hpp"

using namespace cgicc;
using namespace std;

void getContent(string contentID)
{
	string content = "";
	
	sql::Driver *driver;
	sql::Connection *con;
	sql::Statement *stmt;
	sql::ResultSet *res;
	
	
	driver = get_driver_instance();
	con = driver->connect(BitQA::Database::HOST,
						  BitQA::Database::USERNAME,
						  BitQA::Database::PASSWORD
						  );
	
	con->setSchema(BitQA::Database::SCHEMA);
	
	stmt = con->createStatement();
	
	res = stmt->executeQuery("SELECT content FROM BitQA.tblContent WHERE id = '" + contentID + "'");
	
	while (res->next()) {
		content = res->getString("content");
	}
	cout << "<form action=\"\" method=\"post\">";
	cout << "<textarea name=\"content\" class=\"form-control\" rows=\"3\">" << content << "</textarea>" << endl;
	cout << "<br><button type=\"submit\" class=\"btn btn-primary\">Submit</button>";
	cout << "</form>";
	
	delete res;
	delete stmt;
	delete con;
}

void updateContent(string contentID, string newContent)
{
	sql::Driver *driver;
	sql::Connection *con;
	sql::PreparedStatement *prep_stmt;
	
	driver = get_driver_instance();
	con = driver->connect(BitQA::Database::HOST,
						  BitQA::Database::USERNAME,
						  BitQA::Database::PASSWORD
						  );
	
	con->setSchema(BitQA::Database::SCHEMA);
	
	prep_stmt = con->prepareStatement("CALL ProcUpdateContent(?, ?);");
	prep_stmt->setString(1, contentID);
	prep_stmt->setString(2, newContent);
	prep_stmt->execute();
	
	delete prep_stmt;
	delete con;
}

int main()
{
	Cgicc cgicc;
	
	BitQA::HTML::displayHeader("Edit Content", cgicc);
	
	cout << "<h1>Editing</h1>" << endl;
	
	CgiEnvironment environment = cgicc.getEnvironment();
	
	string contentID = "", questionID = "", content = "";
	
	contentID = cgicc("contentid");
	questionID = cgicc("questionid");
	content = cgicc("content");
	
	// Validation
	if ((contentID.length() > 0) ||
		(questionID.length() > 0)
		) {
		
		if (environment.getRequestMethod() == "POST") {

			updateContent(contentID, content);
			
			cout << "<div class=\"alert alert-success\"><strong>Success!</strong> Content Updated.</div>";
			cout << "<script>setTimeout(function(){window.location = \"/question.html?id=" << questionID << "\";}, 1500);</script>";
			
		} else {
			getContent(contentID);
		}
		
	} else {
		cout << "<p>Invalid Inputs</p>";
	}
	
	BitQA::HTML::displayFooter();
}
