/**
 * @file lphashtable.cpp
 * Implementation of the LPHashTable class.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Summer 2012
 */
#include "lphashtable.h"

using hashes::hash;
using std::pair;

template <class K, class V>
LPHashTable<K, V>::LPHashTable(size_t tsize)
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
LPHashTable<K, V>::~LPHashTable()
{
    for (size_t i = 0; i < size; i++)
        delete table[i];
    delete[] table;
    delete[] should_probe;
}

template <class K, class V>
LPHashTable<K, V> const& LPHashTable<K, V>::operator=(LPHashTable const& rhs)
{
    if (this != &rhs) {
        for (size_t i = 0; i < size; i++)
            delete table[i];
        delete[] table;
        delete[] should_probe;

        table = new pair<K, V>*[rhs.size];
        should_probe = new bool[rhs.size];
        for (size_t i = 0; i < rhs.size; i++) {
            should_probe[i] = rhs.should_probe[i];
            if (rhs.table[i] == NULL)
                table[i] = NULL;
            else
                table[i] = new pair<K, V>(*(rhs.table[i]));
        }
        size = rhs.size;
        elems = rhs.elems;
    }
    return *this;
}

template <class K, class V>
LPHashTable<K, V>::LPHashTable(LPHashTable<K, V> const& other)
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
void LPHashTable<K, V>::insert(K const& key, V const& value)
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
     int index = hash(key, size);
     while (should_probe[index] == true) { //if occupied, move forward
       index = (index + 1) % size;
     }
     table[index] = new pair<K, V>(key, value);
     should_probe[index] = true;
}

template <class K, class V>
void LPHashTable<K, V>::remove(K const& key)
{
  /**
   * @todo: implement this function
   */
   /*
   int index = findIndex(key);
   if (index == -1) return;
   else {
     delete table[index];
     table[index] = nullptr;
     elems--;
   } */
   int index = findIndex(key);
   if (index == -1) return;
   else {
     delete table[index];
     table[index] = NULL;
     should_probe[index] = false;
     --elems;
   }
}

template <class K, class V>
int LPHashTable<K, V>::findIndex(const K& key) const
{
  /**
   * @todo Implement this function
   *
   * Be careful in determining when the key is not in the table!
   */
    size_t index = hash(key, size);
    size_t curr = index;
    while (should_probe[curr] == true) {
        if (table[curr] != NULL && table[curr]->first == key)
            return curr;
        curr = (curr + 1) % size;
        // if we've looped all the way around, the key has not been found
        if (curr == index)
            return -1;
    }
    return -1;
}

template <class K, class V>
V LPHashTable<K, V>::find(K const& key) const
{
    int idx = findIndex(key);
    if (idx != -1)
        return table[idx]->second;
    return V();
}

template <class K, class V>
V& LPHashTable<K, V>::operator[](K const& key)
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
bool LPHashTable<K, V>::keyExists(K const& key) const
{
    return findIndex(key) != -1;
}

template <class K, class V>
void LPHashTable<K, V>::clear()
{
    for (size_t i = 0; i < size; i++)
        delete table[i];
    delete[] table;
    delete[] should_probe;
    table = new pair<K, V>*[17];
    should_probe = new bool[17];
    for (size_t i = 0; i < 17; i++)
        should_probe[i] = false;
    size = 17;
    elems = 0;
}

template <class K, class V>
void LPHashTable<K, V>::resizeTable()
{
  /**
   * @todo Implement this function
   *
   * The size of the table should be the closest prime to size * 2.
   *
   * @hint Use findPrime()!
   */

   //1) create a new table: new size, set to blank
   //2) populate from old table (rehash every time)
   //3) delte old table, replace

   size_t newsize = findPrime(2*size);
   pair<K, V>** temp = new pair<K, V>*[newsize]; //temp is a pointer to an array of pair pointers
   delete[] should_probe; //clear old should_probe table
   should_probe = new bool[newsize]; //resize

   for (size_t i = 0; i < newsize; i++) { //set everything ot null and false (blank HashTable)
     should_probe[i] = false;
     temp[i] = NULL;
   }

   for (size_t i = 0; i < size; i++) {
     if (table[i] != NULL) { //if occupied in origina
       size_t index = hash(table[i]->first, newsize);
       while (temp[index] != NULL) { //find next empty index to place into new
         index = (index + 1) % newsize;
       }
      should_probe[index] =  true;
      temp[index] = table[i];
  }
}
    size = newsize;
    delete[] table; //remove/replace old table
    table = temp;
}
