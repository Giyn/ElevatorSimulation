/**
 * @filename ElevatorSimulation.h
 * @description elevator simulation header file
 * @author ���Ԫ
 * @date 2020/12/23
 */

#ifndef ELEVATORSIMULATION_H
#define ELEVATORSIMULATION_H

#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include "Queue.h"
#include "Stack.h"

/* ʹ�����ռ�std�ڶ�������б�ʶ������Ч */
using namespace std;

#define STACK_INIT_SIZE 8 /* �洢�ռ��ʼ������ */
#define STACK_INCREMENT 5 /* �洢�ռ�������� */

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
    Opening,Opened,
    Closing,Closed,
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

#endif /* ELEVATORSIMULATION_H */
