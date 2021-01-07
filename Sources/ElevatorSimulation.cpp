/**
 * @filename ElevatorSimulation.cpp
 * @description elevator simulation source file
 * @author 许继元
 * @date 2020/12/23
 */

#include "../Headers/ElevatorSimulation.h"

extern int CallUp[5], CallDown[5];                 /* 楼层的向上向下按钮 */
extern PassengerWaitingQueue FloorWaitQueue[2][5]; /* 每层楼有俩个等待队列, 0向上, 1向下 */

Status TimeUp(Elevator e) {
    if (e->state == IDLE && e->floor == 1) return FAILED;
    else if (e->StateTimeCount <= 0) return SUCCESS;

    return SUCCESS;
}

/**
 * 没有人进入电梯
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
 * 没有人离开电梯
 *
 * @param[in]  e: elevator structure
 * @return  the operation status, SUCCESS is 1, FAILED is 0
 */
Status NobodyOut(Elevator e) {
    /* 没有乘客坐该楼层的电梯 */
    if (!e->CallCar[e->floor]) return SUCCESS;
    else if (e->state == GoingUp && StackEmpty(e->Stack[e->floor]) == SUCCESS) return SUCCESS;
    else if (e->state == GoingDown && StackEmpty(e->Stack[e->floor]) == SUCCESS) return SUCCESS;
    else return FAILED;
}

/**
 * 没有人进出电梯
 *
 * @param[in]  e: elevator structure
 * @return  the operation status, SUCCESS is 1, FAILED is 0
 */
Status NobodyInOrOut(Elevator e) {
    if (NobodyIn(e) == SUCCESS && NobodyOut(e) == SUCCESS) return SUCCESS;
    else return FAILED;
}

/**
 * 是否要在下一层停留
 *
 * @param[in]  e: elevator structure
 * @return  the operation status, SUCCESS is 1, FAILED is 0
 */
Status StopNextFloor(Elevator e) {
    /**
     * 以下三种情况需要在下一层停留
     * 1.下一层为终点
     * 2.下一层有乘客
     * 3.下一层为目的层
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
 * 高层是否有请求, 有则返回该楼层, 没有则返回-1
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
 * 低层是否有请求, 有则返回该楼层, 没有则返回-1
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
