#include <iostream>
#include <string>
#include <fstream>
#include "urzadzenie.cpp"
#include "fabryka.cpp"

using namespace std;

// Definicja struktury węzła z szablonem
template <typename T>
struct Node {
    T key;
    Node* left;
    Node* right;

    Node(T item) : key(item), left(nullptr), right(nullptr) {}
};

// Definicja szablonowego BST
template <typename T>
class BST {
private:
    Node<T>* root;

    Node<T>* insert(Node<T>* node, T key) {
        if (node == nullptr) return new Node<T>(key);

        if (key < node->key)
            node->left = insert(node->left, key);
        else if (key > node->key)
            node->right = insert(node->right, key);

        return node;
    }

    void inorder(Node<T>* root) {
        if (root != nullptr) {
            inorder(root->left);
            cout << root->key << " ";
            inorder(root->right);
        }
    }

    Node<T>* search(Node<T>* root, T key) {
        if (root == nullptr || root->key == key)
            return root;

        if (root->key < key)
            return search(root->right, key);

        return search(root->left, key);
    }

    bool contains(Node<T>* node, T& t) {
        if (node == nullptr) return false;
        if (node->key == t) return true;
        if (t < node->key)
            return contains(node->left, t);
        else
            return contains(node->right, t);
    }

public:
    BST() : root(nullptr) {}

    void insert(T key) {
        root = insert(root, key);
    }

    void inorder() {
        inorder(root);
        cout << endl;
    }

    Node<T>* search(T key) {
        return search(root, key);
    }

    bool contains(T& t) {
        return contains(root, t);
    }

    void remove(T key) {
        root = remove(root, key);
    }

    // Zapisuje obiekty z drzewa do pliku
    void zapiszDoPliku(const std::string& nazwaPliku) {
        ofstream plik(nazwaPliku);
        if (!plik.is_open()) {
            throw std::runtime_error("Blad: Nie udalo sie otworzyc pliku do zapisu.");
        }

        zapiszDoStrumienia(plik, root);
        plik.close();
        if (plik.fail()) {
            throw std::runtime_error("Blad: Błąd podczas zapisu danych do pliku.");
        }

        cout << "Obiekty zostaly zapisane do pliku: " << nazwaPliku << endl;
    }

    // Odczytuje obiekty z pliku i wstawia je do drzewa
    void odczytajZPliku(const std::string& nazwaPliku) {
        ifstream plik(nazwaPliku);
        if (!plik.is_open()) {
            throw std::runtime_error("Blad: Nie udalo sie otworzyc pliku do odczytu.");
        }

        T obiekt;
        while (plik >> obiekt) {
            insert(obiekt);
        }

        if (plik.fail() && !plik.eof()) {
            throw std::runtime_error("Blad: Błąd podczas odczytu danych z pliku.");
        }

        plik.close();
        cout << "Obiekty zostaly odczytane z pliku: " << nazwaPliku << endl;
    }

    Node<T>* rotateRight(Node<T>* node) {
        if (node == nullptr || node->left == nullptr) return node;

        Node<T>* newRoot = node->left;
        node->left = newRoot->right;
        newRoot->right = node;

        return newRoot;
    }

private:
    Node<T>* remove(Node<T>* root, T key) {
        if (root == nullptr) return root;

        if (key < root->key)
            root->left = remove(root->left, key);
        else if (key > root->key)
            root->right = remove(root->right, key);
        else {
            if (root->left == nullptr) {
                Node<T>* temp = root->right;
                delete root;
                return temp;
            }
            else if (root->right == nullptr) {
                Node<T>* temp = root->left;
                delete root;
                return temp;
            }

            Node<T>* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = remove(root->right, temp->key);
        }
        return root;
    }

    Node<T>* minValueNode(Node<T>* node) {
        Node<T>* current = node;
        while (current && current->left != nullptr)
            current = current->left;
        return current;
    }

    // Pomocnicza funkcja rekurencyjna do zapisu do strumienia
    void zapiszDoStrumienia(std::ostream& strumien, Node<T>* wierzcholek) {
        if (wierzcholek != nullptr) {
            zapiszDoStrumienia(strumien, wierzcholek->left);
            strumien << wierzcholek->key << endl;
            zapiszDoStrumienia(strumien, wierzcholek->right);
        }
    }

};

// Funkcja pomocnicza do wyświetlania menu
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

// Funkcja główna
int main() {
    Fabryka fabryka;

    int wybor;
    do {
        wyswietlMenu();
        cin >> wybor;

        switch (wybor) {
        case 1: {
            string nazwa;
            int id;
            cout << "Podaj nazwe urzadzenia: ";
            cin >> nazwa;
            cout << "Podaj id urzadzenia: ";
            cin >> id;
            try {
                fabryka.dodajUrzadzenie(Urzadzenie(nazwa, id));
            }
            catch (const std::exception& e) {
                cerr << e.what() << endl;
            }
            break;
        }
        case 2: {
            string nazwa;
            int id;
            cout << "Podaj nazwe urzadzenia do usuniecia: ";
            cin >> nazwa;
            cout << "Podaj id urzadzenia do usuniecia: ";
            cin >> id;
            try {
                fabryka.usunUrzadzenie(Urzadzenie(nazwa, id));
            }
            catch (const std::exception& e) {
                cerr << e.what() << endl;
            }
            break;
        }
        case 3: {
            string nazwa;
            int id;
            cout << "Podaj nazwe urzadzenia do wyszukania: ";
            cin >> nazwa;
            cout << "Podaj id urzadzenia do wyszukania: ";
            cin >> id;
            try {
                fabryka.szukajUrzadzenie(Urzadzenie(nazwa, id));
            }
            catch (const std::exception& e) {
                cerr << e.what() << endl;
            }
            break;
        }
        case 4:
            fabryka.wyswietlWszystkieUrzadzenia();
            break;
        case 5: {
            string nazwaPliku;
            cout << "Podaj nazwe pliku do zapisu: ";
            cin >> nazwaPliku;
            try {
                fabryka.zapiszDoPliku(nazwaPliku);
            }
            catch (const std::exception& e) {
                cerr << e.what() << endl;
            }
            break;
        }
        case 6: {
            string nazwaPliku;
            cout << "Podaj nazwe pliku do odczytu: ";
            cin >> nazwaPliku;
            try {
                fabryka.odczytajZPliku(nazwaPliku);
            }
            catch (const std::exception& e) {
                cerr << e.what() << endl;
            }
            break;
        }
        case 7: {
            string nazwa;
            int id;
            cout << "Podaj nazwe urzadzenia do sprawdzenia: ";
            cin >> nazwa;
            cout << "Podaj id urzadzenia do sprawdzenia: ";
            cin >> id;
            if (fabryka.contains(Urzadzenie(nazwa, id))) {
                cout << "Urzadzenie znajduje sie w fabryce.\n";
            }
            else {
                cout << "Urzadzenie nie znajduje sie w fabryce.\n";
            }
            break;
        }
        case 8:
            fabryka.rotacjaWPrawo();
            cout << "Wykonano rotacje w prawo.\n";
            break;
        case 0:
            cout << "Koniec programu.\n";
            break;
        default:
            cout << "Niepoprawna opcja. Wybierz jeszcze raz.\n";
        }

    } while (wybor != 0);

    return 0;
}
