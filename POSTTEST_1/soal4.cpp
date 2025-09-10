#include <iostream>
using namespace std;

// Fungsi untuk menukar dua variabel menggunakan double pointer
void tukarNilai(int **ptr1, int **ptr2) {
    // Menukar nilai yang ditunjuk oleh pointer
    int temp = **ptr1;  // Simpan nilai dari variabel pertama
    **ptr1 = **ptr2;    // Nilai pertama = nilai kedua
    **ptr2 = temp;      // Nilai kedua = nilai sementara (nilai pertama yang lama)
}

// Fungsi untuk menampilkan nilai dan alamat
void tampilkanInfo(int *ptr, string nama) {
    cout << nama << " = " << *ptr 
         << " (alamat: " << ptr << ")" << endl;
}

// Fungsi alternatif: menukar pointer itu sendiri (bukan nilainya)
void tukarPointer(int **ptr1, int **ptr2) {
    cout << "\nMenukar pointer (alamat yang ditunjuk):" << endl;
    int *temp = *ptr1;  // Simpan alamat yang ditunjuk ptr1
    *ptr1 = *ptr2;      // ptr1 menunjuk ke alamat yang ditunjuk ptr2
    *ptr2 = temp;       // ptr2 menunjuk ke alamat yang lama dari ptr1
}

int main() {
    // Deklarasi dua variabel integer
    int a, b;
    
    cout << "PROGRAM PERTUKARAN NILAI MENGGUNAKAN DOUBLE POINTER" << endl;
    cout << "====================================================" << endl;
    
    // Input nilai dari user
    cout << "\nMasukkan nilai untuk variabel A: ";
    cin >> a;
    cout << "Masukkan nilai untuk variabel B: ";
    cin >> b;
    
    // Buat pointer yang menunjuk ke variabel a dan b
    int *ptrA = &a;
    int *ptrB = &b;
    
    // Tampilkan kondisi awal
    cout << "\n=== KONDISI SEBELUM PERTUKARAN ===" << endl;
    tampilkanInfo(ptrA, "Variabel A");
    tampilkanInfo(ptrB, "Variabel B");
    
    // Demonstrasi konsep double pointer
    cout << "\n=== INFORMASI DOUBLE POINTER ===" << endl;
    int **doublePtrA = &ptrA;  // Double pointer ke ptrA
    int **doublePtrB = &ptrB;  // Double pointer ke ptrB
    
    cout << "Double pointer A menunjuk ke alamat: " << doublePtrA << endl;
    cout << "Double pointer A berisi alamat: " << *doublePtrA << endl;
    cout << "Nilai yang ditunjuk double pointer A: " << **doublePtrA << endl;
    cout << endl;
    cout << "Double pointer B menunjuk ke alamat: " << doublePtrB << endl;
    cout << "Double pointer B berisi alamat: " << *doublePtrB << endl;
    cout << "Nilai yang ditunjuk double pointer B: " << **doublePtrB << endl;
    
    // Panggil fungsi untuk menukar nilai menggunakan double pointer
    cout << "\n=== MELAKUKAN PERTUKARAN NILAI ===" << endl;
    cout << "Memanggil fungsi tukarNilai(&ptrA, &ptrB)..." << endl;
    tukarNilai(&ptrA, &ptrB);
    
    // Tampilkan kondisi setelah pertukaran
    cout << "\n=== KONDISI SETELAH PERTUKARAN ===" << endl;
    tampilkanInfo(ptrA, "Variabel A");
    tampilkanInfo(ptrB, "Variabel B");
    
    // Verifikasi bahwa nilai asli juga berubah
    cout << "\n=== VERIFIKASI NILAI VARIABEL ASLI ===" << endl;
    cout << "Nilai variabel a (langsung): " << a << endl;
    cout << "Nilai variabel b (langsung): " << b << endl;
    
    // Demonstrasi tambahan: menukar kembali menggunakan cara yang berbeda
    cout << "\n=== MENUKAR KEMBALI KE KONDISI AWAL ===" << endl;
    tukarNilai(doublePtrA, doublePtrB);
    cout << "Setelah menukar kembali:" << endl;
    cout << "Variabel A = " << a << endl;
    cout << "Variabel B = " << b << endl;
    
    return 0;
}