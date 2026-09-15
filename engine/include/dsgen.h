#ifndef DSGEN_H
#define DSGEN_H

#include "../language/generated/CapabilityDSLParser.h"
#include "datastructure.h"
#include <antlr4-runtime.h>

using namespace antlr4;


std::shared_ptr<Nodes::Node> walk(
    tree::ParseTree*,
    Nodes::Node*,
    std::unordered_map<std::string,
    std::vector<std::shared_ptr<Nodes::ApiCallNode>>>,
    std::shared_ptr<Nodes::ThenNode>
);

std::shared_ptr<Nodes::Node> walkArgExpr(
    CapabilityDSLParser::ArgExprContext*,
    Nodes::Node*, int
);

#endif // DSGEN_H