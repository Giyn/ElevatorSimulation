/**
 * @filename ElevatorSimulation.h
 * @description elevator simulation header file
 * @author ���Ԫ
 * @date 2020/12/23
 */

#ifndef ELEVATORSIMULATION_H
#define ELEVATORSIMULATION_H

#include "ElevatorSimulationDefinition.h"

/* �жϸö�����ʱ�������Ƿ��� */
Status TimeUp(Elevator e);

/* û���˽������ */
Status NobodyIn(Elevator e);

/* û�����뿪���� */
Status NobodyOut(Elevator e);

/* û���˽������� */
Status NobodyInOrOut(Elevator e);

/* �Ƿ�Ҫ����һ��ͣ�� */
Status StopNextFloor(Elevator e);

/* �߲������¥���� */
int HigherRequires(Elevator e);

/* �Ͳ������¥���� */
int LowerRequires(Elevator e);

/* �������һ��ĵ������� */
int HasUpOrDownRequires(Elevator e);

/* ���������ƶ� */
Status ElevatorMoveUp(Elevator &e);

/* ���������ƶ� */
Status ElevatorMoveDown(Elevator &e);

/* �ı���ݵĶ��� */
void ChangeElevatorAction(Elevator e, int k);

/* �Ե��ݽ��е��� */
void Controller(Elevator E[]);

/* ���˿��Ƿ������˵��� */
void CheckGiveUp(Elevator E[]);

/* ��ʼ������ */
void InitElevator(Elevator *E, int num);

#endif /* ELEVATORSIMULATION_H */
