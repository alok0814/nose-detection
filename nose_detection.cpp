#include "MediaImage.hpp"

using namespace std;
using namespace media;

void nose() {
	std::cout << "Write the directory where you want to save the image" << std::endl;
	std::string dir;
	cin >> dir;
	std::string resPath = dir + "/";//Set the directory name to save the image
	_mkdir(resPath.c_str());

	cv::VideoCapture video(0); //Camera on

	if (!video.isOpened()) { //Camera Error
		std::cout << "Camera not found" << std::endl;
		exit(1);
	}
	cv::Mat frame; //For frame storage

	cv::CascadeClassifier cascade_nose; //For nasal cascade classifier storage

	cascade_nose.load("../datas/asm/haarcascade_mcs_nose.xml"); //Reading cascading files

	std::vector<cv::Rect> contour; //For storing rectangles

	while (video.read(frame)) { //Loop

		cascade_nose.detectMultiScale(frame, contour, 1.35, 8, 0, cv::Size(30, 30)); //Target detection

		for (int i = 0; i < contour.size(); i++) { //Repeat for the number of detections
			cv::rectangle(frame, cv::Point(contour[i].x, contour[i].y), cv::Point(contour[i].x + contour[i].width, contour[i].y + contour[i].height), cv::Scalar(0, 0, 255), 1); //Rectangle visualization
			cv::putText(frame, "The nose was detected", cv::Point(0, 40), cv::FONT_HERSHEY_COMPLEX, 1.5, cv::Scalar(0, 0, 255), 3); //Show text
			printf("[x,y]=[%d,%d]\n",contour[i].x, contour[i].y); //Show nose coordinates
			if(contour[i].x == contour[i].y){
				cv::imwrite(resPath + "center_nose(" + to_string(i) + ").jpg", frame);//Save a photo of the nose in the center of the window
			}
		}

		cv::imshow("Nose Detector", frame); //display the window

		int key = cv::waitKey(1);

		if (key == 'q') { //Conditions to end
			cv::destroyWindow("Nose Detector");
			break;
		}
	}
	
}