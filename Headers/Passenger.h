/**
 * @filename Passenger.h
 * @description elevator simulation passenger header file
 * @author 许继元
 * @date 2020/12/23
 */

#ifndef ELEVATORSIMULATION_PASSENGER_H
#define ELEVATORSIMULATION_PASSENGER_H

#include "ElevatorSimulationDefinition.h"

/* 乘客出电梯 */
Status PassengerOut(Elevator &e, int k);

/* 乘客入电梯 */
Status PassengerIn(Elevator &e, int k);

/* 乘客入或出电梯 */
Status PassengerInOrOut(Elevator e, int k);

/* 乘客是否放弃搭乘电梯 */
Status PassengerGiveUp(PassengerWaitingQueue &Q, Elevator E[], int floor);

/* 生成一个新的乘客 */
void NewPassenger();

#endif /* ELEVATORSIMULATION_PASSENGER_H */
