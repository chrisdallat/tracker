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

        void                capture();
        // void                loop();
        void                wait() const;
        bool                valid() const;

    private:
        int                 m_camera = 0;
        bool                m_valid = true;
        cv::VideoCapture    m_capture;
        cv::Mat             m_mat_original; //Matrix Object, input from webcam
        cv::Mat             m_mat_processed;//Matrix Object, processed image 
        
        std::vector<cv::Vec3f> m_vecCircles; //3 element vector of floats, pass by ref output to HoughCircles()
        std::vector<cv::Vec3f>::iterator m_itrCircles; //iterator for vecCircles vector
        
        int                 m_video_width = 640;
        int                 m_video_height = 480;


};

#endif //WEBCAM_HPP

