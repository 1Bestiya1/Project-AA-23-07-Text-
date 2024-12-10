#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <fstream>
#include <vector>
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

string block_encryption_HillCipher(const string& text, int key[5][5]) {
    const int block_size = 5;
    map<char, int> HillAlphabet = Hill_Cipher_Alphabet();
    map<int, char> Alph = Alphabet();
    vector<string> blocks;
    string result;
    int current_length = 0;
    string current_block = "";

    for (char symbol : text) {
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
        int r = block_size - (text.length() % block_size);
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

    return result; // Возвращаем результат.
}

string encrypt(const std::string& input, int key) {
    // Определяем количество строк
    int rows = (input.size() + key - 1) / key; // Округление вверх
    std::vector<std::string> grid(rows, std::string(key, ' '));

    // Заполняем сетку
    for (size_t i = 0; i < input.size(); ++i) {
        grid[i / key][i % key] = input[i];
    }

    // Читаем по столбцам
    std::string output;
    for (int col = 0; col < key; ++col) {
        for (int row = 0; row < rows; ++row) {
            if (grid[row][col] != ' ') { // Пропускаем пустые символы
                output += grid[row][col];
            }
        }
    }

    return output; // Возвращаем зашифрованный текст
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
        string morseText = encrypt(line, 2); // Шифруем
        cout << "Source: " << line << endl; // Исходный текст:
        cout << "Encrypted text in Morse code: " << morseText << endl; // Зашифрованный текст:

        // ШИФР ХИЛЛА. Ключ:
        int hill_key[5][5] = {
            {1,1,2,3,4},
            {3,1,7,3,1},
            {1,8,2,6,4},
            {9,1,6,3,2},
            {4,9,2,6,4}
        };
        string HillText = block_encryption_HillCipher(line, hill_key);
        cout << "HILL CIPHER. Sourse: " << line << endl; // Выводим исходный текст.
        cout << "Encrypted text in Hill cipher: " << HillText << endl; // Выводим зашифрованный текст.
    }

    inputFile.close();
    return 0;

}