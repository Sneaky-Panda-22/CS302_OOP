#include<iostream>
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

int main(){
    int r1,r2,c1,c2;
    std::cout<<"Enter (rows,cols): ";
    std::cin>>r1>>c1;
    NumpyArray arr1(r1,c1);
    std::cout<<"Enter "<<r1*c1<<" Elements: ";
    for(int i=0;i<r1;i++){
        for(int j=0;j<c1;j++){
            double x;std::cin>>x;
            arr1.setValue(i,j,x);
        }
    }
    arr1.printArray();
    std::cout<<"\nEnter (rows,cols): ";
    std::cin>>r2>>c2;
    NumpyArray arr2(r2,c2);
    std::cout<<"Enter "<<r2*c2<<" Elements: ";
    // for(int i=0;i<r2;i++){
    //     for(int j=0;j<c2;j++){
    //         double x;std::cin>>x;
    //         arr2.setValue(i,j,x);
    //     }
    // }
    std::cin >> arr2;
    arr2.printArray();
    std::cout<<"\nArray3 = Array1 + Array2\n";
    NumpyArray arr3 = arr1 + arr2;
    std::cout << arr3;
    std::cout << "\nArray3*2\n";
    arr3 = arr3*2;
    std::cout<<arr3;
    std::cout << "\n4*Array3\n";
    arr3 = 4*arr3;
    std::cout<<arr3;
    std::cout << "\nArray1*Array2: \n";
    NumpyArray res = arr1*arr2;
    std::cout << res;
}