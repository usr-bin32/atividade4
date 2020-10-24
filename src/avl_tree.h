#ifndef AVL_TREE
#define AVL_TREE

#include "avl_node.h"
#include <vector>

class AVLTree {
  public:
    AVLTree(bool balance);
    ~AVLTree();

    bool insert(int value);
    bool search(int value, int &comparisons);
    bool remove(int value);
    void traverse_depth(std::vector<int> &values);

    int height();

  private:
    AVLNode *m_root;
    bool m_balance;

    void balance(AVLNode *node);
    void rotate_left(AVLNode *p);
    void rotate_right_left(AVLNode *p);
    void rotate_right(AVLNode *p);
    void rotate_left_right(AVLNode *p);
};

#endif
