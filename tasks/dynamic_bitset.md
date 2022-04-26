
## dynamic_bitset
Реализуйте аналог контейнера boost::dynamic_bitset. Продемонстрируйте работу вашего класса (необходимо вызвать каждый метод). Проверьте ваш код на утечки памяти. Реализуйте юнит-тесты к классу.

```cpp
class dynamic_bitset
{
public:
    class reference
    {
    public:
        // An automatically generated copy constructor.

        reference& operator=(bool value);
        reference& operator=(const reference& rhs);

        reference& operator|=(bool value);
        reference& operator&=(bool value);
        reference& operator^=(bool value);
        reference& operator-=(bool value);

        bool operator~() const;
        operator bool() const;
        reference& flip();
    };

    explicit dynamic_bitset(size_type num_bits, unsigned long value = 0);

    dynamic_bitset(const dynamic_bitset& b);

    void swap(dynamic_bitset& b);

    dynamic_bitset& operator=(const dynamic_bitset& b);

    void clear();
    void pop_back();
    void push_back(bool bit);

    dynamic_bitset& operator&=(const dynamic_bitset& b);
    dynamic_bitset& operator|=(const dynamic_bitset& b);
    dynamic_bitset& operator^=(const dynamic_bitset& b);
    dynamic_bitset& operator-=(const dynamic_bitset& b);
    dynamic_bitset& operator<<=(size_type n);
    dynamic_bitset& operator>>=(size_type n);
    dynamic_bitset operator<<(size_type n) const;
    dynamic_bitset operator>>(size_type n) const;

    dynamic_bitset& set(size_type n, bool val = true);
    dynamic_bitset& set();
    dynamic_bitset& reset(size_type n);
    dynamic_bitset& reset();
    dynamic_bitset& flip(size_type n);
    dynamic_bitset& flip();
    bool all() const;
    bool any() const;
    bool none() const;
    dynamic_bitset operator~() const;
    size_type count() const noexcept;

    reference operator[](size_type pos);
    bool operator[](size_type pos) const;

    unsigned long to_ulong() const;

    size_type size() const noexcept;
    size_type num_blocks() const noexcept;
    bool empty() const noexcept;
};
```
