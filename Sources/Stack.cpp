/**
 * @filename Stack.cpp
 * @description stack structure source file
 * @author ���Ԫ
 * @date 2020/12/23
 */

#include "../Headers/Stack.h"

/**
 * ��ʼ��ջ
 *
 * @param[in]  S: passenger stack
 * @return  the operation status, SUCCESS is 1, FAILED is 0, OVERFLOW is -2
 */
Status InitStack(PassengerStack &S) {
    S.base = (ElemType *) malloc(STACK_INIT_SIZE * sizeof(ElemType));
    if (!S.base) return OVERFLOW;
    S.top = S.base;
    S.StackSize = STACK_INIT_SIZE;

    return SUCCESS;
}

/**
 * ����ջ
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

/**
 * �ж�ջ�Ƿ�Ϊ��
 *
 * @param[in]  S: passenger stack
 * @return  the operation status, SUCCESS is 1, FAILED is 0
 */
Status StackIsEmpty(PassengerStack S) {
    if (S.top == S.base) return SUCCESS;
    else return FAILED;
}

/**
 * ѹջ
 *
 * @param[in]  S: passenger stack
 * @param[in]  e: passenger stack element
 * @return  the operation status, SUCCESS is 1, FAILED is 0, OVERFLOW is -2
 */
Status PushStack(PassengerStack &S, ElemType e) {
    if (S.top - S.base >= S.StackSize) {
        S.base = (ElemType *) realloc(S.base, (S.StackSize + STACK_INCREMENT) * sizeof(ElemType));
        if (!S.base) return OVERFLOW;

        S.top = S.base + S.StackSize;
        S.StackSize += STACK_INCREMENT;
    }
    *S.top++ = e;

    return SUCCESS;
}

/**
 * ��ջ
 *
 * @param[in]  S: passenger stack
 * @param[in]  e: a variable to receive passenger stack element
 * @return  the operation status, SUCCESS is 1, FAILED is 0
 */
Status PopStack(PassengerStack &S, ElemType &e) {
    if (S.top == S.base) return FAILED;

    e = *(--S.top);

    return SUCCESS;
}
