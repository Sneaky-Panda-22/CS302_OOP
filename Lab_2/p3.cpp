/*
    remember: magic constant = (N * (N^2 + 1))/2
    row sum = diag sum = col sum = sec diag sum = constant!
*/

#include <iostream>
#include <vector>

bool is_magic_square(std::vector<std::vector<int>>& matrix, int size) {
    if (size <= 0) return false;

    long long target_sum = 0;
    long long secondary_diag_sum = 0;
    for (int i = 0; i < size; i++) {
        target_sum += matrix[i][i];
        secondary_diag_sum += matrix[i][size - 1 - i];
    }

    if (target_sum != secondary_diag_sum) return false;

    for (int i = 0; i < size; i++) {
        long long row_sum = 0;
        for (int j = 0; j < size; j++) {
            row_sum += matrix[i][j];
        }
        if (row_sum != target_sum) return false;
    }

    for (int i = 0; i < size; i++) {
        long long col_sum = 0;
        for (int j = 0; j < size; j++) {
            col_sum += matrix[j][i];
        }
        if (col_sum != target_sum) return false;
    }

    return true;
}

int main() {
    int m;
    std::cout << "Enter size: ";
    std::cin >> m;
    
    std::vector<std::vector<int>> matrix(m, std::vector<int>(m));
    std::cout << "Enter elements: " << '\n';
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> matrix[i][j];
        }
    }
    
    if (is_magic_square(matrix, m)) {
        std::cout << "It is a magic square!\n";
    } else {
        std::cout << "Not a magic square!\n";
    }
    return 0;
}
