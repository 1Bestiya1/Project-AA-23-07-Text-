#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <fstream>
#include <chrono>
using namespace std;

//Простейший пример блочного шифрования(его удаляем):
const int BLOCK_SIZE = 5; // Определим размер блока. Каждый в своем методе сам прописывает input для количества блоков

map<char, string> MorseCode() {
    return {
        {'A', ".-"}, {'B', "-..."}, {'C', "-.-."}, {'D', "-.."}, {'E', "."},
        {'F', "..-."}, {'G', "--."}, {'H', "...."}, {'I', ".."}, {'J', ".---"},
        {'K', "-.-"}, {'L', ".-.."}, {'M', "--"}, {'N', "-."}, {'O', "---"},
        {'P', ".--."}, {'Q', "--.-"}, {'R', ".-."}, {'S', "..."}, {'T', "-"},
        {'U', "..-"}, {'V', "...-"}, {'W', ".--"}, {'X', "-..-"}, {'Y', "-.--"},
        {'Z', "--.."},

        {'0', "-----"}, {'1', ".----"}, {'2', "..---"}, {'3', "...--"}, {'4', "....-"},
        {'5', "....."}, {'6', "-...."}, {'7', "--..."}, {'8', "---.."}, {'9', "----."},

        {' ', "!"}
    };
}

string MorseBlock(vector<string>& tet) {
    map<char, string> morseCode = MorseCode();
    stringstream morseStream;
    string currentBlock;
    int currentLength = 0;

    for (const string& str : tet) { // Изменено: обходим каждую строку в векторе
        for (char ch : str) { // Изменено: обходим каждый символ в строке
            ch = toupper(ch);
            if (morseCode.find(ch) != morseCode.end()) {
                string morseSymbol = morseCode[ch];
                int symbolLength = morseSymbol.length();

                if (currentLength + symbolLength > BLOCK_SIZE) {
                    morseStream << currentBlock << "|";
                    currentBlock = morseSymbol;
                    currentLength = symbolLength;
                }
                else {
                    currentBlock += morseSymbol;
                    currentLength += symbolLength;
                }
            }
        }
    }

    if (!currentBlock.empty()) {
        morseStream << currentBlock;
    }
    return morseStream.str();
}

//вот по сюда удаляем


//функцию main и DisplayMenu не удалять! Вместо своей фамилии добавть название своего метода
void DisplayMenu() { // создаем меню для выбора действий
    cout << "__________________(-_-)_/_________________" << endl;
    cout << "                   Menu:          " << endl;
    cout << " 0) Exit the program           " << endl;
    cout << " 1) Mamaev                   " << endl;
    cout << " 2) Saburova                  " << endl;
    cout << " 3) Volkova                   " << endl;
    cout << " 4) Shklyaeva                   " << endl;
    cout << " 5) Govorukhina                   " << endl;
    cout << "__________________(~_~)_/_________________" << endl;
}

int main() {
    bool E = true;
    string filename;
    string line;
    int choice;
    string wrong;
    string symbol;
    int dataSize = 0;
    vector<string> results;
    vector<string> text;

    cout << "Enter file name, necessarily with .txt: ";// обязательно с указанием расширения .txt, также файл должен находиться в папке проекта
    getline(cin, filename);

    ifstream inputFile(filename);

    if (!inputFile) {
        cerr << "Error opening file: " << filename << endl;
        return 1; 
    }

    while (inputFile >> symbol) {
        dataSize++;
        text.push_back(symbol);
    }
    inputFile.close();

    //здесь я запускаю счетчик времени, чтобы понять за какое количество времени производится шифровка(к сожалению в case не запихнуть) вы должны поменять названия функций вместо фамилий
    auto start1 = chrono::high_resolution_clock::now();
    MorseBlock(text);//поменять название функции и разкоментить, text оставить
    auto end1 = chrono::high_resolution_clock::now();
    auto lag1 = chrono::duration_cast<chrono::milliseconds>(end1 - start1).count();

    auto start2 = chrono::high_resolution_clock::now();
    /*Saburova(text)*/;//поменять название функции и разкоментить, text оставить
    auto end2 = chrono::high_resolution_clock::now();
    auto lag2 = chrono::duration_cast<chrono::milliseconds>(end2 - start2).count();

    auto start3 = chrono::high_resolution_clock::now();
    /*Volkova(text)*/;//поменять название функции и разкоментить, text оставить
    auto end3 = chrono::high_resolution_clock::now();
    auto lag3 = chrono::duration_cast<chrono::milliseconds>(end3 - start3).count();

    auto start4 = chrono::high_resolution_clock::now();
    /*Shklyaeva(text)*/;//поменять название функции и разкоментить, text оставить
    auto end4 = chrono::high_resolution_clock::now();
    auto lag4 = chrono::duration_cast<chrono::milliseconds>(end4 - start4).count();

    auto start5 = chrono::high_resolution_clock::now();
    /*Govorukhina(text)*/;//поменять название функции и разкоментить, text оставить
    auto end5 = chrono::high_resolution_clock::now();
    auto lag5 = chrono::duration_cast<chrono::milliseconds>(end5 - start5).count();

    while (E) {
        DisplayMenu();
        cout << "Choose the action: ";
        getline(cin >> choice, wrong);
        if (cin.fail() || choice < 0 || choice > 5) {
            cout << "Not true number" << endl;
            cin.clear();
            continue;
        }

        switch (choice) {
        case 0:
            E = false;
            break;
        case 1:
            MorseBlock(text);//поменять название функции, text оставить

            cout << "Source: ";//это выводит изначальный текст
            for (size_t i = 0; i < text.size(); ++i) {
                cout << text[i];
                if (i < text.size() - 1) {
                    cout << " ";
                }
            }
            cout << endl;

            cout << "Encrypted text in Morse code: " << MorseBlock(text) << endl;//выводит зашифрованный текст, поменять название функции

            results.push_back("File: " + filename + " Encrypting time: " + to_string(lag1) + " ms");
            for (const auto& result : results) {
                cout << result << endl;
            }
            break;
        case 2:
            /*Saburova(text);*///поменять название функции и разкоментить, text оставить

            cout << "Source: ";//это выводит изначальный текст
            for (size_t i = 0; i < text.size(); ++i) {
                cout << text[i];
                if (i < text.size() - 1) {
                    cout << " ";
                }
            }
            cout << endl;

            cout << "Encrypted text in Morse code: " << MorseBlock(text) << endl;//выводит зашифрованный текст и разкоментить, поменять название функции

            results.push_back("File: " + filename + " Encrypting time: " + to_string(lag2) + " ms");
            for (const auto& result : results) {
                cout << result << endl;
            }
            break;
        case 3:
            /*Volkova(text);*///поменять название функции и разкоментить, text оставить

            cout << "Source: ";//это выводит изначальный текст
            for (size_t i = 0; i < text.size(); ++i) {
                cout << text[i];
                if (i < text.size() - 1) {
                    cout << " ";
                }
            }
            cout << endl;

            cout << "Encrypted text in Morse code: " << MorseBlock(text) << endl;//выводит зашифрованный текст, поменять название функции

            results.push_back("File: " + filename + " Encrypting time: " + to_string(lag3) + " ms");
            for (const auto& result : results) {
                cout << result << endl;
            }
            break;
        case 4:
            /*Shklyaeva(text);*///поменять название функции и разкоментить, text оставить

            cout << "Source: ";//это выводит изначальный текст
            for (size_t i = 0; i < text.size(); ++i) {
                cout << text[i];
                if (i < text.size() - 1) {
                    cout << " ";
                }
            }
            cout << endl;

            cout << "Encrypted text in Morse code: " << MorseBlock(text) << endl;//выводит зашифрованный текст, поменять название функции

            results.push_back("File: " + filename + " Encrypting time: " + to_string(lag4) + " ms");
            for (const auto& result : results) {
                cout << result << endl;
            }
            break;
        case 5:
            /*Govorukhina(text);*///поменять название функции и разкоментить, text оставить

            cout << "Source: ";//это выводит изначальный текст
            for (size_t i = 0; i < text.size(); ++i) {
                cout << text[i];
                if (i < text.size() - 1) {
                    cout << " ";
                }
            }
            cout << endl;

            cout << "Encrypted text in Morse code: " << MorseBlock(text) << endl;//выводит зашифрованный текст, поменять название функции

            results.push_back("File: " + filename + " Encrypting time: " + to_string(lag5) + " ms");
            for (const auto& result : results) {
                cout << result << endl;
            }
            break;
        }
    }
}