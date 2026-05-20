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





int main(int argc, char **argv)
{
	
	return 0;
}

