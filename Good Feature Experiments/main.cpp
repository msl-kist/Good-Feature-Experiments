#include "data_structure.h"


int main()
{
	Mat	referenceImage;
	vector<Mat> transformedImages;

	vector<Mat> matrices;

	// 먼저 영상들을 로드한다.
	LoadImages(referenceImage, transformedImages, matrices);

	// Reference 영상을 처리하자
	//==============================================================


	for(int i=0; i<transformedImages.size();++i)
	{
		Mat &transformedImage = transformedImages[i];

		// 1번 실험
		CornernessTest(referenceImage, transformedImage,
						vector<KeyPoint> &referenceKeyPoints, vector<KeyPoint> &transformedKeyPoints,				// K and K'
			vector<struct Data> &result);
	}

	return 0;
}

