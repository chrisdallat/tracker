#include "webcam.hpp"

#include <iostream>

Webcam::Webcam() 
{
    if (m_capture.open(m_camera) == false) 
    {
    std::cout << "Failed to open camera" << std::endl;
    m_valid = false;
    }

    m_capture.set(cv::CAP_PROP_FRAME_WIDTH, m_video_width);
    m_capture.set(cv::CAP_PROP_FRAME_HEIGHT, m_video_height);
    m_mat_original = cv::Mat::zeros(m_video_height, m_video_width, CV_8UC3);
}

Webcam::~Webcam() 
{
  m_capture.release();
  cv::destroyAllWindows();
}

void Webcam::capture() 
{
    while(m_valid)
    {
        if(m_capture.read(m_mat_original) == false)
        {
            std::cout << "error: frame not read from webcam" << std::endl;
            m_valid = false;
        }
        cv::flip(matOriginal, matOriginal, 1); //1 flips around y-axis
    }
}

void Webcam::wait() const { cv::waitKey(25); }

bool Webcam::valid() const { return m_valid; }

// void Webcam::loop() {

