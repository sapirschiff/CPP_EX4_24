//sapirblumshtein@gmail.com
//324246651

#ifndef TREE_HPP
#define TREE_HPP

#include <queue>
#include <iostream>
#include <stack>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include "node.hpp"
#include <map>
#include "complex.hpp"
#include <sstream>
#include <functional>

// Tree class template
template <typename T>
class Tree {
public:
    // Constructor to initialize the tree with a given maximum number of children (k)
    explicit Tree(size_t k = 2) : root(nullptr), k(k) {}

    // Set the root node of the tree
    void set_root(Node<T> &node) {
        root = &node;
    }

    // Add a child to a parent node, ensuring the maximum number of children (k) is not exceeded
    void add_child(Node<T> &parent, Node<T> &child) {
        if (!root) {
            throw std::runtime_error("Error: Root not set.");
        }

        Node<T> *parentNode = find_node(root, parent.get_value());
        if (parentNode) {
            parentNode->add_child(&child, k);
        } else {
            throw std::runtime_error("Parent node not found.");
        }
    }

    // Template specialization to prevent adding a child of a different type
    template <typename U>
    void add_child(Node<T> &parent, Node<U> &child) {
        throw std::runtime_error("Child node type does not match");
    }

    ~Tree() {}

    // Pre-order iterator class
    class pre_order_iterator {
    public:
        explicit pre_order_iterator(Node<T> *node, size_t k) : k(k) {
            if (node) nodes.push(node);
        }

        bool operator!=(const pre_order_iterator &other) const {
            return !nodes.empty() != !other.nodes.empty();
        }

        Node<T> *operator->() const {
            return nodes.top();
        }

        Node<T> &operator*() const {
            return *nodes.top();
        }

        pre_order_iterator &operator++() {
            Node<T> *current = nodes.top();
            nodes.pop();
            for (auto it = current->get_children().rbegin(); it != current->get_children().rend(); ++it) {
                if (*it != nullptr)
                    nodes.push(*it);
            }
            return *this;
        }

    private:
        std::stack<Node<T> *> nodes;
        size_t k;
    };

    pre_order_iterator pre_order_begin() const {
        return pre_order_iterator(root, k);
    }

    pre_order_iterator pre_order_end() const {
        return pre_order_iterator(nullptr, k);
    }

    // In-order iterator class
    class in_order_iterator {
    public:
        explicit in_order_iterator(Node<T> *node, size_t k) : k(k) {
            if (node) {
                if (k == 2) {
                    push_left(node);
                } else {
                    nodes.push(node);
                    while (!nodes.empty() && !nodes.top()) nodes.pop();
                }
            }
        }

        bool operator!=(const in_order_iterator &other) const {
            return !nodes.empty() != !other.nodes.empty();
        }

        Node<T> *operator->() const {
            return nodes.top();
        }

        Node<T> &operator*() const {
            return *nodes.top();
        }

        in_order_iterator &operator++() {
            if (nodes.empty()) return *this;

            if (k == 2) {
                Node<T> *node = nodes.top();
                nodes.pop();
                if (node->get_children().size() > 1 && node->get_children()[1] != nullptr) {
                    push_left(node->get_children()[1]);
                }
            } else {
                Node<T> *current = nodes.top();
                nodes.pop();
                for (auto it = current->get_children().rbegin(); it != current->get_children().rend(); ++it) {
                    if (*it != nullptr)
                        nodes.push(*it);
                }
            }
            return *this;
        }

    private:
        std::stack<Node<T> *> nodes;
        size_t k;

        void push_left(Node<T> *node) {
            while (node != nullptr) {
                nodes.push(node);
                if (node->get_children().size() > 0)
                    node = node->get_children()[0];
                else
                    break;
            }
        }
    };

    in_order_iterator in_order_begin() const {
        return in_order_iterator(root, k);
    }

    in_order_iterator in_order_end() const {
        return in_order_iterator(nullptr, k);
    }

    // Post-order iterator class
    class post_order_iterator {
    public:
        explicit post_order_iterator(Node<T> *node, size_t k) : current_node(nullptr), k(k) {
            if (node) {
                push_leftmost(node);
            }
            ++(*this);
        }

        bool operator!=(const post_order_iterator &other) const {
            return current_node != other.current_node;
        }

        Node<T> *operator->() const {
            return current_node;
        }

        Node<T> &operator*() const {
            return *current_node;
        }

        post_order_iterator &operator++() {
            if (!nodes.empty()) {
                Node<T> *node = nodes.top();
                nodes.pop();
                if (!nodes.empty()) {
                    Node<T> *parent = nodes.top();
                    auto it = std::find(parent->get_children().begin(), parent->get_children().end(), node);
                    if (it != parent->get_children().end() && ++it != parent->get_children().end()) {
                        push_leftmost(*it);
                    }
                }
                current_node = node;
            } else {
                current_node = nullptr;
            }
            return *this;
        }

    private:
        std::stack<Node<T> *> nodes;
        Node<T> *current_node;
        size_t k;

        void push_leftmost(Node<T> *node) {
            while (node) {
                nodes.push(node);
                if (!node->get_children().empty()) {
                    node = node->get_children()[0];
                } else {
                    break;
                }
            }
        }
    };

    post_order_iterator post_order_begin() const {
        return post_order_iterator(root, k);
    }

    post_order_iterator post_order_end() const {
        return post_order_iterator(nullptr, k);
    }

    // BFS iterator class
    class BFSIterator {
    public:
        explicit BFSIterator(Node<T> *node) {
            if (node) nodes.push(node);
        }

        bool operator!=(const BFSIterator &other) const {
            return !nodes.empty() != !other.nodes.empty();
        }

        Node<T> *operator->() const {
            return nodes.front();
        }

        Node<T> &operator*() const {
            return *nodes.front();
        }

        BFSIterator &operator++() {
            Node<T> *current = nodes.front();
            nodes.pop();
            for (const auto &child : current->get_children()) {
                if (child != nullptr)
                    nodes.push(child);
            }
            return *this;
        }

    private:
        std::queue<Node<T> *> nodes;
    };

    BFSIterator bfs_begin() const {
        return BFSIterator(root);
    }

    BFSIterator bfs_end() const {
        return BFSIterator(nullptr);
    }

    // DFS iterator class
    class DFSIterator {
    public:
        explicit DFSIterator(Node<T> *node) {
            if (node) nodes.push(node);
        }

        bool operator!=(const DFSIterator &other) const {
            return !nodes.empty() != !other.nodes.empty();
        }

        Node<T> *operator->() const {
            return nodes.top();
        }

        Node<T> &operator*() const {
            return *nodes.top();
        }

        DFSIterator &operator++() {
            Node<T> *current = nodes.top();
            nodes.pop();
            for (auto it = current->get_children().rbegin(); it != current->get_children().rend(); ++it) {
                if (*it != nullptr)
                    nodes.push(*it);
            }
            return *this;
        }

    private:
        std::stack<Node<T> *> nodes;
    };

    DFSIterator dfs_begin() const {
        return DFSIterator(root);
    }

    DFSIterator dfs_end() const {
        return DFSIterator(nullptr);
    }

    BFSIterator begin() const {
        return BFSIterator(root);
    }

    BFSIterator end() const {
        return BFSIterator(nullptr);
    }

    // Heap iterator class
    class HeapIterator {
    public:
        explicit HeapIterator(Node<T> *node, size_t k) : k(k) {
            if (node) {
                collect_nodes(node);
                std::make_heap(heap_nodes.begin(), heap_nodes.end(), CompareNodes());
            }
        }

        bool operator!=(const HeapIterator &other) const {
            return !heap_nodes.empty() != !other.heap_nodes.empty();
        }

        Node<T> *operator->() const {
            return heap_nodes.front();
        }

        Node<T> &operator*() const {
            return *heap_nodes.front();
        }

        HeapIterator &operator++() {
            if (!heap_nodes.empty()) {
                std::pop_heap(heap_nodes.begin(), heap_nodes.end(), CompareNodes());
                heap_nodes.pop_back();
            }
            return *this;
        }

    private:
        struct CompareNodes {
            bool operator()(Node<T> *a, Node<T> *b) {
                return a->get_value() > b->get_value();
            }
        };

        void collect_nodes(Node<T> *node) {
            if (node) {
                heap_nodes.push_back(node);
                for (auto child : node->get_children()) {
                    collect_nodes(child);
                }
            }
        }

        std::vector<Node<T> *> heap_nodes;
        size_t k;
    };

    HeapIterator heap_begin() const {
        return HeapIterator(root, k);
    }

    HeapIterator heap_end() const {
        return HeapIterator(nullptr, k);
    }

    // Get the root node of the tree
    Node<T> *get_root() const {
        return root;
    }

private:
    Node<T> *root; // Root node of the tree
    size_t k; // Maximum number of children

    // Helper function to find a node with a specific value in the tree
    Node<T> *find_node(Node<T> *current, const T &value) const {
        if (current->get_value() == value)
            return current;
        for (auto child : current->get_children()) {
            if (child) {
                Node<T> *result = find_node(child, value);
                if (result)
                    return result;
            }
        }
        return nullptr;
    }
};

#endif // TREE_HPP
