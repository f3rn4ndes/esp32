/*
  Copyright (c), 2022 - NUTES - Nucleo de Tecnologias Estrategicas na Saude
  http://nutes.uepb.edu.br/
  All rights reserved.
*/

#ifndef BOARD_H
#define BOARD_H

/* Includes */
#include <Arduino.h>

/* Defines */

// External Inputs (SCA_EI_*)
// Digital Inputs
#define SCA_EI_D0_PIN GPIO_NUM_39
#define SCA_EI_D1_PIN GPIO_NUM_34
#define SCA_EI_D2_PIN GPIO_NUM_35

// Door Interface (SCA_DOOR_*)
// Digital Inputs
#define SCA_DOOR_SENSOR_PIN SCA_EI_D0_PIN
// Digital Ouputs
#define SCA_DOOR_CMD_PIN GPIO_NUM_25

// Rfid Interface (SCA_RFID_*)
// Digital Inputs
#define SCA_RFID_D0_PIN GPIO_NUM_14
#define SCA_RFID_D1_PIN GPIO_NUM_27
// Digital Outputs
#define SCA_RFID_POWER_CMD_PIN GPIO_NUM_26

// RGB Lights LED (SCA_RLL_*)
// Digital Outputs
#define SCA_RLL_CMD_PIN GPIO_NUM_32

// Buzzer (SCA_BUZZER_*)
// Digital Outputs
#define SCA_BUZZER_CMD_PIN GPIO_NUM_33

// On Board Flash Memory Pins (SCA_FM_*)
// Digital Inputs
#define SCA_FM_MISO_PIN GPIO_NUM_19
// Digital Outputs
#define SCA_FM_CS_PIN GPIO_NUM_5
#define SCA_FM_CLK_PIN GPIO_NUM_18
#define SCA_FM_MOSI_PIN GPIO_NUM_23

// I2C Expansion Port Pins (SCA_I2C_*)
// Digital Inputs
#define SCA_I2C_INT_PIN GPIO_NUM_2
// Digital Outputs
#define SCA_I2C_SCL_PIN GPIO_NUM_22
// Digital Inputs/Outputs
#define SCA_I2C_SDA_PIN GPIO_NUM_21

// SPI Expansion Port Pins (SCA_ESPI_*)
// Digital Inputs
#define SCA_ESPI_MISO_PIN SCA_FM_MISO_PIN
// Digital Outputs
#define SCA_ESPI_CS0_PIN GPIO_NUM_16
#define SCA_ESPI_CS1_PIN GPIO_NUM_17
#define SCA_ESPI_CLK_PIN SCA_FM_CLK_PIN
#define SCA_ESPI_MOSI_PIN SCA_FM_MOSI_PIN

// Temperature and Humidity Sensor (SCA_THS_*)
// Inputs/Ouputs
#define SCA_THS_SENSOR_PIN GPIO_NUM_13

// Ambient Light Sensor (SCA_ALS_*)
// Inputs (Analog)
#define SCA_ALS_SENSOR_PIN GPIO_NUM_36

// Presence Sensor (SCA_PS_*)
// Digital Inputs
#define SCA_PS_SENSOR_PIN GPIO_NUM_4

// Onboard Buttons
// Digital Inputs
#define SCA_BUTTON_RESET_FACTORY_PIN GPIO_NUM_15


// Serial
#define SERIAL_BAUD_RATE 115200

#endif
