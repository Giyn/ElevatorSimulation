/**
 * @filename ElevatorSimulation.h
 * @description elevator simulation header file
 * @author ���Ԫ
 * @date 2020/12/23
 */

#ifndef ELEVATORSIMULATION_H
#define ELEVATORSIMULATION_H

/* �˿ͽṹ������ */
typedef struct PassengerNode {
    int PassengerID; /* �˿�ID */
    int InFloor; /* ����¥�� */
    int OutFloor; /* Ŀ��¥�� */
    int GiveUpTime; /* ����ʱ�� */
} *Passenger;

typedef Passenger ElemType;

/* ����״̬�� */
typedef enum {
    SUCCESS = 1,
    FAILED = 0,
    INFEASIBLE = -1,
    OVERFLOW = -2
} Status;

#endif /* ELEVATORSIMULATION_H */
