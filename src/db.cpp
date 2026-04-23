#include "functions.h"
#include <functional>
#include <vector>

bool exists(const Database& database, int id) {
    return database.db.count(id) > 0;
}

bool insert(Database& database, int id, int age, const std::string& name) {
    if (exists(database, id)) return false;

    auto [_, inserted] = database.db.emplace(id, Record{name, id, age});
    return inserted;
}

bool remove(Database& database, int id) {
    return database.db.erase(id) > 0;
}

std::vector<Record> select(const Database& database, std::function<bool(const Record&)> condition) {
    std::vector<Record> results;
    for (const auto& [_, record] : database.db) {
        if (condition(record)) results.push_back(record);
    }
    return results;
}

bool update(Database& database, int id, std::optional<int> age, std::optional<std::string> name) {
    auto it = database.db.find(id);
    if (it == database.db.end()) return false;

    Record& record = it->second;

    if (age) record.age = *age;
    if (name) record.name = *name;

    return true;
}
