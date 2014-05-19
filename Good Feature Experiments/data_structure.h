#include <vector>
#include <map>

#include <opencv2/opencv.hpp>
#include "OpenCv2.4.5_libs.h"

#include <opencv2/legacy/legacy.hpp>
#include "../Transformed Images Generator/value.h"

using namespace std;
using namespace cv;

/************************************************************************/
/*	Null Keypoint ó������ ��ũ��										*/
/*	(������)															*/
/************************************************************************/
#define IS_NULL(keypoint)	(keypoint.pt.x == 99999 && keypoint.pt.y == 99999)
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
	map<int, int>	seperatibility;	// ���� 3) Histogram			- MAP �ڷ����� http://www.hanbit.co.kr/network/view.html?bi_id=1618 ���� �����Ͻÿ�
};

/************************************************************************/
/*	�� Image�� ����Ǵ� ������ ��										*/
/*	(������)																*/
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
/*TODO: (ä��ȣ) 	2�� ���� - Self Similarity Test ���� �ڵ�	
/************************************************************************/
void SelfSimilarityTest(vector<KeyPoint> &referenceKeyPoints, vector<KeyPoint> &transformedKeyPoints,				// K and K'
					Mat &referenceDescriptors, Mat &transformedDescriptors,									// d(K) and d(K')
					BruteForceMatcher<Hamming> &matcher, vector<DMatch> &matches_brisk,
					vector<struct Data> &result);

/************************************************************************/
/*TODO: (ä��ȣ) 	3�� ���� - Seperatibility ���� �ڵ�
/************************************************************************/
void SeperatibilityTest(vector<KeyPoint> &referenceKeyPoints, vector<KeyPoint> &transformedKeyPoints,				// K and K'
					Mat &referenceDescriptors, Mat &transformedDescriptors,									// d(K) and d(K')
					BruteForceMatcher<Hamming> &matcher, vector<DMatch> &matches_brisk,
					vector<struct Data> &result);


/************************************************************************/
/*TODO: (������) 	1�� ���� - Cornerness ���� �ڵ�
/************************************************************************/
void CornernessTest(vector<KeyPoint> &referenceKeyPoints, vector<KeyPoint> &transformedKeyPoints, 				// K and K'
	Mat &transformedDescriptors,struct ImageData &result, int width, int height);

/************************************************************************/
/*TODO: (������) 	����� ����� ��ȯ����� �ε��ϴ� �ڵ�
/************************************************************************/
void LoadData(vector<KeyPoint> &referenceKeyPoints, vector<vector<KeyPoint>> &transformedKeyPoints,
	Mat &referenceDescriptor, vector<Mat> &transformedDescriptors, vector<struct ImageData> &result);

/************************************************************************/
/*TODO: (������) 	����� ����� ��ȯ����� �ε��ϴ� �ڵ�
/************************************************************************/
void LoadImage(int num, int& width, int& height);