#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <vector>
#include "plotOpenCv.h"

using namespace cr::utils;

int main()
{
    std::cout << "===========================================" << std::endl;
    std::cout << "plotOpenCv test"                             << std::endl;
    std::cout << "===========================================" << std::endl;

    std::vector<float> linePoints(9000);
    float degree=0;
    for(int i =0 ; i < 9000; i++ )
    {
        linePoints.at(i) = sin(degree);
        degree+=0.01;
    }

    std::vector<float> linePoints2(1000);
    degree=0;
    for(int i =0 ; i < 1000; i++ )
    {
        linePoints2.at(i) = degree*degree;
        degree+=0.5;
    }

    window myWindow("Test",1280,720);
    myWindow.renderPlot(&linePoints,1, cv::Scalar(255,0,0), 5);
    myWindow.renderPlot(&linePoints2,1, cv::Scalar(0, 255, 0),1);
    myWindow.show();
    cv::waitKey(0);

    return 0;
}
