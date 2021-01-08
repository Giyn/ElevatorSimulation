/**
 * @filename ElevatorSimulation.cpp
 * @description elevator simulation source file
 * @author ���Ԫ
 * @date 2020/12/23
 */

#include "../Headers/ElevatorSimulation.h"
#include "../Headers/IO.h"

extern int CallUp[5], CallDown[5];                 /* ¥����������°�ť */
extern int MaxPassengerNum;                        /* ���ݵ����˿��� */
extern PassengerWaitingQueue FloorWaitQueue[2][5]; /* ÿ��¥�������ȴ�����, 0����, 1���� */

/**
 * ��ʱ
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

/**
 * �����ϻ������µ�����, �������һ��ĵ�������
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
 * ���������ƶ�
 *
 * @param[in]  e: elevator structure
 * @return  the operation status, SUCCESS is 1, FAILED is 0
 */
Status ElevatorMoveUp(Elevator &e) {
    int floor = HigherRequires(e);
    if (floor != -1) {
        /* ���������Ǹò����, ��ֱ�Ӵ򿪵����� */
        if (floor == e->floor) e->action = Opening;
        else {
            e->CallCar[floor] = 1;
            e->action = Accelerate;
            /* ��Ӧ�ò������ */
            CallUp[floor] = -1;
        }
        return SUCCESS;
    } else return FAILED;
}

/**
 * ���������ƶ�
 *
 * @param[in]  e: elevator structure
 * @return  the operation status, SUCCESS is 1, FAILED is 0
 */
Status ElevatorMoveDown(Elevator &e) {
    int floor = LowerRequires(e);
    if (floor != -1) {
        /* ���������Ǹò����, ��ֱ�Ӵ򿪵����� */
        if (e->floor == floor) e->action = Opening;
        else {
            e->CallCar[floor] = 1;
            e->action = Accelerate;
            /* ��Ӧ�ò������ */
            CallDown[floor] = -1;
        }
        return SUCCESS;
    } else return FAILED;
}

/**
 * �ı���ݵĶ���
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
            /* ���û���˽������ߵ��������ﵽ����, ����� */
            if (NobodyInOrOut(e) == SUCCESS || e->PassengerNum == MaxPassengerNum) {
                e->action = Closing;
                e->StateTimeCount = DoorTime;
            } else e->StateTimeCount = CloseTestTime;
            break;
        case Closing:
            if (NobodyInOrOut(e) == SUCCESS) e->action = Closed;
                /* ��������ڼ����˽���, ���� */
            else if (e->PassengerNum < MaxPassengerNum) {
                e->action = Opening;
                e->StateTimeCount = DoorTime;
            }
            break;
        case Closed:
            /* ������ɺ��ж���Ҫ�����ƶ����������ƶ�����ֹͣ */
            if (e->state == GoingUp) {
                /* �����Ӧ�¼� */
                if (CallUp[e->floor] == -1) CallUp[e->floor] = 0;
                int j;
                /* �ж��Ƿ���Ҫ�������� */
                for (j = e->floor; j <= MaxFloor; j++) {
                    /* ����ϲ���Ŀ��¥��, ����Ҫ���� */
                    if (e->CallCar[j] == 1) {
                        e->action = Accelerate;
                        e->StateTimeCount = AccelerateTime;
                        break;
                    }
                }/* ˵��û�����ϵ�Ŀ��¥�� */
                if (j > MaxFloor) {
                    e->action = Waiting;
                    e->state = IDLE;
                }
            } else if (e->state == GoingDown) {
                /* �����Ӧ�¼� */
                if (-1 == CallDown[e->floor]) CallDown[e->floor] = 0;
                int j;
                /* ���и��׵�Ŀ��¥��, �������� */
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
            /* ����ʱ����½�ʱ�䲻һ��, Ҫ���ֿ� */
            if (e->state == GoingUp) e->StateTimeCount = UpTime;
            else e->StateTimeCount = DownTime;
            break;
        case Moving: /* ����ƶ� */
            /* �������������ʾ���� */
            DisappearElevatorBody(e, k, e->floor);
            if (e->state == GoingUp) {
                e->floor++;
                if (SUCCESS == StopNextFloor(e)) {
                    e->action = Decelerate;
                    e->StateTimeCount = UpSlowTime;
                }/* ����������� */
                else e->StateTimeCount = UpTime;
            } else if (GoingDown == e->state) {
                e->floor--;
                if (SUCCESS == StopNextFloor(e)) {
                    e->action = Decelerate;
                    e->StateTimeCount = DownSlowTime;
                }/* ��������½� */
                else e->StateTimeCount = DownTime;
            }
            ShowElevatorBody(e, k, e->floor);
            break;
        case Decelerate:
            /* ����ò�, ��յ����ڵ�Ŀ��¥���־λ */
            e->CallCar[e->floor] = 0;
            /* �ж��Ƿ���Ҫת�䷽�� */
            if (e->state == GoingUp) {
                int need = 1;
                /* ��û����Ŀ���������ı䷽�� */
                for (int j = e->floor; j < MaxFloor; j++) {
                    if (e->CallCar[j] == 1) {
                        need = 0;
                        break;
                    }
                }
                /* ����ı䷽��, �жϸ߲��Ƿ�������, ���û��, �ı䷽�� */
                if (need == 1 && HigherRequires(e) == -1) e->state = GoingDown;;
            } else if (e->state = GoingDown) {
                int need = 1;
                /* û�ﵽ���Ŀ���������ı䷽�� */
                for (int j = e->floor; j > MinFloor; j--) {
                    if (1 == e->CallCar[j]) {
                        need = 0;
                        break;
                    }
                }
                /* ����, �����Ͳ㻹û��Ӧ�ı�״̬ */
                if (need == 1 && LowerRequires(e) == -1) e->state = GoingUp;
            }
            e->action = Opening;
            e->StateTimeCount = DoorTime;
            break;
        case Waiting: /* �ȴ�״̬��Control����������һ�ж����ж� */
            break;
    }
}

/**
 * ͨ�����Ļ���, �Ե��ݽ��е���, �����˷���Դ
 *
 * @param[in]  E: elevator structure array
 * @return  none
 */
void Controller(Elevator E[]) {
    for (int i = 0; i <= 2; i++) {
        /* ���i�ŵ���λ�ڵȴ�״̬ */
        if (E[i]->action == Waiting) {
            /* ������������µ��ݵĻ��� */
            int floor;
            /* ����ڱ����г˿�, ֱ�ӿ��� */
            if (CallUp[E[i]->floor] == 1) {
                E[i]->action = Opening;
                CallUp[E[i]->floor] = -1;
                E[i]->state = GoingUp;
            } else if (CallDown[E[0]->floor] == 1) {
                E[i]->action = Opening;
                CallDown[E[i]->floor] = -1;
                E[i]->state = GoingDown;
            }
                /* �����ҵ����������¥�� */
            else {
                floor = HasUpOrDownRequires(E[i]);
                /* û�г˿���Ӧ */
                if (floor < 0 || floor > MaxFloor) return;
                else if (1 == CallUp[floor]) {
                    /* ���������˶� */
                    if (floor >= E[i]->floor) {
                        E[i]->action = Accelerate;
                        E[i]->CallCar[floor] = 1;
                        /* ����¥����Ӧ��־ */
                        CallUp[floor] = -1;
                        E[i]->state = GoingUp;
                    } else {
                        E[i]->action = Accelerate;
                        E[i]->CallCar[floor] = 1;
                        /* ����¥����Ӧ��־ */
                        CallUp[floor] = -1;
                        E[i]->state = GoingDown;
                    }
                } else if (CallDown[floor] == 1) {
                    /* ���������˶� */
                    if (floor >= E[i]->floor) {
                        E[i]->action = Accelerate;
                        E[i]->CallCar[floor] = 1;
                        /* ����¥����Ӧ��־ */
                        CallDown[floor] = -1;
                        E[i]->state = GoingUp;
                    } else {
                        E[i]->action = Accelerate;
                        E[i]->CallCar[floor] = 1;
                        /* ����¥����Ӧ��־ */
                        CallDown[floor] = -1;
                        E[i]->state = GoingDown;
                    }
                }
            }
        }
    }
}
