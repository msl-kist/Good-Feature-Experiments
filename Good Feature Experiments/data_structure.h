#include <vector>

#include <opencv2/opencv.hpp>
#include "OpenCv2.4.5_libs.h"

using namespace std;
using namespace cv;

/************************************************************************/
/*	Null Keypoint ó������ ��ũ��										*/
/*	(������)															*/
/************************************************************************/
#define IS_NULL(keypoint)	((keypoint).pt.x == 99999 && (keypoint).pt.y == 99999)
#define NULL_KEYPOINT		(cv::KeyPoint(99999, 99999, 0))						// ���� - K_.push_back(NULL_KEYPOINT);


/************************************************************************/
/*	�� Keypoint�� ����Ǵ� ������ ��										*/
/*	(������)																*/
/************************************************************************/
struct Data
{
	cv::KeyPoint	keypoint;
	cv::Mat			descriptor;

	int	cornerness;					// ���� 1) cornerness(n_exist)  - n_exist / n_transformed
	vector<float>	selfSimilarity; // ���� 2) Self Similarity	- ����: # of transformed images
	//vector						// ���� 3) Histogram
};

/************************************************************************/
/*	2�� ���� - Self Similarity Test ���� �ڵ�								*/
/*	(ä��ȣ)																*/
/************************************************************************/
void SelfSimilarityTest(Mat &referenceImage, Mat &transformedImage,												// I and T(I)
	vector<KeyPoint> &referenceKeyPoints, vector<KeyPoint> &transformedKeyPoints,				// K and K'
	Mat &referenceDescriptors, Mat &transformedDescriptors,									// d(K) and d(K')
	vector<struct Data> &result);

/************************************************************************/
/*	1�� ���� - Cornerness ���� �ڵ�
/*	(������)
/************************************************************************/
void CornernessTest(Mat &referenceImage, Mat &transformedImage,
	vector<KeyPoint> &referenceKeyPoints, vector<KeyPoint> &transformedKeyPoints,				// K and K'
	vector<struct Data> &result);