/**
 * @filename ElevatorSimulation.h
 * @description elevator simulation header file
 * @author 许继元
 * @date 2020/12/23
 */

#ifndef ELEVATORSIMULATION_H
#define ELEVATORSIMULATION_H

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <windows.h>

#include "Queue.h"
#include "Stack.h"

/* 使命名空间std内定义的所有标识符都有效 */
using namespace std;

#define STACK_INIT_SIZE 8 /* 存储空间初始分配量 */
#define STACK_INCREMENT 5 /* 存储空间分配增量 */

#define CloseTestTime  40  /* 电梯关门测试时间, 有人进出时, 电梯每隔40t测试一次, 若无人进出, 则关门 */
#define AccelerateTime 15  /* 加速时间 */
#define UpTime         51  /* 上升时间 */
#define DownTime       61  /* 下降时间 */
#define UpSlowTime     14  /* 上升减速 */
#define DownSlowTime   23  /* 下降减速 */
#define DoorTime       20  /* 开门关门时间, 关门和开门各需要20t */

#define MaxFloor 4        /* 最高层 */
#define MinFloor 0        /* 最低层 */
#define FloorHeight 3     /* 楼层高度 */
#define LeftElevatorX  6  /* 左边电梯的x起始坐标 */
#define LeftElevatorY  12 /* 左边电梯的y起始坐标 */
#define RightElevatorX 62 /* 右边电梯的x起始坐标 */
#define RightElevatorY 12 /* 右边电梯的y起始坐标 */

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

Status TimeUp(Elevator e);

/* 没有人进入电梯 */
Status NobodyIn(Elevator e);

/* 没有人离开电梯 */
Status NobodyOut(Elevator e);

/* 没有人进出电梯 */
Status NobodyInOrOut(Elevator e);

/* 是否要在下一层停留 */
Status StopNextFloor(Elevator e);

/* 高层请求的楼层数 */
int HigherRequires(Elevator e);

/* 低层请求的楼层数 */
int LowerRequires(Elevator e);

/* 返回最近一层的电梯请求 */
int HasUpOrDownRequires(Elevator e);

/* 电梯向上移动 */
Status ElevatorMoveUp(Elevator &e);

/* 电梯向下移动 */
Status ElevatorMoveDown(Elevator &e);

/* 改变电梯的动作 */
void ChangeElevatorAction(Elevator e, int k);

/* 对电梯进行调度 */
void Controller(Elevator E[]);

#endif /* ELEVATORSIMULATION_H */
