// MANAJEMEN PROYEK PEMBANGUNAN JALAN
// NAYLA ZEANLITA PUTRI NUR'AIN
// 2309106052
// POSTTEST 5 STRUKTUR DATA

#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <algorithm>
#include <cmath>

using namespace std;

struct Kontraktor
{
    int id;
    string nama;
};

Kontraktor daftarKontraktor[] = {
    {1, "Yusman"},
    {2, "Reza"},
    {3, "Salim"},
    {4, "Saputra"},
    {5, "Yoseph"}};

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
    Proyek *next;
};

Material *head_material = nullptr;
Proyek *head_proyek = nullptr;

void tampilkanDaftarKontraktor()
{
    cout << "\nDaftar Kontraktor:\n";
    cout << setw(5) << "ID" << setw(15) << "Nama" << endl;
    cout << string(20, '-') << endl;
    for (const auto &kontraktor : daftarKontraktor)
    {
        cout << setw(5) << kontraktor.id << setw(15) << kontraktor.nama << endl;
    }
}

void tambahProyek(const Proyek &proyek)
{
    Proyek *newNode = new Proyek(proyek);
    newNode->next = nullptr;

    if (!head_proyek)
    {
        head_proyek = newNode;
    }
    else
    {
        Proyek *current = head_proyek;
        while (current->next)
        {
            current = current->next;
        }
        current->next = newNode;
    }
}

int fibonacciSearch(Kontraktor arr[], int n, int x)
{
    int fibM2 = 0;
    int fibM1 = 1;
    int fibM = fibM2 + fibM1;

    while (fibM < n)
    {
        fibM2 = fibM1;
        fibM1 = fibM;
        fibM = fibM2 + fibM1;
    }

    int offset = -1;

    while (fibM > 1)
    {
        int i = min(offset + fibM2, n - 1);

        if (arr[i].id < x)
        {
            fibM = fibM1;
            fibM1 = fibM2;
            fibM2 = fibM - fibM1;
            offset = i;
        }
        else if (arr[i].id > x)
        {
            fibM = fibM2;
            fibM1 = fibM1 - fibM2;
            fibM2 = fibM - fibM1;
        }
        else
        {
            return i;
        }
    }

    if (fibM1 && arr[offset + 1].id == x)
    {
        return offset + 1;
    }

    return -1;
}

int getproyekLength(Proyek *head_proyek)
{
    int length = 0;
    while (head_proyek)
    {
        length++;
        head_proyek = head_proyek->next;
    }
    return length;
}

void shellsortProyekDesc()
{
    int n = getproyekLength(head_proyek);
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; i++)
        {
            Proyek *temp = head_proyek;
            for (int k = 0; k < i; k++)
                temp = temp->next;

            Proyek *current = temp;
            int j = i;
            while (j >= gap)
            {
                Proyek *prev = head_proyek;
                for (int k = 0; k < j - gap; k++)
                    prev = prev->next;

                if (current->nama > prev->nama)
                {
                    swap(current->nama, prev->nama);
                    swap(current->kode, prev->kode);
                    swap(current->status, prev->status);
                }
                else
                    break;
                j -= gap;
            }
        }
    }
}

int getmaterialLength(Material *head_material)
{
    int length = 0;
    while (head_material)
    {
        length++;
        head_material = head_material->next;
    }
    return length;
}

Material *jumpSearchmaterial(Material *head_material, int x)
{
    if (head_material == nullptr)
        return nullptr;

    int step = sqrt(getmaterialLength(head_material));
    Material *prev = nullptr;
    Material *current = head_material;

    while (current && current->id < x)
    {
        prev = current;
        for (int i = 0; i < step && current->next; i++)
            current = current->next;
    }

    while (prev && prev->id <= x)
    {
        if (prev->id == x)
            return prev;
        prev = prev->next;
    }

    return nullptr;
}

Material *sortedMerge(Material *a, Material *b)
{
    if (!a)
        return b;
    if (!b)
        return a;

    Material *result = nullptr;
    if (a->kodeProyek <= b->kodeProyek)
    {
        result = a;
        result->next = sortedMerge(a->next, b);
    }
    else
    {
        result = b;
        result->next = sortedMerge(a, b->next);
    }
    return result;
}

void split(Material *source, Material **front, Material **back)
{
    Material *fast = source->next;
    Material *slow = source;

    while (fast)
    {
        fast = fast->next;
        if (fast)
        {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *front = source;
    *back = slow->next;
    slow->next = nullptr;
}

void mergeSortMaterial(Material *&head)
{
    if (!head || !head->next)
        return;

    Material *a;
    Material *b;

    split(head, &a, &b);

    mergeSortMaterial(a);
    mergeSortMaterial(b);

    head = sortedMerge(a, b);
}

void tampilkanDaftarMaterial()
{
    cout << "\nDaftar Material (Sorted by Kode Proyek):\n";
    cout << setw(5) << "ID" << setw(15) << "Kode Proyek" << setw(20) << "Nama"
         << setw(15) << "Kuantitas" << setw(15) << "Harga" << endl;
    cout << string(70, '-') << endl;

    Material *last = head_material;
    while (last->next)
        last = last->next;
    mergeSortMaterial(head_material);

    Material *current = head_material;
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

void tampilkanDaftarProyek()
{
    shellsortProyekDesc();
    cout << "\nDaftar Proyek (Sorted by Nama Desc):\n";
    cout << setw(5) << "Kode" << setw(30) << "Nama" << setw(15) << "Status" << endl;
    cout << string(50, '-') << endl;
    Proyek *current = head_proyek;
    while (current)
    {
        cout << setw(5) << current->kode
             << setw(30) << current->nama
             << setw(15) << current->status << endl;
        current = current->next;
    }
}

void tambahMaterial(const Material &material)
{
    Material *newNode = new Material(material);
    newNode->next = nullptr;

    if (!head_material)
    {
        head_material = newNode;
    }
    else
    {
        Material *current = head_material;
        while (current->next)
        {
            current = current->next;
        }
        current->next = newNode;
    }
}

void hapusMaterial(int id)
{
    if (!head_material)
        return;

    if (head_material->id == id)
    {
        Material *temp = head_material;
        head_material = head_material->next;
        delete temp;
        return;
    }

    Material *current = head_material;
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
    Material *current = head_material;
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

float hitungAnggaranProyek(int kodeProyek)
{
    float total = 0;
    Material *current = head_material;
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

void tampilkanAnggaran()
{
    cout << "Anggaran Proyek:\n";
    cout << setw(30) << "Nama Proyek" << setw(20) << "Anggaran Terpakai" << endl;
    cout << string(50, '-') << endl;

    Proyek *currentProyek = head_proyek;
    while (currentProyek)
    {
        float anggaran = hitungAnggaranProyek(currentProyek->kode);
        cout << setw(30) << currentProyek->nama
             << setw(20) << fixed << setprecision(2) << anggaran << endl;
        currentProyek = currentProyek->next;
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

void menuPencarian()
{
    int pilihan;
    do
    {
        cout << "\nMenu Pencarian:\n";
        cout << "1. Cari Kontraktor\n";
        cout << "2. Cari Material\n";
        cout << "3. Kembali ke Menu Utama\n";
        cout << "Pilihan Anda: ";
        cin >> pilihan;

        switch (pilihan)
        {
        case 1:
        {
            int id;
            cout << "Masukkan ID Kontraktor yang dicari: ";
            cin >> id;
            int result = fibonacciSearch(daftarKontraktor, 5, id);
            if (result != -1)
                cout << "Kontraktor ditemukan: " << daftarKontraktor[result].nama << endl;
            else
                cout << "Kontraktor tidak ditemukan." << endl;
            break;
        }
        case 2:
        {
            int id;
            cout << "Masukkan ID Material yang dicari: ";
            cin >> id;
            Material *result = jumpSearchmaterial(head_material, id);
            if (result)
                cout << "Material ditemukan: \n"
                     << setw(15) << "Kode Proyek" << setw(20) << "Nama"
                     << setw(15) << "Kuantitas" << setw(15) << "Harga\n"
                     << setw(15) << result->kodeProyek
                     << setw(20) << result->nama
                     << setw(15) << result->kuantitas
                     << setw(15) << result->harga << endl;
            else
                cout << "Material tidak ditemukan." << endl;
            break;
        }
        case 3:
            cout << "Kembali ke menu utama...\n";
            break;
        default:
            cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 4);
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
        cout << "5. Searching\n";
        cout << "6. Keluar\n";
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
            menuPencarian();
            break;
        case 6:
            cout << "Terima kasih telah menggunakan program ini.\n";
            break;
        default:
            cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 6);
}

int main()
{
    // tambah data proyek
    Proyek proyek1 = {1, "Tol Balikpapan-Samarinda", "Selesai", nullptr};
    Proyek proyek2 = {2, "Tol IKN", "Menunggu", nullptr};
    Proyek proyek3 = {3, "Jalan Poros Berau-Bontang", "Selesai", nullptr};
    Proyek proyek4 = {4, "Jembatan Penajam-Balikpapan", "Berlangsung", nullptr};
    Proyek proyek5 = {5, "Jalur MRT Surabaya", "Berlangsung", nullptr};

    tambahProyek(proyek1);
    tambahProyek(proyek2);
    tambahProyek(proyek3);
    tambahProyek(proyek4);
    tambahProyek(proyek5);

    // tambah data material
    Material material1 = {1, 1, "Aspal", 1000, 10000, nullptr};
    Material material2 = {2, 1, "Batu kerikil", 500, 5000, nullptr};
    Material material3 = {3, 2, "Semen", 200, 50000, nullptr};
    Material material4 = {4, 3, "Pasir", 300, 2000, nullptr};
    Material material5 = {5, 4, "Besi beton", 100, 15000, nullptr};
    Material material6 = {6, 5, "Batu kerikil", 5000, 5000, nullptr};

    tambahMaterial(material1);
    tambahMaterial(material2);
    tambahMaterial(material3);
    tambahMaterial(material4);
    tambahMaterial(material5);
    tambahMaterial(material6);

    cout << "Manajemen Proyek Pembangunan Jalan\n";
    menuUtama();

    // Clean up
    while (head_material)
    {
        Material *temp = head_material;
        head_material = head_material->next;
        delete temp;
    }

    while (head_proyek)
    {
        Proyek *temp = head_proyek;
        head_proyek = head_proyek->next;
        delete temp;
    }

    return 0;
}