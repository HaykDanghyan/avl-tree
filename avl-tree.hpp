#include "avl-tree.h"

template <typename T> 
AVL<T>::AVL() : root{nullptr}, node_count{} {}

template <typename T>
AVL<T>::AVL(const T& val) : root{nullptr}, node_count{} {
    root = new TreeNode(val);
    node_count = 1;
}

template <typename T>
AVL<T>::AVL(T&& val) : root{nullptr}, node_count{} {
    root = new TreeNode(std::move(val));
    node_count = 1;
}

template <typename T>
AVL<T>::AVL(std::initializer_list<T> init) : root{nullptr}, node_count{} {
    for (const auto& elem : init) {
        insert(elem);
    }
}

template <typename T>
AVL<T>::AVL(const AVL<T>& rhs) : root{nullptr}, node_count{} {
    root = clone(rhs.root);
    node_count = rhs.node_count;
}

template <typename T>
AVL<T>::AVL(AVL<T>&& rhs) : root{nullptr} {
    root = rhs.root;
    rhs.root = nullptr;
    node_count = rhs.node_count;
}

template <typename T>
AVL<T>::~AVL() {
    clear();
    root = nullptr;
}

template <typename T>
AVL<T>& AVL<T>::operator=(const AVL<T>& rhs) {
    if (this != &rhs) {
        clear();
        root = clone(rhs.root);
        node_count = rhs.node_count;
    }
    return *this;
}

template <typename T>
AVL<T>& AVL<T>::operator=(AVL<T>&& rhs) {
    if (this != &rhs) {
        clear();
        root = rhs.root;
        rhs.root = nullptr;
        node_count = rhs.node_count;

    }
    return *this;
}

template <typename T>
void AVL<T>::insert(const T& val) {
    if (root == nullptr) {
        root = new TreeNode(val);
        ++node_count;
        return;
    }
    insert_help(root, val);
}

template <typename T>
void AVL<T>::insert(T&& val) {
    if (root == nullptr) {
        root = new TreeNode(std::move(val));
        return;
    }
    insert_help(root, std::move(val));
}

template <typename T>
void AVL<T>::insert_help(TreeNode*& r, const T& val) {
    if (r == nullptr) {
        r = new TreeNode(val);
        ++node_count;
        return;
    }
    if (val < r->val) {
        insert_help(r->left, val);
    } 
    if (val > r->val) {
        insert_help(r->right, val);
    }
    if (val == r->val) {
        return;
    }
    int bf = balance_factor(r);
    if (bf > 1 || bf < -1) {
        bring_to_balance(r, val);
    }
}

template <typename T>
void AVL<T>::insert_help(TreeNode*& r, T&& val) {
    if (r == nullptr) {
        r = new TreeNode(std::move(val));
        ++node_count;
        return;
    }
    if (val < r->val) {
        insert_help(r->left, val);
    } 
    if (val > r->val) {
        insert_help(r->right, val);
    }
    if (val == r->val) {
        return;
    }
    int bf = balance_factor(r);
    if (bf > 1 || bf < -1) {
        bring_to_balance(r, val);
    }
}

template <typename T>
void AVL<T>::bring_to_balance(TreeNode*& root, const T& val) {
    if (root->left == nullptr && root->right == nullptr) {
        return;
    }
    int bf = balance_factor(root);
    if (bf < -1 && root->right->left == nullptr) {
        root = left_rotate(root);
    }
    if (bf > 1 && root->left->right == nullptr) {
        root = right_rotate(root);
    }
    if (bf < - 1 && root->right->left != nullptr) {
        root = left_right_rotate(root);
    }
    if (bf > 1 && root->left->right != nullptr) {
        root = right_left_rotate(root);
    }

}

template <typename T> 
void AVL<T>::bring_to_balance(TreeNode*& root, T&& val) {
    if (root->left == nullptr && root->right == nullptr) {
        return;
    }
    int bf = balance_factor(root);
    if (bf < -1 && root->right->left == nullptr) {
        root = left_rotate(root);
    }
    if (bf > 1 && root->left->right == nullptr) {
        root = right_rotate(root);
    }
    if (bf < - 1 && root->right->left != nullptr) {
        root = left_right_rotate(root);
    }
    if (bf > 1 && root->left->right != nullptr) {
        root = right_left_rotate(root);
    }

    
}

template <typename T>
typename AVL<T>::TreeNode* AVL<T>::left_rotate(TreeNode* x) {
    TreeNode* y = x->right;
    TreeNode* t = y->left;
    y->left = x;
    x->right = t;
    return y;
}

template <typename T>
typename AVL<T>::TreeNode* AVL<T>::right_rotate(TreeNode* y) {
    TreeNode* x = y->left;
    TreeNode* t = x->right;
    x->right = y;
    y->left = t;
    return x;
}

template <typename T>
typename AVL<T>::TreeNode* AVL<T>::right_left_rotate(TreeNode* x) {
    x->right = right_rotate(x->right);
    return left_rotate(x);
}

template <typename T>
typename AVL<T>::TreeNode* AVL<T>::left_right_rotate(TreeNode* x) {
    x->left = left_rotate(x->left);
    return right_rotate(x);
}

template <typename T>
typename AVL<T>::TreeNode* AVL<T>::clone(TreeNode* root) {
    if (root == nullptr) {
        return root;
    }
    return (new TreeNode(root->val, clone(root->left), clone(root->right)));
}

template <typename T>
void AVL<T>::inorder() {
    if (root == nullptr) {
        return;
    }
    inorder(root);
}

template <typename T>
void AVL<T>::inorder(TreeNode* root) {
    if (root == nullptr) {
        return;
    }
    inorder(root->left);
    std::cout << root->val << std::endl;
    inorder(root->right);
}

template <typename T>
void AVL<T>::preorder() {
    if (root == nullptr) {
        return;
    }
    preorder(root);
}

template <typename T>
void AVL<T>::preorder(TreeNode* root) {
    if (root == nullptr) {
        return;
    }
    std::cout << root->val << std::endl;
    preorder(root->left);
    preorder(root->right);
}

template <typename T>
void AVL<T>::postorder() {
    if (root == nullptr) {
        return;
    }
    postorder(root);
}

template <typename T>
void AVL<T>::postorder(TreeNode* root) {
    if (root == nullptr) {
        return;
    }
    postorder(root->left);
    postorder(root->right);
    std::cout << root->val << std::endl;
}

template <typename T>
void AVL<T>::levelorder() {
    if (root == nullptr) {
        return;
    }
    for (int i = 0; i < height(root); ++i) {
        levelorder(root, i);
    }
}

template <typename T>
void AVL<T>::levelorder(TreeNode* root, int h) {
    if (root == nullptr) {
        return;
    }
    if (h == 0) {
        std::cout << root->val << std::endl;
    } else {
        levelorder(root->left, h - 1);
        levelorder(root->right, h - 1);
    }
}


template <typename T>
bool AVL<T>::empty() const {
    return root == nullptr;
}

template <typename T>
bool AVL<T>::contains(const T& val) {
    return contains_help(root, val);
}

template <typename T>
bool AVL<T>::contains_help(TreeNode* root, const T& val) {
    if (root == nullptr) {
        return false;
    }
    if (val < root->val) {
        return contains_help(root->left, val);
    }    
    if (val > root->val) {
        return contains_help(root->right, val);
    }
    return true;
}

template <typename T>
void AVL<T>::clear() {
    clear_help(this->root);
}

template <typename T>
void AVL<T>::clear_help(TreeNode* r) {
    if (r == nullptr) {
        return;
    }
    clear_help(r->left);
    clear_help(r->right);
    delete r;
    r = nullptr;
}

template <typename T>
int AVL<T>::height(TreeNode* r) const {
    if (r == nullptr) {
        return 0;
    }
    return 1 + std::max(height(r->left), height(r->right));
}

template <typename T>
int AVL<T>::balance_factor(TreeNode* root) {
    return height(root->left) - height(root->right);
}

template <typename T>
typename AVL<T>::TreeNode* AVL<T>::find(const T& val) {
    return find_help(root, val);
}

template <typename T>
typename AVL<T>::TreeNode* AVL<T>::find_help(TreeNode* root, const T& val) {
    if (root == nullptr || root->val == val) {
        return root;
    }
    if (val < root->val) {
        return find_help(root->left, val);
    }
    if (val > root->val) {
        return find_help(root->right, val);
    }
    return root;
}

template <typename T>
void AVL<T>::erase(const T& val) {
    if (val == root->val) {
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            root = nullptr;
            return;
        }
        erase_root(root);
        int bf = balance_factor(root);
        if (bf > 1 || bf < -1) {
            bring_to_balance(root, val);
        }
        return;
    }
    if (find(val) == nullptr) {
        throw std::invalid_argument("Value doesn't exist");
    }
    erase_help(root, val);
    int bf = balance_factor(root);
    if (bf > 1 || bf < -1) {
        bring_to_balance(root, val);
    }
}

template <typename T>
void AVL<T>::erase(T&& val) {
    if (val == root->val) {
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            root = nullptr;
            return;
        }
        erase_root(root);
        int bf = balance_factor(root);
        if (bf > 1 || bf < -1) {
            bring_to_balance(root, val);
        }
        return;
    }
    if (find(val) == nullptr) {
        throw std::invalid_argument("Value doesn't exist");
    }
    erase_help(root, val);
    int bf = balance_factor(root);
    if (bf > 1 || bf < -1) {
        bring_to_balance(root, val);
    }
}

template <typename T>
void AVL<T>::erase_help(TreeNode*& root, const T& val) {
    if (root == nullptr) {
        return;
    }
    if (val < root->val) {
        erase_help(root->left, val);
    }
    else if (val > root->val) {
        erase_help(root->right, val);
    } 
    else if (root->left != nullptr && root->right != nullptr) {
        root->val = find_min()->val;
        erase_help(root->right, root->val);
    } else {
        TreeNode* oldNode = root;
        root = (root->left != nullptr) ? root->left : root->right;
        delete oldNode;
        oldNode = nullptr;
    }
}

template <typename T>
void AVL<T>::erase_root(TreeNode*& r) {
    if (r->left != nullptr && r->right == nullptr) {
        TreeNode* del = r;
        r->left->right = r->right;
        r = r->left;
        delete del;
        del = nullptr;
    } else if (r->left == nullptr && r->right != nullptr) {
        TreeNode* del = r;
        r->right->left = r->left;
        r = r->right;
        delete del;
        del = nullptr;
    } else {
        TreeNode* del = nullptr;
        r->right->left = r->left;
        r = r->right;
        delete del;
        del = nullptr;
    }
}


template <typename T>
size_t AVL<T>::number_of_nodes() {
    return node_count;
}

template <typename T>
T AVL<T>::get_root_data() {
    return root->val;
}

template <typename T>
typename AVL<T>::TreeNode* AVL<T>::find_min() const {
    return find_min(root);
}   

template <typename T>
typename AVL<T>::TreeNode* AVL<T>::find_min(TreeNode* root) const {
    if (!root) {
        return nullptr;
    }
    if (!root->left) {
        return root;
    }
    return find_min(root->left);   
}   

template <typename T>
typename AVL<T>::TreeNode* AVL<T>::find_max() const {
    return find_max(root);
}

template <typename T>
typename AVL<T>::TreeNode* AVL<T>::find_max(TreeNode* root) const {
    if (!root) {
        return nullptr;
    }
    if (!root->right) {
        return root;
    }
    return find_max(root->right);   
}


template <typename T>
void AVL<T>::merge(const AVL<T>& rhs) {
    if (rhs.root == nullptr) {
        return;
    }
    merge_help(root, rhs.root);
}

template <typename T>
void AVL<T>::merge_help(TreeNode*& r, TreeNode* rhs) {
    if (rhs == nullptr) {
        return;
    }
    if (r == nullptr) {
        r = new TreeNode(rhs->val);
    }
    merge_help(r, rhs->left);
    insert_help(r, rhs->val);
    merge_help(r, rhs->right);
    insert_help(r, rhs->val);
}
