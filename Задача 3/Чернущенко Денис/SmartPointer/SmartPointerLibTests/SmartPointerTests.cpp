#include "gtest/gtest.h"
#include "../SmartPointerLib/SmartPointer.cpp"
#include <iostream>
#include <map>

#define DEBUG

static std::map<int, bool>CreatedObjectsMap;

struct TestClass
{
    int number = -1;

    explicit TestClass(int number) : number(number)
    {
        CreatedObjectsMap[number] = true;
#ifdef DEBUG
        printf("Created object(number %d)\n", number);
#endif
    }

    ~TestClass()
    {
        CreatedObjectsMap[number] = false;
#ifdef DEBUG
        printf("Deleted object(number %d)\n", number);
#endif
    }
};

void rewriteMap(int pairsCount)
{
    CreatedObjectsMap.clear();
    for (int number = 0; number < pairsCount; ++number)
        CreatedObjectsMap.insert( { number, true } );
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

        ASSERT_EQ(p1->number, 0);
    }
}

TEST(SmartPointer, DereferenceOperator)
{
    rewriteMap(1);
    {
        SmartPointer<TestClass> p1(new TestClass(0));

        ASSERT_EQ((*p1).number, 0);
    }
}

TEST(SmartPointer, Get)
{
    rewriteMap(1);
    {
        SmartPointer<TestClass> p1(new TestClass(0));

        ASSERT_EQ(p1.Get().number, 0);
    }
}

TEST(SmartPointer, Set)
{
    rewriteMap(1);
    {
        SmartPointer<TestClass> p1(new TestClass(0));
        SmartPointer<TestClass> p2(p1);

        p1.Set(new TestClass(999));

        ASSERT_EQ(p1->number, 999);
        ASSERT_EQ(p2->number, 0);
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

        ASSERT_THROW(p1->number, std::runtime_error);
        ASSERT_EQ(p2->number, 0);
    }
}
