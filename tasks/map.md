## map
Реализуйте аналог стандартного контейнера std::map<Key, T, Cmp>. Продемонстрируйте работу вашего класса (необходимо вызвать каждый метод). Проверьте ваш код на утечки памяти. Реализуйте юнит-тесты к классу.

```cpp
template <class Key, class T, class Cmp>
class map
{
public:
    map();
    ~map();
    map(const map&);
    map& operator=(const map&);
    
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
