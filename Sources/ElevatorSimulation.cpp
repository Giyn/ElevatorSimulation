/**
 * @filename ElevatorSimulation.cpp
 * @description elevator simulation source file
 * @author ���Ԫ
 * @date 2020/12/23
 */

#include "../Headers/ElevatorSimulation.h"

extern PassengerWaitingQueue FloorWaitQueue[2][5];            //ÿ��¥�������ȴ����У�0����,1����

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
