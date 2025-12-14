#include "pch.h"
#include "../Pythagorean/pyth.h"
#include "gtest/gtest.h"

TEST(CountATest, SimpleValues) {
    EXPECT_EQ(count_a(2, 1), 3);
    EXPECT_EQ(count_a(3, 2), 5);
    EXPECT_EQ(count_a(4, 1), 15);
}

TEST(CountBTest, SimpleValues) {
    EXPECT_EQ(count_b(2, 1), 4);
    EXPECT_EQ(count_b(3, 2), 12);
    EXPECT_EQ(count_b(4, 1), 8);
}

TEST(CountCTest, SimpleValues) {
    EXPECT_EQ(count_c(2, 1), 5);
    EXPECT_EQ(count_c(3, 2), 13);
    EXPECT_EQ(count_c(4, 1), 17);
}

TEST(PrimitiveTest, TruePairs) {
    EXPECT_TRUE(is_primitive(2, 1));
    EXPECT_TRUE(is_primitive(3, 2));
    EXPECT_TRUE(is_primitive(4, 1));
}

TEST(PrimitiveTest, FalsePairs) {
    EXPECT_FALSE(is_primitive(4, 2));
    EXPECT_FALSE(is_primitive(6, 3));
    EXPECT_FALSE(is_primitive(5, 1));
}

TEST(TripleTest, Pythagoras) {
    EXPECT_TRUE(is_primitive(4, 1));
    int64_t a = count_a(4, 1);
    int64_t b = count_b(4, 1);
    int64_t c = count_c(4, 1);
    EXPECT_EQ(a * a + b * b, c * c);
}

TEST(TripleTest, TripleCheck) {
    std::vector<std::vector<int64_t>> triples = generate_triples(15);
    std::cout << "ТРОЙКИ" << std::endl;
    for (size_t i = 0; i < triples.size(); ++i) {
        for (size_t j = 0; j < triples[i].size(); ++j) {
            std::cout << triples[i][j] << " ";
        }
        std::cout << "\n";
    }
    int found_triples = 0;
    for (int i = 0; i < triples.size(); ++i) {
        if (triples[i][0] == 3 && triples[i][1] == 4 && triples[i][2] == 5) {
            ++found_triples;
            break;
        }
    }
    for (int i = 0; i < triples.size(); ++i) {
        if (triples[i][0] == 5 && triples[i][1] == 12 && triples[i][2] == 13) {
            ++found_triples;
            break;
        }
    }
    for (int i = 0; i < triples.size(); ++i) {
        if (triples[i][0] == 6 && triples[i][1] == 8 && triples[i][2] == 10) {
            ++found_triples;
            break;
        }
    }
    for (int i = 0; i < triples.size(); ++i) {
        if (triples[i][0] == 9 && triples[i][1] == 12 && triples[i][2] == 15) {
            ++found_triples;
            break;
        }
    }
    EXPECT_EQ(found_triples, triples.size());
}

TEST(GenerateTriplesTest, MaxTooSmall) {
    EXPECT_EQ(generate_triples(4).size(), 0ll);
}

TEST(GenerateTriplesTest, MaxFive) {
    EXPECT_EQ(generate_triples(5).size(), 1ll);
}

TEST(GenerateTriplesTest, MaxTwenty) {
    EXPECT_EQ(generate_triples(20).size(), 6ll);
}

TEST(GenerateTriplesTest, MaxTenThousands) {
    EXPECT_EQ(generate_triples(10000).size(), 12471ll);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}