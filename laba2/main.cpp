#include <iostream>
#include "HashTable.h"
#include <list>
#include "Task.h"

/*int main() {
    // Initialize hash table with capacity 10 using std::list as container
    HashTable<int, std::string, std::list> hash_table(10);

    // Insert values
    hash_table.insert(1, "One");
    hash_table.insert(2, "Two");
    hash_table.insert(3, "Three");

    // Print hash table contents
    std::cout << "Hash table contents after insertion:" << std::endl;
    hash_table.print();

    // Check if values exist
    std::cout << "Does table contain 'One'? " << (hash_table.contains("One") ? "Yes" : "No") << std::endl;
    std::cout << "Does table contain 'Four'? " << (hash_table.contains("Four") ? "Yes" : "No") << std::endl;

    // Search for an element
    Pair<int, std::string>* found = hash_table.search(2);
    if (found) {
        std::cout << "Found element: [" << found->key << ": " << found->value << "]" << std::endl;
    }
    else {
        std::cout << "Element with key 2 not found." << std::endl;
    }

    // Remove an element
    if (hash_table.erase(2)) {
        std::cout << "Element with key 2 successfully removed." << std::endl;
    }
    else {
        std::cout << "Failed to remove element with key 2." << std::endl;
    }

    // Print contents after removal
    std::cout << "Hash table contents after removal:" << std::endl;
    hash_table.print();

    // Insert or update value
    hash_table.insert_or_assign(1, "Uno");
    std::cout << "Updated value for key 1." << std::endl;

    // Print contents after update
    std::cout << "Hash table contents after update:" << std::endl;
    hash_table.print();

    // Test count method
    std::cout << "Number of elements in bucket for key 1: " << hash_table.count(1) << std::endl;

    return 0;
}*/

int main() {
    // Создаем таблицу перестановок для хеша Пирсона (256 значений)
    HashTable<size_t, size_t> pearson_table(256, true);

    // Получаем строку от пользователя
    string user_input_1, user_input_2;
    cout << "Enter a first string to hash: ";
    getline(cin, user_input_1);
    cout << "Enter a second string to hash: ";
    getline(cin, user_input_2);

    // Вычисляем и сохраняем хеш
    size_t saved_hash_1 = pearson_hash(user_input_1, pearson_table);
    std::cout << "Saved hash: " << saved_hash_1 << std::endl;

    size_t saved_hash_2 = pearson_hash(user_input_2, pearson_table);
    std::cout << "Saved hash: " << saved_hash_2 << std::endl;

    cout << (compare_hashes(saved_hash_1, user_input_2, pearson_table) ? "Match" : "Dont match");

    return 0;
}