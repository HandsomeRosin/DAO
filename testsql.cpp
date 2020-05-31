#include "testsql.h"

sqlmap _sqlmap;

int a = 123;
string b = "rosin";
char *c = "handsome";
void initsql() {
    _sqlmap.set("a", &a);
    _sqlmap.set("b", &b);
    _sqlmap.set("c", &c);
}
