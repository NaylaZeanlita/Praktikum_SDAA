// // MANAJEMEN PROYEK PEMBANGUNAN JALAN
// // NAYLA ZEANLITA PUTRI NUR'AIN
// // 2309106052
// // POSTTEST 5 STRUKTUR DATA

#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <queue>
#include <stack>
#include <algorithm>
#define MAX 100

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
stack<Proyek> daftarProyek;

Kontraktor daftarKontraktor[MAX];
int front = -1;
int rear = -1;

bool isEmpty()
{
    return front == -1;
}

bool isFull()
{
    return rear == MAX - 1;
}

void enqueue(int id, string nama)
{
    if (isFull())
    {
        cout << "Queue penuh. Tidak dapat menambahkan kontraktor baru.\n";
        return;
    }
    if (isEmpty())
    {
        front = 0;
    }
    rear++;
    daftarKontraktor[rear] = {id, nama};
    cout << "Kontraktor " << nama << " telah ditambahkan ke daftar.\n";
}

void dequeue()
{
    if (isEmpty())
    {
        cout << "Daftar kontraktor kosong!\n";
        return;
    }
    cout << "Kontraktor " << daftarKontraktor[front].nama << " telah dihapus dari daftar.\n";
    if (front == rear)
    {
        front = rear = -1;
    }
    else
    {
        front++;
    }
}

void tambahKontraktor()
{
    int id;
    tampilkanDaftarKontraktor();
    string nama;
    Kontraktor kontraktor;
    cout << "Masukkan ID Kontraktor: ";
    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Masukkan Nama Kontraktor: ";
    getline(cin, nama);
    enqueue(id, nama);
    cout << "Kontraktor berhasil ditambahkan.\n";
}

void tampilkanDaftarKontraktor()
{
    if (isEmpty())
    {
        cout << "Daftar Kontraktor kosong" << endl;
        return;
    }
    cout << "Daftar Kontraktor:\n";
    cout << setw(5) << "ID" << setw(30) << "Nama" << endl;
    cout << string(50, '-') << endl;
    for (int i = front; i <= rear; i++)
    {
        cout << setw(5) << daftarKontraktor[i].id;
        cout << setw(30) << daftarKontraktor[i].nama << endl;
    }
}

void hapusKontraktor()
{
    dequeue();
}

void tambahProyek()
{
    Proyek proyek;
    cout << "Masukkan Kode Proyek: ";
    cin >> proyek.kode;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Masukkan Nama Proyek: ";
    getline(cin, proyek.nama);
    cout << "Masukkan Status Proyek: ";
    getline(cin, proyek.status);
    daftarProyek.push(proyek);
    cout << "Proyek berhasil ditambahkan.\n";
}

void tampilkanDaftarProyek()
{
    cout << "Daftar Proyek:\n";
    cout << setw(5) << "Kode" << setw(30) << "Nama" << setw(15) << "Status" << endl;
    cout << string(50, '-') << endl;
    stack<Proyek> tempStack = daftarProyek;
    while (!tempStack.empty())
    {
        Proyek proyek = tempStack.top();
        cout << setw(5) << proyek.kode
             << setw(30) << proyek.nama
             << setw(15) << proyek.status << endl;
        tempStack.pop();
    }
}

void updateProyek()
{
    int kode;
    tampilkanDaftarProyek();
    cout << "Masukkan Kode Proyek yang akan diupdate: ";
    cin >> kode;

    stack<Proyek> tempStack;
    bool found = false;
    while (!daftarProyek.empty())
    {
        Proyek proyek = daftarProyek.top();
        daftarProyek.pop();
        if (proyek.kode == kode)
        {
            found = true;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Masukkan Nama Proyek baru: ";
            getline(cin, proyek.nama);
            cout << "Masukkan Status Proyek baru: ";
            getline(cin, proyek.status);
        }
        tempStack.push(proyek);
    }
    while (!tempStack.empty())
    {
        daftarProyek.push(tempStack.top());
        tempStack.pop();
    }

    if (found)
        cout << "Proyek berhasil diupdate.\n";
    else
        cout << "Proyek dengan Kode tersebut tidak ditemukan.\n";
}

void hapusProyek()
{
    int kode;
    tampilkanDaftarProyek;
    cout << "Masukkan Kode Proyek yang akan dihapus: ";
    cin >> kode;

    stack<Proyek> tempStack;
    bool found = false;
    while (!daftarProyek.empty())
    {
        Proyek proyek = daftarProyek.top();
        daftarProyek.pop();
        if (proyek.kode != kode)
        {
            tempStack.push(proyek);
        }
        else
        {
            found = true;
        }
    }
    while (!tempStack.empty())
    {
        daftarProyek.push(tempStack.top());
        tempStack.pop();
    }

    if (found)
        cout << "Proyek berhasil dihapus.\n";
    else
        cout << "Proyek dengan Kode tersebut tidak ditemukan.\n";
}

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

void tampilkanAnggaran()
{
    cout << "Anggaran Proyek:\n";
    cout << setw(30) << "Nama Proyek" << setw(20) << "Anggaran Terpakai" << endl;
    cout << string(50, '-') << endl;
    stack<Proyek> tempStack = daftarProyek;
    while (!tempStack.empty())
    {
        Proyek proyek = tempStack.top();
        float anggaran = hitungAnggaranProyek(proyek.kode);
        cout << setw(30) << proyek.nama
             << setw(20) << fixed << setprecision(2) << anggaran << endl;
        tempStack.pop();
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
            tampilkanDaftarMaterial();
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
            tampilkanDaftarMaterial();
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
            tampilkanDaftarMaterial();
            int id;
            cout << "Masukkan ID Material yang akan dihapus: ";
            cin >> id;
            hapusMaterial(id);
            cout << "Material berhasil dihapus.\n";
            break;
        }
        case 5:
            cout << "Kembali ke menu utama...\n";
            return;
        default:
            cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 5);
}

void menuKontraktor()
{
    int pilihan;
    while (true)
    {
        cout << "\nMenu Kontraktor:\n";
        cout << "1. Tampilkan Daftar Kontraktor\n";
        cout << "2. Tambah Kontraktor\n";
        cout << "3. Hapus Kontraktor\n";
        cout << "4. Kembali ke Menu Utama\n";
        cout << "Pilihan Anda: ";
        cin >> pilihan;

        switch (pilihan)
        {
        case 1:
            tampilkanDaftarKontraktor();
            break;
        case 2:
            tambahKontraktor();
            break;
        case 3:
            hapusKontraktor();
            break;
        case 4:
            cout << "Kembali ke menu utama...\n";
            return;
        default:
            cout << "Pilihan tidak valid.\n";
        }
    };
}

void menuProyek()
{
    int pilihan;
    while (true)
    {
        cout << "\nMenu Proyek:\n";
        cout << "1. Tampilkan Daftar Proyek\n";
        cout << "2. Tambah Proyek\n";
        cout << "3. Update Proyek\n";
        cout << "4. Hapus Proyek\n";
        cout << "5. Kembali ke Menu Utama\n";
        cout << "Pilihan Anda: ";
        cin >> pilihan;

        switch (pilihan)
        {
        case 1:
            tampilkanDaftarProyek();
            break;
        case 2:
            tambahProyek();
            break;
        case 3:
            updateProyek();
            break;
        case 4:
            hapusProyek();
            break;
        case 5:
            cout << "Kembali ke menu utama...\n";
            return;
        default:
            cout << "Pilihan tidak valid.\n";
        }
    };
}

void menuUtama()
{
    int pilihan;
    while (true)
    {
        cout << "\nMenu Utama:\n";
        cout << "1. Manajemen Kontraktor\n";
        cout << "2. Manajemen Material\n";
        cout << "3. Manajemen Proyek\n";
        cout << "4. Anggaran Proyek\n";
        cout << "5. Keluar\n";
        cout << "Pilihan Anda: ";
        cin >> pilihan;

        switch (pilihan)
        {
        case 1:
            menuKontraktor();
            break;
        case 2:
            menuMaterial();
            break;
        case 3:
            menuProyek();
            break;
        case 4:
            tampilkanAnggaran();
            break;
        case 5:
            cout << "Terima kasih telah menggunakan program ini.\n";
            exit(0);
        default:
            cout << "Pilihan tidak valid.\n";
        }
    };
}

void Datakontraktor()
{
    enqueue(1, "Yusman");
    enqueue(2, "Reza");
    enqueue(3, "Salim");
    enqueue(4, "Saputra");
    enqueue(5, "Yoseph");
}

void Dataproyek()
{
    daftarProyek.push({5, "Jalur MRT Surabaya", "Berlangsung"});
    daftarProyek.push({4, "Jembatan Penajam-Balikpapan", "Berlangsung"});
    daftarProyek.push({3, "Jalan Poros Berau-Bontang", "Selesai"});
    daftarProyek.push({2, "Tol IKN", "Menunggu"});
    daftarProyek.push({1, "Tol Balikpapan-Samarinda", "Selesai"});
}

void Datamaterial()
{
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
}

int main()
{
    Datakontraktor();
    Dataproyek();
    Datamaterial();
    system("cls");

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