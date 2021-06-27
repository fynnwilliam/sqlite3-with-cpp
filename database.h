#include <sqlite3.h>
#include <iostream>
#include <string>
#include <vector>

class database
{
private:
    static bool is_first_;
    constexpr static int field_width_ = 15;
    static int total_width_;
    char *errmsg_;
    sqlite3 *db_;
    int status_{};

    enum class operation
    {
        create_table,
        insert_values,
        delete_data,
        update_data
    };

    std::vector<std::string> operations{"create table", "insert values", "delete data", "update data"};

    static int callback(void *data, int argc, char **argv, char **col_name);
    static void print_header_line(int const &index, char **col_name);
    static void print_header(int const &argc, char **col_name);
    static void print_body_line(int const &index, char **argv);
    static void print_body(int const &argc, char **argv);
    static void print_break();
    void check_status(operation sql) const;

public:
    database() :  status_(0), errmsg_(nullptr), db_(nullptr){}
    void insert_values(std::string const values);
    void create_table(std::string const table);
    void select_data(std::string const column);
    void update_data(std::string const fields);
    void delete_data(std::string const alien);
    void display_data(std::string const all);
    void open(std::string const filename);
    ~database() { sqlite3_close(db_); }
};