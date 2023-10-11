#include "CubicProbing.h"
using namespace std;
int db_size3=0;
long long int pow4(int num, int exp){
    long long int product=num;
    while(exp>1){
        product*=num;
        exp--;
    }
    return product;
}
CubicProbing::CubicProbing() {
    Account dummy;dummy.id="";dummy.balance=0;
    bankStorage1d.resize(200009, dummy);
}
void CubicProbing::createAccount(std::string id, int count) {
    // IMPLEMENT YOUR CODE HERE
    Account acc;
    acc.id=id; acc.balance=count;
    int hash_value=hash(id);
    long long int counter=0;
    long long int t=(hash_value+ pow4(counter, 3)%bankStorage1d.size())%bankStorage1d.size();
    while(bankStorage1d[t].id!=""){
        counter++;
        t=(hash_value+ pow4(counter, 3))%bankStorage1d.size();
    }
    bankStorage1d[t]=acc;
    db_size3++;
}
void merge4(std::vector<int>& arr, int l, int m, int r){
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
void merge_sort4(std::vector<int> &arr, int left, int right){
    if(left<right){
        int mid=(left+right)/2;
        merge_sort4(arr, left, mid);
        merge_sort4(arr, mid+1, right);
        merge4(arr, left, mid, right);
    }
}
std::vector<int> CubicProbing::getTopK(int k) {
    // IMPLEMENT YOUR CODE HERE
    vector<int> balances;
    for(int i=0;i<bankStorage1d.size();i++){
        if(bankStorage1d[i].id!="")
            balances.push_back(bankStorage1d[i].balance);
    }
    merge_sort4(balances, 0, balances.size()-1);
    vector<int> temp;
    if(balances.size()>=k) {
        for (int i = 0; i < k; i++) {
            temp.push_back(balances[i]);
        }
    }else{
        for(int i=0;i<balances.size();i++)
            temp.push_back(balances[i]);
    }
    return temp; // Placeholder return value
}

int CubicProbing::getBalance(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int hash_value=hash(id);
    long long int counter=0;
    long long int temp=(hash_value+ pow4(counter, 3)%bankStorage1d.size())%bankStorage1d.size();
    bool end=false;
    if(bankStorage1d[temp].id==id)
        return bankStorage1d[temp].balance;
    else {
        counter++;
        if(hash_value+ pow4(counter, 3)%bankStorage1d.size()>bankStorage1d.size())
            end=true;
        temp=(hash_value+ pow4(counter, 3)%bankStorage1d.size())%bankStorage1d.size();
    }
    while((temp<hash_value) or end==false){
        if(bankStorage1d[temp].id==id)
            return bankStorage1d[temp].balance;
        counter++;
        if(end==false and hash_value+ pow4(counter, 3)%bankStorage1d.size()>bankStorage1d.size())
            end=true;
        else if(end==true and hash_value+ pow4(counter, 3)%bankStorage1d.size()>bankStorage1d.size())
            break;
        temp=(hash_value+ pow4(counter, 3)%bankStorage1d.size())%bankStorage1d.size();
    }
    return -1; // Placeholder return value
}

void CubicProbing::addTransaction(std::string id, int count) {
    // IMPLEMENT YOUR CODE HERE
    int hash_value=hash(id);
    long long int counter=0;
    long long int temp=(hash_value+ pow4(counter, 3)%bankStorage1d.size())%bankStorage1d.size();
    bool end=false;
    if(bankStorage1d[temp].id==id) {
        bankStorage1d[temp].balance += count;
        return;
    }
    else {
        counter++;
        if(hash_value+ pow4(counter, 3)%bankStorage1d.size()>bankStorage1d.size())
            end=true;
        temp=(hash_value+ pow4(counter, 3)%bankStorage1d.size())%bankStorage1d.size();
    }
    while((temp<hash_value) or end==false){
        if(bankStorage1d[temp].id==id) {
            bankStorage1d[temp].balance += count;
            return;
        }
        counter++;
        if(end==false and hash_value+ pow4(counter, 3)%bankStorage1d.size()>bankStorage1d.size())
            end=true;
        else if(end==true and hash_value+ pow4(counter, 3)%bankStorage1d.size()>bankStorage1d.size())
            break;
        temp=(hash_value+ pow4(counter, 3)%bankStorage1d.size())%bankStorage1d.size();
    }
    createAccount(id, count);
}

bool CubicProbing::doesExist(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int hash_value=hash(id);
    long long int counter=0;
    long long int temp=(hash_value+ pow4(counter, 3)%bankStorage1d.size())%bankStorage1d.size();
    bool end=false;
    if(bankStorage1d[temp].id==id)
        return true;
    else {
        counter++;
        if(hash_value+ pow4(counter, 3)%bankStorage1d.size()>bankStorage1d.size())
            end=true;
        temp=(hash_value+ pow4(counter, 3)%bankStorage1d.size())%bankStorage1d.size();
    }
    while((temp<hash_value) or end==false){
        if(bankStorage1d[temp].id==id)
            return true;
        counter++;
        if(end==false and hash_value+ pow4(counter, 3)%bankStorage1d.size()>bankStorage1d.size())
            end=true;
        else if(end==true and hash_value+ pow4(counter, 3)%bankStorage1d.size()>bankStorage1d.size())
            break;
        temp=(hash_value+ pow4(counter, 3)%bankStorage1d.size())%bankStorage1d.size();
    }
    return false; // Placeholder return value
}

bool CubicProbing::deleteAccount(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int hash_value=hash(id);
    long long int counter=0;
    long long int temp=(hash_value+ pow4(counter, 3)%bankStorage1d.size())%bankStorage1d.size();
    bool end=false;
    if(bankStorage1d[temp].id==id) {
        bankStorage1d[temp].id="";
        db_size3--;
        return true;
    }
    else {
        counter++;
        if(hash_value+ pow4(counter, 3)%bankStorage1d.size()>bankStorage1d.size())
            end=true;
        temp=(hash_value+ pow4(counter, 3)%bankStorage1d.size())%bankStorage1d.size();
    }
    while((temp<hash_value) or end==false){
        if(bankStorage1d[temp].id==id) {
            bankStorage1d[temp].id="";
            db_size3--;
            return true;
        }
        counter++;
        if(end==false and hash_value+ pow4(counter, 3)%bankStorage1d.size()>bankStorage1d.size())
            end=true;
        else if(end==true and hash_value+ pow4(counter, 3)%bankStorage1d.size()>bankStorage1d.size())
            break;
        temp=(hash_value+ pow4(counter, 3)%bankStorage1d.size())%bankStorage1d.size();
    }
    return false; // Placeholder return value
}
int CubicProbing::databaseSize() {
    // IMPLEMENT YOUR CODE HERE
    return db_size3; // Placeholder return value
}

int CubicProbing::hash(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    long long int h=0;
    for(int i=0;i<id.size();i++){
        h+=id[i]*pow4(2, i);
    }
    return h%200009; // Placeholder return value
}
