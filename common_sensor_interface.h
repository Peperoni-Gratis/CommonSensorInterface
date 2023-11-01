#ifndef ESPTESTING_COMMON_SENSOR_INTERFACE_H
#define ESPTESTING_COMMON_SENSOR_INTERFACE_H

#include <freertos/portmacro.h>
#include <cstdint>
#include <exception>
#include "esp_check.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

class SensorException : public std::exception {
public:
    enum Etype{
        init,
        reading,
    };
private:
    SensorException();
    Etype type;
public:
    static SensorException InitError(){
        auto e = SensorException();
        e.type = Etype::init;
    }

    static SensorException ReadingError(){
        auto e = SensorException();
        e.type = Etype::reading;
    }

    const char *what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override;

    Etype get_type() const {
        return type;
    }
};

const char *SensorException::what() const noexcept {
    switch (type) {
        case init:
            return "Error during sensor init";
        case reading:
            return "Error during sensor reading";
    }
}




template <typename T>
class CommonSensorInterface{
public:
    //get sensor readings
    virtual T get_readings() const = 0;
};

template <typename T>
class FixedRateSensorInterface: public CommonSensorInterface<T>{
public:
    //create task that samples at fixed rate giving the task name and the sampling rate in milliseconds
    virtual void start_sampling(const char* task_name, uint64_t &sampling_rate) = 0;
    //destroy task that samples at fixed rate
    virtual void stop_sampling() = 0;
    //get the sampling rate in milliseconds
    virtual uint64_t get_sampling_rate() const = 0;
    //check if the sampling is active by returning ESP_OK
    virtual bool get_sampling_status() const = 0;
};

#endif ESPTESTING_COMMON_SENSOR_INTERFACE_H