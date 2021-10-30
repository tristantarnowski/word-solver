#include <algorithm>
#include <array>
#include <chrono>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

struct result {
    std::string string;
    int points;
};

struct compare_length {
    bool operator()(const result& first, const result& second) {
        return first.string.size() < second.string.size();
    }
};

struct compare_points {
    bool operator()(const result& first, const result& second) {
        return first.points < second.points;
    }
};



int main(int argc, char const* argv[]) {
    std::set<std::string> word_list;
    std::ifstream file("words_alpha.txt");
    std::string line;

    std::array<int, 26> values =
        {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

    while (file >> line) {
        word_list.insert(line);
    }


    bool scrabble_mode = false;
    while (1) {
        std::string input;
        std::cout << "Sorting by " << (scrabble_mode ? "points" : "length") << '\n';
        std::cout << "Enter letters: ";
        std::cin >> input;

        
        if (input == "_") {
            scrabble_mode = !scrabble_mode;
            continue;
        }



        auto start = std::chrono::high_resolution_clock::now();

        int blanks = std::count(input.begin(), input.end(), '_');
        std::vector<result> results;

        for (auto word : word_list) {
            std::string temp = input;
            int flag = 0;
            int points = 0;

            for (auto letter : word) {

                std::size_t pos = temp.find(letter);

                if (pos != std::string::npos) {
                    temp.erase(pos, 1);
                    points += values[letter - 'a'];
                } else if (++flag > blanks) {
                    break;
                }
            }

            if (flag <= blanks) {
                results.push_back({word, points});
            }
        }

        if (scrabble_mode) {
            compare_points c;
            std::sort(results.begin(), results.end(), c);
        } else {
            compare_length c;
            std::sort(results.begin(), results.end(), c);
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        for (auto result : results) {
            std::cout << result.string << " " << result.points << '\n';
        }

        std::cout << "Found " << results.size() << " results in "
                  << duration.count() << " milliseconds" << "\n\n";
    }
}
