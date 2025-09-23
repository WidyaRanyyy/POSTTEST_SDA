#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

struct item {
    int id;
    string namaitem;
    int jumlah;
    string tipe;
    item* next;
    item* prev;
};

int idCounter = 1;

// hanya menerima tipe (fire, water, wind)
bool isValidTipe(const string& tipe) {
    string lowerTipe = tipe;
    transform(lowerTipe.begin(), lowerTipe.end(), lowerTipe.begin(), ::tolower);
    return lowerTipe == "fire" || lowerTipe == "water" || lowerTipe == "wind";
}

// 1. jumlah item awal = 11
void tambahitem(item*& head, const string& nama, const string& tipe) {
    string validTipe = tipe;
    while (!isValidTipe(validTipe)) {
        cout << "Tipe tidak valid! Harus 'fire', 'water', atau 'wind'. Masukkan kembali: ";
        getline(cin, validTipe);
    }
    
    item* baru = new item{idCounter++, nama, 11, validTipe, nullptr, nullptr};
    if (!head) {
        head = baru;
    } else {
        item* temp = head;
        while (temp->next) temp = temp->next;
        temp->next = baru;
        baru->prev = temp; 
    }
    cout << "item berhasil ditambahkan!\n";
}

// 2. Posisi Sisip item (Add Specific) = 11 + 1
void sisipitem(item*& head, const string& nama, const string& tipe) {
    string validTipe = tipe;
    while (!isValidTipe(validTipe)) {
        cout << "Tipe tidak valid! Harus 'fire', 'water', atau 'wind'. Masukkan kembali: ";
        getline(cin, validTipe);
    }
    
    const int posisi = 12;
    item* baru = new item{idCounter++, nama, 11, validTipe, nullptr, nullptr};
    if (posisi <= 1 || !head) {
        baru->next = head;
        if (head) head->prev = baru; 
        head = baru;
    } else {
        item* temp = head;
        int idx = 1;
        while (temp->next && idx < posisi - 1) {
            temp = temp->next;
            idx++;
        }
        baru->next = temp->next;
        baru->prev = temp; 
        if (temp->next) temp->next->prev = baru;
        temp->next = baru;
    }
    cout << "item berhasil diselipkan!\n";
}

// 3. Hapus item Terakhir
void hapusitemTerakhir(item*& head) {
    if (!head) {
        cout << "Inventory kosong!\n";
        return;
    }
    if (!head->next) {
        cout << "item '" << head->namaitem << "' dihapus.\n";
        delete head;
        head = nullptr;
        return;
    }
    item* temp = head;
    while (temp->next->next) temp = temp->next;
    cout << "item '" << temp->next->namaitem << "' dihapus.\n";
    delete temp->next;
    temp->next = nullptr;
}

// 4. Menggunakan item, jika ada (-1), jika tidak ada maka dihapus dari inventory
void gunakanitem(item*& head, const string& namaCari) {
    item* temp = head;
    item* prev = nullptr;
    while (temp) {
        if (temp->namaitem == namaCari) {
            temp->jumlah--;
            cout << "item '" << namaCari << "' digunakan! Sisa: " << temp->jumlah << endl;
            if (temp->jumlah <= 0) {
                if (!prev) {
                    head = temp->next;
                    if (head) head->prev = nullptr;
                } else {
                    prev->next = temp->next;
                    if (temp->next) temp->next->prev = prev;
                }
                cout << "item '" << namaCari << "' habis dan dihapus dari inventory.\n";
                delete temp;
            }
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    cout << "item tidak ditemukan!\n";
}

// 5. Tampilkan Inventory (from head to tail)
void tampilkanInventory(item* head) {
    cout << "\n+---------------------------------------------+\n";
    cout << "|              INVENTORY GAME   H-T           |\n";
    cout << "+---------------------------------------------+\n";
    if (!head) {
        cout << "|          Inventory Kosong                   |\n";
    } else {
        item* temp = head;
        int idx = 1;
        while (temp) {
            cout << "| " << idx << ". " << temp->namaitem 
                 << " (" << temp->tipe << ") - Jumlah: " 
                 << temp->jumlah << "\n";
            temp = temp->next;
            idx++;
        }
    }
    cout << "+---------------------------------------------+\n";
}

// 6. Tampilkan Inventory dari Belakang (from tail to head)
void tampilkanInventoryDariBelakang(item* head) {
    cout << "\n+---------------------------------------------+\n";
    cout << "|               INVENTORY GAME T-H            |\n";
    cout << "+---------------------------------------------+\n";
    if (!head) {
        cout << "|          Inventory Kosong                   |\n";
    } else {
        item* tail = head;
        while (tail->next) tail = tail->next;
        item* temp = tail;
        int idx = 1;
        while (temp) {
            cout << "| " << idx << ". " << temp->namaitem 
                 << " (" << temp->tipe << ") - Jumlah: " 
                 << temp->jumlah << "\n";
            temp = temp->prev;
            idx++;
        }
    }
    cout << "+---------------------------------------------+\n";
}

void tampilkanDaftarID(item* head) {
    cout << "\n+---------------------------------------------+\n";
    cout << "|                  DAFTAR ID ITEM               |\n";
    cout << "+-----------------------------------------------+\n";
    if (!head) {
        cout << "|          Inventory Kosong                 |\n";
    } else {
        item* temp = head;
        while (temp) {
            cout << "| ID: " << temp->id << " - " << temp->namaitem << "\n";
            temp = temp->next;
        }
    }
    cout << "+---------------------------------------------+\n";
}

// 7. Tampilkan Detail berdasarkan ID
void tampilkanDetailitem(item* head, int idFind) {
    item* temp = head;
    while (temp) {
        if (temp->id == idFind) {
            cout << "\n+-------------------------------------------------------------+\n";
            cout << "|                      DETAIL ITEM                           |\n";
            cout << "+-------------------------------------------------------------+\n";
            cout << "| ID Item     : " << temp->id << "\n";
            cout << "| Nama Item   : " << temp->namaitem << "\n";
            cout << "| Tipe Item   : " << temp->tipe << "\n";
            cout << "| Jumlah      : " << temp->jumlah << "\n";
            cout << "+-------------------------------------------------------------+\n";
            return;
        }
        temp = temp->next;
    }
    cout << "Item dengan ID " << idFind << " tidak ditemukan!\n";
}

int main() {
    string nama, nim;
    cout << "Masukkan Nama anda: ";
    getline(cin, nama);
    cout << "Masukkan NIM anda : ";
    getline(cin, nim);

    item* inventory = nullptr;
    int pilihan;

    do {
        cout << "\n+--------------------------------------------------+\n";
        cout << "|            MANAJEMEN INVENTORY GAME              |\n";
        cout << "|    [ halo " << nama << " - " << nim << " ]        |\n";
        cout << "+--------------------------------------------------+\n";
        cout << "| 1. Tambah item Baru                              |\n";
        cout << "| 2. Sisipkan item                                 |\n";
        cout << "| 3. Hapus item Terakhir                           |\n";
        cout << "| 4. Gunakan item                                  |\n";
        cout << "| 5. Tampilkan Inventory (HEAD-TAIL)               |\n";
        cout << "| 6. Tampilkan Inventory (TAIL-HEAD)               |\n";
        cout << "| 7. Tampilkan Detail Item berdasarkan ID          |\n";
        cout << "| 0. Keluar                                        |\n";
        cout << "+--------------------------------------------------+\n";
        cout << "Pilih menu : ";
        if (!(cin >> pilihan)) {
            cin.clear();
            cin.ignore();
            pilihan = -1;
        } else {
            cin.ignore();
        }

        if (pilihan == 1) {
            string namaitem, tipe;
            cout << "Masukkan Nama item : ";
            getline(cin, namaitem);
            cout << "Masukkan Tipe item (fire/water/wind) : ";
            getline(cin, tipe);
            tambahitem(inventory, namaitem, tipe);
        } else if (pilihan == 2) {
            string namaitem, tipe;
            cout << "Masukkan Nama item : ";
            getline(cin, namaitem);
            cout << "Masukkan Tipe item (fire/water/wind) : ";
            getline(cin, tipe);
            sisipitem(inventory, namaitem, tipe);
        } else if (pilihan == 3) {
            hapusitemTerakhir(inventory);
        } else if (pilihan == 4) {
            string namaitem;
            cout << "Nama item yang ingin digunakan : ";
            getline(cin, namaitem);
            gunakanitem(inventory, namaitem);
        } else if (pilihan == 5) {
            tampilkanInventory(inventory);
        } else if (pilihan == 6) {
            tampilkanInventoryDariBelakang(inventory);
        } else if (pilihan == 7) {
            if (!inventory) {
                cout << "Inventory kosong!\n";
            } else {
                tampilkanDaftarID(inventory);
                int idCari;
                cout << "\nMasukkan ID Item yang ingin dilihat detailnya : ";
                if (cin >> idCari) {
                    cin.ignore();
                    tampilkanDetailitem(inventory, idCari);
                } else {
                    cout << "ID tidak valid!\n";
                    cin.clear();
                    cin.ignore();
                }
            }
        } else if (pilihan == 0) {
            cout << "Terima kasih, " << nama << "! Program selesai.\n";
        } else {
            cout << "Pilihan tidak valid!\n";
        }
    } while (pilihan != 0);

    // Clean up memory
    while (inventory) {
        item* temp = inventory;
        inventory = inventory->next;
        delete temp;
    }
    return 0;
}