#include <vector>

using namespace std;

#include "OpenCv2.4.5_libs.h"

#include <opencv2/opencv.hpp>

#include "data_structure.h"


void SelfSimilarityTest();

int main()
{
	cv::Mat	referenceImage;
	vector<cv::Mat> images;

	SelfSimilarityTest();
	

	return 0;
}

