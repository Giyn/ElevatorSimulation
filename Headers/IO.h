/**
 * @filename IO.h
 * @description elevator simulation input and output header file
 * @author 许继元
 * @date 2020/12/23
 */

#ifndef ELEVATORSIMULATION_IO_H
#define ELEVATORSIMULATION_IO_H

#include "ElevatorSimulation.h";

/* 定位控制台的光标位置 */
void GotoXY(short x, short y);

/* 打印字符串内容 */
void Print(string content, WORD color);

/* 清除电梯结构 */
void DisappearElevatorBody(Elevator e, int k, int x);

/* 显示电梯结构 */
void ShowElevatorBody(Elevator e, int k, int x);

#endif /* ELEVATORSIMULATION_IO_H */