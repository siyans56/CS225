#include <algorithm>
/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

 template <class K, class V>
 void AVLTree<K, V>::UpdateHeight(Node*& node) {
   int height = (heightOrNeg1(node->left) > heightOrNeg1(node->right)) ? heightOrNeg1(node->left) : heightOrNeg1(node->right);
   node->height = 1 + height;
 }

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    //make left node root
    //give old root->left the new roots right children
    //make new root right old root

    Node* temp = t;
    t->right = temp->right->left;
    t->left = temp;
    temp->height = 1 + max(heightOrNeg1(temp->left), heightOrNeg1(temp->right));
    t->height = 1 + max(heightOrNeg1(t->left), heightOrNeg1(t->right));
    t = temp;

    UpdateHeight(t);

}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);

    //UpdateHeight(t);

}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here

    Node* temp = t;
    t->left = temp->left->right;
    t->right = temp;
    temp->height = 1 + max(heightOrNeg1(temp->left), heightOrNeg1(temp->right));
    t->height = 1 + max(heightOrNeg1(t->left), heightOrNeg1(t->right));
    t = temp;

    UpdateHeight(t);


}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);

//    UpdateHeight(t);

}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    if (heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left) == 2) {
      //right imbalance, check next
      if (heightOrNeg1(subtree->right->right) - heightOrNeg1(subtree->right->left) == 1) {
        rotateLeft(subtree);
      }
      else { //NOTE: not sure if to do else or only for -1 case (ignore 0 case?)
        rotateRightLeft(subtree);
      }
    }
   if (heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left) == -2) {
     //left imbalance
     if (heightOrNeg1(subtree->right->right) - heightOrNeg1(subtree->right->left) == 1) {
       rotateRight(subtree);
     }
     else {
       rotateLeftRight(subtree);
     }
   }
   subtree->height = 1 + max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right));
}


template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
      if ( subtree == NULL ) { // Found a leaf, add node:
        subtree = new Node(key, value);
      } else if (key < subtree->key) { // Recurse into left child:
        insert(subtree->left, key, value);
      } else if ( key > subtree->key ) {
        insert(subtree->right, key, value);
      }
      rebalance(subtree);
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree->left, key);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            // no-child remove
            // your code here
            delete subtree;
            subtree = nullptr;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            // two-child remove
            // your code here
            Node * temp = subtree->left;
           if (temp->right == NULL) {
             swap(subtree, temp);
             remove(subtree->left, key);
           } else {
             while (temp->right->right != NULL) {
               temp = temp->right;
             }
             swap(subtree, temp->right);
             remove(temp->right, key);
           }
        } else {
            // one-child remove
            // your code here
            if (subtree->left == NULL) {
              Node * temp = subtree;
              subtree = temp->right;
              delete temp;
            } else if (subtree->right == NULL) {
              Node * temp = subtree;
              subtree = temp->left;
              delete temp;
            }
        }
        // your code here
    }
    rebalance(subtree); /*
    remove(subtree->left, key);
} else if (key > subtree->key) {
    // your code here
    remove(subtree->right, key);
} else {
    if (subtree->left == NULL && subtree->right == NULL) {
        // your code here
        delete subtree;
        subtree = NULL;
    } else if (subtree->left != NULL && subtree->right != NULL) {
        // your code here
        Node * temp = subtree->left;
        if (temp->right == NULL) {
          swap(subtree, temp);
          remove(subtree->left, key);
        } else {
          while (temp->right->right != NULL) {
            temp = temp->right;
          }
          swap(subtree, temp->right);
          remove(temp->right, key);
        }

    } else {
        // your code here
        if (subtree->left == NULL) {
          Node * temp = subtree;
          subtree = temp->right;
          delete temp;
        } else if (subtree->right == NULL) {
          Node * temp = subtree;
          subtree = temp->left;
          delete temp;
        }
    }
    // your code here
}
rebalance(subtree); */
}
