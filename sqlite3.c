#include <stdio.h>
#include <unistd.h>
#include <sqlite3.h>

// gcc -o sqlite3 sqlite3.c -lsqlite3

#define DB_PATH "./demo.db"

#ifndef bool
typedef enum { true, false } bool;
#endif

int common_cb(void *not_used, int argc, char **argv, char **col_name)
{
	int i;
	for (i = 0; i < argc; i++) {
		printf("%s = %s\n", col_name[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

bool exec_sqlite3_cmd(sqlite3 * db, char *sql, sqlite3_callback cb)
{
	int ret;
	char *err_msg = 0;

	ret = sqlite3_exec(db, sql, cb, 0, &err_msg);
	if (ret != SQLITE_OK) {
		fprintf(stderr, "SQLite3 error: %s,%s\n", err_msg, sql);
		sqlite3_free(err_msg);
	}

	return true;
}

bool init_db(sqlite3 ** db)
{
	char *sql;
	int ret, no_table_found = 0;

	if (0 != access(DB_PATH, W_OK))
		no_table_found = 1;

	ret = sqlite3_open_v2(DB_PATH, db, SQLITE_OPEN_READWRITE |
			      SQLITE_OPEN_CREATE, NULL);
	if (SQLITE_OK != ret) {
		fprintf(stderr, "Can't open database: %s\n",
			sqlite3_errmsg(*db));
		return false;
	}

	if (1 == no_table_found) {
		sql = "create table demo(id integer primary key,"
		    "val text default 'UNKNOWN');";
		exec_sqlite3_cmd(*db, sql, common_cb);
	}
	return true;
}

bool exec_sqlite3_select(sqlite3 * db, char *sql)
{
	int i, j;
	char **result;
	char *err_msg;
	int nrows, ncols;

	sqlite3_get_table(db, sql, &result, &nrows, &ncols, &err_msg);

	for (i = 0; i <= nrows; i++) {	/* '<=' : because the first line is header */
		for (j = 0; j < ncols; j++)
			printf("%s\t", result[i * ncols + j]);
		printf("\n");
	}

	sqlite3_free(err_msg);
	sqlite3_free_table(result);

	if (nrows > 0)
		return true;
	else
		return false;
}

void some_operations(sqlite3 * db)
{
	char sql[256];

	snprintf(sql, 256, "insert into demo(id, val) values(%d, '%s');", 1,
		 "hello");
	exec_sqlite3_cmd(db, sql, common_cb);

	exec_sqlite3_cmd(db, "insert into demo(id, val) values(2, 'world');",
			 common_cb);

	exec_sqlite3_cmd(db,
			 "update demo set val = 'hello1' where val = 'hello';",
			 common_cb);
}

int main(int argc, char *argv[])
{
	sqlite3 *demo_db;

	if (false == init_db(&demo_db))
		return -1;

	some_operations(demo_db);
	exec_sqlite3_select(demo_db, "select * from demo;");

	sqlite3_close(demo_db);
	return 0;
}
