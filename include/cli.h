#pragma once

#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

#include "functions.h"

extern std::unordered_map<
    std::string,
    std::function<void(Database&, std::vector<std::string>&)>
> commands;

void handleInsert(Database& db, std::vector<std::string>& tokens);
void handleRemove(Database& db, std::vector<std::string>& tokens);
void handleUpdate(Database& db, std::vector<std::string>& tokens);
void handleSelect(Database& db, std::vector<std::string>& tokens);