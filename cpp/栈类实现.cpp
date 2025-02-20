// 题目：实现一个通用的栈类
// 编写一个模板类 Stack<T>，表示一个后进先出（LIFO）的栈。要求：
// 支持动态扩容。
// 提供 push(T value)、pop()、top()、isEmpty() 等基本操作。
// 提供拷贝构造函数和赋值运算符重载，确保深拷贝。
// 提供 size() 函数，返回当前栈中元素的数量。
// （可选）支持迭代器，可以使用范围for循环遍历栈

#include<iostream>
#include<vector>

using namespace std;

template<class T>
class  Stack{
public:
    Stack(){

    };
    Stack(const Stack& s);//拷贝构造函数
    Stack& operator=(const Stack& s);//赋值运算符重载
    void push(T value);//加到栈顶
    void pop();//移除栈顶元素
    T& top();//获取栈顶元素
    bool isEmpty();//判断栈是否为空
    size_t size();//得到栈中元素的数量
private:
    vector<T> container;//用vector实现动态扩容，应该可以吧TT
};

//以下是函数实现std::
template<class T>
Stack<T>::Stack(const Stack& s){
    container=s.container;//vector自身实现深拷贝
}

template<class T>
Stack<T>& Stack<T>::operator=(const Stack& s){
    container = s.container;
    return *this;
}
template<class T>
void Stack<T>::push(T value){
    container.push_back(value);
}
template<class T>
void Stack<T>::pop(){
    container.pop_back();
}
template<class T>
T& Stack<T>::top(){
    return container.back();
}
template<class T>
size_t Stack<T>::size(){
    size_t sizee;
    sizee=container.size();
    return sizee;
}

int main() {
    Stack<int> stack;
    stack.push(10);
    stack.push(20);
    stack.push(30);

    cout << "Stack size: " << stack.size() << endl;
    cout << "Top element: " <<stack.top() << endl;

    stack.pop();
    cout << "After pop, top element: " << stack.top() << endl;

    Stack<int> anotherStack = stack;
    cout << "Another stack size: " << anotherStack.size() <<endl;

    return 0;
}//测试代码