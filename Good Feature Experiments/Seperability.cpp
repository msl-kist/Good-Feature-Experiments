#include "data_structure.h"

using namespace cv;

#define SWAP(a, b) { int t; t = a; a = b; b = t; }


void SeperatibilityTest(vector<KeyPoint> &referenceKeyPoints, vector<KeyPoint> &transformedKeyPoints,				// K and K'
	Mat &referenceDescriptors, Mat &transformedDescriptors,									// d(K) and d(K')
	BruteForceMatcher<Hamming> &matcher, vector<DMatch> &matches_brisk,
	vector<struct Data> &result)
{
	for(int i=0; i<referenceKeyPoints.size(); ++i)
	{
		if(!IS_NULL(referenceKeyPoints[i]))				//TODO: NONE 정의
		{
			// 디스크립터 추출
			Mat desc1;
			desc1.push_back(referenceDescriptors.row(i));

			for(int j=0; j< result.size() ; ++j)
			{
				if(!IS_NULL(result[j].keypoint))				//TODO: NONE 정의
				{
					// 디스크립터 추출
					Mat desc2;
					desc2.push_back(result[j].descriptor);

					//TODO: 거리구하기
					matcher.match(desc1, desc2, matches_brisk);

					float score = matches_brisk[0].distance;

					// result에 넣기
					result[i].selfSimilarity.push_back(score);

					//insertionSort(result[i * referenceKeyPoints.size() + j].selfSimilarity, result[i * referenceKeyPoints.size() + j].selfSimilarity.size());
					result[i].seperatibility[(int)score]++;
				}
			}
		}
	}	
}

//
//void insertionSort(vector<float> data, int n)
//{
//	for(int i = 1; i<n; i++)
//	{
//		float temp = data[i];
//
//		for(int j = i; i>0; j--)
//		{
//			if(temp < data[j-1])
//			{
//				data[j] = data[j-1];
//				data[j-1] = temp;
//			}
//			else
//			{
//				break;
//			} 
//		}
//	}
//}