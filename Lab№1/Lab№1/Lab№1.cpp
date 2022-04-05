#include <iostream>
#include <chrono>

#include "Auxil.h"

#define CYCLE 1000000

int main()
{
    setlocale(LC_ALL, "RUS");
    double av1 = 0, av2 = 0;
    const auto start_time = std::chrono::system_clock::now();
    for (int i = 0; i < CYCLE; i++) {
        av1 += (double)Auxil::iget(-100, 100);
        av2 += Auxil::dget(-100, 100);
    }
    const auto end_time = std::chrono::system_clock::now();
    const std::chrono::duration<double> diff = end_time - start_time;

    std::cout << "Количество циклов: " << CYCLE << std::endl;
    std::cout << "Среднее значение (int) = " << av1 / CYCLE << std::endl;
    std::cout << "Среднее значение (double) = " << av2 / CYCLE << std::endl;
    std::cout << "Продолжительность: " 
        << std::chrono::duration_cast<std::chrono::milliseconds>(diff).count() << " мс" << std::endl;
}