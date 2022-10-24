#include "webcam.hpp"

#include <iostream>
#include <stdio.h>

int main()
{
	Webcam webcam;

	//test show windows (show main window, show processed image window)
	webcam.set_show_bools(true, false);

	if(webcam.valid() == false)
		return -1;

	webcam.main_loop();

	return 0;
}
