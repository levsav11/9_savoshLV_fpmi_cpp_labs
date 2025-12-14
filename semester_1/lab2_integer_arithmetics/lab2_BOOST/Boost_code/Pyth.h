#pragma once

#include <vector>
#include <cstdint>
int64_t count_a(int32_t m, int32_t n);
int64_t count_b(int32_t m, int32_t n);
int64_t count_c(int32_t m, int32_t n);
std::vector<std::vector<int64_t>> generate_triples(int32_t max);
bool is_primitive(int32_t m, int32_t n);