/**
 * @brief Hash table implementation using open addressing with linear probing.
 * 
 * @tparam T Type of elements stored. Must have a `key` field of type std::string.
 */
template<class T>
class TableHash
{
public:
    /**
     * @brief Finds the list of elements with the specified key.
     * 
     * @param key The key to search for.
     * @return Pointer to the vector of matching elements.
     */
    std::vector<T>* find(std::string key);

    /**
     * @brief Constructs a new TableHash object with default size.
     */
    TableHash();

    /**
     * @brief Destroys the TableHash object.
     */
    ~TableHash();

    /**
     * @brief Adds an object to the hash table.
     * 
     * @param object The object to add.
     */
    void add(T object);

    /**
     * @brief Returns the number of unique keys stored in the table.
     * 
     * @return The count of keys.
     */
    int get_count();

    int size = 100; ///< Current capacity of the hash table

private:
    /**
     * @brief Doubles the size of the table and rehashes all elements.
     */
    void resize();

    std::vector<std::vector<T>> items; ///< Buckets storing elements per key
    int count = 0; ///< Number of unique keys in the table
    int a = 9; ///< Base used in custom hash function (currently unused)
};

/**
 * @brief Computes integer exponentiation.
 * 
 * @param a Base value.
 * @param power Exponent value.
 * @return a raised to the power.
 */
size_t pow(int a, int power)
{
    if (power == 1)
        return a;
    if (power == 0)
        return 1;
    if (power & 1)
        return pow(a, power - 1) * a;
    return pow(a, power / 2) * pow(a, power / 2);
}

/**
 * @brief Computes a polynomial hash of a string.
 * 
 * @param s The string to hash.
 * @param a Base value for polynomial hashing.
 * @param m Modulo value.
 * @return Hash value.
 */
size_t hash(std::string s, int a, int m)
{
    size_t ans = 0;
    int size = s.size();
    for (int i = 0; i < size; i++)
    {
        ans += ((int)s[i] * pow(a, size - 1 - i)) % m;
    }
    ans %= m;
    return ans;
}

template<class T>
TableHash<T>::TableHash() {
    items.resize(size);
}

template<class T>
TableHash<T>::~TableHash() {
}

template<class T>
void TableHash<T>::resize() {
    size *= 2;
    std::vector<std::vector<T>> new_items;
    new_items.resize(size);
    for (int i = 0; i < size / 2; i++) {
        size_t h = std::hash<std::string>{}(items[i][0].key) % size;

        while (true) {
            if (new_items[h].empty()) {
                break;
            } else {
                h = (h + 1) % size;
            }
        }

        new_items[h].resize(items[i].size());

        for (int j = 0; j < items[i].size(); j++) {
            new_items[h][j] = items[i][j];
        }
    }
    items.clear();
    items = std::move(new_items);
}

template<class T>
void TableHash<T>::add(T object) {
    size_t h = std::hash<std::string>{}(object.key) % size;
    bool flag = true;

    if (count == size) {
        resize();
    }

    while (true) {
        if (items[h].empty()) {
            break;
        } else {
            if (items[h][0].key == object.key) {
                break;
            } else {
                h = (h + 1) % size;
            }
        }
    }

    if (items[h].empty()) {
        count += 1;
    }

    items[h].resize(items[h].size() + 1);
    items[h][items[h].size() - 1] = object;
}

template<class T>
std::vector<T>* TableHash<T>::find(std::string key) {
    size_t h = std::hash<std::string>{}(key) % size;
    for(int i = 0; i < size; i++) {
        if (!items[h].empty()){
            if (items[h][0].key == key) {
                break;
            }
            h = (h + 1) % size;
        }
    }
    return &items[h];
}

template<class T>
int TableHash<T>::get_count()
{
    return count;
}
