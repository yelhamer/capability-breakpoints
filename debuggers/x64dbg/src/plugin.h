#pragma once

#include "datastructure.h"
#include "pluginmain.h"
#include "pluginsdk/bridgemain.h"
#include "x64dbg-debugger.h"

#include <memory>
#include <string>
#include <unordered_map>

class Rule;

// The actual vector is defined in plugin.cpp.
extern std::vector<std::shared_ptr<Rule>> rules;
std::shared_ptr<Rule> addRule(std::string ruleName, std::string ruleExpression);
void removeRule(size_t index);

// functions
bool pluginInit(PLUG_INITSTRUCT* initStruct);
void pluginStop();
void pluginSetup();
