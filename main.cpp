#include <iostream>
#include <fstream>
#include <string>

std::string readFile(const std::string& filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "File could not be opened.\n";
    }
    std::string content;
    std::getline(file, content);

    return content;
}

int main()
{
    std::string filePath = "../txts/mcode1.txt";
    std::string content = readFile(filePath);
    std::cout << "File content: " << content << std::endl;
    return 0;
}