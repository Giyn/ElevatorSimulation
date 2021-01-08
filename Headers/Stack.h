/**
 * @filename Stack.h
 * @description stack structure header file
 * @author Ðí¼ÌÔª
 * @date 2020/12/23
 */

#ifndef ELEVATORSIMULATION_STACK_H
#define ELEVATORSIMULATION_STACK_H

#include "ElevatorSimulationDefinition.h"

/* ³õÊ¼»¯Õ» */
Status InitStack(PassengerStack &S);

/* Ïú»ÙÕ» */
Status DestroyStack(PassengerStack &S);

/* ÅÐ¶ÏÕ»ÊÇ·ñÎª¿Õ */
Status StackIsEmpty(PassengerStack S);

/* Ñ¹Õ» */
Status PushStack(PassengerStack &S, ElemType e);

/* µ¯Õ» */
Status PopStack(PassengerStack &S, ElemType &e);

#endif /* ELEVATORSIMULATION_STACK_H */
