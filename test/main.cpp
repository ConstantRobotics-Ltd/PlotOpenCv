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
    for(int i =0 ; i < 5000; i++ )
    {
        linePoints.at(i) = sin(degree);
        degree+=0.01;
    }
    for (int i = 5000; i < 7000; i++)
    {
        linePoints.at(i) = (0.3f);
    }
    float temp=0;
    for(int i = 7000; i<9000; i++)
    {
        temp += 0.00015f;
        linePoints.at(i) = 0.3f - temp;
    }
    for (int i = 0; i < 9000; i++)
    {
        std::cout << "data [" << i << "]" << linePoints.at(i) << std::endl;
    }
    std::vector<float> linePoints2(1000);
    degree=0;
    for(int i =0 ; i < 1000; i++ )
    {
        linePoints2.at(i) = degree*degree;
        degree+=0.5;
    }
    plot myWindow("Test graph",1280,720, cv::Scalar(50, 50, 50));
    myWindow.renderPlot(&linePoints,0, 9000, cv::Scalar(255,0,0), 5);
    myWindow.renderPlot(&linePoints2,0,0, cv::Scalar(0, 255, 0),1);

    const int numElements = 1280;

    // Create a multidimensional vector to store the data (2D in this case)
    std::vector<std::vector<float>> data(numElements, std::vector<float>(2));

    // Generate the data for sin wave and store it in the vector
    int time = 0;
    for (int i = 0; i < numElements; ++i) 
    {
        data[i][0] = time;
        data[i][1] = sin(2.0 * 3.14 * 10 * time);
        time += 1;
    }

    myWindow.renderPlot(&data, cv::Scalar(0,0,255), 3);
    myWindow.show();
    cv::waitKey(0);
    return 0;
}
