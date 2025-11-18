#pragma once
#include <memory>
#include <functional>
#include <initializer_list>
#include <queue>
#include <stdexcept>
#include <utility>
#include "SmartList.hpp"

template <typename T, typename Compare = std::less<T>>
class Tree {
public:
    struct Node {
        T value;
        std::shared_ptr<Node> left{};
        std::shared_ptr<Node> right{};
        std::weak_ptr<Node> parent{};

        explicit Node(T v) : value(std::move(v)) {}

        bool isLeaf() const noexcept { return !left && !right; }
    };
    using NodePtr = std::shared_ptr<Node>;

private:
    NodePtr root_{};
    Compare comp_{};

public:
    Tree() = default;
    explicit Tree(Compare cmp) : comp_(cmp) {}
    explicit Tree(NodePtr r, Compare cmp = Compare{}) : root_(std::move(r)), comp_(cmp) {}

    Tree(std::initializer_list<T> init, Compare cmp = Compare{}) : comp_(cmp) {
        for (auto const& x : init) insert(x);
    }

    NodePtr root() const noexcept { return root_; }
    bool empty() const noexcept { return !root_; }

    void insert(T x) {
        if (!root_) {
            root_ = std::make_shared<Node>(std::move(x));
            return;
        }
        NodePtr cur = root_, prev = nullptr;
        while (cur) {
            prev = cur;
            if (comp_(x, cur->value)) cur = cur->left;
            else if (comp_(cur->value, x)) cur = cur->right;
            else return;
        }
        auto n = std::make_shared<Node>(std::move(x));
        n->parent = prev;
        if (comp_(n->value, prev->value)) prev->left = n;
        else prev->right = n;
    }

    template <typename Visit>
    void inorder(Visit&& f) const {
        std::function<void(NodePtr)> dfs = [&](NodePtr n) {
            if (!n) return;
            dfs(n->left);
            f(n->value);
            dfs(n->right);
        };
        dfs(root_);
    }
};

template <typename T, typename Compare, typename Visit>
void level_order(Tree<T,Compare> const& tree, Visit&& visit) {
    using NodePtr = typename Tree<T,Compare>::NodePtr;

    if (tree.empty()) return;
    std::queue<NodePtr> q;
    q.push(tree.root());
    while (!q.empty()) {
        NodePtr n = q.front(); q.pop();
        visit(n->value);
        if (n->left) q.push(n->left);
        if (n->right) q.push(n->right);
    }
}

template <typename T, typename Compare>
Tree<T,Compare> prune(Tree<T,Compare> const& tree) {
    using Node = typename Tree<T,Compare>::Node;
    using NodePtr = std::shared_ptr<Node>;

    if (tree.empty()) return Tree<T,Compare>{};

    std::function<NodePtr(NodePtr, NodePtr)> copyWithoutLeaves =
        [&](NodePtr src, NodePtr parent) -> NodePtr {
            if (!src) return nullptr;
            if (src->isLeaf()) return nullptr;

            NodePtr dst = std::make_shared<Node>(src->value);
            dst->parent = parent;
            dst->left  = copyWithoutLeaves(src->left,  dst);
            dst->right = copyWithoutLeaves(src->right, dst);
            return dst;
        };

    return Tree<T,Compare>(copyWithoutLeaves(tree.root(), nullptr));
}

template <typename T, typename Compare>
SmartList<T> fringe(Tree<T,Compare> const& tree) {
    SmartList<T> out;
    using NodePtr = typename Tree<T,Compare>::NodePtr;

    if (tree.empty()) return out;

    std::queue<NodePtr> q;
    q.push(tree.root());

    while (!q.empty()) {
        NodePtr n = q.front(); q.pop();
        if (n->isLeaf()) out.push_back(n->value);
        else {
            if (n->left) q.push(n->left);
            if (n->right) q.push(n->right);
        }
    }
    return out;
}

template <typename T, typename Compare>
bool hasSameFringe(Tree<T,Compare> const& a, Tree<T,Compare> const& b) {
    SmartList<T> fa = fringe(a), fb = fringe(b);
    if (fa.size() != fb.size()) return false;
    auto it1 = fa.begin();
    auto it2 = fb.begin();
    for (; it1 != fa.end(); ++it1, ++it2)
        if (*it1 != *it2) return false;
    return true;
}
