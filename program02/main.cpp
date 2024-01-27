#include <iostream>
#include <string>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>

void display(cv::Mat image, std::string windowName = "Image") {
    cv::namedWindow(windowName);
    cv::imshow(windowName, image);
    cv::waitKey(1000 * 100);
    cv::destroyWindow(windowName);
}

int main(int argc, char* argv[]){

  if( argc != 2 ){
    std::cout << "main <filename>" << std::endl;
    exit(0);
  }

  cv::Mat src = cv::imread(argv[1], 0);

  std::vector<cv::KeyPoint> keypoints;
  cv::Ptr<cv::SIFT> detector = cv::SiftFeatureDetector::create();
  detector->detect(src, keypoints);

	// キーポイントの数を表示
	int keypoint_num = keypoints.size();
	std::cout << "keypoint_num :" << keypoint_num << std::endl;

  cv::Mat dst;
  cv::drawKeypoints(src, keypoints, dst);    

  display(dst);

  return 0;
}

