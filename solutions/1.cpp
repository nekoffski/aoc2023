#include <utils.hpp>

int main(int argc, char** argv) {
    const auto input = readInput(argc, argv);

    // 1
    const auto output1 = std::accumulate(
      input.begin(), input.end(), 0u,
      [&](u32 rest, std::string line) -> u32 {
          LOG("{}", line);
          std::erase_if(line, [](char c) -> bool { return c < '0' || c > '9'; });
          if (line.size() == 1)
              line.append(std::string{ line[0] });
          else
              line = fmt::format("{}{}", line[0], line[line.size() - 1]);
          LOG("{} + {}", rest, line);
          if (line.size() == 0) return rest;
          return rest + std::stoi(line);
      }
    );
    LOG("Output1 = {}", output1);
    // 2
    std::unordered_map<std::string, u32> dict = {
        {"one",    1},
        { "two",   2},
        { "three", 3},
        { "four",  4},
        { "five",  5},
        { "six",   6},
        { "seven", 7},
        { "eight", 8},
        { "nine",  9},
    };
    for (u32 i = 0; i < 10u; ++i) dict[std::to_string(i)] = i;

    const auto output2 = std::accumulate(
      input.begin(), input.end(), 0u,
      [&](u32 rest, std::string line) -> u32 {
          std::vector<std::pair<int, int>> records;

          for (const auto& [s, d] : dict) {
              if (u64 l = line.find(s); l != line.npos) records.push_back({ l, d });
              if (u64 r = line.rfind(s); r != line.npos) records.push_back({ r, d });
          }

          const auto& [min, max] = std::minmax_element(
            records.begin(), records.end(),
            [](auto& lhs, auto& rhs) -> bool { return lhs.first <= rhs.first; }
          );
          return rest + (min->second * 10 + max->second);
      }
    );
    LOG("Output2 = {}", output2);
    return 0;
}