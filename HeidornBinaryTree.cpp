//
// Created by Richard Maclin on 11/9/23.
//

#include "HeidornBinaryTree.h"
#include <iomanip>
#include <memory>

namespace std {
    shared_ptr<BinaryNode>doFind(int d, shared_ptr<BinaryNode>curr) {
        if (curr == nullptr) {
            return nullptr;
        }
        cout << "Looking at " << curr->getData() << endl;
        int cmp = curr->compare(d);
        if (cmp == 0) {
            return curr;
        }
        else {
            if (cmp < 0) {
                return doFind(d,curr->getLeft());
            }
            else {
                return doFind(d,curr->getRight());
            }
        }
    }

    shared_ptr<BinaryNode>BinaryTree::find(int d) {
        return doFind(d,root);
    }

    shared_ptr<BinaryNode>doInsert(shared_ptr<BinaryNode>curr, int d) {
        if (curr == NULL) {
            //return new BinaryNode(d);
            return make_shared<BinaryNode>(d);
        }
        cout << "curr is " << curr->getData() << endl;
        int cmp = curr->compare(d);
        if (cmp <= 0) {
            curr->setLeft(doInsert(curr->getLeft(),d));
        }
        else {
            curr->setRight(doInsert(curr->getRight(),d));
        }
        return curr;
    }

    void BinaryTree::insert(int d) {
        if (root == nullptr) {
            //root = new BinaryNode(d);
            root = make_shared<BinaryNode>(d);
            return;
        }
        int cmp = root->compare(d);
        if (cmp <= 0) {
            root->setLeft(doInsert(root->getLeft(),d));
        }
        else {
            root->setRight(doInsert(root->getRight(),d));
        }
    }

    shared_ptr<BinaryNode>removeNextHighestValue(shared_ptr<BinaryNode>curr, int &nextD) {
        if (curr->getLeft() == nullptr) {
            shared_ptr<BinaryNode>discard = curr;
            nextD = curr->getData();
            if (curr->getRight() == nullptr) {
                //delete discard;
                return nullptr;
            }
            else {
                shared_ptr<BinaryNode>rightC = curr->getRight();
                //delete discard;
                return rightC;
            }
        }
        else {
            curr->setLeft(removeNextHighestValue(curr->getLeft(),nextD));
            return curr;
        }
    }

    shared_ptr<BinaryNode>doRemove(shared_ptr<BinaryNode>curr, int d, bool &found) {
        if (curr == nullptr) {
            return nullptr;
        }
        int cmp = curr->compare(d);
        if (cmp == 0) {
            found = true;
            if (curr->getLeft() == nullptr) {
                if (curr->getRight() == nullptr) {
                    //delete curr;
                    return nullptr;
                }
                else {
                    shared_ptr<BinaryNode>rightC = curr->getRight();
                    //delete curr;
                    return rightC;
                }
            }
            else {
                if (curr->getRight() == nullptr) {
                    shared_ptr<BinaryNode>leftC = curr->getLeft();
                    //delete curr;
                    return leftC;
                }
                else {
                    int nextD;
                    curr->setRight(removeNextHighestValue(curr->getRight(),nextD));
                    curr->setData(nextD);
                    return curr;
                }
            }
        }
        else {
            if (cmp < 0) {
                curr->setLeft(doRemove(curr->getLeft(),d,found));
            }
            else {
                curr->setRight(doRemove(curr->getRight(),d,found));
            }
            return curr;
        }
    }

    bool BinaryTree::remove(int d) {
        if (root == nullptr) {
            return false;
        }
        bool found = false;
        root = doRemove(root,d,found);
        return found;
    }

    void BinaryNode::doPrintFlat(ostream &out) {
        if (left != nullptr) left->doPrintFlat(out);
        out << data << " ";
        if (right != nullptr) right->doPrintFlat(out);
    }

    void BinaryTree::printFlat(ostream &out) {
        if (root != nullptr) {
            root->doPrintFlat(out);
        }
        out << endl;
    }

    void BinaryNode::doPrintInOrder(ostream &out, int indent) {
        if (right != nullptr) right->doPrintInOrder(out,indent+1);
        out << setw(indent*3) << " ";
        out << data << "\n";
        if (left != nullptr) left->doPrintInOrder(out,indent+1);
    }

    void BinaryTree::printInOrder(ostream &out) {
        if (root != nullptr) {
            root->doPrintInOrder(out);
        }
        out << endl;
    }

    void BinaryNode::doPrintPreOrder(ostream &out, int indent) {
        out << setw(indent*3) << " ";
        out << data << "\n";
        if (right != nullptr) right->doPrintPreOrder(out,indent+1);
        if (left != nullptr) left->doPrintPreOrder(out,indent+1);
    }

    void BinaryTree::printPreOrder(ostream &out) {
        if (root != nullptr) {
            root->doPrintPreOrder(out,0);
        }
        out << endl;
    }

    void BinaryNode::doPrintPostOrder(ostream &out, int indent) {
        if (right != nullptr) right->doPrintPostOrder(out,indent+1);
        if (left != nullptr) left->doPrintPostOrder(out,indent+1);
        out << setw(indent*3) << " ";
        out << data << "\n";
    }

    void BinaryTree::printPostOrder(ostream &out) {
        root->doPrintPostOrder(out,0);
        out << endl;
    }
} // std