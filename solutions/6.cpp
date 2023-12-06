#include <utils.hpp>

int main(int argc, char** argv) {
    // 1. data
    std::vector<u64> times     = { 46, 82, 84, 79 };
    std::vector<u64> distances = { 347, 1522, 1406, 1471 };

    const auto calculate =
      [](const std::vector<u64>& times, const std::vector<u64>& distances) {
          u64 output = 1;

          // velocity * rest_time >= distance
          for (int i = 0; i < times.size(); ++i) {
              const auto t = times[i];
              const auto d = distances[i];

              u64 lval = 0u;
              u64 rval = 0u;

              for (int i = 1; i <= t; ++i) {
                  if (i * (t - i) > d) {
                      lval = i;
                      break;
                  }
              }
              for (int i = t; i >= 0; --i) {
                  if (i * (t - i) > d) {
                      rval = i;
                      break;
                  }
              }
              output *= (rval - lval + 1);
          }

          return output;
      };

    LOG("Output1={}", calculate(times, distances));
    LOG("Output2={}", calculate({ 46828479 }, { 347152214061471 }));

    return 0;
}
