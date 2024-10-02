// MANAJEMEN PROYEK PEMBANGUNAN JALAN
// NAYLA ZEANLITA PUTRI NUR'AIN
// 2309106052
// POSTTEST 3 STRUKTUR DATA

#include <iostream>
#include <string>
#include <iomanip>
#include <limits>

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
    Material *next;
};

struct Proyek
{
    int kode;
    string nama;
    string status;
};

Material *head = nullptr;
Kontraktor daftarKontraktor[] = {
    {1, "Yusman"},
    {2, "Reza"},
    {3, "Salim"},
    {4, "Saputra"},
    {5, "Yoseph"}};
Proyek daftarProyek[] = {
    {1, "Tol Balikpapan-Samarinda", "Selesai"},
    {2, "Tol IKN", "Menunggu"},
    {3, "Jalan Poros Berau-Bontang", "Selesai"},
    {4, "Jembatan Penajam-Balikpapan", "Berlangsung"},
    {5, "Jalur MRT Surabaya", "Berlangsung"}};

void tambahMaterial(const Material &material)
{
    Material *newNode = new Material(material);
    newNode->next = nullptr;

    if (!head)
    {
        head = newNode;
    }
    else
    {
        Material *current = head;
        while (current->next)
        {
            current = current->next;
        }
        current->next = newNode;
    }
}

void hapusMaterial(int id)
{
    if (!head)
        return;

    if (head->id == id)
    {
        Material *temp = head;
        head = head->next;
        delete temp;
        return;
    }

    Material *current = head;
    while (current->next && current->next->id != id)
    {
        current = current->next;
    }

    if (current->next)
    {
        Material *temp = current->next;
        current->next = current->next->next;
        delete temp;
    }
}

void updateMaterial(int id, const Material &updatedMaterial)
{
    Material *current = head;
    while (current && current->id != id)
    {
        current = current->next;
    }

    if (current)
    {
        current->kodeProyek = updatedMaterial.kodeProyek;
        current->nama = updatedMaterial.nama;
        current->kuantitas = updatedMaterial.kuantitas;
        current->harga = updatedMaterial.harga;
    }
}

void tampilkanDaftarMaterial()
{
    cout << "Daftar Material:\n";
    cout << setw(5) << "ID" << setw(15) << "Kode Proyek" << setw(20) << "Nama"
         << setw(15) << "Kuantitas" << setw(15) << "Harga" << endl;
    cout << string(70, '-') << endl;

    Material *current = head;
    while (current)
    {
        cout << setw(5) << current->id
             << setw(15) << current->kodeProyek
             << setw(20) << current->nama
             << setw(15) << current->kuantitas
             << setw(15) << current->harga << endl;
        current = current->next;
    }
}

float hitungAnggaranProyek(int kodeProyek)
{
    float total = 0;
    Material *current = head;
    while (current)
    {
        if (current->kodeProyek == kodeProyek)
        {
            total += current->harga * current->kuantitas;
        }
        current = current->next;
    }
    return total;
}

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
            tambahMaterial(material);
            cout << "Material berhasil ditambahkan.\n";
            break;
        }
        case 3:
        {
            int id;
            cout << "Masukkan ID Material yang akan diupdate: ";
            cin >> id;
            Material updatedMaterial;
            updatedMaterial.id = id;
            cout << "Masukkan Kode Proyek baru: ";
            cin >> updatedMaterial.kodeProyek;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Masukkan Nama Material baru: ";
            getline(cin, updatedMaterial.nama);
            cout << "Masukkan Kuantitas baru: ";
            cin >> updatedMaterial.kuantitas;
            cout << "Masukkan Harga baru: ";
            cin >> updatedMaterial.harga;
            updateMaterial(id, updatedMaterial);
            cout << "Material berhasil diupdate.\n";
            break;
        }
        case 4:
        {
            int id;
            cout << "Masukkan ID Material yang akan dihapus: ";
            cin >> id;
            hapusMaterial(id);
            cout << "Material berhasil dihapus.\n";
            break;
        }
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
    Material material1 = {1, 1, "Aspal", 1000, 10000, nullptr};
    Material material2 = {2, 1, "Batu kerikil", 500, 5000, nullptr};
    Material material3 = {3, 2, "Semen", 200, 50000, nullptr};
    Material material4 = {4, 3, "Pasir", 300, 2000, nullptr};
    Material material5 = {5, 4, "Besi beton", 100, 15000, nullptr};
    Material material6 = {2, 5, "Batu kerikil", 5000, 5000, nullptr};

    tambahMaterial(material1);
    tambahMaterial(material2);
    tambahMaterial(material3);
    tambahMaterial(material4);
    tambahMaterial(material5);
    tambahMaterial(material6);

    cout << "Manajemen Proyek Pembangunan Jalan\n";
    menuUtama();
    while (head)
    {
        Material *temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}