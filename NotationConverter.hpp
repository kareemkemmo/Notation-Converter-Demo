#include <iostream>
#include "NotationConverterInterface.hpp"
using namespace std;

struct Dnode {
    private:
    string elem;
    Dnode* next;
    Dnode* prev;
    friend class Dlinkedlist;
};

class Dlinkedlist{
    public:
    Dlinkedlist();
    ~Dlinkedlist();
    bool empty() const;
    const string& front() const;
    const string& back() const;
    void addFront(const string& e);
    void addBack(const string& e);
    void removeFront();
    void removeBack();
    private:
    Dnode* header;
    Dnode* trailer;
};
class Deque{
    public:
    Deque();
    int size() const;
    bool empty() const;
    const string& front() const;
    const string& back() const;    
    void push_front(const string& e);
    void push_back(const string& e);
    void pop_front();
    void pop_back();
    private:
    Dlinkedlist D;
    int n;
};

class NotationConverter: public NotationConverterInterface
{
public:
  string postfixToInfix(std::string inStr);
  string postfixToPrefix(std::string inStr);

  string infixToPostfix(std::string inStr);
  string infixToPrefix(std::string inStr);

  string prefixToInfix(std::string inStr);
  string prefixToPostfix(std::string inStr);
};