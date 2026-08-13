#include<iostream>
#include<vector>
int M,N;
std::vector<std::vector<int>>matrix;
std::vector<std::vector<bool>>visited;

void dfs(int i,int j){
    if(i<0 || i>=M || j<0 || j>=N)return;
    if(matrix[i][j]==1)return;
    if(visited[i][j])return;

    visited[i][j] = true;
    dfs(i,j+1);//right
    dfs(i+1,j);//left
}

int main(){
    std::cout << "Enter (rows,cols): ";
    std::cin >> M >> N;
    matrix.resize(M,std::vector<int>(N));
    visited.resize(M,std::vector<bool>(N,false));

    std::cout << "Enter elements: \n";
    for(auto &row:matrix){
        for(auto &val:row){
            std::cin >> val;
        }
    }

    dfs(0,0);

    if(visited[M-1][N-1]){
        std::cout << "YES\n";
    }else{
        std::cout << "NO\n";
    }
    return 0;
}