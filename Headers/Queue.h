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
typedef struct WaitQueueNode {
    PassengerQueuePtr front;
    PassengerQueuePtr rear;
    int WaitingPassengersNum;
} WaitQueue;

#endif /* ELEVATORSIMULATION_QUEUE_H */
