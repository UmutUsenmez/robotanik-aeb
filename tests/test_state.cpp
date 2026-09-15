#include <iostream>
#include <memory>

#include "normal_state.hpp"
#include "warning_state.hpp"

int main()
{
    std::unique_ptr<State>                     // State sınıfının pointer'ı oluşturuluyor
    state = std::make_unique<NormalState>();   // NormalState sınıfının pointer'ı oluşturuluyor
    state->execute();                          // NormalState sınıfının execute fonksiyonu çağrılıyor
    state = std::make_unique<WarningState>();  // WarningState sınıfının pointer'ı oluşturuluyor
    state->execute();                          // WarningState sınıfının execute fonksiyonu çağrılıyor

    return 0;
}