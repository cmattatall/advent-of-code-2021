#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include <charconv>
#include <functional>

struct point {
    int x;
    int y;
    int aim;
};

struct Solution {
   public:
    Solution() : input("input.txt"), coords{0, 0} {}

    ~Solution() {
        input.close();
    }

    void part1();
    void part2();

    void init();   // rewind the input file for reading and reset the coordinates
    void print();  // output the coordinates
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

enum class Direction { DIR_X, DIR_Y };

struct Dirmap {
    Direction dir;
    int sign;
};

std::map<std::string, Dirmap> dirmap1 = {
    {"forward", {Direction::DIR_X, 1}},
    {"up", {Direction::DIR_Y, -1}},    // we are measuring DEPTH so UP is negative
    {"down", {Direction::DIR_Y, 1}}};  // we are measuring DEPTH so DOWN is positive

void Solution::init() {
    input.clear();
    input.seekg(0);
    coords.x = 0;
    coords.y = 0;
    coords.aim = 0;
}

void Solution::part1() {
    init();
    std::string line;
    while (std::getline(input, line)) {
        std::vector<std::string> fields = tokenize(line);

        int distance;
        std::string const &dist_str = fields[1];
        std::from_chars(dist_str.data(), dist_str.data() + dist_str.size(), distance);

        switch (dirmap1[fields[0]].dir) {
            case Direction::DIR_X:
                coords.x += dirmap1[fields[0]].sign * distance;
                break;
            case Direction::DIR_Y:
                coords.y += dirmap1[fields[0]].sign * distance;
                break;
            default:
                throw std::string("THERES A BUG IN YOUR CODE");
        }
    }
    std::cout << coords.x * coords.y << std::endl;
}

void Solution::part2() {
    init();
    std::map<std::string, std::function<void(std::string const &)>> dirmap2 = {
        {"forward",
         [this](std::string const &dist_str) {
             int value;
             std::from_chars(dist_str.data(), dist_str.data() + dist_str.size(), value);

             std::cout << "before >forward " << dist_str << "< , x = " << this->coords.x << ", y = " << this->coords.y
                       << " and aim = " << this->coords.aim << std::endl;
             this->coords.x += value;
             this->coords.y += value * this->coords.aim;
             std::cout << "after >forward " << dist_str << "< , x = " << this->coords.x << ", y = " << this->coords.y
                       << " and aim = " << this->coords.aim << std::endl;
         }},
        {"up",
         [this](std::string const &dist_str) {
             int value;
             std::from_chars(dist_str.data(), dist_str.data() + dist_str.size(), value);

             std::cout << "before >up " << dist_str << "< , x = " << this->coords.x << ", y = " << this->coords.y
                       << " and aim = " << this->coords.aim << std::endl;
             this->coords.aim -= value;
             std::cout << "after >up " << dist_str << "< , x = " << this->coords.x << ", y = " << this->coords.y
                       << " and aim = " << this->coords.aim << std::endl;
         }},
        {"down", [this](std::string const &dist_str) {
             int value;
             std::from_chars(dist_str.data(), dist_str.data() + dist_str.size(), value);
             std::cout << "before >down " << dist_str << "< , x = " << this->coords.x << ", y = " << this->coords.y
                       << " and aim = " << this->coords.aim << std::endl;
             this->coords.aim += value;
             std::cout << "after >down " << dist_str << "< , x = " << this->coords.x << ", y = " << this->coords.y
                       << " and aim = " << this->coords.aim << std::endl;
         }}};

    std::string line;
    while (std::getline(input, line)) {
        std::cout << "line = " << line << std::endl;
        std::vector<std::string> fields = tokenize(line);
        dirmap2[fields[0]](fields[1]);
    }
    std::cout << coords.x * coords.y << std::endl;
}

int main(int argc, char **argv) {
    Solution solution;

    solution.part1();

    solution.part2();

    return 0;
}
