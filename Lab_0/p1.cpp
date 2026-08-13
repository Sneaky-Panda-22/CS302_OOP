#include<iostream>

int** multiply_matrix(int** matrix1, int** matrix2, int size){
    int** ans = new int*[size];
    for(int i=0;i<size;i++){
        ans[i] = new int[size];
    }
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            long long sum = 0;
            for(int k=0;k<size;k++){
                sum+=(matrix1[i][k]*matrix2[k][j]);
            }
            ans[i][j] = sum;
        }
    }
    return ans;
}

void print_matrix(int** matrix, int size){
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            std::cout << matrix[i][j] << " ";
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

void find_transpose(int** matrix, int size){
    for(int i=0;i<size;i++){
        for(int j=i+1;j<size;j++){
            int temp = *(*(matrix + i) + j);
            *(*(matrix + i) + j) = *(*(matrix + j) + i);
            *(*(matrix + j) + i) = temp; 
        }
    }
}

int main(){
    int n; //size of n*n matrix
    std::cout << "Enter size: ";
    std::cin >> n;

    int** matrix1 = new int*[n];
    int** matrix2 = new int*[n];
    int** ans = new int*[n];
    
    for(int i=0;i<n;i++){
        matrix1[i] = new int[n];
        matrix2[i] = new int[n];
        ans[i] = new int[n];
    }
    std::cout << "Enter elements of matrix1:\n";
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            std::cin >> matrix1[i][j];
        }
    }

    find_transpose(matrix1, n); //find matrix transpose
    std::cout << "Transpose of matrix 1:\n";
    print_matrix(matrix1, n);
    find_transpose(matrix1, n);//revert to orig

    std::cout << "Enter elements of matrix 2:\n";
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            std::cin >> matrix2[i][j];
        }
    }
    std::cout << "Matrix multiplication :\n";
    print_matrix(multiply_matrix(matrix1,matrix2,n), n);
    return 0;
}