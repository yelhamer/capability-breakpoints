#ifndef ENGINE_H
#define ENGINE_H

#include "datastructure.h"
#include "debugger.h"

#include <memory>
#include <string>

std::shared_ptr<Rule> generateRuleFromExpression(std::string ruleName, std::string ruleExpression);

Rule* attemptMatchFromNode(int tid, std::shared_ptr<DebuggerInterface> debugger, Nodes::Node* node);

Rule* attemptMatchFromApiNode(int tid, std::shared_ptr<DebuggerInterface> debugger,
                              Nodes::ApiCallNode* apiNode);

#endif // ENGINE_H