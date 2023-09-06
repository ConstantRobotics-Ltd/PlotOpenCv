#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>
#include <string>
#include <algorithm>



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
    *
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
    * @param Points vector of points for plot.
    * @param dt period of x axis for plotting.
    * @param color printing color of plot.
    * @param tickness line tickness for plot
    */
    void renderPlot(std::vector<float>* Points, int start = 0, int end = 0, 
                    cv::Scalar color = cv::Scalar(255, 255, 255), int tickness = 1);

    /**
    * @brief Method to render plots on window.
    * @param Points 2d vector of points for plot.
    * @param color printing color of plot.
    * @param tickness line tickness for plot
    */
    void renderPlot(std::vector<std::vector<float>> *Points, int start = 0, int end =0,
                    cv::Scalar color = cv::Scalar(255, 255, 255), int tickness = 1);

    /**
    * @brief Method to show window.
    */
    void show();

private:

    /**
    * @brief 2d plot struct.
    */
    struct _2Dplot
    {
    public:

        _2Dplot(std::vector<float>* Points, int start = 0, int end = 0)
        {
            if ((end - start) <= 0)
            {
                m_inMax = *max_element(Points->begin() , Points->end());
                m_inMin = *min_element(Points->begin(), Points->end());
            }
            else 
            {
                m_inMax = *max_element(Points->begin() + start, Points->begin() + end);
                m_inMin = *min_element(Points->begin() + start, Points->begin() + end);
            }
            m_points1d = Points;
        }

        _2Dplot(std::vector<std::vector<float>> *Points): m_inMax(std::numeric_limits<float>::lowest()),
            m_inMin(std::numeric_limits<float>::max())
        {
            // Iterate through the vector and find max and min in the second column (column index 1)
            for (const std::vector<float>& row : *Points) 
            {
                if (row.size() > 1) 
                {
                    float value = row[1]; // Access the second column (column index 1)

                    // Update maximum value using std::max
                    m_inMax = std::max(m_inMax, value);

                    // Update minimum value using std::min
                    m_inMin = std::min(m_inMin, value);
                }
            }
            m_points2d = Points;
        }

        ~_2Dplot()
        {

        }

        float m_scale{50};
        float m_inMax;
        float m_inMin;
        float m_outMax;
        float m_outMin{0};
        int m_offsetY{0};
        std::vector<float> *m_points1d;    // for constant dx
        std::vector<std::vector<float>>* m_points2d;

    private:

    };

    /// background image for plotting.
    cv::Mat* m_image;
    /// grid sizes in pixel for plotting background 
    int m_gridSize{ 50 };
    /// window width
    int m_width;
    /// window heigth
    int m_heigth;
    /// window name
    std::string m_name;
};
}
}