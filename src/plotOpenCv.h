#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>
#include <string>



namespace cr
{
namespace utils
{
/**
    * @brief plot class.
*/
class plot {
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
    */
    plot(std::string name, int width = 1280, int height = 720, cv::Scalar color = cv::Scalar(255,255,255));

    /**
    * @brief Class destructor.
    */
    ~plot();

    /**
    * @brief Method to render plots on window.
    * @param Points  vector of points for plot.
    * @param id ploting id.
    * @param start beggining index for plotting
    * @param end ending index for plotting
    * @param color printing color of plot.
    * @param tickness line tickness for plot
    */
    void addPlot(std::vector<float>& Points, int id, int start = 0, int end = 0,
                cv::Scalar color = cv::Scalar(255, 255, 255), int tickness = 1);
    /**
    * @brief Method to render plots on window.
    * @param Points  2D vector of points for plot.
    * @param id ploting id.
    * @param start beggining index for plotting
    * @param end ending index for plotting
    * @param color printing color of plot.
    * @param tickness line tickness for plot
    */
    void addPlot(std::vector<std::vector<float>>& Points, int id, int start = 0, int end = 0,
                cv::Scalar color = cv::Scalar(255, 255, 255), int tickness = 1);

    /**
    * @brief Method to show window.
    */
    void show();

private:

    /**
    * @brief plot struct.
    */
    struct _2Dplot
    {
    public:
        /**
        * @brief struct constructor.
        */
        _2Dplot(std::vector<float>& Points, int id, int start, int end, cv::Scalar color, int tickness )
        {
            m_length = end - start;

            //Invalid range, use complete vector.
            if (m_length <= 0)
            {
                m_length = Points.size();
                std::copy(Points.begin(), Points.end(), std::back_inserter(m_points1d));
            }
            // Copy specified range of input vector.
            else 
            {
                // Define the range you want to copy
                std::vector<float>::iterator startindex = Points.begin() + start; // Start from index
                std::vector<float>::iterator endindex = Points.begin() + end;   // End at index

                // Copy the range from sourceVector to destinationVector
                std::copy(startindex, endindex, std::back_inserter(m_points1d));
            }

            // Max and min values are required for vertical scaling.
            m_inMax = *max_element(Points.begin() , Points.end());
            m_inMin = *min_element(Points.begin(), Points.end());

            // Update params
            m_id = id;
            m_color = color;
            m_tickness = tickness;
            m_type = 0;
        }

        /**
        * @brief struct constructor.
        */
        _2Dplot(std::vector<std::vector<float>> &Points, int id, int start , int end,
            cv::Scalar color, int tickness): m_inMax(std::numeric_limits<float>::lowest()),
            m_inMin(std::numeric_limits<float>::max()), m_offsetX(std::numeric_limits<float>::max())
        {
            m_length = end - start;

            // Invalid range, use complete vector.
            if (m_length <= 0)
            {
                m_length = Points.size();
                std::copy(Points.begin(), Points.end(), std::back_inserter(m_points2d));
            }
            // Copy specified range of input vector.
            else
            {
                // Range of copy
                std::vector<std::vector<float>>::iterator startindex = Points.begin() + start; // Start from index
                std::vector<std::vector<float>>::iterator endindex = Points.begin() + end;   // End at index

                // Copy the range from sourceVector to destinationVector
                std::copy(startindex, endindex, std::back_inserter(m_points2d));
            };

            // Iterate through the vector within the specified range
            for (int i = start; i < end && i < Points.size(); ++i) {
                const std::vector<float>& row = Points[i];

                if (row.size() > 1) {
                    float valueY = row[1]; // y component
                    float valueX = row[0]; // x component

                    // Update maximum value using std::max
                    m_inMax = std::max(m_inMax, valueY);

                    // Update minimum value using std::min
                    m_inMin = std::min(m_inMin, valueY);

                    // Find the smallest value in X direction for horizontal offset.
                    m_offsetX = std::min(m_offsetX, valueX);
                }
            }

            // Update params
            m_id = id;
            m_tickness = tickness;
            m_color = color;
            m_type = 1;
        }

        /**
        * @brief Class destructor.
        */
        ~_2Dplot(){}

        /// Id of plot.
        int m_id{0};
        /// Max value from data set.
        float m_inMax;
        /// Min value from data set.
        float m_inMin;
        /// Max value for scaling.
        float m_outMax;
        /// Min value for scaling.
        float m_outMin{0};
        /// Vertical offset.
        int m_offsetY{0};
        /// Horizontal offset.
        float m_offsetX;
        /// Color of plot.
        cv::Scalar m_color;
        /// Tickness of plot line.
        int m_tickness;
        /// Plot type (0 - one dimentional (without horizontal points), 1 - two dimentional).
        int m_type;
        /// Number of points on plot.
        int m_length;
        /// Dataset for one dimentional plot.
        std::vector<float> m_points1d;
        /// Dataset for two dimentional plot.
        std::vector<std::vector<float>> m_points2d;

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
    cv::Scalar m_color;
    /// Window name
    std::string m_name;
    /// List of plots
    std::list<_2Dplot> m_plots;
    /// List of ids
    std::vector<int> m_ids;

    /**
    * @brief Method to render a plot on window.
    * @param plot object to draw.
    */
    void renderPlot(_2Dplot plot);

};
}
}