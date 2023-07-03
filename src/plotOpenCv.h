#ifndef PLOTCV_H
#define PLOTCV_H

#include <iostream>
#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/highgui/highgui.hpp>
#include <vector>
#include <algorithm>
#include <string>

using namespace cv;
using namespace std;

class _2Dplot{
public:
    _2Dplot(std::vector<float>*Points)
    {
        m_in_max= *max_element(Points->begin(),Points->end());
        m_in_min= *min_element(Points->begin(),Points->end());
        m_points = Points;
    }
    ~_2Dplot(){}

    int m_thickness = 1;
    float m_scale = 50;
    float m_in_max;
    float m_in_min;
    float m_out_max;
    float m_out_min=0;
    int m_offsetY=0;
    std::vector<float>*m_points;
};

class window{
public:
    window(string name,int width = 1280, int height = 720);
    ~window();

    // Method to render plot on window.
    void renderPlot(_2Dplot plot, int dt=1);

    // Showing graph with rendered plots.
    void graphShow();

private:
    std::unique_ptr<cv::Mat> m_image;
    int m_gridSize{50};
    int m_width;
    int m_heigth;
    string m_nameGraph;
};

#endif // PLOTCV_H
