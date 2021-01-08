/**
 * @filename Queue.h
 * @description queue structure header file
 * @author 许继元
 * @date 2020/12/23
 */

#ifndef ELEVATORSIMULATION_QUEUE_H
#define ELEVATORSIMULATION_QUEUE_H

#include "ElevatorSimulationDefinition.h"

/* 初始化队列 */
Status InitQueue(PassengerWaitingQueueNode &Q);

/* 销毁队列 */
Status DestroyQueue(PassengerWaitingQueueNode &Q);

/* 判断队列是否为空 */
Status QueueIsEmpty(PassengerWaitingQueueNode Q);

/* 入队 */
Status EnQueue(PassengerWaitingQueueNode &Q, ElemType e);

/* 出队 */
Status DeQueue(PassengerWaitingQueueNode &Q, ElemType &e);

/* 删除队列指针p所指结点的下一个结点 */
Status DeleteNextQueueNode(PassengerWaitingQueueNode &Q, PassengerQueuePtr p);

/* 打印队列 */
Status PrintQueue(PassengerWaitingQueueNode Q);

#endif /* ELEVATORSIMULATION_QUEUE_H */
