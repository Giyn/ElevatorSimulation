/**
 * @filename ElevatorSimulation.h
 * @description elevator simulation header file
 * @author 许继元
 * @date 2020/12/23
 */

#ifndef ELEVATORSIMULATION_H
#define ELEVATORSIMULATION_H

#include "ElevatorSimulationDefinition.h"

/* 判断该动作的时间周期是否到了 */
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

/* 检测乘客是否放弃搭乘电梯 */
void CheckGiveUp(Elevator E[]);

/* 初始化电梯 */
void InitElevator(Elevator *E, int num);

#endif /* ELEVATORSIMULATION_H */
