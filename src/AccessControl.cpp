#include "AccessControl.h"

bool AccessControl::isAuthorized(
    const Member& member,
    Operation operation
) const
{
    switch (operation)
    {
        case Operation::AddBook:
        case Operation::RemoveBook:
        case Operation::UpdateBook:

            return member.getRole() == MemberRole::Librarian;

        case Operation::SearchBook:

            return true;
    }

    return false;
}