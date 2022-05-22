// Copyright 2022 roflanpotsan l1sZ@ya.ru

#ifndef TEMPLATE_MY_UNORDERED_SET_H
#define TEMPLATE_MY_UNORDERED_SET_H
#include <iostream>
#include <iterator>
template <class T>
class SimpleList {
  class Node {
    T data;
    Node *next = nullptr;

   public:
    Node() = default;
    explicit Node(const T &value) { this->data = value; }
    ~Node() = default;
    void assignNext(Node *new_next) { next = new_next; }
    T getData() { return this->data; }
    Node *getNext() { return this->next; }
  };

  Node *head;
  Node *tail;
  size_t size = 0;

 public:
  class Iterator {
    Node *pointer;

   public:
    explicit Iterator(Node *new_pointer) : pointer(new_pointer){};
    T operator*() { return pointer->getData(); }
    Node *operator->() { return pointer; }
    Iterator &operator++() {
      pointer = pointer->getNext();
      return *this;
    }
    friend bool operator==(const Iterator &a, const Iterator &b) {
      return a.pointer == b.pointer;
    };
    friend bool operator!=(const Iterator &a, const Iterator &b) {
      return a.pointer != b.pointer;
    };
  };

  SimpleList() {
    head = nullptr;
    tail = head;
  }

  ~SimpleList() {
    Node *current = this->head;
    while (current) {
      Node *next = current->getNext();
      delete current;
      current = next;
    }
    size = 0;
  }

  void push_back(const T &value) {
    auto *new_node = new Node(value);
    if (head == nullptr) {
      head = new_node;
      tail = new_node;
    } else {
      tail->assignNext(new_node);
      tail = new_node;
    }
    size++;
  }

  void erase(const T &value) {
    Node *current = head, *prev_current = head;
    if (current->getData() == value) {
      head = head->getNext();
      delete current;
      size--;
    } else {
      current = current->getNext();
      while (current) {
        if (current->getData() == value) {
          prev_current->assignNext(current->getNext());
          delete current;
          size--;
          break;
        }
        prev_current = current;
        current = current->getNext();
      }
    }
  }

  void erase(Iterator pos) {
    Node *current = head, *prev_current = head;
    if (current->getData() == *pos) {
      head = head->getNext();
      delete current;
      size--;
    } else {
      current = current->getNext();
      while (current) {
        if (current->getNext() == pos->getNext()) {
          prev_current->assignNext(current->getNext());
          delete current;
          size--;
          break;
        }
        prev_current = current;
        current = current->getNext();
      }
    }
  }

  bool empty() { return size == 0; }
  // size_t getSize() { return size; }
  Iterator begin() { return Iterator(head); }
  Iterator end() { return Iterator(nullptr); }
};

template <class T, class Hash = std::hash<T>,
          class EqualKey = std::equal_to<T>>  // Hash = hash_func, EqualKey =
                                              // check whether items
                                              // with identical hash are same
class unordered_set {
  SimpleList<T> *hash_table;
  size_t table_size = 0, el_count = 0;

  void rehash() {
    size_t new_size = table_size * 2;
    auto *new_table = new SimpleList<T>[new_size + 1];
    for (size_t i = 0; i <= new_size; i++) {
      new_table[i] = SimpleList<T>();
    }
    for (size_t i = 0; i < table_size; i++) {
      for (const auto &value : hash_table[i]) {
        new_table[Hash{}(value) % new_size].push_back(value);
      }
    }
    delete[] hash_table;
    hash_table = new_table;
    table_size = new_size;
  }

 public:
  class Iterator {
    typename SimpleList<T>::Iterator ptr =
        typename SimpleList<T>::Iterator(nullptr);
    SimpleList<T> *array, *begin;
    size_t max_size = 0;

   public:
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = const T *;
    using reference = const T &;
    using iterator_category = std::forward_iterator_tag;

    explicit Iterator(SimpleList<T> *new_begin, SimpleList<T> *arr,
                      size_t new_size) {
      begin = new_begin;
      array = arr;
      max_size = new_size;
      if (max_size == 0) {
        ptr = typename SimpleList<T>::Iterator(nullptr);
      } else {
        if ((*array).empty() && array != begin + max_size) {
          while (std::next(array) != begin + max_size &&
                 (*std::next(array)).empty()) {
            array = std::next(array);
          }
          array = std::next(array);
        }
        if (array == begin + max_size)
          if ((*array).empty())
            ptr = typename SimpleList<T>::Iterator(nullptr);
          else
            ptr = (*array).begin();
        else
          ptr = (*array).begin();
      }
    };

    ~Iterator() = default;
    T operator*() { return *ptr; }
    Iterator &operator++() {
      if (ptr != typename SimpleList<T>::Iterator(nullptr)) {
        if (ptr->getNext() != nullptr) {
          ++ptr;
        } else {
          while (std::next(array) != begin + max_size &&
                 (*std::next(array)).empty()) {
            array = std::next(array);
          }
          array = std::next(array);
          if (array == begin + max_size) {
            if ((*array).empty()) {
              ptr = typename SimpleList<T>::Iterator(nullptr);
            } else {
              ptr = (*array).begin();
            }
          } else
            ptr = (*array).begin();
        }
      }
      return *this;
    }

    const Iterator operator++(int) {
      Iterator tmp = *this;
      ++(*this);
      return tmp;
    }
    friend bool operator==(const Iterator &a, const Iterator &b) {
      return a.ptr == b.ptr;
    };
    friend bool operator!=(const Iterator &a, const Iterator &b) {
      return a.ptr != b.ptr;
    };
  };

  unordered_set() { hash_table = nullptr; }

  unordered_set(std::initializer_list<T> values) {
    table_size = values.size();
    hash_table = new SimpleList<T>[table_size + 1];
    for (const auto &value : values) {
      this->insert(value);
    }
  }

  unordered_set(const unordered_set &values) {
    table_size = values.capacity();
    hash_table = new SimpleList<T>[table_size + 1];
    for (auto i = values.begin(); i != values.end(); i++) {
      this->insert(*i);
    }
  }

  ~unordered_set() {
    delete[] hash_table;
    table_size = 0;
    el_count = 0;
  }

  unordered_set &operator=(const unordered_set<T> &values) {
    table_size = values.capacity();
    el_count = 0;
    delete[] hash_table;
    hash_table = new SimpleList<T>[table_size + 1];
    for (auto i = values.begin(); i != values.end(); ++i) {
      this->insert(*i);
    }
    return *this;
  }

  unordered_set &operator=(std::initializer_list<T> values) {
    table_size = values.size();
    el_count = 0;
    delete[] hash_table;
    hash_table = new SimpleList<T>[table_size + 1];
    for (const auto &value : values) {
      this->insert(value);
    }
    return *this;
  }

  bool operator==(const unordered_set<T> &new_set) {
    for (auto i = new_set.begin(); i != new_set.end(); ++i) {
      if (!(this->has(*i))) return false;
    }
    return true;
  }

  void insert(const T &value) {
    if (table_size == 0) {
      hash_table = new SimpleList<T>[2];
      table_size++;
      hash_table[0].push_back(value);
      el_count++;
    } else {
      if (this->has(value)) {
        return;
      }
      if (el_count == table_size) {
        rehash();
      }
      hash_table[Hash{}(value) % table_size].push_back(value);
      el_count++;
    }
  }

  template <class It>
  void insert(It first, It last) {
    while (first != last) {
      if (table_size == 0) {
        hash_table = new SimpleList<T>[2];
        table_size++;
        hash_table[0].push_back(*first);
        el_count++;
      } else {
        if (this->has(*first)) {
          return;
        }
        if (el_count == table_size) {
          rehash();
        }
        hash_table[Hash{}(*first) % table_size].push_back(*first);
        el_count++;
      }
      ++first;
    }
  }

  void insert(std::initializer_list<T> values) {
    for (const auto &value : values) {
      if (table_size == 0) {
        hash_table = new SimpleList<T>[2];
        table_size++;
        hash_table[0].push_back(value);
        el_count++;
      } else {
        if (this->has(value)) {
          return;
        }
        if (el_count == table_size) {
          rehash();
        }
        hash_table[Hash{}(value) % table_size].push_back(value);
        el_count++;
      }
    }
  }

  bool has(const T &value) const {
    if (!hash_table[Hash{}(value) % table_size].empty())
      for (auto el : hash_table[Hash{}(value) % table_size]) {
        if (EqualKey{}(el, value)) {
          return true;
        }
      }
    return false;
  }

  void clear() {
    delete[] hash_table;
    hash_table = nullptr;
    table_size = 0;
    el_count = 0;
  }

  [[nodiscard]] size_t size() const { return el_count; }
  [[nodiscard]] size_t capacity() const { return table_size; }
  bool empty() { return el_count == 0; }
  void erase(const T &value) {
    if (this->has(value)) {
      hash_table[Hash{}(value) % table_size].erase(value);
      el_count--;
    }
  }

  void erase(Iterator pos) {
    if (this->has(*pos)) {
      hash_table[Hash{}(*pos) % table_size].erase(*pos);
      el_count--;
    }
  }

  Iterator begin() const {
    return Iterator(hash_table, hash_table, table_size);
  }

  Iterator end() const {
    return Iterator(hash_table, hash_table + table_size, table_size);
  }

  Iterator find(const T &value) {
    if (this->has(value)) {
      Iterator it(hash_table, hash_table + Hash{}(value) % table_size,
                  table_size);
      while (!EqualKey{}(*it, value)) ++it;
      return it;
    } else {
      return this->end();
    }
  }
};

template <class T>
void swap(unordered_set<T> &a, unordered_set<T> &b) {
  unordered_set<T> temp = a;
  a = std::move(b);
  b = std::move(temp);
}

template <class T>
bool operator==(const unordered_set<T> &new_set,
                const unordered_set<T> &old_set) {
  for (auto i = new_set.begin(); i != new_set.end(); ++i) {
    if (!(old_set.has(*i))) return false;
  }
  return true;
}

template <class T>
bool operator!=(const unordered_set<T> &new_set,
                const unordered_set<T> &old_set) {
  return !(new_set == old_set);
}

#endif  // TEMPLATE_MY_UNORDERED_SET_H
