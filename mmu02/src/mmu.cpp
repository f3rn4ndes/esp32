/*
  Copyright (c), 2022 - NUTES - Nucleo de Tecnologias Estrategicas na Saude
  http://nutes.uepb.edu.br/
  All rights reserved.
*/

/* Defines */
#define _MMU_

/* Includes */
#include "mmu.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/* Functions */

void mmuSetup(void)
{
    #if (VERBOSE_MODULE_MMU == VERBOSE_ON)
        Serial.println("[MMU] FUNCTION : mmuSetup");
    #endif

    xMmu.criticalFailures = MMU_NO_CRITICAL_FAILURES;
    xMmu.internalFlashError = MMU_INTERNAL_FLASH_ERROR;

    mmuInit();
}

void mmuInit(void)
{
    #if (VERBOSE_MODULE_MMU == VERBOSE_ON)
        Serial.println("[MMU] FUNCTION : mmuInit");
    #endif

    mmuInternalFlashInit();
}

uint8_t mmuInternalFlashInit(void)
{
    #if (VERBOSE_MODULE_MMU == VERBOSE_ON)
        Serial.println("[MMU] FUNCTION : mmuInternalFlashInit");
    #endif

    xMmu.internalFlashError = MMU_INTERNAL_FLASH_ERROR;
    if (!SPIFFS.begin())
    {
        #if (VERBOSE_MODULE_STEP_MMU == VERBOSE_ON)
        Serial.println("[MMU STEP] FAIL to mount Internal Flash Memory");
        #endif
    }
    else
    {
        xMmu.internalFlashError = MMU_INTERNAL_FLASH_OK;
        #if (VERBOSE_MODULE_STEP_MMU == VERBOSE_ON)
        Serial.println("[MMU STEP] SUCCESS: Internal Flash Memory Mounted");
        Serial.printf("[MMU STEP] Internal Flash Size %d bytes\n", mmuGetInternalFlashSize());
        Serial.printf("[MMU STEP] Internal Flash Used %d bytes\n", mmuGetInternalFlashUsed());
        #endif
    }

    return xMmu.internalFlashError;
}

void mmuTaskCreate(void)
{
    BaseType_t rc;

    #if (VERBOSE_MODULE_MMU == VERBOSE_ON)
        Serial.println("[MMU] FUNCTION : mmuTaskCreate");
    #endif

    rc = xTaskCreatePinnedToCore
    (
        mmuTask,
        "MMU",
        MMU_TASK_STACK_SIZE,
        NULL,
        MMU_TASK_PRIORITY,
        &mmuTaskHandle,
        MMU_TASK_CORE
    );
    assert(rc == pdPASS);
}

static void mmuTask(void *pvParameters)
{
    uint32_t rv;

    for (;;)
    {
        rv = ulTaskNotifyTake(pdTRUE,portMAX_DELAY);
        #if (VERBOSE_TASK_MMU == VERBOSE_ON)
        Serial.println("[MMU TASK] mmuTask : Notification");
        #endif
        #if (VERBOSE_TASK_MMU == VERBOSE_ON)
        Serial.println("[MMU TASK] mmuTask : Finish");
        #endif
    }
}


uint8_t mmuGetInternalFlashError(void)
{
    return xMmu.internalFlashError;
}

size_t mmuGetInternalFlashSize(void)
{
    size_t value = 0;
    if (!mmuGetInternalFlashError())
    {
        value = SPIFFS.totalBytes();
    }
    return value;
}

size_t mmuGetInternalFlashUsed(void)
{
    size_t value = 0;

    #if (VERBOSE_MODULE_MMU == VERBOSE_ON)
        Serial.println("[MMU] FUNCTION : mmuGetInternalFlashUsed");
    #endif

    if (!mmuGetInternalFlashError())
    {
        value = SPIFFS.usedBytes();
    }
    return value;
}

boolean mmuFileExists(String& fileName)
{
    #if (VERBOSE_MODULE_MMU == VERBOSE_ON)
        Serial.println("[MMU] FUNCTION : mmuFileExists");
    #endif

    if (!mmuGetInternalFlashError())
    {
        String fullName = fileName;
        return SPIFFS.exists(fullName);
    }
    else
    {
        return false;
    }
}

boolean mmuReadFile(String& fileName, JsonDocument& doc)
{
    File file;
    
    #if (VERBOSE_MODULE_MMU == VERBOSE_ON)
        Serial.println("[MMU] FUNCTION : mmuReadFile");
    #endif

    if (mmuFileExists(fileName))
    {
        file = SPIFFS.open(fileName, FILE_READ);
        if (!file)
        {
            #if (VERBOSE_MODULE_STEP_MMU == VERBOSE_ON)
            Serial.printf("[MMU] Fail to read filename: %s \n", fileName);
            #endif
            return false;
        }
        else
        {
            DeserializationError error = deserializeJson(doc, file);
            #if (VERBOSE_MODULE_STEP_MMU == VERBOSE_ON)
            if (error)
            {
                Serial.printf("[MMU] Fail deserialize filename: %s error: %d \n", fileName, error);
            }
            #endif
            file.close();
            return (error.code() == DeserializationError::Ok ? true: false);
        }
    }
    else
    {
        return false;
    }

}


boolean mmuWriteFile(String& fileName, JsonDocument& doc)
{
    File file;
    
    #if (VERBOSE_MODULE_MMU == VERBOSE_ON)
        Serial.println("[MMU] FUNCTION : mmuWriteFile");
    #endif

    if (!mmuRemoveFile(fileName))
    {
        return false;
    }

    file = SPIFFS.open(fileName, FILE_WRITE);
    if (file)
    {
        size_t size = serializeJson(doc, file);

        if (!size)
        {
            #if (VERBOSE_MODULE_STEP_MMU == VERBOSE_ON)
            Serial.printf("[MMU] Fail to serialize Json to file: %s \n", fileName);
            #endif
        }
        file.close();
        return (size > 0 ? true: false);
    }
    else
    {
        #if (VERBOSE_MODULE_STEP_MMU == VERBOSE_ON)
        Serial.printf("[MMU] Fail to write filename: %s \n", fileName);
        #endif
        return false;
    }

}

boolean mmuRemoveFile(String& fileName)
{
    #if (VERBOSE_MODULE_MMU == VERBOSE_ON)
        Serial.println("[MMU] FUNCTION : mmuRemoveFile");
    #endif

    if (mmuFileExists(fileName))
    {
        if (SPIFFS.remove(fileName))
        {
            #if (VERBOSE_MODULE_STEP_MMU == VERBOSE_ON)
            Serial.printf("[MMU STEP] File removed: %s \n", fileName);
            #endif
            return true;
        }
        else
        {
            #if (VERBOSE_MODULE_STEP_MMU == VERBOSE_ON)
            Serial.printf("[MMU STEP] Fail to remove File: %s \n", fileName);
            #endif
            return false;
        }
    }
    else
    {
        return true;
    }
}

void mmuReadSca(void)
{
    DynamicJsonDocument doc(1024);
    String fileName = "/sca.json";

    #if (VERBOSE_MODULE_MMU == VERBOSE_ON)
        Serial.println("[MMU] FUNCTION : mmuReadSca");
    #endif

    if (mmuReadFile(fileName, doc))
    {
        #if (VERBOSE_MODULE_STEP_MMU == VERBOSE_ON)
        Serial.printf("[MMU] File Exists: %s \n", fileName.c_str());
        Serial.println();
        serializeJsonPretty(doc, Serial);
        Serial.println();
        Serial.flush();
        #endif
    }
    else
    {
        #if (VERBOSE_MODULE_STEP_MMU == VERBOSE_ON)
        Serial.printf("[MMU] File NOT Exists: %s \n", fileName.c_str());
        Serial.flush();
        #endif
    }
}

void mmuWriteSca(void)
{
    DynamicJsonDocument doc(1024);
    String fileName = "/sca.json";

    doc["enabled"] = true;
    doc["visual"] = true;
    doc["sound"] = true;
    doc["history"] = true;

    JsonObject parameters = doc.createNestedObject("parameters");
    parameters["timeout"] = 300;
    parameters["priority"] = 1;
    parameters["color"] = 2;
    doc["scheduler"] = false;

    JsonArray schedule = doc.createNestedArray("schedule");

    JsonObject schedule_0 = schedule.createNestedObject();
    schedule_0["day"] = 1;
    schedule_0["start"] = "00:00";
    schedule_0["end"] = "00:00";
    schedule_0["tomorrow"] = true;

    JsonObject schedule_1 = schedule.createNestedObject();
    schedule_1["day"] = 2;
    schedule_1["start"] = "00:00";
    schedule_1["end"] = "00:00";
    schedule_1["tomorrow"] = true;

    JsonObject schedule_2 = schedule.createNestedObject();
    schedule_2["day"] = 3;
    schedule_2["start"] = "00:00";
    schedule_2["end"] = "00:00";
    schedule_2["tomorrow"] = true;

    JsonObject schedule_3 = schedule.createNestedObject();
    schedule_3["day"] = 4;
    schedule_3["start"] = "00:00";
    schedule_3["end"] = "00:00";
    schedule_3["tomorrow"] = true;

    JsonObject schedule_4 = schedule.createNestedObject();
    schedule_4["day"] = 5;
    schedule_4["start"] = "00:00";
    schedule_4["end"] = "00:00";
    schedule_4["tomorrow"] = true;

    JsonObject schedule_5 = schedule.createNestedObject();
    schedule_5["day"] = 6;
    schedule_5["start"] = "00:00";
    schedule_5["end"] = "00:00";
    schedule_5["tomorrow"] = true;

    JsonObject schedule_6 = schedule.createNestedObject();
    schedule_6["day"] = 7;
    schedule_6["start"] = "00:00";
    schedule_6["end"] = "00:00";
    schedule_6["tomorrow"] = true;    

    if (mmuWriteFile(fileName, doc))
    {
        #if (VERBOSE_MODULE_STEP_MMU == VERBOSE_ON)
        Serial.printf("[MMU] File Writed: %s \n", fileName.c_str());
        Serial.println();
        serializeJsonPretty(doc, Serial);
        Serial.println();
        Serial.flush();
        #endif
    }
    else
    {
        #if (VERBOSE_MODULE_STEP_MMU == VERBOSE_ON)
        Serial.printf("[MMU] Fail to Write File: %s \n", fileName.c_str());
        Serial.flush();
        #endif
    }

}







