#ifndef TESTSQL_H
#define TESTSQL_H

#include <map>
#include <string>
#include <iostream>
using namespace std;

class sqlmap {
 public:
    map<string, void*> m_data;

    template<typename T>
    void set(string key, T *value) {
        m_data[key] = (void*)value;
    }
    
    template<typename T>
    T get(string key) {
        return *((T*)m_data[key]);
    }

    int getInt(string key) {
        return get<int>(key);
    }
    string getString(string key) {
        return get<string>(key);
    }
    bool getBoolean(string key) {
        return get<bool>(key);
    }
    double getDouble(string key) {
        return get<double>(key);
    }

    void* getByIndex(int index) {
        switch(index) {
            case 0:
                return m_data["a"];
            case 1:
                return m_data["b"];
            case 2:
                return m_data["c"]
        }
    }
};
extern sqlmap _sqlmap;

extern int a;
extern string b;
extern char *c;
void initsql();

#endif
