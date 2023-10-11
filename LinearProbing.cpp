#include "LinearProbing.h"

using namespace std;
int db_size1=0;
LinearProbing::LinearProbing() {
    Account dummy;dummy.id="";dummy.balance=0;
    bankStorage1d.resize(200009, dummy);
}
void LinearProbing::createAccount(std::string id, int count) {
    // IMPLEMENT YOUR CODE HERE
    //cout<<"createAccount failed"<<endl;
    Account acc;
    acc.id=id; acc.balance=count;
    int hash_value=hash(id);
    while(bankStorage1d[hash_value].id!=""){
        hash_value=(hash_value+1)%bankStorage1d.size();
    }
    bankStorage1d[hash_value]=acc;
    db_size1++;
}
void merge2(std::vector<int>& arr, int l, int m, int r){
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
void merge_sort2(std::vector<int> &arr, int left, int right){
    if(left<right){
        int mid=(left+right)/2;
        merge_sort2(arr, left, mid);
        merge_sort2(arr, mid+1, right);
        merge2(arr, left, mid, right);
    }
}
std::vector<int> LinearProbing::getTopK(int k) {
    // IMPLEMENT YOUR CODE HERE
    vector<int> balances;
    for(int i=0;i<bankStorage1d.size();i++){
        if(bankStorage1d[i].id!="")
            balances.push_back(bankStorage1d[i].balance);
    }
    merge_sort2(balances, 0, balances.size()-1);
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

int LinearProbing::getBalance(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    //cout<<"getBalance failed"<<endl;
    int hash_value=hash(id);
    int temp=hash_value;
    if(bankStorage1d[hash_value].id==id)
        return bankStorage1d[hash_value].balance;
    else
        hash_value=(hash_value+1)%bankStorage1d.size();
    while(hash_value!=temp){
        if(bankStorage1d[hash_value].id==id)
            return bankStorage1d[hash_value].balance;
        hash_value=(hash_value+1)%bankStorage1d.size();
    }
    return -1; // Placeholder return value
}

void LinearProbing::addTransaction(std::string id, int count) {
    // IMPLEMENT YOUR CODE HERE
    //cout<<"addTransaction failed"<<endl;
    int hash_value = hash(id);
    int temp= hash_value;
    if(bankStorage1d[hash_value].id==id){
        bankStorage1d[hash_value].balance+=count;
        return;
    }else
        hash_value=(hash_value+1)%bankStorage1d.size();
    while(hash_value!=temp){
        if(bankStorage1d[hash_value].id==id){
            bankStorage1d[hash_value].balance+=count;
            return;
        }
        hash_value=(hash_value+1)%bankStorage1d.size();
    }
    createAccount(id, count);
}

bool LinearProbing::doesExist(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    //cout<<"doesExist failed"<<endl;
    int hash_value = hash(id);
    int temp= hash_value;
    if(bankStorage1d[hash_value].id==id)
        return true;
    else
        hash_value=(hash_value+1)%bankStorage1d.size();
    while(temp!=hash_value){
        if(bankStorage1d[hash_value].id==id)
            return true;
        hash_value=(hash_value+1)%bankStorage1d.size();
    }
    return false; // Placeholder return value
}

bool LinearProbing::deleteAccount(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    //cout<<"deleteAccount failed";
    int hash_value=hash(id);
    int temp=hash_value;
    if(bankStorage1d[hash_value].id==id){
        bankStorage1d[hash_value].id="";
        db_size1--;
        return true;
    }else{
        hash_value=(hash_value+1)%bankStorage1d.size();
    }
    while(temp!=hash_value){
        if(bankStorage1d[hash_value].id==id){
            bankStorage1d[hash_value].id="";
            db_size1--;
            return true;
        }
        hash_value=(hash_value+1)%bankStorage1d.size();
    }
    return false; // Placeholder return value
}
int LinearProbing::databaseSize() {
    // IMPLEMENT YOUR CODE HERE
    return db_size1; // Placeholder return value
}
int pow2(int num, int exp){
    int product=num;
    while(exp>1){
        product*=num;
        exp--;
    }
    return product;
}
int LinearProbing::hash(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int h=0;
    for(int i=0;i<id.size();i++){
        h+=id[i]*pow2(2, i);
    }
    return h%200009; // Placeholder return value
}
/*
int main(){
    LinearProbing q;
    q.createAccount("Alice", 1000);
    q.createAccount("Bob", 1500);
    q.createAccount("Charlie", 2000);

    cout<<q.getBalance("Alice")<<endl;
    cout<<q.getBalance("Bob")<<endl;
    cout<<q.getBalance("Charlie")<<endl;

    q.addTransaction("Alice", -200);
    q.addTransaction("Bob", 300);
    q.addTransaction("Charlie", -400);
    q.addTransaction("Delta", 1234);

    cout<<q.getBalance("Alice")<<endl;
    cout<<q.getBalance("Bob")<<endl;
    cout<<q.getBalance("Charlie")<<endl;
    cout<<q.getBalance("Delta")<<endl;

    std::vector<int> topBalances = q.getTopK(2);
    cout<<topBalances.size()<<endl;
    cout<<topBalances[0]<<endl;
    cout<<topBalances[1]<<endl;
    cout<<q.databaseSize()<<endl;

    cout<<q.doesExist("Alice")<<endl;
    cout<<q.doesExist("Eve")<<endl;

    cout<<q.deleteAccount("EFNET")<<endl;
    cout<<q.deleteAccount("Alice")<<endl;
    cout<<q.doesExist("Alice")<<endl;
    cout<<q.databaseSize()<<endl;
}
*/