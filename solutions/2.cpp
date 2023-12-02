#include <utils.hpp>

int main(int argc, char** argv) {
    const auto input = readInput(argc, argv);
    // 1
    static const auto createTarget =
      [](int red = 12, int green = 13, int blue = 14) {
          return std::unordered_map<std::string, int>{
              {"red",    red  },
              { "green", green},
              { "blue",  blue },
          };
      };

    const auto output1 = std::accumulate(
      input.begin(), input.end(), 0u,
      [&](u32 rest, std::string line) -> u32 {
          auto dataOffset = line.find(":") + 1;
          auto id         = std::stoi(line.substr(5, dataOffset - 6));
          LOG("{}", id);
          for (auto session : core::split(line.substr(dataOffset + 1), ';')) {
              boost::algorithm::trim(session);
              auto target = createTarget();
              LOG("\t{}", session);
              for (auto colorInfo : core::split(session, ',')) {
                  boost::algorithm::trim(colorInfo);
                  LOG("\t\t{}", colorInfo);
                  auto s = core::split(colorInfo, ' ');
                  target[s[1]] -= std::stoi(s[0]);
              }
              for (const auto& [k, v] : target) {
                  if (v < 0) {
                      LOG("Game impossible: {}", k);
                      return rest;
                  }
              }
          }

          return rest + id;
      }
    );
    LOG("Output1 = {}", output1);

    // 2
    const auto output2 = std::accumulate(
      input.begin(), input.end(), 0u,
      [&](u32 rest, std::string line) -> u32 {
          auto dataOffset = line.find(":") + 1;
          auto id         = std::stoi(line.substr(5, dataOffset - 6));
          LOG("{}", id);

          auto target = createTarget(0, 0, 0);

          for (auto session : core::split(line.substr(dataOffset + 1), ';')) {
              boost::algorithm::trim(session);
              LOG("\t{}", session);

              auto localTarget = createTarget(0, 0, 0);

              for (auto colorInfo : core::split(session, ',')) {
                  boost::algorithm::trim(colorInfo);
                  auto s     = core::split(colorInfo, ' ');
                  auto color = s[1];
                  auto count = std::stoi(s[0]);

                  localTarget[color] += count;
              }

              for (const auto& [k, v] : localTarget)
                  if (target[k] < localTarget[k]) target[k] = v;
          }

          auto v = target | std::views::values;

          return rest
                 + std::accumulate(v.begin(), v.end(), 1u, [](u32 rest, auto& v) {
                       return rest * v;
                   });
      }
    );
    LOG("Output2 = {}", output2);

    return 0;
}