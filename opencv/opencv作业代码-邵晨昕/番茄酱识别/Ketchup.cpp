#include <opencv2/opencv.hpp>
#include <iostream>

int main() {

    cv::Mat image=cv::imread("Ketchup_Packet.png");
    if (image.empty()){
        std::cerr<<"Error"<<std::endl;
        return 0;
    }

    //图像预处理，转灰度图+二值处理+高斯模糊+边缘检测
    cv::Mat gray,binary,blurred,edges;
    cv::cvtColor(image,gray,cv::COLOR_BGR2GRAY);
    cv::threshold(gray,binary,0,255,cv::THRESH_BINARY_INV|cv::THRESH_OTSU);
    cv::GaussianBlur(binary,blurred,cv::Size(5, 5), 0);
    cv::Canny(blurred,edges,50,150);

    //检测轮廓
    std::vector<std::vector<cv::Point>>contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(edges,contours,hierarchy,cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    //绘制轮廓
    std::vector<cv::Point> maxContour;
    for (size_t i=0;i<contours.size();i++) {
        double area=cv::contourArea(contours[i]);
        std::cout<<area<<std::endl;
        if (area>100000) {
            cv::drawContours(image,contours,i,cv::Scalar(255,0,0),5);
            maxContour=contours[i];
        }
    }

    cv::imshow("demo",image);

    ////////////仿射变换////////////

    std::vector<cv::Point> hull;
    cv::convexHull(maxContour,hull);

    //找到凸包的四个角点（近似四边形）
    std::vector<cv::Point> approx;
    cv::approxPolyDP(hull,approx,0.02 * cv::arcLength(hull, true), true);

    if (approx.size()== 4) {
    //定义目标矩形的四个角点
        std::vector<cv::Point2f> targetPoints={
            cv::Point2f(0,0),
            cv::Point2f(400,0),
            cv::Point2f(400,800),
            cv::Point2f(0,800)
        };
    
    //将点转换为cv::Point2f
    std::vector<cv::Point2f> srcPoints;
    for (const auto& point:approx) {
        srcPoints.push_back(cv::Point2f(point.x,point.y));
    }

    //透视变换矩阵
    cv::Mat transformMatrix=cv::getPerspectiveTransform(srcPoints,targetPoints);
    cv::Mat demoo;
    cv::warpPerspective(image,demoo,transformMatrix,cv::Size(400,800));
    cv::imshow("仿射变换",demoo);
}

    cv::waitKey(0);

    return 0;
}
