#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <initializer_list>
#include <iostream>

template <typename T>
class AVL {
private:
    struct TreeNode {
        TreeNode* left;
        T val;
        TreeNode* right;
        TreeNode(const T& v = T(), TreeNode* l = nullptr, TreeNode* r = nullptr)
        : val{v}, left{l}, right{r} {}
    };
    TreeNode* root; 
    size_t node_count;

public: // Special member functions
    AVL();
    AVL(const T&);
    AVL(T&&);
    AVL(std::initializer_list<T>);
    AVL(const AVL<T>&);
    AVL(AVL<T>&&);
    ~AVL();

    AVL<T>& operator=(const AVL<T>&);
    AVL<T>& operator=(AVL<T>&&);

public: // Tree Traversals
    void inorder();
    void preorder();
    void postorder();
    void levelorder();

public:
    bool empty() const;
    bool contains(const T&);
    void clear();
    size_t number_of_nodes();
    T get_root_data();

public:
    void insert(const T&);
    void insert(T&&);
    TreeNode* find(const T&);
    void erase(const T&);
    void erase(T&&);
    void merge(const AVL<T>&);

public:
    TreeNode* find_min() const;
    TreeNode* find_max() const;

private: // helpers
    TreeNode* clone(TreeNode*);
    TreeNode* find_help(TreeNode*, const T&);
    TreeNode* find_min(TreeNode*) const;
    TreeNode* find_max(TreeNode*) const;
    void insert_help(TreeNode*&, const T&);
    void insert_help(TreeNode*&, T&&);
    void clear_help(TreeNode*);
    bool contains_help(TreeNode*, const T&);
    void erase_help(TreeNode*&, const T&);
    void erase_root(TreeNode*&);
    void merge_help(TreeNode*&, TreeNode*);


private: // balance helpers   
    int height(TreeNode*) const;
    int balance_factor(TreeNode*);
    void bring_to_balance(TreeNode*&, const T&);
    void bring_to_balance(TreeNode*&, T&&);
    TreeNode* left_rotate(TreeNode*);
    TreeNode* right_rotate(TreeNode*);
    TreeNode* left_right_rotate(TreeNode*);
    TreeNode* right_left_rotate(TreeNode*);

private: // traversal helper
    void inorder(TreeNode*);
    void preorder(TreeNode*);
    void postorder(TreeNode*);
    void levelorder(TreeNode*, int);
};
#include "avl-tree.hpp"
#endif