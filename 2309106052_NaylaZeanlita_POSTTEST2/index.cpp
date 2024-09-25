// MANAJEMEN PROYEK PEMBANGUNAN JALAN
// NAYLA ZEANLITA PUTRI NUR'AIN
// 2309106052
// POSTTEST 2 STRUKTUR DATA

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>
#include <algorithm>

using namespace std;

struct Kontraktor
{
    int id;
    string nama;
};

struct Material
{
    int id;
    int kodeProyek;
    string nama;
    float kuantitas;
    float harga;
};

struct Proyek
{
    int kode;
    string nama;
    string status;
};

vector<Kontraktor> daftarKontraktor = {
    {1, "Yusman"},
    {2, "Reza"},
    {3, "Salim"},
    {4, "Saputra"},
    {5, "Yoseph"}};

vector<Proyek> daftarProyek = {
    {1, "Tol Balikpapan-Samarinda", "Selesai"},
    {2, "Tol IKN", "Menunggu"},
    {3, "Jalan Poros Berau-Bontang", "Selesai"},
    {4, "Jembatan Penajam-Balikpapan", "Berlangsung"},
    {5, "Jalur MRT Surabaya", "Berlangsung"}};

vector<Material> daftarMaterial;

void tampilkanDaftarKontraktor()
{
    cout << "Daftar Kontraktor:\n";
    cout << setw(5) << "ID" << setw(15) << "Nama" << endl;
    cout << string(20, '-') << endl;
    for (const auto &kontraktor : daftarKontraktor)
    {
        cout << setw(5) << kontraktor.id << setw(15) << kontraktor.nama << endl;
    }
}

void tampilkanDaftarMaterial()
{
    cout << "Daftar Material:\n";
    cout << setw(5) << "ID" << setw(15) << "Kode Proyek" << setw(20) << "Nama"
         << setw(15) << "Kuantitas" << setw(15) << "Harga" << endl;
    cout << string(70, '-') << endl;
    for (const auto &material : daftarMaterial)
    {
        cout << setw(5) << material.id
             << setw(15) << material.kodeProyek
             << setw(20) << material.nama
             << setw(15) << material.kuantitas
             << setw(15) << material.harga << endl;
    }
}

void tampilkanDaftarProyek()
{
    cout << "Daftar Proyek:\n";
    cout << setw(5) << "Kode" << setw(30) << "Nama" << setw(15) << "Status" << endl;
    cout << string(50, '-') << endl;
    for (const auto &proyek : daftarProyek)
    {
        cout << setw(5) << proyek.kode
             << setw(30) << proyek.nama
             << setw(15) << proyek.status << endl;
    }
}

float hitungAnggaranProyek(int kodeProyek)
{
    float total = 0;
    for (const auto &material : daftarMaterial)
    {
        if (material.kodeProyek == kodeProyek)
        {
            total += material.harga * material.kuantitas;
        }
    }
    return total;
}

void tampilkanAnggaran()
{
    cout << "Anggaran Proyek:\n";
    cout << setw(30) << "Nama Proyek" << setw(20) << "Anggaran Terpakai" << endl;
    cout << string(50, '-') << endl;
    for (const auto &proyek : daftarProyek)
    {
        float anggaran = hitungAnggaranProyek(proyek.kode);
        cout << setw(30) << proyek.nama
             << setw(20) << fixed << setprecision(2) << anggaran << endl;
    }
}

void tambahMaterial()
{
    Material material;
    cout << "Masukkan ID Material: ";
    cin >> material.id;
    cout << "Masukkan Kode Proyek: ";
    cin >> material.kodeProyek;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Masukkan Nama Material: ";
    getline(cin, material.nama);
    cout << "Masukkan Kuantitas: ";
    cin >> material.kuantitas;
    cout << "Masukkan Harga: ";
    cin >> material.harga;

    daftarMaterial.push_back(material);
    cout << "Material berhasil ditambahkan.\n";
}

void hapusMaterial()
{
    int id;
    cout << "Masukkan ID Material yang akan dihapus: ";
    cin >> id;

    auto it = remove_if(daftarMaterial.begin(), daftarMaterial.end(),
                        [id](const Material &m)
                        { return m.id == id; });

    if (it != daftarMaterial.end())
    {
        daftarMaterial.erase(it, daftarMaterial.end());
        cout << "Material berhasil dihapus.\n";
    }
    else
    {
        cout << "Material tidak ditemukan.\n";
    }
}

void updateMaterial()
{
    int id;
    cout << "Masukkan ID Material yang akan diupdate: ";
    cin >> id;

    for (auto &material : daftarMaterial)
    {
        if (material.id == id)
        {
            cout << "Masukkan Kode Proyek baru: ";
            cin >> material.kodeProyek;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Masukkan Nama Material baru: ";
            getline(cin, material.nama);
            cout << "Masukkan Kuantitas baru: ";
            cin >> material.kuantitas;
            cout << "Masukkan Harga baru: ";
            cin >> material.harga;
            cout << "Material berhasil diupdate.\n";
            return;
        }
    }
    cout << "Material tidak ditemukan.\n";
}

void menuMaterial()
{
    int pilihan;
    do
    {
        cout << "\nMenu Material:\n";
        cout << "1. Tampilkan Daftar Material\n";
        cout << "2. Tambah Material\n";
        cout << "3. Update Material\n";
        cout << "4. Hapus Material\n";
        cout << "5. Kembali ke Menu Utama\n";
        cout << "Pilihan Anda: ";
        cin >> pilihan;

        switch (pilihan)
        {
        case 1:
            tampilkanDaftarMaterial();
            break;
        case 2:
            tambahMaterial();
            break;
        case 3:
            updateMaterial();
            break;
        case 4:
            hapusMaterial();
            break;
        case 5:
            cout << "Kembali ke menu utama...\n";
            break;
        default:
            cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 5);
}

void menuUtama()
{
    int pilihan;
    do
    {
        cout << "\nMenu Utama:\n";
        cout << "1. Daftar Kontraktor\n";
        cout << "2. Manajemen Material\n";
        cout << "3. Daftar Proyek\n";
        cout << "4. Anggaran Proyek\n";
        cout << "5. Keluar\n";
        cout << "Pilihan Anda: ";
        cin >> pilihan;

        switch (pilihan)
        {
        case 1:
            tampilkanDaftarKontraktor();
            break;
        case 2:
            menuMaterial();
            break;
        case 3:
            tampilkanDaftarProyek();
            break;
        case 4:
            tampilkanAnggaran();
            break;
        case 5:
            cout << "Terima kasih telah menggunakan program ini.\n";
            break;
        default:
            cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 5);
}

int main()
{
    cout << "Selamat datang di Program Manajemen Proyek Pembangunan Jalan\n";
    menuUtama();
    return 0;
}