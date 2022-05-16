#ifndef _MAIN_HPP_
#define _MAIN_HPP_

#include <vector>
#include <tuple>
#include <algorithm> 
#include <climits>

void scan_vector(std::vector<unsigned>& vector, const unsigned size)
{
    vector.resize(size);
    for (unsigned i = 0; i < size; ++i) {
        std::cin >> vector[i];
    }
}

void scan_matrix(std::vector<std::vector<unsigned>>& cost
    , const unsigned row
    , const unsigned col)
{
    cost.resize(row);
    for (unsigned i = 0; i < row; ++i) {
        cost[i].resize(col);
    }
    for (unsigned i = 0; i < row; ++i) {
        scan_vector(cost[i], col);
    }
}

void print_vector(const std::vector<unsigned>& vector, const unsigned size)
{
    for (unsigned i = 0; i < size; ++i) {
        std::cout << vector[i] << " ";
    }
    std::cout << std::endl;
}

void print_matrix(const std::vector<std::vector<unsigned>>& cost
    , const unsigned row
    , const unsigned col)
{
    std::cout << "Given cost matrix:" << std::endl;
    for (unsigned i = 0; i < row; ++i) {
        print_vector(cost[i], col);
    }
}

unsigned NW_method(const std::vector<std::vector<unsigned>>& cost
    , const unsigned row
    , const unsigned col
    , const std::vector<unsigned>& offer_given
    , const std::vector<unsigned>& demand_given)
{
    // Necessary initializations
    std::vector<unsigned> offer;
    std::vector<unsigned> demand;
    std::copy(demand_given.cbegin(), demand_given.cend(), std::back_inserter(demand));
    std::copy(offer_given.cbegin(), offer_given.cend(), std::back_inserter(offer));
    std::vector<unsigned> selected_cost;
    std::vector<unsigned> final_demand;
    unsigned i = 0, j = 0;

    while (i < row && j < col) {
        // Take the north-west element first
        selected_cost.push_back(cost[i][j]);
        if (offer[i] == demand[j]) {
            final_demand.push_back(offer[i]);
            // Do not take into consideration columns and rows
            // where offer and demand are depleted
            i++; j++;
        }
        else if (offer[i] > demand[j]) {
            final_demand.push_back(demand[j]);
            offer[i] -= demand[j];
            // Do not take into consideration columns 
            // where demand is depleted
            j++;
        }
        else if (offer[i] < demand[j]) {
            final_demand.push_back(offer[i]);
            demand[j] -= offer[i];
            // Do not take into consideration rows
            // where offer is depleted
            i++;
        }
    }

    return std::inner_product(selected_cost.cbegin(), selected_cost.cend(), final_demand.cbegin(), 0);
}

// Input: matrix, number od rows and columns
// Output: array where a single element is an element from the given matrix and its position
std::vector<std::tuple<unsigned, unsigned, unsigned>> matrix2array
(const std::vector<std::vector<unsigned>>& matrix
    , const unsigned row
    , const unsigned col)
{
    std::vector<std::tuple<unsigned, unsigned, unsigned>> array;
    for (unsigned i = 0; i < row; ++i) {
        for (unsigned j = 0; j < col; ++j) {
            array.push_back(std::make_tuple(matrix[i][j], i, j));
        }
    }
    return array;
}

unsigned min_method(const std::vector<std::vector<unsigned>>& cost
    , const unsigned row
    , const unsigned col
    , const std::vector<unsigned>& offer_given
    , const std::vector<unsigned>& demand_given)
{
    // Necessary initializations
    std::vector<unsigned> offer;
    std::vector<unsigned> demand;
    std::copy(demand_given.cbegin(), demand_given.cend(), std::back_inserter(demand));
    std::copy(offer_given.cbegin(), offer_given.cend(), std::back_inserter(offer));
    std::vector<unsigned> selected_cost;
    std::vector<unsigned> final_demand;
    unsigned i = 0, j = 0;

    auto cost_array = matrix2array(cost, row, col);
    // Thus, minimum element is always at the position 0
    std::sort(cost_array.begin(), cost_array.end());

    while (cost_array.size()) {
        // Extract minimum element
        unsigned min_element = std::get<0>(cost_array[0]);
        i = std::get<1>(cost_array[0]);
        j = std::get<2>(cost_array[0]);

        // Minimum element is always in the end result
        selected_cost.push_back(min_element);
        cost_array.erase(cost_array.cbegin());

        if (offer[i] == demand[j]) {
            // Do not take into consideration columns and rows
            // where offer and demand are depleted
            final_demand.push_back(offer[i]);
            cost_array.erase(
                std::remove_if(cost_array.begin(), cost_array.end(),
                    [i, j](auto cost) { return (std::get<1>(cost) == i) or (std::get<2>(cost) == j); }),
                cost_array.end()
            );
        }
        else if (offer[i] > demand[j]) {
            // Do not take into consideration columns
            // where demand is depleted
            final_demand.push_back(demand[j]);
            offer[i] -= demand[j];
            cost_array.erase(
                std::remove_if(cost_array.begin(), cost_array.end(),
                    [i, j](auto cost) { return std::get<2>(cost) == j; }),
                cost_array.end()
            );
        }
        else if (offer[i] < demand[j]) {
            // Do not take into consideration rows
            // where offer is depleted
            final_demand.push_back(offer[i]);
            demand[j] -= offer[i];
            cost_array.erase(
                std::remove_if(cost_array.begin(), cost_array.end(),
                    [i, j](auto cost) { return std::get<1>(cost) == i; }),
                cost_array.end()
            );
        }
    }

    return std::inner_product(selected_cost.cbegin(), selected_cost.cend(), final_demand.cbegin(), 0);
}

std::vector<std::vector<unsigned>> copy_matrix(const std::vector<std::vector<unsigned>>& cost_given)
{
    return cost_given;
}

unsigned fogels_method(const std::vector<std::vector<unsigned>>& cost_given
    , const unsigned row
    , const unsigned col
    , const std::vector<unsigned>& offer_given
    , const std::vector<unsigned>& demand_given)
{
    // Necessary initializations
    std::vector<unsigned> offer;
    std::vector<unsigned> demand;
    std::copy(demand_given.cbegin(), demand_given.cend(), std::back_inserter(demand));
    std::copy(offer_given.cbegin(), offer_given.cend(), std::back_inserter(offer));
    std::vector<unsigned> selected_cost;
    std::vector<unsigned> final_demand;
    std::vector<std::vector<unsigned>> cost;
    cost = copy_matrix(cost_given);
    std::vector<unsigned> rows_min;
    std::vector<unsigned> cols_min;
    unsigned fst_row_min;
    unsigned snd_row_min;
    unsigned fst_col_min;
    unsigned snd_col_min;
    unsigned num_elems = row * col;
    // In the function of number of visited matrix elements
    unsigned iter = 0;
    unsigned i = 0, j = 0;

    while (iter < num_elems) {
        rows_min.resize(0);
        cols_min.resize(0);
        // Find the difference from two smallest elements for each row
        for (i = 0; i < row; ++i) {
            fst_row_min = INT_MAX;
            snd_row_min = INT_MAX;
            for (j = 0; j < col; ++j) {
                if (cost[i][j] < fst_row_min) {
                    snd_row_min = fst_row_min;
                    fst_row_min = cost[i][j];
                }
                else if (cost[i][j] < snd_row_min and cost[i][j] >= fst_row_min) {
                    snd_row_min = cost[i][j];
                }
            }
            if (fst_row_min != INT_MAX and snd_row_min == INT_MAX) {
                rows_min.push_back(fst_row_min);
            }
            else {
                rows_min.push_back(abs(static_cast<int>(fst_row_min - snd_row_min)));
            }
        }
        // Find the difference from two smallest elements for each column
        for (j = 0; j < col; ++j) {
            fst_col_min = INT_MAX;
            snd_col_min = INT_MAX;
            for (i = 0; i < row; ++i) {
                if (cost[i][j] < fst_col_min) {
                    snd_col_min = fst_col_min;
                    fst_col_min = cost[i][j];
                }
                else if (cost[i][j] < snd_col_min and cost[i][j] >= fst_col_min) {
                    snd_col_min = cost[i][j];
                }
            }
            if (fst_col_min != INT_MAX and snd_col_min == INT_MAX) {
                cols_min.push_back(fst_col_min);
            }
            else {
                cols_min.push_back(abs(static_cast<int>(fst_col_min - snd_col_min)));
            }
        }

        auto max_min_rows = std::max_element(rows_min.cbegin(), rows_min.cend());
        auto max_min_cols = std::max_element(cols_min.cbegin(), cols_min.cend());

        // Find minimum in i-th row
        if (*max_min_rows >= *max_min_cols) {
            unsigned row_min = std::distance(rows_min.cbegin(), max_min_rows);
            fst_row_min = cost[row_min][0];
            j = 0;
            for (unsigned k = 1; k < col; ++k) {
                if (cost[row_min][k] < fst_row_min) {
                    fst_row_min = cost[row_min][k];
                    j = k;
                }
            }
            i = row_min;
        }
        // Find minimum in i-th column
        else {
            unsigned col_min = std::distance(cols_min.cbegin(), max_min_cols);
            fst_col_min = cost[0][col_min];
            i = 0;
            for (unsigned k = 1; k < row; ++k) {
                if (cost[k][col_min] < fst_col_min) {
                    fst_col_min = cost[k][col_min];
                    i = k;
                }
            }
            j = col_min;
        }

        selected_cost.push_back(cost[i][j]);
        cost[i][j] = INT_MAX;
        iter++;
        unsigned k, l;

        if (offer[i] == demand[j]) {
            final_demand.push_back(offer[i]);
            for (k = 0; k < row; ++k) {
                for (l = 0; l < col; ++l) {
                    if ((l == j or i == k) and cost[k][l] != INT_MAX) {
                        cost[k][l] = INT_MAX;
                        iter++;
                    }
                }
            }
        }
        else if (offer[i] > demand[j]) {
            final_demand.push_back(demand[j]);
            offer[i] -= demand[j];
            for (k = 0; k < row; ++k) {
                if (cost[k][j] != INT_MAX) {
                    cost[k][j] = INT_MAX;
                    iter++;
                }
            }
        }
        else if (offer[i] < demand[j]) {
            final_demand.push_back(offer[i]);
            demand[j] -= offer[i];
            for (l = 0; l < col; ++l) {
                if (cost[i][l] != INT_MAX) {
                    cost[i][l] = INT_MAX;
                    iter++;
                }
            }
        }
    }
    return std::inner_product(selected_cost.cbegin(), selected_cost.cend(), final_demand.cbegin(), 0);
}

#endif