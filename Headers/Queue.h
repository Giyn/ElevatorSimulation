/**
 * @filename Queue.h
 * @description queue structure header file
 * @author ���Ԫ
 * @date 2020/12/23
 */

#ifndef ELEVATORSIMULATION_QUEUE_H
#define ELEVATORSIMULATION_QUEUE_H

#include "ElevatorSimulation.h"

/* �˿Ͷ��нṹ������ */
typedef struct PassengerQueueNode {
    Passenger data;
    PassengerQueueNode *next;
} *PassengerQueuePtr;

/* �˿͵ȴ����нṹ������ */
typedef struct PassengerWaitingQueueNode {
    PassengerQueuePtr front;
    PassengerQueuePtr rear;
    int WaitingPassengerNum;
} PassengerWaitingQueueNode;

/* ��ʼ������ */
Status InitQueue(PassengerWaitingQueueNode &Q);

/* ���ٶ��� */
Status DestroyQueue(PassengerWaitingQueueNode &Q);

/* �ж϶����Ƿ�Ϊ�� */
Status QueueIsEmpty(PassengerWaitingQueueNode Q);

/* ��� */
Status EnQueue(PassengerWaitingQueueNode &Q, ElemType e);

/* ���� */
Status DeQueue(PassengerWaitingQueueNode &Q, ElemType &e);

/* ɾ������ָ��p��ָ������һ����� */
Status DeleteNextQueueNode(PassengerWaitingQueueNode &Q, PassengerQueuePtr p);

#endif /* ELEVATORSIMULATION_QUEUE_H */
