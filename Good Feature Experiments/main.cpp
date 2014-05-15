#include "data_structure.h"


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
		//--------------------------------------------------------------

		// 2�� ����
		SelfSimilarityTest(	referenceImage,
							transformedImage,
							referenceKeyPoints,
							transformedKeyPoints[i],
							referenceDescriptor,
							transformedDescriptors[i],
							result);

		// 3�� ����
		SeperatibilityTest(	referenceKeyPoints,
							transformedKeyPoints[i],
							referenceDescriptor,
							transformedDescriptors[i],
							result);
	}

	// TODO: (����) ���� ����

	return 0;
}

