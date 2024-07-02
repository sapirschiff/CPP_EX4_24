//sapirblumshtein@gmail.com
//324246651

#include <iostream>
#include <string>
#include "node.hpp"
#include "tree.hpp"
#include "complex.hpp"

using namespace std;

// Function to display the tree using SFML
template <typename T>
void display_tree(Tree<T>& tree, const string& title) {
    sf::RenderWindow window(sf::VideoMode(1000, 800), title);
    window.setVerticalSyncEnabled(true);

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        cerr << "Error loading font\n";
        return;
    }

    const float node_radius = 25.f;
    const float vertical_spacing = 80.f;
    const float initial_horizontal_spacing = 200.f;

    map<Node<T>*, sf::Vector2f> positions;

    function<void(Node<T>*, float, float, float)> position_nodes = [&](Node<T>* node, float x, float y, float horizontal_spacing) {
        if (!node)
            return;

        positions[node] = sf::Vector2f(x, y);

        float child_x_offset = x - (node->get_children().size() - 1) * horizontal_spacing / 2.f;

        for (size_t i = 0; i < node->get_children().size(); ++i) {
            Node<T>* child = node->get_children()[i];
            if (child) {
                position_nodes(child, child_x_offset + i * horizontal_spacing, y + vertical_spacing, horizontal_spacing / 2.f);
            }
        }
    };

    position_nodes(tree.get_root(), window.getSize().x / 2.f, node_radius + 50.f, initial_horizontal_spacing);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);

        for (const auto& pair : positions) {
            Node<T>* node = pair.first;
            sf::Vector2f position = pair.second;

            sf::CircleShape circle(node_radius);
            circle.setFillColor(sf::Color::Blue);
            circle.setPosition(position - sf::Vector2f(node_radius, node_radius));
            window.draw(circle);

            sf::Text text;
            text.setFont(font);
            text.setStyle(sf::Text::Bold);
            if constexpr (is_same<T, string>::value) {
                text.setString(node->get_value());
            } else if constexpr (is_same<T, Complex>::value) {
                ostringstream oss;
                oss << node->get_value();
                text.setString(oss.str());
            } else {
                text.setString(to_string(node->get_value()));
            }
            text.setCharacterSize(16);
            text.setFillColor(sf::Color::Black);
            sf::FloatRect text_bounds = text.getLocalBounds();
            text.setOrigin(text_bounds.left + text_bounds.width / 2.0f, text_bounds.top + text_bounds.height / 2.0f);
            text.setPosition(position);
            window.draw(text);

            for (Node<T>* child : node->get_children()) {
                if (child) {
                    sf::Vector2f child_position = positions[child];

                    sf::Vertex line[] = {
                        sf::Vertex(position, sf::Color::Black),
                        sf::Vertex(child_position, sf::Color::Black)
                    };
                    window.draw(line, 2, sf::Lines);
                }
            }
        }

        window.display();
    }
}

// Function to print tree traversals
template <typename T>
void print_traversals(Tree<T>& tree) {
    cout << "Pre-order traversal:" << endl;
    for (auto node = tree.pre_order_begin(); node != tree.pre_order_end(); ++node) {
        cout << node->get_value() << endl;
    }

    cout << "Post-order traversal:" << endl;
    for (auto node = tree.post_order_begin(); node != tree.post_order_end(); ++node) {
        cout << node->get_value() << endl;
    }

    cout << "In-order traversal:" << endl;
    for (auto node = tree.in_order_begin(); node != tree.in_order_end(); ++node) {
        cout << node->get_value() << endl;
    }

    cout << "BFS traversal:" << endl;
    for (auto node = tree.bfs_begin(); node != tree.bfs_end(); ++node) {
        cout << node->get_value() << endl;
    }

    cout << "Range-based for loop (BFS traversal):" << endl;
    for (auto node : tree) {
        cout << node.get_value() << endl;
    }
}

int main() {
    // Example with double values
    Node<double>* root_node = new Node<double>(1.1);
    Tree<double> double_tree; // Binary tree that contains doubles.
    double_tree.set_root(*root_node);
    Node<double>* n1 = new Node<double>(1.2);
    Node<double>* n2 = new Node<double>(1.3);
    Node<double>* n3 = new Node<double>(1.4);
    Node<double>* n4 = new Node<double>(1.5);
    Node<double>* n5 = new Node<double>(1.6);

    double_tree.add_child(*root_node, *n1);
    double_tree.add_child(*root_node, *n2);
    double_tree.add_child(*n1, *n3);
    double_tree.add_child(*n1, *n4);
    double_tree.add_child(*n2, *n5);

    display_tree(double_tree, "Double Tree");
    print_traversals(double_tree);

    // Create a new root node for the 3-ary tree
    Node<double>* new_root_node = new Node<double>(1.1);
    Tree<double> three_ary_tree(3); // 3-ary tree.
    three_ary_tree.set_root(*new_root_node);
    Node<double>* new_n1 = new Node<double>(1.2);
    Node<double>* new_n2 = new Node<double>(1.3);
    Node<double>* new_n3 = new Node<double>(1.4);
    Node<double>* new_n4 = new Node<double>(1.5);
    Node<double>* new_n5 = new Node<double>(1.6);

    three_ary_tree.add_child(*new_root_node, *new_n1);
    three_ary_tree.add_child(*new_root_node, *new_n2);
    three_ary_tree.add_child(*new_root_node, *new_n3);
    three_ary_tree.add_child(*new_n1, *new_n4);
    three_ary_tree.add_child(*new_n2, *new_n5);

    display_tree(three_ary_tree, "Three-ary Double Tree");
    print_traversals(three_ary_tree);

    // Example with Complex values
    Node<Complex>* complex_root_node = new Node<Complex>(Complex(1.0, 1.0));
    Tree<Complex> complex_tree; // Binary tree that contains Complex numbers.
    complex_tree.set_root(*complex_root_node);
    Node<Complex>* cn1 = new Node<Complex>(Complex(2.0, 3.0));
    Node<Complex>* cn2 = new Node<Complex>(Complex(3.0, 4.0));
    Node<Complex>* cn3 = new Node<Complex>(Complex(4.0, 5.0));
    Node<Complex>* cn4 = new Node<Complex>(Complex(5.0, 6.0));
    Node<Complex>* cn5 = new Node<Complex>(Complex(6.0, 7.0));

    complex_tree.add_child(*complex_root_node, *cn1);
    complex_tree.add_child(*complex_root_node, *cn2);
    complex_tree.add_child(*cn1, *cn3);
    complex_tree.add_child(*cn1, *cn4);
    complex_tree.add_child(*cn2, *cn5);

    display_tree(complex_tree, "Complex Tree");
    print_traversals(complex_tree);

    // Create a new root node for the 3-ary tree with Complex values
    Node<Complex>* new_complex_root_node = new Node<Complex>(Complex(1.0, 1.0));
    Tree<Complex> three_ary_complex_tree(3); // 3-ary tree.
    three_ary_complex_tree.set_root(*new_complex_root_node);
    Node<Complex>* new_cn1 = new Node<Complex>(Complex(2.0, 3.0));
    Node<Complex>* new_cn2 = new Node<Complex>(Complex(3.0, 4.0));
    Node<Complex>* new_cn3 = new Node<Complex>(Complex(4.0, 5.0));
    Node<Complex>* new_cn4 = new Node<Complex>(Complex(5.0, 6.0));
    Node<Complex>* new_cn5 = new Node<Complex>(Complex(6.0, 7.0));

    three_ary_complex_tree.add_child(*new_complex_root_node, *new_cn1);
    three_ary_complex_tree.add_child(*new_complex_root_node, *new_cn2);
    three_ary_complex_tree.add_child(*new_complex_root_node, *new_cn3);
    three_ary_complex_tree.add_child(*new_cn1, *new_cn4);
    three_ary_complex_tree.add_child(*new_cn2, *new_cn5);

    display_tree(three_ary_complex_tree, "Three-ary Complex Tree");
    print_traversals(three_ary_complex_tree);

    return 0;
}
