/**
 * @filename ElevatorSimulation.h
 * @description elevator simulation header file
 * @author ���Ԫ
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

/* ʹ�����ռ�std�ڶ�������б�ʶ������Ч */
using namespace std;

#define STACK_INIT_SIZE 8 /* �洢�ռ��ʼ������ */
#define STACK_INCREMENT 5 /* �洢�ռ�������� */

#define CloseTestTime  40  /* ���ݹ��Ų���ʱ��, ���˽���ʱ, ����ÿ��40t����һ��, �����˽���, ����� */
#define AccelerateTime 15  /* ����ʱ�� */
#define UpTime         51  /* ����ʱ�� */
#define DownTime       61  /* �½�ʱ�� */
#define UpSlowTime     14  /* �������� */
#define DownSlowTime   23  /* �½����� */
#define DoorTime       20  /* ���Ź���ʱ��, ���źͿ��Ÿ���Ҫ20t */

#define MaxFloor 4        /* ��߲� */
#define MinFloor 0        /* ��Ͳ� */
#define FloorHeight 3     /* ¥��߶� */
#define LeftElevatorX  6  /* ��ߵ��ݵ�x��ʼ���� */
#define LeftElevatorY  12 /* ��ߵ��ݵ�y��ʼ���� */
#define RightElevatorX 62 /* �ұߵ��ݵ�x��ʼ���� */
#define RightElevatorY 12 /* �ұߵ��ݵ�y��ʼ���� */

/* �˿ͽṹ������ */
typedef struct PassengerNode {
    int PassengerID; /* �˿�ID */
    int InFloor;     /* ����¥�� */
    int OutFloor;    /* Ŀ��¥�� */
    int GiveUpTime;  /* ����ʱ�� */
} *Passenger;

typedef Passenger ElemType;

/* ���ݵ�8�ֶ��� */
enum ElevatorAction {
    Opening, Opened,
    Closing, Closed,
    Waiting,
    Moving,
    Decelerate,
    Accelerate
};

/* ��������״̬ */
enum ElevatorState {
    GoingUp,
    GoingDown,
    IDLE
};

/* ���ݽṹ������ */
typedef struct ElevatorNode {
    int PassengerNum;        /* �˿����� */
    int PassengerID[8];      /* �洢�����ڵĳ˿ͱ�� */
    int StateTimeCount;      /* ��ǰ״̬�ļ�ʱ */
    int floor;               /* ��ǰ���ڵ�¥�� */
    int CallCar[5];          /* Ŀ��¥������ */
    PassengerStack Stack[5]; /* �˿�ջ�ṹ */
    ElevatorState state;     /* ����״̬ */
    ElevatorAction action;   /* ��ǰ���ݵĶ��� */
} *Elevator;

/* ����״̬�� */
typedef enum {
    SUCCESS = 1,
    FAILED = 0,
    INFEASIBLE = -1,
    OVERFLOW = -2
} Status;

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

#endif /* ELEVATORSIMULATION_H */
