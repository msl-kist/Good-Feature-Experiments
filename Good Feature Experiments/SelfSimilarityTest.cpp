#include "data_structure.h"

using namespace cv;

// TODO: (ä��ȣ) 2�� ���� ��� Ȯ��

void SelfSimilarityTest(vector<KeyPoint> &referenceKeyPoints, vector<KeyPoint> &transformedKeyPoints,				// K and K'
					Mat &referenceDescriptors, Mat &transformedDescriptors,									// d(K) and d(K')
					BruteForceMatcher<Hamming> &matcher, vector<DMatch> &matches_brisk,
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


			//TODO: �Ÿ����ϱ�
			matcher.match(desc1, desc2, matches_brisk);

			float score = matches_brisk[0].distance;

			// result�� �ֱ�
			result[i].selfSimilarity.push_back(score);
		}
	}
}