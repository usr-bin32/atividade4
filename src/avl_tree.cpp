#include "avl_tree.h"

AVLTree::AVLTree(bool balance) {
    m_balance = balance;
    m_root = new AVLNode();
}

AVLTree::~AVLTree() {
    m_root->delete_children();
    delete m_root;
}

bool AVLTree::insert(int value) {
    AVLNode *new_node = m_root->insert(value);

    if (m_balance && new_node != nullptr) {
        AVLNode *node = new_node;
        while (node != nullptr) {
            balance(node);
            node = node->parent();
        }
    }

    return new_node != nullptr;
}

bool AVLTree::remove(int value) {
    AVLNode *parent = nullptr;
    bool result = m_root->remove(value, parent);

    if (m_balance && result) {
        AVLNode *node = parent;
        while (node != nullptr) {
            balance(node);
            node = node->parent();
        }
    }

    return result;
}

bool AVLTree::search(int value, int &comparisons) {
    comparisons = 0;
    return m_root->search(value, comparisons) != nullptr;
}

void AVLTree::traverse_depth(std::vector<int> &values) {
    m_root->traverse(values);
}

void AVLTree::balance(AVLNode *node) {
    if (node->balance_factor() == 2) {
        if (node->right()->balance_factor() > 0) {
            rotate_left(node);
        } else if (node->right()->balance_factor() < 0) {
            rotate_right_left(node);
        }
    } else if (node->balance_factor() == -2) {
        if (node->left()->balance_factor() < 0) {
            rotate_right(node);
        } else if (node->left()->balance_factor() > 0) {
            rotate_left_right(node);
        }
    }
}

void AVLTree::rotate_left(AVLNode *p) {
    AVLNode *q = p->right();

    if (p->parent() != nullptr) {
        if (p->parent()->right() == p) {
            p->parent()->right(q);
        } else {
            p->parent()->left(q);
        }
    } else if (p == m_root) {
        m_root = q;
        q->parent(nullptr);
    }

    p->right(q->left());
    q->left(p);
}

void AVLTree::rotate_right_left(AVLNode *p) {
    AVLNode *q = p->right();
    AVLNode *r = q->left();

    p->right(r);
    q->left(r->right());
    r->right(q);

    rotate_left(p);
}

void AVLTree::rotate_right(AVLNode *p) {
    AVLNode *q = p->left();

    if (p->parent() != nullptr) {
        if (p->parent()->right() == p) {
            p->parent()->right(q);
        } else {
            p->parent()->left(q);
        }
    } else if (p == m_root) {
        m_root = q;
        q->parent(nullptr);
    }

    p->left(q->right());
    q->right(p);
}

void AVLTree::rotate_left_right(AVLNode *p) {
    AVLNode *q = p->left();
    AVLNode *r = q->right();

    p->left(r);
    q->right(r->left());
    r->left(q);

    rotate_right(p);
}

int AVLTree::height() {
    if (m_root == nullptr || m_root->m_empty) {
        return -1;
    }
    return m_root->height();
}
