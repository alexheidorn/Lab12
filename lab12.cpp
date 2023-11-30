/*
* Alex Heidorn
* Created: 11/30/23
* CS2 Lab 12
*  
*/
/*
in my lab11 submission i said i was probably going to skip this assingment too cuz i had the extra drop,
but this assignment was really quick and easy so i just decided to hammer it out
*/

/*Input from .txt file:
I 50
I 25
I 10
I 15
I 30
I 80
I 60
I 70
I 90
I 95

IN

R 30 

F 70


Q
*/

/* Output: Read from file (Y/N)? Y
Filename: bintree.txt
Inserting 50
Inserting 25
Inserting 10
curr is 25
Inserting 15
curr is 25
curr is 10
Inserting 30
curr is 25
Inserting 80
Inserting 60
curr is 80
Inserting 70
curr is 80
curr is 60
Inserting 90
curr is 80
Inserting 95
curr is 80
curr is 90
Print In Order:
         95
      90
   80
         70
      60
 50
      30
   25
         15
      10

Removing value 30
Deleting node with data 30
Successfully removed
Finding 70
Looking at 50
Looking at 80
Looking at 60
Looking at 70
Found
Deleting node with data 50
Deleting node with data 80
Deleting node with data 90
Deleting node with data 95
Deleting node with data 60
Deleting node with data 70
Deleting node with data 25
Deleting node with data 10
Deleting node with data 15
PS C:\Users\alexh\CS2> 
*/

#include <iostream>
#include <fstream>
#include "HeidornBinaryTree.cpp"

using namespace std;


void traverse(shared_ptr<BinaryNode>n, ostream &out) {
    if (n != nullptr) {
        out << "Pre " << n->getData() << " ";
        traverse(n->getLeft(), out);
        out << "In " << n->getData() << " ";
        traverse(n->getRight(), out);
        out << "Post " << n->getData() << " ";
    }
}
void processCommands(bool fromFile, istream& inS) {
    BinaryTree tree;
    string option;
    do {
        int value;
        if (!fromFile) cout << "Commands: I)nsert, R)emove, F)ind, \n     PF)rintflat, printIN)order, printPRE)order printPOST)order T)raverse Q)uit: ";
        inS >> option;
        if (option.compare("I") == 0) {
            if (!fromFile) cout << "Insert value: ";
            inS >> value;
            if (fromFile) cout << "Inserting " << value << endl;
            tree.insert(value);
        }
        else if (option.compare("R") == 0) {
            if (!fromFile) cout << "Remove value: ";
            inS >> value;
            if (fromFile) cout << "Removing value " << value << endl;
            if (tree.remove(value)) {
                cout << "Successfully removed\n";
            }
            else {
                cout << "Not removed\n";
            }
        }
        else if (option.compare("F") == 0) {
            if (!fromFile) cout << "Find value: ";
            inS >> value;
            if (fromFile) cout << "Finding " << value << endl;
            if (tree.find(value)) {
                cout << "Found\n";
            }
            else {
                cout << "Not found\n";
            }
        }
        else if (option.compare("PF") == 0) {
            if (fromFile) cout << "Print Flat:\n";
            tree.printFlat(cout);
        }
        else if (option.compare("IN") == 0) {
            if (fromFile) cout << "Print In Order:\n";
            tree.printInOrder(cout);
        }
        else if (option.compare("PRE") == 0) {
            if (fromFile) cout << "Print PreOrder:\n";
            tree.printPreOrder(cout);
        }
        else if (option.compare("POST") == 0) {
            if (fromFile) cout << "Print PostOrder:\n";
            tree.printPostOrder(cout);
        }
        else if (option.compare("T") == 0) {
            if (fromFile) cout << "Traverse:\n";
            traverse(tree.getRoot(),cout);
        }
        else if (option.compare("Q") != 0) {
            cout << "Unknown option " << option << endl;
        }
    } while (option.compare("Q") != 0);
}

int main() {
    string option;
    string fileName;

    cout << "Read from file (Y/N)? ";
    cin >> option;
    if (option.compare("Y") == 0) {
        cout << "Filename: ";
        cin >> fileName;
        ifstream inF(fileName);
        if (inF.good()) {
            processCommands(true,inF);
        }
    }
    else {
        processCommands(false,cin);
    }


    return 0;
}
