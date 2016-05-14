load data local infile '/Users/Asjad/Desktop/222import/tblQuestionsInserted.csv' into table tmpimport
fields terminated by ',' enclosed by '"' lines terminated by '\n' (id, title, descr, tags, user);

create table tmpimport(
id int,
title text,
descr text,
tags text,
user varchar(45)
);


select * from tmpimport;

select * from tblUser;

delete from tmpimport where username = 'id';


