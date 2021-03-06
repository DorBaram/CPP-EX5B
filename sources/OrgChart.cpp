#include "OrgChart.hpp"

namespace ariel{
    OrgChart::OrgChart() : nodeCount(0) {}
    OrgChart::~OrgChart() {}
    //מקבלת קלט אחד ושמה אותו בשורש של העץ. אם כבר יש משהו בשורש, הוא מוחלף.
    OrgChart &OrgChart::add_root(const string &rootname){
        if (nodeCount == 0){
            nodeCount++;
        }
        this->root.setName(rootname);
        return *this;
    }
    //מקבלת שני קלטים. אדם (או מחלקה) שכבר קיימים במבנה הארגוני ואדם נוסף (או מחלקה נוספת) אשר מדווחים לאדם הראשון ונמצאים מתחתיו בהיררכיה הארגונית.
    OrgChart &OrgChart::add_sub(const string& top, const string& bot){
        if (root.getName().empty() || nodeCount <= 0){
            throw invalid_argument("no root found");
        }
        if (top.empty() || bot.empty() || top == " " || bot == " " || top == "\n" || bot == "\n"|| top == "\t" || bot == "\t"|| top == "\r" || bot == "\r"){
            throw invalid_argument("top or bot must be a valid string");
        }
        if(recursive_add_sub(root,top,bot)){
            return *this;
        }
        throw invalid_argument("didnt find top");
    }
    bool OrgChart::recursive_add_sub(Node &starting,const string &top,const string &bot){
        if(starting.getName() == top){
            starting.addChild(bot);
            nodeCount++;
            return true;
        }
        for (auto& i:starting.getChildrens()){
            if (recursive_add_sub(i,top,bot)){
                return true;
            }
        }
        return false;
    }
    
    // output
    ostream& operator<<(ostream& out, const OrgChart& root){
        out << root.root;
        return out;
    }
    //מחזירות איטרטורים לצורך מעבר בסדר level order (אב - בן - בן - נכד).
    OrgChart::Iter OrgChart::begin_level_order(){
        check();
        Iter I(&root,0);
        I.getQ().push(I.getN());
        return I;
    }
    OrgChart::Iter OrgChart::end_level_order()const{
        check();
        return Iter(nullptr,0);
    }

    //מחזירות איטרטורים לצורך מעבר בסדר reverse level order (נכד - נכד - בן - בן - אב).
    OrgChart::Iter OrgChart::begin_reverse_order(){
        check();
        Iter I(&root,1);
        queue<Node*>& q = I.getQ();
        stack<Node*>& s = I.getS();
        q.push(I.getN());
        while (!q.empty()){
            Node* tmp = q.front();
            s.push(q.front());
            q.pop();
            
            for (int i = (int)tmp->getChildrens().size()-1; i > -1; i--){     //insert all the childerns into q
                q.push(&tmp->getChildrens().at((size_t)i));
            }
        }
        I.setN(s.top());
        return I;
    }
    //מחזירות איטרטורים לצורך מעבר בסדר preorder (אב - בן - נכד - בן - נכד)
    OrgChart::Iter OrgChart::begin_preorder(){
        check();
        Iter I(&root,2);
        I.getV().push_back(I.getN());
        return I;
    }
    OrgChart::Iter OrgChart::end_preorder()const{
        check();
        Iter I(nullptr,2);
        return I;
    }
    OrgChart::Iter OrgChart::reverse_order()const{
        check();
        Iter I(nullptr,1);
        return I;
    }
    void OrgChart::check()const{
        if (nodeCount == 0){
            throw invalid_argument("no nodes in chart");
        }
    }

    //Iter class here
    //getters
    Node* OrgChart::Iter::getN(){
        return curr;
    }
    vector<Node*>& OrgChart::Iter::getV(){
        return vect;
    }
    stack<Node*>& OrgChart::Iter::getS(){
        return stac;
    }
    queue<Node*>& OrgChart::Iter::getQ(){
        return queu;
    }
    //setter
    void OrgChart::Iter::setN(Node* n){
        curr = n;
    }
    //operators
    bool OrgChart::Iter::operator==(const Iter& other)const{
        return (this->curr == other.curr);
    }
    bool OrgChart::Iter::operator!=(const Iter& other)const{
        return (this->curr != other.curr);
    }
    string& OrgChart::Iter::operator*(){//returns the name of the current node
        return this->getN()->getName();
    }    
    Node* OrgChart::Iter::operator->(){
        return curr;
    }
    OrgChart::Iter& OrgChart::Iter::operator++(){
        switch (order){
        case 0:
            return levelOrder();
            break;
        case 1:
            return reverseOrder();
            break;
        case 2:
            return preOrder();
            break;
        default:
            break;
        }
        if (order>2){
            throw runtime_error("no order found");
        }
        return *this; //should not get here at all...
    }
    //orders
    OrgChart::Iter& OrgChart::Iter::levelOrder(){
        vector<Node>& tmp = curr->getChildrens();
        for (size_t i = 0; i < tmp.size(); i++){
            queu.push(&tmp.at(i));
        }
        queu.pop();
        if (queu.empty()){
            curr = nullptr;
        }
        else{
            curr = queu.front();
        }
        return *this;
    }
    OrgChart::Iter& OrgChart::Iter::reverseOrder(){
        stac.pop();
        if (stac.empty()){
            curr = nullptr;
        }
        else{
            curr = stac.top();
        }
        return *this;
    }
    OrgChart::Iter& OrgChart::Iter::preOrder(){
        if (vect.empty()){
            curr = nullptr;
            return *this;
        }
        curr = vect.at(0);
        vect.erase(vect.begin());
        vector<Node>& tmp = curr->getChildrens();
        for (size_t i = 0; i < tmp.size(); i++){
            vect.insert(vect.begin() + (int)i, &tmp.at(i));
        }
        if (vect.empty()){
            curr = nullptr;
            return *this;
        }
        curr = vect.at(0);
        return *this;  
    }

}