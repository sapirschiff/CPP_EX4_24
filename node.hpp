//sapirblumshtein@gmail.com
//324246651

#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
#include <stdexcept>

// Node class template
template <typename T>
class Node {
public:
    // Constructor to initialize the node with a value
    explicit Node(const T& value) : value(value) {}

    // Get the value of the node
    const T& get_value() const {
        return value;
    }

    // Add a child to the node, ensuring the maximum number of children (k) is not exceeded
    void add_child(Node* child, size_t k) {
        if (children.size() >= k) {
            throw std::runtime_error("Maximum children exceeded");
        }
        children.push_back(child);
    }

    // Get the children of the node
    const std::vector<Node*>& get_children() const {
        return children;
    }

private:
    T value; // Value of the node
    std::vector<Node*> children; // Children of the node
};

#endif // NODE_HPP
