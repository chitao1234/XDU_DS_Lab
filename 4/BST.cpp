#include <iostream>

using namespace std;

struct TreeNode {
    int key;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int value)
        : key(value), left(NULL), right(NULL) {
    }
};

class BinarySearchTree {
   private:
    TreeNode *root;

    TreeNode *insertRecursive(TreeNode *node, int key) {
        if (node == NULL) {
            return new TreeNode(key);
        }

        if (key < node->key) {
            node->left = insertRecursive(node->left, key);
        } else if (key > node->key) {
            node->right = insertRecursive(node->right, key);
        }

        return node;
    }

    bool searchRecursive(TreeNode *node, int key) {
        if (node == NULL) {
            return false;
        }

        if (key == node->key) {
            return true;
        } else if (key < node->key) {
            return searchRecursive(node->left, key);
        } else {
            return searchRecursive(node->right, key);
        }
    }

    TreeNode *removeRecursive(TreeNode *node, int key) {
        if (node == NULL) {
            return NULL;
        }

        if (key < node->key) {
            node->left = removeRecursive(node->left, key);
        } else if (key > node->key) {
            node->right = removeRecursive(node->right, key);
        } else {
            if (node->left == NULL) {
                TreeNode *temp = node->right;
                delete node;
                return temp;
            } else if (node->right == NULL) {
                TreeNode *temp = node->left;
                delete node;
                return temp;
            }

            node->key = findPred(node->left);
            removeRecursive(node->left, node->key);
        }

        return node;
    }

    void inorderTraversalRecursive(TreeNode *node) {
        if (node != NULL) {
            inorderTraversalRecursive(node->left);
            cout << node->key << " ";
            inorderTraversalRecursive(node->right);
        }
    }

    int findPred(TreeNode *node) {
        while (node->right != NULL) {
            node = node->right;
        }
        int key = node->key;
        return key;
    }

   public:
    BinarySearchTree()
        : root(NULL) {
    }

    void insert(int key) {
        root = insertRecursive(root, key);
    }

    bool search(int key) {
        return searchRecursive(root, key);
    }

    void remove(int key) {
        root = removeRecursive(root, key);
    }

    void inorderTraversal() {
        inorderTraversalRecursive(root);
        cout << endl;
    }
};

int main() {
    BinarySearchTree bst;

    bst.insert(50);
    bst.insert(30);
    bst.insert(20);
    bst.insert(40);
    bst.insert(70);
    bst.insert(60);
    bst.insert(80);
    cout << "After insert: ";
    bst.inorderTraversal();

    int searchKey = 40;
    if (bst.search(searchKey)) {
        cout << searchKey << " found" << endl;
    } else {
        cout << searchKey << " not found." << endl;
    }

    int deleteKey = 50;
    bst.remove(deleteKey);
    cout << "After delete " << deleteKey << ": ";
    bst.inorderTraversal();

    return 0;
}

