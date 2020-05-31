#ifndef RAINY_H
#define RAINY_H

#include "testsql.h"

#include <string>
#include <vector>
#include <map>
#include <utility>
#include <stdarg.h>

// 获取属性attr在type类中的地址偏移量
#define GETOFFSET(attr, type) ((size_t)&(((type *)0)->attr))
// #define REGIST(tableName, fieldName, structName, fieldType) (s_mapping_table[#tableName][#fieldName]=fieldpair(GETOFFSET(fieldName, structName), fieldType))  // NOLINT

// 注册函数，参数分别是(表名，表中字段名，db结构体名，字段类型，db结构体中的属性名)
#define REGIST(tableName, fieldName, structName, fieldType, attrName)\
    do { \
        structName tmp; \
        domainInfo _domainInfo = {(size_t)(((char *)&(tmp.attrName) - (char *)&tmp)), fieldType}; \
        s_mapping_table[#tableName][#fieldName] = _domainInfo; \
    } while(0);

enum FieldType {
    STRING, INT, BOOL, CHAR, DOUBLE
};

struct domainInfo {
    size_t first;       // 地址偏移量
    FieldType second;   // 字段类型
};

typedef std::map<std::string, std::map<std::string, domainInfo > > tablemap;
typedef std::map<std::string, domainInfo > fieldmap;
typedef domainInfo fieldpair;

// 属性在类中的地址偏移量与其属性名字符串的映射关系表 <表名, <属性名, <属性地址偏移量, 字段类型枚举>>>
extern tablemap s_mapping_table;

/*
 * 为了能在C++中使用类似java的静态代码块的功能。
 * 使用方法:
 * void func () { init code... }
 * static initHelper tmp(func);
 */
class initHelper {
 public:
    initHelper(void (*func)());
};

void genQuerySQL(const std::string &tableName, const std::string &sqlCondition,
    std::string &result, std::vector<std::string> *const fields = NULL);

#endif // RAINY_H
