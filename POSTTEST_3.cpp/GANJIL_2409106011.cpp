#include <iostream>
#include <string>
using namespace std;

struct Item {
    int id;
    string namaItem;
    int jumlah;
    string tipe;
    Item* next;
    Item* prev;
};

int idCounter = 1;

int getJumlahAwal(const string& nim) {
    if (nim.empty()) return 1;
    if (nim.length() == 1) return nim[0] - '0';
    string last2 = nim.substr(max(0, (int)nim.length() - 2));
    try {
        return stoi(last2);
    } catch (...) {
        return 1;
    }
}

int getPosisiSisip(const string& nim) {
    if (nim.empty()) return 1;
    char last = nim[nim.length() - 1];
    if (last < '0' || last > '9') return 1;
    return (last - '0') + 1;
}

void tambahItem(Item*& head, Item*& tail, const string& nama, const string& tipe, int jumlah) {
    Item* baru = new Item{idCounter++, nama, jumlah, tipe, nullptr, nullptr};
    if (!head) {
        head = tail = baru;
    } else {
        tail->next = baru;
        baru->prev = tail;
        tail = baru;
    }
    cout << "Item berhasil ditambahkan dengan ID : " << baru->id << "!\n";
}

void sisipItem(Item*& head, Item*& tail, const string& nama, const string& tipe, int jumlah, int posisi) {
    Item* baru = new Item{idCounter++, nama, jumlah, tipe, nullptr, nullptr};
    
    if (posisi <= 1 || !head) {
        if (!head) {
            head = tail = baru;
        } else {
            baru->next = head;
            head->prev = baru;
            head = baru;
        }
    } else {
        Item* temp = head;
        int idx = 1;
        while (temp && idx < posisi) {
            temp = temp->next;
            idx++;
        }
        
        if (!temp) {
            // item masuk di paling belakang
            tail->next = baru;
            baru->prev = tail;
            tail = baru;
        } else {
            // item masuk di tengah
            baru->next = temp;
            baru->prev = temp->prev;
            if (temp->prev) {
                temp->prev->next = baru;
            } else {
                head = baru;
            }
            temp->prev = baru;
        }
    }
    cout << "Item berhasil disisipkan dengan ID : " << baru->id << "!\n";
}

void hapusItemTerakhir(Item*& head, Item*& tail) {
    if (!head) {
        cout << "Inventory kosong!\n";
        return;
    }
    
    if (head == tail) {
        cout << "Item dengan ID " << head->id << " (" << head->namaItem << ") dihapus!\n";
        delete head;
        head = tail = nullptr;
    } else {
        cout << "Item dengan ID " << tail->id << " (" << tail->namaItem << ") dihapus!\n";
        Item* temp = tail;
        tail = tail->prev;
        tail->next = nullptr;
        delete temp;
    }
}

void gunakanItem(Item*& head, Item*& tail, const string& namaCari) {
    Item* temp = head;
    while (temp) {
        if (temp->namaItem == namaCari) {
            temp->jumlah--;
            cout << "Item '" << namaCari << "' (ID: " << temp->id << ") digunakan! Sisa: " << temp->jumlah << endl;
            if (temp->jumlah <= 0) {
                cout << "Item '" << namaCari << "' habis dan dihapus dari inventory.\n";
                
                // Update pointer bang
                if (temp->prev) temp->prev->next = temp->next;
                else head = temp->next;
                
                if (temp->next) temp->next->prev = temp->prev;
                else tail = temp->prev;
                
                delete temp;
            }
            return;
        }
        temp = temp->next;
    }
    cout << "Item tidak ditemukan!\n";
}

void tampilkanInventory(Item* head) {
    cout << "\n+-------------------------------------------------------------+\n";
    cout << "|                    INVENTORY GAME (dari depan)                |\n";
    cout << "+---------------------------------------------------------------+\n";
    if (!head) {
        cout << "|                    Inventory Kosong                        |\n";
    } else {
        Item* temp = head;
        int idx = 1;
        while (temp) {
            cout << "| " << idx << ". ID: " << temp->id 
                 << " | " << temp->namaItem 
                 << " (" << temp->tipe << ") - Jumlah: " 
                 << temp->jumlah << "\n";
            temp = temp->next;
            idx++;
        }
    }
    cout << "+-------------------------------------------------------------+\n";
}

void tampilkanInventoryMundur(Item* tail) {
    cout << "\n+-------------------------------------------------------------+\n";
    cout << "|                   INVENTORY GAME (dari belakang)              |\n";
    cout << "+---------------------------------------------------------------+\n";
    if (!tail) {
        cout << "|                    Inventory Kosong                        |\n";
    } else {
        Item* temp = tail;
        int idx = 1;
        while (temp) {
            cout << "| " << idx << ". ID: " << temp->id 
                 << " | " << temp->namaItem 
                 << " (" << temp->tipe << ") - Jumlah: " 
                 << temp->jumlah << "\n";
            temp = temp->prev;
            idx++;
        }
    }
    cout << "+-------------------------------------------------------------+\n";
}

void tampilkanDaftarID(Item* head) {
    cout << "\n+---------------------------------------------+\n";
    cout << "|                  DAFTAR ID ITEM               |\n";
    cout << "+-----------------------------------------------+\n";
    if (!head) {
        cout << "|          Inventory Kosong                 |\n";
    } else {
        Item* temp = head;
        while (temp) {
            cout << "| ID: " << temp->id << " - " << temp->namaItem << "\n";
            temp = temp->next;
        }
    }
    cout << "+---------------------------------------------+\n";
}

void tampilkanDetailItem(Item* head, int idCari) {
    Item* temp = head;
    while (temp) {
        if (temp->id == idCari) {
            cout << "\n+-------------------------------------------------------------+\n";
            cout << "|                      DETAIL ITEM                           |\n";
            cout << "+-------------------------------------------------------------+\n";
            cout << "| ID Item     : " << temp->id << "\n";
            cout << "| Nama Item   : " << temp->namaItem << "\n";
            cout << "| Tipe Item   : " << temp->tipe << "\n";
            cout << "| Jumlah      : " << temp->jumlah << "\n";
            cout << "+-------------------------------------------------------------+\n";
            return;
        }
        temp = temp->next;
    }
    cout << "Item dengan ID " << idCari << " tidak ditemukan!\n";
}

int main() {
    string nama, nim;
    cout << "Masukkan Nama : ";
    getline(cin, nama);
    cout << "Masukkan NIM  : ";
    getline(cin, nim);

    int jumlahAwal = getJumlahAwal(nim);
    int posisiSisip = getPosisiSisip(nim);

    Item* inventory = nullptr;
    Item* tail = nullptr;
    int pilihan;

    do {
        cout << "\n+--------------------------------------------------+\n";
        cout << "|           GAME INVENTORY MANAGEMENT              |\n";
        cout << "|        [ " << nama << " - " << nim << " ]\n";
        cout << "+--------------------------------------------------+\n";
        cout << "| 1. Tambah Item Baru                              |\n";
        cout << "| 2. Sisipkan Item                                 |\n";
        cout << "| 3. Hapus Item Terakhir                           |\n";
        cout << "| 4. Gunakan Item                                  |\n";
        cout << "| 5. Tampilkan Inventory (dari depan)              |\n";
        cout << "| 6. Tampilkan Inventory (dari belakang)           |\n";
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
            string namaItem, tipe;
            cout << "Nama Item : "; getline(cin, namaItem);
            cout << "Tipe Item : "; getline(cin, tipe);
            tambahItem(inventory, tail, namaItem, tipe, jumlahAwal);
        } else if (pilihan == 2) {
            string namaItem, tipe;
            cout << "Nama Item : "; getline(cin, namaItem);
            cout << "Tipe Item : "; getline(cin, tipe);
            sisipItem(inventory, tail, namaItem, tipe, jumlahAwal, posisiSisip);
        } else if (pilihan == 3) {
            hapusItemTerakhir(inventory, tail);
        } else if (pilihan == 4) {
            string namaItem;
            cout << "Nama Item yang ingin digunakan : "; getline(cin, namaItem);
            gunakanItem(inventory, tail, namaItem);
        } else if (pilihan == 5) {
            tampilkanInventory(inventory);
        } else if (pilihan == 6) {
            tampilkanInventoryMundur(tail);
        } else if (pilihan == 7) {
            if (!inventory) {
                cout << "Inventory kosong!\n";
            } else {
                tampilkanDaftarID(inventory);
                int idCari;
                cout << "\nMasukkan ID Item yang ingin dilihat detailnya : ";
                if (cin >> idCari) {
                    cin.ignore();
                    tampilkanDetailItem(inventory, idCari);
                } else {
                    cout << "ID tidak valid!\n";
                    cin.clear();
                    cin.ignore();
                }
            }
        } else if (pilihan == 0) {
            cout << "Keluar dari program...\n";
        } else {
            cout << "Pilihan tidak valid!\n";
        }
    } while (pilihan != 0);

    // bersihin memori
    while (inventory) {
        Item* temp = inventory;
        inventory = inventory->next;
        delete temp;
    }
    return 0;
}