#include "PlotOpenCv.h"
#include "PlotOpenCvVersion.h"
#include "Impl/PlotOpenCvImpl.h"



std::string cr::utils::Plot::getVersion()
{
    return PLOT_OPENCV_VERSION;
}



cr::utils::Plot::Plot(std::string name, int width, int height, 
            cr::utils::PlotColor backgroundColor, cr::utils::PlotColor scaleLineColor)
{

    m_impl = new PlotImpl(name, width, height,
                          cv::Scalar(backgroundColor.b, backgroundColor.g, backgroundColor.r),
                          cv::Scalar(scaleLineColor.b, scaleLineColor.g, scaleLineColor.r));
}



cr::utils::Plot::~Plot()
{
    delete m_impl;
}



template <typename T>
void cr::utils::Plot::addPlot(std::vector<T>& points, int id, int start, int end,
     cr::utils::PlotColor color, int thickness) 
{
    m_impl->addPlot(points, id, start, end, cv::Scalar(color.b, color.g, color.r), thickness);
}
 


 template <typename T>
 void cr::utils::Plot::addPlot(std::vector<std::vector<T>>& points, int id, int start, int end,
    cr::utils::PlotColor color, int thickness)
{
    m_impl->addPlot(points, id, start, end, cv::Scalar(color.b, color.g, color.r), thickness);
}



void cr::utils::Plot::clean()
{
    m_impl->clean();
}



void cr::utils::Plot::show()
{
    m_impl->show();
}


template void cr::utils::Plot::addPlot(std::vector<float>& Points, int id,
                            int start, int end, cr::utils::PlotColor color, int thickness);
template void cr::utils::Plot::addPlot(std::vector<double>& Points, int id,
                            int start, int end, cr::utils::PlotColor color, int thickness);
template void cr::utils::Plot::addPlot(std::vector<int>& Points, int id,
                            int start, int end, cr::utils::PlotColor color, int thickness);
template void cr::utils::Plot::addPlot(std::vector<short int>& Points, int id,
                            int start, int end, cr::utils::PlotColor color, int thickness);
template void cr::utils::Plot::addPlot(std::vector<unsigned short int>& Points, int id,
                            int start, int end, cr::utils::PlotColor color, int thickness);
template void cr::utils::Plot::addPlot(std::vector<unsigned int>& Points, int id,
                            int start, int end, cr::utils::PlotColor color, int thickness);
template void cr::utils::Plot::addPlot(std::vector<char>& Points, int id,
                            int start, int end, cr::utils::PlotColor color, int thickness);
template void cr::utils::Plot::addPlot(std::vector<unsigned char>& Points, int id,
                            int start, int end, cr::utils::PlotColor color, int thickness);


template void cr::utils::Plot::addPlot(std::vector<std::vector<float>>& Points, int id,
                            int start, int end, cr::utils::PlotColor color, int thickness);
template void cr::utils::Plot::addPlot(std::vector< std::vector<double>>& Points, int id,
                            int start, int end, cr::utils::PlotColor color, int thickness);
template void cr::utils::Plot::addPlot(std::vector< std::vector<int>>& Points, int id,
                            int start, int end, cr::utils::PlotColor color, int thickness);
template void cr::utils::Plot::addPlot(std::vector< std::vector<short int>>& Points,int id,
                            int start, int end, cr::utils::PlotColor color, int thickness);
template void cr::utils::Plot::addPlot(std::vector< std::vector<unsigned short int>>& Points,
                            int id, int start, int end,
                            cr::utils::PlotColor color, int thickness);
template void cr::utils::Plot::addPlot(std::vector< std::vector<unsigned int>>& Points,
                            int id, int start, int end,
                            cr::utils::PlotColor color, int thickness);
template void cr::utils::Plot::addPlot(std::vector< std::vector<char>>& Points, int id,
                            int start, int end,
                            cr::utils::PlotColor color, int thickness);
template void cr::utils::Plot::addPlot(std::vector< std::vector<unsigned char>>& Points,
                            int id, int start, int end,
                            cr::utils::PlotColor color, int thickness);