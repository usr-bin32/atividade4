#include "avl_node.h"

AVLNode::AVLNode() {
    m_value = 0;
    m_empty = true;
}

AVLNode::AVLNode(int value) {
    m_value = value;
    m_empty = false;
}

AVLNode *AVLNode::left() {
    return m_left;
}

AVLNode *AVLNode::right() {
    return m_right;
}

AVLNode *AVLNode::parent() {
    return m_parent;
}

void AVLNode::left(AVLNode *node) {
    m_left = node;
    if (left() != nullptr) {
        left()->parent(this);
    }
}

void AVLNode::right(AVLNode *node) {
    m_right = node;
    if (right() != nullptr) {
        right()->parent(this);
    }
}

void AVLNode::parent(AVLNode *node) {
    m_parent = node;
}

int AVLNode::height() {
    int height_left = -1;
    if (left() != nullptr) {
        height_left = left()->height();
    }

    int height_right = -1;
    if (right() != nullptr) {
        height_right = right()->height();
    }

    return (height_left > height_right ? height_left : height_right) + 1;
}

int AVLNode::balance_factor() {
    int left_height = -1;
    if (left()) {
        left_height = left()->height();
    }

    int right_height = -1;
    if (right()) {
        right_height = right()->height();
    }

    return right_height - left_height;
}

AVLNode *AVLNode::insert(int value) {
    AVLNode *new_node = nullptr;

    if (m_empty) {
        m_value = value;
        m_empty = false;
        new_node = this;
    } else if (value < m_value) {
        if (left() != nullptr) {
            new_node = left()->insert(value);
        } else {
            new_node = new AVLNode(value);
            left(new_node);
        }
    } else {
        if (right() != nullptr) {
            new_node = right()->insert(value);
        } else {
            new_node = new AVLNode(value);
            right(new_node);
        }
    }

    return new_node;
}

AVLNode *AVLNode::search(int value, int &comparisons) {
    AVLNode *node = nullptr;
    comparisons++;

    if (!m_empty) {
        if (value == m_value) {
            node = this;
        } else if (value < m_value && left() != nullptr) {
            node = left()->search(value, comparisons);
        } else if (right() != nullptr) {
            node = right()->search(value, comparisons);
        }
    }

    return node;
}

bool AVLNode::remove(int value, AVLNode *&parent) {
    int comparisons;
    AVLNode *node = search(value, comparisons);

    if (node == nullptr) {
        return false;
    }
    parent = node->parent();

    if (node->left() == nullptr && node->right() == nullptr) {
        if (node->parent() != nullptr) {
            if (node == node->parent()->left()) {
                node->parent()->left(nullptr);
            } else {
                node->parent()->right(nullptr);
            }
            delete node;
        } else {
            node->m_empty = true;
        }
    } else if (node->left() != nullptr && node->right() != nullptr) {
        AVLNode *min_right = node->right()->min();
        if (min_right != node->right()) {
            int v = min_right->m_value;

            AVLNode *temp;
            min_right->remove(min_right->m_value, temp);

            node->m_value = v;
        } else {
            node->m_value = node->right()->m_value;
            node->right(node->right()->right());

            delete min_right;
        }
    } else {
        AVLNode *child_node = nullptr;
        if (node->left() != nullptr) {
            child_node = node->left();
        } else {
            child_node = node->right();
        }

        if (node->parent() != nullptr) {
            if (node == node->parent()->left()) {
                node->parent()->left(child_node);
            } else {
                node->parent()->right(child_node);
            }
            delete node;
        } else {
            node->m_value = child_node->m_value;
            node->left(child_node->left());
            node->right(child_node->right());

            delete child_node;
        }
    }

    return true;
}

AVLNode *AVLNode::min() {
    if (left() == nullptr) {
        return this;
    }
    return left()->min();
}

void AVLNode::traverse(std::vector<int> &values) {
    if (m_empty) {
        return;
    }

    values.push_back(m_value);

    if (left() != nullptr) {
        left()->traverse(values);
    }

    if (right() != nullptr) {
        right()->traverse(values);
    }
}

void AVLNode::delete_children() {
    if (left() != nullptr) {
        left()->delete_children();
        delete left();
    }

    if (right() != nullptr) {
        right()->delete_children();
        delete right();
    }
}
