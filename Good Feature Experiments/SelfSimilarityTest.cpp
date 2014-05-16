#include "data_structure.h"

using namespace cv;

// TODO: (채승호) 2번 실험 모듈 확인

void SelfSimilarityTest(vector<KeyPoint> &referenceKeyPoints, vector<KeyPoint> &transformedKeyPoints,				// K and K'
					Mat &referenceDescriptors, Mat &transformedDescriptors,									// d(K) and d(K')
					BruteForceMatcher<Hamming> &matcher, vector<DMatch> &matches_brisk,
					vector<struct Data> &result)
{
	for(int i=0; i<referenceKeyPoints.size(); ++i)
	{
		if(!IS_NULL(transformedKeyPoints[i]))
		{
			// 디스크립터 추출
			Mat desc1;
			desc1.push_back(referenceDescriptors.row(i));
			Mat desc2;
			desc2.push_back(transformedDescriptors.row(i));


			//TODO: 거리구하기
			matcher.match(desc1, desc2, matches_brisk);

			float score = matches_brisk[0].distance;

			// result에 넣기
			result[i].selfSimilarity.push_back(score);
		}
	}
}