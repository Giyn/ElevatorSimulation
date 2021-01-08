/**
 * @filename Queue.h
 * @description queue structure header file
 * @author ���Ԫ
 * @date 2020/12/23
 */

#ifndef ELEVATORSIMULATION_QUEUE_H
#define ELEVATORSIMULATION_QUEUE_H

#include "ElevatorSimulationDefinition.h"

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

/* ��ӡ���� */
Status PrintQueue(PassengerWaitingQueueNode Q);

#endif /* ELEVATORSIMULATION_QUEUE_H */
