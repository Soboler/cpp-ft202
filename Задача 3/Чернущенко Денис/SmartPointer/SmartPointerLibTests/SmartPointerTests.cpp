#include "gtest/gtest.h"
#include "../SmartPointerLib/SmartPointer.cpp"
#include <iostream>
#include <map>

#define DEBUG

static std::map<int, bool>CreatedObjectsMap;

struct TestClass
{
    int x = -1;

    explicit TestClass(int x) : x(x)
    {
        CreatedObjectsMap[x] = true;
#ifdef DEBUG
        printf("Created object(x = %d)\n", x);
#endif
    }

    ~TestClass()
    {
        CreatedObjectsMap[x] = false;
#ifdef DEBUG
        printf("Deleted object(x = %d)\n", x);
#endif
    }
};

void rewriteMap(int pairsCount)
{
    CreatedObjectsMap.clear();
    for (int i = 0; i < pairsCount; ++i)
        CreatedObjectsMap.insert( { i, true } );
}

TEST(SmartPointer, Constructor)
{
    rewriteMap(1);
    {
        SmartPointer<TestClass> p1(new TestClass(0));
    }

    for (auto pair : CreatedObjectsMap)
        ASSERT_FALSE(pair.second);
}

TEST(SmartPointer, AssignmentOperator)
{
    rewriteMap(2);
    {
        SmartPointer<TestClass> p1(new TestClass(0));
        SmartPointer<TestClass> p2(new TestClass(1));

        p1 = p2;
    }

    for (auto pair : CreatedObjectsMap)
        ASSERT_FALSE(pair.second);
}

TEST(SmartPointer, CopyConstructor)
{
    rewriteMap(1);
    {
        SmartPointer<TestClass> p1(new TestClass(0));

        SmartPointer<TestClass> p2(p1);
    }

    for (auto pair : CreatedObjectsMap)
        ASSERT_FALSE(pair.second);
}

TEST(SmartPointer, ArrowOperator)
{
    rewriteMap(1);
    {
        SmartPointer<TestClass> p1(new TestClass(0));

        ASSERT_EQ(p1->x, 0);
    }
}

TEST(SmartPointer, DereferenceOperator)
{
    rewriteMap(1);
    {
        SmartPointer<TestClass> p1(new TestClass(0));

        ASSERT_EQ((*p1).x, 0);
    }
}

TEST(SmartPointer, Get)
{
    rewriteMap(1);
    {
        SmartPointer<TestClass> p1(new TestClass(0));

        ASSERT_EQ(p1.Get().x, 0);
    }
}

TEST(SmartPointer, Set)
{
    rewriteMap(1);
    {
        SmartPointer<TestClass> p1(new TestClass(0));
        SmartPointer<TestClass> p2(p1);

        p1.Set(new TestClass(999));

        ASSERT_EQ(p1->x, 999);
        ASSERT_EQ(p2->x, 0);
    }

    for (auto pair : CreatedObjectsMap)
        ASSERT_FALSE(pair.second);
}

TEST(SmartPointer, Release)
{
    rewriteMap(1);
    {
        SmartPointer<TestClass> p1(new TestClass(0));
        SmartPointer<TestClass> p2(p1);

        p1.Release();

        ASSERT_THROW(p1->x, std::runtime_error);
        ASSERT_EQ(p2->x, 0);
    }
}
