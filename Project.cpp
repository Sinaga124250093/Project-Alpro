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

int main(int argc, char **argv)
{
	
	return 0;
}

