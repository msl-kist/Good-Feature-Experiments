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

	// ���� ������� �ε��Ѵ�.
	LoadImages(referenceImage, transformedImages, matrices);

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

	for(int i=0; i<transformedImages.size();++i)
	{
		Mat &transformedImage = transformedImages[i];

		// 1�� ����
		CornernessTest(	referenceImage, 
						transformedImage,
						referenceKeyPoints, 
						transformedKeyPoints[i],				// K and K'
						matrices[i], 
						result);

		// TODO: (����) ��ȯ �̹����� ���� ��ũ���� ����
		descriptorExtractor_brisk->compute(referenceImage, referenceKeyPoints, referenceDescriptor);
		for(int i = 0; i<transformedImages.size(); i++)
			descriptorExtractor_brisk->compute(transformedImages[i], transformedKeyPoints[i], transformedDescriptors[i]);

		// 2�� ����
		SelfSimilarityTest(	referenceKeyPoints,
							transformedKeyPoints[i],
							referenceDescriptor,
							transformedDescriptors[i],
							matcher, matches_brisk,
							result);

		// 3�� ����
		SeperatibilityTest(	referenceKeyPoints,
							transformedKeyPoints[i],
							referenceDescriptor,
							transformedDescriptors[i],
							matcher, matches_brisk,
							result);
	}

	// TODO: (����) ���� ����

	return 0;
}

