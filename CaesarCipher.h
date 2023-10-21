
#ifndef CAESARCIPHER_CAESARCIPHER_H
#define CAESARCIPHER_CAESARCIPHER_H


#include <string>

#include <vector>

class CaesarCipher {
    std::vector<std::string>validWordsVector;
    std::vector<std::string>WordsVector;
public:
    std::string encrypt(std::string message, int shift);
    std::string decrypt(std::string cipher, int shift);
    std::string decryptAll(std::string cipher);
    int validWordsCounter(std::string message);
    int wordCounter(std::string message);
    std::string convertToLower(std::string message);
    void encryptFile(std::string inputFile,std::string outputFile, int shift);
    void decryptFile(std::string inputFile,std::string outputFile, int shift);
};




#endif //CAESARCIPHER_CAESARCIPHER_H
