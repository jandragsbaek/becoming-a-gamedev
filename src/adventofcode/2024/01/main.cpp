#include "util.cpp"
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <map>


void part_one(std::vector<std::string> lines) {
  int64 sum = 0;

  std::vector<int64> FirstList;
  std::vector<int64> SecondList;
  
  for(std::string line : lines){
    auto parts = SplitByDelimiter(line, "   ");
    FirstList.push_back(atoi(parts[0].c_str()));
    SecondList.push_back(atoi(parts[1].c_str()));
  }

  std::sort(std::begin(FirstList), std::end(FirstList));
  std::sort(std::begin(SecondList), std::end(SecondList));

  for(int i=0;i<FirstList.size();i++){
    // printf("first: %lli -- second: %lli -- diff: %lli\n", FirstList[i], SecondList[i], abs(FirstList[i] - SecondList[i]));
    sum += abs(FirstList[i] - SecondList[i]);
  }

  std::cout << "Part 1: " << sum << std::endl;
}

void part_two(std::vector<std::string> lines) {
  int64 sum = 0;

  std::vector<int64> FirstList;
  std::map<int64, int64> Second{};
  
  for(std::string line : lines){
    auto parts = SplitByDelimiter(line, "   ");
    FirstList.push_back(atoi(parts[0].c_str()));

    int64 num = atoi(parts[1].c_str());
    int64 value = Second[num];
    // printf("Got %lli, inserting %lli\n", value, value+1);
    Second[num] = value+1;
  }

  for(int64 value : FirstList){
    int64 similarityScore = value * Second[value];
    // printf("Number %lli appears %lli times, SimScore: %lli\n", value, Second[value], similarityScore);
    sum += similarityScore;
  }

  std::cout << "Part 2: " << sum << std::endl;
}

int main() {
  std::vector<std::string> lines = loadInput("input.txt");

  part_one(lines);
  part_two(lines);

  return 0;
}