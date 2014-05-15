#include "data_structure.h"

using namespace cv;

void SelfSimilarityTest(Mat referenceImage, Mat transformedImage,												// I and T(I)
						vector<KeyPoint> referenceKeyPoints, vector<KeyPoint> transformedKeyPoints,				// K and K'
						Mat referenceDescriptors, Mat transformedDescriptors,									// d(K) and d(K')
						vector<struct Data> result)
{
	for(int i=0; i<referenceKeyPoints.size(); ++i)
	{
		if(!IS_NULL(transformedKeyPoints[i]))				// TODO: NONE 정의
		{
			// 디스크립터 추출
			Mat desc1;
			desc1.push_back(referenceDescriptors.row(i));
			Mat desc2;
			desc2.push_back(transformedDescriptors.row(i));

			

			// TODO: 거리구하기
			float score = 0;

			// result에 넣기
			result[i].selfSimilarity.push_back(score);
		}
	}
}