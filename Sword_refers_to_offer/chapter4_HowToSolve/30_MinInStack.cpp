#include<bits/stdc++.h>
using namespace std;

// 面试题30：包含min函数的栈
// 题目：定义栈的数据结构，请在该类型中实现一个能够得到栈的最小元素的min
// 函数。在该栈中，调用min、push及pop的时间复杂度都是O(1)。

template<typename T>
class StackWithMin{
private:
    stack<T> normal;
    stack<T> minStack;
public:
    StackWithMin() {}
    virtual ~StackWithMin() {}

    void push(T in);
    T min() ;
    void pop();
};

template<typename T> void StackWithMin<T>::push(T in){
    normal.push(in);
    if(minStack.size() > 0 && minStack.top() < in)
        minStack.push(minStack.top());
    else
        minStack.push(in);
}

template<typename T>  T StackWithMin<T>::min(){
    if(minStack.size() > 0)
        return minStack.top();
    else
        return NULL;
}

template<typename T> void StackWithMin<T>::pop(){
    if(normal.size()>0 && minStack.size()>0){
        normal.pop();
        minStack.pop();
    }
    else
        return;
}


//================test===============
void Test(const char* testName,StackWithMin<int>& stack, int expected)
{
    if(testName != nullptr)
        printf("%s begins: ", testName);

    if(stack.min() == expected)
        printf("Passed.\n");
    else
        printf("Failed.\n");
}

int main(int argc, char* argv[])
{
    StackWithMin<int> stack;

    stack.push(3);
    Test("Test1", stack, 3);

    stack.push(4);
    Test("Test2", stack, 3);

    stack.push(2);
    Test("Test3", stack, 2);

    stack.push(3);
    Test("Test4", stack, 2);

    stack.pop();
    Test("Test5", stack, 2);

    stack.pop();
    Test("Test6", stack, 3);

    stack.pop();
    Test("Test7", stack, 3);

    stack.push(0);
    Test("Test8", stack, 0);

    return 0;
}