#include <vector>
#include <map>

#include <opencv2/opencv.hpp>
#include "OpenCv2.4.5_libs.h"

#include <opencv2/legacy/legacy.hpp>
#include "../Transformed Images Generator/value.h"

using namespace std;
using namespace cv;

/************************************************************************/
/*	Null Keypoint 처리위한 매크로										*/
/*	(서종훈)															*/
/************************************************************************/
#define IS_NULL(keypoint)	(keypoint.pt.x == 99999 && keypoint.pt.y == 99999)
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
	map<int, int>	seperatibility;	// 실험 3) Histogram			- MAP 자료형은 http://www.hanbit.co.kr/network/view.html?bi_id=1618 여기 참조하시오
};

/************************************************************************/
/*	각 Image에 저장되는 데이터 형										*/
/*	(양윤식)																*/
/************************************************************************/
struct ImageData
{
	int dbImageNum;
	float scale;
	int angle;
	int gaussian;

	vector<struct Data> data;
};

/************************************************************************/
/*TODO: (채승호) 	2번 실험 - Self Similarity Test 실험 코드	
/************************************************************************/
void SelfSimilarityTest(vector<KeyPoint> &referenceKeyPoints, vector<KeyPoint> &transformedKeyPoints,				// K and K'
					Mat &referenceDescriptors, Mat &transformedDescriptors,									// d(K) and d(K')
					BruteForceMatcher<Hamming> &matcher, vector<DMatch> &matches_brisk,
					vector<struct Data> &result);

/************************************************************************/
/*TODO: (채승호) 	3번 실험 - Seperatibility 실험 코드
/************************************************************************/
void SeperatibilityTest(vector<KeyPoint> &referenceKeyPoints, vector<KeyPoint> &transformedKeyPoints,				// K and K'
					Mat &referenceDescriptors, Mat &transformedDescriptors,									// d(K) and d(K')
					BruteForceMatcher<Hamming> &matcher, vector<DMatch> &matches_brisk,
					vector<struct Data> &result);


/************************************************************************/
/*TODO: (양윤식) 	1번 실험 - Cornerness 실험 코드
/************************************************************************/
void CornernessTest(vector<KeyPoint> &referenceKeyPoints, vector<KeyPoint> &transformedKeyPoints, 				// K and K'
	Mat &transformedDescriptors,struct ImageData &result, int width, int height);

/************************************************************************/
/*TODO: (양윤식) 	저장된 영상과 변환행렬을 로드하는 코드
/************************************************************************/
void LoadData(vector<KeyPoint> &referenceKeyPoints, vector<vector<KeyPoint>> &transformedKeyPoints,
	Mat &referenceDescriptor, vector<Mat> &transformedDescriptors, vector<struct ImageData> &result);

/************************************************************************/
/*TODO: (양윤식) 	저장된 영상과 변환행렬을 로드하는 코드
/************************************************************************/
void LoadImage(int num, int& width, int& height);