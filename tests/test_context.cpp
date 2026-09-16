#include <cassert>
#include <iostream>

#include "context.hpp"

int main()
{
    AEBContext context;

    // Başlangıç durumu
    assert(context.getCurrentState() == StateType::NORMAL);

    // TTC = 2 s → WARNING
    context.update({20.0, 10.0});
    assert(context.getCurrentState() == StateType::WARNING);

    context.executeCurrentState();

    // TTC = 1 s → EMERGENCY
    context.update({10.0, 10.0});
    assert(context.getCurrentState() == StateType::EMERGENCY_BRAKE);

    context.executeCurrentState();

    // Güvenli veriler geliyor.
    // 3 ardışık güvenli ölçümden sonra NORMAL.
    context.update({100.0, 10.0});
    assert(context.getCurrentState() == StateType::EMERGENCY_BRAKE);

    context.update({100.0, 10.0});
    assert(context.getCurrentState() == StateType::EMERGENCY_BRAKE);

    context.update({100.0, 10.0});
    assert(context.getCurrentState() == StateType::NORMAL);

    context.executeCurrentState();

    // Hız yaklaşık sıfır → TTC hesaplanmıyor.
    // Mesafe 0.4 m → EMERGENCY.
    context.update({0.4, 0.0});
    assert(context.getCurrentState() == StateType::EMERGENCY_BRAKE);

    // Hız yaklaşık sıfır + uzak mesafe → hemen NORMAL değil,
    // çıkış hysteresis'i uygulanıyor.
    context.update({5.0, 0.0});
    assert(context.getCurrentState() == StateType::EMERGENCY_BRAKE);

    context.update({5.0, 0.0});
    assert(context.getCurrentState() == StateType::EMERGENCY_BRAKE);

    context.update({5.0, 0.0});
    assert(context.getCurrentState() == StateType::NORMAL);

    // Geçersiz veri geldiğinde mevcut State korunuyor.
    context.update({-5.0, 10.0});
    assert(context.getCurrentState() == StateType::NORMAL);

    std::cout << "All context tests passed!\n";

    return 0;
}