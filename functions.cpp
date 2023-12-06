#include <vector>
#include <iostream>
#include <math.h>
#include <iomanip>
#include <chrono>

const size_t N = 8192;

// linear search function
bool linear_search(std::vector<std::vector<int>> matrix, int target){
    size_t m = matrix.size(), n = matrix[0].size();

    // starting for search from top right corner
    size_t row = 0, col = n - 1;

    while(row < m){
        // if target was found
        if(matrix[row][col] == target){
            return true;
        }

        // if target is smaller than current value, then move to left
        // otherwise move down
        if(matrix[row][col] > target){
            if(col == 0){
                return false;
            }
            col--;
        }else {
            row++;
        }
    }

    return false;
}

// binary search on a matrix
bool binary_search_matrix(std::vector<std::vector<int>> matrix, int target){
    size_t m = matrix.size(), n = matrix[0].size();

    // starting for search from top right corner
    size_t row = 0, col = n - 1;

    while(row < m){
        // if target was found
        if(matrix[row][col] == target){
            return true;
        }

        // if target is smaller than current value, then perform binary_search on a row
        // otherwise move down
        if(matrix[row][col] > target) {
            size_t end = col, start = 0;
            while(start<end){
                size_t middle = (start + end + 1) / 2;
                if(matrix[row][middle] <= target){
                    start = middle;
                }else{
                    end = middle - 1;
                }
            }

            if(matrix[row][start] == target){
                return true;
            }

            if(matrix[row][start] > target && start == 0){
                break;
            }
            col = start;

        }else{
            row++;
        }
    }
    return false;
}

// exponential search on a matrix
bool exponential_search_matrix(std::vector<std::vector<int>> matrix, int target){
    size_t m = matrix.size(), n = matrix[0].size();

    // starting for search from top right corner
    size_t row = 0, col = n - 1;

    while(row < m){
        // if target was found
        if(matrix[row][col] == target){
            return true;
        }

        // if target is smaller than current value, then perform exponential_search on a row
        // otherwise move down
        if(matrix[row][col] > target) {
            int step = 1;
            size_t pos = col;

            while(pos >- 0){
                if(matrix[row][pos] < target){
                    break;
                }
                pos -= step;
                step *= 2;
            }

            size_t start, end;
            start = std::max(static_cast<int>(pos), 0);
            end = std::min((pos + step), matrix[row].size() - 1);

            while(start < end){
                size_t middle = (start + end + 1)/2;
                if(matrix[row][middle] <= target){
                    start = middle;
                }else{
                    end = middle - 1;
                }
            }

            if(matrix[row][pos] == target){
                return true;
            }

            if(matrix[row][pos] > target && pos == 0){
                break;
            }
            col = pos;
        }else{
            row++;
        }

    }
    return false;
}

std::chrono::time_point<std::chrono::steady_clock> get_time(){
    return std::chrono::steady_clock::now();
}

double time_difference(std::chrono::time_point<std::chrono::steady_clock> start, std::chrono::time_point<std::chrono::steady_clock> finish){
    std::chrono::duration<double, std::ratio<1, 1000>> duration = finish - start;
    return duration.count();
}

std::vector<std::vector<int>> data_generation_1(int m) {
    int n = N;
    std::vector<std::vector<int>> matrix(m, std::vector<int> (n));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = (n / m * i + j) * 2;
        }
    }
    return matrix;
}


std::vector<std::vector<int>> data_generation_2(int m) {
    int n = N;
    std::vector<std::vector<int>> matrix(m, std::vector<int>(n));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = (n / m * i * j) * 2;
        }
    }
    return matrix;
}

void print_data(int variant, std::vector<double> time_1, std::vector<double> time_2, std::vector<double> time_3){
    // displaying results
    if(variant == 1){
        std::cout << "Results for 1st data:\n";
    }else{
        std::cout << "Results for 2nd data:\n";
    }
    std::cout << std::left << std::setw(10)<< "M" << std::setw(15) << "Lin." << std::setw(15) <<"Bin." << "Exp.\n";
    for(int i=0; i<14; i++){
        std::cout << std::setprecision(6) << std::setw(10) << std::pow(2, i) << std::setw(15)
                  << time_1[i] << std::setw(15) << time_2[i] << time_3[i] << "\n";
    }
    std::cout << "\n";
}

void time_calculate(){
    // first calculations for data_generation_1
    // target = 2N+1
    int target = 2*N+1;

    // vectors to hold time data
    std::vector<double> time_1(14, 0), time_2(14, 0), time_3(14, 0);

    // vector to store results
    std::vector<std::vector<bool>> results(14, std::vector<bool> (3,false));
    std::chrono::time_point<std::chrono::steady_clock> time_start;
    std::chrono::time_point<std::chrono::steady_clock> time_finish;

    // initiate loop for data generation
    for(int i=0; i<14; i++){
        // generate data
        auto matrix = data_generation_1(std::pow(2, i));

        time_start = get_time();
        linear_search(matrix,target);
        time_finish = get_time();
        time_1[i] = time_difference(time_start, time_finish);

        time_start = get_time();
        binary_search_matrix(matrix,target);
        time_finish = get_time();
        time_2[i] = time_difference(time_start, time_finish);

        time_start = get_time();
        results[i][2] = exponential_search_matrix(matrix,target);
        time_finish = get_time();
        time_3[i] = time_difference(time_start, time_finish);
    }

    print_data(1, time_1, time_2, time_3);

    // change target = 16N+1
    target = 16*N+1;
    for(int i=0; i<14; i++){
        // generate data
        auto matrix = data_generation_2(std::pow(2, i));

        time_start = get_time();
        linear_search(matrix,target);
        time_finish = get_time();
        time_1[i] = time_difference(time_start, time_finish);

        time_start = get_time();
        binary_search_matrix(matrix,target);
        time_finish = get_time();
        time_2[i] = time_difference(time_start, time_finish);

        time_start = get_time();
        results[i][2] = exponential_search_matrix(matrix,target);
        time_finish = get_time();
        time_3[i] = time_difference(time_start, time_finish);
    }

    print_data(2, time_1, time_2, time_3);

}
