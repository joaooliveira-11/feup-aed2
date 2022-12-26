#ifndef AED_2_HASHTABLE_H
#define AED_2_HASHTABLE_H

#include <vector>
using namespace std;

template <class T>
class HashTable {
private:
    enum EntryType { ACTIVE, EMPTY, DELETED };

    struct HashEntry {
        T element;
        EntryType info;
        HashEntry(const T& e = T(), EntryType i = EMPTY) : element(e), info(i) {}
    };

    vector<HashEntry> array;
    int currentSize;
    const T ITEM_NOT_FOUND;
    bool isActive(int currentPos) const;
    int findPos(const T& x) const;
    const T& find(const T& x) const;
    void insert(const T& x);
    void remove(const T& x);
    int hash(const T& x, int tableSize);
    void rehash();
    void makeEmpty();

public:
    explicit HashTable(int size = 10000) : array(size), currentSize(0) {}
};


#endif //AED_2_HASHTABLE_H
