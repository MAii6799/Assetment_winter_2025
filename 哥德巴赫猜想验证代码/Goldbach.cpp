#include<iostream>
#include<vector>

//判断质数
bool IsPrime(int num){
    if(num==1){
        return false;
    }
    else if(num==2){
        return true;
    }
    else{
        for(int i=2;i<num;i++){
            if(num%i==0){
                return false;
            }
        }
    }
    return true;
}

int main(){
    int number;
    std::cout<<"请输入一个偶数"<<std::endl;
    std::cin>>number;
    std::vector<int> Primes;
//收集小于number的质数
    for(int i=4;i<number;i++){
        if(IsPrime(i)){
            Primes.push_back(i);
        }
    }
//判断能否为两个质数之和
    int flag=0;
    for(int prime:Primes){
        int p_rime=number-prime;
        if(IsPrime(p_rime)){
            flag=1;
        }
    }

    if(flag==1){
        std::cout<<"Goldbach成立"<<std::endl;
    }
    if(flag==0){
        std::cout<<"Goldbach不成立"<<std::endl;
    }
    return 0;

}