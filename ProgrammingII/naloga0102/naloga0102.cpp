#include <iostream>
#include <ctime>
#include <cmath>

using namespace std;

void menu() {
    cout << "============================" << endl;
    cout << "=========== MENU ===========" << endl;
    cout << "============================" << endl;
    cout << "1 ... GENERATE WATER INTAKES" << endl;
    cout << "2 ... PRINT WATER INTAKES" << endl;
    cout << "3 ... PRINT AVERAGE WATER INTAKE" << endl;
    cout << "4 ... PRINT DAYS BELOW AVERAGE WATER INTAKE" << endl;
    cout << "5 ... MAXIMUM WATER INTAKE" << endl;
    cout << "6 ... PRINT DAYS NORMAL WATER INTAKE" <<endl;
    cout << "7 ... PRINT GRAPH" <<endl;
    cout << "0 ... EXIT" << endl;
    cout << "============================" << endl;
    cout << "Select: ";
}

void fillArray(float* array, const unsigned int size) {
    for (unsigned int i = 0; i < size; i++) {
       // float randomNumber = ((float)rand() / (float)RAND_MAX) * (3.5 - 0.5) + 0.5;
        float randomNumber = ((float)rand() / (float)RAND_MAX) * (6.5 - 1) + 1;
        randomNumber = truncf(randomNumber*10)/10;
        array[i] = randomNumber;
    }
}

void printArray(const float* array, const unsigned int size) {
    for (unsigned int i = 0; i < size; i++) {
        cout <<((i > 0) ? ", " : "") << array[i];
    }
}

void printMaxWaterIntake(const float* array, const unsigned int size){
    float max = array[0];
    for(int i=1;i<size;i++){
        if(array[i]>max){
            max = array[i];
        }
    }
    cout<<"Maximum water intake in a day was: " << max << "L";
}

void printGraph(float* array, const unsigned  int size){
    for(int i=0;i<size;i++){
        if(array[i]<2)
            cout<<"-";
        else if(array[i]>=2 && array[i]<4)
            cout<<"o";
        else
            cout<<"+";
    }
}

float averageFromArray(float* array, const unsigned int size){
    float sum = 0;
    for (unsigned int i = 0; i < size; i++){
        sum += array[i];
    }
    return truncf((sum / size)*10)/10;
}

int sumOfDaysBelowAverage(float* array, const unsigned int size){
    float average = averageFromArray(array,size);
    int numberOfDays = 0;
    for(unsigned int i=0;i<size;i++){
        if(array[i]<average)
            numberOfDays+= 1;
    }
    return numberOfDays;
}

int sumOfDaysNormalIntake(float *array, const unsigned int size){
    int sum =0;
    for (int i = 0; i < size; i++) {
        if(array[i]>=2 && array[i]<=2.5){
            sum+=1;
        }
    }
    return sum;
}

int main() {
    const unsigned int days = 30;
    float* waterIntakes = new float[days];

    srand(time(nullptr));

    bool running = true;
    int selection;

    do {
        menu();
        cin >> selection;
        switch (selection) {
            case 1:
                fillArray(waterIntakes, days);
                break;
            case 2:
                printArray(waterIntakes, days);
                break;
            case 3:
                cout<< "Average water intake: " <<averageFromArray(waterIntakes, days) << "L";
                break;
            case 4:
                cout<<"Number of days that are below average water intake("<< averageFromArray(waterIntakes, days) <<"L): " << sumOfDaysBelowAverage(waterIntakes, days);
                break;
            case 5:
                printMaxWaterIntake(waterIntakes, days);
                break;
            case 6:
                cout<<"Number of days where you drank recommended amount of water(2 - 2.5L): " << sumOfDaysNormalIntake(waterIntakes, days);
                break;
            case 7:
                printGraph(waterIntakes, days);
                break;
            case 0:
                cout<<"Goodbye!"<<endl;
                running = false;
                break;
            default:
                cout << "Wrong selection!" << endl;
                break;
        }
        cout << endl;
    } while (running);

    delete[] waterIntakes;

    return 0;
}