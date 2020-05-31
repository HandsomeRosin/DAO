#include "rainy.h"
#include <stdio.h>

// 启用该标志位则会启用字段注册检查逻辑，若检验到字段未注册则会抛出异常
// 并且会启用查询修改前检测逻辑
// #define CHECK_FIELDS_REGISTED_FLAG

const int MAX_SQL_LENGTH = 1024;

tablemap s_mapping_table;

initHelper::initHelper(void (*func)()) {
    func();
}

/*
 * 检查field是否在fields数组中。
 */
bool checkFieldNameExsited(const std::string &field, std::vector<std::string> *const fields = NULL) {
    if (fields == NULL) {
        return true;
    }
    int i_size = fields->size();
    for (int i = 0; i < i_size; ++i) {
        if ((*fields)[i] == field) {
            return true;
        }
    }
    return false;
}

/*
 * 生成查询sql
 * @param tableName 需要查询的表名
 * @param sqlCondition 查询条件语句如WHERE, LIMIT
 * @param fields 需要查询的字段名数组
 * @return result 返回的查询sql字符串
 */
void genQuerySQL(const std::string &tableName, const std::string &sqlCondition,
    std::string &result, std::vector<std::string> *const fields) 
{

#ifdef CHECK_FIELDS_REGISTED_FLAG
    checkFieldsRegisted(tableName, fields);  // 检查
#endif

    char sz_sql[MAX_SQL_LENGTH + 1];

    //拼接所有字段名
    std::string sz_fields;
    fieldmap _fieldmap = s_mapping_table[tableName];
    // 遍历字段映射来查找fields中的指定字段，为了保证拼接的顺序是以map的遍历顺序来的。
    for (fieldmap::iterator it = _fieldmap.begin(); it != _fieldmap.end(); ++it) {
        if (checkFieldNameExsited(it->first, fields)) {
            sz_fields += it->first + ',';
        }
    }
    if (fields == NULL || fields->begin() != fields->end()) {  // 如果字段数组非空，则去除最后一个逗号
        sz_fields.erase(sz_fields.end() - 1);
    }

    snprintf(sz_sql, MAX_SQL_LENGTH, "SELECT %s FROM %s %s", sz_fields.c_str(),
        tableName.c_str(), sqlCondition.c_str());

    result = std::string(sz_sql);
}

void getFromSqlResult(void *domain, const std::string tableName, const std::vector<std::string> &fields, sqlmap &sqlresult) {
    fieldmap _fieldmap = s_mapping_table[tableName];

}

void setVal(void* ptr, sqlmap &sqlresult, int index) {
    *((int *)ptr) = *((int *)sqlresult.getByIndex(index));
}

/*
 * 检查fields中的字段名是否都已注册在映射表中
 * @param tableName 表名
 * @param fields 字段名数组
 * @return 字段名是否都已注册在映射表中
 */
bool checkFieldsRegisted(const std::string &tableName, const std::vector<std::string> &fields)
{
    fieldmap &tmp = s_mapping_table[tableName];

    int i_size = fields.size();
    for (int i = 0; i < i_size; ++i) {
        if (tmp.find(fields[i]) == tmp.end()) {  // 若找不到it所指键值
#ifdef CHECK_FIELDS_REGISTED_FLAG
            char sz_err[64];
            snprintf(sz_err, 63, "%s中%s未注册", tableName.c_str(), it->c_str());
            throw exception(sz_err);
#else
            return false;
#endif
        }
    }

    return true;
}
