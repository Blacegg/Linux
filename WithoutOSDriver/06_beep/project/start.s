.global _start /* 全局标号 */

_start:
    /* 进入SVC模式 */
    mrs r0, cpsr @ 将cpsr寄存器（程序状态寄存器）的值取到r0中
    bic r0, r0, #0x1f @ 将r0（第二个）的0-4位清除，放到r0（第一个）中
    orr r0, r0, #0x13 @ 将r0或上0x13，结果放在r0中，即进入SVC模式
    msr cpsr, r0 @ 将r0的值取到cpsr寄存器中

    ldr sp ,=0x80200000 @ 设置堆栈指针
    b main @ 跳转到main函数


