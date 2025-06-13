/**
 * @brief A generic node class for use in binary and red-black trees.
 * 
 * @tparam T The type of object stored in the node. Must have a `key` field.
 */
template<class T>
class Node {
public:
    T object;                         ///< A single object of type T (not used in main logic, kept for compatibility).
    std::string key;                  ///< The key used to identify this node (typically from the first object).
    std::vector<T> objects;           ///< A list of objects with the same key.
    int color = 2;                    ///< Node color for Red-Black Tree: 0 = black, 1 = red, 2 = null/uninitialized.
    Node<T>* parent = nullptr;        ///< Pointer to the parent node.
    Node<T>* left = nullptr;          ///< Pointer to the left child node.
    Node<T>* right = nullptr;         ///< Pointer to the right child node.

    /**
     * @brief Adds an object to the node's object list.
     * 
     * @param object The object to add.
     */
    void add_object(T object) {
        objects.resize(objects.size() + 1);
        objects[objects.size() - 1] = object;
    }
};
