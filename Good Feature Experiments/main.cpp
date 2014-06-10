#include <conio.h>

#include "data_structure.h"

#include "brisk/brisk.h"
#include "brisk/Matcher.h"
#include "brisk/MatchVerifier.hpp"
#include "brisk/GroundTruth.hpp"

using namespace cv;

//#define DATASAVE
//#define CALCMEAN
#define TEST

float calcMeanValue(struct Data result){
	long double sum=0;
	int cnt=0;
	map<int, int>::iterator Iter_Pos;
	for( Iter_Pos = result.seperatibility.begin(); Iter_Pos != result.seperatibility.end(); ++Iter_Pos)
	{
		sum += (Iter_Pos->second * Iter_Pos->first);
		cnt += Iter_Pos->second;
	}

	return sum/ cnt;
}

float calcVarianceValue(struct Data result, float mean){
	float sum=0;
	int cnt=0;
	map<int, int>::iterator Iter_Pos;
	for( Iter_Pos = result.seperatibility.begin(); Iter_Pos != result.seperatibility.end(); ++Iter_Pos)
	{
		sum += (pow(Iter_Pos->first - mean,2) * Iter_Pos->second);
		cnt += Iter_Pos->second;
	}
	return sum/ cnt;
}

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


	vector<vector<KeyPoint>> changedKeypoint;
	vector<Mat>	changedDescriptor;

	// 결과 저장 자료형
	vector<struct Data> result;
	vector<struct ImageData> imageData;


#ifdef DATASAVE
	char name[100];

	// 먼저 영상들을 로드한다.
	LoadData(referenceKeyPoints, transformedKeyPoints, referenceDescriptor, transformedDescriptors, result, imageData);
	LoadImage(1,width,height);

	for(int i=0; i<imageData.size();++i)
	{
		vector<KeyPoint> tempKeypoint;
		Mat	tempDescriptor;

		// 1번 실험
		CornernessTest(	referenceKeyPoints, 
			referenceDescriptor,
			transformedKeyPoints[i],				// K and K'
			transformedDescriptors[i],
			imageData[i],result, tempKeypoint,
			tempDescriptor,width,height);



		// 2번 실험
		SelfSimilarityTest(	referenceKeyPoints,
			tempKeypoint,
			referenceDescriptor,
			tempDescriptor,
			matcher, matches_brisk,
			result);

		// 3번 실험
		SeperatibilityTest(	referenceKeyPoints,
			tempKeypoint,
			referenceDescriptor,
			tempDescriptor,
			matcher, matches_brisk,
			result);

		// 4번 실험
		MatchingCountTest(referenceKeyPoints, 
			referenceDescriptor, 
			transformedKeyPoints[i],
			transformedDescriptors[i],
			imageData[i],
			result,
			width,
			height);

	}

	SaveData(result);

	cout<<"END"<<endl;

#endif

#ifdef CALCMEAN
	//실험 데이터 Load
	ReadResultData(result,transformedKeyPoints, transformedDescriptors);

	FILE* meanFile;
	FILE* varianceFile;
	FILE* deviationFile;
	meanFile = fopen("mean.txt","w");
	varianceFile = fopen("variance.txt","w");
	deviationFile = fopen("deviation.txt","w");
	for(int i =0;i < result.size();i++){
		float mean = calcMeanValue(result[i]);
		float variance = calcVarianceValue(result[i],mean);

		fprintf(meanFile,"%f\n",mean);
		fprintf(varianceFile,"%f\n",variance);
		fprintf(deviationFile,"%f\n",sqrt(variance));
	}

	fclose(meanFile);
	fclose(varianceFile);
	fclose(deviationFile);

#endif

#ifdef TEST

#endif


	getch();
}

