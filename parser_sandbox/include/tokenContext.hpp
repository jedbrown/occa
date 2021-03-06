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
#ifndef OCCA_LANG_TOKENCONTEXT_HEADER
#define OCCA_LANG_TOKENCONTEXT_HEADER

#include <list>
#include <map>
#include <vector>

namespace occa {
  namespace lang {
    class tokenRange;
    class token_t;
    class exprNode;

    typedef std::vector<token_t*>   tokenVector;
    typedef std::list<tokenRange>   tokenRangeList;
    typedef std::vector<tokenRange> tokenRangeVector;
    typedef std::map<int, int>      intIntMap;

    class tokenRange {
    public:
      int start, end;

      tokenRange();

      tokenRange(const int start_,
                 const int end_);
    };

    class tokenContext {
    public:
      tokenVector tokens;
      intIntMap pairs;
      intVector semicolons;
      bool hasError;

      tokenRangeList stack;
      tokenRange tp;

      tokenContext();
      ~tokenContext();

      void clear();
      void setup();

      void findPairs();
      void findSemicolons();

      bool indexInRange(const int index) const;

      void set(const int start);
      void set(const int start,
               const int end);

      void push();
      void push(const int start);
      void push(const int start,
                const int end);

      void pushPairRange(const int pairStart);

      tokenRange pop();
      void popAndSkipPair();

      int size() const;
      token_t* operator [] (const int index);

      token_t* end();

      void getTokens(tokenVector &tokens_);
      void getAndCloneTokens(tokenVector &tokens_);

      int getClosingPair(const int index);
      token_t* getClosingPairToken(const int index);

      int getNextOperator(const opType_t &opType);

      exprNode* getExpression();
      exprNode* getExpression(const int start,
                              const int end);
    };
  }
}
#endif
