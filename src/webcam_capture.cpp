//opencv
#include "opencv2/opencv.hpp"

//std
#include <iostream>
#include <cstdlib>

//

//main
int main(int argc, char *argv[])
{
    cv::VideoCapture camera; //OpenCV video capture object
    cv::Mat image; //OpenCV image object
	  int cam_id; //camera id . Associated to device number in /dev/videoX
	  cv::Scalar_<unsigned char> px_value; //pixel value (4-element vector)
	  int user_key; //user pressed key to quit



    void paint_center(cv::Mat & image)
    {
            const int y = image.rows/2;
            const int x = image.cols/2;

       for(int j = 0; j < image.rows/2; j++)
       {
           for(int i = 0; i < image.cols/2; i++)
           {
            cv::Vec3b intensity = image.at<cv::Vec3b>(y+j, x+i);

                    intensity[1] = 0;
                    intensity[2] = 0;
                    intensity[3] = 255;

         }
         image.at<cv::Vec3b>(y+j, x+i) = intensity;
       }
     }
	//check user args
	switch(argc)
	{
		case 1: //no argument provided, so try /dev/video0
			cam_id = 0;
			break;
		case 2: //an argument is provided. Get it and set cam_id
			cam_id = atoi(argv[1]);
			break;
		default:
			std::cout << "Invalid number of arguments. Call program as: webcam_capture [video_device_id]. " << std::endl;
			std::cout << "EXIT program." << std::endl;
			break;
	}

	//advertising to the user
	std::cout << "Opening video device " << cam_id << std::endl;

    //open the video stream and make sure it's opened
    if( !camera.open(cam_id) )
	{
        std::cout << "Error opening the camera. May be invalid device id. EXIT program." << std::endl;
        return -1;
    }

    //capture loop. Out of user press a key
    while(1)
	{
		//Read image and check it. Blocking call up to a new image arrives from camera.
        if(!camera.read(image))
		   {
            std::cout << "No frame" << std::endl;
            paint_center(image);
            cv::waitKey();

        }
}


        //show image in a window
        cv::imshow("Output Window", image);

		//Waits 30 millisecond to check if 'q' key has been pressed. If so, breaks the loop. Otherwise continues.
    	if( (unsigned char)(cv::waitKey(30) & 0xff) == 'q' ) break;
    }
}
