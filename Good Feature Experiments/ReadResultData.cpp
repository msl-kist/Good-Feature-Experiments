#include "data_structure.h"

void ReadResultData(vector<struct Data>& result,vector<vector<KeyPoint>> keypoint, vector<Mat>	descriptor){
	/*
	float maxScale = MAX_SCALE;
	int maxDBSize = MAX_DB_SIZE;
	int cnt=0;

	FileStorage fs("data/rotateInformation.xml",FileStorage::READ);

	for(int imageNum = 1 ; imageNum <= maxDBSize; imageNum++){
	for(float scale = MIN_SCALE; scale <= maxScale; scale += SCALE_INCREASE){			//scale 변화
	for(int angle = 0; angle < 360; angle += ANGLE_INCREASE){						//angle 변화
	for(int gaussian = 0; gaussian < 8; gaussian+=2){
	if(gaussian == 2)
	gaussian++;
	vector<KeyPoint> keypointTemp;
	Mat descriptorTemp;
	char name[100];
	sprintf(name, "K_%d_%d_%d_%d",imageNum,(int)(scale*10),angle,gaussian);
	FileNode features = fs[name];
	read(features, keypointTemp);
	sprintf(name, "D_%d_%d_%d_%d",imageNum,(int)(scale*10),angle,gaussian);
	fs[name] >> descriptorTemp;

	keypoint.push_back(keypointTemp);
	descriptor.push_back(descriptorTemp);
	cout<<cnt++<<endl;
	}
	}
	}
	}
	*/
	char name[100];

	FILE* file1;
	FILE* file2;
	FILE* file3;
	FILE* file4;

	//File open
	file1 = fopen("1_repeatability.txt","r");
	file2 = fopen("2.txt","r");
	file4 = fopen("4.txt","r");

	for(int i=0 ; i<1012; i++){
		struct Data tempData;
		fscanf(file1,"%d\n",&tempData.cornerness);
		fscanf(file4,"%d\n",&tempData.matchScore);

		float tempFloat;
		do 
		{
			fscanf(file2,"%f",&tempFloat);
			tempData.selfSimilarity.push_back(tempFloat);
		} while (fgetc(file2) != '\n');

		sprintf(name,"3_%d",i);
		file3 = fopen(name,"r");
		while(true){
			int a, b;
			fscanf(file3,"%d %d\n",&a,&b);

			tempData.seperatibility[a] = b;
			if(feof(file3)){
				break;
			}
		}

		result.push_back(tempData);
		fclose(file3);
		cout<<"read"<<i<<endl;
	}
	fclose(file1);
	fclose(file2);
	fclose(file4);

	cout<<"Finished reading data"<<endl;
}