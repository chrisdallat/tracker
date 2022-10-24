#ifndef WEBCAM_HPP
#define WEBCAM_HPP

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/tracking.hpp>

#include <iostream>

class Webcam
{
    public:
        Webcam();
        ~Webcam();

        //testing: remove later
        void                set_show_bools(bool, bool); //for ease of testing

        //main methods
        void                capture();
        void                set_tracking_box();
        void                create_windows();
        void                show_video_outputs();
        void                main_loop();
        void                wait(int, int);
        bool                valid();

        //not used: for colour range tracking
        void                process_object_range();
        void                output_tracking_circle();

    private:
        int                 m_camera = 0;
        bool                m_valid = true;
        bool                m_spacebar_pressed = false;
        cv::VideoCapture    m_capture;
        cv::Mat             m_mat_original; //Matrix Object, input from webcam
        cv::Mat             m_mat_processed;//Matrix Object, processed image 
        bool                m_original_show; 
        bool                m_processed_show;

        //manual selection tracker
        cv::Ptr<cv::Tracker> m_tracker;
        cv::Rect m_tracking_box;
        
        //original colour range circle tracker
        std::vector<cv::Vec3f> m_vec_circles; //3 element vector of floats, pass by ref output to HoughCircles()
        std::vector<cv::Vec3f>::iterator m_itr_circles; //iterator for vecCircles vector
        
        //will move to a video settings class
        int                 m_video_width = 640;
        int                 m_video_height = 480;


};

#endif

