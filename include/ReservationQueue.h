#ifndef RESERVATION_QUEUE_H
#define RESERVATION_QUEUE_H

#include <queue>
#include <string>

class ReservationQueue
{
    private:
        std::queue<std::string> waitingMembers; // Queue of member IDs

    public:
        //Add a member to the end of the queue 
        void addMember(const std::string& memberId);

        //check whether the queue is empty
        bool isEmpty() const;

        //Get the member ID at the front of the queue without removing it. If the queue is empty, throw an exception.
        const std::string& front() const;

        //Remove the member ID at the front of the queue. If the queue is empty, throw an exception.
        void pop();

        //Number of members waiting in the queue 
        std::size_t size() const;
};

#endif // RESERVATION_QUEUE_H