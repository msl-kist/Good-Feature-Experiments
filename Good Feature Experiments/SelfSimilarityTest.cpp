#include "data_structure.h"

using namespace cv;

// TODO: (ä��ȣ) 2�� ���� ��� Ȯ��
void SelfSimilarityTest(Mat &referenceImage, Mat &transformedImage,												// I and T(I)
						vector<KeyPoint> &referenceKeyPoints, vector<KeyPoint> &transformedKeyPoints,				// K and K'
						Mat &referenceDescriptors, Mat &transformedDescriptors,									// d(K) and d(K')
						vector<struct Data> &result)
{
	for(int i=0; i<referenceKeyPoints.size(); ++i)
	{
		if(!IS_NULL(transformedKeyPoints[i]))
		{
			// ��ũ���� ����
			Mat desc1;
			desc1.push_back(referenceDescriptors.row(i));
			Mat desc2;
			desc2.push_back(transformedDescriptors.row(i));


			/////TEST ���Դϴ�///////
			

			// TODO: �Ÿ����ϱ�
			float score = 0;

			// result�� �ֱ�
			result[i].selfSimilarity.push_back(score);
		}
	}
}