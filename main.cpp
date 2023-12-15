#include <windows.h>
#include <iostream>
#include <cstdlib>

const int y = 20;
const int x = 100;

const int Const_thicknessX = 7+10;
const int Const_thicknessY = 4+6;

const int quantity = x / y;

std::string map[y][x] = { {} };

struct Elements {
    std::string empty = ".";
    std::string terra = "#";
    std::string preterra = "~";
    std::string reset = "`";
} e;

int GenField() {
    for (int oy = 0; oy < y; oy++) {
        for (int ox = 0; ox < x; ox++) {
            map[oy][ox] = e.empty;
        }
    }
    return 0;
}

int GenTerra() {
    srand(static_cast<unsigned>(time(nullptr)));
    for (int oy = 0; oy < (rand() % quantity)+1; oy++) {
        int rx = rand() % x;
        int ry = rand() % y;
        map[ry][rx] = e.terra;

        int ty = (rand() % Const_thicknessY)+3;
        for (int i = 0; i < ty; i++) {
            int tx = (rand() % Const_thicknessX) + 3;
            for (int k = 0; k < tx; k++) {
                if ((ry - i) < y && (ry - i) >= 0 && (rx + k) < x) {
                    map[ry - i][rx - k] = e.terra;
                }
                if ((ry - i + 1) < y && (ry - i + 1) >= 0 && map[ry - i + 1][rx - k] != e.terra)
                    map[ry - i + 1][rx - k] = e.preterra;
                if (rand() % 4 == 1)
                    if ((ry - i + 2) < y && (ry - i + 2) >= 0 && map[ry - i + 2][rx - k] != e.terra)
                        map[ry - i + 2][rx - k] = e.preterra;
            }
            tx = (rand() % Const_thicknessX) + 3;
            for (int k = 0; k < tx; k++) {
                if ((ry - i) < y && (ry - i) >= 0 && (rx + k) < x) {
                    map[ry - i][rx + k - 1] = e.terra;
                }
                if ((ry - i + 1) < y && (ry - i + 1) >= 0 && map[ry - i + 1][rx - k] != e.terra)
                    map[ry - i + 1][rx + k] = e.preterra;
                if (rand() % 4 == 1)
                    if ((ry - i + 2) < y && (ry - i + 2) >= 0 && map[ry - i + 2][rx - k] != e.terra)
                        map[ry - i + 2][rx + k] = e.preterra;
            }
        }
    }
    return 0;
}

void Print() {
    system("cls");
    for (int oy = 0; oy < y; oy++) {
        for (int ox = 0; ox < x; ox++) {
            std::cout << map[oy][ox];
        }
        std::cout << std::endl;
    }
}

int reset() {
    for (int i = 0; i < y; i++) {
        for (int k = 0; k < x; k++) {
            if (i + 1 != y) {
                map[i + 1][k] = e.terra;
            }
            map[i][k] = e.reset;
        }
        Print();
    }
    GenField();
    GenTerra();
    Print();
    return 0;
}

int main() {
    GenField();
    GenTerra();
    Print();
    for ( ; ; )
        if (GetAsyncKeyState('R') & 0x001) reset();

    return 0;
}