#include "ttc.hpp"

double calculateTTC(const SensorData& data)  // & sadece sensor verisini oku ve hesapla, kopyalama yapma    
{
    return data.distance / data.speed;  // TTC hesaplaması: mesafe / hız
}