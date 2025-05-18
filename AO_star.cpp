#include <iostream>
#include <vector>
#include <limits>
#include <string>

using namespace std;

struct Node;

struct ChildSet {
    vector<Node*> children;
};

struct Node {
    string name;
    vector<ChildSet> childrenSets;
    int heuristic;
    bool solved;
    Node* bestChild;
    ChildSet* bestSet;
    int totalCost;

    Node(string n, int h) {
        name = n;
        heuristic = h;
        solved = false;
        bestChild = NULL;
        bestSet = NULL;
        totalCost = h;
    }
};

int AOStar(Node* node) {
    if (node->solved) {
        return node->totalCost;
    }

    if (node->childrenSets.size() == 0) {
        node->solved = true;
        return node->heuristic;
    }

    int minCost = numeric_limits<int>::max();
    ChildSet* bestSet = NULL;

    for (int i = 0; i < (int)node->childrenSets.size(); i++) {
        ChildSet& childSet = node->childrenSets[i];

        int setCost = (int)childSet.children.size();

        for (int j = 0; j < (int)childSet.children.size(); j++) {
            Node* child = childSet.children[j];
            setCost += AOStar(child);
        }

        if (setCost < minCost) {
            minCost = setCost;
            bestSet = &childSet;
        }
    }

    node->totalCost = minCost;
    node->solved = true;
    node->bestSet = bestSet;

    if (bestSet->children.size() == 1) {
        node->bestChild = bestSet->children[0];
    } else {
        node->bestChild = NULL;
    }

    return node->totalCost;
}

void printSolution(Node* node) {
    if (node == NULL) {
        return;
    }

    cout << node->name;

    if (node->childrenSets.size() == 0) {
        cout << " (goal)";
        return;
    }

    if (node->bestChild != NULL) {
        cout << " -> ";
        printSolution(node->bestChild);
    } else {
        cout << " -> [";
        for (int i = 0; i < (int)node->bestSet->children.size(); i++) {
            printSolution(node->bestSet->children[i]);
            if (i != (int)node->bestSet->children.size() - 1) {
                cout << ", ";
            }
        }
        cout << "]";
    }
}

int main() {
    Node* A = new Node("A", 0);
    Node* B = new Node("B", 4);
    Node* C = new Node("C", 2);
    Node* D = new Node("D", 3);
    Node* E = new Node("E", 6);
    Node* F = new Node("F", 8);
    Node* G = new Node("G", 2);
    Node* H = new Node("H", 0);
    Node* I = new Node("I", 0);
    Node* J = new Node("J", 0);

    ChildSet set1;
    set1.children.push_back(B);
    ChildSet set2;
    set2.children.push_back(C);
    set2.children.push_back(D);
    A->childrenSets.push_back(set1);
    A->childrenSets.push_back(set2);

    ChildSet bset1;
    bset1.children.push_back(E);
    ChildSet bset2;
    bset2.children.push_back(F);
    B->childrenSets.push_back(bset1);
    B->childrenSets.push_back(bset2);

    ChildSet cset;
    cset.children.push_back(H);
    cset.children.push_back(I);
    C->childrenSets.push_back(cset);

    ChildSet dset;
    dset.children.push_back(J);
    D->childrenSets.push_back(dset);

    AOStar(A);

    cout << "\n\nSolution Path: ";
    printSolution(A);
    cout << endl;

    delete A; delete B; delete C; delete D; delete E; delete F;
    delete G; delete H; delete I; delete J;

    return 0;
}
