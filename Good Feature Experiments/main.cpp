#include <conio.h>

#include "data_structure.h"

#include "brisk/brisk.h"
#include "brisk/Matcher.h"
#include "brisk/MatchVerifier.hpp"
#include "brisk/GroundTruth.hpp"

void main()
{
	Mat	referenceImage;
	vector<Mat> transformedImages;

	int width, height;

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
	vector<struct ImageData> imageData;

	// 먼저 영상들을 로드한다.
	LoadData(referenceKeyPoints, transformedKeyPoints, referenceDescriptor, transformedDescriptors, result, imageData);
	LoadImage(1,width,height);

	for(int i=0; i<imageData.size();++i)
	{
		//Mat &transformedImage = transformedImages[i];
		vector<KeyPoint> tempKeypoint;

		// 1번 실험
		CornernessTest(	referenceKeyPoints, 
						transformedKeyPoints[i],				// K and K'
						transformedDescriptors[i],
						imageData[i],result, tempKeypoint,width,height);


		/*
		// TODO: (종훈) 변환 이미지에 대한 디스크립터 생성
		descriptorExtractor_brisk->compute(referenceImage, referenceKeyPoints, referenceDescriptor);
		for(int i = 0; i<transformedImages.size(); i++)
			descriptorExtractor_brisk->compute(transformedImages[i], transformedKeyPoints[i], transformedDescriptors[i]);
		*/
		
		// 2번 실험
		SelfSimilarityTest(	referenceKeyPoints,
							transformedKeyPoints[i],
							referenceDescriptor,
							transformedDescriptors[i],
							matcher, matches_brisk,
							result);
		/*
		// 3번 실험
		SeperatibilityTest(	referenceKeyPoints,
							transformedKeyPoints[i],
							referenceDescriptor,
							transformedDescriptors[i],
							matcher, matches_brisk,
							result[i].data);
		*/					
	}

	// TODO: (종훈) 파일 저장

	//return 0;

	getch();
}

