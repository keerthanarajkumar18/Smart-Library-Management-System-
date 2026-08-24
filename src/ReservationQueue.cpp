#include "ReservationQueue.h"
#include <stdexcept>

void ReservationQueue::addMember(const std::string& memberId)
{
    waitingMembers.push(memberId);
}

bool ReservationQueue::isEmpty() const
{
    return waitingMembers.empty();
}

const std::string& ReservationQueue::front() const
{
    if (isEmpty())
    {
        throw std::runtime_error("Reservation Queue is empty");
    }
    return waitingMembers.front();
}

void ReservationQueue::pop()
{
    if (isEmpty())
    {
        throw std::runtime_error("Queue is empty");
    }
    waitingMembers.pop();
}

std::size_t ReservationQueue::size() const
{
    return waitingMembers.size();
}