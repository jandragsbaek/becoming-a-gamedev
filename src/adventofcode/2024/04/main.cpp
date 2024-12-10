#include "util.cpp"
#include <iostream>

void part_one(std::vector<std::string> lines) {
  int64 sum = 0;

  const int height = lines.size();
  const int width = lines[0].length();

  std::vector<std::vector<char>> arr;

  for(std::string line : lines){
    std::vector<char> tmp;
    for(char c : line){
      tmp.push_back(c);
    }
    arr.push_back(tmp);
  }

  for(int y=0;y<arr.size();y++){
    
    for(int x=0;x<arr[0].size();x++){

      if(arr[y][x] == 'X'){

        // up
        if(y >= 3 && arr[y-1][x] == 'M' && arr[y-2][x] == 'A' && arr[y-3][x] == 'S'){
          sum++;
        }

        // up-left
        if(y >= 3 && x >= 3 && arr[y-1][x-1] == 'M' && arr[y-2][x-2] == 'A' && arr[y-3][x-3] == 'S'){
          sum++;
        }

        // up-right
        if(y >= 3 && x <= width-3 && arr[y-1][x+1] == 'M' && arr[y-2][x+2] == 'A' && arr[y-3][x+3] == 'S'){
          sum++;
        }      

        // down
        if(y < height-3 && arr[y+1][x] == 'M' && arr[y+2][x] == 'A' && arr[y+3][x] == 'S'){
          sum++;
        }

        // down-left
        if(y < height-3 && x >= 3 && arr[y+1][x-1] == 'M' && arr[y+2][x-2] == 'A' && arr[y+3][x-3] == 'S'){
          sum++;
        }

        // down-right
        if(y < height-3 && x < width-3 && arr[y+1][x+1] == 'M' && arr[y+2][x+2] == 'A' && arr[y+3][x+3] == 'S'){
          sum++;
        } 

        // left
        if(x >= 3 && arr[y][x-1] == 'M' && arr[y][x-2] == 'A' && arr[y][x-3] == 'S'){
          sum++;
        }

        // right
        if(x < width-3 && arr[y][x+1] == 'M' && arr[y][x+2] == 'A' && arr[y][x+3] == 'S'){
          sum++;
        } 
      }
    }
  }

  printf("Part 1: %lli\n",sum);
}

void part_two(std::vector<std::string> lines) {
  int64 sum = 0;

  std::vector<std::vector<char>> arr;

  for(std::string line : lines){
    std::vector<char> tmp;
    for(char c : line){
      tmp.push_back(c);
    }
    arr.push_back(tmp);
  }

  for(int y=1;y<arr.size()-1;y++){
    
    for(int x=1;x<arr[0].size()-1;x++){

      if(arr[y][x] == 'A'){

        // M S
        //  A
        // M S
        if(arr[y-1][x-1] == 'M' && arr[y+1][x+1] == 'S' && arr[y-1][x+1] == 'M' && arr[y+1][x-1] == 'S'){
          sum++;
        }

        // M M 
        //  A
        // S S
        if(arr[y-1][x-1] == 'M' && arr[y+1][x+1] == 'S' && arr[y+1][x-1] == 'M' && arr[y-1][x+1] == 'S'){
          sum++;
        }

        // S S
        //  A
        // M M

        if(arr[y+1][x-1] == 'M' && arr[y-1][x+1] == 'S' && arr[y+1][x+1] == 'M' && arr[y-1][x-1] == 'S'){
          sum++;
        }

        // S M
        //  A
        // S M

        if(arr[y+1][x-1] == 'S' && arr[y-1][x+1] == 'M' && arr[y+1][x+1] == 'M' && arr[y-1][x-1] == 'S'){
          sum++;
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