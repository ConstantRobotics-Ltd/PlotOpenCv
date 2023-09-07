#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <vector>
#include "plotOpenCv.h"

using namespace cr::utils;

int main()
{
    std::cout << "==========================================="   << std::endl;
    std::cout << "plotOpenCv v" << plot::getVersion() << " test" << std::endl;
    std::cout << "==========================================="   << std::endl;

    // Create plotting window.
    plot graph("Test graph", 1280, 720, cv::Scalar(50, 50, 50));

    // Prepare 1d vector for plotting.
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

    // Prepare 1d vector for plotting.
    std::vector<float> linePoints2(1000);
    degree=0;
    for(int i =0 ; i < 1000; i++ )
    {
        linePoints2.at(i) = degree*degree;
        degree+=0.5;
    }

    // Put charts on graph.
    graph.addPlot(linePoints,0, 0, 0, cv::Scalar(255,0,0), 5);
    graph.addPlot(linePoints2,2, 0, 0, cv::Scalar(0, 255, 0), 1);

    // Prepare 2d vector for plotting.
    std::vector<std::vector<float>> linePoints3(9000, std::vector<float>(2));

    // Generate the data for sin wave and store it in the vector.
    int time = 0;
    for (int i = 0; i < 9000; ++i)
    {
        linePoints3[i][0] = time;
        linePoints3[i][1] = sin(2.0 * 3.14 * 10 * time);
        time += 1;
    }

    // Put chart on graph.
    graph.addPlot(linePoints3, 3, 0, 9000, cv::Scalar(0,0,255), 3);

    // Show graph and wait.
    graph.show();
    cv::waitKey(0);
    return 0;
}
