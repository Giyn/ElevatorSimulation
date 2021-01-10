/**
 * @filename Passenger.cpp
 * @description elevator simulation passenger source file
 * @author 许继元
 * @date 2020/12/23
 */

#include "../Headers/Passenger.h"
#include "../Headers/Stack.h"
#include "../Headers/Queue.h"
#include "../Headers/IO.h"

extern int MaxPassengerNum;                        /* 电梯的最大乘客数 */
extern int TotalPassenger;                         /* 总乘客数 */
extern int NextInterTime;                          /* 下一个乘客进入系统的时间 */
extern int CallUp[5], CallDown[5];                 /* 楼层的向上向下按钮 */
extern PassengerWaitingQueue FloorWaitQueue[2][5]; /* 每层楼有2个等待队列, 0向上, 1向下 */

/**
 * 乘客出电梯
 *
 * @param[in]  e: elevator structure
 * @param[in]  k:
 * @return  the operation status, SUCCESS is 1, FAILED is 0
 */
Status PassengerOut(Elevator &e, int k) {
    Passenger p;
    int i, j;
    /* 乘客出栈, 每出去一个乘客需要等待25t */
    if (StackIsEmpty(e->Stack[e->floor]) != SUCCESS) {
        PopStack(e->Stack[e->floor], p);
        for (i = 0; i < MaxPassengerNum; i++) {
            if (e->PassengerID[i] == p->PassengerID) break;
        }
        e->PassengerNum--;

        /* 覆盖乘客ID数组的数据 */
        for (j = i; j < 7; j++) e->PassengerID[j] = e->PassengerID[j + 1];
        GotoXY(10 + 30 * k, 6);
        printf("                         ");
        GotoXY(10 + 30 * k, 6);
        printf(" %d号乘客出电梯 %d", p->PassengerID, k + 1);
        free(p);

        return SUCCESS;
    } else return FAILED;
}

/**
 * 乘客入电梯
 *
 * @param[in]  e: elevator structure
 * @param[in]  k:
 * @return  the operation status, SUCCESS is 1, FAILED is 0
 */
Status PassengerIn(Elevator &e, int k) {
    Passenger p;
    if (e->PassengerNum >= 8) return FAILED;
    switch (e->state) {
        /* 如果该电梯向下, 则只接收向下的乘客 */
        case GoingDown:
            if (FloorWaitQueue[1][e->floor].WaitingPassengerNum) {
                if (DeQueue(FloorWaitQueue[1][e->floor], p) == SUCCESS) {
                    if (PushStack(e->Stack[p->OutFloor], p) == SUCCESS) {
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
                    if (PushStack(e->Stack[p->OutFloor], p) == SUCCESS) {
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
 * @return  the operation status, SUCCESS is 1, FAILED is 0
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

/**
 * 乘客是否放弃搭乘电梯
 *
 * @param[in]  Q    : passenger waiting queue
 * @param[in]  E    : elevator structure array
 * @param[in]  floor: current floor
 * @return  the operation status, SUCCESS is 1, FAILED is 0
 */
Status PassengerGiveUp(PassengerWaitingQueue &Q, Elevator E[], int floor) {
    Passenger node;
    PassengerQueuePtr p = Q.front;

    if (Q.WaitingPassengerNum <= 0) return FAILED;
    else if (Q.front->next) node = Q.front->next->data;
    else return FAILED;

    /* 如果忍耐时间到了并且该层没有电梯 */
    if (node && node->GiveUpTime <= 0 && E[0]->floor != floor && E[1]->floor != floor) {
        GotoXY(10 + 30, 6);
        printf("                         ");
        GotoXY(10 + 30, 6);
        printf(" %d号乘客放弃搭乘电梯\n", node->PassengerID);

        /* 乘客放弃搭乘电梯, 则更新当前正在等待的乘客 */
        DisappearWaitingPassenger(FloorWaitQueue[1][floor], 0, 0);
        DisappearWaitingPassenger(FloorWaitQueue[0][floor], 1, FloorWaitQueue[1][floor].WaitingPassengerNum);
        DeleteNextQueueNode(Q, p);
        ShowWaitingPassenger(FloorWaitQueue[1][floor], 0, 0);
        ShowWaitingPassenger(FloorWaitQueue[0][floor], 1, FloorWaitQueue[1][floor].WaitingPassengerNum);
    } else node->GiveUpTime--;

    return SUCCESS;
}

/**
 * 生成一个新的乘客
 *
 * @param[in]  none
 * @return  none
 */
void NewPassenger() {
    Passenger p;
    p = (Passenger) malloc(sizeof(PassengerNode));
    srand((unsigned) time(NULL));

    p->PassengerID = TotalPassenger++;
    p->GiveUpTime = rand() % MaxGiveUpTime; /* 忍耐时间 */
    /* 忍耐时间在50t-300t之间 */
    while (p->GiveUpTime <= 50) p->GiveUpTime = rand() % MaxGiveUpTime;
    p->InFloor = rand() * 11 % (MaxFloor + 1); /* 当前所在楼层 */
    p->OutFloor = rand() * 17 % (MaxFloor + 1); /* 目标楼层 */

    /* 如果目标楼层与当前所在楼层相同, 则重新生成 */
    while (p->OutFloor == p->InFloor) p->OutFloor = rand() % MaxFloor;

    NextInterTime = rand() % MaxInterTime;
    /* 下一乘客出现的时间在5t-120t之间 */
    while (NextInterTime < 5) NextInterTime = rand() % MaxInterTime;

    /* 先判断其是向上还是先下, 接着更新队列显示, 乘客入队 */
    if (p->InFloor > p->OutFloor) {
        DisappearWaitingPassenger(FloorWaitQueue[1][p->InFloor], 0, 0);
        DisappearWaitingPassenger(FloorWaitQueue[0][p->InFloor], 1, FloorWaitQueue[1][p->InFloor].WaitingPassengerNum);

        /* 进入等待队列  */
        EnQueue(FloorWaitQueue[1][p->InFloor], p);
        /* 按下该层的电梯按钮 */
        if (CallDown[p->InFloor] != -1) CallDown[p->InFloor] = 1;

        ShowWaitingPassenger(FloorWaitQueue[1][p->InFloor], 0, 0);
        ShowWaitingPassenger(FloorWaitQueue[0][p->InFloor], 1, FloorWaitQueue[1][p->InFloor].WaitingPassengerNum);
    } else {
        DisappearWaitingPassenger(FloorWaitQueue[1][p->InFloor], 0, 0);
        DisappearWaitingPassenger(FloorWaitQueue[0][p->InFloor], 1, FloorWaitQueue[1][p->InFloor].WaitingPassengerNum);

        /* 进入等待队列  */
        EnQueue(FloorWaitQueue[0][p->InFloor], p);
        /* 按下该层的电梯按钮 */
        if (CallUp[p->InFloor] != -1) CallUp[p->InFloor] = 1;

        ShowWaitingPassenger(FloorWaitQueue[1][p->InFloor], 0, 0);
        ShowWaitingPassenger(FloorWaitQueue[0][p->InFloor], 1, FloorWaitQueue[1][p->InFloor].WaitingPassengerNum);
    }
}
