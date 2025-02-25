#include<iostream>
#include<opencv2/opencv.hpp>

int main(int argc, char** argv) {
    cv::Mat image=imread("enoz_noise.png",cv::IMREAD_COLOR);
    cv::imshow("image",image);
    cv::Mat gau,bila;
    //高斯
    cv::GaussianBlur(image,gau,cv::Size(5,5),0);
    //双边
    cv::bilateralFilter(gau,bila,9,50,25/2);
    cv::imshow("Bila",bila);
    cv::waitKey(0); 
    return 0;
}