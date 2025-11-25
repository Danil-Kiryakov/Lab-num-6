#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>

class FifteenPuzzle {
private:
    static const int SIZE = 4;
    std::vector<std::vector<int>> board;
    int emptyRow, emptyCol;

    // Перемешивает поле, делая только допустимые ходы
    void shuffle() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dirDist(0, 3);
        const int moves = 1000; // количество ходов для перемешивания

        for (int i = 0; i < moves; ++i) {
            int dir = dirDist(gen);
            switch (dir) {
            case 0: moveTile(emptyRow - 1, emptyCol); break; // вверх
            case 1: moveTile(emptyRow + 1, emptyCol); break; // вниз
            case 2: moveTile(emptyRow, emptyCol - 1); break; // влево
            case 3: moveTile(emptyRow, emptyCol + 1); break; // вправо
            }
        }
    }

    // Пытается переместить фишку на позицию (r, c) в пустую ячейку
    void moveTile(int r, int c) {
        if (r < 0 || r >= SIZE || c < 0 || c >= SIZE) return;
        std::swap(board[r][c], board[emptyRow][emptyCol]);
        emptyRow = r;
        emptyCol = c;
    }

    // Проверяет, решена ли головоломка
    bool isSolved() const {
        int expected = 1;
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (i == SIZE - 1 && j == SIZE - 1) {
                    return board[i][j] == 0; // последняя ячейка должна быть пустой
                }
                if (board[i][j] != expected) return false;
                ++expected;
            }
        }
        return true;
    }

public:
    FifteenPuzzle() {
        // Инициализация поля
        board.resize(SIZE, std::vector<int>(SIZE));
        int num = 1;
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                board[i][j] = num++;
            }
        }
        board[SIZE - 1][SIZE - 1] = 0; // пустая ячейка
        emptyRow = SIZE - 1;
        emptyCol = SIZE - 1;

        shuffle(); // перемешиваем
    }

    void printBoard() const {
        std::cout << "\n+----+----+----+----+\n";
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (board[i][j] == 0) {
                    std::cout << "|    ";
                }
                else {
                    std::cout << "| " << (board[i][j] < 10 ? " " : "") << board[i][j] << " ";
                }
            }
            std::cout << "|\n+----+----+----+----+\n";
        }
    }

    void play() {
        char input;
        std::cout << "Управление: w - вверх, s - вниз, a - влево, d - вправо, q - выход\n";

        while (!isSolved()) {
            printBoard();
            std::cout << "Ваш ход: ";
            std::cin >> input;

            if (input == 'q' || input == 'Q') {
                std::cout << "Выход из игры.\n";
                return;
            }

            int newRow = emptyRow, newCol = emptyCol;
            switch (input) {
            case 'w': case 'W': newRow = emptyRow + 1; break;
            case 's': case 'S': newRow = emptyRow - 1; break;
            case 'a': case 'A': newCol = emptyCol + 1; break;
            case 'd': case 'D': newCol = emptyCol - 1; break;
            default:
                std::cout << "Неверная команда!\n";
                continue;
            }

            moveTile(newRow, newCol);
        }

        printBoard();
        std::cout << "Поздравляем! Вы решили головоломку!\n";
    }
};

int main() {
    setlocale(LC_ALL, "Russian"); // для поддержки кириллицы (опционально)

    std::cout << "Добро пожаловать в игру \"Пятнашки\"!\n";
    FifteenPuzzle game;
    game.play();

    return 0;
}