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
typedef struct PassengerWaitingQueueNode {
    PassengerQueuePtr front;
    PassengerQueuePtr rear;
    int WaitingPassengerNum;
} PassengerWaitingQueueNode;

/* 初始化队列 */
Status InitQueue(PassengerWaitingQueueNode &Q);

/* 销毁队列 */
Status DestroyQueue(PassengerWaitingQueueNode &Q);

/* 入队 */
Status EnQueue(PassengerWaitingQueueNode &Q, ElemType e);

#endif /* ELEVATORSIMULATION_QUEUE_H */
