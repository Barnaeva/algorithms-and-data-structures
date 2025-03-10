#include <iostream>
#include <chrono>
#include <vector>
#include "BST.h"

using namespace std;

size_t lcg() {
    static size_t x = 0;
    x = (1021 * x + 24631) % 116640;
    return x;
}

void fill_vector(vector<int>& vec) {
    for (size_t i = 0; i < vec.size(); i++) {
        vec[i] = lcg();
    }
}

void measure_fill_time(vector<int>& vec, BinaryTree& tree, size_t size, size_t attempts) {
    chrono::duration<double> total_vec_fill_duration(0);
    chrono::duration<double> total_tree_fill_duration(0);

    for (size_t i = 0; i < attempts; i++) {
        fill_vector(vec);

        auto start = chrono::system_clock::now();
        for (const auto& value : vec) {
            vec.push_back(value);
        }
        auto end = chrono::system_clock::now();
        total_vec_fill_duration += end - start;

        tree.clear();
        start = chrono::system_clock::now();
        for (const auto& value : vec) {
            tree.insert(value);
        }
        end = chrono::system_clock::now();
        total_tree_fill_duration += end - start;
    }

    cout << "Среднее время заполнения std::vector (" << size << "): " << (total_vec_fill_duration.count() / attempts) << " секунд" << endl;
    cout << "Среднее время заполнения BinaryTree (" << size << "): " << (total_tree_fill_duration.count() / attempts) << " секунд" << endl;
}

void measure_search_time(const vector<int>& vec, BinaryTree& tree, size_t attempts) {
    chrono::duration<double> total_vec_search_duration(0);
    chrono::duration<double> total_tree_search_duration(0);

    for (size_t i = 0; i < attempts; i++) {
        int random_value = lcg();

        auto start = chrono::system_clock::now();
        bool found = false;
        for (const auto& value : vec) {
            if (value == random_value) {
                found = true;
                break;
            }
        }
        auto end = chrono::system_clock::now();
        total_vec_search_duration += end - start;

        start = chrono::system_clock::now();
        tree.contains(random_value);
        end = chrono::system_clock::now();
        total_tree_search_duration += end - start;
    }

    cout << "Среднее время поиска в std::vector: " << (total_vec_search_duration.count() / attempts) << " секунд" << endl;
    cout << "Среднее время поиска в BinaryTree: " << (total_tree_search_duration.count() / attempts) << " секунд" << endl;
}

void measure_add_remove_time(vector<int>& vec, BinaryTree& tree, size_t attempts) {
    chrono::duration<double> total_vec_add_remove_duration(0);
    chrono::duration<double> total_tree_add_remove_duration(0);

    for (size_t i = 0; i < attempts; i++) {
        int random_value = lcg();

        auto start = chrono::system_clock::now();
        vec.push_back(random_value);
        auto end = chrono::system_clock::now();
        total_vec_add_remove_duration += end - start;

        start = chrono::system_clock::now();
        vec.pop_back();
        end = chrono::system_clock::now();
        total_vec_add_remove_duration += end - start;

        start = chrono::system_clock::now();
        tree.insert(random_value);
        end = chrono::system_clock::now();
        total_tree_add_remove_duration += end - start;

        start = chrono::system_clock::now();
        tree.erase(random_value);
        end = chrono::system_clock::now();
        total_tree_add_remove_duration += end - start;
    }

    cout << "Среднее время добавления и удаления в std::vector: " << (total_vec_add_remove_duration.count() / attempts) << " секунд" << endl;
    cout << "Среднее время добавления и удаления в BinaryTree: " << (total_tree_add_remove_duration.count() / attempts) << " секунд" << endl;
}

void run_all_measures(size_t min_size, size_t max_size, size_t step, size_t attempts) {
    for (size_t size = min_size; size <= max_size; size += step) {
        vector<int> vec(size);
        BinaryTree tree;

        measure_fill_time(vec, tree, size, attempts);
        measure_search_time(vec, tree, attempts);
        measure_add_remove_time(vec, tree, attempts);
    }
}