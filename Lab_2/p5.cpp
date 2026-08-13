#include<iostream>
#include<vector>
#include<utility>
#include<algorithm>

int M, N;
std::vector<std::vector<int>> matrix;

void find_saddle_points(std::vector<std::vector<int>> matrix){
    
    std::vector<std::pair<int, int>> row_temp_saddle, col_temp_saddle;
    
    // row minimun
    for(int i = 0; i < M; i++){
        int current_row_min = *std::min_element(matrix[i].begin(), matrix[i].end());
        for(int j = 0; j < N; j++){
            if(matrix[i][j] == current_row_min){
                row_temp_saddle.push_back({i, j}); 
            }
        }
    }

    // col maxm
    for(int j = 0; j < N; j++){
        int current_col_max = matrix[0][j];
        for(int i = 0; i < M; i++){
            if(matrix[i][j] > current_col_max){
                current_col_max = matrix[i][j];
            }
        }

        for(int i = 0; i < M; i++){
            if(matrix[i][j] == current_col_max){
                col_temp_saddle.push_back({i, j});
            }
        }
    }

    // check if both (i,j) are present
    int flag = 0;
    for(const auto& r_pt : row_temp_saddle){
        for(const auto& c_pt : col_temp_saddle){
            if(r_pt.first == c_pt.first && r_pt.second == c_pt.second){
                flag = 1;
                std::cout << "found "<< matrix[r_pt.first][r_pt.second] 
                          << " idx: " << r_pt.first << " " << r_pt.second << '\n';
            }
        }
    }

    if(!flag) std::cout << "No saddle found!\n";
}

int main(){
    std::cout << "Enter (rows,cols): ";
    std::cin >> M >> N;
    matrix.resize(M, std::vector<int>(N));

    for(auto &row : matrix){
        for(auto &val : row){
            std::cin >> val;
        }
    }
    find_saddle_points(matrix);
    return 0;
}
