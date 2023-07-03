#include <iostream>
#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/highgui/highgui.hpp>
#include <vector>
#include <algorithm>
#include "plotOpenCv.h"

using namespace cv;
using namespace std;

int main()
{
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

    _2Dplot myPlot(&linePoints);
    _2Dplot myPlot2(&linePoints2);

    window myWindow("Test",1280,720);
    myWindow.renderPlot(myPlot,1,PlotColor::RED,1);
    myWindow.renderPlot(myPlot2,1,PlotColor::BLUE,5);
    myWindow.graphShow();
    waitKey(0);

    return 0;
}
