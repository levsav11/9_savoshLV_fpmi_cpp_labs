#define BOOST_TEST_MODULE TriplesTest
#include <boost/test/included/unit_test.hpp>
#include "../Boost_code/Pyth.cpp"
bool contains_triple(const std::vector<std::vector<int64_t>> &triples, int64_t a, int64_t b, int64_t c) {
    for (const std::vector<int64_t>& triple : triples) {
        if ((triple[0] == a) && (triple[1] == b) && (triple[2] == c))
            return true;
    }
    return false;
}

BOOST_AUTO_TEST_SUITE(CountTests)
BOOST_AUTO_TEST_CASE(CountATest){
    BOOST_TEST_MESSAGE("Тестирование расчёта стороны a...");
    BOOST_CHECK_MESSAGE(count_a(2, 1) == 3, "count_a(2, 1) = " << count_a(2, 1) << ", ожидалось 3");
    BOOST_CHECK_MESSAGE(count_a(3, 2) == 5,"count_a(3, 2) = " << count_a(3, 2) << ", ожидалось 5");
    BOOST_CHECK_MESSAGE(count_a(4, 1) == 15, "count_a(4, 1) = " << count_a(4, 1) << ", ожидалось 15");
}
BOOST_AUTO_TEST_CASE(CountBTest){
    BOOST_TEST_MESSAGE("Тестирование расчёта стороны b...");
    BOOST_CHECK_MESSAGE(count_b(2, 1) == 4, "count_b(2, 1) = " << count_b(2, 1) << ", ожидалось 4");
    BOOST_CHECK_MESSAGE(count_b(3, 2) == 12, "count_b(3, 2) = " << count_b(3, 2) << ", ожидалось 12");
    BOOST_CHECK_MESSAGE(count_b(4, 1) == 8, "count_b(4, 1) = " << count_b(4, 1) << ", ожидалось 8");
}
BOOST_AUTO_TEST_CASE(CountCTest){
    BOOST_TEST_MESSAGE("Тестирование расчёта стороны c...");
    BOOST_CHECK_MESSAGE(count_c(2, 1) == 5, "count_c(2, 1) = " << count_c(2, 1) << ", ожидалось 5");
    BOOST_CHECK_MESSAGE(count_c(3, 2) == 13, "count_c(3, 2) = " << count_c(3, 2) << ", ожидалось 13");
    BOOST_CHECK_MESSAGE(count_c(4, 1) == 17, "count_c(4, 1) = " << count_c(4, 1) << ", ожидалось 17");
}
BOOST_AUTO_TEST_SUITE_END()



BOOST_AUTO_TEST_SUITE(PrimitiveTests)
BOOST_AUTO_TEST_CASE(PrimitiveTest_TruePairs){
    BOOST_TEST_MESSAGE("Тестирование проверки на взаимно обратность для истинных пар...");
    BOOST_CHECK_MESSAGE(is_primitive(2, 1), "is_primitive(2, 1) = " << is_primitive(2, 1) << ", ожидалось true");
    BOOST_CHECK_MESSAGE(is_primitive(3, 2), "is_primitive(3, 2) = " << is_primitive(3, 2) << ", ожидалось true");
    BOOST_CHECK_MESSAGE(is_primitive(4, 1), "is_primitive(4, 1) = " << is_primitive(4, 1) << ", ожидалось true");
}
BOOST_AUTO_TEST_CASE(PrimitiveTest_FalsePairs){
    BOOST_TEST_MESSAGE("Тестирование проверки на взаимно обратность для ложных пар...");
    BOOST_CHECK_MESSAGE(!is_primitive(4, 2), "is_primitive(4, 2) = " << is_primitive(4, 2) << ", ожидалось false");
    BOOST_CHECK_MESSAGE(!is_primitive(6, 3), "is_primitive(6, 3) = " << is_primitive(6, 3) << ", ожидалось false");
    BOOST_CHECK_MESSAGE(!is_primitive(5, 1), "is_primitive(5, 1) = " << is_primitive(5, 1) << ", ожидалось false");
}
BOOST_AUTO_TEST_SUITE_END()



BOOST_AUTO_TEST_SUITE(TripleTests)
BOOST_AUTO_TEST_CASE(PythagorasTest_4_1) {
    BOOST_TEST_MESSAGE("Тестирование расчёта сторон по теореме Пифагора...");
    int64_t a = count_a(4, 1);
    int64_t b = count_b(4, 1);
    int64_t c = count_c(4, 1);

    BOOST_CHECK_MESSAGE(a * a + b * b == c * c, "Несоответствие теореме Пифагора (a2 + b2 != c2): " << a * a << " + " << b * b << " != " << c * c);
}
BOOST_AUTO_TEST_CASE(PythagorasTest_17_12){
    int64_t a = count_a(17, 12);
    int64_t b = count_b(17, 12);
    int64_t c = count_c(17, 12);

    BOOST_REQUIRE_MESSAGE(a * a + b * b == c * c, "Несоответствие теореме Пифагора (a2 + b2 != c2): " << a * a << " + " << b * b << " != " << c * c);
}
BOOST_AUTO_TEST_CASE(PythagorasTest_100_100) {
    int64_t a = count_a(100, 100);
    int64_t b = count_b(100, 100);
    int64_t c = count_c(100, 100);

    BOOST_REQUIRE_MESSAGE(a * a + b * b == c * c, "Несоответствие теореме Пифагора (a2 + b2 != c2): " << a * a << " + " << b * b << " != " << c * c);
}
BOOST_AUTO_TEST_SUITE_END()



BOOST_AUTO_TEST_SUITE(TripleGeneratorTests)
BOOST_AUTO_TEST_CASE(TripleTest_GeneratingCheck_4) {
    BOOST_TEST_MESSAGE("Тестирование полученных троек для N = 5");
    std::vector<std::vector<int64_t>> triples = generate_triples(5);

    BOOST_CHECK_MESSAGE(contains_triple(triples, 3, 4, 5) == true, "generate_triples(15) не содержит тройку (3, 4, 5)");
}
BOOST_AUTO_TEST_CASE(TripleTest_GeneratingCheck_15){
    BOOST_TEST_MESSAGE("Тестирование полученных троек для N = 15");
    std::vector<std::vector<int64_t>> triples = generate_triples(15);

    BOOST_CHECK_MESSAGE(contains_triple(triples, 3, 4, 5) == true, "generate_triples(15) не содержит тройку (3, 4, 5)");
    BOOST_CHECK_MESSAGE(contains_triple(triples, 5, 12, 13) == true, "generate_triples(15) не содержит тройку (5, 12, 13)");
    BOOST_CHECK_MESSAGE(contains_triple(triples, 6, 8, 10) == true, "generate_triples(15) не содержит тройку (6, 8, 10)");
    BOOST_CHECK_MESSAGE(contains_triple(triples, 9, 12, 15) == true, "generate_triples(15) не содержит тройку (9, 12, 15)");
}
BOOST_AUTO_TEST_CASE(TripleTest_GeneratingCheck_30){
    BOOST_TEST_MESSAGE("Тестирование полученных троек для N = 30");
    std::vector<std::vector<int64_t>> triples = generate_triples(30);

    BOOST_CHECK_MESSAGE(contains_triple(triples, 3, 4, 5) == true, "generate_triples(30) не содержит тройку (3, 4, 5)");
    BOOST_CHECK_MESSAGE(contains_triple(triples, 5, 12, 13) == true, "generate_triples(30) не содержит тройку (5, 12, 13)");
    BOOST_CHECK_MESSAGE(contains_triple(triples, 6, 8, 10) == true, "generate_triples(30) не содержит тройку (6, 8, 10)");
    BOOST_CHECK_MESSAGE(contains_triple(triples, 9, 12, 15) == true, "generate_triples(30) не содержит тройку (9, 12, 15)");
    BOOST_CHECK_MESSAGE(contains_triple(triples, 12, 16, 20) == true, "generate_triples(30) не содержит тройку (12, 16, 20)");
    BOOST_CHECK_MESSAGE(contains_triple(triples, 15, 20, 25) == true, "generate_triples(30) не содержит тройку (15, 20, 25)");
    BOOST_CHECK_MESSAGE(contains_triple(triples, 18, 24, 30) == true, "generate_triples(30) не содержит тройку (18, 24, 30)");
    BOOST_CHECK_MESSAGE(contains_triple(triples, 20, 21, 29) == true, "generate_triples(30) не содержит тройку (20, 21, 29)");
    BOOST_CHECK_MESSAGE(contains_triple(triples, 10, 24,26) == true, "generate_triples(30) не содержит тройку (10, 24, 26)");
    BOOST_CHECK_MESSAGE(contains_triple(triples, 7, 24, 25) == true, "generate_triples(30) не содержит тройку (7, 24, 25)");
    BOOST_CHECK_MESSAGE(contains_triple(triples, 8, 15, 17) == true, "generate_triples(30) не содержит тройку (8, 15, 17)");
}
BOOST_AUTO_TEST_SUITE_END()



BOOST_AUTO_TEST_SUITE(TripleCountTests_Equal)
BOOST_AUTO_TEST_CASE(TripleCountTests_MaxTooSmall){
    BOOST_TEST_MESSAGE("Тестирование полученного количества троек: \n для малого N = 4...");
    BOOST_CHECK_MESSAGE(generate_triples(4).size() == 0ll, "generate_triples(4) должен содержать 0 троек, содержит " << generate_triples(4).size());
}
BOOST_AUTO_TEST_CASE(TripleCountTests_MaxFive){
    BOOST_TEST_MESSAGE(" для N = 5...");
    BOOST_CHECK_MESSAGE(generate_triples(5).size() == 1ll, "generate_triples(5) должен содержать 1 троек, содержит " << generate_triples(5).size());
}
BOOST_AUTO_TEST_CASE(TripleCountTests_MaxTwenty){
    BOOST_TEST_MESSAGE(" для N = 20...");
    BOOST_CHECK_MESSAGE(generate_triples(20).size() == 6ll, "generate_triples(20) должен содержать 6 троек, содержит " << generate_triples(20).size());
}
BOOST_AUTO_TEST_CASE(TripleCountTests_MaxTenThousands){
    BOOST_TEST_MESSAGE(" для большого N = 10000...");
    BOOST_CHECK_MESSAGE(generate_triples(10000).size() == 12471ll , "generate_triples(10000) должен содержать 12471 троек, содержит " << generate_triples(10000).size());
}
BOOST_AUTO_TEST_SUITE_END()