/**
 * @filename Stack.h
 * @description stack structure header file
 * @author 许继元
 * @date 2020/12/23
 */

#ifndef ELEVATORSIMULATION_STACK_H
#define ELEVATORSIMULATION_STACK_H

#include "ElevatorSimulation.h"

/* 乘客栈结构体类型 */
typedef struct PassengerStackNode {
    ElemType *base; /* 栈底指针 */
    ElemType *top; /* 栈顶指针 */
    int StackSize; /* 当前已分配的存储空间, 以元素为单位 */
} PassengerStack;

/* 初始化栈 */
Status InitStack(PassengerStack &S);

/* 销毁栈 */
Status DestroyStack(PassengerStack &S);

#endif /* ELEVATORSIMULATION_STACK_H */
