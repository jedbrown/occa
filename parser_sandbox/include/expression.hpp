/* The MIT License (MIT)
 *
 * Copyright (c) 2014-2018 David Medina and Tim Warburton
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 */
#ifndef OCCA_LANG_EXPRESSION_HEADER
#define OCCA_LANG_EXPRESSION_HEADER

#include <stack>
#include <vector>

#include "exprNode.hpp"

namespace occa {
  namespace lang {
    typedef std::stack<operatorToken*> operatorStack;

    //---[ Expression State ]-----------
    class expressionState {
    public:
      tokenVector &tokens;

      // Keep track of the prev/next tokens
      //   to break ++ and -- left/right
      //   unary ambiguity
      token_t *prevToken;
      token_t *nextToken;

      token_t *tokenBeforePair;
      exprNodeStack output;
      operatorStack operators;

      exprNodeStack usedOutput;

      bool hasError;

      expressionState(tokenVector &tokens_);
      ~expressionState();

      int outputCount();
      int operatorCount();

      exprNode& lastOutput();
      operatorToken& lastOperator();

      exprNode& popOutput();
      operatorToken& popOperator();
    };
    //==================================

    // Using Shunting-Yard algorithm
    exprNode* getExpression(tokenVector &tokens);

    void getInitialExpression(tokenVector &tokens,
                              expressionState &state);

    void pushOutputNode(token_t *token,
                        expressionState &state);

    void closePair(operatorToken &opToken,
                   expressionState &state);

    void extractArgs(exprNodeVector &args,
                     exprNode &node,
                     expressionState &state);

    void transformLastPair(operatorToken &opToken,
                           expressionState &state);

    void attachPair(operatorToken &opToken,
                    expressionState &state);

    bool operatorIsLeftUnary(operatorToken &opToken,
                             expressionState &state);

    void updateOperatorToken(operatorToken &opToken,
                             expressionState &state);

    void applyFasterOperators(operatorToken &opToken,
                              expressionState &state);

    void applyOperator(operatorToken &opToken,
                       expressionState &state);

    void applyLeftUnaryOperator(operatorToken &opToken,
                                const unaryOperator_t &op,
                                exprNode &value,
                                expressionState &state);
  }
}

#endif
