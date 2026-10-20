#include<iostream>
class NumpyArray {
private:
    double* data;
    int rows;
    int cols;
    int totalSize;
public:
    // Constructor for 1D array
    NumpyArray(int size) {
        rows = 1;
        cols = size;
        totalSize = size;
        data = new double[totalSize];
        // Initialise the array with zeros
        for(int i=0;i<totalSize;i++)data[i] = 0.0;
    }

    // Constructor for 2D array
    NumpyArray(int r,int c) {
        rows = r;
        cols = c;
        totalSize = r * c;
        data = new double[totalSize];
        // Initialise the array with zeros
        for(int i=0;i<totalSize;i++)data[i] = 0.0;
    }

    // Copy constructor
    NumpyArray(const NumpyArray& obj) {
        rows = obj.rows;
        cols = obj.cols;
        totalSize = obj.totalSize;
        // Allocate NEW independent memory on the heap
        data = new double[totalSize];
        for(int i=0;i<totalSize;i++)data[i] = obj.data[i];
    }

    // Destructor 
    ~NumpyArray() {
        delete[] data;
    }

    // Function to set a value using 2D coordinates
    void setValue(int r, int c, double val) {
        // for any index(i,j): array[i][j] can be accessed by setting the index in 1D array as i * (no of columns) + j
        int index = (r * cols) + c; 
        data[index] = val;
    }
    // Function to print the array
    void print() {
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++) {
                int index = (i * cols) + j;
                std::cout << data[index] << " ";
            }
            std::cout << "\n";
        }
    }

    // assignment operator overloading(a=b)
    NumpyArray& operator=(const NumpyArray& obj) {
        // Prevent self-assignment (e.g., a = a)
        if(this==&obj) return *this;
        // clean old memory as earlier a was pointing to some array. now we have to change the reference to b so we muct clear old memory
        delete[] data;

        // allocate new memory and copy data inside
        rows = obj.rows;
        cols = obj.cols;
        totalSize = obj.totalSize;
        data = new double[totalSize];
        for(int i=0;i<totalSize;i++)data[i] = obj.data[i];
        return *this;
    }
    
};
int main(){
    int r=5,c=2;
    NumpyArray nparray(r,c);
    for(int row=0;row<r;row++){
        for(int col=0;col<c;col++){
            nparray.setValue(row,col,row+1);
        }
    }
    nparray.print();
}