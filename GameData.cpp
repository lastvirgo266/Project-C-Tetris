#include"common.h"

int GameDataLoad(){
	int bestScore;
	FILE *fp;
	fp = fopen("Gamedata.dat", "rb");

	if (fp == NULL)
		return 0;

	fread(&bestScore, sizeof(int), 1, fp);

	fclose(fp);

	return bestScore;

}


void GameDataSave(int score){
	FILE *fp;
	fp = fopen("Gamedata.dat", "wb");
	fwrite(&score, sizeof(int), 1, fp);
	fclose(fp);

}