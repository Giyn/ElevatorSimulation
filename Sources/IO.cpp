/**
 * @filename IO.cpp
 * @description elevator simulation input and output
 * @author 许继元
 * @date 2020/12/23
 */

#include "../Headers/ElevatorSimulation.h"

/**
 * 定位控制台的光标位置
 *
 * @param[in]  x: x coordinate
 * @param[in]  y: y coordinate
 * @return  none
 */
void GotoXY(short x, short y) {
    COORD coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
