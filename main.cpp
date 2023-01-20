#include "camerabasler.h"
#include <opencv2/opencv.hpp>
#include <iostream>

using Vision::Cpp::CameraBasler;

int main()
{
	std::cout << "Basler pylon example" << std::endl;

	uint32_t width, height;

	CameraBasler cameraBasler = CameraBasler(1, 500);

	std::vector<uint8_t> * buffer = cameraBasler.GrabImage(&width, &height);

	if (buffer == nullptr)
	{
		std::cout << "Unable to grab from camera ... exiting" << std::endl;

		return EXIT_FAILURE;
	}

	cv::Mat openCvImage = cv::Mat(height, width, CV_8UC1, (void *) buffer->data()).clone();
	
	cv::Mat openCvImageResized;
	cv::resize(openCvImage, openCvImageResized, cv::Size(width / 3, height / 3), cv::INTER_LINEAR);
	std::cout << "Resized image dimensions: " << openCvImageResized.size() << std::endl;

	cv::imshow("Window", openCvImageResized);
	cv::waitKey(0);	

	return EXIT_SUCCESS;
}

