/**
 * @filename Queue.cpp
 * @description queue structure source file
 * @author ���Ԫ
 * @date 2020/12/23
 */

#include "../Headers/Queue.h"

/**
 * ��ʼ������
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
 * ���ٶ���
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
 * �ж϶����Ƿ�Ϊ��
 *
 * @param[in]  Q: passenger waiting queue
 * @return  the operation status, SUCCESS is 1, FAILED is 0
 */
Status QueueIsEmpty(PassengerWaitingQueueNode Q) {
    if (Q.front == Q.rear) return SUCCESS;
    else return FAILED;
}

/**
 * ���
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
 * ����
 *
 * @param[in]  Q: passenger waiting queue
 * @param[in]  e: a variable to receive passenger waiting queue element
 * @return  the operation status, SUCCESS is 1, FAILED is 0
 */
Status DeQueue(PassengerWaitingQueueNode &Q, ElemType &e) {
    if (Q.front == Q.rear) return FAILED;

    PassengerQueuePtr p;
    /* �ƹ�ͷ��� */
    p = Q.front->next;
    e = p->data;
    Q.front->next = p->next;

    if (Q.rear == p) Q.rear = Q.front;
    delete p;
    Q.WaitingPassengerNum--;

    return SUCCESS;
}

/**
 * ɾ������ָ��p��ָ������һ�����
 *
 * @param[in]  Q: passenger waiting queue
 * @param[in]  p: passenger waiting queue pointer
 * @return  the operation status, SUCCESS is 1, FAILED is 0
 */
Status DeleteNextQueueNode(PassengerWaitingQueueNode &Q, PassengerQueuePtr p) {
    if (!p || !p->next) return FAILED;

    PassengerQueuePtr q;
    PassengerQueuePtr *temp = &Q.rear;
    q = p->next;
    p->next = q->next;
    if (!p->next) *(temp) = p;
    Q.WaitingPassengerNum--;

    return SUCCESS;
}
