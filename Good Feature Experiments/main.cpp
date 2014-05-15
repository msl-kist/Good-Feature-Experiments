#include "data_structure.h"


int main()
{
	Mat	referenceImage;
	vector<Mat> transformedImages;

	vector<Mat> matrices;

	// ���� ������� �ε��Ѵ�.
	LoadImages(referenceImage, transformedImages, matrices);

	// Reference ������ ó������
	//==============================================================


	for(int i=0; i<transformedImages.size();++i)
	{
		Mat &transformedImage = transformedImages[i];

		// 1�� ����
		CornernessTest(referenceImage, transformedImage,
						vector<KeyPoint> &referenceKeyPoints, vector<KeyPoint> &transformedKeyPoints,				// K and K'
			vector<struct Data> &result);
	}

	return 0;
}

