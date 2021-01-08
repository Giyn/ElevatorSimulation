/**
 * @filename Passenger.cpp
 * @description elevator simulation passenger source file
 * @author ���Ԫ
 * @date 2020/12/23
 */

#include "../Headers/Passenger.h"

extern int MaxPassengerNum; /* ���ݵ����˿��� */

/**
 * �˿ͳ�����
 *
 * @param[in]  e: elevator structure
 * @param[in]  k:
 * @return  none
 */
Status PassengerOut(Elevator &e, int k) {
    Passenger p;
    int i, j;
    /* �˿ͳ�ջ, ÿ��ȥһ���˿���Ҫ�ȴ�25t */
    if (StackEmpty(e->Stack[e->floor]) != SUCCESS) {
        Pop(e->Stack[e->floor], p);
        for (i = 0; i < MaxPassengerNum; i++) {
            if (e->PassengerID[i] == p->PassengerID) break;
        }
        e->PassengerNum--;

        /* ���ǳ˿�ID��������� */
        for (j = i; j < 7; j++) e->PassengerID[j] = e->PassengerID[j + 1];
        GotoXY(10 + 30 * k, 6);
        printf("                         ");
        GotoXY(10 + 30 * k, 6);
        printf(" %d�˿ͳ����� %d", p->PassengerID, k + 1);
        free(p);

        return SUCCESS;
    } else return FAILED;
}
