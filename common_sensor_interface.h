//
// Created by Lorenzo on 07/10/2023.
//

#ifndef ESPTESTING_COMMON_SENSOR_INTERFACE_H
#define ESPTESTING_COMMON_SENSOR_INTERFACE_H

#include <freertos/portmacro.h>
#include "stdint.h"
#include "esp_check.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"


template <typename T>
class CommonSensorInterface{
public:
    //get sensor readings
    virtual esp_err_t get_readings(T &store) = 0;
};

template <typename T>
class FixedRateSensorInterface: CommonSensorInterface<T>{
public:
    //create task that samples at fixed rate
    virtual esp_err_t start_sampling() = 0;
    //destroy task that samples at fixed rate
    virtual esp_err_t stop_sampling() = 0;
    //set the sampling rate in milliseconds
    virtual esp_err_t set_sampling_rate(uint64_t millis) = 0;
    //get the sampling rate in milliseconds
    virtual esp_err_t get_sampling_rate(uint64_t &millis) = 0;
    //block current task until new reading is available, if wait_time = 0 then this is just polling the sensor to see if new reading is available
    virtual esp_err_t wait_new_reading(TickType_t wait_time) = 0;
};

#endif ESPTESTING_COMMON_SENSOR_INTERFACE_H
