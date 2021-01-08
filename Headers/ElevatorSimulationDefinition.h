/**
 * @filename ElevatorSimulationDefinition.h
 * @description elevator simulation definition
 * @author 许继元
 * @date 2020/12/23
 */

#ifndef ELEVATORSIMULATIONDEFINITION_H
#define ELEVATORSIMULATIONDEFINITION_H

/* 使命名空间std内定义的所有标识符都有效 */
using namespace std;

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <cstdio>

#define CloseTestTime  40  /* 电梯关门测试时间, 有人进出时, 电梯每隔40t测试一次, 若无人进出, 则关门 */
#define AccelerateTime 15  /* 加速时间 */
#define UpTime         51  /* 上升时间 */
#define DownTime       61  /* 下降时间 */
#define UpSlowTime     14  /* 上升减速 */
#define DownSlowTime   23  /* 下降减速 */
#define DoorTime       20  /* 开门关门时间, 关门和开门各需要20t */
#define MaxGiveUpTime  300 /* 乘客最长忍耐时间 */
#define MaxInterTime   100 /* 下一个乘客最长的出现时间 */
#define InOutTime      25  /* 进出电梯时间, 每个人进出电梯均需要25t */
#define OverTime       300 /* 电梯停候超时时间, 如果电梯在某层静止时间超过300t, 则返回1层候命 */

#define MaxFloor       4  /* 最高层 */
#define MinFloor       0  /* 最低层 */
#define FloorHeight    3  /* 楼层高度 */
#define LeftElevatorX  6  /* 左边电梯的x起始坐标 */
#define LeftElevatorY  12 /* 左边电梯的y起始坐标 */
#define RightElevatorX 62 /* 右边电梯的x起始坐标 */
#define RightElevatorY 12 /* 右边电梯的y起始坐标 */

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

/* 乘客栈结构体类型 */
typedef struct PassengerStackNode {
    ElemType *base; /* 栈底指针 */
    ElemType *top; /* 栈顶指针 */
    int StackSize; /* 当前已分配的存储空间, 以元素为单位 */
} PassengerStack;

/* 乘客队列结构体类型 */
typedef struct PassengerQueueNode {
    Passenger data;
    PassengerQueueNode *next;
} *PassengerQueuePtr;

/* 乘客等待队列结构体类型 */
typedef struct PassengerWaitingQueueNode {
    PassengerQueuePtr front;
    PassengerQueuePtr rear;
    int WaitingPassengerNum;
} PassengerWaitingQueue;

/* 电梯的8种动作 */
enum ElevatorAction {
    Opening, Opened,
    Closing, Closed,
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

#endif /* ELEVATORSIMULATION_ELEVATORSIMULATIONDEFINITION_H */
