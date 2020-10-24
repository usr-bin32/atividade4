#ifndef AVL_NODE
#define AVL_NODE

#include <vector>

class AVLNode {
  public:
    AVLNode();
    AVLNode(int value);

    AVLNode *left();
    AVLNode *right();
    AVLNode *parent();
    void left(AVLNode *node);
    void right(AVLNode *node);
    void parent(AVLNode *node);

    int height();
    int balance_factor();

    AVLNode *insert(int value);
    AVLNode *search(int value, int &comparisons);
    bool remove(int value, AVLNode *&parent);
    AVLNode *min();

    void traverse(std::vector<int> &values);
    void delete_children();

    int m_value;
    bool m_empty;

  private:
    AVLNode *m_left = nullptr;
    AVLNode *m_right = nullptr;
    AVLNode *m_parent = nullptr;
};

#endif
