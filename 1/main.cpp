#include <algorithm>
#include <exception>
#include <fmt/core.h>
#include <fstream>
#include <string>
#include <vector>
#include <variant>

/*
    * Herausfinden welche Zahlen Kontakt haben mit einem Symbol
    * Partnumber true/false
    * Position
    */

/*
    * std::ispunct zum kontrollieren ob es sich um ein Sonderzeichen etc handelt
    * "punctuation character"
    */

struct partType {
    std::variant<char, unsigned int>  parsedSign;
    unsigned int position;
    bool         partNumberFlag;
};

int main() {
    std::string const filePath{"../puzzle.txt"};
    std::fstream      fileHandle{filePath};
    if(!fileHandle.is_open()) {
        fmt::print(stderr, "Error opening File!\n");
        std::terminate();
    }

    std::string           line{};
    std::vector<partType> parsedSigns{};

    auto parseFunction = [&](std::string const& str) {
        partType tempSign;
        //get the numbers and characters
        for(std::size_t i = 0; auto const& character : str) {
            if(std::isdigit(character)) {
                //gefundene Zahl cast to ASCII - ASCII '0' to get int value
                tempSign.parsedSign.emplace<unsigned int>(static_cast<unsigned int>(character - '0'));
                //fmt::print("foo: {}\n", std::get<1>(tempSign.parsedSign));
                tempSign.position       = i;
                tempSign.partNumberFlag = true;
                parsedSigns.push_back(tempSign);
            } else if(std::ispunct(character) && character != '.') {
                //Sonderzeichen gefunden außer "."
                tempSign.parsedSign.emplace<char>(character);
                //fmt::print("bar: {}\n", std::get<0>(tempSign.parsedSign));
                tempSign.position       = i;
                tempSign.partNumberFlag = false;
                parsedSigns.push_back(tempSign);
            }
            ++i;
        }
        fmt::print("{}\n", str);
    };

    while(std::getline(fileHandle, line)) {
        parseFunction(line);
    }
}
