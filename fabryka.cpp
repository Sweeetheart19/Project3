#include <iostream>
#include <string>
using namespace std;

class Fabryka {
private:
    BST<Urzadzenie> bstUrzadzenie;

public:
    // Metoda do dodawania urz¹dzenia do fabryki
    void dodajUrzadzenie(const Urzadzenie& urzadzenie) {
        bstUrzadzenie.insert(urzadzenie);
        cout << "Urzadzenie " << urzadzenie << " dodane do fabryki.\n";
    }

    // Metoda do usuwania urz¹dzenia z fabryki
    void usunUrzadzenie(const Urzadzenie& urzadzenie) {
        if (bstUrzadzenie.search(urzadzenie) != nullptr) {
            bstUrzadzenie.remove(urzadzenie);
            cout << "Urzadzenie " << urzadzenie << " usuniete z fabryki.\n";
        }
        else {
            cout << "Urzadzenie " << urzadzenie << " nie znajduje sie w fabryce.\n";
        }
    }

    // Metoda do wyszukiwania urz¹dzenia w fabryce
    void szukajUrzadzenie(const Urzadzenie& urzadzenie) {
        if (bstUrzadzenie.search(urzadzenie) != nullptr) {
            cout << "Urzadzenie " << urzadzenie << " znajduje sie w fabryce.\n";
        }
        else {
            cout << "Urzadzenie " << urzadzenie << " nie znajduje sie w fabryce.\n";
        }
    }

    // Metoda do wyswietlania wszystkich urz¹dzeñ w fabryce
    void wyswietlWszystkieUrzadzenia() {
        cout << "Urzadzenia w fabryce:\n";
        bstUrzadzenie.inorder();
    }

    // Zapisuje obiekty z drzewa do pliku
    void zapiszDoPliku(const std::string& nazwaPliku) {
        try {
            bstUrzadzenie.zapiszDoPliku(nazwaPliku);
        }
        catch (const std::exception& e) {
            cerr << e.what() << endl;
        }
    }

    // Odczytuje obiekty z pliku i wstawia je do drzewa
    void odczytajZPliku(const std::string& nazwaPliku) {
        try {
            bstUrzadzenie.odczytajZPliku(nazwaPliku);
        }
        catch (const std::exception& e) {
            cerr << e.what() << endl;
        }
    }

    // Metoda do sprawdzania, czy obiekt znajduje siê w fabryce
    bool contains(const Urzadzenie& urzadzenie) {
        return bstUrzadzenie.contains(urzadzenie);
    }

    // Metoda do rotacji w prawo
    void rotacjaWPrawo() {
        if (bstUrzadzenie.root != nullptr) {
            bstUrzadzenie.root = bstUrzadzenie.rotateRight(bstUrzadzenie.root);
        }
    }

};

// Funkcja pomocnicza do wyœwietlania menu
void wyswietlMenu() {
    cout << "Menu:\n";
    cout << "1. Dodaj urzadzenie\n";
    cout << "2. Usun urzadzenie\n";
    cout << "3. Wyszukaj urzadzenie\n";
    cout << "4. Wyswietl wszystkie urzadzenia\n";
    cout << "5. Zapisz urzadzenia do pliku\n";
    cout << "6. Odczytaj urzadzenia z pliku\n";
    cout << "7. Sprawdz, czy obiekt znajduje sie w fabryce\n";
    cout << "8. Rotacja w prawo\n";
    cout << "0. Wyjdz\n";
    cout << "Wybierz opcje: ";
}