#include <iostream>
#include <vector>
#include <queue>

using namespace std;

template <typename T>
class TreeNode {
public:
    T data;
    vector<TreeNode*> children;

    TreeNode(T value) : data(value) {}
};

template <typename T>
class GeneralTree {
private:
    TreeNode<T>* root;

public:
    GeneralTree() : root(nullptr) {}

    TreeNode<T>* getRoot() {
        return root;
    }

    TreeNode<T>* getParent(TreeNode<T>* node, TreeNode<T>* current = nullptr) {
        if (current == nullptr) {
            current = root;
        }

        if (current == nullptr) {
            return nullptr;
        }

        for (TreeNode<T>* child : current->children) {
            if (child == node) {
                return current;
            }
            else {
                TreeNode<T>* parent = getParent(node, child);
                if (parent != nullptr) {
                    return parent;
                }
            }
        }

        return nullptr;
    }

    vector<TreeNode<T>*> getChildren(TreeNode<T>* node) {
        return node->children;
    }

    int size(TreeNode<T>* node) {
        if (node == nullptr) {
            return 0;
        }

        int count = 1;  
        for (TreeNode<T>* child : node->children) {
            count += size(child);  
        }
        return count;
    }

    int depth(TreeNode<T>* node) {
        if (node == root) {
            return 0;
        }
        else {
            TreeNode<T>* parent = getParent(node);
            return 1 + depth(parent);
        }
    }

    bool isEmpty() {
        return root == nullptr;
    }

    bool isRoot(TreeNode<T>* node) {
        return node == root;
    }

    bool isLeaf(TreeNode<T>* node) {
        return node->children.empty();
    }

    void insert(T value) {
        TreeNode<T>* newNode = new TreeNode<T>(value);
        if (root == nullptr) {
            root = newNode;
        }
        else {
            root->children.push_back(newNode);
        }
    }

    void insertAsChild(TreeNode<T>* parent, T value) {
        if (parent == nullptr) {
            cout << "Parent is null. Cannot insert as child." << endl;
            return;
        }
        TreeNode<T>* newNode = new TreeNode<T>(value);
        parent->children.push_back(newNode);
    }

    void deleteNode(TreeNode<T>* node) {
        TreeNode<T>* parent = getParent(node);
        if (parent == nullptr) {
            cout << "Cannot delete the root node." << endl;
            return;
        }

        for (auto it = parent->children.begin(); it != parent->children.end(); ++it) {
            if (*it == node) {
                parent->children.erase(it);
                delete node;
                return;
            }
        }
    }

    void depthFirstPreorderTraversal(TreeNode<T>* node) {
        if (node == nullptr) {
            return;
        }

        cout << node->data << " ";
        for (TreeNode<T>* child : node->children) {
            depthFirstPreorderTraversal(child);
        }
    }

    void breadthFirstTraversal() {
        if (root == nullptr) {
            return;
        }

        queue<TreeNode<T>*> q;
        q.push(root);

        while (!q.empty()) {
            TreeNode<T>* node = q.front();
            q.pop();

            cout << node->data << " ";

            for (TreeNode<T>* child : node->children) {
                q.push(child);
            }
        }
    }
    
};

int main() {
    GeneralTree<int> tree;

    tree.insert(1);
    TreeNode<int>* node2 = tree.getRoot();
    tree.insertAsChild(node2, 2);
    tree.insertAsChild(node2, 3);
    TreeNode<int>* node4 = node2->children[0];
    tree.insertAsChild(node4, 4);
    tree.insertAsChild(node4, 5);
    TreeNode<int>* node6 = node4->children[1];
    tree.insertAsChild(node6, 6);



    cout << "Depth-First Preorder Traversal: ";
    tree.depthFirstPreorderTraversal(tree.getRoot());
    cout << endl;

    cout << "Breadth-First Traversal: ";
    tree.breadthFirstTraversal();
    cout << endl;

    cout << "Size of the tree: " << tree.size(tree.getRoot()) << endl;
    cout << "Depth of node 6: " << tree.depth(node6) << endl;

    return 0;
}

