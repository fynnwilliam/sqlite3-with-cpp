#include "operation.h"
#include "query.h"
    
int main()
{
    std::cout << "opening database...\n";
	open_database("example.db");

    std::cout << "creating tables...\n";
	create_table(table);

    std::cout << "inserting and displaying values...\n";
	insert_values(values);
    display_data(all);

    std::cout << "deleting a record...\n";
	delete_data(alien);

    std::cout << "updating some fields...\n";
	update_data(fields);
    display_data(after_update);
	
    std::cout << "displaying selected columns...\n";
    select_data(column);

    sqlite3_close(db);

    return 0;
}
