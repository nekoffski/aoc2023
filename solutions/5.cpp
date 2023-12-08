#include <utils.hpp>

#include <kc/async/TaskScheduler.hpp>
#include <kc/async/Utils.hpp>

int main(int argc, char** argv) {
    const auto input = readInput(argc, argv);

    // 1
    std::vector<u64> seeds;
    for (auto seed : core::split(input[0].substr(input[0].find(":") + 1), ' '))
        seeds.push_back(std::stoul(seed));

    struct FlatRangeMap {
        struct Record {
            u64 k;
            u64 v;
            u64 range;
        };
        u64 lookup(u64 key) const {
            for (auto& record : records) {
                if (key >= record.k && key <= record.k + record.range) {
                    const auto diff = key - record.k;
                    return record.v + diff;
                }
            }
            return key;
        }

        std::vector<u64> rangeLookup(const std::vector<std::pair<u64, u64>>& range) {
            std::vector<u64> out;
            for (auto& [i, j] : range) {
                // auto v = i + j;
            }

            return out;
        }

        void push(u64 k, u64 v, u64 range) { records.push_back({ k, v, range }); }

        std::vector<Record> records;
    };

    std::vector<FlatRangeMap> maps;

    for (int i = 2; i < input.size(); ++i) {
        auto& line = input[i];
        if (line.empty()) continue;
        if (line.find("map") != line.npos) {
            maps.push_back(FlatRangeMap{});
        } else {
            auto data = core::split(line, ' ');
            maps.back().push(
              std::stoul(data[1]), std::stoul(data[0]), std::stoul(data[2])
            );
        }
    }

    auto seedsCopy = seeds;
    for (auto& map : maps)
        for (auto& seed : seedsCopy) seed = map.lookup(seed);
    auto min = std::min_element(seedsCopy.begin(), seedsCopy.end());
    LOG("Output1 = {}", *min);

    // 2.
    std::vector<u64> possibleSeeds;
    for (int i = 0; i < seeds.size(); i += 2) {
        // auto local = maps[0].rangeLookup(seeds[i], seeds[i + 1]);
        // std::copy(local.begin(), local.end(), std::back_inserter(possibleSeeds));
    }

    for (int i = 1; i < maps.size(); ++i)
        for (auto& seed : possibleSeeds) seed = maps[i].lookup(seed);
    min = std::min_element(possibleSeeds.begin(), possibleSeeds.end());
    LOG("Output2 = {}", *min);
}
