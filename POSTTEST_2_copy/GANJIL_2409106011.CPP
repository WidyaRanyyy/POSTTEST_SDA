#include <iostream>
#include <string>
using namespace std;

//ini sudah dimodif

// Struct for item in inventory
struct Item {
    string namaItem;
    int jumlah;
    string tipe;
    Item* next;
};

// Class for Single Linked List
class Inventory {
private:
    Item* head;

public:
    Inventory() {
        head = nullptr;
    }

    // Add new item with initial jumlah = 11
    void tambahItem(string nama, string tipe) {
        Item* newItem = new Item;
        newItem->namaItem = nama;
        newItem->jumlah = 11; // Personalization: initial jumlah = 11
        newItem->tipe = tipe;
        newItem->next = nullptr;

        if (head == nullptr) {
            head = newItem;
        } else {
            Item* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newItem;
        }
        cout << "Item '" << nama << "' berhasil ditambahkan dengan jumlah 11.\n";
    }

    // Insert item at position 12
    void sisipkanItem(string nama, string tipe, int pos) {
        if (pos < 1) {
            cout << "Posisi tidak valid!\n";
            return;
        }

        Item* newItem = new Item;
        newItem->namaItem = nama;
        newItem->jumlah = 11; // Personalization: initial jumlah = 11
        newItem->tipe = tipe;
        newItem->next = nullptr;

        if (pos == 1) {
            newItem->next = head;
            head = newItem;
            cout << "Item '" << nama << "' disisipkan di posisi 1.\n";
            return;
        }

        Item* temp = head;
        int currentPos = 1;
        while (temp != nullptr && currentPos < pos - 1) {
            temp = temp->next;
            currentPos++;
        }

        if (temp == nullptr) {
            cout << "Posisi " << pos << " melebihi panjang inventory!\n";
            delete newItem;
            return;
        }

        newItem->next = temp->next;
        temp->next = newItem;
        cout << "Item '" << nama << "' disisipkan di posisi " << pos << ".\n";
    }

    // Delete last item
    void hapusItemTerakhir() {
        if (head == nullptr) {
            cout << "Inventory kosong!\n";
            return;
        }

        if (head->next == nullptr) {
            cout << "Item '" << head->namaItem << "' dihapus.\n";
            delete head;
            head = nullptr;
            return;
        }

        Item* temp = head;
        while (temp->next->next != nullptr) {
            temp = temp->next;
        }
        cout << "Item '" << temp->next->namaItem << "' dihapus.\n";
        delete temp->next;
        temp->next = nullptr;
    }

    // Use item: reduce jumlah by 1, delete if jumlah becomes 0
    void gunakanItem(string nama) {
        Item* temp = head;
        Item* prev = nullptr;

        while (temp != nullptr && temp->namaItem != nama) {
            prev = temp;
            temp = temp->next;
        }

        if (temp == nullptr) {
            cout << "Item '" << nama << "' tidak ditemukan!\n";
            return;
        }

        temp->jumlah--;
        cout << "Item '" << nama << "' digunakan. Jumlah tersisa: " << temp->jumlah << "\n";

        if (temp->jumlah == 0) {
            if (prev == nullptr) {
                head = temp->next;
            } else {
                prev->next = temp->next;
            }
            cout << "Item '" << nama << "' habis dan dihapus dari inventory.\n";
            delete temp;
        }
    }

    // Display inventory
    void tampilkanInventory() {
        if (head == nullptr) {
            cout << "Inventory kosong!\n";
            return;
        }

        cout << "\n=== Isi Inventory ===\n";
        Item* temp = head;
        int pos = 1;
        while (temp != nullptr) {
            cout << pos << ". Nama: " << temp->namaItem
                 << ", Jumlah: " << temp->jumlah
                 << ", Tipe: " << temp->tipe << "\n";
            temp = temp->next;
            pos++;
        }
        cout << "====================\n";
    }

    // Optional: Delete item by name
    void hapusItemByNama(string nama) {
        Item* temp = head;
        Item* prev = nullptr;

        while (temp != nullptr && temp->namaItem != nama) {
            prev = temp;
            temp = temp->next;
        }

        if (temp == nullptr) {
            cout << "Item '" << nama << "' tidak ditemukan!\n";
            return;
        }

        if (prev == nullptr) {
            head = temp->next;
        } else {
            prev->next = temp->next;
        }
        cout << "Item '" << nama << "' dihapus.\n";
        delete temp;
    }

    // Optional: Count total item
    int hitungTotalItem() {
        int total = 0;
        Item* temp = head;
        while (temp != nullptr) {
            total += temp->jumlah;
            temp = temp->next;
        }
        return total;
    }
};

// Main program
int main() {
    Inventory inv;
    string nama, nim;
    int pilihan;
    string namaItem, tipe;
    const int POSISI_SISIP = 12; // Personalization: insert at position 12

    // Input Identitas
    cout << "Masukkan Nama: ";
    getline(cin, nama);
    cout << "Masukkan NIM: ";
    getline(cin, nim);

    do {
        // Display Menu
        cout << "\n+======================================+\n";
        cout << "|    GAME INVENTORY MANAGEMENT          |\n";
        cout << "|    " << nama << " - " << nim << "          |\n";
        cout << "+======================================+\n";
        cout << "| 1. Tambah Item Baru                  |\n";
        cout << "| 2. Sisipkan Item                     |\n";
        cout << "| 3. Hapus Item Terakhir               |\n";
        cout << "| 4. Gunakan Item                      |\n";
        cout << "| 5. Tampilkan Inventory               |\n";
        cout << "| 6. Hapus Item by Nama (Bonus)        |\n";
        cout << "| 7. Hitung Total Item (Bonus)         |\n";
        cout << "| 0. Keluar                            |\n";
        cout << "+======================================+\n";
        cout << "Pilih menu: ";
        cin >> pilihan;
        cin.ignore(); // Clear buffer

        switch (pilihan) {
            case 1: // Tambah Item Baru
                cout << "Masukkan nama item: ";
                getline(cin, namaItem);
                cout << "Masukkan tipe item (contoh: Sword, Potion, Armor): ";
                getline(cin, tipe);
                inv.tambahItem(namaItem, tipe);
                break;

            case 2: // Sisipkan Item
                cout << "Masukkan nama item: ";
                getline(cin, namaItem);
                cout << "Masukkan tipe item: ";
                getline(cin, tipe);
                inv.sisipkanItem(namaItem, tipe, POSISI_SISIP);
                break;

            case 3: // Hapus Item Terakhir
                inv.hapusItemTerakhir();
                break;

            case 4: // Gunakan Item
                cout << "Masukkan nama item yang ingin digunakan: ";
                getline(cin, namaItem);
                inv.gunakanItem(namaItem);
                break;

            case 5: // Tampilkan Inventory
                inv.tampilkanInventory();
                break;

            case 6: // Bonus: Hapus Item by Nama
                cout << "Masukkan nama item yang ingin dihapus: ";
                getline(cin, namaItem);
                inv.hapusItemByNama(namaItem);
                break;

            case 7: // Bonus: Hitung Total Item
                cout << "Total jumlah item di inventory: " << inv.hitungTotalItem() << "\n";
                break;

            case 0: // Keluar
                cout << "Terima kasih, " << nama << "! Program selesai.\n";
                break;

            default:
                cout << "Pilihan tidak valid!\n";
        }
    } while (pilihan != 0);

    return 0;
}