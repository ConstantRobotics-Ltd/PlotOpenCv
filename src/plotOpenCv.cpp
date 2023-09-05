#include "plotOpenCv.h"
#include "plotOpenCvVersion.h"

// Linear mapping method.
float map(float x, float in_min, float in_max, float out_min, float out_max) 
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


// This method will be used for some future features like zoom in, move along x,y etc.
void CallBackFuncMouse(int event, int x, int y, int flags, void* userdata)
{
    // window which event is captured.
    window * current_window = static_cast<window *>(userdata);

    if  ( event == cv::EVENT_LBUTTONDOWN )
    {
       // cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
    }
    else if  ( event == cv::EVENT_RBUTTONDOWN )
    {
        //cout << "Right button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
    }
    else if  ( event == cv::EVENT_MBUTTONDOWN )
    {
       // cout << "Middle button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
    }
    else if ( event == cv::EVENT_MOUSEMOVE )
    {
       // cout << "Mouse move over the window - position (" << x << ", " << y << ")" << endl;
    }
}

std::string window::getVersion()
{
    return PLOT_OPENCV_VERSION;
}

window::window(std::string name, int width, int height)
{
    // Create a window.
    cv::namedWindow(name,0);
    
    // remember window name for showing
    m_name=name;

    // background image (white) for window
    m_image = new cv::Mat(height, width, CV_8UC3, cv::Scalar(255, 255, 255));

    // remember window size
    m_width = width;
    m_heigth= height;

    //set the callback function for event
    cv::setMouseCallback(name, CallBackFuncMouse, this);

    //draw horizontal scale line
    cv::line(*m_image, cv::Point(0, height/2), cv::Point(width, height/2), cv::Scalar(0, 128, 128),5);


    // draw grid lines
    for (int i = 0; i<height; i += 50)
       cv::line(*m_image, cv::Point(0, i), cv::Point(width, i), cv::Scalar(0, 0, 0));

    for (int i = 0; i<width; i += 50)
       cv::line(*m_image, cv::Point(i, 0), cv::Point(i, height), cv::Scalar(0, 0, 0));
}

window::~window()
{
    delete m_image;
}

void window::renderPlot(std::vector<float>* Points, int dt, plotColor color, int tickness)
{
    // Temp plot object to render graph on image.
    _2Dplot plot(Points);

    // Update current plot params with respect to current window
    plot.m_out_max = m_heigth*plot.m_scale/100;

    // offset value is different for dataset which has negative values
    if(plot.m_in_min<0)
    {
        plot.m_offsetY = m_heigth/2 - plot.m_out_max/2;
    }
    else 
    {
        plot.m_offsetY = 0;
    }

    // Temporary points to draw a line
    cv::Point currentPoint;
    cv::Point previousPoint;
    cv::Scalar lineColor;

    switch (color)
    {
    case plotColor::BLUE:
    {
        lineColor.val[0] = 255;
        lineColor.val[1] = 0;
        lineColor.val[2] = 0;
        break;
    }
    case plotColor::GREEN:
    {
        lineColor.val[0] = 0;
        lineColor.val[1] = 255;
        lineColor.val[2] = 0;
        break;
    }
    case plotColor::RED:
    {
        lineColor.val[0] = 0;
        lineColor.val[1] = 0;
        lineColor.val[2] = 255;
        break;
    }
    }

    // Time period in x axis
    int t = 0;

    // Lines between points
    for(int i = 1; i<plot.m_points->size() ; ++i)
    {
        // line between two points
        previousPoint.x=t;
        previousPoint.y = (::map(plot.m_points->at(i - 1), plot.m_in_min, plot.m_in_max, plot.m_out_max, plot.m_out_min) + plot.m_offsetY);
        t+=dt;
        currentPoint.x=t;
        currentPoint.y=(::map(plot.m_points->at(i),plot.m_in_min,plot.m_in_max,plot.m_out_max,plot.m_out_min) + plot.m_offsetY );

        cv::line(*m_image,previousPoint ,currentPoint,lineColor,tickness, cv::LINE_8);
    }
}

void window::show()
{
    cv::imshow(m_name, *m_image);
}


