#include "util.cpp"
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <ctype.h>

void part_one(std::vector<std::string> lines) {
  int64 sum = 0;

  for(std::string line : lines){

    int pos = 0;

    // forward scan for the mul(x,y)
    while(pos < line.length()){

      char currentCharacter = line.at(pos);
    
      if(currentCharacter == 'm'){
        pos++;
        currentCharacter = line.at(pos);

        if(currentCharacter == 'u'){
          pos++;
          currentCharacter = line.at(pos);

          if(currentCharacter == 'l'){
            pos++;
            currentCharacter = line.at(pos);

            if(currentCharacter == '('){
              pos++;
              currentCharacter = line.at(pos);

              std::string firstNum{};

              while(true){
                if(std::isdigit(currentCharacter)){
                  // construct a number
                  firstNum += currentCharacter;
                  pos++;
                  currentCharacter = line.at(pos);
                } else {
                  break;
                }
              }

              if(currentCharacter == ',' && firstNum.length() > 0){
                pos++;
                currentCharacter = line.at(pos);

                std::string secondNum{};
                while(true){
                  if(std::isdigit(currentCharacter)){
                    // construct a number
                    secondNum += currentCharacter;
                    pos++;
                    currentCharacter = line.at(pos);
                  } else {
                    break;
                  }
                }

                if(currentCharacter == ')' && secondNum.length() > 0){
                  // successfully built mul(x,y)

                  sum += atoi(firstNum.c_str()) * atoi(secondNum.c_str());
                }
              }
            }
          }
        }
      }

      pos++;
    }

  }

  std::cout << "Part 1: " << sum << std::endl;
}

void part_two(std::vector<std::string> lines) {
  int64 sum = 0;

  int doProcess = true;

  for(std::string line : lines){
    int pos = 0;

    while(pos < line.length()){

      char currentCharacter = line.at(pos);
    
      if(currentCharacter == 'd'){
        pos++;
        currentCharacter = line.at(pos);

        if(currentCharacter == 'o'){
          pos++;
          currentCharacter = line.at(pos);

          if(currentCharacter == '('){
            pos++;
            currentCharacter = line.at(pos);

            if(currentCharacter == ')'){
              //printf("do()\n");
              doProcess = true;
              pos++;
              continue;
            }
          }

          if(currentCharacter == 'n'){
            pos++;
            currentCharacter = line.at(pos);

            if(currentCharacter == '\''){
              pos++;
              currentCharacter = line.at(pos);

              if(currentCharacter == 't'){
                pos++;
                currentCharacter = line.at(pos);
                
                if(currentCharacter == '('){
                  pos++;
                  currentCharacter = line.at(pos);

                  if(currentCharacter == ')'){
                    //printf("don't()\n");
                    doProcess = false;
                  }
                }
              }
            }
          }
        }
      }




      
      if(currentCharacter == 'm' && doProcess){
        pos++;
        currentCharacter = line.at(pos);

        if(currentCharacter == 'u'){
          pos++;
          currentCharacter = line.at(pos);

          if(currentCharacter == 'l'){
            pos++;
            currentCharacter = line.at(pos);

            if(currentCharacter == '('){
              pos++;
              currentCharacter = line.at(pos);

              std::string firstNum{};

              while(true){
                if(std::isdigit(currentCharacter)){
                  // construct a number
                  firstNum += currentCharacter;
                  pos++;
                  currentCharacter = line.at(pos);
                } else {
                  break;
                }
              }

              if(currentCharacter == ',' && firstNum.length() > 0){
                pos++;
                currentCharacter = line.at(pos);

                std::string secondNum{};
                while(true){
                  if(std::isdigit(currentCharacter)){
                    // construct a number
                    secondNum += currentCharacter;
                    pos++;
                    currentCharacter = line.at(pos);
                  } else {
                    break;
                  }
                }

                if(currentCharacter == ')' && secondNum.length() > 0){
                  // successfully built mul(x,y)
                  //printf("mul(%i,%i)\n", atoi(firstNum.c_str()), atoi(secondNum.c_str()));

                  sum += atoi(firstNum.c_str()) * atoi(secondNum.c_str());

                }
              }
            }
          }
        }
      }

      pos++;
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