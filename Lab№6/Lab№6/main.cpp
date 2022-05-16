#include <iostream>
#include <vector>
#include <numeric>

#include "main.hpp"

int main() {
    unsigned row = 5;
    unsigned col = 6;

    std::vector< std::vector<unsigned>> cost {
        { 21, 11, 15, 12, 20, 10 },
        { 19, 9, 17, 14, 16, 22 },
        { 10, 14, 20, 17, 11, 20 },
        { 13, 19, 19, 12, 22, 11 },
        { 12, 20, 18, 9, 19, 13 }
    };
    //scan_matrix(cost, row, col);
    print_matrix(cost, row, col);
    std::vector<unsigned> offer { 177, 122, 159, 168, 109 };
    std::vector<unsigned> demand { 152, 116, 140, 202, 104, 172 };
    //scan_vector(offer, row);
    //scan_vector(demand, col);
    std::cout << "Offer: " << std::endl;
    print_vector(offer, row);
    std::cout << "Demand: " << std::endl;
    print_vector(demand, col);

    if (std::accumulate(offer.cbegin(), offer.cend(), 0) == std::accumulate(demand.cbegin(), demand.cend(), 0)) {
        std::cout << "Problem is saturated." << std::endl;
    }

    std::cout << "North-west method: " << NW_method(cost, row, col, offer, demand) << std::endl;
    std::cout << "Minimum method: " << min_method(cost, row, col, offer, demand) << std::endl;
    std::cout << "Fogel's method: " << fogels_method(cost, row, col, offer, demand) << std::endl;

    return 0;
}