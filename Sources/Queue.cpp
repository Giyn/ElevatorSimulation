/**
 * @filename Queue.cpp
 * @description queue structure source file
 * @author 许继元
 * @date 2020/12/23
 */

#include "../Headers/Queue.h"

/**
 * 初始化队列
 *
 * @param[in]  Q: passenger waiting queue
 * @return  the operation status, SUCCESS is 1, FAILED is 0, OVERFLOW is -2
 */
Status InitQueue(PassengerWaitingQueueNode &Q) {
    Q.front = Q.rear = new PassengerQueueNode;
    if (!Q.front) return OVERFLOW;

    Q.front->next = NULL;
    Q.front->data = NULL;
    Q.WaitingPassengerNum = 0;

    return SUCCESS;
}

/**
 * 销毁队列
 *
 * @param[in]  Q: passenger waiting queue
 * @return  the operation status, SUCCESS is 1, FAILED is 0
 */
Status DestroyQueue(PassengerWaitingQueueNode &Q) {
    while (Q.front) {
        Q.rear = Q.front->next;
        if (Q.front->data) free(Q.front->data);
        delete Q.front;
        Q.front = Q.rear;
    }

    return SUCCESS;
}

/**
 * 入队
 *
 * @param[in]  Q: passenger waiting queue
 * @param[in]  e: passenger waiting queue element that to be inserted
 * @return  the operation status, SUCCESS is 1, FAILED is 0, OVERFLOW is -2
 */
Status EnQueue(PassengerWaitingQueueNode &Q, ElemType e) {
    PassengerQueuePtr p;
    p = new PassengerQueueNode;
    if (!p) return OVERFLOW;

    p->data = e;
    p->next = NULL;
    Q.rear->next = p;
    Q.rear = p;
    Q.WaitingPassengerNum++;

    return SUCCESS;
}

/**
 * 出队
 *
 * @param[in]  Q: passenger waiting queue
 * @param[in]  e: a variable to receive passenger waiting queue element
 * @return  the operation status, SUCCESS is 1, FAILED is 0
 */
Status DeQueue(PassengerWaitingQueueNode &Q, ElemType &e) {
    if (Q.front == Q.rear) return FAILED;

    PassengerQueuePtr p;
    /* 绕过头结点 */
    p = Q.front->next;
    e = p->data;
    Q.front->next = p->next;

    if (Q.rear == p) Q.rear = Q.front;
    delete p;
    Q.WaitingPassengerNum--;

    return SUCCESS;
}
