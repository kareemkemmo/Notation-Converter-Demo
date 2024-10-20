#include "NotationConverter.hpp"

// ----------------------------------- Doubly Linked List Implementation ------------------------------

Dlinkedlist::Dlinkedlist(){
    header = new Dnode;
    trailer = new Dnode;
    header->next = trailer;
    trailer->prev = header;
}
Dlinkedlist::~Dlinkedlist(){
    while(!empty())removeFront();
    delete header;
    delete trailer;
}
bool Dlinkedlist::empty() const{
    return header->next == trailer;
}
const string& Dlinkedlist::front() const{
    return header->next->elem;
}
const string& Dlinkedlist::back() const{
    return trailer->prev->elem;
}
void Dlinkedlist::addFront(const string& e){
    Dnode* new_node = new Dnode;
    new_node->elem = e;
    new_node->next = header->next;
    new_node->prev = header;
    header->next = new_node;
    header->next->prev = new_node;
}
void Dlinkedlist::addBack(const string& e){
    Dnode* new_node = new Dnode;
    new_node->elem = e;
    new_node->next = trailer;
    new_node->prev = trailer->prev;
    trailer->prev = new_node;
    trailer->prev->next = new_node;
}
void Dlinkedlist::removeFront(){
    if (!empty()){
    Dnode* old = header->next;
    Dnode* u = old->prev;
    Dnode* v = old->next;
    u->next = v;
    v->prev = u;
    delete old;
    }
}
void Dlinkedlist::removeBack(){
    if (!empty()){
    Dnode* old = trailer->prev;
    Dnode* u = old->prev;
    Dnode* v = old->next;
    u->next = v;
    v->prev = u;
    delete old;
    }
}

// ----------------------------------- Double Ended Queue Implementation ------------------------------

Deque::Deque(){
    n = 0;
}
int Deque::size() const{
    return n;
}
bool Deque::empty() const{
    return D.empty();
}
const string& Deque::front() const{
    return D.front();
}
const string& Deque::back() const{
    return D.back();
}
void Deque::push_front(const string& e){
    D.addFront(e);
}
void Deque::push_back(const string& e){
    D.addBack(e);
}
void Deque::pop_front(){
    D.removeFront();
}
void Deque::pop_back(){
    D.removeBack();
}




// ------------------------------------ Notation Covertion Functions ----------------------------------
//the idea behind using deques to convert:
//we can create a deque of strings and we can push onto it the operands in order
//if an operator is encountered we can reformat the combination as we wish
//pop the old format and push the new format
string NotationConverter::postfixToInfix(std::string inStr){
    Deque infix_format;//string deque created (used string instead of char so that inputs could include operand expressions as well as single operands)
    for (int i = 0; i < inStr.length(); i++) {//iterate through word
        if((inStr[i] >= 'a' && inStr[i] <= 'z') || (inStr[i] >= 'A' && inStr[i] <= 'Z')){//if char is an operand
            string operand(1, inStr[i]);//turn operand char into an operand string
            infix_format.push_front(operand);// push the operand to the front of the deque
        }        
        else if ((inStr[i] == '*') || (inStr[i] == '/') || (inStr[i] == '+') || (inStr[i] == '-')){//if char is an operation
            string frst_operand = infix_format.front();//get the first operand from the deque front
            infix_format.pop_front();//pop the operand from the front (stack like use)
            string scnd_operand = infix_format.front();//get the second operand from the front
            infix_format.pop_front();//pop the second operand from the front
            string new_operand = '(' + scnd_operand + inStr[i] + frst_operand + ')';//create new operand as a combo of the two, brackets, and the operation (reformating the operand to infix)
            infix_format.push_front(new_operand);//add the newly formated operand to the deque front
        }
        
        else if (inStr[i] == ' '){// if whitespace
            //do nothing
        }
        else{// if any other char
        //throw exception
        }
    };
    return infix_format.front();//after converting all the operands and operation to infix format the operands would be reformed to infix as a single string at the top of the stack
}
//the code for prefix to postfix is similar just with different formating in the new operand, iterating in the reverse order
string NotationConverter::prefixToPostfix(std::string inStr){
    Deque postfix_format;//string deque created (used string instead of char so that inputs could include operand expressions as well as single operands)
    for (int i = inStr.length()-1; i >= 0; i--) {//iterate through word in reverse order
        if((inStr[i] >= 'a' && inStr[i] <= 'z') || (inStr[i] >= 'A' && inStr[i] <= 'Z')){//if char is an operand
            string operand(1, inStr[i]);//turn operand char into an operand string
            postfix_format.push_front(operand);// push the operand to the front of the deque
        }        
        else if ((inStr[i] == '*') || (inStr[i] == '/') || (inStr[i] == '+') || (inStr[i] == '-')){//if char is an operation
            string frst_operand = postfix_format.front();//get the first operand from the deque front
            postfix_format.pop_front();//pop the operand from the front (stack like use)
            string scnd_operand = postfix_format.front();//get the second operand from the front
            postfix_format.pop_front();//pop the second operand from the front
            string new_operand = frst_operand + scnd_operand + inStr[i];//create new operand as a combo of the two and the operation (reformating the operand to postfix)
            postfix_format.push_front(new_operand);//add the newly formated operand to the deque front
        }
        else if (inStr[i] == ' '){// if whitespace
            //do nothing
        }
        else{// if any other char
        //throw exception
        }
    };
    return postfix_format.front();//after converting all the operands and operation to infix format the operands would be reformed to infix as a single string at the top of the stack
}
//the code for infix to prefix is the same as the rest with the difference being that the new operand is created with a ')' and refactors the 2 operands and operator before it
string NotationConverter::infixToPrefix(std::string inStr){
    Deque prefix_format;//string deque created (used string instead of char so that inputs could include operand expressions as well as single operands)
    for (int i = 0; i < inStr.length(); i++) {//iterate through word in reverse order
        if((inStr[i] >= 'a' && inStr[i] <= 'z') || (inStr[i] >= 'A' && inStr[i] <= 'Z')){//if char is an operand
            string operand(1, inStr[i]);//turn operand char into an operand string
            prefix_format.push_front(operand);// push the operand to the front of the deque
        }        
        else if ((inStr[i] == '*') || (inStr[i] == '/') || (inStr[i] == '+') || (inStr[i] == '-') || (inStr[i] == '(')){//if char is an operation or an opening bracket '('
            string operation(1, inStr[i]);//turn operand char into an operand string
            prefix_format.push_front(operation);// push the operand to the front of the deque
        }
        else if (inStr[i] == ')'){//if char is a closing bracket ')'
            string frst_operand = prefix_format.front();//get the first operand from the deque front
            prefix_format.pop_front();//pop the operand from the front (stack like use)
            string operation = prefix_format.front();//get the operation from the deque front
            prefix_format.pop_front();//pop the operation from the front (stack like use)
            string scnd_operand = prefix_format.front();//get the second operand from the front
            prefix_format.pop_front();//pop the second operand from the front
            prefix_format.pop_front();//pop the opening bracket '('
            string new_operand =  operation + scnd_operand +  frst_operand;//create new operand as a combo of the two and the operation (reformating the operand to postfix)
            prefix_format.push_front(new_operand);//add the newly formated operand to the deque front
        }
        else if (inStr[i] == ' '){// if whitespace
            //do nothing
        }
        else{// if any other char
        //throw exception
        }
    };
    return prefix_format.front();//after converting all the operands and operation to infix format the operands would be reformed to infix as a single string at the top of the stack
}
string NotationConverter::infixToPostfix(std::string inStr){
    string prefix_str = infixToPrefix(inStr);
    string postfix_str = prefixToPostfix(prefix_str);
    return postfix_str;//after converting all the operands and operation to infix format the operands would be reformed to infix as a single string at the top of the stack
}
string NotationConverter::prefixToInfix(std::string inStr){
    string postfix_str = prefixToPostfix(inStr);
    string infix_str = postfixToInfix(postfix_str);
    return infix_str;//after converting all the operands and operation to infix format the operands would be reformed to infix as a single string at the top of the stack
}
string NotationConverter::postfixToPrefix(std::string inStr){
    string infix_str = postfixToInfix(inStr);
    string prefix_str = infixToPrefix(infix_str);
    return prefix_str;//after converting all the operands and operation to infix format the operands would be reformed to infix as a single string at the top of the stack
}