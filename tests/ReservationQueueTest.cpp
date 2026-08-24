#include <gtest/gtest.h>
#include "ReservationQueue.h"

// Test case to verify that the ReservationQueue is initially empty
TEST(ReservationQueueTest, InitiallyEmpty)
{
    ReservationQueue queue;
    EXPECT_TRUE(queue.isEmpty());
    EXPECT_EQ(queue.size(), 0);
}

// Test case to verify that adding a member to the ReservationQueue works correctly
TEST(ReservationQueueTest, AddMember)
{
    ReservationQueue queue;
    queue.addMember("M001");
    EXPECT_FALSE(queue.isEmpty());
    EXPECT_EQ(queue.size(), 1);
    EXPECT_EQ(queue.front(), "M001");
}

// Test case to verify that popping a member from the ReservationQueue works correctly
TEST(ReservationQueueTest, MaintainsFIFOOrder)
{
    ReservationQueue queue;
    queue.addMember("M001");
    queue.addMember("M002");
    queue.addMember("M003");

    EXPECT_EQ(queue.front(), "M001");
    queue.pop();
    EXPECT_EQ(queue.front(), "M002");
    queue.pop();
    EXPECT_EQ(queue.front(), "M003");
    queue.pop();
    EXPECT_TRUE(queue.isEmpty());
}

// Test case to pop a member from the ReservationQueue and check if the size decreases
TEST(ReservationQueueTest, PopRemovesMember)
{
    ReservationQueue queue;
    queue.addMember("M001");
    queue.addMember("M002");

    queue.pop();
    EXPECT_EQ(queue.front(), "M002");
    EXPECT_EQ(queue.size(), 1);
}

// Test case to verify that popping from an empty ReservationQueue throws an exception
TEST(ReservationQueueTest, FrontOnEmptyQueueThrows)
{
    ReservationQueue queue;
    EXPECT_THROW(queue.front(), std::runtime_error);
}