#include <iostream>
#include <string>
using namespace std;

struct Item {
    string namaItem;
    int jumlah;
    string tipe;
    Item* next;
};

// Add new item with initial jumlah = 11
void tambahItem(Item*& head, const string& nama, const string& tipe) {
    Item* baru = new Item{nama, 11, tipe, nullptr}; // Personalization: initial jumlah = 11
    if (!head) {
        head = baru;
    } else {
        Item* temp = head;
        while (temp->next) temp = temp->next;
        temp->next = baru;
    }
    cout << "Item berhasil ditambahkan!\n";
}

// Insert item at position 12
void sisipItem(Item*& head, const string& nama, const string& tipe) {
    const int posisi = 12; // Personalization: insert at position 12
    Item* baru = new Item{nama, 11, tipe, nullptr}; // Personalization: initial jumlah = 11
    if (posisi <= 1 || !head) {
        baru->next = head;
        head = baru;
    } else {
        Item* temp = head;
        int idx = 1;
        while (temp->next && idx < posisi - 1) {
            temp = temp->next;
            idx++;
        }
        baru->next = temp->next;
        temp->next = baru;
    }
    cout << "Item berhasil disisipkan!\n";
}

// Delete last item
void hapusItemTerakhir(Item*& head) {
    if (!head) {
        cout << "Inventory kosong!\n";
        return;
    }
    if (!head->next) {
        cout << "Item '" << head->namaItem << "' dihapus.\n";
        delete head;
        head = nullptr;
        return;
    }
    Item* temp = head;
    while (temp->next->next) temp = temp->next;
    cout << "Item '" << temp->next->namaItem << "' dihapus.\n";
    delete temp->next;
    temp->next = nullptr;
}

// Use item: reduce jumlah by 1, delete if jumlah becomes 0
void gunakanItem(Item*& head, const string& namaCari) {
    Item* temp = head;
    Item* prev = nullptr;
    while (temp) {
        if (temp->namaItem == namaCari) {
            temp->jumlah--;
            cout << "Item '" << namaCari << "' digunakan! Sisa: " << temp->jumlah << endl;
            if (temp->jumlah <= 0) {
                if (!prev) {
                    head = temp->next;
                } else {
                    prev->next = temp->next;
                }
                cout << "Item '" << namaCari << "' habis dan dihapus dari inventory.\n";
                delete temp;
            }
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    cout << "Item tidak ditemukan!\n";
}

// Display inventory
void tampilkanInventory(Item* head) {
    cout << "\n+---------------------------------------------+\n";
    cout << "|                INVENTORY GAME                |\n";
    cout << "+---------------------------------------------+\n";
    if (!head) {
        cout << "|          Inventory Kosong                   |\n";
    } else {
        Item* temp = head;
        int idx = 1;
        while (temp) {
            cout << "| " << idx << ". " << temp->namaItem 
                 << " (" << temp->tipe << ") - Jumlah: " 
                 << temp->jumlah << "\n";
            temp = temp->next;
            idx++;
        }
    }
    cout << "+---------------------------------------------+\n";
}

int main() {
    string nama, nim;
    cout << "Masukkan Nama : ";
    getline(cin, nama);
    cout << "Masukkan NIM  : ";
    getline(cin, nim);

    Item* inventory = nullptr;
    int pilihan;

    do {
        cout << "\n+--------------------------------------------------+\n";
        cout << "|           GAME INVENTORY MANAGEMENT              |\n";
        cout << "|        [ " << nama << " - " << nim << " ]           |\n";
        cout << "+--------------------------------------------------+\n";
        cout << "| 1. Tambah Item Baru                              |\n";
        cout << "| 2. Sisipkan Item                                 |\n";
        cout << "| 3. Hapus Item Terakhir                           |\n";
        cout << "| 4. Gunakan Item                                  |\n";
        cout << "| 5. Tampilkan Inventory                           |\n";
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
            cout << "Nama Item : ";
            getline(cin, namaItem);
            cout << "Tipe Item : ";
            getline(cin, tipe);
            tambahItem(inventory, namaItem, tipe);
        } else if (pilihan == 2) {
            string namaItem, tipe;
            cout << "Nama Item : ";
            getline(cin, namaItem);
            cout << "Tipe Item : ";
            getline(cin, tipe);
            sisipItem(inventory, namaItem, tipe);
        } else if (pilihan == 3) {
            hapusItemTerakhir(inventory);
        } else if (pilihan == 4) {
            string namaItem;
            cout << "Nama Item yang ingin digunakan : ";
            getline(cin, namaItem);
            gunakanItem(inventory, namaItem);
        } else if (pilihan == 5) {
            tampilkanInventory(inventory);
        } else if (pilihan == 0) {
            cout << "Terima kasih, " << nama << "! Program selesai.\n";
        } else {
            cout << "Pilihan tidak valid!\n";
        }
    } while (pilihan != 0);

    // Clean up memory
    while (inventory) {
        Item* temp = inventory;
        inventory = inventory->next;
        delete temp;
    }
    return 0;
}