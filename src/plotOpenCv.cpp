#include "plotOpenCv.h"


float mapp(float x, float in_min, float in_max, float out_min, float out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


// This method will be used for some features like zoom in, move along x/y etc.
void CallBackFuncMouse(int event, int x, int y, int flags, void* userdata){

    // window which event is captured.
    window * current_window = static_cast<window *>(userdata);

    if  ( event == EVENT_LBUTTONDOWN )
    {
       // cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
    }
    else if  ( event == EVENT_RBUTTONDOWN )
    {
        //cout << "Right button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
    }
    else if  ( event == EVENT_MBUTTONDOWN )
    {
       // cout << "Middle button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
    }
    else if ( event == EVENT_MOUSEMOVE )
    {
       // cout << "Mouse move over the window - position (" << x << ", " << y << ")" << endl;
    }
}

window::window(string name, int width, int height){
    namedWindow(name,0);
    m_nameGraph=name;
    m_image = std::make_unique<cv::Mat>(height, width, CV_8UC3, cv::Scalar(255, 255, 255));
    m_width = width;
    m_heigth= height;
    //set the callback function for any mouse event
    setMouseCallback(name, CallBackFuncMouse, this);

    for (int i = 0; i<height; i += 50)
       cv::line(*m_image, Point(0, i), Point(width, i), cv::Scalar(0, 0, 0));

    for (int i = 0; i<width; i += 50)
       cv::line(*m_image, Point(i, 0), Point(i, height), cv::Scalar(0, 0, 0));
}

window::~window(){
    // delete m_image;
}

void window::renderPlot(_2Dplot plot, int dt, PlotColor color, int tickness){

    plot.m_out_max = m_heigth*plot.m_scale/100;
    // offset value is different for dataset which has negative values
    if(plot.m_in_min<0)
    {
        plot.m_offsetY = m_heigth/2 - plot.m_out_max/2;
    }
    else
        plot.m_offsetY=0;

    Point pCurrent;
    Point pPrev;
    Scalar line_color;

    if(color == PlotColor::BLUE)
    {
        line_color.val[0] = 255;
        line_color.val[1] = 0;
        line_color.val[2] = 0;
    }
    else if(color == PlotColor::GREEN)
    {
        line_color.val[0] = 0;
        line_color.val[1] = 255;
        line_color.val[2] = 0;
    }
    else if(color == PlotColor::RED)
    {
        line_color.val[0] = 0;
        line_color.val[1] = 0;
        line_color.val[2] = 255;
    }

    int t = 0;

    // Line drawn using 8 connected
    for(int i = 1; i<plot.m_points->size() ; ++i)
    {
        pPrev.x=t;
        pPrev.y = (mapp(plot.m_points->at(i-1),plot.m_in_min,plot.m_in_max,plot.m_out_max,plot.m_out_min)+plot.m_offsetY );
        t+=dt;
        pCurrent.x=t;
        pCurrent.y=(mapp(plot.m_points->at(i),plot.m_in_min,plot.m_in_max,plot.m_out_max,plot.m_out_min)+plot.m_offsetY );

        line(*m_image,pPrev ,pCurrent,line_color,tickness, LINE_8);
    }
}

void window::graphShow(){
    // Show our image inside window
    imshow(m_nameGraph, *m_image);
}


