build:
	g++ -std=c++0x includes/database.cpp includes/html.cpp drivers/index.cpp -o ../www/index.html -lmysqlcppconn -lcgicc
	g++ -std=c++0x includes/database.cpp includes/html.cpp process/post.cpp drivers/post.cpp -o ../www/post.html -lmysqlcppconn -lcgicc
	g++ -std=c++0x includes/database.cpp includes/html.cpp process/question.cpp process/comment.cpp drivers/question.cpp -o ../www/question.html -lmysqlcppconn -lcgicc
    g++ -std=c++0x includes/database.cpp includes/html.cpp process/browse.cpp drivers/browse.cpp -o ../www/browse.html -lmysqlcppconn -lcgicc
