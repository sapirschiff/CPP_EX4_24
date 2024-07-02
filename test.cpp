//sapirblumshtein@gmail.com
//324246651

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "complex.hpp"
#include "tree.hpp"
#include "node.hpp"

// Testing simple tree structure with integers
TEST_CASE("Testing simple tree structure with integers") {
    Tree<int> intTree;
    Node<int> root(1);
    intTree.set_root(root);

    Node<int> n2(2);
    Node<int> n3(3);
    Node<int> n4(4);
    Node<int> n5(5);
    Node<int> n6(6);

    intTree.add_child(root, n2);
    intTree.add_child(root, n3);
    intTree.add_child(n2, n4);
    intTree.add_child(n2, n5);
    intTree.add_child(n3, n6);

    CHECK(root.get_value() == 1);
    auto it = intTree.pre_order_begin();
    CHECK(it->get_value() == 1);
    ++it;
    CHECK(it->get_value() == 2);
    ++it;
    CHECK(it->get_value() == 4);
    ++it;
    CHECK(it->get_value() == 5);
    ++it;
    CHECK(it->get_value() == 3);
    ++it;
    CHECK(it->get_value() == 6);
}

// Testing tree with strings
TEST_CASE("Testing tree with strings") {
    Tree<std::string> stringTree;
    Node<std::string> root("root");
    stringTree.set_root(root);

    Node<std::string> left("left");
    Node<std::string> right("right");
    Node<std::string> left_left("left.left");
    Node<std::string> left_right("left.right");
    Node<std::string> right_left("right.left");

    stringTree.add_child(root, left);
    stringTree.add_child(root, right);
    stringTree.add_child(left, left_left);
    stringTree.add_child(left, left_right);
    stringTree.add_child(right, right_left);

    CHECK(root.get_value() == "root");
    auto it = stringTree.pre_order_begin();
    CHECK(it->get_value() == "root");
    ++it;
    CHECK(it->get_value() == "left");
    ++it;
    CHECK(it->get_value() == "left.left");
    ++it;
    CHECK(it->get_value() == "left.right");
    ++it;
    CHECK(it->get_value() == "right");
    ++it;
    CHECK(it->get_value() == "right.left");
}

// Testing tree with doubles
TEST_CASE("Testing tree with doubles") {
    Tree<double> doubleTree;
    Node<double> root(1.1);
    doubleTree.set_root(root);

    Node<double> n1(1.2);
    Node<double> n2(1.3);
    Node<double> n3(1.4);
    Node<double> n4(1.5);
    Node<double> n5(1.6);

    doubleTree.add_child(root, n1);
    doubleTree.add_child(root, n2);
    doubleTree.add_child(n1, n3);
    doubleTree.add_child(n1, n4);
    doubleTree.add_child(n2, n5);

    CHECK(root.get_value() == 1.1);
    auto it = doubleTree.pre_order_begin();
    CHECK(it->get_value() == 1.1);
    ++it;
    CHECK(it->get_value() == 1.2);
    ++it;
    CHECK(it->get_value() == 1.4);
    ++it;
    CHECK(it->get_value() == 1.5);
    ++it;
    CHECK(it->get_value() == 1.3);
    ++it;
    CHECK(it->get_value() == 1.6);
}

// Testing tree with complex numbers
TEST_CASE("Testing tree with complex numbers") {
    Tree<Complex> complexTree;
    Node<Complex> root(Complex(1.1, 2.2));
    complexTree.set_root(root);

    Node<Complex> n1(Complex(1.2, 2.3));
    Node<Complex> n2(Complex(1.3, 2.4));
    Node<Complex> n3(Complex(1.4, 2.5));
    Node<Complex> n4(Complex(1.5, 2.6));
    Node<Complex> n5(Complex(1.6, 2.7));

    complexTree.add_child(root, n1);
    complexTree.add_child(root, n2);
    complexTree.add_child(n1, n3);
    complexTree.add_child(n1, n4);
    complexTree.add_child(n2, n5);

    CHECK(root.get_value() == Complex(1.1, 2.2));
    auto it = complexTree.pre_order_begin();
    CHECK(it->get_value() == Complex(1.1, 2.2));
    ++it;
    CHECK(it->get_value() == Complex(1.2, 2.3));
    ++it;
    CHECK(it->get_value() == Complex(1.4, 2.5));
    ++it;
    CHECK(it->get_value() == Complex(1.5, 2.6));
    ++it;
    CHECK(it->get_value() == Complex(1.3, 2.4));
    ++it;
    CHECK(it->get_value() == Complex(1.6, 2.7));
}

// Testing tree with characters
TEST_CASE("Testing tree with characters") {
    Tree<char> charTree;
    Node<char> root('A');
    charTree.set_root(root);

    Node<char> n1('B');
    Node<char> n2('C');
    Node<char> n3('D');
    Node<char> n4('E');
    Node<char> n5('F');

    charTree.add_child(root, n1);
    charTree.add_child(root, n2);
    charTree.add_child(n1, n3);
    charTree.add_child(n1, n4);
    charTree.add_child(n2, n5);

    CHECK(root.get_value() == 'A');
    auto it = charTree.pre_order_begin();
    CHECK(it->get_value() == 'A');
    ++it;
    CHECK(it->get_value() == 'B');
    ++it;
    CHECK(it->get_value() == 'D');
    ++it;
    CHECK(it->get_value() == 'E');
    ++it;
    CHECK(it->get_value() == 'C');
    ++it;
    CHECK(it->get_value() == 'F');
}

// Testing exceeding maximum number of children
TEST_CASE("Testing exceeding maximum number of children") {
    Tree<int> intTree(2);
    Node<int> root(1);
    intTree.set_root(root);

    Node<int> n1(2);
    Node<int> n2(3);
    Node<int> n3(4);

    intTree.add_child(root, n1);
    intTree.add_child(root, n2);
    REQUIRE_THROWS_AS(intTree.add_child(root, n3), std::runtime_error);
}

// Testing tree with k = 1
TEST_CASE("Testing tree with k = 1") {
    Tree<int> intTree(1);
    Node<int> root(1);
    intTree.set_root(root);

    Node<int> n1(2);
    Node<int> n2(3);

    intTree.add_child(root, n1);
    REQUIRE_THROWS_AS(intTree.add_child(root, n2), std::runtime_error);

    CHECK(root.get_value() == 1);
    auto it = intTree.pre_order_begin();
    CHECK(it->get_value() == 1);
    ++it;
    CHECK(it->get_value() == 2);
}
