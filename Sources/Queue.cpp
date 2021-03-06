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
Status InitQueue(PassengerWaitingQueue &Q) {
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
Status DestroyQueue(PassengerWaitingQueue &Q) {
    while (Q.front) {
        Q.rear = Q.front->next;
        if (Q.front->data) free(Q.front->data);
        delete Q.front;
        Q.front = Q.rear;
    }

    return SUCCESS;
}

/**
 * 判断队列是否为空
 *
 * @param[in]  Q: passenger waiting queue
 * @return  the operation status, SUCCESS is 1, FAILED is 0
 */
Status QueueIsEmpty(PassengerWaitingQueue Q) {
    if (Q.front == Q.rear) return SUCCESS;
    else return FAILED;
}

/**
 * 入队
 *
 * @param[in]  Q: passenger waiting queue
 * @param[in]  e: passenger waiting queue element that to be inserted
 * @return  the operation status, SUCCESS is 1, FAILED is 0, OVERFLOW is -2
 */
Status EnQueue(PassengerWaitingQueue &Q, ElemType e) {
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
Status DeQueue(PassengerWaitingQueue &Q, ElemType &e) {
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

/**
 * 删除队列指针p所指结点的下一个结点
 *
 * @param[in]  Q: passenger waiting queue
 * @param[in]  p: passenger waiting queue pointer
 * @return  the operation status, SUCCESS is 1, FAILED is 0
 */
Status DeleteNextQueueNode(PassengerWaitingQueue &Q, PassengerQueuePtr p) {
    if (!p || !p->next) return FAILED;

    PassengerQueuePtr q;
    PassengerQueuePtr *temp = &Q.rear;
    q = p->next;
    p->next = q->next;

    if (!p->next) *(temp) = p;
    Q.WaitingPassengerNum--;

    return SUCCESS;
}

/**
 * 打印队列
 *
 * @param[in]  Q: passenger waiting queue
 * @return  the operation status, SUCCESS is 1, FAILED is 0
 */
Status PrintQueue(PassengerWaitingQueue Q) {
    int count = 0;

    if (!Q.front->next) goto end; /* 如果队列为空, 跳转到end */

    PassengerQueuePtr q;
    q = Q.front->next;

    while (q) {
        cout << setw(3) << q->data->PassengerID << ' ';
        q = q->next;
        count++;
    }
    end:
    while (count++ <= 4) cout << "    "; /* 输出空格补全占位, 每次占3个字符位 */

    return SUCCESS;
}
