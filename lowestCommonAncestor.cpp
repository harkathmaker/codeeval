// https://www.codeeval.com/open_challenges/11/

#include <iostream>
#include <fstream>

class Node {
public:
    Node(int val): value(val), level(0), parent(NULL), left(NULL), right(NULL) {
    }
    Node(int val,Node *p): value(val), level(p->level+1), parent(p), left(NULL), right(NULL) {
    }
    ~Node() {
        delete left;
        delete right;
    }

    void addChild(int val) {
        if(val < value) {
            if(left != NULL) {
                left->addChild(val);
            } else {
                left = new Node(val,this);
            }
        } else {
            if(right != NULL) {
                right->addChild(val);
            } else {
                right = new Node(val,this);
            }
        }
    }

    const Node *nodeForValue(int val) const {
        if(val == value) {
            return this;
        } else if(val < value && left != NULL) {
            return left->nodeForValue(val);
        } else if(val >= value && right != NULL) {
            return right->nodeForValue(val);
        }
        return NULL;
    }

    const Node *commonAncestor(const Node *other) const {
        if(other == NULL) {
            return NULL;
        }
        const Node *anc = this;
        const Node *other_anc = other;
        while(anc->level > other_anc->level) {
            anc = anc->parent;
        }
        while(other_anc->level > anc->level) {
            other_anc = other_anc->parent;
        }
        while(other_anc->value != anc->value) {
            other_anc = other_anc->parent;
            anc = anc->parent;
        }
        return anc;
    }

    int getValue() const {
        return value;
    }

private:
    int value;
    int level;
    Node *parent;
    Node *left;
    Node *right;
};

int main(int argc, char *argv[]) {
    std::ifstream fid;
    std::string line;
    fid.open(argv[1],std::ios::in);
    if(!fid.is_open()) {
        fprintf(stderr,"Error opening file!\n");
    }
    // Hard-coded tree
    Node tree(30);
    tree.addChild(8);
    tree.addChild(52);
    tree.addChild(3);
    tree.addChild(20);
    tree.addChild(10);
    tree.addChild(29);
    

    while(!fid.eof()) {
        getline(fid,line);
        size_t secondNumStart = line.find(' ');
        int n1 = atoi(line.c_str());
        const Node *node1 = tree.nodeForValue(n1);
        int n2 = atoi(line.c_str()+secondNumStart);
        const Node *node2 = tree.nodeForValue(n2);
        if(node1 == NULL || node2 == NULL) {
            continue;
        }
        printf("%d\n",node1->commonAncestor(node2)->getValue());
    }
    fid.close();

    return 0;
}
