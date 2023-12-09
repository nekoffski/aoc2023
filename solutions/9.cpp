#include <utils.hpp>

int main(int argc, char** argv) {
    const auto input = readInput(argc, argv);

    static const auto transformLine =
      [](const std::string& line) -> std::vector<i64> {
        auto tokens = core::split(line, ' ');
        std::vector<i64> out;
        std::transform(
          tokens.begin(), tokens.end(), std::back_inserter(out),
          [](const std::string& num) -> i64 { return std::stol(num); }
        );
        return out;
    };

    static const auto allZero = [](std::vector<i64>& data) -> bool {
        return std::all_of(data.begin(), data.end(), [](i64 record) -> bool {
            return record == 0;
        });
    };

    // 1
    i64 output = 0;
    for (const auto& line : input) {
        auto data = transformLine(line);

        std::vector<i64> cache = { data.back() };
        std::vector<i64> diffs = data;

        do {
            data = diffs;
            diffs.clear();
            for (int i = 0; i < data.size() - 1; ++i)
                diffs.push_back(data[i + 1] - data[i]);
            cache.push_back(diffs.back());
        } while (not allZero(diffs));

        auto local = std::accumulate(cache.begin(), cache.end(), 0);
        LOG("Cache: {}, sum={}", formatVector(cache), local);
        output += local;
    }

    LOG("Output1={}", output);
    // 2
    output = 0;
    for (const auto& line : input) {
        auto data = transformLine(line);

        std::vector<i64> cache = { data.front() };
        std::vector<i64> diffs = data;

        do {
            data = diffs;
            diffs.clear();
            for (int i = 0; i < data.size() - 1; ++i)
                diffs.push_back(data[i + 1] - data[i]);
            cache.push_back(diffs.front());
        } while (not allZero(diffs));

        LOG("Cache: {}", formatVector(cache));

        while (cache.size() > 1) {
            const int n = cache.size();
            cache[n - 2] -= cache[n - 1];
            cache.pop_back();
        }

        i64 local = cache.front();
        LOG("\tdifference={}", local);
        output += local;
    }

    LOG("Output2={}", output);

    return 0;
}