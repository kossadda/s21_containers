/**
 * @file queue_test.cc
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief Unit tests for the queue class
 * @version 1.0
 * @date 2024-06-14
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <list>
#include <queue>

#include "../../s21_containers.h"
#include "../main_test.h"

template <typename T>
static bool compare_queues(std::queue<T, std::list<int>> &std_queue,
                           s21::queue<T, s21::list<int>> &s21_queue) {
  if (std_queue.size() != s21_queue.size()) {
    return false;
  }

  while (!std_queue.empty() && !s21_queue.empty()) {
    if (std_queue.front() != s21_queue.front()) {
      return false;
    }

    std_queue.pop();
    s21_queue.pop();
  }

  return true;
}

template <typename T>
static bool compare_queues(std::queue<T> &std_queue, s21::queue<T> &s21_queue) {
  if (std_queue.size() != s21_queue.size()) {
    return false;
  }

  while (!std_queue.empty() && !s21_queue.empty()) {
    if (s21_queue.front() != std_queue.front()) {
      return false;
    }

    std_queue.pop();
    s21_queue.pop();
  }

  return true;
}

TEST(QueueTest, DefaultConstructor) {
  s21::queue<int> l;
  EXPECT_TRUE(l.empty());
}

TEST(QueueTest, CopyConstructorContainer1) {
  s21::list<int> s21_l{1, 2, 3};
  std::list<int> std_l{1, 2, 3};

  s21::queue<int, s21::list<int>> s21_queue(s21_l);
  std::queue<int, std::list<int>> std_queue(std_l);

  EXPECT_EQ(s21_queue.size(), std_queue.size());

  EXPECT_TRUE(compare_queues(std_queue, s21_queue));
}

TEST(QueueTest, CopyConstructorContainer2) {
  s21::list<int> s21_l{3, 4, 1, 2, 9};
  std::list<int> std_l{3, 4, 1, 2, 9};

  s21::queue<int, s21::list<int>> s21_queue(s21_l);
  std::queue<int, std::list<int>> std_queue(std_l);

  EXPECT_EQ(s21_queue.size(), std_queue.size());

  EXPECT_TRUE(compare_queues(std_queue, s21_queue));
}

TEST(QueueTest, CopyConstructorContainerFail) {
  s21::list<int> s21_l{3, 4, 1, 2, 9};
  std::list<int> std_l{3, 4, 1, 2, 9, 2, 1};

  s21::queue<int, s21::list<int>> s21_queue(s21_l);
  std::queue<int, std::list<int>> std_queue(std_l);

  EXPECT_FALSE(compare_queues(std_queue, s21_queue));
}

TEST(QueueTest, MoveConstructorContainer1) {
  s21::list<int> s21_l{1, 2, 3};
  std::list<int> std_l{1, 2, 3};

  s21::queue<int, s21::list<int>> s21_queue(std::move(s21_l));
  std::queue<int, std::list<int>> std_queue(std::move(std_l));
  EXPECT_EQ(s21_queue.size(), std_queue.size());

  EXPECT_TRUE(s21_l.empty());
  EXPECT_TRUE(std_l.empty());
  EXPECT_TRUE(compare_queues(std_queue, s21_queue));
}

TEST(QueueTest, MoveConstructorContainer2) {
  s21::list<int> s21_l{3, 4, 1, 2, 9};
  std::list<int> std_l{3, 4, 1, 2, 9};

  s21::queue<int, s21::list<int>> s21_queue(std::move(s21_l));
  std::queue<int, std::list<int>> std_queue(std::move(std_l));
  EXPECT_EQ(s21_queue.size(), std_queue.size());

  EXPECT_TRUE(s21_l.empty());
  EXPECT_TRUE(std_l.empty());
  EXPECT_TRUE(compare_queues(std_queue, s21_queue));
}

TEST(QueueTest, CopyConstructor1) {
  s21::queue<int> s21_original;
  std::queue<int> std_original;

  s21_original.push(1);
  s21_original.push(2);
  s21_original.push(3);

  std_original.push(1);
  std_original.push(2);
  std_original.push(3);

  s21::queue<int> s21_copy(s21_original);
  std::queue<int> std_copy(std_original);

  EXPECT_EQ(s21_original.size(), std_original.size());
  EXPECT_EQ(std_copy.size(), s21_copy.size());

  EXPECT_TRUE(compare_queues(std_copy, s21_copy));
}

TEST(QueueTest, CopyConstructorFail) {
  s21::queue<int> s21_original;
  std::queue<int> std_original;

  s21_original.push(1);
  s21_original.push(2);
  s21_original.push(3);
  s21_original.push(6);

  std_original.push(1);
  std_original.push(2);
  std_original.push(3);

  s21::queue<int> s21_copy(s21_original);
  std::queue<int> std_copy(std_original);

  EXPECT_NE(s21_original.size(), std_original.size());
  EXPECT_NE(std_copy.size(), s21_copy.size());

  EXPECT_FALSE(compare_queues(std_copy, s21_copy));
}

TEST(QueueTest, MoveConstructor1) {
  s21::queue<int> s21_original;
  std::queue<int> std_original;

  s21_original.push(1);
  s21_original.push(2);
  s21_original.push(3);

  std_original.push(1);
  std_original.push(2);
  std_original.push(3);

  s21::queue<int> s21_copy(std::move(s21_original));
  std::queue<int> std_copy(std::move(std_original));

  EXPECT_EQ(s21_original.size(), std_original.size());
  EXPECT_EQ(std_copy.size(), s21_copy.size());

  EXPECT_TRUE(compare_queues(std_copy, s21_copy));
}

TEST(QueueTest, PushLvalue) {
  s21::queue<int> s21_original;
  std::queue<int> std_original;

  int num = 1;
  s21_original.push(num);
  s21_original.push(num);
  s21_original.push(num);

  std_original.push(num);
  std_original.push(num);
  std_original.push(num);

  s21::queue<int> s21_copy(std::move(s21_original));
  std::queue<int> std_copy(std::move(std_original));

  EXPECT_EQ(s21_original.size(), std_original.size());
  EXPECT_EQ(std_copy.size(), s21_copy.size());

  EXPECT_TRUE(compare_queues(std_copy, s21_copy));
}

TEST(QueueTest, EmplaceEmpty) {
  std::queue<int> std_q;
  s21::queue<int> s21_q;

  std_q.emplace(10);
  s21_q.emplace(10);

  EXPECT_TRUE(compare_queues(std_q, s21_q));
}

TEST(QueueTest, Emplace) {
  std::list<int> std_l{3, 4, 1, 2, 9};
  s21::list<int> s21_l{3, 4, 1, 2, 9};

  std::queue<int, std::list<int>> std_q(std::move(std_l));
  s21::queue<int, s21::list<int>> s21_q(std::move(s21_l));

  std_q.emplace(123);
  s21_q.emplace(123);

  EXPECT_TRUE(compare_queues(std_q, s21_q));
}
