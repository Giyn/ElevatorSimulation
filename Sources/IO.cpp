/**
 * @filename IO.cpp
 * @description elevator simulation input and output source file
 * @author ���Ԫ
 * @date 2020/12/23
 */

#include "../Headers/IO.h"

extern int MaxRunTime; /* ���������ʱ�� */

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

/**
 * ��ӡ�ַ������ݲ�����
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
 * ��ʾ���ݽṹ
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
 * ��ʾ����ģ���������
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
    PrintLine("**                        ����ģ��                         **", FOREGROUND_GREEN);
    GotoXY(28, 8);
    PrintLine("**                                                         **", FOREGROUND_GREEN);
    GotoXY(28, 9);
    PrintLine("**                                                         **", FOREGROUND_GREEN);
    GotoXY(28, 10);
    PrintLine("**                                                         **", FOREGROUND_GREEN);
    GotoXY(28, 11);
    PrintLine("**                    �������ѧ�뼼��1��                      **", FOREGROUND_GREEN);
    GotoXY(28, 12);
    PrintLine("**                    3119004757                           **", FOREGROUND_GREEN);
    GotoXY(28, 13);
    PrintLine("**                    ���Ԫ                               **", FOREGROUND_GREEN);
    GotoXY(28, 14);
    PrintLine("**                                                         **", FOREGROUND_GREEN);
    GotoXY(28, 15);
    PrintLine("**                                                         **", FOREGROUND_GREEN);
    GotoXY(28, 16);
    PrintLine("*************************************************************", FOREGROUND_GREEN);
    GotoXY(32, 17);
    Print("���������ϵͳ������ʱ�䣨500=<x<=10000��:", FOREGROUND_GREEN);
    while (scanf("%d", &MaxRunTime) != 1 || MaxRunTime < 500 || MaxRunTime > 10000) {
        GotoXY(32, 17);
        printf("                                                                                ");
        GotoXY(32, 17);
        Print("���������������루500=<x<=10000��:", FOREGROUND_GREEN);
        while (getchar() != '\n') continue;
    }
}

/**
 * ��ӡ���ݿ��
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
    Print("������Ϣ:", FOREGROUND_GREEN);
    GotoXY(0, 6);
    Print("�˿���Ϊ:", FOREGROUND_GREEN);
}

/**
 * ��ʾ�ȴ����еĳ˿�
 *
 * @param[in]  Q   : passenger waiting queue
 * @param[in]  flag: 0 - passengers in this queue will go down
 *                   1 - passengers in this queue will go up
 * @param[in]  num : the number of passengers in another queue in the same floor
 *                   (The display must be after it, otherwise it will overwrite the data of the previous queue.)
 * @return  none
 */
void ShowWaitingPassenger(PassengerWaitingQueue Q, int flag, int num) {
    PassengerQueueNode *p;
    p = Q.front->next;
    int j = num;
    while (p) {
        gotoxy(RightElevatorX + 26 + j * 6, RightElevatorY - 1 + (4 - p->data->InFloor) * FloorHeight);
        printf(" %d", p->data->PassengerID);
        if (flag) printf("��");
        else printf("��");
        printf("%d", p->data->OutFloor);
        p = p->next;
        j++;
    }
}

/**
 * ����ȴ����еĳ˿�
 *
 * @param[in]  Q   : passenger waiting queue
 * @param[in]  flag: 0 - passengers in this queue will go down
 *                   1 - passengers in this queue will go up
 * @param[in]  num : the number of passengers in another queue in the same floor
 * @return  none
 */
void DisappearWaitingPassenger(PassengerWaitingQueue Q, int flag, int num) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    ShowWaitingPassenger(Q, flag, num);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

/**
 * ��ӡ���ݵ����ж���
 *
 * @param[in]  e: elevator structure
 * @param[in]  k:
 * @return  none
 */
void PrintfElevatorAction(Elevator e, int k) {
    GotoXY(10 + 30 * k, 4);
    printf("                         ");
    GotoXY(10 + 30 * k, 4);
    switch (e->action) {
        case Opening:
            printf(" %d�ŵ��� �����ڴ�", k + 1);
            break;
        case Opened:
            printf(" %d�ŵ��� ���Ѿ���", k + 1);
            break;
        case Closing:
            printf(" %d�ŵ��� �����ڹر�", k + 1);
            break;
        case Closed:
            printf(" %d�ŵ��� ���Ѿ��ر�", k + 1);
            break;
        case Moving:
            printf(" %d�ŵ��� �����ƶ�", k + 1);
            break;
        case Decelerate:
            printf(" %d�ŵ��� ���ڼ���", k + 1);
            break;
        case Accelerate:
            printf(" %d�ŵ��� ���ڼ���", k + 1);
            break;
        case Waiting:
            printf(" %d�ŵ��� ���ڵȴ�", k + 1);
            break;
    }
}
