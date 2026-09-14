#ifndef TTC_HPP
#define TTC_HPP

#include "sensor_data.hpp"    // sensör verilerini içeren dosyayı buraya dahil ediyoruz

double calculateTTC(const SensorData&data);   // SensorData& sensor verisini kopyalamadan kullanır ve ttc hesabı yapar

#endif