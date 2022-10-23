#ifndef WEBCAM_HPP
#define WEBCAM_HPP

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

class Webcam
{
    public:
        Webcam();
        ~Webcam();



    private:
        int                m_camera;
        cv::Mat            m_mat;
};

#endif //WEBCAM_HPP

