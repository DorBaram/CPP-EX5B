#include "Node.hpp"

namespace ariel{
    Node::Node(){}  //def constructor
    Node::Node(const string &n){   //constructor
        name = n;
    }
    Node::~Node(){} //destructor

    string& Node::getName(){//get name of the node
        return name;
    }      
    void Node::setName(string n){//set name of node
        name = move(n);
    }    
    vector<Node>& Node::getChildrens(){//get the vector of childrens of the node
        return childrens;
    }   
    void Node::addChild(const string &n){//add a child to the vector
        childrens.push_back(Node(n));
    }   
    int Node::population(){//returns the amount of childrens in vector
        return childrens.size();
    }   
    char Node::at(size_t i){//returns the name of the children at i
        return name.at(i);
    }  
    ostream& operator<<(ostream& out, const Node& n){//for output
        out << n.name;
        return out;
    }      
}