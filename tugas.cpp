#include<iostream>
#include<vector>
#include<string>
using namespace std;

const int TABLE_SIZE = 10;

class HashTable{
    private:
        vector<pair<int, string>> table;
        vector<int> status;

        int hash1(int key){
            return key % TABLE_SIZE;
        }

        int hash2(int key){
            return 7 - (key % 7);
        }

    public:
        HashTable(){
            table.resize(TABLE_SIZE);
            status.resize(TABLE_SIZE, 0);
        }

    void insert(int nim, string nama){
        int index = hash1(nim);
        int step = hash2(nim);
        int initialIndex = index;

        int deletedIndex = -1;

        while(true){
            if(status[index] == 1 && table[index].first == nim){
                table[index].second = nama;
                cout << "NIM sudah ada, nama diperbarui\n";
                return;
            }

            if (status[index] == 2 && deletedIndex == -1){
                deletedIndex = index;
            }

            if (status[index] == 0){
                if (deletedIndex != -1){
                    index = deletedIndex;
                }
                table[index] = make_pair(nim, nama);
                status[index] = 1;
                cout << "Data berhasil disimpan di index " << index << endl;
                return;
            }

            index = (index + step) % TABLE_SIZE;

            if(index == initialIndex){
                break;
            }
        }

        if(deletedIndex != -1){
            table[deletedIndex] = make_pair(nim, nama);
            status[deletedIndex] = 1;
            cout << "Data berhasil disimpan di index " << deletedIndex << endl;
        } else {
            cout << "Tabel penuh\n";
        }
    }

    void search(int nim){
        int index = hash1(nim);
        int step = hash2(nim);
        int initialIndex = index;

        while (status[index] != 0){
            if (status[index] == 1 && table[index].first == nim){
                cout << "Data ditemukan di index " << index << ": " << table[index].second << endl;
                return;
            }

            index = (index + step) % TABLE_SIZE;

            if(index == initialIndex){
                break;
            }
        }
        cout << "Data tidak ditemukan\n";
    }

    void remove(int nim){
        int index = hash1(nim);
        int step = hash2(nim);
        int initialIndex = index;

        while (status[index] != 0){
            if (status[index] == 1 && table[index].first == nim){
                status[index] = 2;
                cout << "Data berhasil dihapus\n";
                return;
            }

            index = (index + step) % TABLE_SIZE;

            if (index == initialIndex){
                break;
            }
        }
        cout << "Data tidak ditemukan\n";
    }

    void display(){
        for (int i = 0; i < TABLE_SIZE; i++){
            cout << i << " : ";

            if (status[i] == 1){
                cout << table[i].first << " - " << table[i].second;
            } else if (status[i] == 2){
                cout << "DELETED";
            } else {
                cout << "EMPTY";
            }

            cout << endl;
        }
    }
};

int main(){
    system("cls");
    HashTable ht;

    int pilihan, nim;
    string nama;

    do {
        cout << "\n=== HASH TABLE MAHASISWA ===\n";
        cout << "1. Insert\n";
        cout << "2. Search\n";
        cout << "3. Remove\n";
        cout << "0. Selesai dan tampilkan hash table\n";
        cout << "Pilihan: "; cin >> pilihan;

        if (pilihan == 1){
            cout << "Masukkan NIM  : "; cin >> nim;
            cin.ignore();
            cout << "Masukkan nama : "; getline(cin, nama);
            ht.insert(nim, nama);
        } else if (pilihan == 2){
            cout << "Masukkan NIM yang dicari: "; cin >> nim;
            ht.search(nim);
        } else if (pilihan == 3){
            cout << "Masukkan NIM yang dihapus: "; cin >> nim;
            ht.remove(nim);
        } else if (pilihan != 0){
            cout << "Pilihan tidak valid\n";
        }
    } while (pilihan != 0);

    cout << endl << "Isi hash table setelah seluruh operasi: \n";
    ht.display();

    return 0;
}