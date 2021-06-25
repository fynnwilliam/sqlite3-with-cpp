#include "database.h"

bool Database::is_first_ = true;
int Database::total_width_ = 0;

int Database::callback(void *data, int argc, char **argv, char **col_name)
{
    total_width_ = field_width_ * argc + 1;
    if (is_first_)
        print_header(argc, col_name);

    print_body(argc, argv);
    std::cout << '\n';

    return 0;
}

void Database::print_header_line(int const &index, char **col_name)
{
    std::cout.width(field_width_);
    std::cout.setf(std::ios::left);
    std::cout << "| " + static_cast<std::string>(col_name[index]);
}

void Database::print_header(int const &argc, char **col_name)
{
    print_break();
    for (int index = 0; index < argc; index++)
        print_header_line(index, col_name);
    std::cout << "|\n";

    print_break();
    is_first_ = false;
}

void Database::print_body_line(int const &index, char **argv)
{
    std::cout.width(field_width_);
    std::cout.setf(std::ios::left);
    std::cout << "| " + static_cast<std::string>((argv[index] ? argv[index] : "null"));
}

void Database::print_body(int const &argc, char **argv)
{
    for (int index = 0; index < argc; index++)
        print_body_line(index, argv);
    std::cout << '|';
}

void Database::insert_values(std::string const values)
{
    status_ = sqlite3_exec(db_, values.c_str(), NULL, 0, &errmsg_);
    check_status(Operation::insert_values);
}

void Database::create_table(std::string const table)
{
    status_ = sqlite3_exec(db_, table.c_str(), NULL, 0, &errmsg_);
    check_status(Operation::create_table);
}

void Database::select_data(std::string const column)
{
    sqlite3_exec(db_, column.c_str(), callback, NULL, NULL);
    print_break();
    is_first_ = true;
}

void Database::update_data(std::string const fields)
{
    status_ = sqlite3_exec(db_, fields.c_str(), NULL, 0, &errmsg_);
    check_status(Operation::update_data);
}

void Database::delete_data(std::string const alien)
{
    status_ = sqlite3_exec(db_, alien.c_str(), NULL, 0, &errmsg_);
    check_status(Operation::delete_data);
}

void Database::display_data(std::string const all)
{
    sqlite3_exec(db_, all.c_str(), callback, NULL, NULL);
    print_break();
    is_first_ = true;
}

void Database::check_status(Operation sql) const
{
    if (status_ != SQLITE_OK)
    {
        std::cout << "could not " << operations[(int)sql] << ".\n";
        sqlite3_free(errmsg_);
    }
}

void Database::open(std::string const filename)
{
    status_ = sqlite3_open(filename.c_str(), &db_);
    if (status_)
        std::cout << sqlite3_errmsg(db_) << ", check your permisions in the current directory\n";
}

void Database::print_break()
{
    std::cout.width(total_width_);
    std::cout.fill('-');
    std::cout << '-' << '\n';
    std::cout.fill(' ');
}