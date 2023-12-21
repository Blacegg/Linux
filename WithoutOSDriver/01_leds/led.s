.global _start  @全局标号

_start:

    /* 
     * 打开时钟
     * LED0 连接的是 GPIO1_IO03, 其时钟是在 CCM_CCGR1 的 bit27-26
     */
    ldr r0, =0X020C406C     @给 r0 赋值 CCM_CCGR1 的地址
    ldr r1, =0x00ff0000     @给 r1 赋值，开启 GPIO1_IO03 的时钟
    str r1, [r0]            @将 r1 的值写入地址为 r0 的空间

    /* 复用 GPIO1_IO03 为 GPIO 功能 */
    ldr r0, =0x020e0068     @给 r0 赋值 IOMUXC_SW_MUL_CTL_PAD_GPIO1_IO03 的地址
    ldr r1, =0x00000005     @给 r1 赋值，复用为 GPIO
    str r1, [r0]            @将 r1 的值写入地址为 r0 的空间

    /*
     * 配置 GPIO1_IO03
     */
    ldr r0, =0x020e02f4     @给 r0 赋值 IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO03 的地址
    ldr r1, =0x000010b0     @给 r1 赋值，设置 IO 口的功能
    str r1, [r0]            @将 r1 的值写入地址为 r0 的空间
    
    ldr r0, =0x0209c004     @给 r0 赋值 GPIO1_GDIR 的地址
    ldr r1, =0x00000008     @设置 GPIO1_IO3 为输出模式
    str r1, [r0]            @将 r1 的值写入地址为 r0 的空间

    ldr r0, =0x0209c000     @给 r0 赋值 GPIO1_DR 的地址
    ldr r1, =0              @设置 GPIO1_IO3 为输出低电平
    str r1, [r0]            @将 r1 的值写入地址为 r0 的空间

loop:
    b loop 
    
