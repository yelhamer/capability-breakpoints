grammar CapabilityDSL;

// --- Parser Rules ---

// Precedence (highest to lowest): parens/calls > AND > OR > THEN
ruleExpr
    : '(' ruleExpr ')'                         # ParentNode
    | apiCall                                  # CallNode
    | ruleExpr AND ruleExpr                    # AndNode
    | ruleExpr OR ruleExpr                     # OrNode
    | ruleExpr THEN ruleExpr                   # ThenNode
    ;

apiCall
    : apiName '(' apiArgs ')'                  # ApiWithArgs
    ;

apiName
    : IDENTIFIER                               # IdentifierName
    ;

apiArgs
    : apiArg (',' apiArg)*                      # ArgListContainer
    ;

apiArg
    : argExpr?
    ;

// AND is deliberately NOT available here: a single argument can't equal
// two different literal values at once ("1 and 2" is meaningless), so
// only OR/NOT/parens combine plain values. AND only exists inside
// memExpr, where it means "buffer matches pattern A AND pattern B" -
// which IS meaningful, since one buffer can satisfy multiple substring
// conditions at once.
argExpr
    : '(' argExpr ')'                          # ArgParen
    | NOT argExpr                              # ArgNot
    | argExpr OR argExpr                       # ArgOr
    | memExpr                                  # MemMatch
    | primaryVal                               # PrimaryValue
    ;

memExpr
    : '(' memExpr ')'                          # MemParen
    | NOT memExpr                              # MemNot
    | memExpr AND memExpr                      # MemAnd
    | memExpr OR memExpr                       # MemOr
    | memDereference                           # MemLeaf
    ;

memDereference
    : '[' patternExpr ']'                      # MemDeref
    ;

patternExpr
    : patternElems  '@' primary                                # OffsetPattern
    | patternElems ':'                                         # PrefixPattern
    | ':' patternElems                                         # SuffixPattern
    | ':' patternElems ':'                                     # ContainsPattern
    ;


// Prefix/suffix/contains never take an offset, so there's no scoping
// ambiguity left to guard against - just a plain list, no parens needed.
patternElems
    : patternElem                                   # SingleElem
    | '(' patternElems (',' patternElems)* ')'      # MultiElems
    ;

patternElem
    : STRING '*' INT                           # ElemStringRepeat
    | STRING                                   # ElemString
    | hexList '*' INT                          # ElemHexRepeat
    | HEX_INT                                  # ElemHex
    | intList '*' INT                          # ElemIntRepeat
    | INT                                      # ElemInt
    | WILDCARD+ '*' INT                        # ElemWildcardRepeat
    | WILDCARD+                                # ElemWildcard
    ;

hexList                                        
    : HEX_INT                                  # SingleHex
    | '(' hexList (',' hexList)* ')'           # MultiHex
    ;

intList
    : INT                                      # SingleInt
    | '(' intList (',' intList)* ')'           # MultiInt
    ;

primary
    : HEX_INT                                  # PrimaryHex
    | INT                                      # PrimaryInt
    ;

primaryVal
    : HEX_INT                                  # PrimaryValHex
    | INT                                      # PrimaryValInt
    | STRING                                   # PrimaryValStr
    ;

// --- Lexer Rules ---
AND        : [aA][nN][dD] ;
OR         : [oO][rR] ;
THEN       : [tT][hH][eE][nN] ;
NOT        : [nN][oO][tT] ;
WILDCARD   : '?' ;
HEX_INT    : '0' [xX] [0-9a-fA-F]+ ;
INT        : [0-9]+ ;
IDENTIFIER : [a-zA-Z_] [a-zA-Z0-9_]* ;
STRING     : '"' (~["\r\n\\] | '\\' .)* '"' ;
COMMENT    : '#' ~[\r\n]* -> skip ;
WS         : [ \t\r\n]+ -> skip ;
