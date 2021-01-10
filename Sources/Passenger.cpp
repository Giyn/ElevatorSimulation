/**
 * @filename Passenger.cpp
 * @description elevator simulation passenger source file
 * @author ���Ԫ
 * @date 2020/12/23
 */

#include "../Headers/Passenger.h"
#include "../Headers/Stack.h"
#include "../Headers/Queue.h"
#include "../Headers/IO.h"

extern int MaxPassengerNum;                        /* ���ݵ����˿��� */
extern int TotalPassenger;                         /* �ܳ˿��� */
extern int NextInterTime;                          /* ��һ���˿ͽ���ϵͳ��ʱ�� */
extern int CallUp[5], CallDown[5];                 /* ¥����������°�ť */
extern PassengerWaitingQueue FloorWaitQueue[2][5]; /* ÿ��¥��2���ȴ�����, 0����, 1���� */

/**
 * �˿ͳ�����
 *
 * @param[in]  e: elevator structure
 * @param[in]  k:
 * @return  the operation status, SUCCESS is 1, FAILED is 0
 */
Status PassengerOut(Elevator &e, int k) {
    Passenger p;
    int i, j;
    /* �˿ͳ�ջ, ÿ��ȥһ���˿���Ҫ�ȴ�25t */
    if (StackIsEmpty(e->Stack[e->floor]) != SUCCESS) {
        PopStack(e->Stack[e->floor], p);
        for (i = 0; i < MaxPassengerNum; i++) {
            if (e->PassengerID[i] == p->PassengerID) break;
        }
        e->PassengerNum--;

        /* ���ǳ˿�ID��������� */
        for (j = i; j < 7; j++) e->PassengerID[j] = e->PassengerID[j + 1];
        GotoXY(10 + 30 * k, 6);
        printf("                         ");
        GotoXY(10 + 30 * k, 6);
        printf(" %d�ų˿ͳ����� %d", p->PassengerID, k + 1);
        free(p);

        return SUCCESS;
    } else return FAILED;
}

/**
 * �˿������
 *
 * @param[in]  e: elevator structure
 * @param[in]  k:
 * @return  the operation status, SUCCESS is 1, FAILED is 0
 */
Status PassengerIn(Elevator &e, int k) {
    Passenger p;
    if (e->PassengerNum >= 8) return FAILED;
    switch (e->state) {
        /* ����õ�������, ��ֻ�������µĳ˿� */
        case GoingDown:
            if (FloorWaitQueue[1][e->floor].WaitingPassengerNum) {
                if (DeQueue(FloorWaitQueue[1][e->floor], p) == SUCCESS) {
                    if (PushStack(e->Stack[p->OutFloor], p) == SUCCESS) {
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
                    if (PushStack(e->Stack[p->OutFloor], p) == SUCCESS) {
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
 * @return  the operation status, SUCCESS is 1, FAILED is 0
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

/**
 * �˿��Ƿ������˵���
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

    /* �������ʱ�䵽�˲��Ҹò�û�е��� */
    if (node && node->GiveUpTime <= 0 && E[0]->floor != floor && E[1]->floor != floor) {
        GotoXY(10 + 30, 6);
        printf("                         ");
        GotoXY(10 + 30, 6);
        printf(" %d�ų˿ͷ�����˵���\n", node->PassengerID);

        /* �˿ͷ�����˵���, ����µ�ǰ���ڵȴ��ĳ˿� */
        DisappearWaitingPassenger(FloorWaitQueue[1][floor], 0, 0);
        DisappearWaitingPassenger(FloorWaitQueue[0][floor], 1, FloorWaitQueue[1][floor].WaitingPassengerNum);
        DeleteNextQueueNode(Q, p);
        ShowWaitingPassenger(FloorWaitQueue[1][floor], 0, 0);
        ShowWaitingPassenger(FloorWaitQueue[0][floor], 1, FloorWaitQueue[1][floor].WaitingPassengerNum);
    } else node->GiveUpTime--;

    return SUCCESS;
}

/**
 * ����һ���µĳ˿�
 *
 * @param[in]  none
 * @return  none
 */
void NewPassenger() {
    Passenger p;
    p = (Passenger) malloc(sizeof(PassengerNode));
    srand((unsigned) time(NULL));

    p->PassengerID = TotalPassenger++;
    p->GiveUpTime = rand() % MaxGiveUpTime; /* ����ʱ�� */
    /* ����ʱ����50t-300t֮�� */
    while (p->GiveUpTime <= 50) p->GiveUpTime = rand() % MaxGiveUpTime;
    p->InFloor = rand() * 11 % (MaxFloor + 1); /* ��ǰ����¥�� */
    p->OutFloor = rand() * 17 % (MaxFloor + 1); /* Ŀ��¥�� */

    /* ���Ŀ��¥���뵱ǰ����¥����ͬ, ���������� */
    while (p->OutFloor == p->InFloor) p->OutFloor = rand() % MaxFloor;

    NextInterTime = rand() % MaxInterTime;
    /* ��һ�˿ͳ��ֵ�ʱ����5t-120t֮�� */
    while (NextInterTime < 5) NextInterTime = rand() % MaxInterTime;

    /* ���ж��������ϻ�������, ���Ÿ��¶�����ʾ, �˿���� */
    if (p->InFloor > p->OutFloor) {
        DisappearWaitingPassenger(FloorWaitQueue[1][p->InFloor], 0, 0);
        DisappearWaitingPassenger(FloorWaitQueue[0][p->InFloor], 1, FloorWaitQueue[1][p->InFloor].WaitingPassengerNum);

        /* ����ȴ�����  */
        EnQueue(FloorWaitQueue[1][p->InFloor], p);
        /* ���¸ò�ĵ��ݰ�ť */
        if (CallDown[p->InFloor] != -1) CallDown[p->InFloor] = 1;

        ShowWaitingPassenger(FloorWaitQueue[1][p->InFloor], 0, 0);
        ShowWaitingPassenger(FloorWaitQueue[0][p->InFloor], 1, FloorWaitQueue[1][p->InFloor].WaitingPassengerNum);
    } else {
        DisappearWaitingPassenger(FloorWaitQueue[1][p->InFloor], 0, 0);
        DisappearWaitingPassenger(FloorWaitQueue[0][p->InFloor], 1, FloorWaitQueue[1][p->InFloor].WaitingPassengerNum);

        /* ����ȴ�����  */
        EnQueue(FloorWaitQueue[0][p->InFloor], p);
        /* ���¸ò�ĵ��ݰ�ť */
        if (CallUp[p->InFloor] != -1) CallUp[p->InFloor] = 1;

        ShowWaitingPassenger(FloorWaitQueue[1][p->InFloor], 0, 0);
        ShowWaitingPassenger(FloorWaitQueue[0][p->InFloor], 1, FloorWaitQueue[1][p->InFloor].WaitingPassengerNum);
    }
}
