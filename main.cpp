/**
 * @filename main.cpp
 * @description Elevator Simulation Test
 * @author ���Ԫ
 * @date 2020/12/23
 */

#include "./Headers/ElevatorSimulation.h"
#include "./Headers/Passenger.h"
#include "./Headers/IO.h"

int MaxPassengerNum = 7;                    /* ���˿����� */
int MaxRunTime;                             /* �������ʱ�� */
int NextInterTime;                          /* ��һ���˿ͽ���ϵͳ��ʱ�� */
int TotalPassenger = 1;                     /* ��ǰ�ܹ��ж��ٸ��˿�(���ڲ������ظ������) */
int CallUp[5], CallDown[5], CallCar[5];     /* ¥����������°�ť, �Լ�Ŀ��¥��, ȡֵΪ1��ʾ����, -1��ʾ�����Ѿ���Ӧ */
PassengerWaitingQueue FloorWaitQueue[2][5]; /* ÿ��¥��2���ȴ�����, 0����, 1���� */

int main() {
    int Time = 0, t[3];
    Elevator E[3];
    srand((unsigned) time(NULL));

    t[2] = t[1] = t[0] = 0;
    InitElevator(E, 3);

    while (TRUE) {
        ShowTitle();
        GotoXY(32, 17);
        Print("���������ģ��ϵͳ������ʱ��(500��x��10000):", FOREGROUND_GREEN);
        MaxRunTime = InputInteger();
        if (MaxRunTime < 500 || MaxRunTime > 10000) {
            GotoXY(32, 17);
            printf("                                                                                ");
            GotoXY(32, 17);
            Print("�������, ����������500��10000֮�������!\n", FOREGROUND_GREEN);
            system("pause");
            system("cls");
        } else break;
    }
    system("cls");

    PrintElevatorFrame();
    ShowElevatorBody(E[0], 0, 1);
    ShowElevatorBody(E[1], 1, 1);
    ShowElevatorBody(E[2], 2, 1);

    while (Time++ < MaxRunTime) {
        /* �����µĳ˿� */
        if (NextInterTime == 0) NewPassenger();
        else NextInterTime--;

        CheckGiveUp(E);
        Controller(E);

        for (int i = 0; i < 3; i++) {
            /* ������ڿ���״̬, ÿ��һ����ʱ��������������˿� */
            if (E[i]->action == Opened) {
                /* ÿ��25t��һ���� */
                if (t[i] == InOutTime) {
                    t[i] = 0;
                    /* �ȴ��ĳ˿ͽ����������µȴ��ĳ˿� */
                    DisappearWaitingPassenger(FloorWaitQueue[1][E[i]->floor], 0, 0);
                    DisappearWaitingPassenger(FloorWaitQueue[0][E[i]->floor], 1,
                                              FloorWaitQueue[1][E[i]->floor].WaitingPassengerNum);
                    if (PassengerInOrOut(E[i], i) == SUCCESS) {
                        /* ���֮ǰ�ĵ���, ��ʾ�˿ͽ����ĵ��� */
                        DisappearElevatorBody(E[i], i, E[i]->floor);
                        ShowElevatorBody(E[i], i, E[i]->floor);
                    }
                    /* ���������ʾ */
                    ShowWaitingPassenger(FloorWaitQueue[1][E[i]->floor], 0, 0);
                    ShowWaitingPassenger(FloorWaitQueue[0][E[i]->floor], 1,
                                         FloorWaitQueue[1][E[i]->floor].WaitingPassengerNum);
                } else t[i]++;
            }
            /* ����ǰ״̬��ʱ�����ڵ���, ��ı�״̬ */
            if (TimeUp(E[i]) == SUCCESS) {
                ChangeElevatorAction(E[i], i);
                PrintfElevatorAction(E[i], i);
            } else E[i]->StateTimeCount--; /* ��ʱ */
        }
        if (Time % 10 == 0) {
            GotoXY(40, 2);
            Print("��ǰʱ��Ϊ:", FOREGROUND_GREEN);
            printf(" %d", Time);
        }
        if (Time % 100 == 0) PrintElevatorFrame();
        Sleep(80);
    }
    GotoXY(45, 30);

    printf("����ģ�����, ��л����ʹ��!");
    _getch();
}
