#include "bsp_beep.h"

/*
 * @description : ��ʼ����������Ӧ�� IO
 * @param : ��
 * @return : ��
 */
void beep_init(void)
{
    /* 1����ʼ�� IO ���ã�����Ϊ GPIO5_IO01 */
    IOMUXC_SetPinMux(IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01, 0);
    /* 2������ GPIO1_IO03 �� IO ���� */
    IOMUXC_SetPinConfig(IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01, 0X10B0);
    /* 3����ʼ�� GPIO,GPIO5_IO01 ����Ϊ��� */
    GPIO5->GDIR |= (1 << 1);
    /* 4������ GPIO5_IO01 ����ߵ�ƽ���رշ����� */
    GPIO5->DR |= (1 << 1);

    GPIO_Pin_Config_t beep_config;
    beep_config.Direction = kGPIO_DigitalOutput;
    beep_config.OutputLogic = 1;
    GPIO_Init(GPIO5, 1, &beep_config);
}

/*
 * @description : ���������ƺ��������Ʒ������򿪻��ǹر�
 * @param - status : 0���رշ�������1 �򿪷�����
 * @return : ��
 */
void beep_switch(int status)
{
    // if (status == ON)
    //     GPIO5->DR &= ~(1 << 1); /* �򿪷����� */
    // else if (status == OFF)
    //     GPIO5->DR |= (1 << 1); /* �رշ����� */
    GPIO_PinWrite(GPIO5, 1, status);
}
