#include <utils.hpp>

std::vector<u32> getIntersection(const std::string& line) {
    const auto splitCard = [&](const std::string& line) {
        auto data = core::split(line, '|');

        const auto split = [&](std::string line) {
            boost::algorithm::trim(line);
            auto numbers = core::split(line, ' ');

            std::vector<u32> out;
            out.reserve(numbers.size());

            std::transform(
              numbers.begin(), numbers.end(), std::back_inserter(out),
              [](const std::string& n) -> u32 { return std::stoi(n); }
            );

            return out;
        };
        return std::make_pair(split(data[0]), split(data[1]));
    };

    auto [lhs, rhs] = splitCard(line);

    std::sort(lhs.begin(), lhs.end());
    std::sort(rhs.begin(), rhs.end());

    std::vector<u32> intersection;
    std::set_intersection(
      lhs.begin(), lhs.end(), rhs.begin(), rhs.end(),
      std::back_inserter(intersection)
    );

    return intersection;
}

u64 processLine(
  u64 id, const std::string& line, std::unordered_map<u64, u64>& cache,
  const std::vector<std::string>& cards
) {
    if (cache.contains(id)) return cache.at(id);

    LOG("Processing card: {}", id);

    u64 local = 1u;  // self
    for (int i = 0; i < getIntersection(line).size(); ++i)
        local += processLine(id + i + 1, cards[id + i], cache, cards);
    cache[id] = local;
    return local;
}

int main(int argc, char** argv) {
    const auto input = readInput(argc, argv);

    // 1
    std::vector<std::string> cards;
    cards.reserve(input.size());

    std::transform(
      input.begin(), input.end(), std::back_inserter(cards),
      [](const std::string& line) -> std::string {
          return line.substr(line.find(":") + 2);
      }
    );

    const auto output1 = std::accumulate(
      cards.begin(), cards.end(), 0u,
      [&](u32 rest, std::string line) -> u32 {
          auto intersection = getIntersection(line);

          if (auto n = intersection.size(); n >= 1) return rest + (1 << (n - 1));
          return rest;
      }
    );
    LOG("Output1 = {}", output1);

    // 2
    u64 output2 = 0;
    std::unordered_map<u64, u64> cache;

    for (int i = 0; i < cards.size(); ++i)
        output2 += processLine(i + 1, cards[i], cache, cards);
    LOG("Output2 = {}", output2);

    return 0;
}