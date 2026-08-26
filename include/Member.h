#ifndef MEMBER_H
#define MEMBER_H

#include <string>
#include <vector>

enum class MemberRole
{
    Student, 
    Faculty,
    Librarian
};

class Member
{
    private:
    
        std::string memberId;
        std::string name;
        MemberRole role;

        std::vector<std::string> borrowingHistory; // Store ISBNs of borrowed books

    public:
     
        Member(const std::string &memberId, const std::string &name, MemberRole role);
        const std::string &getMemberId() const;
        const std::string &getName() const;
        MemberRole getRole() const;

        void addBorrowRecord(const std::string& recordId);

        const std::vector<std::string>& getBorrowingHistory() const;
};

#endif // MEMBER_H