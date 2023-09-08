#pragma once
#include <vector>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>



namespace cr
{
namespace utils
{
/**
    * @brief plot class.
*/
class Plot {
public:

    /**
    * @brief Method to get string of current library version.
    * @return String of current library version.
    */
    static std::string getVersion();

    /**
    * @brief Class constructor.
    * @param name window name.
    * @param width width of window.
    * @param height height of window.
    * @param backgroundColor color of background.
    * @param scaleLineColor color of horizontal scale line.
    */
    Plot(std::string name, int width = 1280, int height = 720, 
         cv::Scalar backgroundColor = cv::Scalar(255, 255, 255),
         cv::Scalar scaleLineColor = cv::Scalar(0, 128, 128));

    /**
    * @brief Class destructor.
    */
    ~Plot();

    /**
    * @brief Method to render plots on window.
    * @param Points  vector of points for plot.
    * @param id ploting id for a line chart, can be used to update existing plot 
             or add new one.
    * @param start beginning index for plotting in given vector.
    * @param end ending index for plotting in given vector.
    * @param color printing color of plot.
    * @param thickness line thickness for plot.
    */
    template <typename T>
    void addPlot(std::vector<T>& points, int id, int start = 0, int end = 0,
                cv::Scalar color = cv::Scalar(255, 255, 255), int thickness = 1);
    /**
    * @brief Method to render plots on window.
    * @param Points  2D vector of points for plot.
    * @param id ploting id for a line chart, can be used to update existing plot
             or add new one.
    * @param start beginning index for plotting in given vector.
    * @param end ending index for plotting in given vector.
    * @param color printing color of plot.
    * @param thickness line thickness for plot
    */
    template <typename T>
    void addPlot(std::vector<std::vector<T>>& points, int id, 
                int start = 0, int end = 0,
                cv::Scalar color = cv::Scalar(255, 255, 255), int thickness = 1);

    /**
    * @brief Method to clean window.
    */
    void clean();

    /**
    * @brief Method to show window.
    */
    void show();

private:

    /**
    * @brief plot struct.
    */
    struct Plot2D
    {
        /**
        * @brief struct constructor.
        */
        Plot2D(std::vector<double>& points, int id, 
               int start, int end, cv::Scalar color, int tickness);

        /**
        * @brief struct constructor.
        */
        Plot2D(std::vector<std::vector<double>>& points, int id, 
               int start, int end,
               cv::Scalar color, int tickness);

        /**
        * @brief Class destructor.
        */
        ~Plot2D();

        /// Id of plot.
        int m_id{0};
        /// Max value from data set.
        double m_inMax;
        /// Min value from data set.
        double m_inMin;
        /// Max value for scaling.
        double m_outMax;
        /// Min value for scaling.
        double m_outMin{0};
        /// Vertical offset.
        int m_offsetY{0};
        /// Horizontal offset.
        double m_offsetX;
        /// Color of plot.
        cv::Scalar m_color;
        /// Tickness of plot line.
        int m_tickness;
        /// Plot type(0 - one dimentional (only vertical), 1 - two dimentional).
        int m_type;
        /// Number of points on plot.
        int m_length;
        /// Dataset for one dimentional plot.
        std::vector<double> m_points1D;
        /// Dataset for two dimentional plot.
        std::vector<std::vector<double>> m_points2D;

    private:
    };

    /// Background image for plotting.
    cv::Mat* m_image;
    /// Grid sizes in pixel for plotting background 
    int m_gridSize{ 50 };
    /// Window width
    int m_width;
    /// Window heigth
    int m_height;
    /// Color of background
    cv::Scalar m_backgroundColor;
    /// Color of horizontal scale line
    cv::Scalar m_horizontalScaleLineColor;
    /// Window name
    std::string m_name;
    /// List of plots
    std::list<Plot2D> m_plots;
    /// List of ids
    std::vector<int> m_ids;

    /**
    * @brief Method to render a plot on window.
    * @param plot object to draw.
    */
    void renderPlot(Plot2D plot);
};
}
}