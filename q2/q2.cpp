#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include <charconv>

struct point {
    int x;
    int y;
};

class Solution {
   public:
    Solution() : input("input.txt"), coords{0, 0} {}

    ~Solution() {
        input.close();
    }

    void part1();
    void part2();

   private:
    void init();   // rewind the input file for reading and reset the coordinates
    void print();  // output the coordinates
    void answer();
    std::vector<std::string> tokenize(std::string const &line);
    std::ifstream input;

    point coords;
};

std::vector<std::string> Solution::tokenize(std::string const &line) {
    std::stringstream ss(line);
    std::string s;
    std::vector<std::string> tokens;
    while (std::getline(ss, s, ' ')) {
        tokens.push_back(s);
    }
    return tokens;
}

void Solution::print() {
    std::cout << "(" << coords.x << ", " << coords.y << ")" << std::endl;
}

void Solution::answer() {
    std::cout << coords.x * coords.y << std::endl;
}

enum class Direction { DIR_X, DIR_Y };

struct Dirmap {
    Direction dir;
    int sign;
};

std::map<std::string, Dirmap> dirmap = {{"forward", {Direction::DIR_X, 1}},
                                        {"backward", {Direction::DIR_X, -1}},
                                        {"up", {Direction::DIR_Y, -1}},    // we are measuring DEPTH so UP is negative
                                        {"down", {Direction::DIR_Y, 1}}};  // we are measuring DEPTH so DOWN is positive

void Solution::init() {
    input.clear();
    input.seekg(0);
    coords.x = 0;
    coords.y = 0;
}

void Solution::part1() {
    init();
    std::string line;
    while (std::getline(input, line)) {
        std::vector<std::string> fields = tokenize(line);

        int distance;
        std::string const &dist_str = fields[1];
        std::from_chars(dist_str.data(), dist_str.data() + dist_str.size(), distance);

        switch (dirmap[fields[0]].dir) {
            case Direction::DIR_X:
                coords.x += dirmap[fields[0]].sign * distance;
                break;
            case Direction::DIR_Y:
                coords.y += dirmap[fields[0]].sign * distance;
                break;
            default:
                throw std::string("THERES A BUG IN YOUR CODE");
        }
    }
    answer();
}

void Solution::part2() {
    init();
    std::string line;
    while (std::getline(input, line)) {
    }
    answer();
}

int main(int argc, char **argv) {
    Solution solution;

    solution.part1();

    solution.part2();

    return 0;
}
