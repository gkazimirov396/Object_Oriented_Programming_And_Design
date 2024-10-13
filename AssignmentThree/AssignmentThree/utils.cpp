#include <string>
#include <sstream>
#include <functional> 

static std::string generateID(int coords, const std::string& color, int extra) {
    std::hash<std::string> hashFunction;

    std::stringstream ss;
    ss << coords << color << extra;

    return std::to_string(hashFunction(ss.str()));
}