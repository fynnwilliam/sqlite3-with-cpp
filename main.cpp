#include "operation.h"
#include "query.h"
    
int main()
{
    open_database("example.db");

    create_table(table);

    insert_values(insert);
    display_data(all);

    delete_data(alien);
    display_data(all);

	std::cout << "displaying selected columns...\n";
    select_data(column);

    sqlite3_close(db);

    return 0;
}
