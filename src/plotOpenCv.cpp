#include "plotOpenCv.h"
#include "plotOpenCvVersion.h"




// Linear interpolation method.
template <typename T>
T map(T x, T in_min, T in_max, T out_min, T out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

std::string cr::utils::Plot::getVersion()
{
    return PLOT_OPENCV_VERSION;
}

cr::utils::Plot::Plot(std::string name, int width, int height, 
            cv::Scalar backgroundColor, cv::Scalar scaleLineColor)
{
    // Create a window.
    cv::namedWindow(name, 0);

    // Background image (white) for window.
    m_image = new cv::Mat(height, width, CV_8UC3, backgroundColor);

    // Remember window params.
    m_width = width;
    m_height = height;
    m_backgroundColor = backgroundColor;
    m_horizontalScaleLineColor = scaleLineColor;
    m_name = name;

    //Draw horizontal scale line.
    cv::line(*m_image, cv::Point(0, height / 2),
        cv::Point(width, height / 2), m_horizontalScaleLineColor, 5);

    // Draw grid lines.
    for (int i = 0; i < height; i += 50)
    {
        cv::line(*m_image, cv::Point(0, i),
            cv::Point(width, i), cv::Scalar(0, 0, 0));
    }
    for (int i = 0; i < width; i += 50) 
    {
        cv::line(*m_image, cv::Point(i, 0), 
                 cv::Point(i, height), cv::Scalar(0, 0, 0));
    }
}

cr::utils::Plot::~Plot()
{
    delete m_image;
}

void cr::utils::Plot::renderPlot(Plot2D plot)
{
    // Ratio/offset for horizontal axis.
    float dt = 0.0f;

    // Fit signal into window.
    dt = (float)m_width / (float)plot.m_length;

    // Temporary points to draw a line.
    cv::Point currentPoint;
    cv::Point previousPoint;

    // Update plot params with respect window.
    plot.m_outMax = m_height / 2;

    // Offset value for dataset that has negative values.
    if (plot.m_inMin < 0)
    {
        plot.m_offsetY = plot.m_outMax - (plot.m_outMax / 2);
    }

    // 1D vector drawing.
    if (plot.m_type == 0) 
    {
        // Points on horizontal axis.
        float t = 0;
        // Lines between points.
        for (int i = 1; i < plot.m_length; ++i)
        {
            // line between two points
            previousPoint.x = t;
            previousPoint.y = (::map(plot.m_points1D.at(i - 1), plot.m_inMin, 
                plot.m_inMax, plot.m_outMax, plot.m_outMin) + plot.m_offsetY);
            t += dt;
            currentPoint.x = t;
            currentPoint.y = (::map(plot.m_points1D.at(i), plot.m_inMin, 
                plot.m_inMax, plot.m_outMax, plot.m_outMin) + plot.m_offsetY);

            cv::line(*m_image, previousPoint, currentPoint, plot.m_color,
                    plot.m_tickness, cv::LINE_8);
        }
    }
    // 2D vector drawing.
    else 
    {
        // Lines between points
        for (int i = 1; i < plot.m_points2D.size(); ++i)
        {
            // line between two points
            previousPoint.x = ((plot.m_points2D)[i - 1][0] - plot.m_offsetX) * dt;
            previousPoint.y = (::map((plot.m_points2D)[i - 1][1], plot.m_inMin, plot.m_inMax, plot.m_outMax, plot.m_outMin) + plot.m_offsetY);
            currentPoint.x = ((plot.m_points2D)[i][0] - plot.m_offsetX) * dt;
            currentPoint.y = (::map((plot.m_points2D)[i][1], plot.m_inMin, plot.m_inMax, plot.m_outMax, plot.m_outMin) + plot.m_offsetY);
            cv::line(*m_image, previousPoint, currentPoint, plot.m_color, plot.m_tickness, cv::LINE_8);
        }
    }
}

 template <typename T>
 void cr::utils::Plot::addPlot(std::vector<T>& points, int id, int start, int end,
     cv::Scalar color, int thickness) 
 {
     // Check if id is already contained.
     for (const auto& pair : m_plots)
     {
         const int& i = pair.first;
         if (i == id)
         {
             // Remove plot from list.
             auto it = m_plots.find(i);
             if (it != m_plots.end()) 
                 m_plots.erase(it);
         }
     }

     // Add ploting object to list.
     std::vector<double> doubles;
     for (int i =0;i<points.size(); i++)
     {
         doubles.push_back(static_cast<double>(points[i]));
     }

     m_plots.insert(std::make_pair(id, Plot2D(doubles, id, start, end, color, thickness)));
 
 }
 
 template <typename T>
 void cr::utils::Plot::addPlot(std::vector<std::vector<T>>& points, int id, int start, int end,
    cv::Scalar color, int thickness)
{
    // Check if id is already contained.
    for (const auto& pair : m_plots)
    {
        const int& i = pair.first;
        if (i == id)
        {
            // Remove plot from list.
            auto it = m_plots.find(i);
            if (it != m_plots.end())
                m_plots.erase(it);
        }
    }

    // Convert points vector to double.
    std::vector<std::vector<double>> doubles;
    std::vector<double> temp(2);
    for (int i = 0; i < points.size(); i++)
    {
        temp[0] = static_cast<double>(points[i][0]);
        temp[1] = static_cast<double>(points[i][1]);

        doubles.push_back(temp);
    }

    // Add ploting object to list.
    m_plots.insert(std::make_pair(id, Plot2D(doubles, id, start, end, color, thickness)));

}

void cr::utils::Plot::clean()
{
    // Clean window.
    m_image->setTo(m_backgroundColor);

    // Draw horizontal scale line.
    cv::line(*m_image, cv::Point(0, m_height / 2),
            cv::Point(m_width, m_height / 2), m_horizontalScaleLineColor, 3);

    // Draw grid lines.
    for (int i = 0; i < m_height; i += 50)
        cv::line(*m_image, cv::Point(0, i), 
                cv::Point(m_width, i), cv::Scalar(0, 0, 0));

    for (int i = 0; i < m_width; i += 50)
        cv::line(*m_image, cv::Point(i, 0), 
                cv::Point(i, m_height), cv::Scalar(0, 0, 0));

    // Clear all instances from container.
    m_plots.clear();
}

void cr::utils::Plot::show()
{
    // Clean window.
    m_image->setTo(m_backgroundColor);

    // Draw horizontal scale line.
    cv::line(*m_image, cv::Point(0, m_height / 2), 
            cv::Point(m_width, m_height / 2), m_horizontalScaleLineColor, 3);

    // Draw grid lines.
    for (int i = 0; i < m_height; i += 50)
    {
        cv::line(*m_image, cv::Point(0, i), 
                 cv::Point(m_width, i), cv::Scalar(0, 0, 0));
    }
    for (int i = 0; i < m_width; i += 50) 
    {
        cv::line(*m_image, cv::Point(i, 0), 
                 cv::Point(i, m_height), cv::Scalar(0, 0, 0));
    }

    // Iterate over the values (Plot2D instances) in the map
    for (const auto& pair : m_plots) 
    {
        const Plot2D& plot = pair.second;
        renderPlot(plot);
    }

    cv::imshow(m_name, *m_image);
}

cr::utils::Plot::Plot2D::Plot2D(std::vector<double>& points, int id,
                     int start, int end, cv::Scalar color, int tickness)
{
    m_length = end - start;

    // Invalid range, use complete vector.
    if (m_length <= 0)
    {
        m_length = points.size();
        std::copy(points.begin(), points.end(), std::back_inserter(m_points1D));
    }
    // Copy specified range of input vector.
    else
    {
        // Define the range you want to copy.
        std::vector<double>::iterator startindex = points.begin() + start;
        std::vector<double>::iterator endindex = points.begin() + end;

        // Copy the range from sourceVector to destinationVector.
        std::copy(startindex, endindex, std::back_inserter(m_points1D));
    }

    // Max and min values are required for vertical scaling.
    m_inMax = *max_element(points.begin(), points.end());
    m_inMin = *min_element(points.begin(), points.end());

    // Update params.
    m_id = id;
    m_color = color;
    m_tickness = tickness;
    m_type = 0;
}

cr::utils::Plot::Plot2D::Plot2D(std::vector<std::vector<double>>& points, int id,
                     int start, int end, cv::Scalar color, int tickness)
{
    m_inMax = std::numeric_limits<double>::lowest();
    m_inMin = std::numeric_limits<double>::max();
    m_offsetX = std::numeric_limits<double>::max();
    m_length = end - start;

    // Invalid range, use complete vector.
    if (m_length <= 0)
    {
        m_length = points.size();
        std::copy(points.begin(), points.end(), std::back_inserter(m_points2D));
    }
    // Copy specified range of input vector.
    else
    {
        // Range of copy.
        std::vector<std::vector<double>>::iterator startindex = points.begin() + start;
        std::vector<std::vector<double>>::iterator endindex = points.begin() + end;

        // Copy the range from sourceVector to destinationVector.
        std::copy(startindex, endindex, std::back_inserter(m_points2D));
    };

    // Iterate through the vector within the specified range.
    for (int i = start; i < end && i < points.size(); ++i) {
        const std::vector<double>& row = points[i];

        if (row.size() > 1) {
            double valueY = row[1]; // y component
            double valueX = row[0]; // x component

            // Update maximum value using std::max
            m_inMax = std::max(m_inMax, valueY);

            // Update minimum value using std::min
            m_inMin = std::min(m_inMin, valueY);

            // Find the smallest value in X direction for horizontal offset.
            m_offsetX = std::min(m_offsetX, valueX);
        }
    }

    // Update params.
    m_id = id;
    m_tickness = tickness;
    m_color = color;
    m_type = 1;
}

cr::utils::Plot::Plot2D::~Plot2D() {}

template void cr::utils::Plot::addPlot(std::vector<float>& Points, int id,
                            int start, int end, cv::Scalar color, int tickness);
template void cr::utils::Plot::addPlot(std::vector<double>& Points, int id,
                            int start, int end, cv::Scalar color, int tickness);
template void cr::utils::Plot::addPlot(std::vector<int>& Points, int id,
                            int start, int end, cv::Scalar color, int tickness);
template void cr::utils::Plot::addPlot(std::vector<short int>& Points, int id,
                            int start, int end, cv::Scalar color, int tickness);
template void cr::utils::Plot::addPlot(std::vector<unsigned short int>& Points, int id,
                            int start, int end, cv::Scalar color, int tickness);
template void cr::utils::Plot::addPlot(std::vector<unsigned int>& Points, int id,
                            int start, int end, cv::Scalar color, int tickness);
template void cr::utils::Plot::addPlot(std::vector<char>& Points, int id,
                            int start, int end, cv::Scalar color, int tickness);
template void cr::utils::Plot::addPlot(std::vector<unsigned char>& Points, int id,
                            int start, int end, cv::Scalar color, int tickness);


template void cr::utils::Plot::addPlot(std::vector<std::vector<float>>& Points, int id,
                            int start, int end, cv::Scalar color, int tickness);
template void cr::utils::Plot::addPlot(std::vector< std::vector<double>>& Points, int id,
                            int start, int end, cv::Scalar color, int tickness);
template void cr::utils::Plot::addPlot(std::vector< std::vector<int>>& Points, int id,
                            int start, int end, cv::Scalar color, int tickness);
template void cr::utils::Plot::addPlot(std::vector< std::vector<short int>>& Points,int id,
                            int start, int end, cv::Scalar color, int tickness);
template void cr::utils::Plot::addPlot(std::vector< std::vector<unsigned short int>>& Points,
                            int id, int start, int end,
                            cv::Scalar color, int tickness);
template void cr::utils::Plot::addPlot(std::vector< std::vector<unsigned int>>& Points,
                            int id, int start, int end,
                            cv::Scalar color, int tickness);
template void cr::utils::Plot::addPlot(std::vector< std::vector<char>>& Points, int id,
                            int start, int end,
                            cv::Scalar color, int tickness);
template void cr::utils::Plot::addPlot(std::vector< std::vector<unsigned char>>& Points,
                            int id, int start, int end,
                            cv::Scalar color, int tickness);