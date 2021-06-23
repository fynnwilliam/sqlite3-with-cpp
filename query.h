#pragma once
#include <string>

std::string all("select * from Test;");

std::string table("create table Test("
                  "EmployeeID int primary key not null, "
                  "FirstName varchar(255) not null, "
                  "MiddleName varchar(255), "
                  "LastName varchar(255) not null, "
                  "Age int not null, "
                  "Address varchar(255), "
                  "Salary real, "
                  "check (age > 0));");

std::string values("insert into Test values(1, 'Ama', '', 'Kerls', 21, 'New York', 10000.00);"
                   "insert into Test values(2, 'Jim', '', 'Smith', 31, 'Otawa', 12000.00);"
                   "insert into Test values(3, 'Kimberley', 'J.', 'Wiggles', 22, 'Illinois', 22000.00);"
                   "insert into Test values(4, 'fname', 'mname', 'lname', 18, 'location', 1000000.00);");

std::string alien("delete from Test where EmployeeID = 4;");

std::string fields("update Test "
                   "set Salary = '14000', Address = 'Ottawa' "
                   "where EmployeeID = 2;");

std::string after_update("select * from Test "
                         "where EmployeeID = 2 and FirstName = 'Jim';");

std::string column("select EmployeeID, FirstName, LastName, Salary from Test;");