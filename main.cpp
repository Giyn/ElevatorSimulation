/**
 * @filename main.cpp
 * @description Elevator Simulation Test
 * @author 许继元
 * @date 2020/12/23
 */

#include "./Headers/ElevatorSimulation.h"

int MaxPassengerNum = 7;                    /* 最大乘客人数 */
int MaxRunTime;                             /* 最大运行时间 */
int NextInterTime;                          /* 下一个乘客进入系统的时间 */
int TotalPassenger = 1;                     /* 当前总共有多少个乘客(用于产生不重复的序号) */
int CallUp[5], CallDown[5], CallCar[5];     /* 楼层的向上向下按钮, 以及目标楼层, 取值为1表示按下, -1表示电梯已经响应 */
PassengerWaitingQueue FloorWaitQueue[2][5]; /* 每层楼有2个等待队列, 0向上, 1向下 */

int main() {
    int Time = 0, t[3];
    Elevator E[3];
    srand((unsigned) time(NULL));

    t[2] = t[1] = t[0] = 0;
    InitElevator(E, 3);

    ShowTitle();
    system("cls");

    PrintElevatorFrame();
    ShowElevatorBody(E[0], 0, 1);
    ShowElevatorBody(E[1], 1, 1);
    ShowElevatorBody(E[2], 2, 1);

    while (Time++ < MaxRunTime) {
        /* 产生新的乘客 */
        if (NextInterTime == 0) NewPassenger();
        else NextInterTime--;

        CheckGiveUp(E);
        Controller(E);

        for (int i = 0; i < 3; i++) {
            /* 如果处于开门状态, 每隔一定的时间周期允许进出乘客 */
            if (E[i]->action == Opened) {
                /* 每隔25t进一个人 */
                if (t[i] == InOutTime) {
                    t[i] = 0;
                    /* 等待的乘客进入电梯则更新等待的乘客 */
                    DisappearWaitingPassenger(FloorWaitQueue[1][E[i]->floor], 0, 0);
                    DisappearWaitingPassenger(FloorWaitQueue[0][E[i]->floor], 1,
                                              FloorWaitQueue[1][E[i]->floor].WaitingPassengerNum);
                    if (PassengerInOrOut(E[i], i) == SUCCESS) {
                        /* 清除之前的电梯, 显示乘客进入后的电梯 */
                        DisappearElevatorBody(E[i], i, E[i]->floor);
                        ShowElevatorBody(E[i], i, E[i]->floor);
                    }
                    /* 清除后再显示 */
                    ShowWaitingPassenger(FloorWaitQueue[1][E[i]->floor], 0, 0);
                    ShowWaitingPassenger(FloorWaitQueue[0][E[i]->floor], 1,
                                         FloorWaitQueue[1][E[i]->floor].WaitingPassengerNum);
                } else t[i]++;
            }
            /* 若当前状态的时间周期到了, 则改变状态 */
            if (TimeUp(E[i]) == SUCCESS) {
                ChangeElevatorAction(E[i], i);
                PrintfElevatorAction(E[i], i);
            } else E[i]->StateTimeCount--; /* 计时 */
        }
        if (Time % 10 == 0) {
            GotoXY(40, 2);
            Print("当前时间为:", FOREGROUND_GREEN);
            printf(" %d", Time);
        }
        if (Time % 100 == 0) PrintElevatorFrame();
        Sleep(80);
    }
    GotoXY(45, 30);
    
    printf("电梯模拟结束, 感谢您的使用!");
    _getch();
}
