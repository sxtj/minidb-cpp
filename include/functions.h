#pragma once

#include <iostream>
#include <stdexcept>
#include <unordered_map>
#include <vector>
#include <string>
#include <functional>
#include <optional>


struct Record {
    std::string name;
    int id;
    int age;

    Record(const std::string& n, int i, int a)
        : name(n), id(i), age(a)
    {
        if (i < 0) {
            throw std::invalid_argument("id must be positive");
        }
    }
};


struct Database {
    // id -> record (cleaner + safer than vector + index combo)
    std::unordered_map<int, Record> db;
};


bool insert(Database& database, int id, int age, const std::string& name);
bool remove(Database& database, int id);

std::vector<Record>
select(const Database& database,
       std::function<bool(const Record&)> condition);

bool update(Database& database,
            int id,
            std::optional<int> age,
            std::optional<std::string> name);

bool exists(const Database& database, int id);