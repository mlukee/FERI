#include <iostream>
using namespace std;

int sumOfDigits(int number){
    int sumOfDigits = 0;
    while(number>0){
        sumOfDigits += number % 10;
        number /= 10;
    }
    return sumOfDigits;
}

bool isPerfect(int sum){
    int sumOfDividers = 0;
    for (int i = 1; i < sum; i++) {
        if(sum % i == 0)
            sumOfDividers += i;
    }
    if(sum == sumOfDividers)
        return true;

    return false;
}

int countDivisors(int sum){
    int divisors = 0;
    for(int i=1;i<sum;i++){
        if(sum % i == 0){
            divisors++;
        }
    }
    return divisors;
}

int main() {
    int sum, number, numberOfDivisiors = 0;
    bool isCorrect = false;

    while(!isCorrect){
        cout<<"Vnesite stevilo: ";
        cin>>number;
        if(number<=0){
            cout<<"Wrong number! Try again..."<<endl;
        }else{
            isCorrect = true;
        }
    }
//    do{
//        cout<< "Vnesite stevilo: ";
//        cin>>number;
//        if(number<=0)
//            cout<<"Wrong number! Try again..."<<endl;
//    }while(number<=0);

    sum = sumOfDigits(number);
    cout<<"Vsota cifer v stevilu je: " << sum << endl;

    if(isPerfect(sum)){
        cout<<"Stevilo " << sum << " je popolno stevilo"<<endl;
    } else{
        cout<<"Stevilo " << sum << " ni popolno stevilo"<<endl;
    }

    numberOfDivisiors = countDivisors(sum);
    cout<<"Stevilo deliteljev stevila: " << sum << " je: " << numberOfDivisiors << endl;

    return 0;
}
