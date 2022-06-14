#ifndef SKIPLIST_H
#define SKIPLIST_H
#include "CaiStack.h"
#include <random>
#include <ctime>
#include <iostream>
#include <iomanip>
using namespace std;

template <class T>
class SkipNode
{
public:
    long long key;
    T data;
    SkipNode<T> *pre, *next, *up, *down;
    SkipNode()
    {
        key = 0;
        pre = nullptr;
        next = nullptr;
        up = nullptr;
        down = nullptr;
    };
    SkipNode(long long ikey, T idata)
    {
        key = ikey;
        data = idata;
        pre = nullptr;
        next = nullptr;
        up = nullptr;
        down = nullptr;
    }
};

template <class T>
class SkipList
{
public:
    SkipNode<T> *headNode;    //头节点，入口
    int level;                //当前跳表索引层数
    int length;               //长度
    int rearId;               //最后一个data的id
    double randomDouble();        //根据层数生成随机数
    const int MAX_LEVEL = 32; //最大的层
    SkipList()
    {
        headNode = new SkipNode<T>();
        level = 0;
        length = 0;
    }
    long long insert(T data);
    long long update(SkipNode<T> node);
    void update(long long ikey, T data);
    void deleteByKey(long long key);
    SkipNode<T> *findByKey(long long key);
    SkipList<T> *findByData(T data);
    long long findIdByData(T data);
    template <typename E>
    SkipNode<T> *findByData(string name, E e);
    void setRearId(long long key){this->rearId = key;}
    int getRearId(){return this->rearId;}
    void printList();
};

template <class T>
long long SkipList<T>::insert(T data)
{
    int idTemp;
    if (!length)
        idTemp = 1;
    else
        idTemp = (this->getRearId()) + 1;
    this->update(idTemp, data);
    this->setRearId(idTemp);
    return idTemp;
}

template <class T>
SkipNode<T> *SkipList<T>::findByKey(long long key)
{
    SkipNode<T> *temp = headNode;
    while (temp != nullptr)
    {
        if (temp->key == key)
        {
            return temp;
        }
        else if (temp->next == nullptr)
        { //右侧null，向下
            temp = temp->down;
        }
        else if (temp->next->key > key)
        { //右侧较大，向下
            temp = temp->down;
        }
        else
        {
            temp = temp->next;
        }
    }
    return nullptr;
}

template <class T>
SkipList<T> *SkipList<T>::findByData(T data)
{
    SkipList<T> *res = new SkipList<T>();
    SkipNode<T> *temp = headNode;
    while (temp->down != nullptr) {
        temp = temp->down;
    }
    while(temp != nullptr) {
        if (temp->data == data)
        {
            res->insert(temp->data);
        }
        temp = temp->next;
    }
    return res;
}

template <class T>
void SkipList<T>::deleteByKey(long long key)
{
    SkipNode<T> *temp = headNode;
    while (temp != nullptr)
    {
        if (temp->next == nullptr)
        { //右侧没有了，说明这一层找到，没有只能下降
            temp = temp->down;
        }
        else if (temp->next->key == key) //找到节点，右侧即为待删除节点
        {
            temp->next = temp->next->next; //删除右侧节点
            temp = temp->down;             //向下继续查找删除
        }
        else if (temp->next->key > key) //右侧已经不可能了，向下
        {
            temp = temp->down;
        }
        else
        { //节点还在右侧
            temp = temp->next;
        }
    }
    this->length--;
}

template <class T>
double SkipList<T>::randomDouble()
{
    default_random_engine e(time(0));
    uniform_real_distribution<double> u(-1.2, 3.5);
    return u(e);
}

template <class T>
long long SkipList<T>::findIdByData(T data)
{
    SkipList<T> *res = new SkipList<T>();
    SkipNode<T> *temp = headNode;
    while (temp->down != nullptr) {
        temp = temp->down;
    }
    while(temp != nullptr) {
        if (temp->data == data)
        {
            return temp->key;
        }
        temp = temp->next;
    }
    return 0;
}

template <class T>
long long SkipList<T>::update(SkipNode<T> node)
{
    long long key = node.key;
    SkipNode<T> *findNode = findByKey(key);
    if (findNode != nullptr) //如果存在这个key的节点
    {
        findNode->data = node.data;
        return 0;
    }

    CaiStack<SkipNode<T> *> stack; //存储向下的节点，这些节点可能在右侧插入节点
    SkipNode<T> *temp = headNode; //查找待插入的节点   找到最底层的节点。
    while (temp != nullptr)
    {                              //进行查找操作
        if (temp->next == nullptr) //右侧没有了，只能下降
        {
            stack.push(temp); //将曾经向下的节点记录一下
            temp = temp->down;
        }
        else if (temp->next->key > key) //需要下降去寻找
        {
            stack.push(temp); //将曾经向下的节点记录一下
            temp = temp->down;
        }
        else //向右
        {
            temp = temp->next;
        }
    }

    int currentlevel = 1;            //当前层数，从第一层添加(第一层必须添加，先添加再判断)
    SkipNode<T> *downNode = nullptr; //保持前驱节点(即down的指向，初始为null)
    while (!stack.isEmpty())
    {
        //在该层插入node
        temp = stack.pop();                                           //抛出待插入的左侧节点
        SkipNode<T> *nodetemp = new SkipNode<T>(node.key, node.data); //节点需要重新创建
        nodetemp->down = downNode;                                    //处理竖方向
        downNode = nodetemp;                                          //标记新的节点下次使用
        if (temp->next == nullptr)
        { //右侧为null 说明插入在末尾
            temp->next = nodetemp;
            this->rearId = nodetemp->key;
        }
        //水平方向处理
        else
        { //右侧还有节点，插入在两者之间
            nodetemp->next = temp->next;
            temp->next = nodetemp;
        }
        //考虑是否需要向上
        if (currentlevel > MAX_LEVEL) //已经到达最高级的节点啦
            break;
        double num = randomDouble(); //[0-1]随机数
        if (num > 0.5)               //运气不好结束
            break;
        currentlevel++;
        if (currentlevel > level) //比当前最大高度要高但是依然在允许范围内 需要改变head节点
        {
            level = currentlevel;
            //需要创建一个新的节点
            SkipNode<T> *highHeadNode = new SkipNode<T>;
            highHeadNode->down = headNode;
            headNode = highHeadNode; //改变head
            stack.push(headNode);    //下次抛出head
        }
    }
    this->length++;
    return 1;
}

template <class T>
void SkipList<T>::update(long long ikey, T data){
    SkipNode<T> node(ikey, data);
    long long key = node.key;
    SkipNode<T> *findNode = findByKey(key);
    if (findNode != nullptr) //如果存在这个key的节点
    {
        findNode->data = node.data;
        return;
    }

    CaiStack<SkipNode<T> *> stack; //存储向下的节点，这些节点可能在右侧插入节点
    SkipNode<T> *temp = headNode; //查找待插入的节点   找到最底层的节点。
    while (temp != nullptr)
    {                              //进行查找操作
        if (temp->next == nullptr) //右侧没有了，只能下降
        {
            stack.push(temp); //将曾经向下的节点记录一下
            temp = temp->down;
        }
        else if (temp->next->key > key) //需要下降去寻找
        {
            stack.push(temp); //将曾经向下的节点记录一下
            temp = temp->down;
        }
        else //向右
        {
            temp = temp->next;
        }
    }

    int currentlevel = 1;            //当前层数，从第一层添加(第一层必须添加，先添加再判断)
    SkipNode<T> *downNode = nullptr; //保持前驱节点(即down的指向，初始为null)
    while (!stack.isEmpty())
    {
        //在该层插入node
        temp = stack.pop();                                           //抛出待插入的左侧节点
        SkipNode<T> *nodetemp = new SkipNode<T>(node.key, node.data); //节点需要重新创建
        nodetemp->down = downNode;                                    //处理竖方向
        downNode = nodetemp;                                          //标记新的节点下次使用
        if (temp->next == nullptr)
        { //右侧为null 说明插入在末尾
            temp->next = nodetemp;
        }
        //水平方向处理
        else
        { //右侧还有节点，插入在两者之间
            nodetemp->next = temp->next;
            temp->next = nodetemp;
        }
        //考虑是否需要向上
        if (currentlevel > MAX_LEVEL) //已经到达最高级的节点啦
            break;
        double num = randomDouble(); //[0-1]随机数
        if (num > 0.5)               //运气不好结束
            break;
        currentlevel++;
        if (currentlevel > level) //比当前最大高度要高但是依然在允许范围内 需要改变head节点
        {
            level = currentlevel;
            //需要创建一个新的节点
            SkipNode<T> *highHeadNode = new SkipNode<T>;
            highHeadNode->down = headNode;
            headNode = highHeadNode; //改变head
            stack.push(headNode);    //下次抛出head
        }
    }
    this->length++;
}

template <class T>
void SkipList<T>::printList()
{
    SkipNode<T> *tempNode = headNode;
    int index = 1;
    SkipNode<T> *last = tempNode;
    while (last->down != nullptr)
    {
        last = last->down;
    }
    while (tempNode != nullptr)
    {
        SkipNode<T> *enumNode = tempNode->next;
        SkipNode<T> *enumLast = last->next;
        cout << left << setw(8) << "head->";
        while (enumLast != nullptr && enumNode != nullptr)
        {
            if (enumLast->key == enumNode->key)
            {
                cout << left << setw(5) << enumLast->key << "->";
                enumLast = enumLast->next;
                enumNode = enumNode->next;
            }
            else
            {
                enumLast = enumLast->next;
                cout << left << setw(5) << "";
            }
        }
        tempNode = tempNode->down;
        index++;
        cout << endl;
    }
}

#endif // SKIPLIST_H
