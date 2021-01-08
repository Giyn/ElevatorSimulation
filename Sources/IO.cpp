/**
 * @filename IO.cpp
 * @description elevator simulation input and output source file
 * @author 许继元
 * @date 2020/12/23
 */

#include "../Headers/IO.h"

extern int MaxRunTime; /* 电梯最长运行时间 */

/**
 * 定位控制台的光标位置
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
 * 打印字符串内容
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

/**
 * 打印字符串内容并换行
 *
 * @param[in]  content: elevator structure
 * @param[in]  color  : word color
 * @return  none
 */
void PrintLine(string content, WORD color) {
    if (0 == color) cout << content << endl;
    else {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | color);
        cout << content << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }
}

/**
 * 清除电梯结构
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
 * 显示电梯结构
 *
 * @param[in]  e: elevator structure
 * @param[in]  k:
 * @param[in]  x:
 * @return  none
 */
void ShowElevatorBody(Elevator e, int k, int x) {
    GotoXY(LeftElevatorX + k * 27, LeftElevatorY - 1 + (4 - x) * FloorHeight);
    Print("[", FOREGROUND_RED);
    for (int i = 0; i < e->PassengerNum; i++) {
        if (e->PassengerID[i] != 0) printf(" %d", e->PassengerID[i]);
    }
    GotoXY(LeftElevatorX + k * 26 + 24, LeftElevatorY - 1 + (4 - x) * FloorHeight);
    Print("]", FOREGROUND_RED);
}

/**
 * 显示电梯模拟程序主题
 *
 * @param[in]  none
 * @return  none
 */
void ShowTitle() {
    GotoXY(28, 5);
    PrintLine("*************************************************************", FOREGROUND_GREEN);
    GotoXY(28, 6);
    PrintLine("**                                                         **", FOREGROUND_GREEN);
    GotoXY(28, 7);
    PrintLine("**                        电梯模拟                         **", FOREGROUND_GREEN);
    GotoXY(28, 8);
    PrintLine("**                                                         **", FOREGROUND_GREEN);
    GotoXY(28, 9);
    PrintLine("**                                                         **", FOREGROUND_GREEN);
    GotoXY(28, 10);
    PrintLine("**                                                         **", FOREGROUND_GREEN);
    GotoXY(28, 11);
    PrintLine("**                    计算机科学与技术1班                      **", FOREGROUND_GREEN);
    GotoXY(28, 12);
    PrintLine("**                    3119004757                           **", FOREGROUND_GREEN);
    GotoXY(28, 13);
    PrintLine("**                    许继元                               **", FOREGROUND_GREEN);
    GotoXY(28, 14);
    PrintLine("**                                                         **", FOREGROUND_GREEN);
    GotoXY(28, 15);
    PrintLine("**                                                         **", FOREGROUND_GREEN);
    GotoXY(28, 16);
    PrintLine("*************************************************************", FOREGROUND_GREEN);
    GotoXY(32, 17);
    Print("请输入电梯系统的运行时间（500=<x<=10000）:", FOREGROUND_GREEN);
    while (scanf("%d", &MaxRunTime) != 1 || MaxRunTime < 500 || MaxRunTime > 10000) {
        GotoXY(32, 17);
        printf("                                                                                ");
        GotoXY(32, 17);
        Print("输入有误，重新输入（500=<x<=10000）:", FOREGROUND_GREEN);
        while (getchar() != '\n') continue;
    }
}

/**
 * 打印电梯框架
 *
 * @param[in]  none
 * @return  none
 */
void PrintElevatorFrame() {
    int j, i, k;
    for (i = 0; i <= 2; i++) {
        for (j = MaxFloor + 1; j >= 0; j--) {
            if (j == MaxFloor) {
                GotoXY(6 + i * 27, 9);
                Print("***************************", FOREGROUND_GREEN);
            }
            GotoXY(6 + i * 27, 9 + j * FloorHeight);
            Print("***************************", FOREGROUND_GREEN);
        }
        j = MaxFloor + 1;
        for (k = 9; k <= 9 + j * FloorHeight; k++) {
            GotoXY(5 + i * 27, k);
            Print("|", FOREGROUND_GREEN);
            GotoXY(5 + i * 27 + 26, k);
            Print("|", FOREGROUND_GREEN);
        }
    }
    GotoXY(0, 4);
    Print("电梯信息:", FOREGROUND_GREEN);
    GotoXY(0, 6);
    Print("乘客行为:", FOREGROUND_GREEN);
}
