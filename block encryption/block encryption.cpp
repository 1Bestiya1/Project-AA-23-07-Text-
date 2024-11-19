#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <fstream>
using namespace std;

//Простейший пример блочного шифрования,с использованием азбуки Морзе:
const int BLOCK_SIZE = 5; // Определим размер блока в символах Морзе

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

string MorseBlock(const string& text) {
    map<char, string> morseCode = MorseCode();
    stringstream morseStream;
    string currentBlock;
    int currentLength = 0;

    for (char ch : text) {
        ch = toupper(ch);
        if (morseCode.find(ch) != morseCode.end()) {
            string morseSymbol = morseCode[ch]; // Извлекаем код Морзе
            int symbolLength = morseSymbol.length();

            // Проверка, помещается ли текущий символ в блок
            if (currentLength + symbolLength > BLOCK_SIZE) {
                // Если текущий блок полон, добавляем его в результирующий поток
                morseStream << currentBlock << "|"; // Добавляем текущий блок
                // Начинаем новый блок
                currentBlock = morseSymbol;
                currentLength = symbolLength; // Обновляем длину блока
            }
            else {
                currentBlock += morseSymbol; // Добавляем код в текущий блок
                currentLength += symbolLength; // Обновляем текущую длину блока
            }
        }
    }

    // Если остались какие-то символы в текущем блоке, добавляем их в результат
    if (!currentBlock.empty()) {
        morseStream << currentBlock; // Добавляем все оставшиеся символы
    }

    return morseStream.str();
}

int main() {
    string filename;
    cout << "Enter file name, necessarily with .txt: ";// обязательно с указанием расширения .txt, также файл должен находиться в папке проекта
    getline(cin, filename);

    ifstream inputFile(filename);

    if (!inputFile) {
        cerr << "Error opening file: " << filename << endl;
        return 1; // Завершаем программу если файл не открывается
    }

    string line;
    while (getline(inputFile, line)) { // Читаем файл построчно
        string morseText = MorseBlock(line); // Шифруем
        cout << "Source: " << line << endl; // Исходный текст:
        cout << "Encrypted text in Morse code: " << morseText << endl; // Зашифрованный текст:
    }

    inputFile.close();
    return 0;

}