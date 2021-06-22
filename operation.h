#include <sqlite3.h>
#include <iostream>
#include <string>

static int callback(void* data, int argc, char** argv, char** col_name)
{
    for(int i = 0; i < argc; i++)
        std::cout << col_name[i] << ": " << (argv[i] ? argv[i] : "null") << '\n';

    std::cout << '\n';

    return 0;
}

static sqlite3* db;
static int status{};
static char* errmsg;

void open_database(std::string filename)
{
    status = sqlite3_open(filename.c_str(), &db);

    if(status)
        std::cout << sqlite3_errmsg(db) << ", check your permisions in the current directory" << std::endl;
    else
        std::cout << "successfully opened database.\n";
}

void create_table(std::string table)
{
    status = sqlite3_exec(db, table.c_str(), NULL, 0, &errmsg);

    if(status != SQLITE_OK)
    {
        std::cout << "could not create table.\n";
        sqlite3_free(errmsg);
    }
    else
    {
        std::cout << "successfully created table.\n";
    }
}

void insert_values(std::string insert)
{
    status = sqlite3_exec(db, insert.c_str(), NULL, 0, &errmsg);

    if(status != SQLITE_OK)
    {
        std::cout << "could not insert values.\n";
        sqlite3_free(errmsg);
    }
    else
    {
        std::cout << "successfully inserted values.\n";
    }
}

void delete_data(std::string alien)
{
    status = sqlite3_exec(db, alien.c_str(), NULL, 0, &errmsg);

    if(status != SQLITE_OK)
    {
        std::cout << "could not delete data.\n";
        sqlite3_free(errmsg);
    }
    else
    {
        std::cout << "successfully removed data.\n";
    }
}

void update_data(std::string update)
{
	status = sqlite3_exec(db, update.c_str(), NULL, 0, &errmsg);

	if(status != SQLITE_OK)
	{
		std::cout << "could not update data.\n";
		sqlite3_free(errmsg);
	}
	else
	{
		std::cout << "successfully updated data.\n";
	}
}

void select_data(std::string column)
{
    sqlite3_exec(db, column.c_str(), callback, NULL, NULL);
}

void display_data(std::string all)
{
    sqlite3_exec(db, all.c_str(), callback, NULL, NULL);
}
