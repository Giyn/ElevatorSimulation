/**
 * @filename ElevatorSimulation.h
 * @description elevator simulation header file
 * @author 许继元
 * @date 2020/12/23
 */

#ifndef ELEVATORSIMULATION_H
#define ELEVATORSIMULATION_H

#include <stdlib.h>

/* 使命名空间std内定义的所有标识符都有效 */
using namespace std;

#define STACK_INIT_SIZE 8 /* 存储空间初始分配量 */
#define STACK_INCREMENT  5 /* 存储空间分配增量 */

/* 乘客结构体类型 */
typedef struct PassengerNode {
    int PassengerID; /* 乘客ID */
    int InFloor; /* 进入楼层 */
    int OutFloor; /* 目标楼层 */
    int GiveUpTime; /* 放弃时间 */
} *Passenger;

typedef Passenger ElemType;

/* 操作状态码 */
typedef enum {
    SUCCESS = 1,
    FAILED = 0,
    INFEASIBLE = -1,
    OVERFLOW = -2
} Status;

#endif /* ELEVATORSIMULATION_H */
