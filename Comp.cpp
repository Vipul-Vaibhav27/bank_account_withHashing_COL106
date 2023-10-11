#include "Comp.h"
using namespace std;
int db_size4=0;
Comp::Comp() {
    vector<Account> dummy={};
    bankStorage2d.resize(200009, dummy);
}
void Comp::createAccount(std::string id, int count) {
    // IMPLEMENT YOUR CODE HERE
    //cout<<"createAccount failed"<<endl;
    Account acc;
    acc.id=id;acc.balance=count;
    int hash_value=hash(id);
    bankStorage2d[hash_value].push_back(acc);
    //cout<<id<<" "<<count<<endl;
    db_size4++;
}
void merge5(std::vector<int>& arr, int l, int m, int r){
    // both are sorted arrays
    int len1=m-l+1;
    int len2=r-m;
    std::vector<int> arr1(len1);std::vector<int> arr2(len2);
    for(int i=0;i<len1;i++)
        arr1[i]=arr[l+i];
    for(int j=0;j<len2;j++)
        arr2[j]=arr[j+m+1];
    int i=0,j=0,k=0;
    while(i<len1 and j<len2){
        if(arr1[i]>arr2[j]){
            arr[k+l] = arr1[i];
            i++;
            k++;
        }else{
            arr[k+l] = arr2[j];
            k++;
            j++;
        }
    }
    while(i<len1){
        arr[k+l]=arr1[i];
        i++;
        k++;
    }
    while(j<len2){
        arr[k+l]=arr2[j];
        j++;
        k++;
    }
}
void merge_sort5(std::vector<int> &arr, int left, int right){
    if(left<right){
        int mid=(left+right)/2;
        merge_sort5(arr, left, mid);
        merge_sort5(arr, mid+1, right);
        merge5(arr, left, mid, right);
    }
}
std::vector<int> Comp::getTopK(int k) {
    // IMPLEMENT YOUR CODE HERE
    //cout<<"getTopK failed"<<endl;
    std::vector<int> temp;
    for(int i=0;i<bankStorage2d.size();i++){
        for(int j=0;j<bankStorage2d[i].size();j++){
            temp.push_back(bankStorage2d[i][j].balance);
        }
    }
    merge_sort5(temp, 0, temp.size()-1);
    std::vector<int> temp2;
    if(temp.size()>=k) {
        for (int i = 0; i <k; i++) {
            temp2.push_back(temp[i]);
        }
    }else{
        for(int i=0;i<temp.size();i++)
            temp2.push_back(temp[i]);
    }
    return temp2; // Placeholder return value
}

int Comp::getBalance(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    //cout<<"getBalance failed"<<endl;
    int hash_value = hash(id);
    for(int i=0;bankStorage2d[hash_value].size();i++){
        if(bankStorage2d[hash_value][i].id==id)
            return bankStorage2d[hash_value][i].balance;
    }
    return -1; // Placeholder return value
}

void Comp::addTransaction(std::string id, int count) {
    // IMPLEMENT YOUR CODE HERE
    //cout<<"addTransaction failed"<<endl;
    int hash_value = hash(id);
    for(int i=0;bankStorage2d[hash_value].size();i++){
        if(bankStorage2d[hash_value][i].id==id){
            bankStorage2d[hash_value][i].balance+=count;
            //cout<<"Transaction:"<<id<<" "<<count<<endl;
            return;
        }
    }
    createAccount(id, count);
}

bool Comp::doesExist(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    //cout<<"doesExist failed"<<endl;
    int hash_value = hash(id);
    for(int i=0;bankStorage2d[hash_value].size();i++){
        if(bankStorage2d[hash_value][i].id==id)
            return true;
    }
    return false; // Placeholder return value
}

bool Comp::deleteAccount(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    //cout<<"deleteAccount failed";
    int hash_value = hash(id);
    for(int i=0;bankStorage2d[hash_value].size();i++){
        if(bankStorage2d[hash_value][i].id==id){
            bankStorage2d[hash_value].erase(bankStorage2d[hash_value].begin()+i);
            db_size4--;
            //cout<<"Delete:"<<id<<endl;
            return true;
        }
    }
    return false; // Placeholder return value
}
int Comp::databaseSize() {
    // IMPLEMENT YOUR CODE HERE
    //cout<<"dataBaseSize failed"<<endl;
    return db_size4; // Placeholder return value
}
int pow5(int num, int exp){
    int product=num;
    while(exp>1){
        product*=num;
        exp--;
    }
    return product;
}
int Comp::hash(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int h=0;
    for(int i=0;i<id.size();i++){
        h+=id[i]*pow5(2, i);
    }
    return h%200009; // Placeholder return value
}