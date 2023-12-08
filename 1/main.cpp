#include <algorithm>
#include <exception>
#include <fmt/core.h>
#include <fstream>
#include <string>
#include <vector>

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
    std::string               parsedSign;
    unsigned int position;
    bool                      partNumberFlag;
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
        for(std::size_t i = 0; auto const& character : str) {
            if(!std::ispunct(character)) {
                //gefunden Partnumber
                //fmt::print("{}\n",character);
                tempSign.parsedSign     = character;
                tempSign.position       = i;
                tempSign.partNumberFlag = true;
                parsedSigns.push_back(tempSign);
            } else {
                //Sonderzeichen gefunden außer "."
                if(character != '.') {
                    fmt::print("foo: {}\n", character);
                    tempSign.parsedSign     = character;
                    tempSign.position       = i;
                    tempSign.partNumberFlag = false;
                    parsedSigns.push_back(tempSign);
                }
            }
            fmt::print("{}:{} {}\n", i, character, std::ispunct(character));
            ++i;
        }
        fmt::print("{}\n\n", str);
    };

    while(std::getline(fileHandle, line)) {
        parseFunction(line);
    }

    for(auto const& signs : parsedSigns){
        fmt::print("{}\n", signs.parsedSign);

    }

}
