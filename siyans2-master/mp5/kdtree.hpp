/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

using namespace std;

/*template <int Dim>
double arr[Dim];
for (unsigned i = 0; i < Dim; i++) {
  arr[i] = 1000;
}
template <int Dim>
Point<Dim> best(arr); */

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const {
    /**
     * @todo Implement this function!
     */
     if (first[curDim] == second[curDim]) return first < second;
     else return first[curDim] < second[curDim];

}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const {
    /**
     * @todo Implement this function!
     */
     //a is equal to the distance between the poteial and current currentBest
     //b is the distance between the target and the potential
     //if (currentBest == NULL) return true; //if we haven't set the best yet, should set it double
     //else {
      cout << "Should replace "<< currentBest << " with " << potential << " to get to " << target << "?" << endl;
       int dp = 0, dc = 0;
       for (int i = 0; i < Dim; i++) {
         dp = dp + (potential[i]-target[i])*(potential[i]-target[i]);
         dc = dc + (currentBest[i]-target[i])*(currentBest[i]-target[i]);
       }

       if (dc == dp) {
         return potential < currentBest;
       }

       return dp < dc;
     //}

}


template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */

    vec = newPoints;
    size = newPoints.size();

    if (newPoints.empty()) {
      root = NULL;
      return;
    }

    root = recursiveKDTree(0, 0, vec.size()-1);
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode*KDTree<Dim>::recursiveKDTree(int d, int l, int r) {
  /**
   * @todo Implement this function!
   */
   KDTreeNode *currNode = new KDTreeNode();
   int median = (l+r)/2;

   currNode->point = quickie(median, l, r, d);

   if (l != median ) {

     //chooses the dimension to be in
     int dimension = (d + 1) % Dim;
     // if (dimension > Dim) {
     //   dimension = d;
     // }
     currNode->left = recursiveKDTree(dimension, l, median - 1);
   }
   if (r != median) {

     int dimension = (d + 1) % Dim;
     // if (dimension > Dim) {
     //   dimension = d;
     // }
     currNode->right = recursiveKDTree(dimension, median + 1, r);
   }

   return currNode;
}

template <int Dim>
Point<Dim> KDTree<Dim>::quickie(int mid, int l, int r, int d) {
  /**
   * @todo Implement this function!
   */
   if (l == r) {
     return vec[l];
   }

   int pivot = (l+r) / 2;
   pivot = partition(l, r, d, pivot);

   if (pivot == mid) {
     return vec[pivot];
   }

   else if (mid < pivot) {
     return quickie(mid, l, pivot - 1, d);
   }

   else {
     return quickie(mid, pivot + 1,r, d);
   }
}

template <int Dim>
int KDTree<Dim>::partition(int l, int r, int d, int pivot) {
  /**
   * @todo Implement this function!
   */
   Point<Dim> pivotPoint = vec[pivot];
   //moves the pivot to the end of the array
   std::swap(vec[pivot], vec[r]);

   //elements less than pivot pushed to left of index
   //elements more than pivot pushed to the right
   //equal goes either way

   int pInd = l;

   for (int i = l; i < r; i++) {
     if (smallerDimVal(vec[i], pivotPoint, d)) {
       std::swap(vec[i], vec[pInd]);
       pInd++;
     }
   }

   std::swap(vec[pInd], vec[r]);

   return pInd;

}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
   //rescursively add new nodes by traversing the other
   root = copy(other.root);
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::copy(const KDTreeNode* curr) {
  if (curr == NULL) return NULL;


  KDTreeNode* newNode = new KDTreeNode(curr->point);
  newNode->left = copy(curr->left);
  newNode->right = copy(curr->right);
  return newNode;
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
   this->size = rhs.size;
   this->vec = rhs.vec;

   if (this != &rhs) {
    destroy(root);
    root = copy(rhs.root);
  }

  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
   destroy(root);
}

template <int Dim>
void KDTree<Dim>::destroy(KDTreeNode *node) {
  //helper function for the Destructor
  /*if(node->left != NULL) {
    destroy(node->left);
  }
  if(node->right != NULL ) {
    destroy(node->right);
  }
  delete node;
  node = NULL;
  return;*/

  if (node == NULL)
      return;

  destroy(node->left);
  destroy(node->right);
  delete node;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
     //find closest points in KD tree (points is outside the tree)
     if (this->size == 0) return Point<Dim>(); //blank, do nothing
     if (this->size == 1) return root->point; //one node has to best best node
     else {
       cout << "\n" << "Looking for: "<< query << endl;
       KDTreeNode* curr = root;

       double arr[Dim];
       for (unsigned i = 0; i < Dim; i++) {
         arr[i] = 1000;
       }
       Point<Dim> best(arr);
       //Point<Dim> best = new Point<Dim>; //need to set to a large value so it will be overwritten

       Point<Dim> target = query;
       double radius = -1;
       int dims = 0;
       best = findNNHelper(curr, best, target, radius, dims);
       return best;
     }
    //return Point<Dim>();
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNNHelper(KDTreeNode* curr, Point<Dim> best, Point<Dim> target, double radius, int dims) const {
  //Step 1: Recurse through until we have a lead node of branch that is closest
  //Check what is closest by checking dimensions each level (0th, 1st, 2nd, 0th, ...)
//TODO USE SMALELRDIMVAL AND SHOULDREPLACE


if (curr == NULL || best == target) return best; //take care of edge cases (hopefully)
Point<Dim> currpt = curr->point;
if (currpt == target) {
  best = currpt;
  return best;
}
cout << "Current: "<< currpt << endl;
cout << "Best: "<< best << endl;
cout << "Left: " << curr->left << endl;
cout << "Right: " << curr->right << endl;


if ((curr->left == NULL) && (curr->right == NULL)) { //leaf node case
  cout << "Leaf Node "<<endl;
  if (shouldReplace(target, best, currpt)) { //if smaller distance
    best = curr->point;
    cout << "best is now: "<< best << endl;
    radius = getRadius(curr->point, target);
    }
    return best;
}
if (curr->left != NULL && curr->right != NULL) { //if we have two possible paths
  cout << "Internal node with both children"<<endl;
  cout << "Vals: " << target[dims] << currpt[dims] << endl;
  if (currpt[dims] > target[dims]) { //too large, check left tree
    cout << "Moving left"<< endl;
    best = findNNHelper(curr->left, best, target, radius, (dims + 1) % Dim);
  }
  else { //too small, check right tree
    cout << "Moving right"<< endl;
    best = findNNHelper(curr->right, best, target, radius, (dims + 1) % Dim);
    cout << "CHECK CHECK CHECK" << endl;
    // 1 is here
  }
}
else {
  if (curr->left == NULL) {
    cout << "Have to move right"<<endl;
    best = findNNHelper(curr->right, best, target, radius, (dims + 1) % Dim);
    //exit after 2 here 2 gets to check parent, 1 does not
    return best;
  }
  if (curr->right == NULL) {
    cout <<"Have to move left"<<endl;
    best = findNNHelper(curr->left, best, target, radius, (dims + 1) % Dim);
    return best;
  }
}
/*
if (currpt[dims] > target[dims] || curr->right == NULL) { //too large, check left tree
  cout << "Moving left"<< endl;
  best = findNNHelper(curr->left, best, target, radius, (dims + 1) % Dim);
  //
}
if (currpt[dims] <= target[dims] || curr->left == NULL) { //too small, check right tree
  cout << "Moving right"<< endl;
  best = findNNHelper(curr->right, best, target, radius, (dims + 1) & Dim);
}*/
//check parent node
cout << "Checking parent: " << currpt << endl;
if (shouldReplace(target, best, currpt)) {
  best = curr->point;
  cout << "best is now: "<< best << endl;
  radius = getRadius(curr->point, target);
}
//check if we should go into other tree
cout << "Checking if intersects" << endl;
if (intersects(dims, best, target)) {
  cout << "Does intersect"<< endl;
  if (currpt[dims] > target[dims]) { //go into the opposite tree
    cout << "Moving right"<<endl;
    best = findNNHelper(curr->right, best, target, radius, (dims + 1) % Dim);
    return best;
  } else {
      cout <<"Moving left"<<endl;
      best = findNNHelper(curr->left, best, target, radius, (dims + 1) % Dim);
      return best;
    }
}
cout << "TEST"<<endl;
return best;

}

template <int Dim>
double KDTree<Dim>::getRadius(const Point<Dim>& Point1, const Point<Dim>& Point2) const {
  double radius = 0;
  for (int i = 0; i < Dim; i++) {
    radius += (Point1[i] - Point2[i]) * (Point1[i] - Point2[i]);
  }
  cout << "Radius: "<< radius << endl;
  return radius;
}
//if plane distance sq is less than best radius sq, true
template <int Dim>
bool KDTree<Dim>::intersects(const int dims, const Point<Dim>& best, const Point<Dim>& target) const {
  double planedist = best[dims]-target[dims] * best[dims]-target[dims];
  double currdist = getRadius(best, target) ;
  return (planedist < currdist);
}
