#include<iostream>
#include<string>

class NumpyArray {
private:
    double* data;
    int rows;
    int cols;
    int totalSize;
public:
    // Constructor for 1D array
    NumpyArray(int);
    // Constructor for 2D array
    NumpyArray(int,int);
    // Copy constructor
    NumpyArray(const NumpyArray&);
    // Destructor 
    ~NumpyArray() {delete[] data;}
    // Function to set a value using 2D coordinates
    void setValue(int,int,double);
    // Function to print the array
    void printArray();
    // assignment operator overloading(a=b)
    NumpyArray& operator=(const NumpyArray&);
    // + operator overloading. in numpy, all arithmetic operations are element wise operations. thus for two numpy arrays, there shape must be same for element wise addition
    NumpyArray operator+(const NumpyArray&);
    // << operator overloading for easier and more intuitive way of printing the numpy array
    friend std::ostream& operator<<(std::ostream&,const NumpyArray&);
    // >> operator overloading for easier input from user
    friend std::istream& operator>>(std::istream&,const NumpyArray&);
    // multiplying the numpy array with a scalar constant
    friend NumpyArray operator*(const double,const NumpyArray&);
    friend NumpyArray operator*(const NumpyArray&,const double);
    // matrix multiplication
    friend NumpyArray operator*(const NumpyArray&,const NumpyArray&);
    // element wise subtraction: - operator overloading
    friend NumpyArray operator-(const NumpyArray&,const NumpyArray&);
    // () overloading for accessing the individual array elements like arr(0,1) returns the element at pos. 0*cols+1
    double& operator()(int); // 1D array
    double& operator()(int,int);
    // print the shape of the numpy array
    std::string shape();
    // return the size of the numpy array
    int size();
    // return the dimension of the array. 1D / 2D
    int ndim();
    // finding sum. if axis is specified, we find sum across that axis. 
    // else we return the sum of entire numpy array
    NumpyArray sum(int);
    double sum();
    // finding mean along specified axis. if not specified, we find the mean of entire array
    NumpyArray mean(int);
    double mean();
    // finding minimun along specified axis. if not specified, we find from entire array
    NumpyArray min(int);
    double min();
    // finding maximum along specified axis. if not specified, we find from entire array
    NumpyArray max(int);
    double max();
    // finding the transpose of an array
    NumpyArray transpose();
    // shorthand for writing transpose
    NumpyArray T();
    // reshape an array into another shape.
    NumpyArray reshape(int,int);
    
    // these functions are static as they dont need an object to call. they create new arrays
    // creating an array with all zeros
    static NumpyArray zeros(int,int);
    // creating an array with all ones
    static NumpyArray ones(int,int);
    // creating identity matrix
    static NumpyArray eye(int);
    // generating a sequnece within start and stop range of a given step size
    static NumpyArray arange(int,int,int);

    // row selection
    NumpyArray getRow(int);
    // column selection
    NumpyArray getColumn(int);
    // in splicing, the end index is not included!
    // 1D slicing
    NumpyArray slice(int,int);
    // 2D slicing
    NumpyArray slice(int,int,int,int);
};

NumpyArray::NumpyArray(int size) {
    rows = 1;
    cols = size;
    totalSize = size;
    data = new double[totalSize];
    // Initialise the array with zeros
    for(int i=0;i<totalSize;i++)data[i] = 0.0;
}
NumpyArray::NumpyArray(int r,int c) {
    rows = r;
    cols = c;
    totalSize = r * c;
    data = new double[totalSize];
    // Initialise the array with zeros
    for(int i=0;i<totalSize;i++)data[i] = 0.0;
}
NumpyArray::NumpyArray(const NumpyArray& obj) {
    rows = obj.rows;
    cols = obj.cols;
    totalSize = obj.totalSize;
    // Allocate NEW independent memory on the heap
    data = new double[totalSize];
    for(int i=0;i<totalSize;i++)data[i] = obj.data[i];
}
void NumpyArray::setValue(int r, int c, double val) {
    // for any index(i,j): array[i][j] can be accessed by setting the index in 1D array as i * (no of columns) + j
    int index = (r * cols) + c; 
    data[index] = val;
}
void NumpyArray::printArray() {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            int index = (i * cols) + j;
            std::cout << data[index] << "\t";
        }
        std::cout << "\n";
    }
}
NumpyArray& NumpyArray::operator=(const NumpyArray& obj) {
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
NumpyArray NumpyArray::operator+(const NumpyArray& obj) {
    // for two numpy arrays to be addition compatible, they must have same shape for element wise addition
    if(rows!=obj.rows || cols!=obj.cols){
        std::cout<<"Shape Error! ("<<rows<<", "<<cols<<") and ("<<obj.rows<<", "<<obj.cols<<")\n";
        return NumpyArray(0,0);// return empty array on failure
    }
    NumpyArray result(rows,cols);
    for(int i=0;i<totalSize;i++){
        result.data[i] = data[i] + obj.data[i]; // add element wise
    }
    return result;// return the resulting array
}
std::ostream& operator<<(std::ostream& dout,const NumpyArray& obj){
    for(int i=0;i<obj.rows;i++){
        for(int j=0;j<obj.cols;j++){
            int index = (i*obj.cols)+j;
            dout << obj.data[index] << "\t";// output the data
        }
        dout << '\n';
    }
    return dout;// return refernce
}
std::istream& operator>>(std::istream& din,const NumpyArray& obj) {
    std::cout<<"Enter "<<obj.totalSize<<" Elements:\n";
    for(int i=0;i<obj.totalSize;i++)din>>obj.data[i];// take input
    return din; // return refernece
}
NumpyArray operator*(const double k,const NumpyArray& obj){
    NumpyArray result(obj.rows,obj.cols);// to store the resulting array
    for(int i=0;i<obj.totalSize;i++)result.data[i] = k*(obj.data[i]);// scale the array with constant k
    return result;
}
NumpyArray operator*(const NumpyArray& obj,const double k){
    NumpyArray result(obj.rows,obj.cols);// to store the resulting array
    for(int i=0;i<obj.totalSize;i++)result.data[i] = k*(obj.data[i]);// scale the array with constant k
    return result;
}
NumpyArray operator*(const NumpyArray& a,const NumpyArray& b){
    if(a.cols!=b.rows){
        std::cout<<"Shape Error! ("<<a.rows<<", "<<a.cols<<") and ("<<b.rows<<", "<<b.cols<<")\n";
        return NumpyArray(0,0);// return empty array on failure
    }
    NumpyArray result(a.rows,b.cols);
    for(int i=0;i<a.rows;i++){
        for(int j=0;j<b.cols;j++){
            double sum = 0;
            // calculate the dot product
            for(int k=0;k<a.cols;k++){
                // in general the matrix multiplication is given as a.data[i][k] + b.data[k][j] to 1D as (i*a.cols)+k  and (k*b.cols)+j respectively
                int indexA = (i*a.cols) + k; // strore the index of array a
                int indexB = (k*b.cols) + j; // strore the index of array b
                sum += (a.data[indexA]*b.data[indexB]);
            }
            // the final index will be in an array of dimensions (a.rows,b.cols). hence to access any index (i,j) inside the resultant array, the resultIndex = (i*b.cols)+j
            int resultIndex = (i*b.cols) + j;
            result.data[resultIndex] = sum;
        }
    }
    return result;
}
NumpyArray operator-(const NumpyArray& a,const NumpyArray& b) {
    if(a.rows!=b.rows || a.cols!=b.cols){
        std::cout<<"Shape Error! ("<<a.rows<<", "<<a.cols<<") and ("<<b.rows<<", "<<b.cols<<")\n";
        return NumpyArray(0,0);// return empty array on failure
    }
    NumpyArray res(a.rows,a.cols);
    for(int i=0;i<a.totalSize;i++)res.data[i] = a.data[i] - b.data[i];
    return res;
}
double& NumpyArray::operator()(int i){
    return data[i];
}
double& NumpyArray::operator()(int i,int j){
    return data[i*cols+ j];
}
std::string NumpyArray::shape(){
    if(rows == 1) {
        return "(" + std::to_string(cols) + ",)";
    }else{
        return "(" + std::to_string(rows) + ", " + std::to_string(cols) + ")";
    }
}
int NumpyArray::size(){return totalSize;}
int NumpyArray::ndim(){
    if(rows == 1) return 1;
    else return 2;
}
double NumpyArray::sum(){ // works for both 1D and 2D arrays
    double total = 0;
    for(int i=0;i<totalSize;i++)total+=data[i];
    return total;
}
NumpyArray NumpyArray::sum(int axis){
    if(axis != 0 && axis != 1){
        std::cout<<"Invalid axis! \n";
        return NumpyArray(0,0); // return an empty array if error occoured
    }
    if(axis == 0) {
        NumpyArray res(cols);
        for(int c=0;c<cols;c++){
            double total = 0;
            for(int r=0;r<rows;r++){
                total += data[r*cols + c];
            }
            res(c) = total;
        }
        return res;
    }
    else{
        NumpyArray res(rows);
        for(int r=0;r<rows;r++){
            double total = 0;
            for(int c=0;c<cols;c++){
                total += data[r*cols + c];
            }
            res(r) = total;
        }
        return res;
    }
}
double NumpyArray::mean(){
    return sum()/this->totalSize;
}
NumpyArray NumpyArray::mean(int axis){
    if(axis!=0 && axis!=1){
        std::cout<<"Invalid axis! \n";
        return NumpyArray(0,0); // return an empty array if error occoured
    }
    NumpyArray res = sum(axis);
    if(axis==0) for(int c=0;c<cols;c++) res(c)/=rows;
    else for(int r=0;r<rows;r++) res(r)/=cols;
    return res;
}
NumpyArray NumpyArray::min(int axis) {
    if(axis!=0 && axis!=1){
        std::cout<<"Invalid axis! \n";
        return NumpyArray(0,0); // return an empty array if error occoured
    }
    if (axis == 0) {
        NumpyArray result(cols);
        for (int c = 0; c < cols; c++) {
            double smallest = data[c];
            for (int r = 1; r < rows; r++) {
                if (data[r * cols + c] < smallest) {
                    smallest = data[r * cols + c];
                }
            }
            result(c) = smallest;
        }
        return result;
    }
    NumpyArray result(rows);
    for (int r = 0; r < rows; r++) {
        double smallest = data[r * cols];
        for (int c = 1; c < cols; c++) {
            if (data[r * cols + c] < smallest) {
                smallest = data[r * cols + c];
            }
        }
        result(r) = smallest;
    }
    return result;
}
double NumpyArray::min() {
    double result = data[0];
    for (int i = 1; i < totalSize; i++) {
        if (data[i] < result) {
            result = data[i];
        }
    }
    return result;
}
NumpyArray NumpyArray::max(int axis) {
    if(axis!=0 && axis!=1){
        std::cout<<"Invalid axis! \n";
        return NumpyArray(0,0); // return an empty array if error occoured
    }
    if (axis == 0) {
        NumpyArray result(cols);
        for (int c = 0; c < cols; c++) {
            double largest = data[c];
            for (int r = 1; r < rows; r++) {
                if (data[r * cols + c] > largest) {
                    largest = data[r * cols + c];
                }
            }
            result(c) = largest;
        }
        return result;
    }
    NumpyArray result(rows);
    for (int r = 0; r < rows; r++) {
        double largest = data[r * cols];
        for (int c = 1; c < cols; c++) {
            if (data[r * cols + c] > largest) {
                largest = data[r * cols + c];
            }
        }
        result(r) = largest;
    }
    return result;
}
double NumpyArray::max() {
    double result = data[0];
    for (int i = 1; i < totalSize; i++) {
        if (data[i] > result) {
            result = data[i];
        }
    }
    return result;
}
NumpyArray NumpyArray::transpose() {
    NumpyArray result(cols, rows);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result.data[j * rows + i] = data[i * cols + j];
        }
    }
    return result;
}
NumpyArray NumpyArray::T(){return this->transpose();}

NumpyArray NumpyArray::reshape(int newRow,int newCol){
    NumpyArray newarr(newRow,newCol);
    for(int i=0;i<this->totalSize;i++) newarr.data[i] = this->data[i];
    return newarr;
}
NumpyArray NumpyArray::zeros(int rows, int cols) {
    return NumpyArray(rows, cols);
}
NumpyArray NumpyArray::ones(int rows, int cols) {
    NumpyArray result(rows, cols);
    for (int i = 0; i < result.totalSize; i++) {
        result.data[i] = 1;
    }
    return result;
}
NumpyArray NumpyArray::eye(int size) {
    NumpyArray result(size, size);
    for (int i = 0; i < size; i++) {
        result.data[i * size + i] = 1;
    }
    return result;
}
NumpyArray NumpyArray::arange(int start, int stop, int step=1) {
    int count = 0;
    for (int i = start; i < stop; i += step) {
        count++;
    }
    NumpyArray result(count);

    int index = 0;
    for (int i = start; i < stop; i += step) {
        result(index++) = i;
    }
    return result;
}
NumpyArray NumpyArray::getRow(int row) {
    NumpyArray result(cols);

    for (int j = 0; j < cols; j++) {
        result(j) = data[row * cols + j];
    }

    return result;
}
NumpyArray NumpyArray::getColumn(int col) {
    NumpyArray result(rows);

    for (int i = 0; i < rows; i++) {
        result(i) = data[i * cols + col];
    }

    return result;
}
NumpyArray NumpyArray::slice(int start, int stop) {
    NumpyArray result(stop - start);

    for (int i = start; i < stop; i++) {
        result(i - start) = data[i];
    }

    return result;
}
NumpyArray NumpyArray::slice(int rowStart, int rowStop,int colStart, int colStop) {
    int newRows = rowStop - rowStart;
    int newCols = colStop - colStart;

    NumpyArray result(newRows, newCols);
    for (int i = rowStart; i < rowStop; i++) {
        for (int j = colStart; j < colStop; j++) {
            result((i - rowStart), (j - colStart)) =
                data[i * cols + j];
        }
    }
    return result;
}
int main() {
    NumpyArray A(3, 4);

    int value = 1;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            A(i, j) = value++;
        }
    }

    std::cout << "Original array:\n" << A;

    NumpyArray part = A.slice(0, 2, 1, 3);

    std::cout << "\nSliced array:\n" << part;

    return 0;
}