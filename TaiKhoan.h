#ifndef QUANLY_TAIKHOAN_H
#define QUANLY_TAIKHOAN_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class TaiKhoan {
private:
    string soTK;
    string matKhau;
    string ten;

public:
    TaiKhoan() : soTK(""), matKhau(""), ten("") {}
    TaiKhoan(string s, string m, string t) : soTK(s), matKhau(m), ten(t) {}

    string getSoTK() const { return soTK; }
    string getMK() const { return matKhau; }
    string getTen() const { return ten; }

    friend ostream& operator<<(ostream& os, const TaiKhoan& tk) {
        os << tk.soTK << " " << tk.matKhau << " " << tk.ten;
        return os;
    }
};

template <typename T>
struct Node {
    T tk;
    Node* next;
    Node(const T& t) : tk(t), next(nullptr) {}
};

template <typename T>
class HashTable {
private:
    static const int HASH_SIZE = 100;
    Node<T>* buckets[HASH_SIZE];

    unsigned int hash(const string& key) const {
        unsigned int h = 0;
        for (char c : key)
            h = (h * 31 + c) % HASH_SIZE;
        return h;
    }

public:
    HashTable() {
        for (int i = 0; i < HASH_SIZE; i++)
            buckets[i] = nullptr;
    }

    void insert(const T& tk) {
        unsigned int index = hash(tk.getSoTK());
        Node<T>* node = new Node<T>(tk);
        node->next = buckets[index];
        buckets[index] = node;
    }

    T* find(const string& soTK, const string& mk) {
        unsigned int index = hash(soTK);
        Node<T>* node = buckets[index];
        while (node) {
            if (node->tk.getSoTK() == soTK && node->tk.getMK() == mk)
                return &node->tk;
            node = node->next;
        }
        return nullptr;
    }

    void loadFromFile(const string& filename) {
        ifstream f(filename);
        if (!f.is_open()) return;

        string stk, mk, ten;
        while (f >> stk >> mk) {
            getline(f, ten);
            if (!ten.empty() && ten[0] == ' ') ten.erase(0, 1);
            insert(T(stk, mk, ten));
        }
        f.close();
    }

    void saveToFile(const string& filename) {
        ofstream f(filename);
        if (!f.is_open()) return;

        for (int i = 0; i < HASH_SIZE; ++i) {
            Node<T>* node = buckets[i];
            while (node) {
                f << node->tk << "\n";
                node = node->next;
            }
        }
        f.close();
    }
};

#endif
