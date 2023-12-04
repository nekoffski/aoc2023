#include <utils.hpp>

int main(int argc, char** argv) {
    const auto input = readInput(argc, argv);

    const u64 w = input[0].size();
    const u64 h = input.size();

    std::unordered_map<u64, std::vector<u64>> d;

    // 1
    u64 output1 = 0;

    const auto isDigit  = [](char c) -> bool { return std::isdigit(c); };
    const auto isSymbol = [&](char c) -> bool { return not isDigit(c) && c != '.'; };
    const auto isGood   = [&](int i, int j, int xoffset, u64 local) -> bool {
        bool isGood = false;
        for (int y = -1; y <= 1; ++y) {
            for (int x = -1; x <= xoffset; ++x) {
                int yy = i + y;
                int xx = j + x;

                if (yy >= 0 && xx >= 0 && yy < h && xx < w && isSymbol(input[yy][xx])) {
                    isGood = true;

                    if (input[yy][xx] == '*') d[yy * w + xx].push_back(local);
                }
            }
        }
        return isGood;
    };

    std::string number;
    for (u64 i = 0; i < h; ++i) {
        for (u64 j = 0; j < w; ++j) {
            const auto& line = input[i];
            if (isDigit(line[j])) {
                u64 begin   = j;
                u64 xoffset = 0;

                while (j < w && isDigit(line[j])) {
                    ++j;
                    ++xoffset;
                }
                u64 local = std::stoi(line.substr(begin, xoffset));
                if (isGood(i, begin, xoffset, local)) output1 += local;
            }
        }
    }
    LOG("Output1 = {}", output1);

    u64 output2 = 0u;
    for (const auto& [k, v] : d)
        if (v.size() == 2) output2 += v[0] * v[1];
    LOG("Output2 = {}", output2);

    return 0;
}