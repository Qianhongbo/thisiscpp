#include "thisiscpp/class_demo/class_demo.h"
#include "gtest/gtest.h"

TEST(ClassTest, MyClass) {
  MyClass my_class(5);
  for (int i = 0; i < my_class.size(); ++i) {
    my_class[i] = i;
  }
  EXPECT_EQ(my_class.size(), 5);
  EXPECT_EQ(my_class[0], 0);
  EXPECT_EQ(my_class[1], 1);
  EXPECT_EQ(my_class[2], 2);
}

TEST(ClassTest, MyClassCopyConstructor) {
  MyClass my_class(5);
  for (int i = 0; i < my_class.size(); ++i) {
    my_class[i] = i;
  }
  MyClass my_class_copy(my_class);
  EXPECT_EQ(my_class_copy.size(), 5);
  EXPECT_EQ(my_class_copy[0], 0);
  EXPECT_EQ(my_class_copy[1], 1);
  EXPECT_EQ(my_class_copy[2], 2);
}

TEST(ClassTest, MyClassCopyAssignment) {
  MyClass my_class(5);
  for (int i = 0; i < my_class.size(); ++i) {
    my_class[i] = i;
  }
  MyClass my_class_copy;
  my_class_copy = my_class;
  EXPECT_EQ(my_class_copy.size(), 5);
  for (int i = 0; i < my_class_copy.size(); ++i) {
    EXPECT_EQ(my_class_copy[i], i);
  }
  for (int i = 0; i < my_class.size(); ++i) {
    EXPECT_EQ(my_class[i], i);
  }
}

TEST(ClassTest, MyClassMoveConstructor) {
  MyClass my_class(5);
  for (int i = 0; i < my_class.size(); ++i) {
    my_class[i] = i;
  }
  MyClass my_class_move(std::move(my_class));
  EXPECT_EQ(my_class.size(), 0);
  EXPECT_EQ(my_class_move.size(), 5);
  for (int i = 0; i < my_class_move.size(); ++i) {
    EXPECT_EQ(my_class_move[i], i);
  }
}

TEST(ClassTest, MyClassMoveAssignment) {
  MyClass my_class(5);
  for (int i = 0; i < my_class.size(); ++i) {
    my_class[i] = i;
  }
  MyClass my_class_move;
  my_class_move = std::move(my_class);
  EXPECT_EQ(my_class.size(), 0);
  EXPECT_EQ(my_class_move.size(), 5);
  for (int i = 0; i < my_class_move.size(); ++i) {
    EXPECT_EQ(my_class_move[i], i);
  }
}