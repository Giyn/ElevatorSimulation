/**
 * @filename Passenger.cpp
 * @description elevator simulation passenger source file
 * @author 许继元
 * @date 2020/12/23
 */

#include "../Headers/Passenger.h"

extern int MaxPassengerNum; /* 电梯的最大乘客数 */

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
