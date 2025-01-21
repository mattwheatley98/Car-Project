//
// Created by matt on 4/17/23.
//

#pragma once

void objectDetectionTask(void *parameter);
extern SemaphoreHandle_t frontBackObjectDetectionHandle;
extern SemaphoreHandle_t frontObjectDetectionHandle;
extern SemaphoreHandle_t backObjectDetectionHandle;
extern SemaphoreHandle_t interruptObjectDetectionHandle;
extern boolean toggleStatus;
