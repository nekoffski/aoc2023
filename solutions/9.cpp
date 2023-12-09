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
    i64 output1 = 0;
    i64 output2 = 0;
    for (const auto& line : input) {
        auto data = transformLine(line);

        std::vector<i64> rcache = { data.back() };
        std::vector<i64> lcache = { data.front() };
        std::vector<i64> diffs  = data;

        do {
            data = diffs;
            diffs.clear();
            for (int i = 0; i < data.size() - 1; ++i)
                diffs.push_back(data[i + 1] - data[i]);
            rcache.push_back(diffs.back());
            lcache.push_back(diffs.front());
        } while (not allZero(diffs));

        // 1.
        auto local = std::accumulate(rcache.begin(), rcache.end(), 0);
        output1 += local;

        // 2.
        while (lcache.size() > 1) {
            const int n = lcache.size();
            lcache[n - 2] -= lcache[n - 1];
            lcache.pop_back();
        }

        output2 += lcache.front();
    }

    LOG("Output1={}", output1);
    LOG("Output2={}", output2);

    return 0;
}