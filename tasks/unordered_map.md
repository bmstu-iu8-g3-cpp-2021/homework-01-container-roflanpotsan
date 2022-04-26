
## unordered_map
Реализуйте аналог стандартного контейнера std::unordered_map<Key, Value, Hash, EqualKey>.  Продемонстрируйте работу вашего класса (необходимо вызвать каждый метод). Проверьте ваш код на утечки памяти. Реализуйте юнит-тесты к классу.

```cpp
template <class Key, class T, class Hash, class EqualKey>
class unordered_map
{
public:
    unordered_map();
    ~unordered_map();
    unordered_map(const unordered_map&);
    unordered_map& operator=(const unordered_map&);
    
    begin
    end
    
    size
    empty
    
    operator[]
    at
    
    insert
    erase
    swap
    clear
    
    find
};
```
