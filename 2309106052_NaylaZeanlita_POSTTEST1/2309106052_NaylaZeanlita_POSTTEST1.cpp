#include <iostream>
#include <iomanip>
using namespace std;

// Array untuk menampung segitiga pascal
int RumusPascal(int baris, int kolom)
{
    if (kolom == 0)
    {
        return 1;
    }
    if (kolom == baris)
    {
        return 1;
    }
    return RumusPascal(baris - 1, kolom - 1) + RumusPascal(baris - 1, kolom);
}

void SegitigaPascal(int segitiga)
{
    // Menampilkan segitiga pascal
    for (int i = 0; i < segitiga; i++)
    {
        cout << setw(segitiga - i) << "";
        for (int j = 0; j <= i; j++)
        {
            cout << RumusPascal(i, j) << " ";
        }
        cout << endl;
    }
}

int main()
{
    int segitiga;
    while (true)
    {
        cout << "Berapa baris segitiga pascal yang ingin ditampilkan: ";
        cin >> segitiga;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            cout << "Input salah" << endl;
        }
        if (segitiga < 0)
        {
            cout << "Input harus berupa bilangan bulat positif" << endl;
        }
        else
        {
            SegitigaPascal(segitiga);
            break;
        }
    }
}