#include "database.h"
#include "query.h"
    
int main()
{
    database db;

    std::cout << "opening database...\n";
    db.open("example.db");

    std::cout << "creating tables...\n";
    db.create_table(table);

    std::cout << "inserting and displaying values...\n";
    db.insert_values(values);
    db.display_data(all);

    std::cout << "deleting a record...\n";
    db.delete_data(alien);

    std::cout << "updating some fields...\n";
    db.update_data(fields);
    db.display_data(after_update);
	
    db.display_data(all);

    std::cout << "displaying selected columns...\n";
    db.select_data(column);

    return 0;
}