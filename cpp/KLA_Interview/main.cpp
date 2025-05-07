#include <iostream>
#include <string>
#include <vector>

struct TreeNode {
    std::string name;
    std::vector<TreeNode*> children;
};

class KLA_Tree {
    public:
        void add_root(TreeNode* root) { this->root = root; }
        void add_node(TreeNode* parent, TreeNode*node);
        TreeNode* get_parent(int level);
        void print_tree();
    private:
        TreeNode* root;
};

void KLA_Tree::add_node(TreeNode* parent, TreeNode* node) {
    parent->children.push_back(node);
}

TreeNode* KLA_Tree::get_parent(int level) {
    TreeNode* node = root;

    for( int i = 0; i < level; i++ ) {
        node = node->children[node->children.size() - 1];
    }

    return node;
}

void print_helper(TreeNode* node) {
    if(node == nullptr) {
        return;
    } else {
        std::cout << node->name << ", ";
        for(int i = 0; i < node->children.size(); i++) {
            print_helper(node->children[i]);
        }
    }
}

void KLA_Tree::print_tree() {
    print_helper(root);
}

struct Entry {
    std::string name;
    int level;
};

std::vector<Entry> my_data = 
{
    {"Machine", 0},
    {"System A", 1},
    {"Sub-system A1", 2},
    {"Component 1", 3},
    {"Component 2", 3},
    {"Sub-component 3", 4},
    {"Sub-system A2", 2},
    {"Component 3", 3},
    {"Component 4", 3},
    {"Sub-component 4s", 4},
    {"System B", 1},
    {"Sub-system B1", 2},
    {"Component 1", 3},
    {"Component 2", 3},
    {"Component 3", 3},
    {"Sub-component 3", 4},
    {"Sub-component 4", 4},
    {"Sub-component 5", 4},
    {"Sub-system C1", 2},
    {"Component C11", 3},
    {"Interconnect", 1},
    {"Sub-system-Interconnect", 1},
};

int main() {
    KLA_Tree my_tree;

    for (Entry entry: my_data) {
        TreeNode* new_node = new TreeNode();
        new_node->name = entry.name;
        if( entry.level == 0 ) {
            my_tree.add_root(new_node);
        } else {
            TreeNode* parent = my_tree.get_parent(entry.level-1);
            my_tree.add_node(parent, new_node);
        }
    }

    my_tree.print_tree();
    return 1;
}