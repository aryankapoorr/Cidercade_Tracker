/******************************************************************************

Aryan Kapoor
NetID: AXK200159

*******************************************************************************/
// Class declarations/imports below
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <queue>
#include "Game.h"
#include "BinTree.h"

using namespace std;

// Main class function prototypes below
void readData(BinTree<Game>&, string);
void readBatch(BinTree<Game>&, string);
void writeData(Node<Game>*, ofstream&);
void inorder(Node<Game>*, bool);

/*
* Driver of the program
*/
int main() {
    // Creates the input and output file streams, reading in the
    // names of the input files
    ifstream newFile1, newFile2;
    ofstream oFile;
    string inputFile1, inputFile2, nextLine;
    cin >> inputFile1 >> inputFile2;

    // Cretes the binary search tree to be used for the driver
    BinTree<Game> bst;

    // Opens all of the input/output files
    newFile1.open(inputFile1);
    newFile2.open(inputFile2);
    oFile.open("cidercade.dat");

    if (newFile1.is_open()) {
        // Reads through each line in database file, adding the
        // data to the BST
        while (getline(newFile1, nextLine)) {
            readData(bst, nextLine);
        }
    }
    if (newFile2.is_open()) {
        // Reads through each line in the batch file, outputting 
        // approprate info and editing the BST as necessary
        while (getline(newFile2, nextLine)) {
            readBatch(bst, nextLine);
        }
    }
    if (oFile.is_open()) {
        // Writes the database to the output file
        writeData(bst.getRoot(), oFile);
    }

    // Closes the files and the entire program
    newFile1.close();
    newFile2.close();
    oFile.close();

    return 0;
}

/*
* Reads the line of data, inputting it into the BST
*/
void readData(BinTree<Game>& b, string line) {
    // Finds the spot of the end of the name in order to read
    // the rest of the data properly
    long endName = line.find(",");
    string name, rest, score, in, plays;
    name = line.substr(0, endName);
    rest = line.substr(endName + 2);
    stringstream ss(rest);

    // Reads in and creates the variables holding the data
    ss >> score >> in >> plays;
    score = score.substr(0, score.length() - 1);
    in = in.substr(0, in.length() - 1);
    plays = plays.substr(0, plays.length() - 1);
    long s = stol(score);
    int p = stoi(plays);

    // Creates the objects and nodes for the data, inserting it into the BST
    Game obj(name, s, in, p);
    Node<Game>* add = new Node<Game>(obj);
    b.insert(b.getRoot(), add);
}

/*
* Reads through the batch file line, determining the action and
* outputting the necessary information while making changes
* as required to the BST
*/
void readBatch(BinTree<Game>& b, string line) {
    // Reads in the line to a stringstream
    stringstream ss(line);
    string lineType;
    ss >> lineType;

    // Iterates if the command is to add data to the BST
    if (lineType == "1") {
        // Finds the end of the name in order to properly read all of the data
        // Reads in and stores the data to put into an object
        string name, rest, score, in, plays;
        long cutoff = line.find("\"", 3);
        name = line.substr(3, cutoff - 3);
        rest = line.substr(cutoff + 2);
        stringstream addss(rest);

        addss >> score >> in >> plays;
        long s = stol(score);
        int p = stoi(plays);

        // Creates the objects and nodes for the data, inserting it into the BST
        Game temp(name, s, in, p);
        Node<Game>* add = new Node<Game>(temp);
        b.insert(b.getRoot(), add);

        // Outputs the successful command, showing the contents of the object created
        cout << "RECORD ADDED" << endl << "Name: " << temp.getName() << endl;
        cout << "High Score: " << temp.getScore() << endl << "Initials: ";
        cout << temp.getInitials() << endl << "Plays: " << temp.getPlays() << endl;
        cout << "Revenue: $";
        printf("%.2f", temp.getRevenue());
        cout << endl << endl;
    }
    // Iterates if the command is to search for data in the BST
    else if (lineType == "2") {
        // Creates to node to check if the data matches an object in the BST
        string name = line.substr(2);
        Node<Game>* output = new Node<Game>();
        output = b.search(b.getRoot(), name);

        // Iterates if the data is not found in the BST
        if (output == nullptr)
            cout << name << " NOT FOUND" << endl << endl;
        else {
            Game obj = output->getObj();

            // Outputs the successful command, showing the contents of the object found
            cout << name << " FOUND" << endl << "High Score: " << obj.getScore();
            cout << endl << "Initials: " << obj.getInitials() << endl;
            cout << "Plays: " << obj.getPlays() << endl << "Revenue: $";
            printf("%.2f", obj.getRevenue());
            cout << endl << endl;
        }
    }
    // Iterates if the command is to edit a certain portion of the BST data
    else if (lineType == "3") {
        // Finds the end of the name in order to properly read all of the data
        string name, rest, fieldNum, newVal;
        string field = "";
        long cutoff = line.find("\"", 3);
        name = line.substr(3, cutoff - 3);
        rest = line.substr(cutoff + 2);

        // Reads in and stores the data
        stringstream restss(rest);
        restss >> fieldNum >> newVal;

        // Searches through and finds the object to be changed
        Node<Game>* edit = b.search(b.getRoot(), name);
        Game change = edit->getObj();

        // Iterates if the score of the entry is to be updated
        if (fieldNum == "1") {
            field = "high score - ";
            long v = stol(newVal);
            change.setScore(v);
            edit->setObj(change);
        }
        // Iterates if the initials of the entry are to be updated
        else if (fieldNum == "2") {
            field = "initials - ";
            change.setInitials(newVal);
            edit->setObj(change);
        }
        // Iterates if the amount of plays of the entry are to be updated
        else if (fieldNum == "3") {
            field = "plays - ";
            int v = stoi(newVal);
            change.setPlays(v);
            edit->setObj(change);
        }

        Game obj = edit->getObj();

        // Outputs the successful command, showing the contents of the object edited
        cout << obj.getName() << " UPDATED" << endl << "UPDATE TO " << field;
        cout << "VALUE " << newVal << endl << "High Score: " << obj.getScore();
        cout << endl << "Initials: " << obj.getInitials() << endl << "Plays: ";
        cout << obj.getPlays() << endl << "Revenue: $";
        printf("%.2f", obj.getRevenue());
        cout << endl << endl;

    }
    // Iterates if the command is to delete an entry from the BST
    else if (lineType == "4") {
        // Creates the object to find the object to delete the data
        string name = line.substr(2);
        Game obj = b.del(name);

        // Outputs the successful command, showing the contents of the object deleted
        cout << "RECORD DELETED" << endl << "Name: " << obj.getName() << endl;
        cout << "High Score: " << obj.getScore() << endl << "Initials: ";
        cout << obj.getInitials() << endl << "Plays: " << obj.getPlays() << endl;
        cout << "Revenue: $";
        printf("%.2f", obj.getRevenue());
        cout << endl << endl;
    }
    // Iterates if the command is to sort/display the contents of the BST
    else if (lineType == "5") {
        string order;
        ss >> order;
        cout << "RECORDS SORTED ";

        // Prints the records in ascending order
        if (order == "asc") {
            cout << "ASCENDING" << endl;
            inorder(b.getRoot(), true);
            cout << endl;
        }
        // Prints the records in descending order
        else if (order == "des") {
            cout << "DESCENDING" << endl;
            inorder(b.getRoot(), false);
            cout << endl;
        }
    }
}

/*
* Writes the contents of the entire database to an output file,
* traversing through the BST using a breadth-first/level order traversal
*/
void writeData(Node<Game>* p, ofstream& file) {
    // Exits the method if the BST is empty
    if (p == nullptr)
        return;

    // Creates the queue used to iterate through the BST, pushing the root
    queue<Node<Game>*> list;
    list.push(p);

    // Iterates until the queue is empty and all of the data is outputted
    while (!list.empty()) {
        // Creates the object at the front of the queue to output to the file
        Node<Game>* n = list.front();
        Game obj = n->getObj();
        file << obj;

        // Removes the front of the queue once printed
        list.pop();

        // Pushes the left child of the node to the queue if it exists
        if (n->getLeft() != nullptr)
            list.push(n->getLeft());
        // Pushes the right child of the node to the queue if it exists
        if (n->getRight() != nullptr)
            list.push(n->getRight());
    }
}

/*
* Performs an in order depth-first traversal of the BST, outputting
* the contents of the tree recursively
*/
void inorder(Node<Game>* n, bool asc) {
    // Exits the method if the node does not exist
    if (n) {
        // Iterates if the BST is being printed in order,
        // recursively calling itself
        if (asc) {
            inorder(n->getLeft(), asc);
            cout << n->getObj();
            inorder(n->getRight(), asc);
        }
        // Iterates if the BST is being printed in reverse order,
        // recursively calling itself
        else {
            inorder(n->getRight(), asc);
            cout << n->getObj();
            inorder(n->getLeft(), asc);
        }
    }
}