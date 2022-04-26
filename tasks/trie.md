
## Префиксное дерево
Реализуйте класс префиксного дерева. Сравните его производительность с std::map<std::string, T>. Продемонстрируйте работу вашего класса (необходимо вызвать каждый метод). Проверьте ваш код на утечки памяти. Реализуйте юнит-тесты к классу.

```cpp
template <class T, class KeyType=wchar_t>
class trie
{
public:
    trie();
    trie(const trie&);
    ~trie();
    
    operator=
    
    begin
    end
    
    size
    empty
    
    insert
    erase
    swap
    clear
    
    find
    get_value
    find_longest_prefix
    
    struct search_iterator
    {
        bool get_value(T* out_value = nullptr) const;
        bool has_value() const;
        bool advance(const std::basic_string<KeyType>& sub_key);
        bool advance(const KeyType* sub_key);
    };
};
```
