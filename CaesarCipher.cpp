#include "CaesarCipher.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <QMessageBox>

std::string roundToTwoDecimalPlaces(double number) {
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(2) << number;
    return stream.str();
}

std::string CaesarCipher::encrypt(std::string message, int shift) {
    std::string result = "";
    for (char c : message) {
        if (std::isalpha(c)) {
            char base = std::isupper(c) ? 'A' : 'a';
            char encrypted = (c - base + shift) % 26 + base;
            result += encrypted;
        } else {
            result += c;
        }
    }
    return result;
}

std::string CaesarCipher::decrypt(std::string cipher, int shift) {
    std::string result = "";
    for (char c : cipher) {
        if (std::isalpha(c)) {
            char base = std::isupper(c) ? 'A' : 'a';
            char decrypted = (c - base - shift + 26) % 26 + base;
            result += decrypted;
        } else {
            result += c;
        }
    }
    return result;
}

std::string CaesarCipher::decryptAll(std::string cipher) {
    std::string result;
    std::string text;

    for (int shift = 0; shift < 26; shift++) {
        std::string decryptedText;
        text = "\nShift " + std::to_string(shift) + ":\n";
        for (char c : cipher) {
            if (std::isalpha(c)) {
                char base = std::isupper(c) ? 'A' : 'a';
                char decrypted = (c - base - shift + 26) % 26 + base;
                decryptedText += decrypted;
            } else {
                decryptedText += c;
            }
        }

        double validWords = static_cast<double>(CaesarCipher::validWordsCounter(CaesarCipher::convertToLower(decryptedText)));
        int wordCount = CaesarCipher::wordCounter(decryptedText);
        double probability = std::round(((validWords/wordCount)*100)*100) / 100;
        text += decryptedText;
        text += "\n||| Accuracy: " + roundToTwoDecimalPlaces(probability) + "%\n\n";
        result += text;
    }

    return result;
}



int CaesarCipher::validWordsCounter(std::string message) {
    std::ifstream file("words_alpha.txt");
    if (!file.is_open()) {
        std::cout << "!!! Error !!! Couldn't open the file... " << std::endl;
        QMessageBox::critical(nullptr, "Error", "Unable to open the file!");
        return 0;
    }

    std::string word;
    std::string wordToFind;
    int validWords = 0;
    CaesarCipher::validWordsVector.clear();

    for (int i = 0; i < message.length(); ++i) {
        if (message[i] == ' ' || !std::isalpha(message[i])) {
            while (std::getline(file, word)) {
                if (wordToFind == word) {
                    CaesarCipher::validWordsVector.push_back(wordToFind);
                    validWords += 1;
                    break;
                }
            }
            file.clear();
            file.seekg(0);
            wordToFind = "";
        } else {
            wordToFind += message[i];

            if (i == message.length()-1) {
                while (std::getline(file, word)) {
                    if (wordToFind == word) {
                        CaesarCipher::validWordsVector.push_back(wordToFind);
                        validWords += 1;
                        break;
                    }
                }
                file.clear();
                file.seekg(0);
                wordToFind = "";
            }
        }
    }

    file.close();

    return validWords;
}


int CaesarCipher::wordCounter(std::string message) {
    int wordCount = 0;

    for (int i = 0; i < message.length(); ++i) {
        if (message[i] == ' ' || !std::isalpha(message[i])) {
            wordCount++;

        }
    }
    return wordCount;
}

std::string CaesarCipher::convertToLower(std::string message) {
    std::string result ="";
    for (char c : message)
    {
        if (std::isalpha(c) && (c <= 90 && c >= 65))
        {
            c += 32;
        }
            result += c;
    }
    return result;
}

void CaesarCipher::encryptFile(std::string inputFile,std::string outputFile, int shift) {
    inputFile += ".txt";
    outputFile += ".txt";

    std::ifstream inFile(inputFile);


    std::ofstream outFile(outputFile);


    if (!inFile.is_open()) {
        std::cout << "Failed to open input file: \n" << inputFile << std::endl;
        QMessageBox::critical(nullptr, "Error", "Unable to open the file!");
        return;
    }

    if (!outFile.is_open()) {
        std::cout << "Failed to open output file: \n" << outputFile << std::endl;
        QMessageBox::critical(nullptr, "Error", "Unable to open the file!");
        inFile.close();
        return;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        std::string encrypted = encrypt(line, shift);
        outFile << encrypted << std::endl;
    }
    std::string message = "Your file has been saved as:\n\"" + outputFile + "\"";
    std::cout << "File encrypted successfully. \nEncrypted content saved to: " << outputFile << std::endl;
    QMessageBox::information(nullptr, "Done!", message.c_str());
    inFile.close();
    outFile.close();
}


void CaesarCipher::decryptFile(std::string inputFile,std::string outputFile, int shift) {
    inputFile += ".txt";
    outputFile += ".txt";

    std::ifstream inFile(inputFile);


    std::ofstream outFile(outputFile);


    if (!inFile.is_open()) {
        std::cout << "Failed to open input file: \n" << inputFile << std::endl;
        QMessageBox::critical(nullptr, "Error", "Unable to open the file!");
        return;
        return;
    }

    if (!outFile.is_open()) {
        std::cout << "Failed to open output file: \n" << outputFile << std::endl;
        QMessageBox::critical(nullptr, "Error", "Unable to open the file!");
        inFile.close();
        return;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        std::string decrypted = decrypt(line, shift);
        outFile << decrypted << std::endl;
    }

    std::string message = "Your file has been saved as:\n\"" + outputFile + "\"";
    std::cout << "File encrypted successfully. \nEncrypted content saved to: " << outputFile << std::endl;
    QMessageBox::information(nullptr, "Done!", message.c_str());

    inFile.close();
    outFile.close();
}




