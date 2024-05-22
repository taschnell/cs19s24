/**
 * @file cs19_linked_list_smart_pointers.h
 * @author Jeffrey Bergamini for CS 19, jeffrey.bergamini@cabrillo.edu
 *
 * Smart pointers allow us to avoid manual memory management. Note the lack of a
 * destructor!
 *
 */
#ifndef CS19_LINKED_LIST_H_
#define CS19_LINKED_LIST_H_

#include <initializer_list>
#include <iostream>
#include <memory>  // for smart pointer types: std::(unique|shared|weak)_ptr

namespace cs19 {

template <typename T>
class LinkedList {
  // private members
  struct Node {
    explicit Node(T data) : data(data) {
      // N/A
    }
    // We can uncomment this to get some info on when nodes are automatically
    // destroyed ~Node() {
    //   std::cerr << "Node@" << this << " (" << this->data
    //             << ") is in the process of being destroyed\n";
    // }
    T data;
    std::shared_ptr<Node> next = nullptr;  // forward link is a `shared_ptr`
    std::weak_ptr<Node> prev;              // backward link is a `weak_ptr` to avoid cyclical refs
  };
  std::shared_ptr<Node> head_ = nullptr;  // will share ownership of the head node
  std::shared_ptr<Node> tail_ = nullptr;  // will share ownership of the tail node
  std::size_t size_ = 0;

 public:
  class Iterator {
   public:
    friend LinkedList;
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using difference_type = int;
    using pointer = T *;
    using reference = T &;
    // Default constructor
    Iterator() : node_(nullptr) {}
    // Copy constructor
    Iterator(const Iterator &other) : node_(other.node_) {}
    Iterator(std::shared_ptr<Node> node) : node_(node) {}
    // Copy constructor
    Iterator &operator=(const Iterator &that) {
      this->node_ = that.node_;
      return *this;
    }

    // Prefix increment
    Iterator &operator++() {
      if (node_) node_ = node_->next;
      return *this;
    }
    // Postfix increment
    Iterator operator++(int) {
      Iterator tmp(*this);
      this->operator++();
      return tmp;
    }

    // Prefix decrement
    Iterator &operator--() {
      if (node_) node_ = node_->prev.lock();
      return *this;
    }
    // Postfix decrement
    Iterator operator--(int) {
      Iterator tmp(*this);
      this->operator--();
      return tmp;
    }
    // Inequality
    bool operator!=(const Iterator &that) const { return this->node_ != that.node_; }
    // Equality
    bool operator==(const Iterator &that) const { return this->node_ == that.node_; }
    // lvalue dereference
    T &operator*() const { return node_->data; }
    // referring
    T *operator->() { return &(node_->data); }

   private:
    std::shared_ptr<Node> node_;
  };

  LinkedList() {
    // N/A
  }
  LinkedList(const LinkedList &that) {
    // Get a copy of that.head_ pointer (temporarily increments that.head_'s use
    // count)
    std::shared_ptr<Node> node = that.head_;
    while (node) {
      this->push_back(node->data);
      node = node->next;  // decrements use count of current node, increments use
                          // count of next node
    }
  }
  // Move constructor (used with std::move, e.g. `new_list_var =
  // std::move(old_list_var)`). Also used automatically by compiler for copy
  // elision in some cases.
  LinkedList(const LinkedList &&that) : head_(that.head_), tail_(that.tail_), size_(that.size_) {
    // We have transferred another list's pointers to this list (and we now own
    // them)
  }
  LinkedList(std::initializer_list<T> list) {
    for (auto &&val : list) this->push_back(val);
  }
  // Range Constructor
  template <typename InputIterator>
  LinkedList(InputIterator first, InputIterator last) {
    for (; first != last; ++first) {
      this->push_back(*first);
    }
  }

  friend std::ostream &operator<<(std::ostream &out, const LinkedList &l) {
    out << "[";
    // Technically we increment and decrement use counts on each node as we
    // traverse the list:
    for (std::shared_ptr<Node> cur = l.head_; cur; cur = cur->next) {
      out << cur->data;
      if (cur->next) out << ", ";
    }
    out << ']';
    return out;
  }
  /**
   * @brief Returns an iterator pointing to the first element in this list.
   *
   * Notice that, unlike `front()`, which returns a reference to the first element, this function
   * returns a bidirectional iterator pointing to it.
   *
   * If this list is empty, the returned iterator value shall not be dereferenced.
   *
   * @return An iterator to the beginning of the sequence.
   */
  Iterator begin() { return Iterator(head_); }

  /**
   * @brief Returns an iterator referring to the past-the-end element in this list.
   *
   * The past-the-end element is the theoretical element that would follow the last element in the
   * list. It does not point to any element, and thus shall not be dereferenced.
   *
   * Because the ranges used by functions of the standard library do not include the element pointed
   * by their closing iterator, this function is often used in combination with `begin()` to
   * specify a range including all the elements in the list.
   *
   * If this list is empty, this function returns the same as `begin()`.
   *
   * @return An iterator to the element past the end of the sequence.
   */
  Iterator end() { return Iterator(nullptr); }

  /**
   * Extends this list by inserting a new element before the element at the specified position.
   *
   * @param position Position in the list where the new element is inserted.
   * @param val Value to be copied to the inserted element.
   * @return An iterator that points to the newly inserted element.
   */
  Iterator insert(Iterator position, const T &val) {
    auto node_new = std::make_shared<Node>(val);
    if (position == begin()) {
      node_new->next = head_;
      if (head_) {
        head_->prev = node_new;
      }
      head_ = node_new;
      if (!tail_) {
        tail_ = node_new;
      } else if (position == end()) {
        node_new->prev = tail_;
        if (tail_) {
          tail_->next = node_new;
        }
        tail_ = node_new;
        if (!head_) {
          head_ = node_new;
        } else {
          auto pos_node = position.node_;
          node_new->next = pos_node;
          node_new->prev = pos_node->prev;
          if (auto prev_node = pos_node->prev.lock()) {
            prev_node->next = node_new;
          }
          pos_node->prev = node_new;
        }

        ++size_;
        return Iterator(node_new);
      }
    }
    return Iterator(position);
  }

  /**
   * Extends this list by inserting new elements before the element at the specified position.
   *
   * @param position Position in the list where the new elements are inserted.
   * @param n Number of elements to insert. Each element is initialized to a copy of `val`.
   * @param val Value to be copied to the inserted elements.
   * @return An iterator that points to the first of the newly inserted elements.
   */
  Iterator insert(Iterator position, std::size_t n, const T &val) {
    Iterator last = position;
    for (size_t i = 0; i < n; ++i) {
      last = insert(position, val);
    }
    return last;
  }

  /**
   * Extends this list by inserting new elements in the range [first,last) before the element at the
   * specified position.
   *
   * @param position Position in the list where the new elements are inserted.
   * @param first An iterator that points to the first value to be inserted.
   * @param last An iterator that points to the value after the last value to be inserted.
   * @return An iterator that points to the first of the newly inserted elements.
   */
  template <typename InputIterator>
  Iterator insert(Iterator position, InputIterator first, InputIterator last) {
    for (; first != last; ++first) {
      position = insert(position, *first);
    }
    return position;
  }

  /**
   * Extends this list by inserting new elements from an initializer list at the specified position.
   *
   * @param position Position in the list where the new elements are inserted.
   * @param init_list The list of values to be inserted.
   * @return An iterator that points to the first of the newly inserted elements.
   */
  Iterator insert(Iterator position, std::initializer_list<T> init_list) {
    for (auto element : init_list) {
      position = insert(position, element);
    }
    return position;
  }

  /**
   * Removes from this list a single element at the specified position.
   *
   * @param position Iterator pointing to a single element to be removed from the list.
   * @return An iterator pointing to the element that followed the last element erased by the
   * function call. This is the list end if the operation erased the last element in the
   * sequence.
   */
  Iterator erase(Iterator position) {
    if (position == end()) {
      return end();
    }
    auto node_to_remove = position.node_;
    auto node_next = node_to_remove->next;

    if (node_to_remove == head_) {
      head_ = node_next;
      if (head_) {
        head_->prev.reset();
      }
    } else {
      auto prev_node = node_to_remove->prev.lock();
      prev_node->next = node_next;
    }

    if (node_to_remove == tail_) {
      tail_ = node_to_remove->prev.lock();
    } else {
      if (node_next) {
        node_next->prev = node_to_remove->prev;
      }
    }

    --size_;
    return Iterator(node_next);
  }

  /**
   * removes from this list a range of elements (`[first,last)`).
   *
   * @param first An iterator that points to the first value to be removed.
   * @param last An iterator that points to the value after the last value to be removed.
   * @return An iterator pointing to the element that followed the last element erased by the
   * function call. This is the list end if the operation erased the last element in the sequence.
   */
  Iterator erase(Iterator first, Iterator last) {
    while (first != last) {
      first = erase(first);
    }
    return last;
  };

  /**
   * Transfers all elements from another list into this list, inserting them at `position`. The
   * operation does not involve the construction or destruction of any element.
   *
   * @param position An iterator that points to the position in this list where elements are
   * inserted.
   * @param that The list from which to copy elements.
   */
  void splice(Iterator position, LinkedList &that) {
    if (that.size_ == 0) return;

    if (position == begin()) {
      if (head_) {
        head_->prev = that.tail_;
      }
      that.tail_->next = head_;
      head_ = that.head_;
    } else if (position == end()) {
      if (tail_) {
        tail_->next = that.head_;
      }
      that.head_->prev = tail_;
      tail_ = that.tail_;
    } else {
      auto pos_node = position.node_;
      auto prev_node = pos_node->prev.lock();
      prev_node->next = that.head_;
      that.head_->prev = prev_node;
      that.tail_->next = pos_node;
      pos_node->prev = that.tail_;
    }
    size_ += that.size_;
    that.head_ = that.tail_ = nullptr;
    that.size_ = 0;
  }

  /**
   * Transfers one element from another list into this list, inserting it at `position`. The
   * operation does not involve the construction or destruction of any element.
   *
   * @param position An iterator that points to the insertion position in this list.
   * @param that The list from which to copy an element.
   * @param that_position An iterator that points to the element to transfer from the other list to
   * this list.
   */
  void splice(Iterator position, LinkedList &that, Iterator that_position) {
    if (that.size_ == 0 || that_position == that.end()) return;

    auto node_to_transfer = that_position.node_;
    if (node_to_transfer == that.head_) {
      that.head_ = node_to_transfer->next;
      if (that.head_) {
        that.head_->prev.reset();
      }
    } else {
      auto prev_node = node_to_transfer->prev.lock();
      prev_node->next = node_to_transfer->next;
      if (node_to_transfer->next) {
        node_to_transfer->next->prev = prev_node;
      }
    }

    if (node_to_transfer == that.tail_) {
      that.tail_ = node_to_transfer->prev.lock();
    }

    --that.size_;

    if (position == begin()) {
      node_to_transfer->next = head_;
      if (head_) {
        head_->prev = node_to_transfer;
      }
      head_ = node_to_transfer;
    } else if (position == end()) {
      node_to_transfer->prev = tail_;
      if (tail_) {
        tail_->next = node_to_transfer;
      }
      tail_ = node_to_transfer;
    } else {
      auto pos_node = position.node_;
      node_to_transfer->next = pos_node;
      node_to_transfer->prev = pos_node->prev;
      if (auto prev_node = pos_node->prev.lock()) {
        prev_node->next = node_to_transfer;
      }
      pos_node->prev = node_to_transfer;
    }

    ++size_;
  } /**
     * Transfers the range of elements `[first,last)` from another list into this list, inserting it
     * at `position`. The operation does not involve the construction or destruction of any element.
     *
     * @param position An iterator that points to the insertion position in this list.
     * @param that The list from which to copy a range of elements.
     * @param first An iterator that points to the first value to be transferred.
     * @param last An iterator that points to the value after the last value to be transferred.
     */
  void splice(Iterator position, LinkedList &that, Iterator first, Iterator last) {
    while (first != last) {
      auto next = std::next(first);
      splice(position, that, first);
      first = next;
    }
  }

  void push_back(const T &val) {
    // std::make_shared: alternative to:
    // auto new_node = std::shared_ptr<Node>(new Node(val));
    auto new_node = std::make_shared<Node>(val);  // new_node has an initial use count of 1
    if (this->size_ == 0) {
      this->head_ = this->tail_ = new_node;
    } else {
      this->tail_->next = new_node;                       // forward link: shared_ptr (use count: 2)
      new_node->prev = std::weak_ptr<Node>(this->tail_);  // backward link: weak_ptr
      this->tail_ = new_node;                             // use count 3 (down to 2 when local var
                                                          // `new_node` is out of scope)
    }
    ++this->size_;
  }
  void push_front(const T &val) {
    auto new_node = std::make_shared<Node>(val);

    if (this->size_ == 0) {
      this->head_ = this->tail_ = new_node;
    } else {
      new_node->next = this->head_;
      this->head_->prev = std::weak_ptr<Node>(new_node);
      this->head_ = new_node;
    }
    ++this->size_;
  }

  T pop_back() {
    if (this->size_ == 0) {
      throw std::logic_error("No List :(");
    }

    T to_return = this->tail_->data;
    if (this->size_ == 1) {
      this->head_ = this->tail_ = nullptr;
    } else {
      // weak_ptr::lock() temporarily promotes weak_ptr to shared_ptr (otherwise
      // can't dereference):
      this->tail_->prev.lock()->next = nullptr;
      this->tail_ = this->tail_->prev.lock();
    }
    --this->size_;
    return to_return;
  }
  T pop_front() {
    if (this->size_ == 0) {
      throw std::logic_error("No List :(");
    }

    T to_return = this->head_->data;
    if (this->size_ == 1) {
      this->head_ = this->tail_ = nullptr;
    } else {
      this->head_->next->prev = std::weak_ptr<Node>();

      this->head_ = this->head_->next;
    }

    --this->size_;
    return to_return;
  }

  std::size_t size() const { return this->size_; }

  bool empty() const { return this->size_ == 0; }

  T front() const {
    if (size_ == 0) {
      throw std::logic_error("No List :(");
    }
    return this->head_->data;
  }

  T back() const {
    if (size_ == 0) {
      throw std::logic_error("No List :(");
    }
    return this->tail_->data;
  }

  void clear() {
    head_ = tail_ = nullptr;
    size_ = 0;
  }
  void reverse() {
    if (size_ <= 1) {
      return;
    }

    std::shared_ptr<Node> prev_node = nullptr;
    std::shared_ptr<Node> current_node = head_;
    std::shared_ptr<Node> node_next = nullptr;

    while (current_node != nullptr) {
      node_next = current_node->next;
      current_node->next = prev_node;
      current_node->prev = node_next;
      prev_node = current_node;
      current_node = node_next;
    }

    std::swap(head_, tail_);
  }
  void resize(std::size_t n) {
    if (n < size_) {
      while (size_ > n) {
        pop_back();
      }
    } else if (n > size_) {
      for (std::size_t i = size_; i < n; ++i) {
        push_back(T());  // Default-constructed element of type T
      }
    }
  }

  void resize(std::size_t n, const T &fill_value) {
    if (n < size_) {
      while (size_ > n) {
        pop_back();
      }
    } else if (n > size_) {
      for (std::size_t i = size_; i < n; ++i) {
        push_back(T(fill_value));  // Default-constructed element of type T
      }
    }
  }

  void unique() {
    if (size_ <= 1) {
      // no duplicates if list is size 1 or less
      return;
    }

    std::shared_ptr<Node> current_node = head_;

    while (current_node->next != nullptr) {
      if (current_node->data == current_node->next->data) {
        current_node->next = current_node->next->next;
        if (current_node->next != nullptr) {
          current_node->next->prev = current_node;
        } else {
          tail_ = current_node;
        }
        --size_;
      } else {
        current_node = current_node->next;
      }
    }
  }
  void remove(const T &val) {
    std::shared_ptr<Node> current_node = head_;

    while (current_node != nullptr) {
      if (current_node->data == val) {
        if (current_node == head_) {
          head_ = current_node->next;
          if (head_ != nullptr) {
            head_->prev.reset();
          } else {
            tail_ = nullptr;
          }
        } else if (current_node == tail_) {
          tail_ = current_node->prev.lock();
          tail_->next = nullptr;
        } else {
          current_node->prev.lock()->next = current_node->next;
          current_node->next->prev = current_node->prev;
        }
        --size_;
      }
      current_node = current_node->next;
    }
  }
  // Opperators
  LinkedList &operator=(std::initializer_list<T> init_list) {
    clear();

    for (const auto &val : init_list) {
      push_back(val);
    }

    return *this;
  }
  LinkedList &operator=(const LinkedList<T> &another) {
    clear();

    std::shared_ptr<Node> current = another.head_;
    while (current) {
      push_back(current->data);
      current = current->next;
    }

    return *this;
  }
  bool operator==(const LinkedList<T> &other) const {
    if (size_ != other.size_) {
      return false;
    }

    std::shared_ptr<Node> current_this = head_;
    std::shared_ptr<Node> current_other = other.head_;

    while (current_this && current_other) {
      if (current_this->data != current_other->data) {
        return false;
      }
      current_this = current_this->next;
      current_other = current_other->next;
    }

    return true;
  }
  bool operator!=(const LinkedList<T> &other) const { return !(*this == other); }
};

}  // namespace cs19

#endif  // CS19_LINKED_LIST_SMART_POINTERS_H_s