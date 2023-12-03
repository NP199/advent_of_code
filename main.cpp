#include <algorithm>
#include <exception>
#include <fmt/core.h>
#include <fstream>
#include <regex>

int main() {
    auto findFirstNum = [](std::string const& str) {
        std::size_t const num    = str.find_first_of("0123456789");
        if(num != std::string::npos) {
            return str.substr(num, 1);
        }
        return std::string{};
    };
    auto findLastNum = [](std::string const& str) {
        std::size_t const num    = str.find_last_of("0123456789");
        if(num != std::string::npos) {
            return str.substr(num, 1);
        }
        return std::string{};
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
        std::uint64_t tempFirstVal{std::stoi(findFirstNum(line))};
        std::uint64_t tempLastVal{std::stoi(findLastNum(line))};
        std::uint64_t calNumber{(tempFirstVal * 10) + tempLastVal};
        sumCalValues += calNumber;
        fmt::print("first: {}\t last: {}\t number:{}\t sum:{}\t", tempFirstVal, tempLastVal, calNumber ,sumCalValues);
        fmt::print("{}\n", line);
    }
}
