#include <iostream>  
#include <string>  

#include <opencv2/opencv.hpp>  


int main(int argc, char** argv)
{
	std::string videoFile = "../test.avi";

	cv::VideoCapture capture;
	capture.open(videoFile);

	if (!capture.isOpened())
	{
		std::cout << "read video failure" << std::endl;
		std::cin.get();
		return -1;
	}


	cv::BackgroundSubtractorMOG2 mog;

	cv::Mat foreground;
	cv::Mat background;

	cv::Mat frame;
	long frameNo = 0;
	while (capture.read(frame))
	{
		++frameNo;

		std::cout << frameNo << std::endl;

		// ÔË¶¯Ç°¾°¼ì²â£¬²¢¸üÐÂ±³¾°  
		//242
		mog(frame, foreground, 0.005);

		// ¸¯Ê´  
		cv::erode(foreground, foreground, cv::Mat());

		// ÅòÕÍ  
		cv::dilate(foreground, foreground, cv::Mat());

		mog.getBackgroundImage(background);   // ·µ»Øµ±Ç°±³¾°Í¼Ïñ  

		cv::imshow("video", foreground);
		cv::imshow("background", background);
		cv::imshow("avi",frame);

		if (cv::waitKey(25) > 0)
		{
			break;
		}
	}
	return 0;
}