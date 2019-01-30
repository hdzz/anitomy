/*
** Copyright (c) 2014-2019, Eren Okka
**
** This Source Code Form is subject to the terms of the Mozilla Public
** License, v. 2.0. If a copy of the MPL was not distributed with this
** file, You can obtain one at https://mozilla.org/MPL/2.0/.
*/

#pragma once

#include <vector>

#include <anitomy/string.hpp>

namespace anitomy {

enum class TokenType {
  Unknown,
  Bracket,
  Delimiter,
  Identifier,
  Invalid,
};

enum TokenFlag {
  kFlagNone,
  // Categories
  kFlagBracket     = 1 << 0,  kFlagNotBracket    = 1 << 1,
  kFlagDelimiter   = 1 << 2,  kFlagNotDelimiter  = 1 << 3,
  kFlagIdentifier  = 1 << 4,  kFlagNotIdentifier = 1 << 5,
  kFlagUnknown     = 1 << 6,  kFlagNotUnknown    = 1 << 7,
  kFlagValid       = 1 << 8,  kFlagNotValid      = 1 << 9,
  // Enclosed
  kFlagEnclosed    = 1 << 10, kFlagNotEnclosed   = 1 << 11,
  // Masks
  kFlagMaskCategories = kFlagBracket | kFlagNotBracket |
                        kFlagDelimiter | kFlagNotDelimiter |
                        kFlagIdentifier | kFlagNotIdentifier |
                        kFlagUnknown | kFlagNotUnknown |
                        kFlagValid | kFlagNotValid,
  kFlagMaskEnclosed = kFlagEnclosed | kFlagNotEnclosed,
};

struct Token {
  Token(TokenType type, string_view_t value, bool enclosed)
      : type{type}, value{string_t{value}}, enclosed{enclosed} {}

  bool operator==(const Token& token) const;

  TokenType type = TokenType::Unknown;
  string_t value;
  bool enclosed = false;
};

using Tokens = std::vector<Token>;
using token_iterator_t = Tokens::iterator;
using token_reverse_iterator_t = Tokens::reverse_iterator;

token_iterator_t FindToken(token_iterator_t first, token_iterator_t last, unsigned int flags);
token_reverse_iterator_t FindToken(token_reverse_iterator_t first, token_reverse_iterator_t last, unsigned int flags);
token_iterator_t FindPreviousToken(Tokens& tokens, token_iterator_t first, unsigned int flags);
token_iterator_t FindNextToken(Tokens& tokens, token_iterator_t first, unsigned int flags);

}  // namespace anitomy
