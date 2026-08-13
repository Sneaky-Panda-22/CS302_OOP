#include<iostream>
#include<vector>
#include<list>

int main(){
    std::vector<std::list<int>>hash(10);//hash table
    //hash func: h(x) = x%10

    std::cout << "Enter choice: \n" << "1.Insert\n" << "2.Search\n" << "3.Delete\n" << "4.Display\n" << "-1.EXIT\n";

    while(1){
        int x;
        std::cout << "Enter choice: ";
        std::cin >> x;
        if(x==1){
            int val;
            std::cout << "Enter val: ";
            std::cin >> val;
            //insert into hash table.
            hash[val%10].push_back(val);
        }
        else if(x==2){
            int val;
            std::cout << "Enter val to search: ";
            std::cin >> val;

            if(std::find(hash[val%10].begin(),hash[val%10].end(),val)==hash[val%10].end()){
                std::cout << "Value not found!\n";
            }else{
                std::cout << "Found!\n";
            }
        }
        else if(x==3){
            int val;
            std::cout << "Enter val to delete: ";
            std::cin >> val;

            if(std::find(hash[val%10].begin(),hash[val%10].end(),val)==hash[val%10].end()){
                std::cout << "Value not found!\n";
            }else{
                hash[val%10].remove(val);
                std::cout << "Removed "<<val<< '\n';
            }
        }
        else if(x==4){
            for(int i=0;i<10;i++){
                std::cout << "Bucket "<<i <<": ";
                for(auto it:hash[i]){
                    std::cout << it << " ";
                }
                std::cout << '\n';
            }
        }
        else break;
    }
    return 0;
}