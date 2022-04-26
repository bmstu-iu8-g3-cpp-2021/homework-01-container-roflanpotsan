
## unordered_set
Реализуйте аналог стандартного контейнера std::unordered_set<Value, Hash, EqualKey>. Продемонстрируйте работу вашего класса (необходимо вызвать каждый метод). Проверьте ваш код на утечки памяти. Реализуйте юнит-тесты к классу.

```cpp
template <class T, class Hash, class EqualKey>
class unordered_set
{
public:
    unordered_set();
    ~unordered_set();
    unordered_set(const unordered_set&);
    unordered_set& operator=(const unordered_set&);
    
    begin
    end
    
    size
    empty
    
    has
    
    insert
    erase
    swap
    clear
    
    find
};
```
