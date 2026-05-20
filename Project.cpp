#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

struct Aspirasi {
    char nim[20];
    char keluhan[255];
    Aspirasi* next;
};
Aspirasi* headAspirasi = NULL;

struct Beasiswa {
    char nim[20];
    char nama[50];
    float ipk;
    int urgensi;
    Beasiswa* next;
};
Beasiswa* headBeasiswa = NULL;
Beasiswa* tailBeasiswa = NULL;

void tambahAspirasi() {
    Aspirasi* nodeBaru = new Aspirasi;
    cout << "\n--- Tambah Aspirasi / Keluhan ---" << endl;
    cout << "Masukkan NIM: "; cin >> nodeBaru->nim;
    cout << "Keluhan (Gunakan '_' untuk spasi): "; cin >> nodeBaru->keluhan;
    
    nodeBaru->next = headAspirasi;
    headAspirasi = nodeBaru;
    
    cout << "Data aspirasi berhasil ditambahkan di awal antrean!" << endl;
}

void tambahBeasiswa() {
    Beasiswa* nodeBaru = new Beasiswa;
    cout << "\n--- Pengajuan Beasiswa ---" << endl;
    cout << "Masukkan NIM: "; cin >> nodeBaru->nim;
    cout << "Nama (Gunakan '_' untuk spasi): "; cin >> nodeBaru->nama;
    cout << "IPK: "; cin >> nodeBaru->ipk;
    cout << "Tingkat Urgensi (1-5): "; cin >> nodeBaru->urgensi;
    
    nodeBaru->next = NULL;
    
    if (headBeasiswa == NULL) {
        headBeasiswa = nodeBaru;
        tailBeasiswa = nodeBaru;
    } else {
        tailBeasiswa->next = nodeBaru;
        tailBeasiswa = nodeBaru;
    }
    cout << "Data pengajuan beasiswa masuk ke dalam antrean (Tail)!" << endl;
}

void cariData() {
    char cariNIM[20];
    cout << "\nMasukkan NIM yang ingin dicari: ";
    cin >> cariNIM;
    
    bool ditemukan = false;
    
    Aspirasi* tempA = headAspirasi;
    while (tempA != NULL) {
        if (strcmp(tempA->nim, cariNIM) == 0) {
            cout << "[Ditemukan di Data Aspirasi] Keluhan: " << tempA->keluhan << endl;
            ditemukan = true;
        }
        tempA = tempA->next;
    }
    
    Beasiswa* tempB = headBeasiswa;
    while (tempB != NULL) {
        if (strcmp(tempB->nim, cariNIM) == 0) {
            cout << "[Ditemukan di Data Beasiswa] Nama: " << tempB->nama 
                 << " | IPK: " << tempB->ipk << " | Urgensi: " << tempB->urgensi << endl;
            ditemukan = true;
        }
        tempB = tempB->next;
    }
    
    if (!ditemukan) {
        cout << "Data dengan NIM " << cariNIM << " tidak ditemukan." << endl;
    }
}

void urutkanBeasiswa() {
    if (headBeasiswa == NULL || headBeasiswa->next == NULL) {
        cout << "Data belum cukup untuk diurutkan." << endl;
        return;
    }
    
    bool swapped;
    Beasiswa* ptr1;
    Beasiswa* lptr = NULL;
    
    do {
        swapped = false;
        ptr1 = headBeasiswa;
        
        while (ptr1->next != lptr) {
            if (ptr1->ipk < ptr1->next->ipk) { 
                char tempNim[20], tempNama[50];
                strcpy(tempNim, ptr1->nim);
                strcpy(tempNama, ptr1->nama);
                float tempIpk = ptr1->ipk;
                int tempUrgensi = ptr1->urgensi;
                
                strcpy(ptr1->nim, ptr1->next->nim);
                strcpy(ptr1->nama, ptr1->next->nama);
                ptr1->ipk = ptr1->next->ipk;
                ptr1->urgensi = ptr1->next->urgensi;
                
                strcpy(ptr1->next->nim, tempNim);
                strcpy(ptr1->next->nama, tempNama);
                ptr1->next->ipk = tempIpk;
                ptr1->next->urgensi = tempUrgensi;
                
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
    
    cout << "Data beasiswa berhasil diurutkan berdasarkan IPK (Tertinggi ke Terendah)!" << endl;
}

void tampilkanAspirasi() {
    cout << "--- Riwayat Aspirasi Mahasiswa ---" << endl;
    if (headAspirasi == NULL) { cout << "Data Kosong." << endl; return; }
    
    Aspirasi* temp = headAspirasi;
    while (temp != NULL) {
        cout << "NIM: " << temp->nim << " | Keluhan: " << temp->keluhan << endl;
        temp = temp->next;
    }
}

void tampilkanBeasiswa() {
    cout << "--- Antrean Pengajuan Beasiswa ---" << endl;
    if (headBeasiswa == NULL) { cout << "Data Kosong." << endl; return; }
    
    Beasiswa* temp = headBeasiswa;
    while (temp != NULL) {
        cout << "NIM: " << temp->nim << " | Nama: " << temp->nama 
             << " | IPK: " << temp->ipk << " | Urgensi: " << temp->urgensi << endl;
        temp = temp->next;
    }
}

void simpanData() {
    FILE* file = fopen("data_advokasi.txt", "w");
    if (file == NULL) {
        cout << "Gagal membuat file!" << endl; return;
    }
    
    Aspirasi* tempA = headAspirasi;
    while (tempA != NULL) {
        fprintf(file, "ASPIRASI %s %s\n", tempA->nim, tempA->keluhan);
        tempA = tempA->next;
    }
    
    Beasiswa* tempB = headBeasiswa;
    while (tempB != NULL) {
        fprintf(file, "BEASISWA %s %s %.2f %d\n", tempB->nim, tempB->nama, tempB->ipk, tempB->urgensi);
        tempB = tempB->next;
    }
    
    fclose(file);
    cout << "\nData berhasil disimpan ke dalam data_advokasi.txt!" << endl;
}

void muatData() {
    FILE* file = fopen("data_advokasi.txt", "r");
    if (file == NULL) {
        cout << "File data belum ada. Memulai program dari awal." << endl;
        return;
    }
    
    char tipe[20];
    while (fscanf(file, "%s", tipe) != EOF) {
        if (strcmp(tipe, "ASPIRASI") == 0) {
            Aspirasi* nodeBaru = new Aspirasi;
            fscanf(file, "%s %s", nodeBaru->nim, nodeBaru->keluhan);
            nodeBaru->next = headAspirasi;
            headAspirasi = nodeBaru;
            
        } else if (strcmp(tipe, "BEASISWA") == 0) {
            Beasiswa* nodeBaru = new Beasiswa;
            fscanf(file, "%s %s %f %d", nodeBaru->nim, nodeBaru->nama, &nodeBaru->ipk, &nodeBaru->urgensi);
            nodeBaru->next = NULL;
            
            if (headBeasiswa == NULL) {
                headBeasiswa = nodeBaru;
                tailBeasiswa = nodeBaru;
            } else {
                tailBeasiswa->next = nodeBaru;
                tailBeasiswa = nodeBaru;
            }
        }
    }
    fclose(file);
    cout << "Data historis berhasil dimuat!" << endl;
}

int main() {
    muatData(); 
    int pilihan;
    
    do {
        cout << "=============================================" << endl;
        cout << "     SISTEM MANAJEMEN ADVOKASI MAHASISWA     " << endl;
        cout << "=============================================" << endl;
        cout << "1. Tambah Keluhan/Aspirasi" << endl;
        cout << "2. Ajukan Beasiswa" << endl;
        cout << "3. Lihat Semua Aspirasi" << endl;
        cout << "4. Lihat Antrean Beasiswa";
        cout << "5. Urutkan Beasiswa Berdasarkan IPK" << endl;
        cout << "6. Cari Status Berdasarkan NIM" << endl;
        cout << "7. Simpan Data & Keluar" << endl;
        cout << "=============================================" << endl;
        cout << "Pilihan Anda: ";
        cin >> pilihan;
        
        switch (pilihan) {
            case 1: tambahAspirasi(); break;
            case 2: tambahBeasiswa(); break;
            case 3: tampilkanAspirasi(); break;
            case 4: tampilkanBeasiswa(); break;
            case 5: urutkanBeasiswa(); break;
            case 6: cariData(); break;
            case 7: 
                simpanData(); 
                cout << "Program selesai. Data tersimpan." << endl;
                break;
            default: cout << "Pilihan tidak valid!" << endl;
        }
    } while (pilihan != 7);
    
    return 0;
}

