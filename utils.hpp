#pragma once

#include <string>
#include <vector>
#include <ostream>
#include <fstream>
#include <sstream>
#include <cstdint>
#include <numeric>
#include <ranges>
#include <algorithm>
#include <concepts>

#include <kc/core/String.h>
#include <boost/algorithm/string.hpp>
#include <fmt/core.h>

using u64 = uint64_t;
using u32 = uint32_t;
using u16 = uint16_t;
using u8  = uint8_t;

using namespace kc;

template <typename T>
requires std::is_integral_v<T>
constexpr T charToIntegral(char c) { return static_cast<T>(c - '0'); }

#define LOG(...)                 \
    {                            \
        fmt::print("$ - ");      \
        fmt::print(__VA_ARGS__); \
        fmt::print("\n");        \
    }

#define ASSERT(condition, ...)                        \
    if (not(condition)) {                             \
        fmt::print("ERROR: ");                        \
        fmt::print(__VA_ARGS__);                      \
        fmt::print("\n");                             \
        throw std::runtime_error("Assertion failed"); \
    }

std::vector<std::string> readInput(int argc, char** argv) {
    ASSERT(argc > 1, "Input file is required");
    std::string inputFile = argv[1];
    LOG("Input file - '{}'", inputFile);

    std::ifstream file(inputFile);
    ASSERT(file.is_open(), "Could not open file");

    std::vector<std::string> out;
    std::string line;
    while (std::getline(file, line)) out.push_back(line);

    file.close();
    return out;
}

void printMap(const auto& map) {
    for (auto& [k, v] : map) LOG("{} -> {}", k, v);
}
