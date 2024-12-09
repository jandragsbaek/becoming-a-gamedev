typedef long int int32;
typedef unsigned long int uint32;
typedef long long int int64;
typedef unsigned long long int uint64;

#include <fstream>
#include <string>
#include <vector>

std::vector<std::string> loadInput(std::string input_file) {
  std::vector<std::string> lines;

  std::ifstream fs;

  fs.open(input_file);

  if (fs.is_open()) {
    while (fs) {
      std::string str;
      std::getline(fs, str);
      if (str.size() > 0) {
        lines.push_back(str);
      }
    }
  }

  return lines;
}

std::vector<std::string> SplitByDelimiter(const std::string& Str, const std::string& Delimiter)
{
    size_t PosStart = 0;
    size_t PosEnd;
    const size_t DelimLen = Delimiter.length();

    std::string Token;
    std::vector<std::string> Res;

    while ((PosEnd = Str.find(Delimiter, PosStart)) != std::string::npos) {
        Token = Str.substr(PosStart, PosEnd - PosStart);
        PosStart = PosEnd + DelimLen;
        Res.push_back(Token);
    }

    Res.push_back(Str.substr(PosStart));
    return Res;
}