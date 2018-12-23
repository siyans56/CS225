/**
 * @file main.cpp
 * This file contains code for output testing of the
 *  BinaryTree class.
 * @author Daniel Hoodin, modified by Jack Toole for colored output
 * @date March 2009
 */

#include <algorithm>
#include <iostream>
#include "util.h"
#include "binarytree.h"
#include "abstractsyntaxtree.h"
#include "coloredout.h"
#include "random.h"
#include "TreeTraversals/PreorderTraversal.h"
#include "TreeTraversals/InorderTraversal.h"

using namespace std;
using namespace util;

template <typename T>
void printTreeInfo(const BinaryTree<T>& tree, const string& name,
                   const string& description);

void printASTInfo(const AbstractSyntaxTree& tree, const string& name,
                   const string& description);

int main(int argc, char** argv)
{
    // Color the output
    bool is_colored
        = (argc > 1 && tolower(argv[1][0]) == 'c') && isatty(STDOUT_FILENO);
    colored_out coloroutput;
    if (is_colored) {
        coloroutput.set_expected_file("soln_treefun.out");
        int status = coloroutput.start();
        if (status < 0)
            return 0;
    }

    // Seed the random generator
    // This can be your favorite number; it's just to set up a
    // pseudorandom sequence that will be predictable
    usrand(86);

    // Make a random unsorted tree with nodes for 1 through 10
    BinaryTree<int> myTree;
    for (int i = 1; i <= 10; i++)
        myTree.insert(i);

    // Print the tree
    printTreeInfo(myTree, "Tree", "random unordered tree");

    // Mirror the tree
    myTree.mirror();
    printTreeInfo(myTree, "Mirrored", "the mirror image of the above tree");

    // Make a sorted tree
    // First, create a random ordering to insert 1..10 into the tree
    vector<int> ordering;
    ordering.reserve(10);
    for (int num = 1; num <= 10; num++)
        ordering.push_back(num);
    usrand(15);
    random_shuffle<vector<int>::iterator>(ordering.begin(), ordering.end(),
                                          urandn);

    // Then create a tree and insert 1..10 shuffled
    BinaryTree<int> myBST;
    for (int index = 0; index < 10; index++)
        myBST.insert(ordering[index], true);

    // Print the tree
    printTreeInfo(myBST, "BST", "random ordered tree");

    // Mirror the tree
    myBST.mirror();
    printTreeInfo(myBST, "BST Mirrored", "the mirror image of the above BST");

    // Make an almost sorted tree
    usrand(128);
    for (int num = 1; num <= 10; num++)
        ordering[num - 1] = num;
    random_shuffle<vector<int>::iterator>(ordering.begin(), ordering.end(),
                                          urandn);

    // Then create a tree and insert 1..10 shuffled
    myBST.clear();
    for (int index = 0; index < 4; index++)
        myBST.insert(ordering[index], true);
    myBST.insert(ordering[4], false);

    printTreeInfo(myBST, "Almost BST",
                  "a tree that has one element out of place");

    std::string compute_string = "(12 + ((6 * 23) - 57) / 2)";
    typename BinaryTree<std::string>::Node* root;
    pemdasToAST(compute_string, root);
    AbstractSyntaxTree basicAST(root);

    printASTInfo(basicAST, compute_string, "AST For Computing The Equation");

    basicAST.mirror();
    printASTInfo(basicAST, "Mirror of " + compute_string, "AST For Computing The Mirror of The Equation");
	
    return 0;
}

void output_header(string name, string desc)
{
    const string bar(79, '~');
    cout << bar << endl;
    colored_out::output_bold(name);
    cout << " - " << desc << endl;
    cout << bar << endl;
}

template <typename T>
void printTreeInfo(const BinaryTree<T>& tree, const string& name,
                   const string& description)
{
      output_header(name, description);
    cout << "height: " << tree.height() << endl;
    cout << "ordered iteratively: " << boolalpha << tree.isOrderedIterative() << endl;
    cout << "ordered recursively: " << boolalpha << tree.isOrderedRecursive() << endl;
    cout << "sumDistances: " << tree.sumDistances() << endl;
    tree.print();
    cout << endl;
    cout << "printLeftRight: ";
    tree.printLeftToRight();
    vector<vector<T> > v;
    tree.getPaths(v);
    for(size_t i=0; i<v.size(); i++){
      cout<<"path: ";
      for(size_t j=0; j<v[i].size(); j++){
        cout<<v[i][j]<<" ";
      }
      cout<<endl;
    }

	cout<<endl;
	
	cout << "preorder: ";
	PreorderTraversal<int> pot(tree.getRoot());
	for (TreeTraversal<int>::Iterator it = pot.begin(); it != pot.end(); ++it) {
		cout<<(*it)->elem<<" ";
	}
	cout<<endl;

	cout << "inorder: ";
	InorderTraversal<int> iot(tree.getRoot());
	for (TreeTraversal<int>::Iterator it = iot.begin(); it != iot.end(); ++it) {
		cout<<(*it)->elem<<" ";
	}


    cout << endl<< endl;
}

void printASTInfo(const AbstractSyntaxTree& tree, const string& name,
                   const string& description)
{
      output_header(name, description);
    cout << "height: " << tree.height() << endl;
    cout << "calculated value: " << tree.eval() << endl;
    tree.print();
    cout << endl;
    cout << "printLeftRight: ";
    tree.printLeftToRight();
    vector<vector<std::string> > v;
    tree.getPaths(v);
    for(size_t i=0; i<v.size(); i++){
      cout<<"path: ";
      for(size_t j=0; j<v[i].size(); j++){
        cout<<v[i][j]<<" ";
      }
      cout<<endl;
    }

	cout<<endl;
	
	cout << "preorder: ";
	PreorderTraversal<std::string> pot(tree.getRoot());
	for (TreeTraversal<std::string>::Iterator it = pot.begin(); it != pot.end(); ++it) {
		cout<<(*it)->elem<<" ";
	}
	cout<<endl;

	cout << "inorder: ";
	InorderTraversal<std::string> iot(tree.getRoot());
	for (TreeTraversal<std::string>::Iterator it = iot.begin(); it != iot.end(); ++it) {
		cout<<(*it)->elem<<" ";
	}


    cout << endl<< endl;
}
