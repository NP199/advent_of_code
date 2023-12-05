#include <algorithm>
#include <exception>
#include <fmt/core.h>
#include <fstream>
#include <string>
#include <vector>

struct GameInfo {
    unsigned int id;
    unsigned int green;
    unsigned int red;
    unsigned int blue;
};

GameInfo parseLine(std::string& line) {
    GameInfo          curGame{};
    std::string const delimiters{":,;"};

    while(!line.empty()) {
        //find blob
        std::size_t pos = line.find_first_of(delimiters);

        //temp save blob
        std::string substr{line.substr(0, pos)};
        //fmt::print("{}\n", substr);

        //parse blob
        std::string name{};
        std::string numStr{};
        if(pos != std::string::npos) {
            for(std::size_t i = 0; i < pos; ++i) {
                if(!(std::isdigit(substr[i]))) {
                    name += substr[i];
                } else {
                    numStr += substr[i];
                }
            }
        } else {
            for(std::size_t i = 0; i < line.size(); ++i) {
                if(!(std::isdigit(substr[i]))) {
                    name += substr[i];
                } else {
                    numStr += substr[i];
                }
            }
        }

        unsigned int number{std::stoi(numStr)};
        name.erase(
          remove_if(name.begin(), name.end(), [](unsigned char c) { return std::isspace(c); }),
          name.end());
        std::transform(name.begin(), name.end(), name.begin(), [](unsigned char c) {
            return std::tolower(c);
        });

        if(name == "green") {
            if(number >= curGame.green) curGame.green = number;
            fmt::print("bigger found:\t{} {} {}\n", name, number, curGame.green);

        } else if(name == "red") {
            if(number >= curGame.red) {
                curGame.red = number;
                fmt::print("bigger found:\t{} {} {}\n", name, number, curGame.red);
            }

        } else if(name == "blue") {
            if(number >= curGame.blue) {
                curGame.blue = number;
                fmt::print("bigger found:\t{} {} {}\n", name, number, curGame.blue);
            }
        } else if(name == "game") {
            curGame.id = number;
            fmt::print("{} {} {}\n", name, number, curGame.id);
        }

        //truncate blob
        if(pos != std::string::npos) {
            line.erase(0, pos + 1);
        } else {
            line.erase(0, pos);
        }
    }
    fmt::print("empty id parsed: {}\n", curGame.id);
    return curGame;
}

int main() {
    std::string const filename{"../puzzle.txt"};
    std::fstream      fileHandle{filename, fileHandle.in};
    if(!fileHandle.is_open()) {
        fmt::print("Error opening file!\n");
        std::terminate();
    }

    std::string           line;
    unsigned int          sumIdValues{0};
    std::vector<GameInfo> playedGames{};
    while(std::getline(fileHandle, line)) {
        fmt::print("{}\n", line);
        playedGames.push_back(parseLine(line));
    }
    fmt::print("");
    GameInfo     combinedGames{};
    unsigned int powerOfGame{1};
    unsigned int sumOfAll{};
    for(auto const& game : playedGames) {
        fmt::print("id {}, red {} blue {} green {}\n", game.id, game.red, game.blue, game.green);
        powerOfGame = game.red * game.blue * game.green;
        sumOfAll    += powerOfGame;
    }
    fmt::print("result: {}\n", sumOfAll);
}
