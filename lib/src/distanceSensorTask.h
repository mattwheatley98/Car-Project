//
// Created by matt on 4/17/23.
//

#ifndef CARPROJECT_DISTANCESENSORTASK_H
#define CARPROJECT_DISTANCESENSORTASK_H

#endif //CARPROJECT_DISTANCESENSORTASK_H

void objectDetectionTask(void *parameter);
extern SemaphoreHandle_t frontBackObjectDetectionHandle;
extern SemaphoreHandle_t frontObjectDetectionHandle;
extern SemaphoreHandle_t backObjectDetectionHandle;
extern SemaphoreHandle_t interruptObjectDetectionHandle;
extern boolean toggleStatus;