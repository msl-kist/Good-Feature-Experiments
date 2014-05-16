#include "data_structure.h"

#include "brisk/brisk.h"
#include "brisk/Matcher.h"
#include "brisk/MatchVerifier.hpp"
#include "brisk/GroundTruth.hpp"

int main()
{
	Mat	referenceImage;
	vector<Mat> transformedImages;

	vector<Mat> matrices;

	// 먼저 영상들을 로드한다.
	LoadImages(referenceImage, transformedImages, matrices);

	// TODO: (종훈) Reference 영상을 처리하자
	//==============================================================
	vector<KeyPoint> referenceKeyPoints;
	vector<vector<KeyPoint>> transformedKeyPoints;

	// Descriptor, Matcher 변수
	Ptr<DescriptorExtractor> descriptorExtractor_brisk;	
	BruteForceMatcher<Hamming> matcher; // recent matcher
	vector<DMatch> matches_brisk;

	Mat referenceDescriptor;
	vector<Mat>	transformedDescriptors;

	// 결과 저장 자료형
	vector<struct Data> result;

	for(int i=0; i<transformedImages.size();++i)
	{
		Mat &transformedImage = transformedImages[i];

		// 1번 실험
		CornernessTest(	referenceImage, 
						transformedImage,
						referenceKeyPoints, 
						transformedKeyPoints[i],				// K and K'
						matrices[i], 
						result);

		// TODO: (종훈) 변환 이미지에 대한 디스크립터 생성
		descriptorExtractor_brisk->compute(referenceImage, referenceKeyPoints, referenceDescriptor);
		for(int i = 0; i<transformedImages.size(); i++)
			descriptorExtractor_brisk->compute(transformedImages[i], transformedKeyPoints[i], transformedDescriptors[i]);

		// 2번 실험
		SelfSimilarityTest(	referenceKeyPoints,
							transformedKeyPoints[i],
							referenceDescriptor,
							transformedDescriptors[i],
							matcher, matches_brisk,
							result);

		// 3번 실험
		SeperatibilityTest(	referenceKeyPoints,
							transformedKeyPoints[i],
							referenceDescriptor,
							transformedDescriptors[i],
							matcher, matches_brisk,
							result);
	}

	// TODO: (종훈) 파일 저장

	return 0;
}

