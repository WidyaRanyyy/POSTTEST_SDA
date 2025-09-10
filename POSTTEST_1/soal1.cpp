#include <iostream>
using namespace std;

// Fungsi untuk membalik urutan array menggunakan pointer
void balikArray(int* arr, int size) {
    int* start = arr;           // Pointer ke elemen pertama
    int* end = arr + size - 1;  // Pointer ke elemen terakhir
    
    while (start < end) {
        int temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}

// Fungsi untuk menampilkan array
void tampilkanArray(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        cout << *(arr + i) << " ";
    }
    cout << endl;
}

int main() {
    const int SIZE = 7;
    int data[SIZE];

    for (int i = 0; i < SIZE; i++) {
        data[i] = (i + 1) * 3;
    }
    
    cout << "\nArray sebelum dibalik: ";
    tampilkanArray(data, SIZE);
    balikArray(data, SIZE);
    
    cout << "Array setelah dibalik:  ";
    tampilkanArray(data, SIZE);
    
    return 0;
}