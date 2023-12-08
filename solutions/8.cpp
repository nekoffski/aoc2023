#include <utils.hpp>

u64 gcd(u64 a, u64 b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

u64 lcm(const std::vector<u64>& arr) {
    u64 ans = arr[0];
    for (int i = 1; i < arr.size(); i++)
        ans = (((arr[i] * ans)) / (gcd(arr[i], ans)));
    return ans;
}

int main(int argc, char** argv) {
    const auto input = readInput(argc, argv);

    std::vector<u8> path;
    std::transform(
      input[0].begin(), input[0].end(), std::back_inserter(path),
      [](char c) -> u8 { return c == 'L' ? 0 : 1; }
    );
    const auto pathSize = path.size();

    using Node = std::array<std::string, 2>;  // {0, 1} -> label
    Map<std::string, Node> nodes;

    for (int i = 2; i < input.size(); ++i) {
        auto& l               = input[i];
        nodes[l.substr(0, 3)] = { l.substr(7, 3), l.substr(12, 3) };
    }

    std::string location = "AAA";
    u64 result1          = 0u;
    u64 pathIterator     = 0u;

    LOG("Output1={}", result1);

    // 2
    u64 result2 = 0u;

    std::vector<std::string> locations;
    for (const auto& k : nodes | std::views::keys)
        if (k.ends_with("A")) locations.push_back(k);

    std::vector<u64> lengths;

    for (auto& location : locations) {
        u64 local    = 0u;
        pathIterator = 0u;

        std::string locationCopy = location;
        do {
            const auto step = path[pathIterator++ % pathSize];
            locationCopy    = nodes[locationCopy][step];
            ++local;
        } while (not locationCopy.ends_with("Z"));

        LOG("{} -> {} length: {}", location, locationCopy, local);

        lengths.push_back(local);
    }

    LOG("Output2={}", lcm(lengths));

    return 0;
}