#pragma once
#include <vector>
#include <iostream>
#include <chrono>


std::vector<std::vector<int>> data_generation_1(int m);
std::vector<std::vector<int>> data_generation_2(int m);
bool linear_search(std::vector<std::vector<int>> matrix, int target);
bool binary_search_matrix(std::vector<std::vector<int>> matrix, int target);
bool exponential_search_matrix(std::vector<std::vector<int>> matrix, int target);
std::chrono::time_point<std::chrono::steady_clock> get_time();
double time_difference(std::chrono::time_point<std::chrono::steady_clock> start, std::chrono::time_point<std::chrono::steady_clock> finish);
void time_calculate();