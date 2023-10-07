//
// Created by Lorenzo on 07/10/2023.
//

#ifndef ESPTESTING_COMMON_SENSOR_INTERFACE_H
#define ESPTESTING_COMMON_SENSOR_INTERFACE_H
#include "stdint.h"
#include "esp_check.h"

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
    //discover whether the sensor has a new reading
    virtual esp_err_t is_new_reading_ready(bool &status) = 0;
};

#endif ESPTESTING_COMMON_SENSOR_INTERFACE_H
