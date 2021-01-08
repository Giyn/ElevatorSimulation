/**
 * @filename ElevatorSimulationDefinition.h
 * @description elevator simulation definition
 * @author ���Ԫ
 * @date 2020/12/23
 */

#ifndef ELEVATORSIMULATIONDEFINITION_H
#define ELEVATORSIMULATIONDEFINITION_H

/* ʹ�����ռ�std�ڶ�������б�ʶ������Ч */
using namespace std;

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <cstdio>

#define CloseTestTime  40  /* ���ݹ��Ų���ʱ��, ���˽���ʱ, ����ÿ��40t����һ��, �����˽���, ����� */
#define AccelerateTime 15  /* ����ʱ�� */
#define UpTime         51  /* ����ʱ�� */
#define DownTime       61  /* �½�ʱ�� */
#define UpSlowTime     14  /* �������� */
#define DownSlowTime   23  /* �½����� */
#define DoorTime       20  /* ���Ź���ʱ��, ���źͿ��Ÿ���Ҫ20t */
#define MaxGiveUpTime  300 /* �˿������ʱ�� */
#define MaxInterTime   100 /* ��һ���˿���ĳ���ʱ�� */
#define InOutTime      25  /* ��������ʱ��, ÿ���˽������ݾ���Ҫ25t */
#define OverTime       300 /* ����ͣ��ʱʱ��, ���������ĳ�㾲ֹʱ�䳬��300t, �򷵻�1����� */

#define MaxFloor       4  /* ��߲� */
#define MinFloor       0  /* ��Ͳ� */
#define FloorHeight    3  /* ¥��߶� */
#define LeftElevatorX  6  /* ��ߵ��ݵ�x��ʼ���� */
#define LeftElevatorY  12 /* ��ߵ��ݵ�y��ʼ���� */
#define RightElevatorX 62 /* �ұߵ��ݵ�x��ʼ���� */
#define RightElevatorY 12 /* �ұߵ��ݵ�y��ʼ���� */

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

/* �˿�ջ�ṹ������ */
typedef struct PassengerStackNode {
    ElemType *base; /* ջ��ָ�� */
    ElemType *top; /* ջ��ָ�� */
    int StackSize; /* ��ǰ�ѷ���Ĵ洢�ռ�, ��Ԫ��Ϊ��λ */
} PassengerStack;

/* �˿Ͷ��нṹ������ */
typedef struct PassengerQueueNode {
    Passenger data;
    PassengerQueueNode *next;
} *PassengerQueuePtr;

/* �˿͵ȴ����нṹ������ */
typedef struct PassengerWaitingQueueNode {
    PassengerQueuePtr front;
    PassengerQueuePtr rear;
    int WaitingPassengerNum;
} PassengerWaitingQueue;

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

#endif /* ELEVATORSIMULATION_ELEVATORSIMULATIONDEFINITION_H */
