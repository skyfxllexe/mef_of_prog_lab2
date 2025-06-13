/**
 * @brief A generic binary search tree for storing objects with string keys.
 * 
 * @tparam T Type of elements stored. Must contain a `key` field of type std::string and support `add_object`.
 */
template<class T>
class BinTree {
public:
    Node<T>* root = nullptr; ///< Pointer to the root of the binary tree

    /**
     * @brief Inserts an object into the binary search tree.
     * 
     * If the key already exists, the object is added to the node's object list.
     * 
     * @param object The object to insert.
     */
    void insert(T object) {
        Node<T>* current = root;
        Node<T>* parent = nullptr;
        int flag_new_node = 1;
        while(current != nullptr) {
            parent = current;
            if(object.key > current->key) {
                current = current->right;
            }
            else if (object.key < current->key) {
                current = current->left;
            }
            else {
                current->add_object(object);
                return;
            }
        }
        current = new Node<T>;
        current->key = object.key;
        if(parent != nullptr) {
            current->parent = parent;
            if(current->key > parent->key) {
                parent->right = current;
            }
            else {
                parent->left = current;
            }
        }
        else {
            root = current;
        }
        current->add_object(object);
    }

    /**
     * @brief Finds all objects with the specified key.
     * 
     * @param key The key to search for.
     * @return A vector of matching objects. Returns an empty vector if key is not found.
     */
    std::vector<T> find(std::string key) {
        std::vector<T> ans;
        Node<T>* current = root;
        while(current != nullptr) {
            if(key > current->key) {
                current = current->right;
            }
            else if(key < current->key) {
                current = current->left;
            }
            else {
                int k = ans.size();
                ans.resize(ans.size() + current->objects.size());
                for(int i = k; i < ans.size(); i++) {
                    ans[i] = current->objects[i-k];
                }
                break;
            }
        }
        return ans;
    }

    /**
     * @brief Destructor that deletes the entire binary tree.
     */
    ~BinTree(){
        deleteTree_rec(root);
    }

    /**
     * @brief Recursively deletes nodes in the binary tree.
     * 
     * @param node Current node to delete.
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
     * @brief Recursively prints the tree contents starting from a node.
     * 
     * @param node The current node to print.
     * @param level The indentation level (used for visualizing the tree).
     */
    void printTree(Node<T>* node, int level)
    {
        for(int i = 0; i < level; i++) {
            std::cout << "     ";
        }
        std::cout << node->objects[0] << std::endl;
        if(node->left != nullptr) { printTree(node->left, level+1); }
        if(node->right != nullptr) { printTree(node->right, level + 1); }
    }
};
