#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

// Liczniki operacji porównania i podstawienia
long long comparison_counter = 0;
long long swap_counter = 0;

void reset_counters() {
    comparison_counter = 0;
    swap_counter = 0;
}

void selection_sort(std::vector<int>& arr) {
    reset_counters();
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        int min_idx = i;
        for (int j = i + 1; j < n; ++j) {
            ++comparison_counter;
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        std::swap(arr[i], arr[min_idx]);
        ++swap_counter;
    }
}

void bubble_sort(std::vector<int>& arr) {
    reset_counters();
    int n = arr.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            ++comparison_counter;
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                ++swap_counter;
            }
        }
    }
}

void optimized_bubble_sort(std::vector<int>& arr) {
    reset_counters();
    int n = arr.size();
    for (int i = 0; i < n; ++i) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; ++j) {
            ++comparison_counter;
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                ++swap_counter;
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
}

void insertion_sort(std::vector<int>& arr) {
    reset_counters();
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && key < arr[j]) {
            ++comparison_counter;
            arr[j + 1] = arr[j];
            ++swap_counter;
            --j;
        }
        arr[j + 1] = key;
    }
}

void run_experiment(std::vector<int>(*data_generator)(int), void (*sorting_method)(std::vector<int>&), const std::string& method_name) {
    std::cout << "Data Size\tComparisons\tSwaps" << std::endl;

    for (int size = 1000; size <= 100000; size += 1000) {
        std::vector<int> data = data_generator(size);
        sorting_method(data);
        std::cout << size << "\t\t" << comparison_counter << "\t\t" << swap_counter << std::endl;
    }
}

std::vector<int> random_data(int size) {
    std::vector<int> data;
    for (int i = 0; i < size; ++i) {
        data.push_back(rand() % 1000 + 1);
    }
    return data;
}

std::vector<int> ascending_data(int size) {
    std::vector<int> data;
    for (int i = 1; i <= size; ++i) {
        data.push_back(i);
    }
    return data;
}

std::vector<int> descending_data(int size) {
    std::vector<int> data;
    for (int i = size; i > 0; --i) {
        data.push_back(i);
    }
    return data;
}

int main() {
    std::cout << "Selection Sort:" << std::endl;
    run_experiment(random_data, selection_sort, "Selection Sort");

    std::cout << "\nBubble Sort:" << std::endl;
    run_experiment(random_data, bubble_sort, "Bubble Sort");

    std::cout << "\nOptimized Bubble Sort:" << std::endl;
    run_experiment(random_data, optimized_bubble_sort, "Optimized Bubble Sort");

    std::cout << "\nInsertion Sort:" << std::endl;
    run_experiment(random_data, insertion_sort, "Insertion Sort");

    return 0;
}