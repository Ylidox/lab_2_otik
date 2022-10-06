#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <bitset>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

bool chek_file(string fileName) {
    ifstream file(fileName);
    if (!file) return false;
    file.close();
    return true;
}
vector<unsigned char> read(string fileName) {

    if (!chek_file(fileName)) cout << "FileName Error!" << endl;

    vector<unsigned char> buff;

    ifstream file(fileName);

    char b;
    while (file.get(b)) {
        buff.push_back((unsigned char)b);
    }

    file.close();

    return buff;
}

template<typename K, typename T>
class Table {
private:
    vector<K> keys;
    vector<T> values;

    int place(K key) {
        size_t i = 0;
        for (; i < keys.size(); i++) {
            if (keys[i] == key) return (int)i;
        }
        return -1;
    }

public:
    Table() {}
    vector<K>& get_keys() { return this->keys; };
    vector<T>& get_values() { return this->values; };

    T get(K name) {
        int index = place(name);
        if (index == -1) return -1;
        return values[index];
    }

    void set(K key, T value) {
        int index = place(key);
        if (index == -1) {
            keys.push_back(key);
            values.push_back(value);
        }
        else {
            values[index] = value;
        }
    }

    void set(K key, T value, int index) {
        if (index == -1) {
            keys.push_back(key);
            values.push_back(value);
        }
        else {
            values[index] = value;
        }
    }

    void change(K key, T value) {
        int index = place(key);
        if (index == -1) {
            set(key, value, index);
            return;
        }
        values[index] += value;
    }

    void print() {
        for (size_t i = 0; i < keys.size(); i++) {
            cout << "'" << keys[i] << "' " << (char)keys[i]<< " : " << values[i] << endl;
        }
    }

    ~Table() {
        keys.clear();
        values.clear();
    }
};

void sort(Table<unsigned int, int>& table){
    int size = table.get_keys().size();

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - 1; j++) {
            if (table.get_values()[j] < table.get_values()[j + 1]) {
                int v = table.get_values()[j];
                table.get_values()[j] = table.get_values()[j + 1];
                table.get_values()[j + 1] = v;

                unsigned int k = table.get_keys()[j];
                table.get_keys()[j] = table.get_keys()[j + 1];
                table.get_keys()[j + 1] = k;
            }
        }
    }
}

int main()
{
    vector<unsigned char> file = read("0.txt");
    Table<unsigned int, int> table;

    for (int i = 0; i < file.size(); i++) {
        table.change(file[i], 1);
    }
    sort(table);
    table.print();

    const int count = 4;

    Table<unsigned int, int> symb;
    Table<unsigned int, int> ascii;

    symb.set(table.get_keys()[0], table.get_values()[0]);
    symb.set(table.get_keys()[1], table.get_values()[1]);
    symb.set(table.get_keys()[2], table.get_values()[2]);
    symb.set(table.get_keys()[3], table.get_values()[3]);

    int index = 0;
    for (int i = 0; i < table.get_keys().size(); i++) {
        if (table.get_keys()[i] < 32 || table.get_keys()[i] > 126) {
            ascii.set(table.get_keys()[i], table.get_values()[i]);
            index++;
        }
        if (index == count) break;
    }

    cout << "*******" << endl;
    symb.print();
    cout << "*******" << endl;
    ascii.print();

}