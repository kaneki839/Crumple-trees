#ifndef __PROJ_FOUR_CRUMPLE_TREE_HPP
#define __PROJ_FOUR_CRUMPLE_TREE_HPP

#include <stdexcept>
#include <string>
#include <vector>

#include <iostream>
namespace shindler::ics46::project4 {

class ElementNotFoundException : public std::runtime_error {
   public:
    explicit ElementNotFoundException(const std::string &err)
        : std::runtime_error(err) {}
};

template <typename K, typename V>
class CrumpleTree {
   private:
    // fill in private member data here
    // If you need to declare private functions, do so here too.
    struct Node
    {
        Node(K key, V val)
            : key{key}, value{val}, left{nullptr}, right{nullptr}, parent{nullptr}, level{0}
        {
        }
        K key;
        V value;
        Node *left;
        Node *right;
        Node *parent;
        int level;
    };

    Node *root;
    size_t treeSize{0};

   public:
    CrumpleTree();

    // In general, a copy constructor and assignment operator
    // are good things to have.
    // For this quarter, I am not requiring these.
    //	CrumpleTree(const CrumpleTree & st);
    //	CrumpleTree & operator=(const CrumpleTree & st);
    // You do not need to implement these
    CrumpleTree(const CrumpleTree &) = delete;
    CrumpleTree(CrumpleTree &&) = delete;
    CrumpleTree &operator=(const CrumpleTree &) = delete;
    CrumpleTree &operator=(CrumpleTree &&) = delete;

    // The destructor is required.
    ~CrumpleTree();

    // size() returns the number of distinct keys in the tree.
    [[nodiscard]] size_t size() const noexcept;

    // isEmpty() returns true if and only if the tree has no values in it.
    [[nodiscard]] bool empty() const noexcept;

    // contains() returns true if and only if there
    //  is a (key, value) pair in the tree
    //	that has the given key as its key.
    bool contains(const K &key) const noexcept;

    // returns the level on which the node with this key resides.
    // If !contains(k), this will throw an ElementNotFoundException
    unsigned level(const K &key) const;

    // find returns the value associated with the given key
    // If !contains(k), this will throw an ElementNotFoundException
    // There needs to be a version for const and non-const CrumpleTrees.
    V &find(const K &key);
    const V &find(const K &key) const;

    void calculateShape(Node *node, int &leftShape, int &rightShape);
    void reArrange(Node *&parent, Node *&child, Node *&prevChild, bool leftNeedReArrange, bool rightNeedReArrange);
    // Inserts the given key-value pair into
    // the tree and performs the balancing operation(s)
    // if needed as described in lecture.
    // If the key already exists in the tree,
    // you may do as you please (no test cases in
    // the grading script will deal with this situation)
    void insert(const K &key, const V &value);

    // Deletes the given key from the tree
    // and performs the balancing operation(s) if needed.
    // If the key does not exist in the tree,
    // do not modify the tree.
    void remove(const K &key);

    // The following three functions all return
    // the set of keys in the tree as a standard vector.
    // Each returns them in a different order.
    void recursiveInOrder(Node *current, std::vector<K> &allKeys) const;
    void recursivePreOrder(Node *current, std::vector<K> &allKeys) const;
    void recursivePostOrder(Node *current, std::vector<K> &allKeys) const;
    [[nodiscard]] std::vector<K> inOrder() const;
    [[nodiscard]] std::vector<K> preOrder() const;
    [[nodiscard]] std::vector<K> postOrder() const;
};

template <typename K, typename V>
CrumpleTree<K, V>::CrumpleTree() 
    : root{nullptr}
{
}

template <typename K, typename V>
CrumpleTree<K, V>::~CrumpleTree() {
    // TODO: Implement this
}

template <typename K, typename V>
size_t CrumpleTree<K, V>::size() const noexcept {
    return treeSize;
}

template <typename K, typename V>
bool CrumpleTree<K, V>::empty() const noexcept {
    // TODO: Implement this
    return treeSize == 0;
}

template <typename K, typename V>
bool CrumpleTree<K, V>::contains(const K &key) const noexcept {
    if (empty())
    {
        return false;
    }

    Node *current{root};
    while (current != nullptr) {
        if (key == current->key)
        {
            return true;
        }
        else if (key < current->key)
        {
            current = current->left;
        }
        else 
        {
            current = current->right;
        }
    }
    return false;
}

template <typename K, typename V>
unsigned CrumpleTree<K, V>::level(const K &key) const {
    if (empty())
    {
        throw ElementNotFoundException("key is not in the tree");
    }

    Node *current{root};
    while (current != nullptr) {
        if (key == current->key)
        {
            return static_cast<unsigned>(current->level);
        }
        else if (key < current->key)
        {
            current = current->left;
        }
        else 
        {
            current = current->right;
        }
    }
    throw ElementNotFoundException("key is not in the tree");
}

template <typename K, typename V>
V &CrumpleTree<K, V>::find(const K &key) {
    if (empty())
    {
        throw ElementNotFoundException("key is not in the tree");
    }

    Node *current{root};
    while (current != nullptr) {
        if (key == current->key)
        {
            return current->value;
        }
        else if (key < current->key)
        {
            current = current->left;
        }
        else 
        {
            current = current->right;
        }
    }
    throw ElementNotFoundException("key is not in the tree");
}

template <typename K, typename V>
const V &CrumpleTree<K, V>::find(const K &key) const {
    if (empty())
    {
        throw ElementNotFoundException("key is not in the tree");
    }

    Node *current{root};
    while (current != nullptr) {
        if (key == current->key)
        {
            return current->value;
        }
        else if (key < current->key)
        {
            current = current->left;
        }
        else 
        {
            current = current->right;
        }
    }
    throw ElementNotFoundException("key is not in the tree");
}
template <typename K, typename V>
void CrumpleTree<K, V>::calculateShape(Node *node, int &leftShape, int &rightShape)
{
    int leftChildLevel = (node->left == nullptr) ? 0 : node->left->level;
    int rightChildLevel = (node->right == nullptr) ? 0 : node->right->level;
    leftShape = node->level - leftChildLevel;
    rightShape = node->level - rightChildLevel;
}

template <typename K, typename V>
void CrumpleTree<K, V>::reArrange(Node *&parent, Node *&child, Node *&prevChild, bool leftNeedReArrange, bool rightNeedReArrange) {
    // left rising
    if (leftNeedReArrange)
    {
        /* note cases:
            prevChild -> 18
            child -> 12
            parent -> 19
        */ 
        /* note cases:
            prevChild -> 15
            child -> 13
            parent -> 17
        */ 
        child->right = prevChild->left;
        if (prevChild->left != nullptr) // for rearrange @left subtree
        {
            prevChild->left->parent = child;  // change the parent for the LC of prev child node
        }
        if (parent->parent != nullptr) // for rearrange @right subtree
        {
            parent->parent->right = prevChild;
        }
        prevChild->left = child;

        parent->left = prevChild->right; 
        prevChild->right = parent;
    }
    // right rising
    else if (rightNeedReArrange)
    {
        /* note cases:
            prevChild -> 22
            child -> 28
            parent -> 21
        */ 

        child->left = prevChild->right;
        if (prevChild->right != nullptr) // for rearrange @right subtree
        {
            prevChild->right->parent = child;  // change the parent for the RC of prev child node
        }
        if (parent->parent != nullptr) // vice-vera
        {
            parent->parent->left = prevChild;
        }
        prevChild->right = child;

        parent->right = prevChild->left; 
        prevChild->left = parent;        
    }
    prevChild->level++;
    parent->level--;
    child->level--;
    
    prevChild->parent = parent->parent;
    child->parent = prevChild;
    parent->parent = prevChild;
    if (parent == root)
    {
        root = prevChild;
    }
}

template <typename K, typename V>
void CrumpleTree<K, V>::insert(const K &key, const V &value) {
    Node *newNode = new Node(key, value);

    if (root == nullptr)
    {
        newNode->level++;
        root = newNode;
        treeSize++;
        return;
    }

    Node *current{root};

    // Search phase and insert at level 0 (basic BST)
    while (current != nullptr)
    {
        if (key < current->key)
        {
            if (current->left == nullptr)
            {
                current->left = newNode;
                newNode->parent = current;
                break;                
            }
            current = current->left;
        }
        else 
        {
            if (current->right == nullptr) 
            {
                current->right = newNode;
                newNode->parent = current;
                break;
            }
            current = current->right;
        }
    }
    
    // Rebalance phase
    Node *parent{current};  // current is the parent of newly inserted node @ level 1
    Node *child{newNode};
    
    // Case 1
    if (child->level == 0)
    {
        child->level++;
    }

    Node *prevChild{};
    while (parent != nullptr)
    {
        int parentLeftShape = 0;
        int parentRightShape = 0;
        calculateShape(parent, parentLeftShape, parentRightShape);
        bool canMoveUpParent = (parentLeftShape != 2) && (parentRightShape != 2);
       
        int childLeftShape = 0;
        int childRightShape = 0;
        calculateShape(child, childLeftShape, childRightShape);
        bool leftNeedReArrange = (childLeftShape == 2 && childRightShape == 1 && child->right != nullptr);
        bool rightNeedReArrange = (childLeftShape == 1 && childRightShape == 2 && child->left != nullptr);

        if (child->level == parent->level)
        {
            if (!canMoveUpParent)
            {
                // Case 5
                if ((parent->left == child && leftNeedReArrange) || (parent->right == child && rightNeedReArrange))
                {
                    reArrange(parent, child, prevChild, leftNeedReArrange, rightNeedReArrange);
                }
                else 
                {
                    // Case 3 & 4
                    parent->level--;
                    if (parent->left == child)    // at left 
                    {
                        parent->left = child->right;
                        child->right = parent;

                        if (parent == root) 
                        {
                            root = child;
                        }
                        else 
                        {
                            parent->parent->left = child;
                        }
                        child->parent = parent->parent;
                        parent->parent = child;
                        if (parent->left != nullptr)
                        {
                            parent->left->parent = parent; // reset the child's parent to the new parent
                        }
                    }
                    else    // at right
                    {
                        parent->right = child->left;
                        child->left = parent;

                        if (parent == root) 
                        {
                            root = child;
                        }
                        else 
                        {
                            parent->parent->right = child;
                        }
                        child->parent = parent->parent;
                        parent->parent = child;
                        if (parent->right != nullptr)
                        {
                            parent->right->parent = parent; // reset the child's parent to the new parent
                        }
                    }
                }
            }
            else 
            {
                // Case 2
                parent->level++;
            }
        }
        prevChild = child;
        child = parent;
        parent = parent->parent;  // next parent of cur's parent
    }
    treeSize++;
}

template <typename K, typename V>
void CrumpleTree<K, V>::remove(const K &key) {
    // check if key in tree
    if (!contains(key) )
    {
        return;
    }

    // Downward phase
    Node *current{root};
    while (current != nullptr) {
        if (key == current->key)
        {
            break;
        }
        else if (key < current->key)
        {
            current = current->left;
        }
        else 
        {
            current = current->right;
        }
    }

    // if current is not leaf node, then swap
    while (current->left != nullptr || current->right != nullptr) {
        K curKey = current->key;
        V curVal = current->value;
        
        // find successor
        Node *successor{current->right};
        Node *predecessor{current->left};
        if (current->right != nullptr)  // leftmost of right subtree if node had right subtree
        {
            while (successor->left != nullptr) {
                successor = successor->left;
            }
            current->key = successor->key;
            current->value = successor->value;
            successor->key = curKey;
            successor->value = curVal;
            current = successor;
        }
        // if node doesn't have right subtree, then find predecessor
        else if (current->left != nullptr)
        {
            while (predecessor->right != nullptr) {
                predecessor = predecessor->right;
            }
            current->key = predecessor->key;
            current->value = predecessor->value;
            predecessor->key = curKey;
            predecessor->value = curVal;
            current = predecessor;
        }
    }
    
    // Rebalance phase
    Node *parent{current->parent};
    Node *child{current};
    while (parent != nullptr) {
        int parentLeftShape = 0;
        int parentRightShape = 0;
        calculateShape(parent, parentLeftShape, parentRightShape);

        // Case 1A
        if (((parentLeftShape == 1 && parentRightShape == 1) || (parentLeftShape == 1 && parentRightShape == 2) || (parentLeftShape == 2 && parentRightShape == 1)) && child->key == key)
        {
            // both left and right
            if (parent->left == child)
            {
                parent->left = child->left;
            }
            else 
            {
                parent->right = child->right;
            }
            delete child;

            // Case 1B
            calculateShape(parent, parentLeftShape, parentRightShape);
            if (parentLeftShape == 2 && parentRightShape == 2)
            {
                parent->level--;
            }
            // break;
        }
        
        // Case 2
        else if ((parentLeftShape == 2 && parentRightShape == 2) && child->key == key)
        {     
            // both left and right
            if (parent->left == child)
            {
                parent->left = child->left;   // might have parent ptr assgining problem here
            }
            else 
            {
                parent->right = child->right;
            }
            delete child;
            parent->level--;
        }

        else if ((parentLeftShape == 3 && parentRightShape == 1)) // left falling
        {
            // Case 3 
            int leftShape = 0;
            int rightShape = 0;
            calculateShape(parent->right, leftShape, rightShape);
            if (leftShape == 1 && rightShape == 1)
            {
                Node *rightChild = parent->right;

                parent->right = rightChild->left;
                rightChild->left->parent = parent;  // changing the parent of old LC
                rightChild->left = parent;
                
                parent->level--;
                rightChild->level++;
                
                rightChild->parent = parent->parent;
                parent->parent = rightChild;

                // reassign left ptr for parent that originally point to old node
                if (parent->parent != nullptr)
                {
                    rightChild->parent->left = rightChild;
                }
            }
        }
        else if (parentLeftShape == 1 && parentRightShape == 3) // right falling
        {
            int leftShape = 0;
            int rightShape = 0;
            calculateShape(parent->right, leftShape, rightShape);
            if (leftShape == 1 && rightShape == 1)
            {
                Node *leftChild = parent->left;
                
                parent->left = leftChild->right;
                leftChild->right->parent = parent;  // changing the parent of old RC
                leftChild->right = parent;
                
                parent->level--;
                leftChild->level++;
                
                leftChild->parent = parent->parent;
                parent->parent = leftChild;

                // reassign right ptr for parent that originally point to old node
                if (parent->parent != nullptr)
                {
                    leftChild->parent->right = leftChild;
                }
            }
        }

        child = parent;
        parent = parent->parent;
    }
    treeSize--;
}

template <typename K, typename V>
void CrumpleTree<K, V>::recursiveInOrder(Node *current, std::vector<K> &allKeys) const {
    if (current == nullptr)
    {
        return;
    }
    recursiveInOrder(current->left, allKeys);
    allKeys.push_back(current->key);
    recursiveInOrder(current->right, allKeys);
}

template <typename K, typename V>
void CrumpleTree<K, V>::recursivePreOrder(Node *current, std::vector<K> &allKeys) const {
    if (current == nullptr)
    {
        return;
    }
    allKeys.push_back(current->key);
    recursivePreOrder(current->left, allKeys);
    recursivePreOrder(current->right, allKeys);
}

template <typename K, typename V>
void CrumpleTree<K, V>::recursivePostOrder(Node *current, std::vector<K> &allKeys) const {
    if (current == nullptr)
    {
        return;
    }
    recursivePostOrder(current->left, allKeys);
    recursivePostOrder(current->right, allKeys);
    allKeys.push_back(current->key);
}

template <typename K, typename V>
std::vector<K> CrumpleTree<K, V>::inOrder() const {
    std::vector<K> allKeys;
    Node *current{root};
    recursiveInOrder(current, allKeys);
    return allKeys;
}

template <typename K, typename V>
std::vector<K> CrumpleTree<K, V>::preOrder() const {
    std::vector<K> allKeys;
    Node *current{root};
    recursivePreOrder(current, allKeys);
    return allKeys;
}

template <typename K, typename V>
std::vector<K> CrumpleTree<K, V>::postOrder() const {
    std::vector<K> allKeys;
    Node *current{root};
    recursivePostOrder(current, allKeys);
    return allKeys;
}

}  // namespace shindler::ics46::project4

#endif
