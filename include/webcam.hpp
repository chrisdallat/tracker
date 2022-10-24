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

        //remove later
        void                set_show_bools(bool, bool); //for ease of testing

        //main methods
        void                capture();
        void                process_object_range();
        void                output_tracking_circle();
        void                create_windows();
        void                show_video_outputs();
        void                main_loop();
        void                wait(int);
        bool                valid();

    private:
        int                 m_camera = 0;
        bool                m_valid = true;
        cv::VideoCapture    m_capture;
        cv::Mat             m_mat_original; //Matrix Object, input from webcam
        cv::Mat             m_mat_processed;//Matrix Object, processed image 
        bool                m_original_show; 
        bool                m_processed_show;
        
        std::vector<cv::Vec3f> m_vec_circles; //3 element vector of floats, pass by ref output to HoughCircles()
        std::vector<cv::Vec3f>::iterator m_itr_circles; //iterator for vecCircles vector
        
        int                 m_video_width = 640;
        int                 m_video_height = 480;


};

#endif //WEBCAM_HPP

