#include <iostream>
#include <string>
using namespace std;

struct Mahasiswa {
    string nama;
    string nim;
    double ipk;
};

// Fungsi untuk input data mahasiswa
void inputMahasiswa(Mahasiswa mhs[], int jumlah) {
    cout << "=== INPUT DATA MAHASISWA ===" << endl;
    for (int i = 0; i < jumlah; i++) {
        cout << "\nData Mahasiswa ke-" << (i + 1) << ":" << endl;
        cout << "Nama: ";
        cin.ignore(); // Membersihkan buffer
        getline(cin, mhs[i].nama);
        cout << "NIM: ";
        cin >> mhs[i].nim;
        cout << "IPK: ";
        cin >> mhs[i].ipk;
    }
}

// Fungsi untuk mencari mahasiswa dengan IPK tertinggi
int cariIPKTertinggi(Mahasiswa mhs[], int jumlah) {
    int indexTertinggi = 0;
    double ipkTertinggi = mhs[0].ipk;
    
    for (int i = 1; i < jumlah; i++) {
        if (mhs[i].ipk > ipkTertinggi) {
            ipkTertinggi = mhs[i].ipk;
            indexTertinggi = i;
        }
    }
    
    return indexTertinggi;
}

// Fungsi untuk menampilkan mahasiswa dengan IPK tertinggi
void tampilkanMahasiswaTerbaik(Mahasiswa mhs[], int jumlah) {
    int indexTerbaik = cariIPKTertinggi(mhs, jumlah);
    
    cout << "\n" << string(50, '=') << endl;
    cout << "MAHASISWA DENGAN IPK TERTINGGI" << endl;
    cout << string(50, '=') << endl;
    cout << "Nama : " << mhs[indexTerbaik].nama << endl;
    cout << "NIM  : " << mhs[indexTerbaik].nim << endl;
    cout << "IPK  : " << fixed << mhs[indexTerbaik].ipk << endl;
    cout << string(50, '=') << endl;
    
}

int main() {
    const int JUMLAH_MAHASISWA = 5;
    Mahasiswa mahasiswa[JUMLAH_MAHASISWA];
    
    cout << "PROGRAM MANAJEMEN DATA MAHASISWA" << endl;
    cout << "Masukkan data untuk " << JUMLAH_MAHASISWA << " mahasiswa" << endl;
    
    // Input data mahasiswa
    inputMahasiswa(mahasiswa, JUMLAH_MAHASISWA);
    
    // Tampilkan mahasiswa dengan IPK tertinggi
    tampilkanMahasiswaTerbaik(mahasiswa, JUMLAH_MAHASISWA);
    
    return 0;
}