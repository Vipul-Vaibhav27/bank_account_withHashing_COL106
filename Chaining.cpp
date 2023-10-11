#include "Chaining.h"
using namespace std;
int db_size=0;
Chaining::Chaining() {
    vector<Account> dummy={};
    bankStorage2d.resize(200009, dummy);
}
void Chaining::createAccount(std::string id, int count) {
    // IMPLEMENT YOUR CODE HERE
    //cout<<"createAccount failed"<<endl;
    Account acc;
    acc.id=id;acc.balance=count;
    int hash_value=hash(id);
    bankStorage2d[hash_value].push_back(acc);
    //cout<<id<<" "<<count<<endl;
    db_size++;
}
void merge1(std::vector<int>& arr, int l, int m, int r){
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
void merge_sort1(std::vector<int> &arr, int left, int right){
    if(left<right){
        int mid=(left+right)/2;
        merge_sort1(arr, left, mid);
        merge_sort1(arr, mid+1, right);
        merge1(arr, left, mid, right);
    }
}
std::vector<int> Chaining::getTopK(int k) {
    // IMPLEMENT YOUR CODE HERE
    //cout<<"getTopK failed"<<endl;
    std::vector<int> temp;
    for(int i=0;i<bankStorage2d.size();i++){
        for(int j=0;j<bankStorage2d[i].size();j++){
            temp.push_back(bankStorage2d[i][j].balance);
        }
    }
    merge_sort1(temp, 0, temp.size()-1);
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

int Chaining::getBalance(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    //cout<<"getBalance failed"<<endl;
    int hash_value = hash(id);
    for(int i=0;bankStorage2d[hash_value].size();i++){
        if(bankStorage2d[hash_value][i].id==id)
            return bankStorage2d[hash_value][i].balance;
    }
    return -1; // Placeholder return value
}

void Chaining::addTransaction(std::string id, int count) {
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

bool Chaining::doesExist(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    //cout<<"doesExist failed"<<endl;
    int hash_value = hash(id);
    for(int i=0;bankStorage2d[hash_value].size();i++){
        if(bankStorage2d[hash_value][i].id==id)
            return true;
    }
    return false; // Placeholder return value
}

bool Chaining::deleteAccount(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    //cout<<"deleteAccount failed";
    int hash_value = hash(id);
    for(int i=0;bankStorage2d[hash_value].size();i++){
        if(bankStorage2d[hash_value][i].id==id){
            bankStorage2d[hash_value].erase(bankStorage2d[hash_value].begin()+i);
            db_size--;
            //cout<<"Delete:"<<id<<endl;
            return true;
        }
    }
    return false; // Placeholder return value
}
int Chaining::databaseSize() {
    // IMPLEMENT YOUR CODE HERE
    //cout<<"dataBaseSize failed"<<endl;
    return db_size; // Placeholder return value
}
int pow1(int num, int exp){
    int product=num;
    while(exp>1){
        product*=num;
        exp--;
    }
    return product;
}
int Chaining::hash(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int h=0;
    for(int i=0;i<id.size();i++){
        h+=id[i]*pow1(2, i);
    }
    return h%200009; // Placeholder return value
}
/*
int main(){
    Chaining q;
    cout<<q.hash("Alice")<<endl;
    cout<<q.hash("Bob")<<endl;
    cout<<q.hash("Bob1")<<endl;
    cout<<q.hash("Bob2")<<endl;
    cout<<q.hash("Charlie")<<endl;
    q.createAccount("Alice", 1000);
    q.createAccount("Bob", 1500);
    q.createAccount("Bob1", 1450);
    q.createAccount("Charlie", 2000);


    q.addTransaction("Alice", -200);
    q.addTransaction("Bob", 300);
    q.addTransaction("Charlie", -400);
    q.addTransaction("Delta", 1234);

    q.createAccount("Priyansh", 2000);
    q.createAccount("Mukul Russian Lauda", 1800);
    std::vector<int> topBalances = q.getTopK(15);
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
    std::vector<int> topBalances1 = q.getTopK(15);

    cout<<topBalances1.size()<<endl;
    cout<<topBalances1[0]<<endl;
    cout<<topBalances1[1]<<endl;
    cout<<q.databaseSize()<<endl;
}
*/
/*
int main(){
    Chaining c;
    c.createAccount("RSSQ3189394_2237913740", 40);
    c.createAccount("SRSS3727640_1535924230", 30);
    c.createAccount("RSSP5674009_8533273013", 13);
    c.createAccount("QSRR8042449_9736521620", 20);
    vector<int> v = c.getTopK(10);
    c.addTransaction("RSSP5674009_8533273013", 50);
    vector<int> v1 = c.getTopK(10);
    c.deleteAccount("RSSP5674009_8533273013");
    vector<int> v2 = c.getTopK(10);
    c.createAccount("PSSR3353605_7855900349", 49);
    c.createAccount("RPPS9847364_2488951758", 58);
    c.createAccount("SQRP4629234_6978837113", 13);
    c.createAccount("QQSS6674159_7113743099", 99);
    c.createAccount("PSPP7360617_4330906375", 75);
    c.createAccount("PSQQ8300411_3110492310", 10);
    vector<int> v3 = c.getTopK(10);
    c.addTransaction("PSQQ8300411_3110492310", 90);
    vector<int> v4 = c.getTopK(10);
    c.deleteAccount("QQSS6674159_7113743099");
    c.createAccount("QRQQ5568410_5086508049", 49);
    c.addTransaction("QSRR8042449_9736521620", 65);
    c.createAccount("QSQP2205304_9535295738", 38);
    vector<int> v5 = c.getTopK(15);
    c.createAccount("RQPP3895200_0384691115", 15);
    c.createAccount("QSPR3210795_2777862273", 73);
    vector<int> v6 = c.getTopK(15);
}
*/