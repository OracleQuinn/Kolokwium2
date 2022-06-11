#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <iomanip> 

using namespace std;

int length(const char lan[]) {
    int i = 0;
    for (; lan[i] != '\0'; i++);
    return i;
}

//ZADANIE 1:
/*
Zaimplementowa� funkcj� double przepisz(char* nPlWe, int wiek), kt�ra jako parametr
otrzymuje nazw� pliku wej�ciowego, kt�rego posta� wygl�da nast�puj�co:
imi�1 nazwisko1 plec1 wiek1 pensja1
imi�2 nazwisko2 plec2 wiek2 pensja2
...

Przy czym imi� zawsze zapisane jest w postaci jednego s�owa (nie zawiera bia�ych znak�w), podobnie nazwisko.
Zawsze podana jest r�wnie� dok�adnie p�e� (char - 'K' lub 'M'), wiek i pensja, a liczba os�b jest nieokre�lona.
Powy�sze dane mo�na po prostu za�o�y� � nie ma konieczno�ci ich weryfikacji.
W rezultacie dzia�ania funkcji powinny powsta� dwa pliki wyj�ciowe, gdzie jeden b�dzie zawiera� jedynie
kobiety (nazwa taka sama, jak pliku w przypadku wej�ciowego zako�czona, liter� 'k'), a drugi m�czyzn
(zako�czony liter� 'm').
Jednocze�nie do nowych plik�w nale�y:
� nie przepisywa� oznaczenia p�ci,
� kobietom o wieku wi�kszym ni� podany jako drugi parametr (wiek) podnie�� pensj� o 5%, a mniejszym
lub r�wnym zmniejszy� o 3% (zapisa� do 2 miejsca po przecinku),
� m�czyznom podnie�� pensj� o tyle procent, ile maj� lat podzielonych przez 10 (zapisa� do 2 miejsca po
przecinku).
Funkcja zwraca �redni wiek wszystkich m�czyzn z pliku wej�ciowego.
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

//ZADANIE 2:
/*
Zaimplementowa� funkcj� funkcj� int fif(char* pl, char* slowo, char* &wsk), kt�ra
przyjmuje jako parametry dwa �a�cuchy znak�w ( pl oraz slowo) i wska�nik (wsk). W funkcji powinno
nast�pi� odczytanie pliku (jego nazwa przekazana jest przez parametr pl) oraz znalezienie pozycji s�owa
(parametr slowo) w tym pliku. Je�li s�owo nie zosta�o znalezione, to nale�y zwr�ci� warto�� -1. Ponadto przez
parametr wsk nale�y zwr�ci� wska�nik na najd�u�sze s�owo, jakie wyst�puje w pliku. Nie ma to by� wska�nik do
pliku, ale do zmiennej � nowej zmiennej stworzonej dynamicznie w funkcji.
*/

int fif(const char* pl, const char* slowo, char*& wsk) {
    int result = -1;

    ifstream file;
    file.open(pl);

    string word;
    int lengthOfWord = 0;

    char* wskWord = new char;

    while (file >> word) {
        if (word == slowo) {
            //licz� od 0
            int position = file.tellg();
            cout << "Slowo znajduje sie na pozycji: " << position + 1 << endl;
            result = 0;
        }
        if (word.length() > lengthOfWord) {
            *wskWord = (char)word.c_str();
            wsk = wskWord;
        }
    }

    file.close();

    return result;
}

int main() {
    cout << "*** ZADANIE 1: ***" << endl;
    cout << setprecision(4);
    double result = przepisz("test.txt", 30);

    cout << result << endl;

    cout << "*** ZADANIE 2: ***" << endl;
    char* wsk = new char;
    int result2 = fif("test.txt", "Polak", wsk);
    cout << result2 << endl;
    cout << "Adres wskaznika po przekazaniu do funkcji: " << *wsk << endl;
}