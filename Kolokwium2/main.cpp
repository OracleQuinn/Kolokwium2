#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

int length(const char lan[]) {
    int i = 0;
    for (; lan[i] != '\0'; i++);
    return i;
}

//ZADANIE 1:
/*
Zaimplementowaæ funkcjê double przepisz(char* nPlWe, int wiek), która jako parametr
otrzymuje nazwê pliku wejœciowego, którego postaæ wygl¹da nastêpuj¹co:
imiê1 nazwisko1 plec1 wiek1 pensja1
imiê2 nazwisko2 plec2 wiek2 pensja2
...

Przy czym imiê zawsze zapisane jest w postaci jednego s³owa (nie zawiera bia³ych znaków), podobnie nazwisko.
Zawsze podana jest równie¿ dok³adnie p³eæ (char - 'K' lub 'M'), wiek i pensja, a liczba osób jest nieokreœlona.
Powy¿sze dane mo¿na po prostu za³o¿yæ – nie ma koniecznoœci ich weryfikacji.
W rezultacie dzia³ania funkcji powinny powstaæ dwa pliki wyjœciowe, gdzie jeden bêdzie zawiera³ jedynie
kobiety (nazwa taka sama, jak pliku w przypadku wejœciowego zakoñczona, liter¹ 'k'), a drugi mê¿czyzn
(zakoñczony liter¹ 'm').
Jednoczeœnie do nowych plików nale¿y:
• nie przepisywaæ oznaczenia p³ci,
• kobietom o wieku wiêkszym ni¿ podany jako drugi parametr (wiek) podnieœæ pensjê o 5%, a mniejszym
lub równym zmniejszyæ o 3% (zapisaæ do 2 miejsca po przecinku),
• mê¿czyznom podnieœæ pensjê o tyle procent, ile maj¹ lat podzielonych przez 10 (zapisaæ do 2 miejsca po
przecinku).
Funkcja zwraca œredni wiek wszystkich mê¿czyzn z pliku wejœciowego.
*/
double przepisz(const char* nPlWe, int wiek) {
    int size = length(nPlWe);
    int counterOfMan = 0;
    int sumOfAge = 0;

    ifstream file;
    file.open(nPlWe);

    string fileOutWoman(nPlWe);
    fileOutWoman.insert(size - 4, "k");
    ofstream fileOutW;
    fileOutW.open(fileOutWoman);

    string fileOutMan(nPlWe);
    fileOutMan.insert(size - 4, "m");
    ofstream fileOutM;
    fileOutM.open(fileOutMan);

    char firstName[256];
    char lastName[256];
    char gender;
    int age;
    float salary;
    while (file >> firstName >> lastName >> gender >> age >> salary) {
        if (gender == 'K') {
            if (age > wiek) {
                fileOutW << firstName << ' ' << lastName << ' ' << age << ' ' << salary * 1.05 << endl;
            }
            else
            {
                fileOutW << firstName << ' ' << lastName << ' ' << age << ' ' << salary * 0.97 << endl;
            }
        }
        else
        {
            counterOfMan++;
            fileOutM << firstName << ' ' << lastName << ' ' << age << ' ' << salary * (1.0 + age / 10) << endl;
            sumOfAge += age;
        }
    }
    file.close();
    fileOutW.close();
    fileOutM.close();

    double result = (double)sumOfAge / counterOfMan;

    return result;
}

int main() {
    double result = przepisz("test.txt", 30);

    cout << result << endl;
}