#include "functions.h"
#include "cli.h"

#include <iostream>
#include <ctime>
#include <chrono>

std::unordered_map<
    std::string,
    std::function<void(Database&, std::vector<std::string>&)>
> commands;

static std::vector<std::string> tokenize(const std::string& line) {
    std::vector<std::string> tokens;
    std::string temp;

    for (char c : line) {
        if (c == ' ') {
            if (!temp.empty()) {
                tokens.push_back(temp);
                temp.clear();
            }
        } else {
            temp += c;
        }
    }

    if (!temp.empty()) {
        tokens.push_back(temp);
    }

    return tokens;
}

int main() {
    Database db;

    commands["INSERT"] = handleInsert;
    commands["REMOVE"] = handleRemove;
    commands["UPDATE"] = handleUpdate;
    commands["SELECT"] = handleSelect;

    std::cout << "MiniDB CLI started. Type EXIT to quit.\n";

    std::string line;

    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, line)) break;

        if (line == "EXIT") break;

        std::vector<std::string> tokens = tokenize(line);

        if (tokens.empty()) continue;

        auto it = commands.find(tokens[0]);

        if (it != commands.end()) {
            it->second(db, tokens);
        } else {
            std::cout << "Unknown command\n";
        }
    }

    return 0;
}
