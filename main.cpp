#include "include/webcam.hpp"

#include <iostream>
#include <stdio.h>

int main()
{
	cv::VideoCapture webcam(0);

	if(webcam.isOpened() == false)
	{
		std::cout << "error: cap-webcam not accessed succesfully" << std::endl;
		return -1;
	}

	cv::Mat matOriginal; 	// Matrix Object, input from webcam
	cv::Mat matProcessed; //Matrix Object, processed image

	std::vector<cv::Vec3f> vecCircles; 
	//3 element vector of floats, pass by ref output to 	HoughCircles()
	std::vector<cv::Vec3f>::iterator itrCircles;  //iterator for vecCircles vector

	cv::namedWindow("Original");
	cv::namedWindow("Processed");

	char charCheckForEscKey = 0;

	while(charCheckForEscKey != 27)
	{
		if(webcam.read(matOriginal) == false)
		{
			std::cout << "error: frame not read from webcam" << std::endl;
			break;
		}
        
		cv::flip(matOriginal, matOriginal, 1); //1 flips around y-axis

		cv::inRange(matOriginal,
				cv::Scalar(0,0,175),
				cv::Scalar(100,100,256),
				matProcessed);

		/* Call inRange to take original image and turn into processed image, 
		Functionname(Function Input, min filter value(if greater than or equal to 		
        this BGR format), max filter value, function output);
		*/

		cv::GaussianBlur(matProcessed, 
						matProcessed, 
						cv::Size(9,9),
						1,5);

		/* This function helps to smooth the image for easier image detection on 		
        next functions.
		functionname(function input, function output, smoothing window width and 		
        height in pixels, sigma value determines how much blur to the image	
		*/

        cv::HoughCircles(matProcessed, 
						vecCircles, 
						cv::HOUGH_GRADIENT, 
						2,
						matProcessed.rows / 4, 
						100,
						50,
						10,
						400);

		
		/*
		fill circles vector with all circles in processed image - > 
		function name( input image, 
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

		for(itrCircles = vecCircles.begin(); itrCircles != vecCircles.end(); itrCircles++)
		{	
			//position centre of circle detected
			std::cout << "position at x_pos = " 	<< 	(*itrCircles)[0]
							    <<  ", y_pos = "	<<  (*itrCircles)[1]
							    <<  ", radius = "	<<  (*itrCircles)[2]  
							    << std::endl;

			//drawing green circle at centre of detected circle
			//drawing on original image, centrepoit of circle(x&y), radius in pixels, green 			//colour
			cv::circle(matOriginal,
					cv::Point((int)(*itrCircles)[0], (int)(*itrCircles)[1]), 
					3, 
					cv::Scalar(0, 255, 0), 
					cv::FILLED);
			
			//draw red circle around object
			cv::circle(matOriginal, 
					cv::Point((int)(*itrCircles)[0], (int)(*itrCircles)[1]),
					40,  //(int)(*itrCircles)[3]
					cv::Scalar(0,0,255),
					3);
		//end for
		}	

		cv::imshow("Original", matOriginal);
		cv::imshow("Processed", matProcessed);
	
		charCheckForEscKey = cv::waitKey(10);
		//end while
	}
		

	return 0;
}
