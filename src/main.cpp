#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>

#include "avl_tree.h"

void test(std::vector<int> &values, int m, bool balance);
void generate_values(std::vector<int> &values, size_t size, bool sort);

int main() {
    std::cout << "Insira N e M: ";

    size_t n = 0;
    std::cin >> n;
    if (n <= 0) {
        std::cout << "Tamanho inválido! Insira N > 0" << std::endl;
        return 0;
    }

    size_t m = 0;
    std::cin >> m;
    if (m <= 0) {
        std::cout << "Tamanho inválido! Insira M > 0" << std::endl;
    }

    std::vector<int> values;

    // randomizar
    std::cout << "VALORES E ORDEM ALEATÓRIOS" << std::endl;
    generate_values(values, n, false);
    test(values, m, false);
    test(values, m, true);

    std::cout << std::endl;

    // randomizar + ordenar
    std::cout << "VALORES ALEATÓRIOS ORDENADOS" << std::endl;
    generate_values(values, n, true);
    test(values, m, false);
    test(values, m, true);

    return 0;
}

void test(std::vector<int> &values, int m, bool balance) {
    if (balance) {
        std::cout << "Árvore AVL:" << std::endl;
    } else {
        std::cout << "Árvore Binária de Busca:" << std::endl;
    }

    AVLTree tree(balance);
    for (auto value : values) {
        tree.insert(value);
    }

    int total_comparisons = 0;

    double t0 = double(clock()) / CLOCKS_PER_SEC;
    for (auto value : values) {
        int comparisons;
        tree.search(value, comparisons);
        total_comparisons += comparisons;
    }
    double t1 = double(clock()) / CLOCKS_PER_SEC;

    std::cout << "    Altura: " << tree.height() << std::endl;
    std::cout << "    Comparações: " << total_comparisons << std::endl;
    std::cout << "    Tempo (s): " << (t1 - t0) << std::endl;
}

void generate_values(std::vector<int> &values, size_t size, bool sort) {
    std::uniform_int_distribution<int> distribution(0, 1000);
    std::default_random_engine generator;
    generator.seed(std::chrono::system_clock::now().time_since_epoch().count());

    values.resize(size);
    std::generate(values.begin(), values.end(), [&distribution, &generator]() {
        return distribution(generator);
    });

    if (sort) {
        std::sort(values.begin(), values.end());
    }
}
