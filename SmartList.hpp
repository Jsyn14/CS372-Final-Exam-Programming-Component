#pragma once
// SmartList.hpp — singly linked list using std::unique_ptr
// Ownership is explicit; no raw delete anywhere. Iterator supports range-for.

#include <memory>
#include <utility>
#include <cstddef>
#include <initializer_list>
#include <stdexcept>

template <typename T>
class SmartList {
private:
    struct Node {
        T value;
        std::unique_ptr<Node> next;
        explicit Node(T v) : value(std::move(v)), next(nullptr) {}
    };

    std::unique_ptr<Node> head_{};
    Node* tail_{};                 
    std::size_t size_ = 0;

public:
    SmartList() = default;

    SmartList(std::initializer_list<T> init) {
        for (auto const& x : init) push_back(x);
    }

    ~SmartList() = default;
    SmartList(SmartList&&) noexcept = default;
    SmartList& operator=(SmartList&&) noexcept = default;

    SmartList(SmartList const& other) {              
        for (auto const& x : other) push_back(x);
    }
    SmartList& operator=(SmartList const& other) {
        if (this == &other) return *this;
        clear();
        for (auto const& x : other) push_back(x);
        return *this;
    }

    void clear() noexcept {
        head_.reset();        
        tail_ = nullptr;
        size_ = 0;
    }

    bool empty() const noexcept { return size_ == 0; }
    std::size_t size() const noexcept { return size_; }

    void push_front(T v) {
        auto n = std::make_unique<Node>(std::move(v));
        if (!head_) {
            tail_ = n.get();
        } else {
            n->next = std::move(head_);
        }
        head_ = std::move(n);
        ++size_;
    }

    void push_back(T v) {
        auto n = std::make_unique<Node>(std::move(v));
        Node* raw = n.get();
        if (!head_) {
            head_ = std::move(n);
            tail_ = raw;
        } else {
            tail_->next = std::move(n);
            tail_ = raw;
        }
        ++size_;
    }

    void pop_front() {
        if (!head_) throw std::out_of_range("pop_front on empty SmartList");
        head_ = std::move(head_->next);
        if (!head_) tail_ = nullptr;
        --size_;
    }

    T& front() {
        if (!head_) throw std::out_of_range("front on empty SmartList");
        return head_->value;
    }
    T const& front() const {
        if (!head_) throw std::out_of_range("front on empty SmartList");
        return head_->value;
    }

    class iterator {
        Node* cur_{};
    public:
        using value_type = T;
        using reference = T&;
        using pointer = T*;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

        iterator() = default;
        explicit iterator(Node* n) : cur_(n) {}
        reference operator*() const { return cur_->value; }
        pointer operator->() const { return &cur_->value; }
        iterator& operator++() { cur_ = cur_->next.get(); return *this; }
        iterator operator++(int){ auto tmp=*this; ++(*this); return tmp; }
        bool operator==(iterator const& rhs) const { return cur_ == rhs.cur_; }
        bool operator!=(iterator const& rhs) const { return cur_ != rhs.cur_; }
    };

    class const_iterator {
        Node const* cur_{};
    public:
        using value_type = T const;
        using reference = T const&;
        using pointer = T const*;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

        const_iterator() = default;
        explicit const_iterator(Node const* n) : cur_(n) {}
        reference operator*() const { return cur_->value; }
        pointer operator->() const { return &cur_->value; }
        const_iterator& operator++() { cur_ = cur_->next.get(); return *this; }
        const_iterator operator++(int){ auto tmp=*this; ++(*this); return tmp; }
        bool operator==(const_iterator const& rhs) const { return cur_ == rhs.cur_; }
        bool operator!=(const_iterator const& rhs) const { return cur_ != rhs.cur_; }
    };

    iterator begin() { return iterator(head_.get()); }
    iterator end() { return iterator(nullptr); }
    const_iterator begin() const { return const_iterator(head_.get()); }
    const_iterator end() const { return const_iterator(nullptr); }
    const_iterator cbegin() const { return const_iterator(head_.get()); }
    const_iterator cend() const { return const_iterator(nullptr); }
};
