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
    std::shared_ptr<Node> next_node = nullptr;

    while (current_node != nullptr) {
      next_node = current_node->next;
      current_node->next = prev_node;
      current_node->prev = next_node;
      prev_node = current_node;
      current_node = next_node;
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