/**
 * @brief Red-Black Tree implementation.
 * 
 * @tparam T Type of elements stored in the tree.
 */
template<class T>
class RBTree {
public:
    Node<T>* root = nullptr; ///< Root of the red-black tree
    int elements; ///< Number of elements (not directly used)

    /**
     * @brief Destructor. Recursively deletes all nodes in the tree.
     */
    ~RBTree(){
        deleteTree_rec(root);
    }

    /**
     * @brief Recursively deletes all nodes in the tree starting from the given node.
     * 
     * @param node The node to start deletion from.
     */
    void deleteTree_rec(Node<T>* node)
    {
        if (node != nullptr) {
            deleteTree_rec(node->left);
            deleteTree_rec(node->right);
            delete node;
        }
    }

    /**
     * @brief Performs a left rotation around the given node.
     * 
     * @param node Reference to the node to rotate.
     */
    void rotateLeft(Node<T>*& node)
    {
        Node<T>* child = node->right;
        node->right = child->left;
        if (node->right != nullptr)
            node->right->parent = node;
        child->parent = node->parent;
        if (node->parent == nullptr)
            root = child;
        else if (node == node->parent->left)
            node->parent->left = child;
        else
            node->parent->right = child;
        child->left = node;
        node->parent = child;
    }

    /**
     * @brief Performs a right rotation around the given node.
     * 
     * @param node Reference to the node to rotate.
     */
    void rotateRight(Node<T>*& node)
    {
        Node<T>* child = node->left;
        node->left = child->right;
        if (node->left != nullptr)
            node->left->parent = node;
        child->parent = node->parent;
        if (node->parent == nullptr)
            root = child;
        else if (node == node->parent->left)
            node->parent->left = child;
        else
            node->parent->right = child;
        child->right = node;
        node->parent = child;
    }

    /**
     * @brief Fixes red-black tree properties after insertion.
     * 
     * @param node Newly inserted node.
     */
    void fixInsert(Node<T>*& node)
    {
        Node<T>* parent = node->parent;
        Node<T>* grandparent = nullptr;
        if (parent != nullptr) {
            grandparent = node->parent->parent;
        }

        while (node != root && node->color == 1 && node->parent->color == 1) {
            parent = node->parent;
            grandparent = parent->parent;

            if (parent == grandparent->left) {
                Node<T>* uncle = grandparent->right;

                if (uncle != nullptr && uncle->color == 1) {
                    grandparent->color = 1;
                    parent->color = 0;
                    uncle->color = 0;
                    node = grandparent;
                } else {
                    if (node == parent->right) {
                        rotateLeft(parent);
                        node = parent;
                        parent = node->parent;
                    }
                    rotateRight(grandparent);
                    std::swap(parent->color, grandparent->color);
                    node = parent;
                }
            } else {
                Node<T>* uncle = grandparent->left;

                if (uncle != nullptr && uncle->color == 1) {
                    grandparent->color = 1;
                    parent->color = 0;
                    uncle->color = 0;
                    node = grandparent;
                } else {
                    if (node == parent->left) {
                        rotateRight(parent);
                        node = parent;
                        parent = node->parent;
                    }
                    rotateLeft(grandparent);
                    std::swap(parent->color, grandparent->color);
                    node = parent;
                }
            }
        }

        root->color = 0;
    }

    /**
     * @brief Inserts a new object into the red-black tree.
     * 
     * @param object Object to insert.
     */
    void insert(T object)
    {
        Node<T>* node = new Node<T>;
        node->add_object(object);
        node->color = 1;

        Node<T>* parent = nullptr;
        Node<T>* current = root;

        while (current != nullptr) {
            parent = current;

            if (node->objects[0].key < current->objects[0].key) {
                current = current->left;
            } else if (node->objects[0].key > current->objects[0].key) {
                current = current->right;
            } else {
                break;
            }
        }

        node->parent = parent;

        if (parent == nullptr) {
            root = node;
        } else if (node->objects[0].key < parent->objects[0].key) {
            parent->left = node;
        } else if (node->objects[0].key > parent->objects[0].key) {
            parent->right = node;
        } else {
            parent->add_object(node->objects[0]);
            delete node;
        }

        fixInsert(node);
    }

    /**
     * @brief Prints the red-black tree to the console (for debugging).
     * 
     * @param node Current node.
     * @param level Current depth level (used for indentation).
     */
    void printTree(Node<T>* node, int level)
    {
        for (int i = 0; i < level; i++) {
            std::cout << "     ";
        }
        std::cout << node->objects[0] << " " << node->color << std::endl;

        if (node->left != nullptr) {
            printTree(node->left, level + 1);
        }

        if (node->right != nullptr) {
            printTree(node->right, level + 1);
        }
    }

    /**
     * @brief Searches for a node by key and returns all associated objects.
     * 
     * @param key Key to search for.
     * @return Pointer to a vector of objects if found, otherwise nullptr.
     */
    std::vector<T>* find_object(std::string key) {
        Node<T>* current = root;

        while (current != nullptr) {
            if (key > (current->objects[0]).key) {
                current = current->right;
            } else if (key < (current->objects[0]).key) {
                current = current->left;
            } else {
                return &current->objects;
            }
        }

        return nullptr;
    }
};
