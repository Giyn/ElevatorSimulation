/**
 * @filename ElevatorSimulation.cpp
 * @description elevator simulation source file
 * @author ���Ԫ
 * @date 2020/12/23
 */

#include "../Headers/ElevatorSimulation.h"

extern int CallUp[5], CallDown[5];                 /* ¥����������°�ť */
extern PassengerWaitingQueue FloorWaitQueue[2][5]; /* ÿ��¥�������ȴ�����, 0����, 1���� */

Status TimeUp(Elevator e) {
    if (e->state == IDLE && e->floor == 1) return FAILED;
    else if (e->StateTimeCount <= 0) return SUCCESS;

    return SUCCESS;
}

/**
 * û���˽������
 *
 * @param[in]  e: elevator structure
 * @return  the operation status, SUCCESS is 1, FAILED is 0
 */
Status NobodyIn(Elevator e) {
    if (e->state == GoingUp && FloorWaitQueue[0][e->floor].WaitingPassengerNum == 0) return SUCCESS;
    else if (e->state == GoingDown && FloorWaitQueue[1][e->floor].WaitingPassengerNum == 0) return SUCCESS;
    else return FAILED;
}

/**
 * û�����뿪����
 *
 * @param[in]  e: elevator structure
 * @return  the operation status, SUCCESS is 1, FAILED is 0
 */
Status NobodyOut(Elevator e) {
    /* û�г˿�����¥��ĵ��� */
    if (!e->CallCar[e->floor]) return SUCCESS;
    else if (e->state == GoingUp && StackEmpty(e->Stack[e->floor]) == SUCCESS) return SUCCESS;
    else if (e->state == GoingDown && StackEmpty(e->Stack[e->floor]) == SUCCESS) return SUCCESS;
    else return FAILED;
}

/**
 * û���˽�������
 *
 * @param[in]  e: elevator structure
 * @return  the operation status, SUCCESS is 1, FAILED is 0
 */
Status NobodyInOrOut(Elevator e) {
    if (NobodyIn(e) == SUCCESS && NobodyOut(e) == SUCCESS) return SUCCESS;
    else return FAILED;
}

/**
 * �Ƿ�Ҫ����һ��ͣ��
 *
 * @param[in]  e: elevator structure
 * @return  the operation status, SUCCESS is 1, FAILED is 0
 */
Status StopNextFloor(Elevator e) {
    /**
     * �������������Ҫ����һ��ͣ��
     * 1.��һ��Ϊ�յ�
     * 2.��һ���г˿�
     * 3.��һ��ΪĿ�Ĳ�
     */
    if (e->state == GoingUp) {
        if (e->floor == MaxFloor) return SUCCESS;
        else if (CallUp[e->floor] == 1) return SUCCESS;
        else if (e->CallCar[e->floor] == 1) return SUCCESS;
        else return FAILED;
    } else {
        if (e->floor == MinFloor) return SUCCESS;
        else if (CallDown[e->floor] == 1) return SUCCESS;
        else if (e->CallCar[e->floor] == 1) return SUCCESS;
        else return FAILED;
    }
}

/**
 * �߲��Ƿ�������, ���򷵻ظ�¥��, û���򷵻�-1
 *
 * @param[in]  e: elevator structure
 * @return  the floor number or -1
 */
int HigherRequires(Elevator e) {
    int floor;
    for (floor = e->floor; floor <= MaxFloor; floor++) {
        if (CallUp[floor]) return floor;
    }

    return -1;
}

/**
 * �Ͳ��Ƿ�������, ���򷵻ظ�¥��, û���򷵻�-1
 *
 * @param[in]  e: elevator structure
 * @return  the floor number or -1
 */
int LowerRequires(Elevator e) {
    int floor;
    for (floor = e->floor; floor >= MinFloor; floor--) {
        if (CallDown[floor]) return floor;
    }

    return -1;
}
