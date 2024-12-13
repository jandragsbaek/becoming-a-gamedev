#include "util.cpp"
#include <print>

bool traverseAndCheck(std::vector<int64> numbers, int64 goal, int64 currentNumber, int64 position){

  // overshot, therefore fail
  if(currentNumber > goal){ return false; }

  // if we matched the number, return true
  if(currentNumber == goal){ return true; }

  // no more numbers left, thus failed
  if(position == numbers.size() - 1){ return false; }

  // otherwise, test both cases
  bool plus = traverseAndCheck(numbers, goal, currentNumber+numbers[position+1], position+1);
  bool multiply = traverseAndCheck(numbers, goal, currentNumber*numbers[position+1], position+1);
  
  return plus || multiply;
}

void part_one(std::vector<std::string> lines) {
  int64 sum = 0;

  for(std::string line : lines){

    std::vector<std::string> spl = SplitByDelimiter(line, ": ");

    int64 finalSum = _atoi64(spl[0].c_str());
    std::vector<int64> numbers;

    for(std::string tmpNum : SplitByDelimiter(spl[1], " ")){
      numbers.push_back(_atoi64(tmpNum.c_str()));
    }
    
    bool foundSolution = traverseAndCheck(numbers, finalSum, numbers[0], 0);
    //std::println("{} -- {}", finalSum, foundSolution ? "true" : "false");

    if(foundSolution) { sum += finalSum; }

    //std::println("{}", numbers.size());
  }

  std::println("Part 1: {}", sum);
}


bool traverseAndCheckWithThirdOperator(std::vector<int64> numbers, int64 goal, int64 currentNumber, int64 position){

  // overshot, therefore fail
  if(currentNumber > goal){ return false; }

  // if we matched the number, return true
  if(currentNumber == goal){ return true; }

  // no more numbers left, thus failed
  if(position == numbers.size() - 1){ return false; }

  // otherwise, test both cases
  bool plus = traverseAndCheckWithThirdOperator(numbers, goal, currentNumber+numbers[position+1], position+1);
  bool multiply = traverseAndCheckWithThirdOperator(numbers, goal, currentNumber*numbers[position+1], position+1);
  
  // add in third case
  int64 concatted = _atoi64(std::format("{}{}", currentNumber, numbers[position+1]).c_str());
  bool concat = traverseAndCheckWithThirdOperator(numbers, goal, concatted, position+1);

  return plus || multiply || concat;
}

void part_two(std::vector<std::string> lines) {
  int64 sum = 0;

  for(std::string line : lines){

    std::vector<std::string> spl = SplitByDelimiter(line, ": ");

    int64 finalSum = _atoi64(spl[0].c_str());
    std::vector<int64> numbers;

    for(std::string tmpNum : SplitByDelimiter(spl[1], " ")){
      numbers.push_back(_atoi64(tmpNum.c_str()));
    }
    
    bool foundSolution = traverseAndCheckWithThirdOperator(numbers, finalSum, numbers[0], 0);
    //std::println("{} -- {}", finalSum, foundSolution ? "true" : "false");

    if(foundSolution) { sum += finalSum; }

    //std::println("{}", numbers.size());
  }


  std::println("Part 2: {}", sum);
}

int main() {
  std::vector<std::string> lines = loadInput("input.txt");

  part_one(lines);
  part_two(lines);

  return 0;
}