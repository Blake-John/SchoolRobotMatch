//
// Created by DTS on 2024/3/9.
//

#include "encode.h"
#include "motorcontrol.h"

Motor MotorFL, MotorFR, MotorBL, MotorBR;
Motor_Rack Rack;
extern uint8_t UART_Rxbuf[1];
extern unsigned char Slave_Send_State;
extern uint8_t PIDCalculate_State;
double Kp = 70;
double Ki = 7;
double Kd = 2;
double Kp1 = 50;
double Ki1 = 0;
double Kd1 = 0;
uint8_t Receive_Sign = 0xB2;

void MotorStructure_Init()
{
    MotorFL.Speed = 0;
    MotorFR.Speed = 0;
    MotorBL.Speed = 0;
    MotorBR.Speed = 0;
    MotorFL.Error = 0;
    MotorFR.Error = 0;
    MotorBL.Error = 0;
    MotorBR.Error = 0;
    MotorFL.Last_Error = 0;
    MotorFR.Last_Error = 0;
    MotorBL.Last_Error = 0;
    MotorBR.Last_Error = 0;
    MotorFL.Integral = 0;
    MotorFR.Integral = 0;
    MotorBL.Integral = 0;
    MotorBR.Integral = 0;
    MotorFL.TargetSpeed = 0;
    MotorFR.TargetSpeed = 0;
    MotorBL.TargetSpeed = 0;
    MotorBR.TargetSpeed = 0;
    Rack.PWM_OUT = 0;
    Rack.Speed = 0;
    Rack.Error = 0;
    Rack.Last_Error = 0;
    Rack.TargetSpeed = 0;
    Rack.Integral = 0;
    Rack.P = 0.01;
    Rack.Posi_Error = 0;
    Rack.Targetposition = 0;
    Rack.Position = 0;
}

void Set_Target_Speed(float Speed)
{
    MotorFL.TargetSpeed = Speed;
    MotorFR.TargetSpeed = Speed;
    MotorBL.TargetSpeed = Speed;
    MotorBR.TargetSpeed = Speed;
}


void Set_Rack_Target_Position(int32_t Position)
{
    Rack.Targetposition = Position;
}

void MotorEncode_Init()
{
    HAL_TIM_Encoder_Start(&ENCODERRACK_TIM, TIM_CHANNEL_ALL);
    HAL_TIM_Encoder_Start(&ENCODERFL_TIM, TIM_CHANNEL_ALL);
    HAL_TIM_Encoder_Start(&ENCODERFR_TIM, TIM_CHANNEL_ALL);
    HAL_TIM_Encoder_Start(&ENCODERBL_TIM, TIM_CHANNEL_ALL);
    HAL_TIM_Encoder_Start(&ENCODERBR_TIM, TIM_CHANNEL_ALL);
    HAL_TIM_Base_Start_IT(&GAP_TIM);
    MotorStructure_Init();
}

void PID_Calculate(Motor *Motor_Side)
{
    if (Motor_Side->Speed < 0)
    {
        Motor_Side->Speed = -Motor_Side->Speed;
    }
    Motor_Side->Error = Motor_Side->TargetSpeed - Motor_Side->Speed;
    Motor_Side->Integral += Motor_Side->Error;
    double d_error = Motor_Side->Error - Motor_Side->Last_Error;
    double pwm = Kp * Motor_Side->Error + Ki * Motor_Side->Integral + Kd * d_error;
    if (pwm > 65535)
    {
        pwm = 65535;
    } else if (pwm < 0)
    {
        pwm = 0;
    }
    Motor_Side->PWM_OUT = (uint16_t) pwm;
    Motor_Side->Last_Error = Motor_Side->Error;
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == GAP_TIM.Instance)
    {
        MotorFL.Speed = (double) ((int16_t) (COUNTER_NUM_FL)) * 50 / 221;
        MotorFR.Speed = (double) ((int16_t) (COUNTER_NUM_FR)) * 25 / 442;
        MotorBL.Speed = (double) ((int16_t) (COUNTER_NUM_BL)) * 25 / 442;
        MotorBR.Speed = (double) ((int16_t) (COUNTER_NUM_BR)) * 25 / 442;
                __HAL_TIM_SetCounter(&ENCODERFL_TIM, 0);
                __HAL_TIM_SetCounter(&ENCODERFR_TIM, 0);
                __HAL_TIM_SetCounter(&ENCODERBL_TIM, 0);
                __HAL_TIM_SetCounter(&ENCODERBR_TIM, 0);
        PIDCalculate_State = 1;
    }
    if (Slave_Send_State == 0x38)
    {
        MotorFL.Speed = 0;
        MotorFR.Speed = 0;
        MotorBL.Speed = 0;
        MotorBR.Speed = 0;
    }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART1)
    {
        if (UART_Rxbuf[0] == Receive_Sign)
        {
            HAL_UART_Transmit(&huart1, (uint8_t *) &MotorFL.PWM_OUT, 2, 0xff);
            HAL_UART_Transmit(&huart1, (uint8_t *) &MotorFR.PWM_OUT, 2, 0xff);
            HAL_UART_Transmit(&huart1, (uint8_t *) &MotorBL.PWM_OUT, 2, 0xff);
            HAL_UART_Transmit(&huart1, (uint8_t *) &MotorBR.PWM_OUT, 2, 0xff);
            HAL_UART_Transmit(&huart1, (uint8_t *) &Slave_Send_State, 1, 0xff);
            Slave_Send_State = 0;
        }
    }
    UART_Rxbuf[0] = 0;
    HAL_UART_Receive_IT(&huart1, (uint8_t *) UART_Rxbuf, 1);
}