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

	// TODO: (����) Reference ������ ó������
	//==============================================================
	vector<KeyPoint> referenceKeyPoints;
	vector<vector<KeyPoint>> transformedKeyPoints;

	// Descriptor, Matcher ����
	Ptr<DescriptorExtractor> descriptorExtractor_brisk;	
	BruteForceMatcher<Hamming> matcher; // recent matcher
	vector<DMatch> matches_brisk;

	Mat referenceDescriptor;
	vector<Mat>	transformedDescriptors;

	// ��� ���� �ڷ���
	vector<struct Data> result;
	vector<struct ImageData> imageData;

	// ���� ������� �ε��Ѵ�.
	LoadData(referenceKeyPoints, transformedKeyPoints, referenceDescriptor, transformedDescriptors, result, imageData);
	LoadImage(1,width,height);

	for(int i=0; i<imageData.size();++i)
	{
		//Mat &transformedImage = transformedImages[i];
		vector<KeyPoint> tempKeypoint;

		// 1�� ����
		CornernessTest(	referenceKeyPoints, 
						transformedKeyPoints[i],				// K and K'
						transformedDescriptors[i],
						imageData[i],result, tempKeypoint,width,height);


		/*
		// TODO: (����) ��ȯ �̹����� ���� ��ũ���� ����
		descriptorExtractor_brisk->compute(referenceImage, referenceKeyPoints, referenceDescriptor);
		for(int i = 0; i<transformedImages.size(); i++)
			descriptorExtractor_brisk->compute(transformedImages[i], transformedKeyPoints[i], transformedDescriptors[i]);
		*/
		
		// 2�� ����
		SelfSimilarityTest(	referenceKeyPoints,
							transformedKeyPoints[i],
							referenceDescriptor,
							transformedDescriptors[i],
							matcher, matches_brisk,
							result);
		/*
		// 3�� ����
		SeperatibilityTest(	referenceKeyPoints,
							transformedKeyPoints[i],
							referenceDescriptor,
							transformedDescriptors[i],
							matcher, matches_brisk,
							result[i].data);
		*/					
	}

	// TODO: (����) ���� ����

	//return 0;

	getch();
}

