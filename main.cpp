#include "rainy.h"
#include "testsql.h"

#include <string>
#include <iostream>
#include <map>
#include <time.h>
using namespace std;  // NOLINT

struct struct1 {
    char *attr1;
    int64_t attr2;
    double attr3;
};

struct struct2 {
    string attr1;
};

void func();
// 相当于静态代码块
static initHelper tmp(func);
void func() {
    REGIST(table1, Field1, struct1, STRING, attr1);
    REGIST(table1, Field2, struct1, INT, attr2);
    REGIST(table1, Field3, struct1, DOUBLE, attr3);
    REGIST(table2, Field1, struct2, STRING, attr1);
}
void printMappingTable();
int main() {
    // testsql part
    initsql();
    int a = _sqlmap.get<int>("a");
    cout << a << endl;
    cout << _sqlmap.get<string>("b") << endl;
    cout << _sqlmap.get<char*>("c") << endl;

    cout << sizeof(string) << endl;


    printMappingTable();
    string sql;
    vector<string> v;
    v.push_back("attr3");
    v.push_back("attr2");
    genQuerySQL("table1", "WHERE Field2 > 0", sql);
    cout << sql << endl;
}

void printMappingTable() {
    cout << "-------------------------------------------------\n";
    for (tablemap::iterator oit = s_mapping_table.begin(); oit != s_mapping_table.end(); ++oit) {
        cout << oit->first << endl;
        fieldmap tmp = oit->second;
        for (fieldmap::iterator it = tmp.begin(); it != tmp.end(); ++it) {
            cout << "{" << it->first << ":<" << it->second.first << ", " << it->second.second << ">}" << endl;
        }

    }
    cout << "-------------------------------------------------\n";
}
