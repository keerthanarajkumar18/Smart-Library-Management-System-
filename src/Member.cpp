#include "Member.h"

Member::Member(const std::string &memberId,
               const std::string &name,
               MemberRole role)
    : memberId(memberId),
      name(name), 
      role(role) {}

const std::string &Member::getMemberId() const {
    return memberId;
}

const std::string &Member::getName() const {
    return name;
}

MemberRole Member::getRole() const {
    return role;
}

void Member::addBorrowRecord(const std::string& recordId) {
    borrowingHistory.push_back(recordId);
}

const std::vector<std::string>& Member::getBorrowingHistory() const {
    return borrowingHistory;
}