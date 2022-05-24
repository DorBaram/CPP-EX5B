#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>
using namespace std;

#pragma once

namespace ariel{
    class Node{
        private:
            string name;
            vector<Node> childrens;

        public:
            Node();                   //def constructor
            Node(const string &n);    //constructor
            ~Node();                  //destructor
            int size() {return name.size();}
            int length() {return size();}
            string& getName();         //get name of the node
            void setName(const string &n);  //set name of node

            vector<Node>& getChildrens();   //get the vector of childrens of the node
            void addChild(const string &n); //add a child to the vector

            int population();   //returns the amount of childrens in vector
            char at(size_t i);  //returns the name of the children at i

            friend ostream& operator<<(ostream& out, const Node& n);  //for output stream

    };
}