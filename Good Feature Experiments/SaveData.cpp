#include "data_structure.h"

void SaveData(vector<struct Data>& result)
{
	FILE *file1;
	FILE *file2;
	FILE *file3;
	FILE *file4;
	FILE *file5;
	FILE *file6;
	FILE *file7;

	file1 = fopen("result.txt","w");
	file2 = fopen("1.txt","w");
	file4 = fopen("response.txt","w");
	file5 = fopen("4.txt","w");
	file3 = fopen("2_min.txt","w");
	file6 = fopen("2_max.txt","w");
	file7 = fopen("2.txt","w");

	for(int i = 0 ; i < result.size(); i++){
		float min = 10000;
		float max = 0;
	
		if(result[i].selfSimilarity.size()>0){
			for(int j = 0 ; j < result[i].selfSimilarity.size(); j++)
			{
				if(min > result[i].selfSimilarity[j]){
					min = result[i].selfSimilarity[j];
				}
				if(max < result[i].selfSimilarity[j]){
					max = result[i].selfSimilarity[j];
				}
			}
		}
		else
		{
			min = -1;
			max = -1;
		}

		fprintf(file2,"%d\n",result[i].cornerness);

		fprintf(file3,"%f\n",min);
		fprintf(file6,"%f\n",max);
		if(result[i].selfSimilarity.size()>0){
			for(int j = 0 ; j < result[i].selfSimilarity.size(); j++)
			{
				fprintf(file7,"%f ",result[i].selfSimilarity[j]);
			}

			fprintf(file7,"\n");
		}else
			fprintf(file7,"%f\n",0);
		fprintf(file4,"%f\n",result[i].keypoint.response);
		fprintf(file5,"%d\n",result[i].matchScore);
		//fprintf(file6,"%d %f\n",result[i].matchScore,max);


		fprintf(file1,"keypoint:%d\n", i);
		//1번 실험 출력
		fprintf(file1,"%d\n", result[i].cornerness);
		
		//3번 출력
		map<int, int>::iterator Iter_Pos;
		for( Iter_Pos = result[i].seperatibility.begin(); Iter_Pos != result[i].seperatibility.end(); ++Iter_Pos)
		{
		//cout << Iter_Pos.second << endl;
			fprintf(file1,"%d %d\n", Iter_Pos->first, Iter_Pos->second);
		}
	}

	fclose(file1);
	fclose(file2);
	fclose(file3);
	fclose(file4);
	fclose(file5);
	fclose(file6);
	fclose(file7);
}