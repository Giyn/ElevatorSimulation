/**
 * @filename Stack.h
 * @description stack structure header file
 * @author ���Ԫ
 * @date 2020/12/23
 */

#ifndef ELEVATORSIMULATION_STACK_H
#define ELEVATORSIMULATION_STACK_H

#include "ElevatorSimulationDefinition.h"

/* ��ʼ��ջ */
Status InitStack(PassengerStack &S);

/* ����ջ */
Status DestroyStack(PassengerStack &S);

/* �ж�ջ�Ƿ�Ϊ�� */
Status StackIsEmpty(PassengerStack S);

/* ѹջ */
Status PushStack(PassengerStack &S, ElemType e);

/* ��ջ */
Status PopStack(PassengerStack &S, ElemType &e);

#endif /* ELEVATORSIMULATION_STACK_H */
