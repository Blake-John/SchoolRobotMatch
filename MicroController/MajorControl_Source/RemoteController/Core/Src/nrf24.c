//
// Created by DTS on 2024/2/24.
//

#include "nrf24.h"
#include "oled.h"

const unsigned char INIT_ADDR0[5] = {0x02, 0x3A, 0xB1, 0xB1, 0x01};
const unsigned char INIT_ADDR1[5] = {0x02, 0x3A, 0x01, 0x01, 0x01};
const unsigned char INIT_ADDR2[5] = {0x03, 0x3A, 0x01, 0x01, 0x01};
const unsigned char INIT_ADDR3[5] = {0x04, 0x3A, 0x01, 0x01, 0x01};
const unsigned char INIT_ADDR4[5] = {0x05, 0x3A, 0x01, 0x01, 0x01};
const unsigned char INIT_ADDR5[5] = {0x06, 0x3A, 0x01, 0x01, 0x01};

/**
 * @brief NRF24L01初始化程序
 */
void NRF_Init(void)
{
    {
        HAL_SPI_Init(&hspi1);
        HAL_GPIO_WritePin(NRF_CE_GPIO_PORT, NRF_CE_Pin, GPIO_PIN_RESET); //清除CE输出
        HAL_GPIO_WritePin(NRF_CSN_GPIO_PORT, NRF_CSN_PIN, GPIO_PIN_SET); //使能CSN输出
        HAL_Delay(10);
    }
}

/**
 * @brief   SPI读写函数
 * @param   Tx_Data 需要发送的数据
 */
unsigned char NRF_SPI_Send_Byte(unsigned char Tx_Data)
{
    unsigned char Rx_Data;
    HAL_SPI_TransmitReceive(&NRF_SPI_PORT, &Tx_Data, &Rx_Data, 1, 0x10);
    return (Rx_Data);
}

/**
 * @brief   NRF24L01写寄存器程序(1个字节)
 * @param   Reg_Addr    寄存器地址
 * @param   Data    需要写的数据
 */
unsigned char NRF_Write_Reg(unsigned char Reg_Addr, unsigned char Data)
{
    unsigned char status;
    HAL_GPIO_WritePin(NRF_CSN_GPIO_PORT, NRF_CSN_PIN, GPIO_PIN_RESET); // 拉低CSN，使NRF接受命令
    status = NRF_SPI_Send_Byte(Reg_Addr); // SPI发送寄存器号
    NRF_SPI_Send_Byte(Data); // SPI发送数据
    HAL_GPIO_WritePin(NRF_CSN_GPIO_PORT, NRF_CSN_PIN, GPIO_PIN_SET); // 重新拉高CSN
    return (status);
}

/**
 * @brief   NRF24L01读寄存器程序(1个字节)
 * @param   Reg_Addr    寄存器地址
 */
unsigned char NRF_Read_Reg(unsigned char Reg_Addr)
{
    unsigned char reg_value;
    HAL_GPIO_WritePin(NRF_CSN_GPIO_PORT, NRF_CSN_PIN, GPIO_PIN_RESET);
    NRF_SPI_Send_Byte(Reg_Addr); // SPI发送寄存器号
    reg_value = NRF_SPI_Send_Byte(0xFF); // 通过空操作NOP(0xFF)得到状态寄存器的值
    HAL_GPIO_WritePin(NRF_CSN_GPIO_PORT, NRF_CSN_PIN, GPIO_PIN_SET);
    return (reg_value);
}

/**
 * @brief    NRF24L01多字节写入
 * @param    Reg_Addr    寄存器地址
 * @param    pBuf    需要传输的数组的指针
 * @param    Buf_len    数据长度
 */
unsigned char NRF_Write_Buf(unsigned char Reg_Addr, unsigned char *pBuf, unsigned char Buf_len)
{
    unsigned char status;
    HAL_GPIO_WritePin(NRF_CSN_GPIO_PORT, NRF_CSN_PIN, GPIO_PIN_RESET);
    status = NRF_SPI_Send_Byte(Reg_Addr);
    HAL_SPI_Transmit(&NRF_SPI_PORT, pBuf, Buf_len, 0x10);
    HAL_GPIO_WritePin(NRF_CSN_GPIO_PORT, NRF_CSN_PIN, GPIO_PIN_SET);
    return (status);
}

/**
 * @brief   NRF24L01多字节读取
 * @param   Reg_Addr    寄存器地址
 * @param   pBuf    存放数据的数组指针
 * @param   Buf_len    数组长度
 */
unsigned char NRF_Read_Buf(unsigned char Reg_Addr, unsigned char *pBuf, unsigned char Buf_len)
{
    unsigned char status;
    HAL_GPIO_WritePin(NRF_CSN_GPIO_PORT, NRF_CSN_PIN, GPIO_PIN_RESET);
    status = NRF_SPI_Send_Byte(Reg_Addr);
    HAL_SPI_Receive(&NRF_SPI_PORT, pBuf, Buf_len, 0x10);
    HAL_GPIO_WritePin(NRF_CSN_GPIO_PORT, NRF_CSN_PIN, GPIO_PIN_SET);
    return (status);
}

/**
 * @brief   检查NRF24L01是否正常，传输5个数据，并读取，判断读写是否一致(return 0)，异常的话return 1
 */
unsigned char NRF_Check(void)
{
    unsigned char BufTx[5] = {0xA5, 0xA5, 0xA5, 0xA5, 0xA5};
    unsigned char BufRx[5];
    unsigned char i;
    NRF_Write_Buf(NRF_WRITE_REG + TX_ADDR, BufTx, 5);
    NRF_Read_Buf(TX_ADDR, BufRx, 5);
    for (i = 0; i < 5; i++)if (BufRx[i] != 0xA5)break;
    if (i != 5)
    {
//        OLED_ShowString(2, 1, "CheckFailed");
        return 1;
    }
//    OLED_ShowString(2, 1, "CheckSucceed");
    return 0;

}

/**
 * @brief    设置为发送模式
 */
void NRF_TX_Mode(void)
{
    HAL_GPIO_WritePin(NRF_CE_GPIO_PORT, NRF_CE_Pin, GPIO_PIN_RESET);
    NRF_Write_Buf(NRF_WRITE_REG + TX_ADDR, (unsigned char *) INIT_ADDR0, TX_ADR_WIDTH);
    NRF_Write_Buf(NRF_WRITE_REG + RX_ADDR_P0, (unsigned char *) INIT_ADDR0, RX_ADR_WIDTH);
    NRF_Write_Reg(NRF_WRITE_REG + EN_AA, 0x01);
    NRF_Write_Reg(NRF_WRITE_REG + EN_RXADDR, 0x01);
    NRF_Write_Reg(NRF_WRITE_REG + SETUP_RETR, 0x1A);
    NRF_Write_Reg(NRF_WRITE_REG + RF_CH, CH_NUM);
    NRF_Write_Reg(NRF_WRITE_REG + RF_SETUP, 0x0F);
    NRF_Write_Reg(NRF_WRITE_REG + CONFIG, 0x0E);
    NRF_Write_Reg(NRF_WRITE_REG + RX_PW_P0, RX_PLOAD_WIDTH);
    HAL_GPIO_WritePin(NRF_CE_GPIO_PORT, NRF_CE_Pin, GPIO_PIN_SET);
}

/**
* @brief    发送数据
*/
unsigned char NRF_TX_Packet(unsigned char *txbuf)
{
    unsigned char state;
    HAL_GPIO_WritePin(NRF_CE_GPIO_PORT, NRF_CE_Pin, GPIO_PIN_RESET);
    NRF_Write_Buf(WR_TX_PLOAD, txbuf, TX_PLOAD_WIDTH);
    HAL_GPIO_WritePin(NRF_CE_GPIO_PORT, NRF_CE_Pin, GPIO_PIN_SET);
    while (HAL_GPIO_ReadPin(NRF_IRQ_GPIO_PORT, NRF_IRQ_PIN) != 0);
    state = NRF_Read_Reg(STATUS);
    NRF_Write_Reg(NRF_WRITE_REG + STATUS, state);
    if (state & MAX_TX)
    {
        NRF_Write_Reg(FLUSH_TX, 0xFF);
        HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_SET);
        return MAX_TX;
    }
    if (state & TX_OK)
    {
        HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_RESET);
        return TX_OK;
    }
    return 0xFF;
}

