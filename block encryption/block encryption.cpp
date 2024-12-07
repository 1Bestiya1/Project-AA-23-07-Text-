#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;



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
    }

    inputFile.close();
    return 0;

}