#include "util.cpp"
#include <cstdlib>
#include <iostream>


bool isLineSafe(std::string line){
  
  // The levels are either all increasing or all decreasing.
  // Any two adjacent levels differ by at least one and at most three.
  
  bool allDecreasing = true;
  bool allIncreasing = true;

  bool validDiff = true;

  std::vector<std::string> levels = SplitByDelimiter(line, " ");
  
  int64 prev = atoi(levels[0].c_str());

  for(int i=1;i<levels.size();i++){
    int64 num = atoi(levels[i].c_str());

    if(num >= prev){
      allDecreasing = false;
    }

    if(num <= prev){
      allIncreasing = false;
    }

    if(prev == num){
      validDiff = false;
    }

    if(abs(prev-num) > 3){
      validDiff = false;
    }
    
    prev = num;
  }
  
  return validDiff && (allIncreasing || allDecreasing);
}

void part_one(std::vector<std::string> lines) {
  int64 sum = 0;

  for(std::string line : lines){
    if(isLineSafe(line)){
      sum++;
    }
  }

  std::cout << "Part 1: " << sum << std::endl;
}

void part_two(std::vector<std::string> lines) {
  int64 sum = 0;

  for(std::string line : lines){
    if(isLineSafe(line)){
      sum++;
    } else {
      // attempt checks by removing a single node
      std::vector<std::string> baseArray = SplitByDelimiter(line, " "); 

      for(int i=0;i<baseArray.size();i++){
        std::vector<std::string> copyArray = baseArray;
        copyArray.erase(copyArray.begin() + i);
        if(isLineSafe(StringJoin(copyArray, " "))){
          sum++;
          break;
        }
      }
    }
  }

  std::cout << "Part 2: " << sum << std::endl;
}

int main() {
  std::vector<std::string> lines = loadInput("input.txt");

  part_one(lines);
  part_two(lines);

  return 0;
}