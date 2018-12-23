/**
 * @file dhhashtable.cpp
 * Implementation of the DHHashTable class.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Summer 2012
 */
#include "dhhashtable.h"

using hashes::hash;
using hashes::secondary_hash;
using std::pair;


template <class K, class V>
DHHashTable<K, V>::DHHashTable(size_t tsize)
{
    if (tsize <= 0)
        tsize = 17;
    size = findPrime(tsize);
    table = new pair<K, V>*[size];
    should_probe = new bool[size];
    for (size_t i = 0; i < size; i++) {
        table[i] = NULL;
        should_probe[i] = false;
    }
    elems = 0;
}

template <class K, class V>
DHHashTable<K, V>::~DHHashTable()
{
    destroy();
}

template <class K, class V>
DHHashTable<K, V> const& DHHashTable<K, V>::operator=(DHHashTable const& rhs)
{
    if (this != &rhs) {
        destroy();

        copy(rhs);
    }
    return *this;
}

template <class K, class V>
DHHashTable<K, V>::DHHashTable(DHHashTable<K, V> const& other)
{
    copy(other);
}


template <class K, class V>
void DHHashTable<K, V>::destroy()
{
    for (size_t i = 0; i < size; i++)
        delete table[i];
    delete[] table; table = nullptr;
    delete[] should_probe; should_probe = nullptr;
}

template <class K, class V>
void DHHashTable<K, V>::copy(const DHHashTable<K, V>& other)
{
    table = new pair<K, V>*[other.size];
    should_probe = new bool[other.size];
    for (size_t i = 0; i < other.size; i++) {
        should_probe[i] = other.should_probe[i];
        if (other.table[i] == NULL)
            table[i] = NULL;
        else
            table[i] = new pair<K, V>(*(other.table[i]));
    }
    size = other.size;
    elems = other.elems;
}

template <class K, class V>
void DHHashTable<K, V>::insert(K const& key, V const& value)
{

    /**
     * @todo Implement this function.
     *
     * @note Remember to resize the table when necessary (load factor >=
     *  0.7). **Do this check *after* increasing elems!!** Also, don't
     *  forget to mark the cell for probing with should_probe!
     */
     elems++;
     if (shouldResize()) resizeTable();
     size_t index = hash(key, size);
     if (table[index] == NULL && should_probe[index] == false) {
       table[index] = new pair<K,V>(key, value);
       should_probe[index] = true;
     }
     else {
       size_t index2 = secondary_hash(key, size);
       while (table[index] != NULL && should_probe[index] != false) {
         index = (index + index2) % size;
       }
     table[index] = new pair<K,V>(key, value);
     should_probe[index] = true;
   }
}

template <class K, class V>
void DHHashTable<K, V>::remove(K const& key)
{
    /**
     * @todo Implement this function
     */
     int index = findIndex(key);
     if (index == -1) return;
     else {
       delete table[index];
       table[index] = NULL;
       elems--;
       should_probe[index] = false;
     }
}

template <class K, class V>
int DHHashTable<K, V>::findIndex(const K& key) const
{
    /**
     * @todo Implement this function
     */
  /*  size_t index = hash(key, size);
    size_t curr = index;
    if (table[index]->first == key && should_probe[index] == true) {
      return index;
    }
    else {
      size_t index2 = secondary_hash(key, size);
      while (should_probe[curr] == true) {
        if (table[curr] != NULL && table[curr]->first == key) {
          return curr;
        }
        curr = (curr + index2) % size;
        if (curr == index) return -1;
      }
    }
    return -1;*/

    size_t index = hash(key, size);
    size_t index2 = secondary_hash(key, size);
    size_t curr = index;
    while (should_probe[curr] == true) {
        if (table[curr] != NULL && table[curr]->first == key)
            return curr;
        curr = (curr + index2) % size;
        // if we've looped all the way around, the key has not been found
        if (curr == index)
            return -1;
    }
    return -1;
}

template <class K, class V>
V DHHashTable<K, V>::find(K const& key) const
{
    int idx = findIndex(key);
    if (idx != -1)
        return table[idx]->second;
    return V();
}

template <class K, class V>
V& DHHashTable<K, V>::operator[](K const& key)
{
    // First, attempt to find the key and return its value by reference
    int idx = findIndex(key);
    if (idx == -1) {
        // otherwise, insert the default value and return it
        insert(key, V());
        idx = findIndex(key);
    }
    return table[idx]->second;
}

template <class K, class V>
bool DHHashTable<K, V>::keyExists(K const& key) const
{
    return findIndex(key) != -1;
}

template <class K, class V>
void DHHashTable<K, V>::clear()
{
    destroy();

    table = new pair<K, V>*[17];
    should_probe = new bool[17];
    for (size_t i = 0; i < 17; i++)
        should_probe[i] = false;
    size = 17;
    elems = 0;
}

template <class K, class V>
void DHHashTable<K, V>::resizeTable()
{
    size_t newSize = findPrime(size * 2);
    pair<K, V>** temp = new pair<K, V>*[newSize];
    delete[] should_probe;
    should_probe = new bool[newSize];
    for (size_t i = 0; i < newSize; i++) {
        temp[i] = NULL;
        should_probe[i] = false;
    }

    for (size_t slot = 0; slot < size; slot++) {
        if (table[slot] != NULL) {
            size_t h = hash(table[slot]->first, newSize);
            size_t jump = secondary_hash(table[slot]->first, newSize);
            size_t i = 0;
            size_t idx = h;
            while (temp[idx] != NULL)
            {
                ++i;
                idx = (h + jump*i) % newSize;
            }
            temp[idx] = table[slot];
            should_probe[idx] = true;
        }
    }

    delete[] table;
    // don't delete elements since we just moved their pointers around
    table = temp;
    size = newSize;
}
