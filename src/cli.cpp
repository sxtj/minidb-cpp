#include <exception>
#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <optional>

#include "cli.h"
#include "functions.h"


void handleInsert(Database& db, std::vector<std::string>& tokens) {
    if (tokens.size() < 4) {
        std::cout << "Usage: INSERT <id> <age> <name>\n";
        return;
    }

    int id, age;

    try {
        id = std::stoi(tokens[1]);
        age = std::stoi(tokens[2]);
    } catch (const std::exception&) {
        std::cout << "Invalid ID or age. Both must be numbers.\n";
        return;
    }

    if (id < 0) {
        std::cout << "Invalid ID. must be positive.\n";
        return;
    }

    std::string name = tokens[3];

    if (insert(db, id, age, name))
        std::cout << "inserted\n";
    else
        std::cout << "ID already exists\n";
}


void handleRemove(Database& db, std::vector<std::string>& tokens) {
    if (tokens.size() < 2) {
        std::cout << "Usage: REMOVE <ID>\n";
        return;
    }

    int id;

    try {
        id = std::stoi(tokens[1]);
    } catch (const std::exception&) {
        std::cout << "Invalid ID. must be a number.\n";
        return;
    }

    if (id < 0) {
        std::cout << "Invalid ID. must be positive.\n";
        return;
    }

    if (remove(db, id)) {
        std::cout << "Removed successfully\n";
    } else {
        std::cout << "ID not found\n";
    }
}


void handleUpdate(Database& db, std::vector<std::string>& tokens) {
    if (tokens.size() < 2) {
        std::cout << "Usage: UPDATE <id> [age=<value>] [name=<value>]\n";
        return;
    }

    int id;

    try {
        id = std::stoi(tokens[1]);
    } catch (const std::exception&) {
        std::cout << "Invalid ID. must be a number\n";
        return;
    }

    if (id < 0) {
        std::cout << "Invalid ID. must be positive\n";
        return;
    }

    std::optional<int> age;
    std::optional<std::string> name;

    // FIX: loop condition was broken
    for (size_t i = 2; i < tokens.size(); i++) {

        if (tokens[i].rfind("age=", 0) == 0) {
            try {
                age = std::stoi(tokens[i].substr(4));
            } catch (...) {
                std::cout << "Invalid age value\n";
                return;
            }
        } 
        else if (tokens[i].rfind("name=", 0) == 0) {
            name = tokens[i].substr(5);
        }
    }

    if (update(db, id, age, name)) {
        std::cout << "Updated successfully\n";
    } else {
        std::cout << "ID not found\n";
    }
}


void handleSelect(Database& db, std::vector<std::string>& tokens) {
    if (tokens.size() < 2) {
        std::cout << "Usage: SELECT ALL | SELECT <id>\n";
        return;
    }

    std::vector<Record> results;

    if (tokens[1] == "ALL") {
        results = select(db, [](const Record&) {
            return true;
        });
    } 
    else {
        int id;

        try {
            id = std::stoi(tokens[1]);
        } catch (const std::exception&) {
            std::cout << "Invalid ID\n";
            return;
        }

        if (id < 0) {
            std::cout << "Invalid ID. must be positive\n";
            return;
        }

        results = select(db, [id](const Record& r) {
            return r.id == id;
        });
    }

    if (results.empty()) {
        std::cout << "No records found\n";
        return;
    }

    for (const auto& r : results) {
        std::cout << "ID: " << r.id
                  << " Age: " << r.age
                  << " Name: " << r.name << "\n";
    }
}
