/**
 * @filename ElevatorSimulation.cpp
 * @description elevator simulation source file
 * @author 许继元
 * @date 2020/12/23
 */

#include "../Headers/ElevatorSimulation.h"
#include "../Headers/IO.h"

extern int CallUp[5], CallDown[5];                 /* 楼层的向上向下按钮 */
extern int MaxPassengerNum;                        /* 电梯的最大乘客数 */
extern PassengerWaitingQueue FloorWaitQueue[2][5]; /* 每层楼有俩个等待队列, 0向上, 1向下 */

/**
 * 计时
 *
 * @param[in]  e: elevator structure
 * @return  the operation status, SUCCESS is 1, FAILED is 0
 */
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

/**
 * 有向上或者向下的请求, 返回最近一层的电梯请求
 *
 * @param[in]  e: elevator structure
 * @return  the elevator request
 */
int HasUpOrDownRequires(Elevator e) {
    int i, j;
    for (j = e->floor - 1, i = e->floor + 1; j >= 0 || i <= MaxFloor; j--, i++) {
        if (j >= 0 && (CallDown[j] == 1 || CallUp[j] == 1)) return j;
        if (i <= MaxFloor && (CallDown[i] == 1 || CallUp[i] == 1)) return i;
    }

    return 0;
}

/**
 * 电梯向上移动
 *
 * @param[in]  e: elevator structure
 * @return  the operation status, SUCCESS is 1, FAILED is 0
 */
Status ElevatorMoveUp(Elevator &e) {
    int floor = HigherRequires(e);
    if (floor != -1) {
        /* 如果请求的是该层电梯, 则直接打开电梯门 */
        if (floor == e->floor) e->action = Opening;
        else {
            e->CallCar[floor] = 1;
            e->action = Accelerate;
            /* 响应该层的请求 */
            CallUp[floor] = -1;
        }
        return SUCCESS;
    } else return FAILED;
}

/**
 * 电梯向下移动
 *
 * @param[in]  e: elevator structure
 * @return  the operation status, SUCCESS is 1, FAILED is 0
 */
Status ElevatorMoveDown(Elevator &e) {
    int floor = LowerRequires(e);
    if (floor != -1) {
        /* 如果请求的是该层电梯, 则直接打开电梯门 */
        if (e->floor == floor) e->action = Opening;
        else {
            e->CallCar[floor] = 1;
            e->action = Accelerate;
            /* 响应该层的请求 */
            CallDown[floor] = -1;
        }
        return SUCCESS;
    } else return FAILED;
}

/**
 * 改变电梯的动作
 *
 * @param[in]  e: elevator structure
 * @param[in]  k:
 * @return  none
 */
void ChangeElevatorAction(Elevator e, int k) {
    switch (e->action) {
        case Opening:
            e->action = Opened;
            e->StateTimeCount = CloseTestTime;
            break;
        case Opened:
            /* 如果没有人进出或者电梯人数达到上限, 则关门 */
            if (NobodyInOrOut(e) == SUCCESS || e->PassengerNum == MaxPassengerNum) {
                e->action = Closing;
                e->StateTimeCount = DoorTime;
            } else e->StateTimeCount = CloseTestTime;
            break;
        case Closing:
            if (NobodyInOrOut(e) == SUCCESS) e->action = Closed;
                /* 如果关门期间有人进入, 则开门 */
            else if (e->PassengerNum < MaxPassengerNum) {
                e->action = Opening;
                e->StateTimeCount = DoorTime;
            }
            break;
        case Closed:
            /* 关门完成后判断是要向上移动还是向下移动还是停止 */
            if (e->state == GoingUp) {
                /* 清空响应事件 */
                if (CallUp[e->floor] == -1) CallUp[e->floor] = 0;
                int j;
                /* 判断是否需要继续往上 */
                for (j = e->floor; j <= MaxFloor; j++) {
                    /* 如果上层有目标楼层, 则需要往上 */
                    if (e->CallCar[j] == 1) {
                        e->action = Accelerate;
                        e->StateTimeCount = AccelerateTime;
                        break;
                    }
                }/* 说明没有往上的目标楼层 */
                if (j > MaxFloor) {
                    e->action = Waiting;
                    e->state = IDLE;
                }
            } else if (e->state == GoingDown) {
                /* 清空响应事件 */
                if (-1 == CallDown[e->floor]) CallDown[e->floor] = 0;
                int j;
                /* 还有更底的目标楼层, 加速启动 */
                for (j = e->floor; j >= 0; j--) {
                    if (1 == e->CallCar[j]) {
                        e->action = Accelerate;
                        e->StateTimeCount = AccelerateTime;
                        break;
                    }
                }
                if (j < MinFloor) {
                    e->action = Waiting;
                    e->state = IDLE;
                }
            } else e->action = Waiting;
            break;
        case Accelerate:
            e->action = Moving;
            /* 上升时间跟下降时间不一样, 要区分开 */
            if (e->state == GoingUp) e->StateTimeCount = UpTime;
            else e->StateTimeCount = DownTime;
            break;
        case Moving: /* 完成移动 */
            /* 先清除电梯再显示电梯 */
            DisappearElevatorBody(e, k, e->floor);
            if (e->state == GoingUp) {
                e->floor++;
                if (SUCCESS == StopNextFloor(e)) {
                    e->action = Decelerate;
                    e->StateTimeCount = UpSlowTime;
                }/* 否则继续上升 */
                else e->StateTimeCount = UpTime;
            } else if (GoingDown == e->state) {
                e->floor--;
                if (SUCCESS == StopNextFloor(e)) {
                    e->action = Decelerate;
                    e->StateTimeCount = DownSlowTime;
                }/* 否则继续下降 */
                else e->StateTimeCount = DownTime;
            }
            ShowElevatorBody(e, k, e->floor);
            break;
        case Decelerate:
            /* 到达该层, 清空电梯内的目的楼层标志位 */
            e->CallCar[e->floor] = 0;
            /* 判断是否需要转变方向 */
            if (e->state == GoingUp) {
                int need = 1;
                /* 还没到达目标层则无需改变方向 */
                for (int j = e->floor; j < MaxFloor; j++) {
                    if (e->CallCar[j] == 1) {
                        need = 0;
                        break;
                    }
                }
                /* 否则改变方向, 判断高层是否有请求, 如果没有, 改变方向 */
                if (need == 1 && HigherRequires(e) == -1) e->state = GoingDown;;
            } else if (e->state = GoingDown) {
                int need = 1;
                /* 没达到最低目标层则无需改变方向 */
                for (int j = e->floor; j > MinFloor; j--) {
                    if (1 == e->CallCar[j]) {
                        need = 0;
                        break;
                    }
                }
                /* 否则, 如若低层还没响应改变状态 */
                if (need == 1 && LowerRequires(e) == -1) e->state = GoingUp;
            }
            e->action = Opening;
            e->StateTimeCount = DoorTime;
            break;
        case Waiting: /* 等待状态有Control函数进行下一行动的判断 */
            break;
    }
}

/**
 * 通过锁的机制, 对电梯进行调度, 避免浪费资源
 *
 * @param[in]  E: elevator structure array
 * @return  none
 */
void Controller(Elevator E[]) {
    for (int i = 0; i <= 2; i++) {
        /* 如果i号电梯位于等待状态 */
        if (E[i]->action == Waiting) {
            /* 计算最近的上下电梯的花费 */
            int floor;
            /* 如果在本层有乘客, 直接开门 */
            if (CallUp[E[i]->floor] == 1) {
                E[i]->action = Opening;
                CallUp[E[i]->floor] = -1;
                E[i]->state = GoingUp;
            } else if (CallDown[E[0]->floor] == 1) {
                E[i]->action = Opening;
                CallDown[E[i]->floor] = -1;
                E[i]->state = GoingDown;
            }
                /* 否则找到最近的请求楼层 */
            else {
                floor = HasUpOrDownRequires(E[i]);
                /* 没有乘客响应 */
                if (floor < 0 || floor > MaxFloor) return;
                else if (1 == CallUp[floor]) {
                    /* 电梯向上运动 */
                    if (floor >= E[i]->floor) {
                        E[i]->action = Accelerate;
                        E[i]->CallCar[floor] = 1;
                        /* 设置楼层响应标志 */
                        CallUp[floor] = -1;
                        E[i]->state = GoingUp;
                    } else {
                        E[i]->action = Accelerate;
                        E[i]->CallCar[floor] = 1;
                        /* 设置楼层响应标志 */
                        CallUp[floor] = -1;
                        E[i]->state = GoingDown;
                    }
                } else if (CallDown[floor] == 1) {
                    /* 电梯向上运动 */
                    if (floor >= E[i]->floor) {
                        E[i]->action = Accelerate;
                        E[i]->CallCar[floor] = 1;
                        /* 设置楼层响应标志 */
                        CallDown[floor] = -1;
                        E[i]->state = GoingUp;
                    } else {
                        E[i]->action = Accelerate;
                        E[i]->CallCar[floor] = 1;
                        /* 设置楼层响应标志 */
                        CallDown[floor] = -1;
                        E[i]->state = GoingDown;
                    }
                }
            }
        }
    }
}
