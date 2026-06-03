#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// [ENCAPSULATION] - Pembuat: Faisyar
class MataKuliah {
private:
    string namaMK;
    int sks;
    double nilaiAngka;

public:
    // Constructor
    MataKuliah(string n, int s, double nilai) {
        namaMK = n;
        sks = s;
        nilaiAngka = nilai;
    }

    // Getter methods untuk mengakses data private secara aman
    string getNamaMK() { return namaMK; }
    int getSKS() { return sks; }
    double getNilaiAngka() { return nilaiAngka; }
};

// [ENCAPSULATION] - Pembuat: Faisyar
class MahasiswaBase {
private:
    string nama;
    string nim;

public:
    // Setter untuk mengisi data
    void setNama(string n) { nama = n; }
    void setNim(string n) { nim = n; }

    // Getter untuk mengambil data
    string getNama() { return nama; }
    string getNim() { return nim; }
};

// [INHERITANCE] - Pembuat: Haikal
class Penilaian {
protected:
    // Fungsi untuk menghitung Indeks Prestasi (IP) per mata kuliah
    double konversiKeBobot(double nilai) {
        if (nilai >= 90) return 4.0;       // A+
        else if (nilai >= 86) return 3.75; // A
        else if (nilai >= 80) return 3.50; // A-
        else if (nilai >= 76) return 3.25; // B+
        else if (nilai >= 73) return 3.00; // B
        else if (nilai >= 66) return 2.75; // B-
        else if (nilai >= 61) return 2.50; // C+
        else if (nilai >= 51) return 2.00; // C
        else if (nilai >= 41) return 1.00; // D
        else return 0.0;                   // E
    }

    string konversiKeHuruf(double nilai) {
        if (nilai >= 90) return "A+";     // A+
        else if (nilai >= 86) return "A"; // A
        else if (nilai >= 80) return "A-";// A-
        else if (nilai >= 76) return "B+";// B+
        else if (nilai >= 73) return "B"; // B
        else if (nilai >= 66) return "B-";// B-
        else if (nilai >= 61) return "C+";// C+
        else if (nilai >= 51) return "C"; // C
        else if (nilai >= 41) return "D"; // D
        else return "E";                  // E
    }
};

// [INHERITANCE] Pembuat: Haikal | [MULTIPLE INHERITANCE] Pembuat: Restu
class TranskripMahasiswa : public MahasiswaBase, public Penilaian {
private:
    vector<MataKuliah> daftarMK; // Relasi 'Has-A' (Satu mahasiswa punya banyak MK)

public:
    void tambahMataKuliah(string namaMK, int sks, double nilai) {
        MataKuliah mk(namaMK, sks, nilai);
        daftarMK.push_back(mk);
    }

    double hitungIPK() {
        double totalNilaiBobot = 0;
        int totalSKS = 0;

        for (auto& mk : daftarMK) {
            // Memanggil fungsi konversiKeBobot hasil warisan dari kelas Penilaian
            double bobot = konversiKeBobot(mk.getNilaiAngka());
            totalNilaiBobot += (bobot * mk.getSKS());
            totalSKS += mk.getSKS();
        }

        if (totalSKS == 0) return 0.0; // Mencegah pembagian dengan nol
        return totalNilaiBobot / totalSKS;
    }

    void cetakTranskrip() {
        cout << "\n======================================================\n";
        cout << "                 KARTU HASIL STUDI (KHS)              \n";
        cout << "======================================================\n";
        // Memanggil fungsi getNama() dan getNim() hasil warisan dari MahasiswaBase
        cout << "Nama Mahasiswa : " << getNama() << "\n";
        cout << "NIM            : " << getNim() << "\n";
        cout << "------------------------------------------------------\n";
        cout << left << setw(20) << "Mata Kuliah" 
             << setw(5) << "SKS" 
             << setw(10) << "Nilai" 
             << setw(10) << "Huruf" 
             << "IP (Bobot)\n";
        cout << "------------------------------------------------------\n";

        for (auto& mk : daftarMK) {
            double bobot = konversiKeBobot(mk.getNilaiAngka());
            string huruf = konversiKeHuruf(mk.getNilaiAngka());

            cout << left << setw(20) << mk.getNamaMK() 
                 << setw(5) << mk.getSKS() 
                 << setw(10) << mk.getNilaiAngka() 
                 << setw(10) << huruf 
                 << fixed << setprecision(2) << bobot << "\n";
        }

        cout << "------------------------------------------------------\n";
        cout << "IPK KESELURUHAN : " << fixed << setprecision(2) << hitungIPK() << "\n";
        cout << "======================================================\n";
    }
};

int main() {
    TranskripMahasiswa mhs;
    string inputNama, inputNim;
    int jumlahMK;

    cout << "=== PROGRAM INPUT DATA AKADEMIK MAHASISWA ===\n\n";

    // Input Data Mahasiswa
    cout << "Masukkan Nama Mahasiswa : ";
    getline(cin, inputNama);
    mhs.setNama(inputNama);

    cout << "Masukkan NIM            : ";
    getline(cin, inputNim);
    mhs.setNim(inputNim);

    // Input Mata Kuliah
    cout << "Masukkan jumlah Mata Kuliah yang diambil: ";
    cin >> jumlahMK;
    cin.ignore(); // Membersihkan buffer enter setelah cin

    for (int i = 0; i < jumlahMK; i++) {
        string namaMK;
        int sks;
        double nilai;

        cout << "\n--- Data Mata Kuliah " << i + 1 << " ---\n";
        cout << "Nama Mata Kuliah : ";
        getline(cin, namaMK);
        cout << "SKS              : ";
        cin >> sks;
        cout << "Nilai Angka (0-100): ";
        cin >> nilai;
        cin.ignore(); 

        mhs.tambahMataKuliah(namaMK, sks, nilai);
    }

    // Menampilkan Hasil Akhir
    mhs.cetakTranskrip();

    return 0;
}
