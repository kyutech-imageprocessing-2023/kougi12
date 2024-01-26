#include <iostream>
#include <string>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>


void display(cv::Mat image, std::string windowName = "Image") {
    cv::namedWindow(windowName);
    cv::imshow(windowName, image);
    cv::waitKey(1000 * 100);
    cv::destroyWindow(windowName);
}

int main(int argc, char* argv[]){

  if( argc != 3 ){
    std::cout << "main <filename> <th>" << std::endl;
    exit(0);
  }

  cv::Mat src = cv::imread(argv[1], 0);
  cv::Mat dst;

  display(src);

  cv::cornerHarris( src, dst, 2, 3, 0.04, cv::BORDER_DEFAULT );

  cv::Mat dst_norm, dst_norm_scaled;
  
  normalize( dst, dst_norm, 0, 255, cv::NORM_MINMAX, CV_32FC1, cv::Mat() );
  convertScaleAbs( dst_norm, dst_norm_scaled );

  int i, j, count = 0;
  for( i=0; i<dst_norm.rows ; i++ ){
    for( j=0; j<dst_norm.cols; j++ ){
      if( dst_norm.at<float>(i,j) > atoi(argv[2]) ){
        count++;
        circle( dst_norm_scaled, cv::Point(j,i), 5, cv::Scalar(0), 2, 8, 0 );
      }
    }
  }

  std::cout << count << " points found." << std::endl;

  display(dst_norm_scaled);
    
  return 0;
}

