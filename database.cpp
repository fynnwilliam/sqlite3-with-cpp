#include "database.h"

bool database::is_first_ = true;
int database::total_width_ = 0;

int database::callback(void *data, int argc, char **argv, char **col_name)
{
    total_width_ = field_width_ * argc + 1;
    if (is_first_)
        print_header(argc, col_name);

    print_body(argc, argv);
    std::cout << '\n';

    return 0;
}

void database::print_header_line(int const &index, char **col_name)
{
    std::cout.width(field_width_);
    std::cout.setf(std::ios::left);
    std::cout << "| " + static_cast<std::string>(col_name[index]);
}

void database::print_header(int const &argc, char **col_name)
{
    print_break();
    for (int index = 0; index < argc; index++)
        print_header_line(index, col_name);
    std::cout << "|\n";

    print_break();
    is_first_ = false;
}

void database::print_body_line(int const &index, char **argv)
{
    std::cout.width(field_width_);
    std::cout.setf(std::ios::left);
    std::cout << "| " + static_cast<std::string>((argv[index] ? argv[index] : "null"));
}

void database::print_body(int const &argc, char **argv)
{
    for (int index = 0; index < argc; index++)
        print_body_line(index, argv);
    std::cout << '|';
}

void database::insert_values(std::string const values)
{
    status_ = sqlite3_exec(db_, values.c_str(), nullptr, nullptr, &errmsg_);
    check_status(operation::insert_values);
}

void database::create_table(std::string const table)
{
    status_ = sqlite3_exec(db_, table.c_str(), nullptr, nullptr, &errmsg_);
    check_status(operation::create_table);
}

void database::select_data(std::string const column)
{
    sqlite3_exec(db_, column.c_str(), callback, nullptr, nullptr);
    print_break();
    is_first_ = true;
}

void database::update_data(std::string const fields)
{
    status_ = sqlite3_exec(db_, fields.c_str(), nullptr, nullptr, &errmsg_);
    check_status(operation::update_data);
}

void database::delete_data(std::string const alien)
{
    status_ = sqlite3_exec(db_, alien.c_str(), nullptr, nullptr, &errmsg_);
    check_status(operation::delete_data);
}

void database::display_data(std::string const all)
{
    sqlite3_exec(db_, all.c_str(), callback, nullptr, nullptr);
    print_break();
    is_first_ = true;
}

void database::check_status(operation sql) const
{
    if (status_ != SQLITE_OK)
    {
        std::cout << "could not " << operations[(int)sql] << ".\n";
        sqlite3_free(errmsg_);
    }
}

void database::open(std::string const filename)
{
    status_ = sqlite3_open(filename.c_str(), &db_);
    if (status_)
        std::cout << sqlite3_errmsg(db_) << ", check your permisions in the current directory\n";
}

void database::print_break()
{
    std::cout.width(total_width_);
    std::cout.fill('-');
    std::cout << '-' << '\n';
    std::cout.fill(' ');
}