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
 * @return  the operation status, SUCCESS is 1, FAILED is 0
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
