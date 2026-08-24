#pragma once

#include "Member.h"

enum class Operation
{
    AddBook,
    RemoveBook,
    UpdateBook,
    SearchBook
};

class AccessControl
{
public:
    bool isAuthorized(
        const Member& member,
        Operation operation
    ) const;
};