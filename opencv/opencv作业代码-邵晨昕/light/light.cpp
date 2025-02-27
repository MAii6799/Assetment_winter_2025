#include <opencv2/opencv.hpp>
#include <iostream>

int main() {

    cv::Mat image=cv::imread("b1.png");
    if (image.empty()){
        std::cerr<<"Error"<<std::endl;
        return 0;
    }
    cv::resize(image,image,cv::Size(image.cols/2,image.rows/2));

    cv::Mat gray,binary,blurred,edges;
    cv::cvtColor(image,gray,cv::COLOR_BGR2GRAY);
    cv::threshold(gray,binary,0,255,cv::THRESH_BINARY_INV|cv::THRESH_OTSU);
    cv::Canny(binary,edges,50,150);

    //检测轮廓
    std::vector<std::vector<cv::Point>>contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(edges,contours,hierarchy,cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    //绘制轮廓
    for (size_t i = 0; i < contours.size(); i++) {
        double area = cv::contourArea(contours[i]);
        std::cout<<area<<std::endl;
        if (area > 100) {
            cv::drawContours(image,contours,i,cv::Scalar(255,0,0),5);
        }
    }

    cv::imshow("demo",image);
    cv::waitKey(0);

    return 0;
}