/*
  Copyright (c), 2023
  All rights reserved.
*/

/* Defines */
#define _APP_

/* Includes */
#include "app.h"

/* Functions */

void appSetup(void)
{
  Serial.begin(APP_MONITOR_SPEED);
}

void appInit(void)
{
  verbose("Mensagem APP", VERBOSE_MODULE_APP);
  verbose("Mensagem MMU", VERBOSE_MODULE_MMU);
}

void appRun(void)
{
#if (APP_SHOW_PARTITIONS == 1)
  appShowPartition();
#endif
}

void appShowPartition(void)
{
  printf("ESP32 Partition table:\n\n");

  printf("| Type | Sub | Offset   | End      |   Size   |       Label      |\n");
  printf("| ---- | --- | -------- | -------- | -------- | ---------------- |\n");

  esp_partition_iterator_t pi = esp_partition_find(ESP_PARTITION_TYPE_ANY, ESP_PARTITION_SUBTYPE_ANY, NULL);
  if (pi != NULL)
  {
    do
    {
      const esp_partition_t *p = esp_partition_get(pi);
      printf("|  %02x  | %02x  | 0x%06X | 0x%06X | 0x%06X | %-16s |\r\n",
             p->type, p->subtype, p->address, (p->address + p->size - 1), p->size, p->label);
    } while (pi = (esp_partition_next(pi)));
  }
}
