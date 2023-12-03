#include <algorithm>
#include <exception>
#include <fmt/core.h>
#include <fstream>
#include <regex>
#include <set>

int main() {
    std::set<std::tuple<std::string, std::uint8_t>> strNums{
      {  "one", 1},
      {  "two", 2},
      {"three", 3},
      { "four", 4},
      { "five", 5},
      {  "six", 6},
      {"seven", 7},
      {"eight", 8},
      { "nine", 9},
      {    "0", 0},
      {    "1", 1},
      {    "2", 2},
      {    "3", 3},
      {    "4", 4},
      {    "5", 5},
      {    "6", 6},
      {    "7", 7},
      {    "8", 8},
      {    "9", 9}
    };

    auto findFirstNum = [&](std::string const& str) {
        std::size_t firstNum{str.size()};
        std::uint8_t result{};
        for(auto& strNum : strNums) {
            std::size_t const num = str.find(std::get<0>(strNum));
            if(firstNum > num) {
                firstNum = num;
                if(num != std::string::npos) {
                    result = std::get<1>(strNum);
                }
            }
        }
        return result;
    };
    auto findLastNum = [&](std::string const& str) {
        std::size_t lastNum{};
        std::uint8_t result{};
        for(auto& strNum : strNums) {
            std::size_t const num = str.rfind(std::get<0>(strNum));
            if(num != std::string::npos) {
                if(lastNum <= num) {
                    lastNum = num;
                    result = std::get<1>(strNum);
                }
            }
        }
        return result;
    };

    std::string const filename{"../calibration.doc"};
    std::fstream      fileHandle{filename, fileHandle.in};
    if(!fileHandle.is_open()) {
        fmt::print("Error opening file!\n");
        std::terminate();
    }

    std::string   line;
    std::uint64_t sumCalValues{0};
    while(std::getline(fileHandle, line)) {
        std::uint8_t tempFirstVal{findFirstNum(line)};
        std::uint8_t tempLastVal{findLastNum(line)};
        std::uint64_t calNumber{(tempFirstVal * 10) + tempLastVal};
        sumCalValues += calNumber;
        fmt::print(
          "first: {}\t last: {}\t number:{}\t sum:{}\t",
          tempFirstVal,
          tempLastVal,
          calNumber,
          sumCalValues);
        fmt::print("{}\n", line);
    }
}
