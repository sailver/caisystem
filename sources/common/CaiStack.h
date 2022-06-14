#ifndef CAISTACK_H
#define CAISTACK_H

template <class T>
struct stackNode {
    T data;
    stackNode *next;
};

template<class T>
class CaiStack {
private:
    unsigned int length;
    unsigned int maxSize;
    stackNode<T>* top;
public:
    CaiStack();
    CaiStack(unsigned int maxSize);
    ~CaiStack();
    int push(T data);
    T pop();
    T getTop();
    bool isEmpty();
    bool isFull();
};

template<class T>
CaiStack<T>::CaiStack()
{
    length = 0;
    maxSize = 100;
    top = nullptr;
}
template<class T>
CaiStack<T>::CaiStack(unsigned int ms)
{
    length = 0;
    maxSize = ms;
    top = nullptr;
}
template<class T>
CaiStack<T>::~CaiStack()
{
    stackNode<T>* p = new stackNode<T>;
    for (unsigned int i = length; i >0; i--)
    {
        p = top;
        top = p->next;
        delete p;
    }
}
template<class T>
int CaiStack<T>::push(T data)
{
    length++;
    if (isFull())
    {
        return -1;
    }
    stackNode<T>* node = new stackNode<T>;
    node->data = data;
    node->next = top;
    top = node;
    return length;
}
template<class T>
T CaiStack<T>::pop()
{
    stackNode<T>* p = top;
    top = top->next;
    T t = p->data;
    delete p;
    length--;
    return t;
}
template<class T>
T CaiStack<T>::getTop()
{
    return top->data;
}
template<class T>
bool CaiStack<T>::isEmpty()
{
    return length == 0 ? true : false;
}
template<class T>
bool CaiStack<T>::isFull()
{
    return length >= maxSize ? true : false;
}

#endif // CAISTACK_H
