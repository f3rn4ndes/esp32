/*
  Copyright (c), 2022 - NUTES - Nucleo de Tecnologias Estrategicas na Saude
  http://nutes.uepb.edu.br/
  All rights reserved.
*/
#ifndef PERIPHERAL_H
#define PERIPHERAL_H

/* Includes */
#include <Arduino.h>

/* Defines */
#define SCA_PHE_ENABLED true
#define SCA_PHE_DISABLED false

// External Inputs
#define SCA_PHE_EI SCA_PHE_ENABLED
// Door
#define SCA_PHE_DOOR SCA_PHE_ENABLED
// Rfid
#define SCA_PHE_RFID SCA_PHE_ENABLED
// Buzzer
#define SCA_PHE_BUZZER SCA_PHE_ENABLED
// RGB Led Lights
#define SCA_PHE_RLL SCA_PHE_ENABLED
// Temperature and Humidity Sensor
#define SCA_PHE_THS SCA_PHE_DISABLED
// Presence Sensor
#define SCA_PHE_PS SCA_PHE_DISABLED
// Ambient Light Sensor
#define SCA_PHE_ALS SCA_PHE_DISABLED
// External SPI Expansion Interface
#define SCA_PHE_ESPI SCA_PHE_DISABLED
// External I2C Expansion Interface
#define SCA_PHE_I2C SCA_PHE_DISABLED
// External Flash Memory Interface
#define SCA_PHE_FM SCA_PHE_DISABLED

#endif
