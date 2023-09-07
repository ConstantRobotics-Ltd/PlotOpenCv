#include "plotOpenCv.h"
#include "plotOpenCvVersion.h"



using namespace cr::utils;



// Linear interpolation method.
float map(float x, float in_min, float in_max, float out_min, float out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}



std::string plot::getVersion()
{
    return PLOT_OPENCV_VERSION;
}



plot::plot(std::string name, int width, int height, cv::Scalar color)
{
    // Create a window.
    cv::namedWindow(name,0);
    
    // background image (white) for window
    m_image = new cv::Mat(height, width, CV_8UC3, color);

    // Remember window params
    m_width = width;
    m_height= height;
    m_color = color;
    m_name = name;

    //draw horizontal scale line
    cv::line(*m_image, cv::Point(0, height/2), cv::Point(width, height/2), cv::Scalar(0, 128, 128),5);

    // draw grid lines
    for (int i = 0; i<height; i += 50)
       cv::line(*m_image, cv::Point(0, i), cv::Point(width, i), cv::Scalar(0, 0, 0));

    for (int i = 0; i<width; i += 50)
       cv::line(*m_image, cv::Point(i, 0), cv::Point(i, height), cv::Scalar(0, 0, 0));
}



plot::~plot()
{
    delete m_image;
}



void plot::renderPlot(_2Dplot plot)
{
    // Ratio/offset for horizontal axis
    float dt = 0.0f;

    // fit signal into window.
    dt = (float)m_width / (float)plot.m_length;

    // Temporary points to draw a line
    cv::Point currentPoint;
    cv::Point previousPoint;

    // Update plot params with respect window
    plot.m_outMax = m_height / 2;

    // offset value for dataset that has negative values
    if (plot.m_inMin < 0)
    {
        plot.m_offsetY = plot.m_outMax - (plot.m_outMax / 2);
    }

    // 1d vector drawing
    if (plot.m_type == 0) 
    {
        // Points on horizontal axis.
        float t = 0;
        // Lines between points
        for (int i = 1; i < plot.m_length; ++i)
        {
            // line between two points
            previousPoint.x = t;
            previousPoint.y = (::map(plot.m_points1d.at(i - 1), plot.m_inMin, plot.m_inMax, plot.m_outMax, plot.m_outMin) + plot.m_offsetY);
            t += dt;
            currentPoint.x = t;
            currentPoint.y = (::map(plot.m_points1d.at(i), plot.m_inMin, plot.m_inMax, plot.m_outMax, plot.m_outMin) + plot.m_offsetY);

            cv::line(*m_image, previousPoint, currentPoint, plot.m_color, plot.m_tickness, cv::LINE_8);
        }
    }
    // 2d vector drawing
    else 
    {
        // Lines between points
        for (int i = 1; i < plot.m_points2d.size(); ++i)
        {
            // line between two points
            previousPoint.x = ((plot.m_points2d)[i - 1][0] - plot.m_offsetX) * dt;
            previousPoint.y = (::map((plot.m_points2d)[i - 1][1], plot.m_inMin, plot.m_inMax, plot.m_outMax, plot.m_outMin) + plot.m_offsetY);
            currentPoint.x = ((plot.m_points2d)[i][0] - plot.m_offsetX) * dt;
            currentPoint.y = (::map((plot.m_points2d)[i][1], plot.m_inMin, plot.m_inMax, plot.m_outMax, plot.m_outMin) + plot.m_offsetY);
            cv::line(*m_image, previousPoint, currentPoint, plot.m_color, plot.m_tickness, cv::LINE_8);
        }
    }
}



void plot::addPlot(std::vector<float>& Points, int id, int start, int end,
    cv::Scalar color, int tickness) 
{
    // Check if id is already contained.
    for (const int& i : m_ids)
    {
        if (i == id)
        {
            // Remove plot from list.
            std::list<_2Dplot>::iterator it = m_plots.begin();
            std::advance(it, id);
            m_plots.erase(it);

            // Remove id from list.
            auto removeIndex = std::remove(m_ids.begin(), m_ids.end(), id);
            m_ids.erase(removeIndex, m_ids.end());
        }
    }

    m_ids.push_back(id);

    // Add ploting object to list.
    m_plots.emplace_back (_2Dplot(Points, id, start, end, color, tickness));

}



void plot::addPlot(std::vector<std::vector<float>>& Points, int id, int start, int end,
    cv::Scalar color, int tickness)
{
    // Check if id is already contained.
    for (const int& i : m_ids)
    {
        if (i == id)
        {
            // Remove plot from list
            std::list<_2Dplot>::iterator it = m_plots.begin();
            std::advance(it, id);
            m_plots.erase(it);

            // Remove id from list
            auto removeIndex = std::remove(m_ids.begin(), m_ids.end(), id);
            m_ids.erase(removeIndex, m_ids.end());
        }
    }

    m_ids.push_back(id);

    // Add ploting object to list
    m_plots.emplace_back(_2Dplot(Points, id, start, end, color, tickness));

}

void plot::clean() 
{
    // Clean window
    m_image->setTo(m_color);

    //draw horizontal scale line
    cv::line(*m_image, cv::Point(0, m_height / 2), cv::Point(m_width, m_height / 2), cv::Scalar(0, 128, 128), 5);

    // draw grid lines
    for (int i = 0; i < m_height; i += 50)
        cv::line(*m_image, cv::Point(0, i), cv::Point(m_width, i), cv::Scalar(0, 0, 0));

    for (int i = 0; i < m_width; i += 50)
        cv::line(*m_image, cv::Point(i, 0), cv::Point(i, m_height), cv::Scalar(0, 0, 0));

    m_plots.clear();
    m_ids.clear();
}


void plot::show()
{
    // Clean window
    m_image->setTo(m_color);

    //draw horizontal scale line
    cv::line(*m_image, cv::Point(0, m_height / 2), cv::Point(m_width, m_height / 2), cv::Scalar(0, 128, 128), 5);

    // draw grid lines
    for (int i = 0; i < m_height; i += 50)
        cv::line(*m_image, cv::Point(0, i), cv::Point(m_width, i), cv::Scalar(0, 0, 0));

    for (int i = 0; i < m_width; i += 50)
        cv::line(*m_image, cv::Point(i, 0), cv::Point(i, m_height), cv::Scalar(0, 0, 0));

    // Draw plot objects on window
    for (const _2Dplot& plot : m_plots)
    {
        renderPlot(plot);
    }

    cv::imshow(m_name, *m_image);
}