build:
	g++ -std=c++0x includes/database.cpp includes/html.cpp drivers/index.cpp -o ../www/index.html -lmysqlcppconn -lcgicc
	g++ -std=c++0x includes/database.cpp includes/html.cpp drivers/post.cpp -o ../www/post.html -lmysqlcppconn -lcgicc
	g++ -std=c++0x includes/database.cpp includes/html.cpp process/question.cpp process/comment.cpp drivers/question.cpp -o ../www/question.html -lmysqlcppconn -lcgicc
	g++ -std=c++0x includes/database.cpp includes/html.cpp process/browse.cpp drivers/browse.cpp -o ../www/browse.html -lmysqlcppconn -lcgicc
	g++ -std=c++0x includes/database.cpp includes/md5.cpp includes/html.cpp process/user.cpp drivers/signup.cpp -o ../www/signup.html -lmysqlcppconn -lcgicc
	g++ -std=c++0x includes/database.cpp includes/md5.cpp includes/html.cpp process/user.cpp drivers/login.cpp -o ../www/login.html -lmysqlcppconn -lcgicc
	g++ -std=c++0x includes/database.cpp includes/html.cpp process/search.cpp drivers/search.cpp -o ../www/search.html -lmysqlcppconn -lcgicc
current:
	g++ -std=c++0x includes/database.cpp includes/html.cpp process/search.cpp drivers/search.cpp -o ../www/search.html -lmysqlcppconn -lcgicc
