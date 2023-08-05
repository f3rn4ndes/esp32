/*
  Copyright (c), 2022 - NUTES - Nucleo de Tecnologias Estrategicas na Saude
  http://nutes.uepb.edu.br/
  All rights reserved.
*/

#ifndef MMU_H
#define MMU_H

/* Includes */
#include <SPIFFS.h>
#include <Arduino.h>
#include <ArduinoJson.h>
#include "board.h"
#include "peripheral.h"
#include "systemtasks.h"
#include "verbose.h"

/* Defines */
#define MMU_OPEN_FILE_TIMEOUT_MS 500
#define MMU_NO_CRITICAL_FAILURES 0

/* Data Types - typedefs, structs, unions and/or enumerated */
typedef enum {
  MMU_INTERNAL_FLASH_OK = 0,
  MMU_INTERNAL_FLASH_ERROR
} eFlashInternalStatus;


typedef struct
{
    uint8_t criticalFailures;
    uint8_t internalFlashError;
    uint32_t usersCount;
    uint32_t eventsCount;
} T_xMmu;


/* Constants */
#ifdef _MMU_

const char * CONFIG_FILE = "/config.json";

const char * USER_PATH = "/user/";
const char * EVENT_PATH = "/event/";
const char * USER_EXTENSION = ".json";
const char * EVENT_EXTENSION = ".json";
const char * SEPARATOR = ",";

#endif

/* Public Functions */
void mmuSetup(void);
uint8_t  mmuInternalFlashInit(void);
uint8_t mmuGetInternalFlashError(void);
size_t mmuGetInternalFlashSize(void);
size_t mmuGetInternalFlashUsed(void);

uint32_t mmuGetInternalFlashUsersCount(void);
uint32_t mmuGetInternalFlashEventsCount(void);

boolean mmuCheckFiles(void);

/* Local Functions */
#ifdef _MMU_

void mmuInit(void);
void mmuTaskCreate(void);
static void mmuTask(void *pvParameters);

boolean mmuFileExists(String& fileName);
boolean mmuReadFile(String& fileName, JsonDocument& doc);
boolean mmuWriteFile(String& fileName, JsonDocument& doc);
boolean mmuRemoveFile(String& fileName);


void mmuReadSca(void);
void mmuWriteSca(void);

#endif

/* Public Variables */

/* Local Variables */
#ifdef _MMU_
T_xMmu xMmu;
static TaskHandle_t mmuTaskHandle = NULL;
#endif

#endif

