/**
 * @filename Queue.h
 * @description queue structure header file
 * @author 许继元
 * @date 2020/12/23
 */

#ifndef ELEVATORSIMULATION_QUEUE_H
#define ELEVATORSIMULATION_QUEUE_H

#include "ElevatorSimulation.h"

/* 乘客队列结构体类型 */
typedef struct PassengerQueueNode {
    Passenger data;
    PassengerQueueNode *next;
} *PassengerQueuePtr;

/* 乘客等待队列结构体类型 */
typedef struct WaitQueueNode {
    PassengerQueuePtr front;
    PassengerQueuePtr rear;
    int WaitingPassengersNum;
} WaitQueue;

#endif /* ELEVATORSIMULATION_QUEUE_H */
