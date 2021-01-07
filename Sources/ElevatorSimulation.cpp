/**
 * @filename ElevatorSimulation.cpp
 * @description elevator simulation source file
 * @author Ðí¼ÌÔª
 * @date 2020/12/23
 */

#include "../Headers/ElevatorSimulation.h"

Status TimeUp(Elevator e) {
    if (e->state == IDLE && e->floor == 1) return FAILED;
    else if (e->StateTimeCount <= 0) return SUCCESS;

    return SUCCESS;
}
