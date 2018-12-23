/**
 * Created: FA17
 *      Lab_trees
 *
 * Modified:
 *      By:
 */
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "catchlib.h"

#include <unistd.h>
#include <iostream>
#include <algorithm>
#include <ctype.h>
#include <vector>
#include <string>
#include <utility>
#include "../util.h"
#include "../binarytree.h"
#include "../abstractsyntaxtree.h"


using namespace std;
using namespace util;

typename BinaryTree<int>::Node* genNonIsOrderedTree()
{
  typename BinaryTree<int>::Node* bottomLeft = new typename BinaryTree<int>::Node(8);
  bottomLeft->left = new typename BinaryTree<int>::Node(2);
  typename BinaryTree<int>::Node* five_node = new typename BinaryTree<int>::Node(5);
  five_node->left = bottomLeft;
  typename BinaryTree<int>::Node* zero_node = new typename BinaryTree<int>::Node(0);
  zero_node->left = five_node;
  zero_node->right = new typename BinaryTree<int>::Node(3);
  zero_node->right->right = new typename BinaryTree<int>::Node(4);
  typename BinaryTree<int>::Node* seven_node = new typename BinaryTree<int>::Node(7);
  seven_node->left = new typename BinaryTree<int>::Node(1);
  seven_node->right = new typename BinaryTree<int>::Node(9);
  typename BinaryTree<int>::Node* root = new typename BinaryTree<int>::Node(6);
  root->left = zero_node;
  root->right = seven_node;
  return root;
}

void genIsOrderedTree(BinaryTree<int> &tree)
{
  tree.insert(6, true);
  tree.insert(10, true);
  tree.insert(7, true);
  tree.insert(4, true);
  tree.insert(0, true);
  tree.insert(8, true);
  tree.insert(9, true);
  tree.insert(11, true);
  tree.insert(1, true);
  tree.insert(3, true);
  tree.insert(2, true);
  tree.insert(5, true);
}

void assertMirror(vector<int> a, vector<int> b)
{
    REQUIRE(a.size() == b.size());

    for(size_t i = 0; i < a.size(); i++){
        CHECK(a[i] == b[b.size()-1-i]);
    }
}

void assert_path(vector<vector <int> > a, vector<vector<int> > b)
{
    REQUIRE(a.size() == b.size());
    for(size_t i = 0; i < a.size(); i++){
        REQUIRE(a[i].size() == b[i].size());
        for(size_t j=0; j<a[i].size();j++){
            CHECK(a[i][j]==b[i][j]);
        }
    }
}

////////////////////////////////////////////////////////////////
//////////////////////// Start of Tests ////////////////////////
////////////////////////////////////////////////////////////////

TEST_CASE("test_mirror", "[weight=10]"){
    vector<int> nodes;
    nodes.push_back(58); //         58
    nodes.push_back(35); //
    nodes.push_back(72); //    35        72
    nodes.push_back(10); //
    nodes.push_back(40); //  10  40    61  80
    nodes.push_back(61); //
    nodes.push_back(80); // 0 19            93
    nodes.push_back(93); //
    nodes.push_back(0); //
    nodes.push_back(19); //

    BinaryTree<int> tree;
    for(size_t i = 0; i < nodes.size(); i++)
        tree.insert(nodes[i], true);

    vector<int> beforeMirror;
    vector<int> afterMirror;

    tree.inOrder(beforeMirror);

    tree.mirror();

    tree.inOrder(afterMirror);

    assertMirror(beforeMirror, afterMirror);
}

TEST_CASE("test_isOrderedRecursive", "[weight=10]"){
    BinaryTree<int> tree(genNonIsOrderedTree());

    REQUIRE(tree.isOrderedRecursive() == false);

    BinaryTree<int> tree2;
    genIsOrderedTree(tree2);

    REQUIRE(tree2.isOrderedRecursive() == true);
}

TEST_CASE("test_isOrderedIterative", "[weight=10]"){
    BinaryTree<int> tree(genNonIsOrderedTree());

    REQUIRE(tree.isOrderedIterative() == false);

    BinaryTree<int> tree2;
    genIsOrderedTree(tree2);

    REQUIRE(tree2.isOrderedIterative() == true);
}

TEST_CASE("test_InorderTraversal", "[weight=10]"){
    vector<int> nodes;
    nodes.push_back(52); //         52
    nodes.push_back(39); //
    nodes.push_back(71); //    39         71
    nodes.push_back(17); //
    nodes.push_back(47); //  17   47     69   80
    nodes.push_back(69); //
    nodes.push_back(80); // 0 24             90
    nodes.push_back(90); //
    nodes.push_back(0); //
    nodes.push_back(24); //

    BinaryTree<int> tree;
    for(size_t i = 0; i < nodes.size(); i++)
        tree.insert(nodes[i], true);

    InorderTraversal<int> t(tree.getRoot());
    TreeTraversal<int>::Iterator it = t.begin();
    REQUIRE( (*it)->elem == 0  ); ++it;
    REQUIRE( (*it)->elem == 17 ); ++it;
    REQUIRE( (*it)->elem == 24 ); ++it;
    REQUIRE( (*it)->elem == 39 ); ++it;
    REQUIRE( (*it)->elem == 47 ); ++it;
    REQUIRE( (*it)->elem == 52 ); ++it;  
    REQUIRE( (*it)->elem == 69 ); ++it;
    REQUIRE( (*it)->elem == 71 ); ++it;
    REQUIRE( (*it)->elem == 80 ); ++it;  
    REQUIRE( (*it)->elem == 90 ); ++it;

}


TEST_CASE("test_getPaths", "[weight=10]"){
    vector<int> nodes;
    nodes.push_back(52); //         52
    nodes.push_back(39); //
    nodes.push_back(71); //    39         71
    nodes.push_back(17); //
    nodes.push_back(47); //  17   47     69   80
    nodes.push_back(69); //
    nodes.push_back(80); // 0 24             90
    nodes.push_back(90); //
    nodes.push_back(0); //
    nodes.push_back(24); //

    BinaryTree<int> tree;
    for(size_t i = 0; i < nodes.size(); i++)
        tree.insert(nodes[i], true);

    vector<vector<int> > treePaths;
    tree.getPaths(treePaths);

    int arr[5][4] = {{52,39,17,0},{52,39,17,24},{52,39,47,-1},{52,71,69,-1},{52,71,80,90}};

    vector<vector <int> > treePathSolution;
    for(int i=0;i<5;i++){
        vector<int> temp;
        for(int j=0; j<4; j++){
            if(arr[i][j]!=-1)
                temp.push_back(arr[i][j]);
        }
        treePathSolution.push_back(temp);
    }
    assert_path(treePathSolution, treePaths);
}


TEST_CASE("test_calcFromAST_simple", "[weight=10]"){
    std::string compute_str = "(5 + 3) * (90 - 3)";
    typename BinaryTree<std::string>::Node* root;
    double res = pemdasToAST(compute_str, root);

    AbstractSyntaxTree calc_tree(root);

    REQUIRE(calc_tree.eval() == res);
}

TEST_CASE("test_calcFromAST_intermediate", "[weight=10]"){
    std::string compute_str = "((28 + 69) * (45 / 3)) + (78643 - 10083 * 4)";
    typename BinaryTree<std::string>::Node* root;
    double res = pemdasToAST(compute_str, root);

    AbstractSyntaxTree calc_tree(root);

    REQUIRE(calc_tree.eval() == res);
}

TEST_CASE("test_calcFromAST_complex", "[weight=10]"){
    std::string compute_str = "(4 * (6 + (3 - 2) * 9 + 23)) + (1097 * (6784 / ((883 + 237) * 3))) + (70934 - (673 / (5  * (3 * 3))))";
    typename BinaryTree<std::string>::Node* root;
    double res = pemdasToAST(compute_str, root);

    AbstractSyntaxTree calc_tree(root);

    REQUIRE(calc_tree.eval() == res);
}

TEST_CASE("test_sumDistances", "[weight=0][extraCredit=1]"){
    vector<int> nodes;
    nodes.push_back(50); //         50
    nodes.push_back(32); //
    nodes.push_back(70); //    32        70
    nodes.push_back(10); //
    nodes.push_back(45); //  10  45    69  88
    nodes.push_back(69);
    nodes.push_back(88);

    BinaryTree<int> tree;
    for(size_t i = 0; i < nodes.size(); i++)
        tree.insert(nodes[i], true);
    REQUIRE(10 == tree.sumDistances());
}
