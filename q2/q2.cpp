#include <fstream>
#include <iostream>

class Solution {
   public:
    Solution() : input("input.txt") {}

    ~Solution() {
        input.close();
    }

    void part1();
    void part2();

   private:
    std::ifstream input;
};

void Solution::part1() {}

void Solution::part2() {}

int main(int argc, char** argv) {
    Solution solution;

    solution.part1();

    solution.part2();

    return 0;
}
