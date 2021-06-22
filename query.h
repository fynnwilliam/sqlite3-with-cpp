std::string all("select * from Test;");

std::string table("create table Test("
                  "ID int primary key not null, "
                  "FirstName varchar(255) not null, "
                  "MiddleName varchar(255), "
                  "LastName varchar(255) not null, "
                  "Age int not null, "
                  "Address varchar(255), "
                  "Salary real);");

std::string insert("insert into Test values(1, 'Ama', '', 'Kerls', 21, 'New York', 10000.00);"
                   "insert into Test values(2, 'Jim', '', 'Smith', 31, 'Otawa', 12000.00);"
                   "insert into Test values(3, 'Kimberley', 'J.', 'Wiggles', 22, 'Illinois', 22000.00);");

std::string alien("delete from Test where ID = 2;");

std::string column("select ID, FirstName, LastName, Salary from Test;");
