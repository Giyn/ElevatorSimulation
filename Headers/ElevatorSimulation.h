/**
 * @filename ElevatorSimulation.h
 * @description elevator simulation header file
 * @author 许继元
 * @date 2020/12/23
 */

#ifndef ELEVATORSIMULATION_H
#define ELEVATORSIMULATION_H

#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include "Queue.h"
#include "Stack.h"

/* 使命名空间std内定义的所有标识符都有效 */
using namespace std;

#define STACK_INIT_SIZE 8 /* 存储空间初始分配量 */
#define STACK_INCREMENT 5 /* 存储空间分配增量 */

/* 乘客结构体类型 */
typedef struct PassengerNode {
    int PassengerID; /* 乘客ID */
    int InFloor;     /* 进入楼层 */
    int OutFloor;    /* 目标楼层 */
    int GiveUpTime;  /* 放弃时间 */
} *Passenger;

typedef Passenger ElemType;

/* 电梯的8种动作 */
enum ElevatorAction {
    Opening,Opened,
    Closing,Closed,
    Waiting,
    Moving,
    Decelerate,
    Accelerate
};

/* 电梯运行状态 */
enum ElevatorState {
    GoingUp,
    GoingDown,
    IDLE
};

/* 电梯结构体类型 */
typedef struct ElevatorNode {
    int PassengerNum;        /* 乘客数量 */
    int PassengerID[8];      /* 存储电梯内的乘客编号 */
    int StateTimeCount;      /* 当前状态的计时 */
    int floor;               /* 当前所在的楼层 */
    int CallCar[5];          /* 目标楼层数据 */
    PassengerStack Stack[5]; /* 乘客栈结构 */
    ElevatorState state;     /* 电梯状态 */
    ElevatorAction action;   /* 当前电梯的动作 */
} *Elevator;

/* 操作状态码 */
typedef enum {
    SUCCESS = 1,
    FAILED = 0,
    INFEASIBLE = -1,
    OVERFLOW = -2
} Status;

Status TimeUp(Elevator e);

/* 没有人进入电梯 */
Status NobodyIn(Elevator e);

/* 没有人离开电梯 */
Status NobodyOut(Elevator e);

#endif /* ELEVATORSIMULATION_H */
