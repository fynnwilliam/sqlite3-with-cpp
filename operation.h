#include <sqlite3.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

static bool is_first{true};

auto print_break = [](int const &total_width)
{
    std::cout.width(total_width);
    std::cout.fill('-');
    std::cout << '-' << '\n';
    std::cout.fill(' ');
};

auto print_header_line = [](int const &index, char **col_name)
{
    std::cout << std::left << "| " << std::setw(11) << col_name[index];
};

auto print_body_line = [](int const &index, char **argv)
{
    std::cout << std::left << "| " << std::setw(11) << (argv[index] ? argv[index] : "null");
};

void print_header(int const &argc, int const &total_width, char **col_name)
{

    print_break(total_width);
    for (int index = 0; index < argc; index++)
        print_header_line(index, col_name);
    std::cout << "|\n";

    print_break(total_width);
    is_first = false;
}

void print_body(int const &argc, char **argv)
{
    for (int index = 0; index < argc; index++)
        print_body_line(index, argv);
    std::cout << '|';
}

static int total_width{};
static int callback(void *data, int argc, char **argv, char **col_name)
{
    total_width = 13 * argc + 1; // same as, 11 * argc + 2 * argc + 1;
    if (is_first)
        print_header(argc, total_width, col_name);

    print_body(argc, argv);

    std::cout << '\n';

    return 0;
}

static sqlite3 *db;
static int status{};
static char *errmsg;
enum class Operation
{
    create_table,
    insert_values,
    delete_data,
    update_data
};
std::vector<std::string> operations{"create table", "insert values", "delete data", "update data"};

void check_status(int const status, Operation sql)
{
    if (status != SQLITE_OK)
    {
        std::cout << "could not " << operations[(int)sql] << ".\n";
        sqlite3_free(errmsg);
    }
}

void open_database(std::string const filename)
{
    status = sqlite3_open(filename.c_str(), &db);

    if (status)
        std::cout << sqlite3_errmsg(db) << ", check your permisions in the current directory\n";
}

void create_table(std::string const table)
{
    status = sqlite3_exec(db, table.c_str(), NULL, 0, &errmsg);

    check_status(status, Operation::create_table);
}

void insert_values(std::string const values)
{
    status = sqlite3_exec(db, values.c_str(), NULL, 0, &errmsg);

    check_status(status, Operation::insert_values);
}

void delete_data(std::string const alien)
{
    status = sqlite3_exec(db, alien.c_str(), NULL, 0, &errmsg);

    check_status(status, Operation::delete_data);
}

void update_data(std::string const fields)
{
    status = sqlite3_exec(db, fields.c_str(), NULL, 0, &errmsg);

    check_status(status, Operation::update_data);
}

void select_data(std::string const column)
{
    sqlite3_exec(db, column.c_str(), callback, NULL, NULL);

    print_break(total_width);
    is_first = true;
}

void display_data(std::string const all)
{
    sqlite3_exec(db, all.c_str(), callback, NULL, NULL);

    print_break(total_width);
    is_first = true;
}