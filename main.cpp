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
            if(number <= 13) {
                curGame.green += number;
                fmt::print("possible\t{} {} {}\n", name, number, curGame.green);
            }else{
                fmt::print("not possible\t{} {} {}\n", name, number, curGame.green);
                return GameInfo{};
            }

        } else if(name == "red") {
            if(number <= 12) {
                curGame.red += number;
                fmt::print("possible\t{} {} {}\n", name, number, curGame.red);
            }
            else{
                fmt::print("not possible\t{} {} {}\n", name, number, curGame.red);
                return GameInfo{};
            }
        } else if(name == "blue") {
            if(number <= 14) {
                curGame.blue += number;
                fmt::print("possible\t{} {} {}\n", name, number, curGame.blue);
            }else{
                fmt::print("not possible\t{} {} {}\n", name, number, curGame.blue);
                return GameInfo{};
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
    GameInfo combinedGames{};
    for(auto const& games : playedGames) {
        if(games.red > 0  && games.green > 0 && games.blue > 0) {
            fmt::print("possible\t");
            fmt::print(
              "id {}, red {} blue {} green {}\n",
              games.id,
              games.red,
              games.blue,
              games.green);

            combinedGames.id += games.id;
        } else {
            fmt::print("not possible\t");
            fmt::print(
              "id {}, red {} blue {} green {}\n",
              games.id,
              games.red,
              games.blue,
              games.green);
        }
    }
    fmt::print("result: {}\n", combinedGames.id);
}
