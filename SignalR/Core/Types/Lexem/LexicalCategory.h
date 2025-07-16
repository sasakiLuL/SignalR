#pragma once

namespace Core::Types
{
    enum class LexicalCategory
    {
        Whitespace = 0,
        Number = 1,
        Identifier = 2,
        Delimiter = 3,
        CommentsOpener = 41,
        CommentsCloser = 42,
        Illegal = 5,
    };
}