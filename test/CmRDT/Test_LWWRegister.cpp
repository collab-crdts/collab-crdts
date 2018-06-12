#include "collabdata/CmRDT/LWWRegister.h"

#include <gtest/gtest.h>
#include <string>

namespace collab {
namespace CmRDT {


// -----------------------------------------------------------------------------
// Class method tests
// -----------------------------------------------------------------------------

TEST(LWWRegister, queryTest) {
    LWWRegister<int, int> data0;

    data0.update(42, 1);
    ASSERT_EQ(data0.query(), 42);
    ASSERT_EQ(data0.timestamp(), 1);

    data0.update(100, 2);
    ASSERT_EQ(data0.query(), 100);
    ASSERT_EQ(data0.timestamp(), 2);

    data0.update(300, 3);
    ASSERT_EQ(data0.query(), 300);
    ASSERT_EQ(data0.timestamp(), 3);
}

TEST(LWWRegister, updateTest) {
    LWWRegister<int, int> data0;

    // Simulate different add at timestamps
    data0.update(666, 6);
    ASSERT_EQ(data0.query(), 666);
    ASSERT_EQ(data0.timestamp(), 6);

    data0.update(555, 5);
    ASSERT_EQ(data0.query(), 666);
    ASSERT_EQ(data0.timestamp(), 6);

    data0.update(888, 8);
    ASSERT_EQ(data0.query(), 888);
    ASSERT_EQ(data0.timestamp(), 8);

    data0.update(777, 7);
    ASSERT_EQ(data0.query(), 888);
    ASSERT_EQ(data0.timestamp(), 8);

    data0.update(999, 9);
    ASSERT_EQ(data0.query(), 999);
    ASSERT_EQ(data0.timestamp(), 9);

    data0.update(444, 4);
    ASSERT_EQ(data0.query(), 999);
    ASSERT_EQ(data0.timestamp(), 9);

    data0.update(222, 2);
    ASSERT_EQ(data0.query(), 999);
    ASSERT_EQ(data0.timestamp(), 9);

    data0.update(111, 1);
    ASSERT_EQ(data0.query(), 999);
    ASSERT_EQ(data0.timestamp(), 9);

    data0.update(333, 3);
    ASSERT_EQ(data0.query(), 999);
    ASSERT_EQ(data0.timestamp(), 9);
}

TEST(LWWRegister, updateReturnTypeTest) {
    LWWRegister<std::string, int> data0;

    bool applied = data0.update("LittleRabbit", 10);
    ASSERT_TRUE(applied);

    applied = data0.update("SuperCarrot", 42);
    ASSERT_TRUE(applied);

    applied = data0.update("Toto", 20);
    ASSERT_FALSE(applied);

    applied = data0.update("Banana", 30);
    ASSERT_FALSE(applied);

    applied = data0.update("MagicCarrot", 64);
    ASSERT_TRUE(applied);
}


// -----------------------------------------------------------------------------
// Operator Tests
// -----------------------------------------------------------------------------

TEST(LWWRegister, operatorEQTest) {
    LWWRegister<int, int> data0;
    LWWRegister<int, int> data1;

    // Exact EQ
    data0.update(42, 1);
    data1.update(42, 1);
    ASSERT_TRUE(data0 == data1);
    ASSERT_FALSE(data0 != data1);

    // Register with different timestamp are equal anyway
    data0.update(77, 7);
    data1.update(77, 9);
    ASSERT_TRUE(data0 == data1);
    ASSERT_FALSE(data0 != data1);
}


// -----------------------------------------------------------------------------
// Use case Tests
// -----------------------------------------------------------------------------

TEST(LWWRegister, usecaseNormalTest) {
    LWWRegister<int, int> data0;
    LWWRegister<int, int> data1;


    // At replicate 0
    data0.update(300, 3);
    ASSERT_EQ(data0.query(), 300);
    ASSERT_EQ(data0.timestamp(), 3);

    data0.update(100, 1);
    ASSERT_EQ(data0.query(), 300);
    ASSERT_EQ(data0.timestamp(), 3);

    data0.update(500, 5);
    ASSERT_EQ(data0.query(), 500);
    ASSERT_EQ(data0.timestamp(), 5);

    data0.update(700, 7);
    ASSERT_EQ(data0.query(), 700);
    ASSERT_EQ(data0.timestamp(), 7);

    data0.update(200, 2);
    ASSERT_EQ(data0.query(), 700);
    ASSERT_EQ(data0.timestamp(), 7);


    // At replicate 1
    data1.update(320, 3);
    ASSERT_EQ(data1.query(), 320);
    ASSERT_EQ(data1.timestamp(), 3);

    data1.update(100, 1);
    ASSERT_EQ(data1.query(), 320);
    ASSERT_EQ(data1.timestamp(), 3);

    data1.update(500, 5);
    ASSERT_EQ(data1.query(), 500);
    ASSERT_EQ(data1.timestamp(), 5);

    data1.update(700, 7);
    ASSERT_EQ(data1.query(), 700);
    ASSERT_EQ(data1.timestamp(), 7);

    ASSERT_EQ(data0.query(), data1.query());
    ASSERT_EQ(data0.timestamp(), data1.timestamp());
}


}} // End namespaces


