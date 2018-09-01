#include <klv/sformat.hpp>
#include <gtest/gtest.h>

TEST(SFormat, SStr) {
    using klv::sstr;

    ASSERT_EQ("", sstr());
    ASSERT_EQ("123", sstr(123));
    ASSERT_EQ("1 + 2 = 3", sstr(1, " + ", 2, " = ", 3));
}

TEST(SFormat, Delims) {
    using klv::delimits;

    std::vector<int> xs0;
    ASSERT_EQ("", sstr(delimits(xs0, ", ")));

    std::vector<int> xs1{1, 2, 3};
    ASSERT_EQ("1, 2, 3", sstr(delimits(xs1, ", ")));
}


TEST(SFormat, CFmt) {
    using klv::cfmt;

    std::stringstream ss1;
    ss1 << cfmt("%04d", 25);
    ASSERT_EQ("0025", ss1.str());

    std::stringstream ss2;
    ss2 << cfmt("%.4f", 12.0);
    ASSERT_EQ("12.0000", ss2.str());
}


TEST(SFormat, CFmt_s) {
    using klv::cfmt_s;

    ASSERT_EQ("0025", cfmt_s("%04d", 25));
    ASSERT_EQ("12.0000", cfmt_s("%.4f", 12.0));
    ASSERT_EQ("1 + 2 = 3", cfmt_s("%d + %d = %d", 1, 2, 3));
}
