#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <fstream>
#include <chrono>
#include <bitset>
using namespace std;

// ШИФР ХИЛЛА
// Создаем алфавит.
// Длина алфавита - простое число, что удобно, т.к. детерминант ключа и длина алфавита должны быть взаимно простыми.
map<char, int> Hill_Cipher_Alphabet() {
    return {
        {'A', 0}, {'B', 1}, {'C', 2}, {'D', 3}, {'E', 4},
        {'F', 5}, {'G', 6}, {'H', 7}, {'I', 8}, {'J', 9},
        {'K', 10}, {'L', 11}, {'M', 12}, {'N', 13}, {'O', 14},
        {'P', 15}, {'Q', 16}, {'R', 17}, {'S', 18}, {'T', 19},
        {'U', 20}, {'V', 21}, {'W', 22}, {'X', 23}, {'Y', 24},
        {'Z', 25},
        {'0', 26}, {'1', 27}, {'2', 28}, {'3', 29}, {'4', 30},
        {'5', 31}, {'6', 32}, {'7', 33}, {'8', 34}, {'9', 35},
        {' ', 36}
    };
}

// Алфавит для обратного преобразования.
map<int, char> Alphabet() {
    return {
        {0, 'A'}, {1, 'B'}, {2, 'C'}, {3, 'D'}, {4, 'E'},
        {5, 'F'}, {6, 'G'}, {7, 'H'}, {8, 'I'}, {9, 'J'},
        {10, 'K'}, {11, 'L'}, {12, 'M'}, {13, 'N'}, {14, 'O'},
        {15, 'P'}, {16, 'Q'}, {17, 'R'}, {18, 'S'}, {19, 'T'},
        {20, 'U'}, {21, 'V'}, {22, 'W'}, {23, 'X'}, {24, 'Y'},
        {25, 'Z'},
        {26, '0'}, {27, '1'}, {28, '2'}, {29, '3'}, {30, '4'},
        {31, '5'}, {32, '6'}, {33, '7'}, {34, '8'}, {35, '9'},
        {36, ' '}
    };
}

string volkova(vector<string> text, int key[5][5]) {
    const int block_size = 5;
    map<char, int> HillAlphabet = Hill_Cipher_Alphabet();
    map<int, char> Alph = Alphabet();
    vector<string> blocks;
    string result;
    int current_length = 0;
    string current_block = "";

    for (const string& str : text) {
        for (char symbol : str) {
            symbol = toupper(symbol);

            // Деление текста на блоки:
            if (current_length == block_size) {
                blocks.push_back(current_block);
                current_block = symbol;
                current_length = 1;
            }
            else {
                current_block += symbol;
                current_length += 1;
            }
        }

        // Если остался не заполненный до конца блок, добавляем пробелы.
        if (!current_block.empty()) {
            int r = block_size - (str.length() % block_size);
            for (int k = 0; k < r; k++) {
                current_block += " ";
            }
            blocks.push_back(current_block);
        }

        // Шифрование каждого блока:
        for (string block : blocks) {
            // Преобразуем блок в вектор:
            vector<int> block_vector;
            for (int j = 0; j < block.size(); j++) {
                int int_symbol = HillAlphabet[block[j]];
                block_vector.push_back(int_symbol);
            }

            // Умножаем вектор на матрицу-ключ:
            vector<int> res_vector = { 0,0,0,0,0 };
            for (int i = 0; i < 5; i++) {
                for (int p = 0; p < 5; p++) {
                    res_vector[i] += block_vector[p] * key[p][i];
                }
            }

            // Берем остаток от деления матрицы на 37 (длина алфавита):
            for (int i = 0; i < 5; i++) {
                res_vector[i] = res_vector[i] % 37;
            }

            // Декодируем полученный вектор:
            for (int i = 0; i < 5; i++) {
                result += Alph[res_vector[i]];
            }
        }
    }

    return result; // Возвращаем результат.
}

// Простейший пример блочного шифрования (его удаляем):
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

// Квадрат Полибия для шифра Bifid
const string POLYBIUS_SQUARE = "ABCDEFGHIKLMNOPQRSTUVWXYZ"; // Без буквы J

// Функция для создания ключа
string generateKey(const string& key) {
    string uniqueKey;
    map<char, bool> usedChars;

    for (char c : key) {
        c = toupper(c);
        if (c == 'J') c = 'I'; // Заменяем J на I
        if (c >= 'A' && c <= 'Z' && !usedChars[c]) {
            uniqueKey += c;
            usedChars[c] = true;
        }
    }

    // Добавляем оставшиеся символы из квадрата Полибия
    for (char c : POLYBIUS_SQUARE) {
        if (!usedChars[c]) {
            uniqueKey += c;
        }
    }

    return uniqueKey;
}

// Функция для преобразования вектора строк в одну строку
string vectorToString(const vector<string>& vec) {
    string result;
    for (const auto& str : vec) {
        result += str;
    }
    return result;
}

// Функция для разделения строки на строки заданной длины
vector<string> splitString(const string& str, size_t lineLength) {
    vector<string> result;
    for (size_t i = 0; i < str.size(); i += lineLength) {
        result.push_back(str.substr(i, lineLength));
    }
    return result;
}

// Функция для шифрования текста
vector<string> bifidEncrypt(const vector<string>& plaintextLines, const string& key) {
    string normalizedText;
    for (const string& line : plaintextLines) {
        for (char c : line) {
            c = toupper(c);
            if (c == 'J') c = 'I'; // Заменяем J на I
            if (c >= 'A' && c <= 'Z') {
                normalizedText += c;
            }
        }
    }

    string polybiusKey = generateKey(key);
    map<char, pair<int, int>> polybiusMap;

    // Создаем карту для квадрата Полибия
    for (int i = 0; i < polybiusKey.size(); ++i) {
        polybiusMap[polybiusKey[i]] = { i / 5 + 1, i % 5 + 1 };
    }

    // Преобразуем текст в пары чисел
    vector<int> rowNumbers, colNumbers;
    for (char c : normalizedText) {
        rowNumbers.push_back(polybiusMap[c].first);
        colNumbers.push_back(polybiusMap[c].second);
    }

    // Объединяем строки и столбцы
    vector<int> combinedNumbers;
    combinedNumbers.insert(combinedNumbers.end(), rowNumbers.begin(), rowNumbers.end());
    combinedNumbers.insert(combinedNumbers.end(), colNumbers.begin(), colNumbers.end());

    // Преобразуем числа обратно в символы
    string ciphertext;
    for (size_t i = 0; i < combinedNumbers.size(); i += 2) {
        int row = combinedNumbers[i];
        int col = combinedNumbers[i + 1];
        char c = polybiusKey[(row - 1) * 5 + (col - 1)];
        ciphertext += c;
    }

    // Разбиваем зашифрованный текст на строки
    size_t lineLength = plaintextLines[0].size(); // Предполагаем, что все строки одинаковой длины
    return splitString(ciphertext, lineLength);
}

// Функция для дешифрования текста
vector<string> bifidDecrypt(const vector<string>& ciphertextLines, const string& key) {
    string ciphertext = vectorToString(ciphertextLines);

    string polybiusKey = generateKey(key);
    map<char, pair<int, int>> polybiusMap;

    // Создаем карту для квадрата Полибия
    for (int i = 0; i < polybiusKey.size(); ++i) {
        polybiusMap[polybiusKey[i]] = { i / 5 + 1, i % 5 + 1 };
    }

    // Преобразуем текст в пары чисел
    vector<int> combinedNumbers;
    for (char c : ciphertext) {
        combinedNumbers.push_back(polybiusMap[c].first);
        combinedNumbers.push_back(polybiusMap[c].second);
    }

    // Разделяем числа на строки и столбцы
    vector<int> rowNumbers, colNumbers;
    for (size_t i = 0; i < combinedNumbers.size() / 2; ++i) {
        rowNumbers.push_back(combinedNumbers[i]);
        colNumbers.push_back(combinedNumbers[i + combinedNumbers.size() / 2]);
    }

    // Преобразуем числа обратно в символы
    string plaintext;
    for (size_t i = 0; i < rowNumbers.size(); ++i) {
        int row = rowNumbers[i];
        int col = colNumbers[i];
        char c = polybiusKey[(row - 1) * 5 + (col - 1)];
        plaintext += c;
    }

    // Разбиваем расшифрованный текст на строки
    size_t lineLength = ciphertextLines[0].size(); // Предполагаем, что все строки одинаковой длины
    return splitString(plaintext, lineLength);
}

// Функция Govorukhina, принимающая вектор строк
string Govorukhina(const vector<string>& text) {
    string key;
    cout << "Enter the key (letters only, no spaces): ";
    cin >> key;
    vector<string> results;


    auto start5 = chrono::high_resolution_clock::now();
    vector<string> ciphertextLines = bifidEncrypt(text, key);
    auto end5 = chrono::high_resolution_clock::now();
    auto lag5 = chrono::duration_cast<chrono::milliseconds>(end5 - start5).count();

    // Шифрование
    cout << "Encrypted text:" << endl;
    for (const string& line : ciphertextLines) {
        cout << line << endl;
    }

    results.push_back("Encrypting time: " + to_string(lag5) + " ms");
    for (const auto& result : results) {
        cout << result << endl;
    }

    return vectorToString(ciphertextLines);
}

// Функция для шифрования текста
string encrypt(const string& input, int key) {
    // Определяем количество строк
    int rows = (input.size() + key - 1) / key; // Округление вверх
    vector<string> grid(rows, string(key, ' '));

    // Заполняем сетку
    for (size_t i = 0; i < input.size(); ++i) {
        grid[i / key][i % key] = input[i];
    }

    // Читаем по столбцам
    string output;
    for (int col = 0; col < key; ++col) {
        for (int row = 0; row < rows; ++row) {
            if (grid[row][col] != ' ') { // Пропускаем пустые символы
                output += grid[row][col];
            }
        }
    }

    return output; // Возвращаем зашифрованный текст
}

// Функция для преобразования вектора строк в одну строку
string VTS(const vector<string>& vec) {
    string result;
    for (const auto& str : vec) {
        result += str;
    }
    return result;
}

// Функция Mamaev, принимающая вектор строк
string Mamaev(const vector<string>& text) {
    int key;
    cout << "key: ";
    cin >> key;
    vector<string> results;

    // Преобразуем вектор строк в одну строку
    string inputText = VTS(text);

    // Шифруем текст
    auto start1 = chrono::high_resolution_clock::now();
    string encryptedText = encrypt(inputText, key);
    auto end1 = chrono::high_resolution_clock::now();
    auto lag1 = chrono::duration_cast<chrono::milliseconds>(end1 - start1).count();
    cout << "Encrypted text:\n" << encryptedText << endl;
    results.push_back("Encrypting time: " + to_string(lag1) + " ms");
    for (const auto& result : results) {
        cout << result << endl;
    }

    return encryptedText;
}

// Перестановки и S-блоки
const int P10[10] = { 2, 4, 1, 6, 3, 9, 5, 8, 7, 0 };
const int P8[8] = { 5, 2, 6, 3, 7, 4, 9, 8 };
const int IP[8] = { 1, 5, 2, 0, 3, 6, 7, 4 };
const int IP_INV[8] = { 3, 0, 2, 4, 6, 1, 7, 5 };
const int E[8] = { 3, 0, 1, 2, 1, 2, 3, 0 };
const int S0[4][4] = {
    {1, 0, 3, 2},
    {3, 2, 1, 0},
    {0, 2, 1, 3},
    {2, 1, 0, 3}
};
const int S1[4][4] = {
    {0, 1, 2, 3},
    {2, 0, 1, 3},
    {3, 0, 1, 0},
    {2, 1, 0, 3}
};

std::vector<std::bitset<8>> textToBinaryBlocks(const std::string& text) {
    std::vector<std::bitset<8>> binaryBlocks;

    // Преобразуем каждый символ в двоичный код
    for (char ch : text) {
        std::bitset<8> binaryChar(ch);
        binaryBlocks.push_back(binaryChar);
    }

    // Проверяем последний блок
    if (!binaryBlocks.empty()) {
        // Если последний блок меньше 8 бит, дополняем его
        std::bitset<8> lastBlock = binaryBlocks.back();
        if (text.size() % 8 != 0) {
            int bitsToAdd = 8 - (text.size() % 8);
            for (int i = 0; i < bitsToAdd; ++i) {
                lastBlock[7 - i] = 0; // Дополняем нулями слева
            }
            binaryBlocks.back() = lastBlock; // Обновляем последний блок
        }
    }
    return binaryBlocks;
}

std::bitset<10> permute1010(const std::bitset<10>& input, const int* perm, int size) {
    std::bitset<10> output;
    for (int i = 0; i < size; ++i) {
        output[i] = input[perm[i]];
    }
    return output;
}

std::bitset<8> permute88(const std::bitset<8>& input, const int* perm, int size) {
    std::bitset<8> output;
    for (int i = 0; i < size; ++i) {
        output[i] = input[perm[i]];
    }
    return output;
}

std::bitset<8> permute108(const std::bitset<10>& input, const int* perm, int size) {
    std::bitset<8> output;
    for (int i = 0; i < size; ++i) {
        output[i] = input[perm[i]];
    }
    return output;
}

// Функция для генерации ключей
std::bitset<8> generateKeys(const std::bitset<10>& key, int number) {
    std::bitset<8> keys;
    std::bitset<10> permutedKey = permute1010(key, P10, 10);

    // Разделяем ключ на две части
    std::bitset<5> left(permutedKey.to_string().substr(0, 5));
    std::bitset<5> right(permutedKey.to_string().substr(5, 5));

    for (int i = 0; i < number; ++i) {
        // Сдвиг влево
        left = bitset<5>(left.to_string().substr(1) + left.to_string().substr(0, 1));
        right = bitset<5>(right.to_string().substr(1) + right.to_string().substr(0, 1));

        // Генерация ключа
        std::bitset<8> keys = permute108(bitset<10>(left.to_string() + right.to_string()), P8, 8);;
    }

    return keys;
}

// Функция для S-блока
std::bitset<2> sBlock(const std::bitset<4>& input, const int s[4][4]) {
    int row = int(input[0]) * int(input[0]) + int(input[3]);
    int col = int(input[1]) * int(input[1]) + int(input[2]);
    return std::bitset<2>(s[row][col]);
}

// Функция F
std::bitset<4> fFunction(const std::bitset<4>& right, const std::bitset<8>& key) {
    std::bitset<8> expanded;
    for (int i = 0; i < 8; ++i) {
        expanded[i] = right[E[i]];
    }

    expanded ^= key; // XOR с ключом

    std::bitset<2> left = sBlock(bitset<4>(expanded.to_string().substr(0, 4)), S0);
    std::bitset<2> rightS = sBlock(bitset<4>(expanded.to_string().substr(4, 4)), S1);
    return bitset<4>(left.to_string() + rightS.to_string());
}

// Шифрование блока
std::bitset<8> encrypt(const std::bitset<8>& block, const std::bitset<10>& key) {
    std::bitset<8> permutedBlock = permute88(block, IP, 8);
    std::bitset<4> left = bitset<4>(permutedBlock.to_string().substr(0, 4));
    std::bitset<4> right = bitset<4>(permutedBlock.to_string().substr(4, 4));

    std::bitset<4> temp = right;
    left ^= fFunction(right, generateKeys(key, 1));
    left = temp;
    temp = right;
    right = left ^ fFunction(right, generateKeys(key, 2));
    left = temp;

    std::bitset<8> combined = bitset<8>(right.to_string() + left.to_string());
    return permute88(combined, IP_INV, 8);
}

string Shklyaeva(const vector<string>& text) {
    vector<string> results;
    std::bitset<10> key("1010000010");
    auto start4 = chrono::high_resolution_clock::now();

    std::vector<std::bitset<8>> binaryText = textToBinaryBlocks(vectorToString(text));
    string result = "";
    for (const auto& i : binaryText) {
        result = result + encrypt(i, key).to_string();
    }

    auto end4 = chrono::high_resolution_clock::now();
    auto lag4 = chrono::duration_cast<chrono::milliseconds>(end4 - start4).count();
    results.push_back("Encrypting time: " + to_string(lag4) + " ms");
    for (const auto& result1 : results) {
        cout << result1 << endl;
    }
    return result;
}

// Функцию main и DisplayMenu не удалять! Вместо своей фамилии добавть название своего метода
void DisplayMenu() { // создаем меню для выбора действий
    cout << "__________________(-_-)_/_________________" << endl;
    cout << "                   Menu:          " << endl;
    cout << " 0) Exit the program           " << endl;
    cout << " 1) The transposition cipher                   " << endl;
    cout << " 2) Saburova                  " << endl;
    cout << " 3) Hill cipher                   " << endl;
    cout << " 4) DES cipher                   " << endl;
    cout << " 5) Bifid cipher                 " << endl;
    cout << "__________________(~_~)_/_________________" << endl;
}

int main() {
    bool E = true;
    string filename;
    string line;
    int choice;
    int dataSize = 0;
    vector<string> results;
    vector<string> text;

    // ШИФР ХИЛЛА. Ключ:
    int hill_key[5][5] = {
        {1,1,2,3,4},
        {3,1,7,3,1},
        {1,8,2,6,4},
        {9,1,6,3,2},
        {4,9,2,6,4}
    };

    cout << "Enter file name, necessarily with .txt: "; // обязательно с указанием расширения .txt, также файл должен находиться в папке проекта
    getline(cin, filename);

    ifstream inputFile(filename);

    if (!inputFile) {
        cerr << "Error opening file: " << filename << endl;
        return 1;
    }

    string inputText;
    while (getline(inputFile, line)) {
        inputText += line + '\n'; // Добавляем новую строку
        text.push_back(line); // Добавляем строку в вектор text
    }
    inputFile.close();

    auto start2 = chrono::high_resolution_clock::now();
    /*Saburova(text)*/; // поменять название функции и разкоментить, text оставить
    auto end2 = chrono::high_resolution_clock::now();
    auto lag2 = chrono::duration_cast<chrono::milliseconds>(end2 - start2).count();

    auto start3 = chrono::high_resolution_clock::now();
    volkova(text, hill_key);
    auto end3 = chrono::high_resolution_clock::now();
    auto lag3 = chrono::duration_cast<chrono::milliseconds>(end3 - start3).count();

    while (E) {
        DisplayMenu();
        cout << "Choose the action: ";
        cin >> choice;
        cin.ignore(); // Игнорируем символ новой строки после ввода числа

        if (cin.fail() || choice < 0 || choice > 5) {
            cout << "Not true number" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
        case 0:
            E = false;
            break;
        case 1:
            cout << "Source: " << inputText << endl; // Выводим исходный текст
            Mamaev(text); // Вызываем функцию Mamaev с передачей вектора text
            break;
        case 2:
            /*Saburova(text);*/ // поменять название функции и разкоментить, text оставить

            cout << "Source: "; // это выводит изначальный текст
            for (size_t i = 0; i < text.size(); ++i) {
                cout << text[i];
                if (i < text.size() - 1) {
                    cout << " ";
                }
            }
            cout << endl;

            cout << "Encrypted text in Morse code: " << MorseBlock(text) << endl; // выводит зашифрованный текст и разкоментить, поменять название функции

            results.push_back("File: " + filename + " Encrypting time: " + to_string(lag2) + " ms");
            for (const auto& result : results) {
                cout << result << endl;
            }
            break;
        case 3:
            volkova(text, hill_key);

            cout << "Source: "; // это выводит изначальный текст
            for (size_t i = 0; i < text.size(); ++i) {
                cout << text[i];
                if (i < text.size() - 1) {
                    cout << " ";
                }
            }
            cout << endl;

            cout << "Block size: 5" << endl;
            cout << "Encrypted text in Hill cipher: " << volkova(text, hill_key) << endl;

            results.push_back("File: " + filename + " Encrypting time: " + to_string(lag3) + " ms");
            for (const auto& result : results) {
                cout << result << endl;
            }
            break;
        case 4:
            
            cout << "Source: "; // это выводит изначальный текст
            for (size_t i = 0; i < text.size(); ++i) {
                cout << text[i];
                if (i < text.size() - 1) {
                    cout << " ";
                }
            }
            cout << endl;

            cout << "Encrypted text in DES code: " << Shklyaeva(text) << endl; // выводит зашифрованный текст, поменять название функции

            
            break;
        case 5:


            cout << "Source: " << inputText << endl; // Выводим исходный текст
            Govorukhina(text); // Вызываем функцию Govorukhina с передачей вектора text
            break;

        }
    }
}