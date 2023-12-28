#include <iostream>
#include "Flight.h"
#include "AviaSale.h"

using namespace std;

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Rus");
    auto* native_adv_avia_sale = new AviaSale();
    native_adv_avia_sale->load_flights_from_csv();
    native_adv_avia_sale->enter();
}
