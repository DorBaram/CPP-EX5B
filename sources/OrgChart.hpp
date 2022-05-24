#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <stdexcept>
#include <string>
using namespace std;
#include "Node.hpp"
#pragma once

namespace ariel{
    class OrgChart{
        private:
            Node root;
            int nodeCount;

        public:
        //inner class for iterator
        class Iter{
            private:
                Node* curr;
                int order;  //orders are 1=level order, 2=reverse order, 3=preorder
                vector<Node*> vect;
                stack<Node*> stac;      //for reverse order
                queue<Node*> queu;      //for level order
            public:
                Iter(Node* n, int o){   //constructor
                    curr = n;
                    order = o;
                }
                ~Iter(){}   //destructor
                //getters
                Node* getN();
                vector<Node*>& getV();
                stack<Node*>& getS();
                queue<Node*>& getQ();
                //setter
                void setN(Node* n);
                //operators
                bool operator==(const Iter& other);
                bool operator!=(const Iter& other);
                string& operator*();    //returns the name of the current node
                Node* operator->();
                Iter& operator++();
                //orders
                Iter& levelOrder();
                Iter& reverseOrder();
                Iter& preOrder();
        };
        //constructor + destructor
        OrgChart();
        ~OrgChart();
        //מקבלת קלט אחד ושמה אותו בשורש של העץ. אם כבר יש משהו בשורש, הוא מוחלף.
        OrgChart& add_root(string rootname);
        //מקבלת שני קלטים. אדם (או מחלקה) שכבר קיימים במבנה הארגוני ואדם נוסף (או מחלקה נוספת) אשר מדווחים לאדם הראשון ונמצאים מתחתיו בהיררכיה הארגונית.
        OrgChart& add_sub(const string& top, const string& bot);
        //מחזירות איטרטורים לצורך מעבר בסדר level order (אב - בן - בן - נכד).
        Iter begin_level_order();
        Iter end_level_order()const;
        //מחזירות איטרטורים לצורך מעבר בסדר reverse level order (נכד - נכד - בן - בן - אב).
        Iter begin_reverse_order();
        //מחזירות איטרטורים לצורך מעבר בסדר preorder (אב - בן - נכד - בן - נכד)
        Iter begin_preorder();
        Iter end_preorder()const;
        Iter reverse_order()const;
        //for loops {i in x}
        Iter begin(){return begin_level_order();}
        Iter end()const{return end_level_order();}
        //for output
        friend ostream& operator<<(ostream& out, const OrgChart& root);   
        void check()const;
    };
}