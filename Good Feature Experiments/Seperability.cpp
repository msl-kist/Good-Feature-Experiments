#include "data_structure.h"

using namespace cv;

#define SWAP(a, b) { int t; t = a; a = b; b = t; }


void Seperability(Mat referenceImage, Mat transformedImage,								// I and T(I)
	vector<KeyPoint> referenceKeyPoints, vector<KeyPoint> transformedKeypoints,				// K and K'
	Mat referenceDescriptors, Mat transformedDescriptors,									// d(K) and d(K')
	vector<struct Data> result)
{
	BruteForceMatcher<Hamming> matcher; // recent matcher
	vector<DMatch> matches_brisk;


	for(int i=0; i<referenceKeyPoints.size(); ++i)
	{
		if(!IS_NULL(referenceDescriptors[i]))				//TODO: NONE ����
		{
			// ��ũ���� ����
			Mat desc1;
			desc1.push_back(referenceDescriptors.row(i));

			for(int j=0; j<transformedKeypoints.size(); ++j)
			{
				if(!IS_NULL(transformedKeypoints[j]))				//TODO: NONE ����
				{
					// ��ũ���� ����
					Mat desc2;
					desc2.push_back(transformedDescriptors.row(j));
					
					//TODO: �Ÿ����ϱ�
					matcher.match(desc1, desc2, matches_brisk);

					float score = matches_brisk[0].distance;

					// result�� �ֱ�
					result[i * referenceKeyPoints.size() + j].selfSimilarity.push_back(score);

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