/**
 * @filename Passenger.cpp
 * @description elevator simulation passenger source file
 * @author 许继元
 * @date 2020/12/23
 */

#include "../Headers/Passenger.h"

extern int MaxPassengerNum;                        /* 电梯的最大乘客数 */
extern PassengerWaitingQueue FloorWaitQueue[2][5]; /* 每层楼有2个等待队列, 0向上, 1向下 */

/**
 * 乘客出电梯
 *
 * @param[in]  e: elevator structure
 * @param[in]  k:
 * @return  none
 */
Status PassengerOut(Elevator &e, int k) {
    Passenger p;
    int i, j;
    /* 乘客出栈, 每出去一个乘客需要等待25t */
    if (StackEmpty(e->Stack[e->floor]) != SUCCESS) {
        Pop(e->Stack[e->floor], p);
        for (i = 0; i < MaxPassengerNum; i++) {
            if (e->PassengerID[i] == p->PassengerID) break;
        }
        e->PassengerNum--;

        /* 覆盖乘客ID数组的数据 */
        for (j = i; j < 7; j++) e->PassengerID[j] = e->PassengerID[j + 1];
        GotoXY(10 + 30 * k, 6);
        printf("                         ");
        GotoXY(10 + 30 * k, 6);
        printf(" %d乘客出电梯 %d", p->PassengerID, k + 1);
        free(p);

        return SUCCESS;
    } else return FAILED;
}

/**
 * 乘客入电梯
 *
 * @param[in]  e: elevator structure
 * @param[in]  k:
 * @return  none
 */
Status PassengerIn(Elevator &e, int k) {
    Passenger p;
    if (e->PassengerNum >= 8) return FAILED;
    switch (e->state) {
        /* 如果该电梯向下, 则只接收向下的乘客 */
        case GoingDown:
            if (FloorWaitQueue[1][e->floor].WaitingPassengerNum) {
                if (DeQueue(FloorWaitQueue[1][e->floor], p) == SUCCESS) {
                    if (Push(e->Stack[p->OutFloor], p) == SUCCESS) {
                        e->CallCar[p->OutFloor] = 1;
                        e->PassengerID[e->PassengerNum++] = p->PassengerID;

                        GotoXY(10 + 30 * k, 6);
                        printf("                         ");
                        GotoXY(10 + 30 * k, 6);
                        printf(" %d号乘客成功进入电梯%d", p->PassengerID, k + 1);
                    } else printf(" %d号乘客进入电梯%d失败", p->PassengerID, k + 1);
                }
            } else return FAILED;
            break;
        case GoingUp:
            /* 如果该电梯向上, 则只接收向上的乘客 */
            if (FloorWaitQueue[0][e->floor].WaitingPassengerNum) {
                if (DeQueue(FloorWaitQueue[0][e->floor], p) == SUCCESS) {
                    if (Push(e->Stack[p->OutFloor], p) == SUCCESS) {
                        e->CallCar[p->OutFloor] = 1;
                        e->PassengerID[e->PassengerNum++] = p->PassengerID;

                        GotoXY(10 + 30 * k, 6);
                        printf("                         ");
                        GotoXY(10 + 30 * k, 6);
                        printf(" %d号乘客成功进入电梯%d", p->PassengerID, k + 1);
                    } else printf(" %d号乘客进入电梯%d失败", p->PassengerID, k + 1);
                } else return FAILED;
            } else return FAILED;
            break;
        case IDLE:
            break;
    }

    return SUCCESS;
}

/**
 * 乘客入或出电梯
 *
 * @param[in]  e: elevator structure
 * @param[in]  k:
 * @return  none
 */
Status PassengerInOrOut(Elevator e, int k) {
    if (PassengerOut(e, k) == FAILED) {
        if (PassengerIn(e, k) == FAILED) return FAILED;

        /* 有乘客进入电梯, 重新显示等待队列 */
        DisappearWaitingPassenger(FloorWaitQueue[1][e->floor], 0, 0);
        DisappearWaitingPassenger(FloorWaitQueue[0][e->floor], 1, FloorWaitQueue[1][e->floor].WaitingPassengerNum);
        ShowWaitingPassenger(FloorWaitQueue[1][e->floor], 0, 0);
        ShowWaitingPassenger(FloorWaitQueue[0][e->floor], 1, FloorWaitQueue[1][e->floor].WaitingPassengerNum);
    }

    return SUCCESS;
}
