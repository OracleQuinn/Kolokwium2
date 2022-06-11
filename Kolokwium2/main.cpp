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

//ZADANIE 2:
/*
Zaimplementowaæ funkcjê funkcjê int fif(char* pl, char* slowo, char* &wsk), która
przyjmuje jako parametry dwa ³añcuchy znaków ( pl oraz slowo) i wskaŸnik (wsk). W funkcji powinno
nast¹piæ odczytanie pliku (jego nazwa przekazana jest przez parametr pl) oraz znalezienie pozycji s³owa
(parametr slowo) w tym pliku. Jeœli s³owo nie zosta³o znalezione, to nale¿y zwróciæ wartoœæ -1. Ponadto przez
parametr wsk nale¿y zwróciæ wskaŸnik na najd³u¿sze s³owo, jakie wystêpuje w pliku. Nie ma to byæ wskaŸnik do
pliku, ale do zmiennej – nowej zmiennej stworzonej dynamicznie w funkcji.
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
            //liczê od 0
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