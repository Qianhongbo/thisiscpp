#include "gtest/gtest.h"
#include "thisiscpp/singleton_pattern/eager_singleton.h"
#include "thisiscpp/singleton_pattern/lazy_singleton.h"

TEST(SingletonPatternTest, EagerSingleton) {
  EagerSingleton* instance1 = EagerSingleton::getInstance();
  EagerSingleton* instance2 = EagerSingleton::getInstance();
  EXPECT_EQ(instance1, instance2);
  instance1->printMessage();
  instance2->printMessage();
}

TEST(SingletonPatternTest, LazySingleton) {
  LazySingleton* instance1 = LazySingleton::getInstance();
  LazySingleton* instance2 = LazySingleton::getInstance();
  EXPECT_EQ(instance1, instance2);
  instance1->printMessage();
  instance2->printMessage();
}