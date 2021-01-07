/**
 * @filename Stack.h
 * @description stack structure header file
 * @author 许继元
 * @date 2020/12/23
 */

#include <stdlib.h>
#include "../Headers/Stack.h"

/**
 * 初始化栈
 *
 * @param[in]  S: passenger stack
 * @return  the operation status, SUCCESS is 1, FAILED is 0
 */
Status InitStack(PassengerStack &S) {
    S.base = (ElemType *) malloc(STACK_INIT_SIZE * sizeof(ElemType));
    if (!S.base) return OVERFLOW;
    S.top = S.base;
    S.StackSize = STACK_INIT_SIZE;

    return SUCCESS;
}

/**
 * 销毁栈
 *
 * @param[in]  S: passenger stack
 * @return  the operation status, SUCCESS is 1, FAILED is 0
 */
Status DestroyStack(PassengerStack &S) {
    if (!S.base) return FAILED;
    else {
        ElemType *p;
        for (p = S.base; p < S.top; p++) free(S.base);
    }
    return SUCCESS;
}
