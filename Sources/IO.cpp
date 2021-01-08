/**
 * @filename IO.cpp
 * @description elevator simulation input and output source file
 * @author ���Ԫ
 * @date 2020/12/23
 */

#include "../Headers/IO.h"

/**
 * ��λ����̨�Ĺ��λ��
 *
 * @param[in]  x: x coordinate
 * @param[in]  y: y coordinate
 * @return  none
 */
void GotoXY(short x, short y) {
    COORD coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

/**
 * ������ݽṹ
 *
 * @param[in]  e: elevator structure
 * @param[in]  k:
 * @param[in]  x:
 * @return  none
 */
void DisappearElevatorBody(Elevator e, int k, int x) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    for (int i = LeftElevatorX + k * 27; i <= LeftElevatorX + k * 26 + 24; i++) {
        GotoXY(short(i), LeftElevatorY - 1 + (4 - x) * FloorHeight);
        printf(" ");
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

/**
 * ��ӡ�ַ�������
 *
 * @param[in]  content: elevator structure
 * @param[in]  color  : word color
 * @return  none
 */
void Print(string content, WORD color) {
    if (color == 0) cout << content;
    else {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | color);
        cout << content;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }
}
