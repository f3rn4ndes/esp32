/*
  Copyright (c), 2023
  All rights reserved.
*/

/* Defines */
#define _VERBOSE_

/* Includes */
#include "verbose.h"

/* Functions */

void verboseSetup(void)
{
}

void verboseInit(void)
{
}

void verbose(const String &message, int key)
{
  if (key == VERBOSE_ON)
  {
    Serial.println(message);
  }
}
