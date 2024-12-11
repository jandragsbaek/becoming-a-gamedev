#include "util.cpp"
#include <map>

struct Restrictions {
  std::vector<std::string> NotAllowedBefore;
  std::vector<std::string> NotAllowedAfter;
};


// void printRules(std::map<std::string, Restrictions> rules){

//   for (auto it = rules.begin(); it != rules.end(); ++it){
//     printf("Rules for number: %s\n", it->first.c_str());

//     printf("Invalid before!\n");
//     for(std::string foo : it->second.NotAllowedBefore){
//       printf("%s\n", foo.c_str());
//     }
    
//   }
// }

std::map<std::string, Restrictions> rules;
int splitCount = 0;

void part_one(std::vector<std::string> lines) {
  int64 sum = 0;

  


  for(int i=0;i<lines.size();i++){
    if(lines[i].empty()){
      splitCount = i;
      break;
    }

    std::vector<std::string> parts = SplitByDelimiter(lines[i], "|");

    // for the first number, the second number must come after - and the reverse is also true. Thus, we'll do lookups for rule breaks and return on those.

    Restrictions currentRestrictions;

    if(rules.find(parts[0]) != rules.end()){
      currentRestrictions = rules.at(parts[0]);
    } else {
      currentRestrictions = Restrictions{{}, {}};
    }
    currentRestrictions.NotAllowedBefore.push_back(parts[1]);
    rules[parts[0]] = currentRestrictions;


    // the reverse
    if(rules.find(parts[1]) != rules.end()){
      currentRestrictions = rules.at(parts[1]);
    } else {
      currentRestrictions = Restrictions{{}, {}};
    }
    currentRestrictions.NotAllowedAfter.push_back(parts[0]);
    rules[parts[1]] = currentRestrictions;

  }

  for(int i = splitCount + 1; i<lines.size()-1; i++){
    bool valid = true;


    //printf("%s\n", lines[i].c_str());
  
    std::vector<std::string> split = SplitByDelimiter(lines[i], ",");

    for(int j=0;j<split.size();j++){
      std::string number = split[j];

      Restrictions currentRules = rules.at(number);

      // check all numbers before this one
      if(j > 0){
        for(int k=0;k<j;k++){
          for(std::string check : currentRules.NotAllowedBefore){
            if(check == split[k]){
              //printf("Found violation. %s is before %s and is not allowed!\n", split[k].c_str(), split[j].c_str());
              valid = false;
            }
          }
          if(!valid){
            break;
          }
        }
      }

      if(j+1 < split.size()){
        for(int k=j+1;k<split.size();k++){
          for(std::string check : currentRules.NotAllowedAfter){
            if(check == split[k]){
              //printf("Found violation. %s is after %s and is not allowed!\n", split[k].c_str(), split[j].c_str());
              valid = false;
            }
          }
          if(!valid){
            break;
          }
        }
      }

      if(!valid){
        break;
      }
    }
  

    if(valid){
      //printf("line is valid\n");
      int middlePosition = split.size()/2;
      //printf("Item in the middle is: %s\n", split[middlePosition].c_str());

      sum += atoi(split[middlePosition].c_str());

    }

  }

  printf("Part 1: %lli\n", sum);
}

bool isValidLine(std::string line){
  std::vector<std::string> split = SplitByDelimiter(line, ",");

  for(int j=0;j<split.size();j++){
    std::string number = split[j];

    Restrictions currentRules = rules.at(number);

    // check all numbers before this one
    if(j > 0){
      for(int k=0;k<j;k++){
        for(std::string check : currentRules.NotAllowedBefore){
          if(check == split[k]){
            return false;
          }
        }
      }
    }

    if(j+1 < split.size()){
      for(int k=j+1;k<split.size();k++){
        for(std::string check : currentRules.NotAllowedAfter){
          if(check == split[k]){
            return false;
          }
        }
      }
    }
  }

  return true;
}

void part_two(std::vector<std::string> lines) {
  int64 sum = 0;

  for(int i = splitCount + 1; i<lines.size()-1; i++){

    if(!isValidLine(lines[i])){
      //printf("%s\n", lines[i].c_str());
    

      std::string currentLine = lines[i];

      while(!isValidLine(currentLine)){
        std::vector<std::string> split = SplitByDelimiter(currentLine, ",");

        bool swapped = false;

        for(int j=0;j<split.size();j++){
          std::string number = split[j];

          Restrictions currentRules = rules.at(number);

          // check all numbers before this one
          if(j > 0){
            for(int k=0;k<j;k++){
              for(std::string check : currentRules.NotAllowedBefore){
                if(check == split[k]){

                  std::string tmp = split[k];
                  split[k] = split[j];
                  split[j] = tmp;

                  // printf("-> %s\n", StringJoin(split, ",").c_str());
                  swapped = true;
                  break;
                }
              }
              if(swapped){ break; }
            }
          }

          if(j+1 < split.size() && !swapped){
            for(int k=j+1;k<split.size();k++){
              for(std::string check : currentRules.NotAllowedAfter){
                if(check == split[k]){
                  std::string tmp = split[k];
                  split[k] = split[j];
                  split[j] = tmp;

                  // printf("-> %s\n", StringJoin(split, ",").c_str());
                  swapped = true;
                  break;
                }
              }
              if(swapped){ break; }
            }
          }
        }

        currentLine = StringJoin(split, ",");
      }
    
      std::vector<std::string> split = SplitByDelimiter(currentLine, ",");
      int middlePosition = split.size()/2;
      sum += atoi(split[middlePosition].c_str());
    
    }
  }

  printf("Part 2: %lli\n", sum);
}

int main() {
  std::vector<std::string> lines = loadInput("input.txt");

  part_one(lines);
  part_two(lines);

  return 0;
}