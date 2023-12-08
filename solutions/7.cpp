#include <utils.hpp>

int main(int argc, char** argv) {
    struct Hand {
        std::string cards;
        u64 bid;
        u64 type;
    };

    const auto input = readInput(argc, argv);
    std::vector<Hand> hands;
    hands.reserve(input.size());

    std::transform(
      input.begin(), input.end(), std::back_inserter(hands),
      [](std::string line) {
          auto d     = core::split(line, ' ');
          auto cards = d[0];

          Map<char, u8> hist;
          for (auto& c : cards) hist[c]++;

          char maxKey = 'A';
          for (auto& [k, v] : hist)
              if (k != 'J' && v > hist[maxKey]) maxKey = k;
          hist[maxKey] += hist['J'];

          Map<u8, u8> counts;
          for (auto& [k, v] : hist)
              if (k != 'J') counts[v]++;

          auto getType = [&](Map<u8, u8>& counts) -> u8 {
              static auto getBaseType = [&] {  // just for logging
                  if (counts.contains(5)) {
                      return 7u;
                  } else if (counts.contains(4)) {
                      return 6u;
                  } else if (counts.contains(3)) {
                      if (counts.contains(2)) return 5u;
                      return 4u;
                  } else if (not counts.contains(2)) {
                      return 1u;
                  }
                  if (counts[2] == 2) {
                      return 3u;
                  } else {
                      return 2u;
                  }
              };
              auto type = getBaseType();
              //   if (jokers > 0) LOG("{} -> {}", cards, type);
              return type;
          };

          return Hand{ cards, std::stoul(d[1]), getType(counts) };
      }
    );

    static Map<char, u16> strengths = {
        {'T',  11},
        { 'J', 2 },
        { 'Q', 12},
        { 'K', 13},
        { 'A', 14}
    };
    for (int i = 2; i <= 9; ++i) strengths['0' + i] = i + 1;

    static auto getStrength = [](char c) -> u8 { return strengths[c]; };

    for (auto& [k, v] : strengths) {
        LOG("{} -> {}", k, v);
    }

    const auto compare = [&](const Hand& lhs, const Hand& rhs) -> bool {
        if (lhs.type != rhs.type) return lhs.type < rhs.type;

        for (int i = 0; i < lhs.cards.size(); ++i) {
            auto lhsCard = getStrength(lhs.cards[i]);
            auto rhsCard = getStrength(rhs.cards[i]);

            if (lhsCard == rhsCard) continue;
            return lhsCard < rhsCard;
        }

        return true;
    };

    std::sort(hands.begin(), hands.end(), compare);

    u64 result1 = 0u;
    for (u64 i = 0u; i < hands.size(); ++i) result1 += (i + 1) * hands[i].bid;
    LOG("Output1={}", result1);

    // 249368947 is wrong/
    // 249410741
    // 249400220

    return 0;
}
