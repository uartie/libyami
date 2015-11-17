#include <gtest/gtest.h>
#include "factory.h"

#define FACTORY_TEST(name) \
    TEST(FactoryTest, name)

class Base {
public:
    virtual ~Base() {}
    virtual int value() const = 0;
};

class A : public Base {
public:
    int value() const { return 1; }
};

class B : public Base {
public:
    int value() const { return 2; }
};

class C : public Base {
public:
    int value() const { return 3; }
};

// Attempt to expose what is commonly referred to as the
// "static initialization order fiasco".
// If the unittest program segfaults during pre-main static
// initialization, then we've likely introduced an initialization
// order bug.
const bool rA = Factory<Base>::register_<A>("A");

FACTORY_TEST(Register) {
    EXPECT_TRUE(rA);
    EXPECT_TRUE(Factory<Base>::register_<B>("B"));
    EXPECT_TRUE(Factory<Base>::register_<B>("B2"));
    EXPECT_TRUE(Factory<Base>::register_<C>("C"));
    EXPECT_FALSE(Factory<Base>::register_<A>("A"));
    EXPECT_FALSE(Factory<Base>::register_<B>("B"));
    EXPECT_FALSE(Factory<Base>::register_<C>("C"));
}

FACTORY_TEST(Create) {
    Base* a = Factory<Base>::create("A");
    Base* z = Factory<Base>::create("Z");
    EXPECT_TRUE(a != NULL);
    EXPECT_TRUE(z == NULL);

    ASSERT_EQ(a->value(), 1);

    delete a;
}
