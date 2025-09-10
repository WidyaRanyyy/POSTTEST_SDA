#include <iostream>
#include <iomanip>
using namespace std;

// Fungsi untuk menampilkan matriks
void tampilkanMatriks(int matriks[3][3]) {
    cout << "\nMatriks 3x3:" << endl;
    cout << "+-----+-----+-----+" << endl;
    for (int i = 0; i < 3; i++) {
        cout << "|";
        for (int j = 0; j < 3; j++) {
            cout << setw(4) << matriks[i][j] << " |";
        }
        cout << endl;
        cout << "+-----+-----+-----+" << endl;
    }
}

// Fungsi untuk menghitung jumlah diagonal utama
int hitungDiagonalUtama(int matriks[3][3]) {
    int jumlah = 0;
    for (int i = 0; i < 3; i++) {
        jumlah += matriks[i][i];
    }
    return jumlah;
}

// Fungsi untuk menghitung jumlah diagonal sekunder
int hitungDiagonalSekunder(int matriks[3][3]) {
    int jumlah = 0;
    for (int i = 0; i < 3; i++) {
        int j = 2 - i;  // Kolom untuk diagonal sekunder
        jumlah += matriks[i][j];
    }
    return jumlah;
}

// Fungsi untuk mengisi matriks dengan nilai awal
void isiMatriks(int matriks[3][3]) {
    int contoh[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            matriks[i][j] = contoh[i][j];
        }
    }
}

int main() {
    int matriks[3][3];

    // Isi matriks dengan nilai
    isiMatriks(matriks);

    // Tampilkan matriks
    tampilkanMatriks(matriks);

    // Hitung diagonal utama
    int jumlahDiagonalUtama = hitungDiagonalUtama(matriks);

    // Hitung diagonal sekunder
    int jumlahDiagonalSekunder = hitungDiagonalSekunder(matriks);

    // Tampilkan hasil perhitungan
    cout << "\n" << string(40, '=') << endl;
    cout << "HASIL PERHITUNGAN:" << endl;
    cout << string(40, '=') << endl;
    cout << "Jumlah Diagonal Utama   : " << jumlahDiagonalUtama << endl;
    cout << "Jumlah Diagonal Sekunder: " << jumlahDiagonalSekunder << endl;
    cout << "Total Kedua Diagonal    : " << (jumlahDiagonalUtama + jumlahDiagonalSekunder) << endl;

    return 0;
}
