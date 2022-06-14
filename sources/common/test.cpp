#include <iostream>
#include "SkipList.h"

class testClass {
    //  所需重载的关系运算符
    friend bool operator==(testClass a, testClass b);
    friend bool operator>(testClass a, testClass b);
};

bool operator>(testClass a, testClass b) {
    
}

int main() {

}