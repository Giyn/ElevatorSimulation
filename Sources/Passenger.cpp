/**
 * @filename Passenger.cpp
 * @description elevator simulation passenger source file
 * @author ���Ԫ
 * @date 2020/12/23
 */

#include "../Headers/Passenger.h"

extern int MaxPassengerNum;                        /* ���ݵ����˿��� */
extern PassengerWaitingQueue FloorWaitQueue[2][5]; /* ÿ��¥��2���ȴ�����, 0����, 1���� */

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

/**
 * �˿������
 *
 * @param[in]  e: elevator structure
 * @param[in]  k:
 * @return  none
 */
Status PassengerIn(Elevator &e, int k) {
    Passenger p;
    if (e->PassengerNum >= 8) return FAILED;
    switch (e->state) {
        /* ����õ�������, ��ֻ�������µĳ˿� */
        case GoingDown:
            if (FloorWaitQueue[1][e->floor].WaitingPassengerNum) {
                if (DeQueue(FloorWaitQueue[1][e->floor], p) == SUCCESS) {
                    if (Push(e->Stack[p->OutFloor], p) == SUCCESS) {
                        e->CallCar[p->OutFloor] = 1;
                        e->PassengerID[e->PassengerNum++] = p->PassengerID;

                        GotoXY(10 + 30 * k, 6);
                        printf("                         ");
                        GotoXY(10 + 30 * k, 6);
                        printf(" %d�ų˿ͳɹ��������%d", p->PassengerID, k + 1);
                    } else printf(" %d�ų˿ͽ������%dʧ��", p->PassengerID, k + 1);
                }
            } else return FAILED;
            break;
        case GoingUp:
            /* ����õ�������, ��ֻ�������ϵĳ˿� */
            if (FloorWaitQueue[0][e->floor].WaitingPassengerNum) {
                if (DeQueue(FloorWaitQueue[0][e->floor], p) == SUCCESS) {
                    if (Push(e->Stack[p->OutFloor], p) == SUCCESS) {
                        e->CallCar[p->OutFloor] = 1;
                        e->PassengerID[e->PassengerNum++] = p->PassengerID;

                        GotoXY(10 + 30 * k, 6);
                        printf("                         ");
                        GotoXY(10 + 30 * k, 6);
                        printf(" %d�ų˿ͳɹ��������%d", p->PassengerID, k + 1);
                    } else printf(" %d�ų˿ͽ������%dʧ��", p->PassengerID, k + 1);
                } else return FAILED;
            } else return FAILED;
            break;
        case IDLE:
            break;
    }

    return SUCCESS;
}

/**
 * �˿���������
 *
 * @param[in]  e: elevator structure
 * @param[in]  k:
 * @return  none
 */
Status PassengerInOrOut(Elevator e, int k) {
    if (PassengerOut(e, k) == FAILED) {
        if (PassengerIn(e, k) == FAILED) return FAILED;

        /* �г˿ͽ������, ������ʾ�ȴ����� */
        DisappearWaitingPassenger(FloorWaitQueue[1][e->floor], 0, 0);
        DisappearWaitingPassenger(FloorWaitQueue[0][e->floor], 1, FloorWaitQueue[1][e->floor].WaitingPassengerNum);
        ShowWaitingPassenger(FloorWaitQueue[1][e->floor], 0, 0);
        ShowWaitingPassenger(FloorWaitQueue[0][e->floor], 1, FloorWaitQueue[1][e->floor].WaitingPassengerNum);
    }

    return SUCCESS;
}
