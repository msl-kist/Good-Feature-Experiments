#include <vector>

#include <opencv2/opencv.hpp>
#include "OpenCv2.4.5_libs.h"

using namespace std;
using namespace cv;

/************************************************************************/
/*	Null Keypoint 처리위한 매크로										*/
/*	(서종훈)															*/
/************************************************************************/
#define IS_NULL(keypoint)	((keypoint).pt.x == 99999 && (keypoint).pt.y == 99999)
#define NULL_KEYPOINT		(cv::KeyPoint(99999, 99999, 0))						// 예제 - K_.push_back(NULL_KEYPOINT);


/************************************************************************/
/*	각 Keypoint에 저장되는 데이터 형										*/
/*	(서종훈)																*/
/************************************************************************/
struct Data
{
	cv::KeyPoint	keypoint;
	cv::Mat			descriptor;

	int	cornerness;					// 실험 1) cornerness(n_exist)  - n_exist / n_transformed
	vector<float>	selfSimilarity; // 실험 2) Self Similarity	- 개수: # of transformed images
	//vector						// 실험 3) Histogram
};

/************************************************************************/
/*	2번 실험 - Self Similarity Test 실험 코드								*/
/*	(채승호)																*/
/************************************************************************/
void SelfSimilarityTest(Mat &referenceImage, Mat &transformedImage,												// I and T(I)
	vector<KeyPoint> &referenceKeyPoints, vector<KeyPoint> &transformedKeyPoints,				// K and K'
	Mat &referenceDescriptors, Mat &transformedDescriptors,									// d(K) and d(K')
	vector<struct Data> &result);

/************************************************************************/
/*	1번 실험 - Cornerness 실험 코드
/*	(양윤식)
/************************************************************************/
void CornernessTest(Mat &referenceImage, Mat &transformedImage,
	vector<KeyPoint> &referenceKeyPoints, vector<KeyPoint> &transformedKeyPoints,				// K and K'
	vector<struct Data> &result);