/**
 * @filename Stack.h
 * @description stack structure header file
 * @author ���Ԫ
 * @date 2020/12/23
 */

#ifndef ELEVATORSIMULATION_STACK_H
#define ELEVATORSIMULATION_STACK_H

#include "ElevatorSimulation.h"

/* �˿�ջ�ṹ������ */
typedef struct PassengerStackNode {
    ElemType *base; /* ջ��ָ�� */
    ElemType *top; /* ջ��ָ�� */
    int StackSize; /* ��ǰ�ѷ���Ĵ洢�ռ�, ��Ԫ��Ϊ��λ */
} PassengerStack;

/* ��ʼ��ջ */
Status InitStack(PassengerStack &S);

/* ����ջ */
Status DestroyStack(PassengerStack &S);

#endif /* ELEVATORSIMULATION_STACK_H */
