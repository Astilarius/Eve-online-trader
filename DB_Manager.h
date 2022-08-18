#pragma once
#include <sqlite3.h>

typedef std::map<int, System> systemMap;
typedef std::map<int, Item> itemMap;
class DB_Manager
{
public:
	typedef std::map<int, System> systemMap;
	typedef std::map<int, Item> itemMap;
	static systemMap getSystems();
	static itemMap getItems();
	static void writeResults(std::vector<Difference> input);
};

systemMap DB_Manager::getSystems()
{
	sqlite3* db;
	sqlite3_stmt* stmt = NULL;
	char* str;

	if (sqlite3_open("database.db", &db) == SQLITE_OK)
	{
		sqlite3_prepare(db, "SELECT * FROM SYSTEMS", -1, &stmt, NULL);
	}
	else
	{
		std::cout << "Failed to open db\n";
	}

	systemMap sys;
	System sus;
	std::string tempstr;
	while (sqlite3_step(stmt) == 100)
	{
		sus.system_id = sqlite3_column_int64(stmt, 0);
		sus.system_name = std::string((char*)sqlite3_column_text(stmt, 1));
		sus.security_status = sqlite3_column_double(stmt, 2);
		sys.insert(systemMap::value_type(sus.system_id, sus));
	}
	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return sys;
}

itemMap DB_Manager::getItems()
{
	sqlite3* db;
	sqlite3_stmt* stmt = NULL;
	char* str;

	if (sqlite3_open("database.db", &db) == SQLITE_OK)
	{
		sqlite3_prepare(db, "SELECT * FROM ITEMS", -1, &stmt, NULL);
	}
	else
	{
		std::cout << "Failed to open db\n";
	}
	itemMap sys;
	Item sus;
	std::string tempstr;
	while (sqlite3_step(stmt) == 100)
	{
		sus.type_id = sqlite3_column_int(stmt, 0);
		sus.market_group_id = sqlite3_column_int(stmt, 1);
		sus.item_name = std::string((char*)sqlite3_column_text(stmt, 2));
		sus.volume = sqlite3_column_double(stmt, 3);
		sus.group_id = sqlite3_column_int(stmt, 4);
		sys.insert(itemMap::value_type(sus.type_id, sus));
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return sys;
}

void DB_Manager::writeResults(std::vector<Difference> input)
{
	sqlite3* db;
	sqlite3_stmt* stmt = NULL;
	char* str;
	char* zErrMsg = 0;
	int rc;
	std::string sql;

	rc = sqlite3_open("database.db", &db);
	if (rc) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
	}

	rc = sqlite3_exec(db, "DELETE FROM RESULTS", NULL, 0, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}

	for (auto it = input.begin(); it != input.end(); it++)
	{
		sql = "INSERT OR IGNORE INTO RESULTS VALUES ('" +
			(*it).buy.item_name + "', " +
			std::to_string((*it).quantity) + ", " +
			std::to_string((*it).diff) + ", " +
			std::to_string((*it).totaldiff) + ", " +
			std::to_string((*it).diff_per_jump) + ", " +
			std::to_string((*it).buy.price) + ", " +
			std::to_string((*it).sell.price) + ", '" +
			(*it).buy.system_name + "', '" +
			(*it).sell.system_name + "', " +
			std::to_string((*it).totalvolume) + ")";


		rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &zErrMsg);

		if (rc != SQLITE_OK) {
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
		}
	}

	sqlite3_close(db);
}