#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <queue>
#include <memory>
#include <algorithm>
#include <iostream>

struct HuffmanNode {
    char character;
    int frequency;
    std::shared_ptr<HuffmanNode> left;
    std::shared_ptr<HuffmanNode> right;
    
    HuffmanNode(char c, int freq) : character(c), frequency(freq), left(nullptr), right(nullptr) {}
    HuffmanNode(int freq, std::shared_ptr<HuffmanNode> l, std::shared_ptr<HuffmanNode> r) 
        : character('\0'), frequency(freq), left(l), right(r) {}
};

struct CompareNodes {
    bool operator()(const std::shared_ptr<HuffmanNode>& a, const std::shared_ptr<HuffmanNode>& b) {
        return a->frequency > b->frequency;
    }
};

class HuffmanCoding {
private:
    std::shared_ptr<HuffmanNode> root;
    std::unordered_map<char, std::string> encodingTable;
    std::unordered_map<char, int> frequencyTable;
    
    void buildFrequencyTable(const std::string& text) {
        frequencyTable.clear();
        for (char c : text) {
            if (c != '\n' && c != '\r') { // Skip newlines
                frequencyTable[c]++;
            }
        }
    }
    
    void buildHuffmanTree() {
        if (frequencyTable.empty()) {
            return;
        }
        
        std::priority_queue<std::shared_ptr<HuffmanNode>, std::vector<std::shared_ptr<HuffmanNode>>, CompareNodes> minHeap;
        
        // Create leaf nodes for each character
        for (const auto& pair : frequencyTable) {
            minHeap.push(std::make_shared<HuffmanNode>(pair.first, pair.second));
        }
        
        // Build the tree
        while (minHeap.size() > 1) {
            auto left = minHeap.top();
            minHeap.pop();
            
            auto right = minHeap.top();
            minHeap.pop();
            
            auto merged = std::make_shared<HuffmanNode>(left->frequency + right->frequency, left, right);
            minHeap.push(merged);
        }
        
        root = minHeap.top();
        minHeap.pop();
    }
    
    void buildEncodingTable(std::shared_ptr<HuffmanNode> node, const std::string& code) {
        if (!node) return;
        
        if (!node->left && !node->right) {
            // Leaf node
            if (!code.empty()) {
                encodingTable[node->character] = code;
            } else {
                // Special case: only one character in the text
                encodingTable[node->character] = "0";
            }
            return;
        }
        
        buildEncodingTable(node->left, code + "0");
        buildEncodingTable(node->right, code + "1");
    }
    
    void cleanup() {
        root.reset();
        encodingTable.clear();
        frequencyTable.clear();
    }
    
public:
    HuffmanCoding() : root(nullptr) {}
    
    ~HuffmanCoding() {
        cleanup();
    }
    
    void buildFromText(const std::string& text) {
        cleanup();
        buildFrequencyTable(text);
        buildHuffmanTree();
        buildEncodingTable(root, "");
    }
    
    std::string encode(const std::string& text) {
        std::string encoded;
        for (char c : text) {
            if (c != '\n' && c != '\r') { // Skip newlines
                if (encodingTable.find(c) != encodingTable.end()) {
                    encoded += encodingTable[c];
                }
            }
        }
        return encoded;
    }
    
    double getAverageEncodingLength() {
        if (frequencyTable.empty()) return 0.0;
        
        int totalChars = 0;
        double weightedSum = 0.0;
        
        for (const auto& pair : frequencyTable) {
            totalChars += pair.second;
        }
        
        for (const auto& pair : frequencyTable) {
            double probability = static_cast<double>(pair.second) / totalChars;
            int codeLength = encodingTable[pair.first].length();
            weightedSum += probability * codeLength;
        }
        
        return weightedSum;
    }
    
    int getCompressedSize(const std::string& text) {
        std::string encoded = encode(text);
        return encoded.length();
    }
    
    bool isSuspicious(const std::string& mcode, double threshold) {
        int mcodeLength = getCompressedSize(mcode);
        double averageLength = getAverageEncodingLength();
        
        // If mcode encoding length is higher than the average, it's considered suspicious
        return mcodeLength > threshold * averageLength;
    }
};
