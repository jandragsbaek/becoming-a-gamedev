#include "util.cpp"
#include <cstdio>
#include <map>
#include <iostream>

std::pair<int, int> guardPosition;
std::pair<int, int> guardDirection;

std::pair<int, int> StartingGuardPosition;
std::pair<int, int> StartingGuardDirection;

std::map<std::string, int> seenPositions;

std::string GetPositionAsString(int x, int y){
    // i kinda do know that I _should_ use a library like fmt for this, but let's hack it and make it work.
  char buffer[100];
  sprintf(buffer, "%i,%i", x, y);
  return buffer;
}

std::string GetPositionAsString(){
  return GetPositionAsString(guardPosition.first, guardPosition.second);
}

void RotateGuardRight(){

  // facing up
  if(guardDirection.first == 0 && guardDirection.second == -1){
    guardDirection = { 1, 0 };
    return;
  }

  // facing right
  if(guardDirection.first == 1 && guardDirection.second == 0){
    guardDirection = { 0, 1};
    return;
  }

  // facing down
  if(guardDirection.first == 0 && guardDirection.second == 1){
    guardDirection = { -1, 0 };
    return;
  }

  // facing left
  if(guardDirection.first == -1 && guardDirection.second == 0){
    guardDirection = {0, -1};
    return;
  }
}

void SavePosition(){
  seenPositions[GetPositionAsString()] = 1;
}

std::vector<std::vector<char>> map;

void part_one(std::vector<std::string> lines) {
  // x, y
  

  // represented as a vector in x,y - starting with going upwards
  guardDirection = { 0, -1 };
  
  for(int y=0;y<lines.size();y++){
    std::vector<char> tmp;
    for(int x=0;x<lines[0].size();x++){
      tmp.push_back(lines[y][x]);
      if(lines[y][x] == '^'){
        guardPosition = {x, y};
      }
    }
    map.push_back(tmp);
  }

  // ready for part 2
  StartingGuardPosition = guardPosition;
  StartingGuardDirection = guardDirection;

  
  SavePosition();
  //printf("Guard Starts as x: %i && y: %i\n", guardPosition.first, guardPosition.second);

  // loop until guard will be out of bounds
  while(true){
    // start with updating guard position
    guardPosition = { guardPosition.first + guardDirection.first, guardPosition.second + guardDirection.second };

    // then out of bounds check on X axis
    if(guardPosition.first < 0 || guardPosition.first == map[0].size()){
      //printf("Out Of Bounds at X: %i && Y: %i\n", guardPosition.first, guardPosition.second);
      break;
    }

    // then out of bounds check on Y axis
    if(guardPosition.second < 0 || guardPosition.second == map.size()){
      //printf("Out Of Bounds at X: %i && Y: %i\n", guardPosition.first, guardPosition.second);
      break;
    }

    // if not out of bounds, check whether new position is an object
    if(map[guardPosition.second][guardPosition.first] == '#'){
      // move back and rotate direction vector 90 degrees to the right
      guardPosition = { guardPosition.first - guardDirection.first, guardPosition.second - guardDirection.second };
      RotateGuardRight();
      //printf("Found Obstacle at X: %i && Y: %i, turning right\n", guardPosition.first, guardPosition.second);
    } else {
      SavePosition();
    }
  }

  std::cout << "Part 1: " << seenPositions.size() << std::endl;
}

// basically just a c/p from part 1, with a few mods
bool IsLooping(int x, int y){

  std::map<std::string, int> positionCounter;


  while(true){
    // start with updating guard position
    guardPosition = { guardPosition.first + guardDirection.first, guardPosition.second + guardDirection.second };

    // out of bounds, means guard is _not_ looping
    if(guardPosition.first < 0 || guardPosition.first == map[0].size()){
      //printf("Out Of Bounds at X: %i && Y: %i\n", guardPosition.first, guardPosition.second);
      return false;
    }

    // out of bounds, means guard is _not_ looping
    if(guardPosition.second < 0 || guardPosition.second == map.size()){
      //printf("Out Of Bounds at X: %i && Y: %i\n", guardPosition.first, guardPosition.second);
      return false;
    }

    // if not out of bounds, check whether new position is an object
    if(map[guardPosition.second][guardPosition.first] == '#' || (guardPosition.first == x && guardPosition.second == y)){
      // move back and rotate direction vector 90 degrees to the right
      guardPosition = { guardPosition.first - guardDirection.first, guardPosition.second - guardDirection.second };
      RotateGuardRight();
      //printf("Found Obstacle at X: %i && Y: %i, turning right\n", guardPosition.first, guardPosition.second);
    } else {
      positionCounter[GetPositionAsString()]++;

      // if we see the same position more than 5 times, surely it is a loop!
      if(positionCounter[GetPositionAsString()] > 5){
        return true;
      }
    }
  }


}

void part_two(std::vector<std::string> lines) {
  int64 sum = 0;

  guardPosition = StartingGuardPosition;
  guardDirection = StartingGuardDirection;
  
  for(int y=0;y<lines.size();y++){
    for(int x=0;x<lines[0].size();x++){
      guardPosition = StartingGuardPosition;
      guardDirection = StartingGuardDirection;

      if(IsLooping(x, y)){
        sum++;
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