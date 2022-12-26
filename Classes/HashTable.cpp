#include "HashTable.h"
#include <string>

using namespace std;

template <class T>
bool HashTable<T>::isActive(int currentPos) const {
    return array[currentPos].info == ACTIVE;
}

template <class T>
void HashTable<T>::makeEmpty() {
    currentSize = 0;
    for (int i = 0; i < array.size(); i++) {
        array[i].info = EMPTY;
    }
}

template <class T>
void HashTable<T>::insert(const T& x){
    int currentPos = findPos(x);
    if ( isActive(currentPos) ) return;
    array[currentPos] = HashEntry(x, ACTIVE);
    if ( ++currentSize > array.size()/2 ) rehash();
}

template <class T>
void HashTable<T>::remove(const T& x){
    int currentPos = findPos(x);
    if ( isActive(currentPos) )
        array[currentPos].info = DELETED; // do not "eliminate" element from table
}

template <class T>
int HashTable<T>::findPos(const T& x) const {
    int collisionNum = 0;
    int currentPos = hash(x, array.size());
    while (array[currentPos].info != EMPTY && array[currentPos].element != x) {
        currentPos += 2 * ++collisionNum - 1;
        if (currentPos >= array.size()) {
            currentPos -= array.size();
        }
    }
    return currentPos;
}

template <class T>
const T& HashTable<T>::find(const T& x) const{
    int currentPos = findPos(x);
    if ( isActive(currentPos) )
        return array[currentPos].element;
    else return ITEM_NOT_FOUND;
}

template <class T>
int HashTable<T>::hash(const T& x, int tableSize) {
    std::size_t h = 0;
    h = 37 * h + std::hash<T>()(x);
    h %= tableSize;
    if (h < 0) {
        h += tableSize;
    }
    return h;
}

template <class T>
void HashTable<T>::rehash(){

    vector<HashEntry> oldArray = array;
    array.resize(nextPrime(2 * oldArray.size()));
    for( int j = 0; j < array.size(); j++ ) {
        array[j].info = EMPTY;
    }
    currentSize = 0;
    for( int i = 0; i < oldArray.size(); i++ ) {
        if (oldArray[i].info == ACTIVE) insert(oldArray[i].element);
    }
}

template <class T>
bool HashTable<T>::EqualFunc(const T& x, const T& y){
    return x == y;
}


