#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <queue>
#include <memory>

struct HuffmanNode {
    char character;
    int frequency;
    std::shared_ptr<HuffmanNode> left;
    std::shared_ptr<HuffmanNode> right;
    
    HuffmanNode(char c, int freq) : character(c), frequency(freq), left(nullptr), right(nullptr) {}
    HuffmanNode(int freq, std::shared_ptr<HuffmanNode> l, std::shared_ptr<HuffmanNode> r) 
        : character('\0'), frequency(freq), left(l), right(r) {}
};

class HuffmanCoding {
private:
    std::shared_ptr<HuffmanNode> root;
    std::unordered_map<char, std::string> encodingTable;
    std::unordered_map<char, int> frequencyTable;
    
    void buildFrequencyTable(const std::string& text);
    void buildHuffmanTree();
    void buildEncodingTable(std::shared_ptr<HuffmanNode> node, const std::string& code);
    void cleanup();
    
public:
    HuffmanCoding();
    ~HuffmanCoding();
    
    void buildFromText(const std::string& text);
    std::string encode(const std::string& text);
    double getAverageEncodingLength();
    int getCompressedSize(const std::string& text);
    bool isSuspicious(const std::string& mcode, double threshold);
};
