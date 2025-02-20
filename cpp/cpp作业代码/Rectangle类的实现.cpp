// 题目：实现一个简单的类
// 编写一个C++类 Rectangle，表示矩形。要求：

// 包含两个私有成员变量：width 和 height。

// 提供构造函数、拷贝构造函数、赋值运算符重载。

// 提供成员函数 area()，计算矩形的面积。

// 提供成员函数 resize(double scale)，按比例缩放矩形的宽度和高度。

// 提供友元函数 bool isSquare(const Rectangle& rect)，判断矩形是否为正方形。


#include<iostream>
using namespace std;

class Rectangle{
    friend bool isSquare(const Rectangle& rect);//友元函数，判断矩形是否为正方形
public:
    Rectangle(double w_width,double w_height);//构造函数
    Rectangle(const Rectangle &rec);//拷贝构造函数
    Rectangle& operator=(Rectangle& rec);//赋值运算符重载
    double area();//计算面积
    void resize(double scale);//按比例缩放矩形的宽度和高度
private:
    double width;
    double height;
};

Rectangle::Rectangle(double w_width,double w_height){
        width=w_width;
        height=w_height;
    }
Rectangle::Rectangle(const Rectangle &rec){
        width=rec.width;
        height=rec.height;
    }
Rectangle& Rectangle::operator=(Rectangle& rec){
        this->height=rec.height;
        this->width=rec.width;
        return *this;
    }
double Rectangle::area(){
    double area;
    area=width*height;
    return area;
}
void Rectangle::resize(double scale){
    width=width*scale;
    height=height*scale;
}
bool isSquare(const Rectangle& rect){
    if(rect.height==rect.width){
        return true;
    }
    else
        return false;
}

int main(){
    Rectangle r1(11.2,9.18);
    Rectangle r2=r1;
    Rectangle r3(r1);
    cout<<"r1面积是："<<r1.area()<<endl;
    cout<<"是否为正方形:"<<isSquare(r1)<<endl;
    cout<<"r2面积是："<<r2.area()<<endl;
    cout<<"r3面积是："<<r3.area()<<endl;
    return 0;
    
}
