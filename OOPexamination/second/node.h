#pragma once
#include <iostream>
#include <string>
#include <utility>

class Node {
public:
    static int constructed;
    static int destroyed;

    std::string text;
    int priority;

    Node() : text(""), priority(0) { ++constructed; }
    Node(const std::string& text_, int priority_) : text(text_), priority(priority_) { ++constructed; }
    Node(const Node& other) : text(other.text), priority(other.priority) { ++constructed; }
    Node(Node&& other) : text(std::move(other.text)), priority(other.priority) { ++constructed; }
    ~Node() { ++destroyed; }

    Node& operator=(const Node& other) {
        text = other.text;
        priority = other.priority;
        return *this;
    }

    bool operator==(const Node& other) const {
        return text == other.text && priority == other.priority;
    }

    bool operator!=(const Node& other) const {
        return !(*this == other);
    }

    static bool balanced() {
        return constructed == destroyed;
    }
};

int Node::constructed = 0;
int Node::destroyed = 0;

std::ostream& operator<<(std::ostream& os, const Node& node) {
    os << node.text << ":" << node.priority;
    return os;
}
