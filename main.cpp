#include <iostream>
#include <sqlite3.h>
#include <string>
#include <iomanip>
using namespace std;

int callback(void* data, int argc, char** argv, char** azColName) {
    for(int i = 0; i < argc; i++) {
        cout << azColName[i] << ": " << (argv[i] ? argv[i] : "NULL") << endl;
    }
    cout << endl;
    return 0;
}

void delete_last(sqlite3* data) {
    char* errMsg = 0;
    string sql = "DELETE FROM employees WHERE id = (SELECT MAX(id) FROM employees);";
    sqlite3_exec(data, sql.c_str(), NULL, 0, &errMsg);
}

void write_data(sqlite3* data, string name, string position, int salary) {
    char* errMsg = 0;
    string sql = "INSERT INTO employees (name, position, salary) VALUES ('" + name + "', '" + position + "', " + to_string(salary) + ");";
    sqlite3_exec(data, sql.c_str(), NULL, 0, &errMsg);
}

void delete_data(sqlite3* data, int n) {
    char* errMsg = 0;
    string sql = "DELETE FROM employees WHERE id = " + to_string(n) + ";";
    sqlite3_exec(data, sql.c_str(), NULL, 0, &errMsg);
}

void read_data(sqlite3* data) {
    char* errMsg = 0;
    string sql = "SELECT id, name, position, salary FROM employees;";
    sqlite3_exec(data, sql.c_str(), callback, 0, &errMsg);
}

void last_id(sqlite3* data){
    sqlite3_exec(data, "DELETE FROM employees WHERE id = (SELECT MIN(id) FROM employees);", 0, 0, 0);
}

int main() {
    sqlite3* data;
    sqlite3_open("mydatabase.db", &data);
    
    char* errMsg = 0;
    string sql = "CREATE TABLE IF NOT EXISTS employees ("
                 "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                 "name TEXT NOT NULL,"
                 "position TEXT,"
                 "salary INTEGER);";
    sqlite3_exec(data, sql.c_str(), NULL, 0, &errMsg);

    write_data(data, "12", "21", 2);
    read_data(data);
    delete_last(data);
    
    
    sqlite3_close(data);
    return 0;
}