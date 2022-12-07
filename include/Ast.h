//
// Created by nik on 12/6/22.
//

#ifndef LANG2_AST_H
#define LANG2_AST_H

#include "Token.h"

namespace Lang::Ast {

class Node {
public:

protected:
	explicit Node(const Token& token) : token(token) {}

	Token token;

};

class BinaryNode {

};

}

#endif //LANG2_AST_H
