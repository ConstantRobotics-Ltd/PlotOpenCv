#pragma once
#include <vector>
#include <string>



namespace cr
{
namespace utils
{

/// Plot implementation class.
class PlotImpl;

/**
 * @brief Plot color.
*/
class PlotColor
{
public:
    /// Class constructor
    PlotColor(int b, int g, int r) : b(b), g(g), r(r) {}
    /// Blue color 0-255.  
    int b{0};
    /// Green color 0-255.
    int g{0};
    /// Red color 0-255.
    int r{0};
};


/**
 * @brief Plot class.
 */
class Plot
{
public:

    /**
    * @brief Get string of current library version.
    * @return String of current library version: "Major.Minor.Patch".
    */
    static std::string getVersion();

    /**
    * @brief Class constructor.
    * @param name Window name.
    * @param width Width of window.
    * @param height Height of window.
    * @param backgroundColor Background color.
    * @param scaleLineColor Horizontal scale line color.
    */
    Plot(std::string name, int width = 1280, int height = 720, 
         PlotColor backgroundColor = PlotColor(255, 255, 255),
         PlotColor scaleLineColor = PlotColor(0, 128, 128));

    /**
    * @brief Class destructor.
    */
    ~Plot();

    /**
    * @brief Render plots on window.
    * @param Points Vector of points for plot.
    * @param id Plot id for a line chart, can be used to update existing plot or add new one.
    * @param start Start index for plotting in given vector.
    * @param end End index for plotting in given vector.
    * @param color printing color of plot.
    * @param thickness line thickness for plot.
    */
    template <typename T>
    void addPlot(std::vector<T>& points, int id, int start = 0, int end = 0,
                 PlotColor color = PlotColor(255, 255, 255), int thickness = 1);
    /**
    * @brief Method to render plots on window.
    * @param Points  2D vector of points for plot.
    * @param id Plot id for a line chart, can be used to update existing plot
             or add new one.
    * @param start Start index for plotting in given vector.
    * @param end End index for plotting in given vector.
    * @param color Printing color of plot.
    * @param thickness line thickness for plot
    */
    template <typename T>
    void addPlot(std::vector<std::vector<T>>& points, int id, 
                 int start = 0, int end = 0,
                 PlotColor color = PlotColor(255, 255, 255), int thickness = 1);

    /**
    * @brief Method to clean window.
    */
    void clean();

    /**
    * @brief Method to show window.
    */
    void show();

private:

    /// Pointer to plot implementation class.
    PlotImpl* m_impl;
};
}
}