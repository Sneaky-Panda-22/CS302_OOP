#include <iostream>
#include <string>
#include <vector>

// color palette used for better printing. 
#define RESET     "\033[0m"
#define BOLD      "\033[1m"
#define COLOR_A   "\033[38;5;32m"  // Soft Matplotlib Blue
#define COLOR_B   "\033[38;5;208m" // Soft Matplotlib Orange
#define COLOR_POS "\033[38;5;28m"  // Deep Forest Green (High contrast for light theme)
#define COLOR_NEG "\033[38;5;124m" // Rich Crimson Red (High contrast for light theme)
#define COLOR_TXT "\033[38;5;240m" // Dark Gray for brackets/text
#define ARRAY_BLUE "\033[34m"      // The crisp blue for the NumpyArray numbers

// base class
class DataObject {
public:
    // Every derived class must override these pure virtual functions 
    virtual void display() = 0;
    virtual void info() = 0;

    // Shared functionality for all data objects.
    void show() {
        info();
        display();
    }

    // virtual destructor
    virtual ~DataObject() {}
};
class NumpyArray: public DataObject {
protected:
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
    friend std::istream& operator>>(std::istream&,NumpyArray&);

    // multiplying the numpy array with a scalar constant
    friend NumpyArray operator*(const double,const NumpyArray&);
    friend NumpyArray operator*(const NumpyArray&,const double);

    // matrix multiplication
    friend NumpyArray operator*(const NumpyArray&,const NumpyArray&);

    // element wise subtraction: (-) operator overloading
    friend NumpyArray operator-(const NumpyArray&,const NumpyArray&);

    // () overloading for accessing the individual array elements like arr(0,1) returns the element at position ->  ((0 * cols) + 1)
    double& operator()(int); // 1D array
    double& operator()(int,int);

    // print the shape of the numpy array
    std::string shape();

    // return the size of the numpy array (total number of elements inside it)
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

    // finding the transpose of the Numpy array
    NumpyArray transpose();

    // shorthand for writing transpose
    NumpyArray T();

    // reshape an array into another shape.
    NumpyArray reshape(int,int);
    
    // these functions are static as they dont need an object to call. they create new numpy arrays

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

    // Reverse elements along a specified axis
    NumpyArray flip(int axis = 0);

    // overriding the base class functions for polymorphism
    void display() override {
        printArray();
    }
    void info() override {
        std::cout << "Object type: NumpyArray" << '\n';
        std::cout << "Total elements: " << size() << '\n';
    }
};
// Class Numpy Array methods:

NumpyArray::NumpyArray(int size) {
    rows = 1; // row vector as its 1D
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
    // copy the object's data
    rows = obj.rows;
    cols = obj.cols;
    totalSize = obj.totalSize;

    // Allocate NEW independent memory on the heap
    data = new double[totalSize];
    for(int i=0;i<totalSize;i++)data[i] = obj.data[i];
}
void NumpyArray::setValue(int r, int c, double val) {
    // for any index(i,j): array[i][j] can be accessed by setting the index in 1D array as i * (no of columns) + j
    if (r < 0 || r >= rows || c < 0 || c >= cols) {
        std::cout << COLOR_NEG << "Error: Index out of bounds\n" << RESET;
        return;
    }
    int index = (r * cols) + c; 
    data[index] = val;
}
void NumpyArray::printArray() {
    std::cout << BOLD << "[\n" << RESET;
    for(int i = 0; i < rows; i++) {
        std::cout << "  [";
        for(int j = 0; j < cols; j++) {
            int index = (i * cols) + j;
            std::cout << ARRAY_BLUE << data[index] << RESET;
            if (j < cols - 1) std::cout << ", ";
        }
        std::cout << "]\n";
    }
    std::cout << BOLD << "]\n" << RESET;
}
NumpyArray& NumpyArray::operator=(const NumpyArray& obj) {
    // Prevent self-assignment (eg: a = a)
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
        std::cout << COLOR_NEG << "Error: Shape mismatch! (" << rows << ", " << cols 
          << ") and (" << obj.rows << ", " << obj.cols << ")\n" << RESET;
        return NumpyArray(0,0);// return empty array on failure
    }
    NumpyArray result(rows,cols);
    for(int i=0;i<totalSize;i++){
        result.data[i] = data[i] + obj.data[i]; // add element wise
    }
    return result;// return the resulting array
}
std::ostream& operator<<(std::ostream& dout, const NumpyArray& obj){
    dout << BOLD << "[\n" << RESET;
    for(int i = 0; i < obj.rows; i++) {
        dout << "  [";
        for(int j = 0; j < obj.cols; j++) {
            int index = (i * obj.cols) + j;
            dout << ARRAY_BLUE << obj.data[index] << RESET;
            if (j < obj.cols - 1) dout << ", ";
        }
        dout << "]\n";
    }
    dout << BOLD << "]\n" << RESET;
    return dout;
}
std::istream& operator>>(std::istream& din,NumpyArray& obj) {
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
        std::cout << COLOR_NEG << "Error: Shape mismatch! (" << a.rows << ", " << a.cols 
          << ") and (" << b.rows << ", " << b.cols << ")\n" << RESET;
        return NumpyArray(0,0);// return empty array on failure
    }
    NumpyArray result(a.rows,b.cols);
    for(int i=0;i<a.rows;i++){
        for(int j=0;j<b.cols;j++){
            double sum = 0;
            // calculate the dot product
            for(int k=0;k<a.cols;k++){
                // in general the matrix multiplication is given as a.data[i][k] + b.data[k][j]. Mapping the idea to 1D storage in our case leads to (i*a.cols)+k  and (k*b.cols)+j respectively as the indices.
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
        std::cout << COLOR_NEG << "Error: Shape mismatch! (" << a.rows << ", " <<  a.cols 
          << ") and (" << b.rows << ", " << b.cols << ")\n" << RESET;
        return NumpyArray(0,0);// return empty array on failure
    }
    NumpyArray res(a.rows,a.cols);
    for(int i=0;i<a.totalSize;i++)res.data[i] = a.data[i] - b.data[i];
    return res;
}
double& NumpyArray::operator()(int i){
    if(i < 0 || i >= totalSize){
        std::cout << COLOR_NEG << "Error: Index out of bounds\n" << RESET;
        return data[0]; // fallback to first element in case of invalid index
    }
    return data[i];// return the element at the index i
}
double& NumpyArray::operator()(int i,int j){
    if(i < 0 || i >= rows || j < 0 || j >= cols){
        std::cout << COLOR_NEG << "Error: Index out of bounds\n" << RESET;
        return data[0]; // fallback to first element in case of invalid index
    }
    return data[i*cols+ j];// return the element (i,j)
}
std::string NumpyArray::shape(){
    // printing the result in a tuple for a more intuitive and pythonic way
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
        std::cout << COLOR_NEG << "Error: Invalid axis!\n" << RESET;
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
        std::cout << COLOR_NEG << "Error: Invalid axis!\n" << RESET;
        return NumpyArray(0,0); // return an empty array if error occoured
    }
    NumpyArray res = sum(axis);
    if(axis==0) for(int c=0;c<cols;c++) res(c)/=rows;
    else for(int r=0;r<rows;r++) res(r)/=cols;
    return res;
}
NumpyArray NumpyArray::min(int axis) {
    if(axis!=0 && axis!=1){
        std::cout << COLOR_NEG << "Error: Invalid axis!\n" << RESET;
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
        std::cout << COLOR_NEG << "Error: Invalid axis!\n" << RESET;
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
    NumpyArray result(cols, rows); // swapped rows and cols
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result.data[j * rows + i] = data[i * cols + j]; // transpose_a[j][i] = a[i][j];
        }
    }
    return result;
}
NumpyArray NumpyArray::T(){return this->transpose();}

NumpyArray NumpyArray::reshape(int newRow,int newCol){
    // check if its reshaping compatible
    if (newRow * newCol != totalSize) {
        std::cout << COLOR_NEG << "Error: Cannot reshape array of size " << totalSize 
                  << " into (" << newRow << ", " << newCol << ")\n" << RESET;
        return NumpyArray(0,0);
    }
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
    // invalid 
    if (row < 0 || row >= rows) {
        std::cout << COLOR_NEG << "Error: Row index out of bounds\n" << RESET;
        return NumpyArray(0, 0);
    }

    NumpyArray result(cols);

    for (int j = 0; j < cols; j++) {
        result(j) = data[row * cols + j];
    }
    return result;
}

NumpyArray NumpyArray::getColumn(int col) {
    // invalid
    if (col < 0 || col >= cols) {
        std::cout << COLOR_NEG << "Error: Column index out of bounds\n" << RESET;
        return NumpyArray(0, 0);
    }

    NumpyArray result(rows);

    for (int i = 0; i < rows; i++) {
        result(i) = data[i * cols + col];
    }
    return result;
}
NumpyArray NumpyArray::slice(int start, int stop) {
    // invalid
    if (start < 0 || stop > totalSize || start >= stop) {
        std::cout << COLOR_NEG << "Error: Invalid slice indices\n" << RESET;
        return NumpyArray(0, 0);
    }

    NumpyArray result(stop - start);

    for (int i = start; i < stop; i++) {
        result(i - start) = data[i];
    }
    return result;
}

NumpyArray NumpyArray::slice(int rowStart, int rowStop, int colStart, int colStop) {
    // invalid
    if (rowStart < 0 || rowStop > rows || rowStart >= rowStop || 
        colStart < 0 || colStop > cols || colStart >= colStop) {
        std::cout << COLOR_NEG << "Error: Invalid slice indices\n" << RESET;
        return NumpyArray(0, 0);
    }

    int newRows = rowStop - rowStart;
    int newCols = colStop - colStart;

    NumpyArray result(newRows, newCols);
    for (int i = rowStart; i < rowStop; i++) {
        for (int j = colStart; j < colStop; j++) {
            result((i - rowStart), (j - colStart)) = data[i * cols + j];
        }
    }
    return result;
}
NumpyArray NumpyArray::flip(int axis) {
    NumpyArray result(rows, cols);

    // 1D array: reverse all elements
    if (rows == 1) {
        for (int i = 0; i < totalSize; i++) {
            result.data[i] = data[totalSize - 1 - i];
        }
    }

    // 2D array: reverse the rows
    else if (axis == 0) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[i * cols + j] =
                    data[(rows - 1 - i) * cols + j];
            }
        }
    }

    // 2D array: reverse the columns
    else if (axis == 1) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[i * cols + j] =
                    data[i * cols + (cols - 1 - j)];
            }
        }
    }

    else {
        std::cout << COLOR_NEG << "Error: Invalid axis!\n" << RESET;
        return NumpyArray(0, 0);
    }
    return result;
}

class Cplot: public NumpyArray {
public:
    // Constructors
    Cplot(int size);
    Cplot(int r, int c);
    Cplot(const NumpyArray& obj);

    // Overridden Functions
    void info() override;
    void display() override;

    // Visualization Methods
    void compare(NumpyArray other);
    void heatmap();
};
// Constructors call the base class constructors
Cplot::Cplot(int size) : NumpyArray(size) {}
Cplot::Cplot(int r, int c) : NumpyArray(r, c) {}
Cplot::Cplot(const NumpyArray& obj) : NumpyArray(obj) {}

void Cplot::info() {
    std::cout << "Object type: Cplot\n";
    std::cout << "Total data points: " << size() << '\n';
}

void Cplot::display() {
    if (ndim() == 1) {
        std::cout << BOLD << "\n--- Terminal Histogram ---\n" << RESET;
        for (int i = 0; i < size(); i++) {
            std::cout << COLOR_TXT << "[" << i << "] | " << COLOR_A;
            int val = static_cast<int>((*this)(i)); 
            for (int j = 0; j < val; j++) std::cout << "█";
            std::cout << RESET << COLOR_TXT << " (" << (*this)(i) << ")\n" << RESET;
        }
        std::cout << COLOR_TXT << "--------------------------\n" << RESET;
        std::cout << BOLD << "Max: " << COLOR_POS << max() 
                  << RESET << BOLD << " | Min: " << COLOR_NEG << min() 
                  << RESET << BOLD << " | Mean: " << COLOR_A << mean() << RESET << "\n\n";
    } else {
        NumpyArray::printArray(); 
    }
}

void Cplot::compare(NumpyArray other) {
    if(size() != other.size()) {
        std::cout << COLOR_NEG << "Error: Array must be of same size to compare\n" << RESET;
        return;
    }
    
    NumpyArray diff = *this - other; 
    
    std::cout << BOLD << "\n--- Comparative Bar Chart ---\n" << RESET;
    for (int i = 0; i < size(); i++) {
        std::cout << BOLD << COLOR_TXT << "Idx[" << i << "]\n" << RESET;
        
        std::cout << COLOR_TXT << "  A: " << COLOR_A;
        for (int j = 0; j < static_cast<int>((*this)(i)); j++) std::cout << "█";
        std::cout << RESET << COLOR_TXT << " (" << (*this)(i) << ")\n" << RESET;
        
        std::cout << COLOR_TXT << "  B: " << COLOR_B;
        for (int j = 0; j < static_cast<int>(other(i)); j++) std::cout << "█";
        std::cout << RESET << COLOR_TXT << " (" << other(i) << ")\n" << RESET;
        
        std::cout << COLOR_TXT << "  Δ: " << RESET;
        double d = diff(i);
        if (d == 0) {
            std::cout << COLOR_POS << "MATCH\n" << RESET;
        } else {
            std::cout << (d > 0 ? COLOR_A : COLOR_NEG) << (d > 0 ? "+" : "") << d << RESET << "\n";
        }
        std::cout << "\n";
    }
}
void Cplot::heatmap(){
    if(ndim() != 2){
        std::cout << COLOR_NEG << "Error: Heatmap requires a 2D matrix.\n" << RESET;
        return;
    }
    double min_v = min();
    double max_v = max();
    double range = max_v - min_v;

    // smooth 25-step ANSI color gradient(Blue,cyan,green,yellow,red)
    const int gradient[] = {
        17, 18, 19, 20, 21, 27, 33, 39, 45, 51,     // Dark Blues to Cyan
        50, 49, 48, 47, 46, 82, 118, 154, 190, 226, // Cyan to Green to Yellow
        220, 214, 208, 202, 196                     // Yellow to Orange to Red
    };
    const int num_colors = sizeof(gradient)/sizeof(gradient[0]); // 25
    std::cout << BOLD << "\n 2D Heatmap (" << rows << "x" << cols << ")\n" << RESET;

    // drawing matrix grid
    for(int r=0 ; r<rows ; r++) {
        std::cout<<" ";
        for(int c=0 ; c<cols ; c++) {
            int color_idx = 0;
            if(range !=0){
                // normalise values between 0.0 and 1.0
                double normalised = ((*this)(r,c) - min_v) / range;
                color_idx = static_cast<int>(normalised * (num_colors - 1));

                // safety clamping
                if(color_idx < 0) color_idx = 0;
                if(color_idx >= num_colors) color_idx = num_colors - 1;
            }
            // Print 2 spaces with the exact background color mapped to this value
            std::cout << "\033[48;5;" << gradient[color_idx] << "m  " << RESET;
        }
        std::cout << '\n';
    }
    // color bar legend
    std::cout << "\n  Legend:  " << min_v << " ";
    for (int i = 0; i < num_colors; i++) {
        std::cout << "\033[48;5;" << gradient[i] << "m " << RESET;
    }
    std::cout << " " << max_v << "\n\n";
}

int main() {
    std::cout << BOLD << "\n--- Array Creation & Properties ---\n" << RESET;

    NumpyArray arr1D(5); 
    std::cout << "1D Array:\n" << arr1D;
    std::cout << "Shape: " << arr1D.shape() << " | ndim: " << arr1D.ndim() << " | size: " << arr1D.size() << "\n\n";

    NumpyArray zeros = NumpyArray::zeros(2, 3);
    std::cout << "Zeros (2x3):\n" << zeros;

    NumpyArray ones = NumpyArray::ones(3, 2);
    std::cout << "Ones (3x2):\n" << ones;

    NumpyArray eyeMatrix = NumpyArray::eye(3);
    std::cout << "Identity Matrix (3x3):\n" << eyeMatrix;

    NumpyArray seq = NumpyArray::arange(1, 13, 1); 
    std::cout << "Arange (1 to 12):\n" << seq;

    std::cout << BOLD << "\n--- Access, Modification & Copying ---\n" << RESET;

    NumpyArray m1 = seq.reshape(3, 4);
    std::cout << "Reshaped Arange (m1 3x4):\n" << m1;

    m1.setValue(0, 0, 99); 
    m1(1, 1) = 88;         
    std::cout << "After modifying (0,0) and (1,1):\n" << m1;

    NumpyArray mCopy(m1);  
    mCopy(2, 3) = 77;
    std::cout << "Copy Constructor (Modified 2,3 - should not affect m1):\n" << mCopy;

    NumpyArray mAssign = NumpyArray::zeros(2, 2);
    mAssign = m1;          
    std::cout << "Assignment Operator (Assigned from m1):\n" << mAssign;

    std::cout << BOLD << "\n--- Slicing & Structural Manipulation ---\n" << RESET;

    std::cout << "Transpose (m1.T()):\n" << m1.T();
    std::cout << "Flipped (axis=0, reverse rows):\n" << m1.flip(0);
    std::cout << "Flipped (axis=1, reverse cols):\n" << m1.flip(1);
    
    std::cout << "Get Row 1:\n" << m1.getRow(1);
    std::cout << "Get Column 2:\n" << m1.getColumn(2);
    
    std::cout << "1D Slice (seq indices 3 to 7):\n" << seq.slice(3, 7);
    std::cout << "2D Slice (m1 rows 0-2, cols 1-3):\n" << m1.slice(0, 2, 1, 3);

    std::cout << BOLD << "\n--- Math & Matrix Operations ---\n" << RESET;

    NumpyArray A = NumpyArray::arange(1, 5, 1).reshape(2, 2);
    NumpyArray B = NumpyArray::ones(2, 2) * 3.0; 

    std::cout << "Matrix A:\n" << A;
    std::cout << "Matrix B (Ones * 3):\n" << B;
    std::cout << "A + B:\n" << A + B;
    std::cout << "A - B:\n" << A - B;
    std::cout << "Matrix Multiplication (A * B):\n" << A * B;

    std::cout << BOLD << "\n--- Aggregations ---\n" << RESET;

    std::cout << "A Overall Sum:  " << COLOR_POS << A.sum() << RESET << "\n";
    std::cout << "A Overall Mean: " << COLOR_POS << A.mean() << RESET << "\n";
    std::cout << "A Overall Max:  " << COLOR_POS << A.max() << RESET << "\n";
    std::cout << "A Overall Min:  " << COLOR_POS << A.min() << RESET << "\n\n";

    std::cout << "A Sum (axis=0 / across rows):\n" << A.sum(0);
    std::cout << "A Max (axis=1 / across cols):\n" << A.max(1);

    std::cout << BOLD << "\n--- Cplot: Polymorphism & 1D Visuals ---\n" << RESET;

    Cplot plotA(5);
    for(int i=0; i<5; i++) plotA(i) = (i+1) * 3; 

    DataObject* objPtr = &plotA;
    std::cout << BOLD << "Polymorphic show() call:" << RESET << "\n";
    objPtr->show(); 

    Cplot plotB(5);
    for(int i=0; i<5; i++) plotB(i) = (i+1) * 2 + (i%2); 
    
    plotA.compare(plotB);

    std::cout << BOLD << "\n--- Cplot: 2D Heatmap ---\n" << RESET;

    // Increased to a 15x40 grid with a center-focused thermal ring formula
    Cplot heatData(15, 40);
    for (int r = 0; r < 15; r++) {
        for (int c = 0; c < 40; c++) {
            double dr = r - 7.0;
            double dc = (c - 19.5) / 1.5; // Scale column distance to account for terminal character height
            heatData(r, c) = -(dr * dr + dc * dc); // Negative values create a hot center that cools outward
        }
    }
    heatData.heatmap();

    std::cout << BOLD << "\n--- Error Handling (Expected Failures) ---\n" << RESET;

    std::cout << "\nTest: Out of bounds (1D & 2D)\n";
    seq(50) = 1;
    m1.setValue(10, 10, 1);

    std::cout << "\nTest: Shape mismatch (+, -, *)\n";
    NumpyArray errRes1 = m1 + A;
    NumpyArray errRes2 = m1 - A;
    NumpyArray errRes3 = m1 * m1; 

    std::cout << "\nTest: Invalid Reshape\n";
    NumpyArray errReshape = m1.reshape(5, 5); 

    std::cout << "\nTest: Invalid Slicing\n";
    m1.slice(10, 15);
    m1.slice(2, 1, 0, 2); 

    std::cout << "\nTest: Invalid Aggregation Axis\n";
    m1.sum(5);
    m1.max(5);

    std::cout << "\nTest: Heatmap on 1D Cplot array\n";
    plotA.heatmap();

    std::cout << BOLD << "\nEOP\n" << RESET;
    return 0;
}