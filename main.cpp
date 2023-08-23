#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>

// quickSort algorithm taken from https://www.programiz.com/dsa/quick-sort
// insertionSort algorithm taken from https://www.programiz.com/dsa/insertion-sort#google_vignette
// selectionSort algorithm taken from https://www.programiz.com/dsa/selection-sort#google_vignette
// bubbleSort algorithm taken from

using namespace std;
const int pageSize = 12*1024;
const int maxNums = pageSize/sizeof(int);

void swap(int *a, int*b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int array[], int low, int high){
    int pivot = array[high];
    int i = (low-1);

    for(int j = low; j < high; j++){
        if(array[j] <= pivot){
            i++;
            swap(&array[i], &array[j]);
        }
    }
    swap(&array[i + 1], &array[high]);
    return (i + 1);
}

void quickSort(int array[], int low, int high){
    if(low < high){
        int pivot = partition(array, low, high);
        quickSort(array, low, pivot - 1);
        quickSort(array, pivot + 1, high);
    }
}

void insertionSort(int array[], int size){
    for (int step = 1; step < size; step++){
        int key = array[step];
        int j = step-1;
        while(key<array[j] && j >= 0){
            array[j+1] = array[j];
            --j;
        }
        array[j+1] = key;
    }
}
void selectionSort(int array[], int size){
    for(int step = 0; step < size - 1; step++) {
        int min_idx = step;
        for(int i = step + 1; i < size; i++) {
            if(array[i] < array[min_idx])
                min_idx = i;
        }
        swap(&array[min_idx], &array[step]);
    }
}
void bubbleSort(int array[], int size){
    for (int step = 0; step < size; ++step) {
        for (int i = 0; i < size - step - 1; ++i) {
            if (array[i] > array[i + 1]) {
                int temp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = temp;
            }
        }
    }
}

int main(int argCount, char* argVector[]) {
    std::string inputFile, algorithm, outputFile;

    for(int i = 1; i < argCount; i += 2){
        if(std::strcmp(argVector[i], "-i") == 0){
            inputFile = argVector[i+1];
        }
        else if(std::strcmp(argVector[i], "-a") == 0){
            algorithm = argVector[i+1];
        }
        else if(std::strcmp(argVector[i], "-o") == 0){
            outputFile = argVector[i +1];
        }
    }

    std::ifstream input(inputFile, std::ios::binary);
    std::ofstream output(outputFile, std::ios::binary);

    std::vector<int> buffer(maxNums);

    while(!input.eof()){
        int numsRead = 0;
        while (numsRead < maxNums && input.read(reinterpret_cast<char *>(&buffer[numsRead]), sizeof(int))) {
            ++numsRead;
        }
        if(algorithm == "QS"){
            quickSort(&buffer[0], 0, numsRead-1);
        }
        if(algorithm == "IS"){
            insertionSort(&buffer[0], numsRead);
        }
        if(algorithm == "SS"){
            selectionSort(&buffer[0], numsRead);
        }
        if(algorithm == "BS"){
            bubbleSort(&buffer[0], numsRead);
        }
    }
}
