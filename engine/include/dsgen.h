#ifndef DSGEN_H
#define DSGEN_H

#include "../language/generated/CapabilityDSLParser.h"
#include "datastructure.h"

#include <antlr4-runtime.h>

using namespace antlr4;

std::shared_ptr<Nodes::Node> walk(tree::ParseTree*, Nodes::Node*,
                                  std::shared_ptr<Nodes::ApiNodeMap>,
                                  std::shared_ptr<Nodes::ThenNode>);

std::shared_ptr<Nodes::Node> walkArgExpr(CapabilityDSLParser::ArgExprContext*, Nodes::Node*, int);

#endif // DSGEN_H