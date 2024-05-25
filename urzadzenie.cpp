#include <iostream>
#include <string>
using namespace std;

class Urzadzenie {
public:
    string nazwa;
    int id;

    Urzadzenie(string nazwa, int id) : nazwa(nazwa), id(id) {}

    bool operator<(const Urzadzenie& other) const {
        return id < other.id;
    }

    bool operator>(const Urzadzenie& other) const {
        return id > other.id;
    }

    bool operator==(const Urzadzenie& other) const {
        return id == other.id;
    }

    friend ostream& operator<<(ostream& os, const Urzadzenie& urzadzenie) {
        os << "(Nazwa: " << urzadzenie.nazwa << ", ID: " << urzadzenie.id << ")";
        return os;
    }
};
