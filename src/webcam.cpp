#include "webcam.hpp"

Webcam::Webcam() 
{
    m_valid = true;
    if (m_capture.open(m_camera) == false) 
    {
        std::cout << "Failed to open camera" << std::endl;
        m_valid = false;
    }

    m_capture.set(cv::CAP_PROP_FRAME_WIDTH, m_video_width);
    m_capture.set(cv::CAP_PROP_FRAME_HEIGHT, m_video_height);
    m_mat_original = cv::Mat::zeros(m_video_height, m_video_width, CV_8UC3);
	m_tracker = cv::TrackerKCF::create();
}

Webcam::~Webcam() 
{
    // m_capture.release();
    // cv::destroyAllWindows();
}

void Webcam::capture() 
{
    if(valid())
    {
        if(m_capture.read(m_mat_original) == false)
        {
            std::cout << "error: frame not read from webcam" << std::endl;
            m_valid = false;
        }
        cv::flip(m_mat_original, m_mat_original, 1); //1 flips around y-axis
    }
}

void Webcam::set_show_bools(bool show_original, bool show_processed)
{
    m_original_show = show_original;
    m_processed_show = show_processed;
}

void Webcam::process_object_range()  	//NOT USED
{
    /* Call inRange to take original image and turn into processed image,
	inRange(Function Input, min filter value(if greater than or equal to
	this BGR format), max filter value, function output);
	*/
    cv::inRange(m_mat_original,
				cv::Scalar(0, 0, 175),
				cv::Scalar(100, 100, 256),
				m_mat_processed);

    /* This function helps to smooth the image for easier image detection on
    next functions.
    GaussianBlur(function input, function output, smoothing window width and
    height in pixels, sigma value determines how much blur to the image
    */

    cv::GaussianBlur(m_mat_processed,
					 m_mat_processed,
					 cv::Size(9, 9),
					 1, 5);

	/*
	fill circles vector with all circles in processed image - >
	HoughCirles(input image,
	function output(must be STL vector!),
	2-pass logo for detecting circles only choice available,
	size of image / this
	value… I.e accumulator resolution = size of image divided by 2,
	min distance in pixels between centres of detected circles,
	high threshold of edge detector,
	low threshold of edge detector,
	min circle radius (smaller won’t be returned),
	max radius.)
	*/

	cv::HoughCircles(m_mat_processed,
					 m_vec_circles,
					 cv::HOUGH_GRADIENT,
					 2,
					 m_mat_processed.rows / 4,
					 100,
					 50,
					 10,
					 400);

}

void Webcam::output_tracking_circle()	//NOT USED
{
    for (m_itr_circles = m_vec_circles.begin(); m_itr_circles != m_vec_circles.end(); m_itr_circles++)
	{
		// position centre of circle detected
		std::cout << "position at x_pos = " << (*m_itr_circles)[0]
				  << ", y_pos = " << (*m_itr_circles)[1]
				  << ", radius = " << (*m_itr_circles)[2]
				  << std::endl;

		// drawing green circle at centre of detected circle
		// drawing on original image, centrepoit of circle(x&y), radius in pixels, green 			
        //colour
		cv::circle(m_mat_original,
				   cv::Point((int)(*m_itr_circles)[0], (int)(*m_itr_circles)[1]),
				   3,
				   cv::Scalar(0, 255, 0),
				   cv::FILLED);

		// draw red circle around object
		cv::circle(m_mat_original,
				   cv::Point((int)(*m_itr_circles)[0], (int)(*m_itr_circles)[1]),
				   60, // OR (int)(*itrCircles)[3]
				   cv::Scalar(0, 0, 255),
				   3);
	}
}

void Webcam::create_windows()
{
    if(m_original_show)
        cv::namedWindow("Main Image");
    if(m_processed_show)
    	cv::namedWindow("Processed Image");
}

void Webcam::show_video_outputs()
{
    if(m_original_show)
        cv::imshow("Main Image", m_mat_original);

    if(m_processed_show)
	    cv::imshow("Processed Image", m_mat_processed);

}

void Webcam::set_tracking_box()
{
	std::cout << "Hit SPACE to pause camera, then select tracking box with mouse..." << std::endl;
	while(!m_spacebar_pressed) //set secondary bool for restarting camera when its not ideal snapshot
	{
		capture();
		show_video_outputs();        
        wait(10, 32);
	}

	while(m_tracking_box.empty()) //required while or any key other than SPACE/ENTER crashes
	{
		m_tracking_box = cv::selectROI("Main Image", m_mat_original, false);
	}
}

void Webcam::main_loop() 
{	
	create_windows();
	set_tracking_box();
	m_tracker->init(m_mat_original, m_tracking_box);

    while(valid() == true)
    {
        capture();
		if(m_tracker->update(m_mat_original, m_tracking_box))
			cv::rectangle(m_mat_original, m_tracking_box, cv::Scalar(255,0,0), 3, 8);

	    // process_object_range();
	    // output_tracking_circle();
	    show_video_outputs();        
        wait(10, 27); //checks for esc key to exit
    }
}

void Webcam::wait(int timer, int key) 
{ 
    int key_pressed;
    key_pressed = cv::waitKey(timer);
    
    if (key_pressed == 27 && key == key_pressed)
    { 
        m_valid = false;
        std::cout << "ESC key pressed, closing app!" << std::endl;
    }
	if (key_pressed == ' ' && key == key_pressed)
    { 
        m_spacebar_pressed = true;
        std::cout << "SPACE pressed, snapshot for tracking box selection!" << std::endl;
    }
}

bool Webcam::valid() { return m_valid; }



