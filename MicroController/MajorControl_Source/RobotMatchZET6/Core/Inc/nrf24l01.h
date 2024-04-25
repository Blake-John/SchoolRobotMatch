//
// Created by DTS on 2024/3/8.
//

#ifndef ROBOTMATCHZET6_NRF24L01_H
#define ROBOTMATCHZET6_NRF24L01_H

#include "stm32f1xx_hal.h"
#include "spi.h"
#include "main.h"

#define TX_ADR_WIDTH    5
#define RX_ADR_WIDTH    5
#define TX_PLOAD_WIDTH  32
#define RX_PLOAD_WIDTH  32
#define MAX_TIME_INTO_IDEL    10
#define CH_NUM  86
extern unsigned char idel_mode_flag;
extern unsigned char mode_time_counter;

#define NRF_SPI_PORT hspi1
#define NRF_IRQ_PIN GPIO_PIN_4
#define NRF_IRQ_GPIO_PORT GPIOA
#define NRF_CE_Pin GPIO_PIN_4
#define NRF_CE_GPIO_PORT GPIOC
#define NRF_CSN_PIN GPIO_PIN_5
#define NRF_CSN_GPIO_PORT GPIOC
//
//NRF24L01寄存器操作命令
#define NRF_READ_REG    0x00  //读配置寄存器,低5位为寄存器地址
#define NRF_WRITE_REG   0x20  //写配置寄存器,低5位为寄存器地址
#define RD_RX_PLOAD     0x61  //读RX有效数据,1~32字节
#define FLUSH_RX        0xE2  //清除RX FIFO寄存器.接收模式下用
#define REUSE_TX_PL     0xE3  //重新使用上一包数据,CE为高,数据包被不断发送.
#define NOP             0xFF  //空操作,可以用来读状态寄存器
//SPI(NRF24L01)寄存器地址
#define CONFIG          0x00  //配置寄存器地址;bit0:1接收模式,0发射模式;bit1:电选择;bit2:CRC模式;bit3:CRC使能;
//bit4:中断MAX_RT(达到最大重发次数中断)使能;bit5:中断TX_DS使能;bit6:中断RX_DR使能
#define EN_AA           0x01  //使能自动应答功能  bit0~5,对应通道0~5
#define EN_RXADDR       0x02  //接收地址允许,bit0~5,对应通道0~5
#define SETUP_AW        0x03  //设置地址宽度(所有数据通道):bit1,0:00,3字节;01,4字节;02,5字节;
#define SETUP_RETR      0x04  //建立自动重发;bit3:0,自动重发计数器;bit7:4,自动重发延时 250*x+86us
#define RF_CH           0x05  //RF通道,bit6:0,工作通道频率;
#define RF_SETUP        0x06  //RF寄存器;bit3:传输速率(0:1Mbps,1:2Mbps);bit2:1,发射功率;bit0:低噪声放大器增益
#define STATUS          0x07  //状态寄存器;bit0:TX FIFO满标志;bit3:1,接收数据通道号(最大:6);bit4,达到最多次重发
//bit5:数据发送完成中断;bit6:接收数据中断;
#define RX_OK        0x40  //接收到数据中断

#define OBSERVE_TX      0x08  //发送检测寄存器,bit7:4,数据包丢失计数器;bit3:0,重发计数器
#define CD              0x09  //载波检测寄存器,bit0,载波检测;
#define RX_ADDR_P0      0x0A  //数据通道0接收地址,最大长度5个字节,低字节在前
#define TX_ADDR         0x10  //发送地址(低字节在前),ShockBurstTM模式下,RX_ADDR_P0与此地址相等
#define RX_PW_P0        0x11  //接收数据通道0有效数据宽度(1~32字节),设置为0则非法
#define NRF_FIFO_STATUS 0x17  //FIFO状态寄存器;bit0,RX FIFO寄存器空标志;bit1,RX FIFO满标志;bit2,3,保留

//bit4,TX FIFO空标志;bit5,TX FIFO满标志;bit6,1,循环发送上一数据包.0,不循环;
//
void NRF_Init(void);

unsigned char NRF_SPI_Send_Byte(unsigned char Tx_Data);

unsigned char NRF_Write_Reg(unsigned char Reg_Addr, unsigned char Data);

unsigned char NRF_Read_Reg(unsigned char Reg_Addr);

unsigned char NRF_Write_Buf(unsigned char Reg_Addr, unsigned char *pBuf, unsigned char Buf_len);

unsigned char NRF_Read_Buf(unsigned char Reg_Addr, unsigned char *pBuf, unsigned char Buf_len);

unsigned char NRF_Check(void);

void NRF_RX_Mode(void);

unsigned char NRF_RX_Packet(unsigned char *rxbuf);

#endif //ROBOTMATCHZET6_NRF24L01_H
