## set
Реализуйте аналог стандартного контейнера std::set<Value, Cmp>. Продемонстрируйте работу вашего класса (необходимо вызвать каждый метод). Проверьте ваш код на утечки памяти. Реализуйте юнит-тесты к классу.

```cpp
template <class T, class Cmp>
class set
{
public:
    set();
    ~set();
    set(const set&);
    set& operator=(const set&);
    
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
