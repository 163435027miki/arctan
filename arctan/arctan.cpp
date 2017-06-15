#include<fstream>
#include<iostream>
#include<string>
#include<sstream> //文字ストリーム
#include<math.h>
#include<time.h>//時間を用いる
#include <direct.h>//フォルダを作成す
#include<stdio.h>
#include <windows.h>

#define PI 3.14159265

using namespace std;



int main(){
//////////////////定義///////////////////////////////////////////////////////////////////////////////////////////
	double V0[255];
	double V90[255];


	char inputdate_directory[255];					//inputdateの場所
	

	char *Input_Filename1_s = "\\V(0).csv";			//入力ファイル名の指定
	char *Input_Filename3_s = "\\V(90).csv";

	
	char *math_name1_s = "arctan.csv";				//出力結果のファイル名の指定
	//char *math_name2_s = "V_sqrt.csv";
	//char *math_name3_s = "Cos_similarity.csv";
	//char *math_name4_s = "Angle.csv";
	char *math_name5_s = "threshold_high.csv";
	//char *math_name6_s = "use_Rvector_flag.csv";
	//char *math_name7_s = "use_Rvector_number.csv";
	char *math_name8_s = "threshold2.csv";
	char *math_name9_s = "threshold_low.csv";
	//char *math_name10_s = "newfunction.csv";						//出力増やす用1/7



	char Input_Filename1[255];						//入力ファイル名・入力元の設定
	char Input_Filename3[255];


													//出力ファイル名・出力先の設定
	char math_name1[64];							//内積						
	//char math_name2[64];							//応答電圧Vの大きさ
	//char math_name3[64];							//cos類似度
	//char math_name4[64];							//角度．最終結果
	char math_name5[64];							//threshold_high
	//char math_name6[64];							//use_Rvector_flag(応答電圧の最小の位置)
	//char math_name7[64];							//use_Rvector_number(内積でしようする基準ベクトルの番号）
	char math_name8[64];							//2つの閾値を一つに
	char math_name9[64];							//threshold(use_Rvector_flagの応答電圧Vの大きさ）
	//char math_name10[64];							//出力増やす用2/7
	
	

	int threshold_high_flag[255];
	int threshold_low_flag[255];
	double threshold_high;
	double threshold_low;
	double threshold_low_abs;
	double threshold_high_abs;
	double Angle[255];								//角度
	//double Angle_accuracy[255];
	

	FILE *fp_arctan,*fp_threshold_low,*fp_threshold_high,*fp_threshold2;;//,*fp_V_sqrt,*fp_Cos_similarity,*fp_Angle,*fp_Angle2,*fp_use_Rvector_flag,*fp_use_Rvector_number,

	//FILE *fp_newfunction;									//出力増やす用3

	int i=1,j=1;
	int count_property=0;
	int count_Allproperty=0;
/////////////////////////////////初期設定1 : input設定//////////////////////////////////////////////////////////////////

	int count_small=1,count_large=1;
	int image_width;						//入力画像の横幅
	int image_wide;							//入力画像の横幅+1
	int All_property[10];					//上記の情報を読み込む用



	std::ifstream propety_dire("..\\property\\simulation17-0615_circle-1\\property_100k.txt");		//ここだけ入力すればよい



	char propety[255];
	char Allpropety[255];
	char inputdate_directory1[255];
	char inputdate_directory2[255];
	char inputdate_directory3[255];
	char inputdate_directory4[255];
	char inputdate_directory5[255];
	char inputdate_directory6[255];			//繰返し数を増やしたい1/4

	//プロパティtxtファイルの読み込み
    if (propety_dire.fail())
    {
        printf("propertyテキストを読み取ることができません\n");
        return -1;
    }
    while (propety_dire.getline(propety, 256 - 1))
    {

		if(count_property==0)sprintf(Allpropety,propety);
		if(count_property==1)sprintf(inputdate_directory1,propety);
		if(count_property==2)sprintf(inputdate_directory2,propety);
		if(count_property==3)sprintf(inputdate_directory3,propety);
		if(count_property==4)sprintf(inputdate_directory4,propety);
		if(count_property==5)sprintf(inputdate_directory5,propety);
		if(count_property==6)sprintf(inputdate_directory6,propety);			//繰返し数を増やしたい2/4

		++count_property;
    }

	std::string tmp_Allpropety;
	std::istringstream stream_Allpropety(Allpropety);
	while(getline(stream_Allpropety,tmp_Allpropety,',')){

		int All_tmp_property=stof(tmp_Allpropety); //stof(string str) : stringをintに変換
		All_property[count_Allproperty]=All_tmp_property;

		if(count_Allproperty==0)image_width=All_property[count_Allproperty];
		//if(count_Allproperty==1)direction_number=All_property[count_Allproperty];
		

		++count_Allproperty;
	}

	image_wide=image_width+1;				//入力画像の横幅+1
	for(int repeat=0;repeat<6;++repeat){

	

	printf("repeat = %d\n",repeat);
	

	
	//繰返し指定例（15°おき）
	/*char kaku[128]={0};
	kakudo=repeat*15;
	sprintf(kaku,"%d",kakudo);
	printf("kaku = %s\n",kaku);
	char inputdate_directory_folder[255];
	sprintf(inputdate_directory_folder,"..\\inputdate\\Simulation16-0704\\素カーネル-人工画像\\");
	strcpy(inputdate_directory, inputdate_directory_folder);
    strcat(inputdate_directory, kaku);
	*/

	if(repeat==0)sprintf(inputdate_directory,inputdate_directory1);	//inputする畳み込みデータのフォルダ指定
	if(repeat==1)sprintf(inputdate_directory,inputdate_directory2);	//inputする畳み込みデータのフォルダ指定
	if(repeat==2)sprintf(inputdate_directory,inputdate_directory3);	//inputする畳み込みデータのフォルダ指定
	if(repeat==3)sprintf(inputdate_directory,inputdate_directory4);	//inputする畳み込みデータのフォルダ指定
	if(repeat==4)sprintf(inputdate_directory,inputdate_directory5);	//inputする畳み込みデータのフォルダ指定
	if(repeat==5)sprintf(inputdate_directory,inputdate_directory6);	//inputする畳み込みデータのフォルダ指定

	//手動指定用
	/*
	if(repeat==0)sprintf(inputdate_directory,"..\\inputdate\\Simulation16-0906\\3×3sobel\\conv3_sobel_real3_sd0");	//inputする畳み込みデータのフォルダ指定
	if(repeat==1)sprintf(inputdate_directory,"..\\inputdate\\Simulation16-0906\\3×3sobel\\conv3_sobel_real3_sd10");	//inputする畳み込みデータのフォルダ指定
	if(repeat==2)sprintf(inputdate_directory,"..\\inputdate\\Simulation16-0906\\3×3sobel\\conv3_sobel_real3_sd20");	//inputする畳み込みデータのフォルダ指定
	if(repeat==3)sprintf(inputdate_directory,"..\\inputdate\\Simulation16-0906\\3×3sobel\\conv3_sobel_real3_sd30");	//inputする畳み込みデータのフォルダ指定
	if(repeat==4)sprintf(inputdate_directory,"..\\inputdate\\Simulation16-0906\\3×3sobel\\conv3_sobel_real3_sd40");	//inputする畳み込みデータのフォルダ指定
	if(repeat==5)sprintf(inputdate_directory,"..\\inputdate\\Simulation16-0906\\3×3sobel\\conv3_sobel_real3_sd50");	//inputする畳み込みデータのフォルダ指定
	*/
	//繰替えし指定例(自然画像)
	/*if(repeat==0){
		//sprintf(inputrvector_directory,"..\\Rvector\\15×15-1.5-255-0-abs");				//inputするRvectorフォルダ指定
		//sprintf(inputdate_directory,"..\\inputdate\\simulation16-0628\\1.5");		//inputする畳み込みデータのフォルダ指定
	}*/
	
	
	
/////////////////////////////////準備/////////////////////////////////////////////////////////////////////////////////////
	//実行日時の表示
	time_t now = time(NULL);
    struct tm *pnow = localtime(&now);
	char date[128]="";
	sprintf(date,"%2d/%2d/%2d - %d:%d:%d\n",pnow->tm_year+1900,pnow->tm_mon + 1,pnow->tm_mday,pnow->tm_hour,pnow->tm_min,pnow->tm_sec);
	printf(date);

	//結果を保存するフォルダの生成
	//フォルダ名は実行日時になる
	char date_directory[128];
	sprintf(date_directory,"..\\result_neko\\%2d-%02d%02d-%02d%02d%02d\\",pnow->tm_year+1900,pnow->tm_mon + 1,pnow->tm_mday,pnow->tm_hour,pnow->tm_min,pnow->tm_sec);
	 if(_mkdir(date_directory)==0){
        printf("フォルダ %s を作成しました\n",date_directory);
    }else{
        printf("フォルダ作成に失敗しました。\n");
    }

	
////////////////////////////入出力ディレクトリの作成(C式のため汚い)//////////////////////////////////////////////////////////////////////////////
	
	//Input
	strcpy(Input_Filename1, inputdate_directory);
    strcat(Input_Filename1, Input_Filename1_s);

	strcpy(Input_Filename3, inputdate_directory);
    strcat(Input_Filename3, Input_Filename3_s);
	

	//Output
	strcpy(math_name1, date_directory);
    strcat(math_name1, math_name1_s);
	/*strcpy(math_name2, date_directory);
    strcat(math_name2, math_name2_s);
	strcpy(math_name3, date_directory);
    strcat(math_name3, math_name3_s);
	strcpy(math_name4, date_directory);
    strcat(math_name4, math_name4_s);*/
	strcpy(math_name5, date_directory);
	strcat(math_name5, math_name5_s);
	//strcpy(math_name6, date_directory);
    //strcat(math_name6, math_name6_s);
	//strcpy(math_name7, date_directory);
    //strcat(math_name7, math_name7_s);
	strcpy(math_name8, date_directory);
    strcat(math_name8, math_name8_s);
	strcpy(math_name9, date_directory);
    strcat(math_name9, math_name9_s);

	//strcpy(math_name10, date_directory);					//出力増やす用4/7
    //strcat(math_name10, math_name10_s);

////////////////////////////ファイルの読み込み//////////////////////////////////////////////////////////////////////////////


	//Input
	ifstream V_0(Input_Filename1);
	ifstream V_90(Input_Filename3);
	

////////////////////////エラー出力/////////////////////////////////////////////////////////////////////////////////////////////

	if(!V_0){cout<<"入力エラー V(0).csvがありません";return 1;}
	if(!V_90){cout<<"入力エラー V(90).csvがありません";return 1;}

	
/////////////////////////出力ファイルを開く///////////////////////////////////////////////////////////////////////////////////
	if((fp_arctan=fopen(math_name1,"w"))==NULL){cout<<"入力エラー arctan.csvが開けません";exit(1);}
	/*if((fp_V_sqrt=fopen(math_name2,"w"))==NULL){cout<<"入力エラー V_sqrt.csvが開けません";exit(1);}
	if((fp_Cos_similarity=fopen(math_name3,"w"))==NULL){cout<<"入力エラー Cos_similarity.csvが開けません";exit(1);}
	if((fp_Angle=fopen(math_name4,"w"))==NULL){cout<<"入力エラー Angle.csvが開けません";exit(1);}*/
	if((fp_threshold_high=fopen(math_name5,"w"))==NULL){cout<<"入力エラー threshold_high.csvが開けません";exit(1);}
	//if((fp_use_Rvector_flag=fopen(math_name6,"w"))==NULL){cout<<"入力エラー use_Rvector_flag.csvが開けません";exit(1);}
	//if((fp_use_Rvector_number=fopen(math_name7,"w"))==NULL){cout<<"入力エラー use_Rvector_number.csvが開けません";exit(1);}
	if((fp_threshold2=fopen(math_name8,"w"))==NULL){cout<<"入力エラー threshold2.csvが開けません";exit(1);}
	if((fp_threshold_low=fopen(math_name9,"w"))==NULL){cout<<"入力エラー threshold.csvが開けません";exit(1);}
	//if((fp_newfanction=fopen(math_name10,"w"))==NULL){cout<<"入力エラー newfunction.csvが開けません";exit(1);}	//出力増やす用5/7


	


	


///////////////////////応答電圧のcsvの読み込み//////////////////////////////////////////////////////////////////////////////////////////
		i=1;
		string str_0,str_90;

		while(getline(V_0,str_0)){					//このループ内ですべてを行う
			count_small=1;count_large=1;			//初期化


///////////////いろいろ定義．ここでやらないといけない///////////////////////////////////////////////////////////////////////////
        string token_V_0;
        istringstream stream_V_0(str_0);
		
		getline(V_90,str_90);	string token_V_90;	istringstream stream_V_90(str_90);
	
		

//////////////////////////配列に代入//////////////////////////////////////////////////////////////////////////////////////////////////
        while(getline(stream_V_0,token_V_0,',')){	 			//一行読み取る．V0のみ，繰り返しの範囲指定に用いる

			double tmp_V_0=stof(token_V_0);//文字を数字に変換 こいつが悪者？
			V0[count_small]=tmp_V_0;				//配列に代入
			//V0[count_small]=V0[count_small];
			//printf("%lf",V0[count_small]);
       
			getline(stream_V_90,token_V_90,',');
			double tmp_V_90=stof(token_V_90);
			V90[count_small]=tmp_V_90;
			//V90[count_small]=V90[count_small];


////大小判定/////////////////////////////////////////////////////////////////////			
			if(V0[count_small]>=V90[count_small]){
				threshold_high_flag[count_small]=1;			//Vの大小比較
				threshold_low_flag[count_small]=3;
			}else{
				threshold_high_flag[count_small]=3;
				threshold_low_flag[count_small]=1;
				}

			count_small++;							//一行読みとったとき用のカウント

			


////////////////////break条件を記す//////////////////////////////////////////////////////////////////////////////////////////////////////////
			if(count_small==image_wide){
				count_large++;
				break;
				}
			}
////////////////////////////計算条件//////////////////////////////////////////////////////////////////////////////////////////////

			for(j=1;j<image_wide;++j){						//一行ずつ計算する
				if(V0[j]==0){Angle[j]=90;
				}else{
			Angle[j]=atan(V90[j]/V0[j])*180/PI;
				}
				double Angle_flag;
				Angle_flag=Angle[j];
				if(Angle_flag<0)Angle[j]=Angle[j]+360;
				
				if(V0[j]<0 && V90[j]>0)Angle[j]=Angle[j]-180;
				if(V0[j]<=0 && V90[j]<=0)Angle[j]=Angle[j]+180;

				if(V0[j]>0 && V90[j]<0){
					if(Angle[j]<20){
						if(Angle[j]<0)Angle[j]=Angle[j]*-1;
						Angle[j]=360-Angle[j];
					}
					
				}
				
				if(V0[j]>=0 && V90[j]>=0){
					if(Angle[j]>200){
						Angle[j]=360-Angle[j];
					}
					
				}
				
				if(Angle[j]<0)Angle[j]=Angle[j]+360;
				
/////////////////////////計算終わり/////////////////////////////////////////////////////////////////////////////////////////////

//////////////ファイルへの書き込み(一行ずつ書き込み）/////////////////////////////////////////////
			fprintf(fp_arctan,"%lf,",Angle[j]);
			if(j==image_width){fprintf(fp_arctan,"\n");}



			if(threshold_high_flag[j]==1){threshold_high=V0[j];fprintf(fp_threshold_high,"%lf,",threshold_high);}
			if(threshold_high_flag[j]==3){threshold_high=V90[j];fprintf(fp_threshold_high,"%lf,",threshold_high);}
			if(j==image_width){fprintf(fp_threshold_high,"\n");}

			if(threshold_low_flag[j]==1){threshold_low=V0[j];fprintf(fp_threshold_low,"%lf,",threshold_low);}
			if(threshold_low_flag[j]==3){threshold_low=V90[j];fprintf(fp_threshold_low,"%lf,",threshold_low);}
			if(j==image_width){fprintf(fp_threshold_low,"\n");}

			threshold_high_abs=threshold_high;
			threshold_low_abs=threshold_low;

			if(threshold_high<0){threshold_high_abs=threshold_high_abs*-1;}
			if(threshold_low<0){threshold_low_abs=threshold_low_abs*-1;}
			if(threshold_high_abs>threshold_low_abs){
				fprintf(fp_threshold2,"%lf,",threshold_high);
			}else{
				fprintf(fp_threshold2,"%lf,",threshold_low);
			}
			if(j==image_width){fprintf(fp_threshold2,"\n");}
							//if(V0[j]<0)Angle[j]=Angle[j]-180;

			

			//fprintf(fp_newfunction,"%lf,",);									//出力増やす用6/7
			//if(j==image_width){fprintf(fp_newfunction,"\n");}




///////////////////////////書き込み終わり/////////////////////////////////////////////////////////			
			
			}																//閉じ　計算条件付近 "for(j=1;j<image_wide;++j){"
		}																	//閉じ　応答電圧のcsvの読み取り付近　"while(getline(V_0,str_0)){"
	//ファイルを閉じる
	fclose(fp_arctan);
	/*fclose(fp_V_sqrt);
	fclose(fp_Cos_similarity);
	fclose(fp_Angle);*/
	fclose(fp_threshold_high);
	fclose(fp_threshold2);
	fclose(fp_threshold_low);
	//fclose(fp_newfunction);													//出力増やす用7/7 + log

////////////////////////logファイルの作成//////////////////////////////////////////////////////////////////////////
	FILE *fp_date;
	char filename_log[128];
	//sprintf(filename_log, "..\\log\\log-%2d-%02d%02d-%02d%02d%02d.txt",pnow->tm_year+1900,pnow->tm_mon + 1,pnow->tm_mday,pnow->tm_hour,pnow->tm_min,pnow->tm_sec);	//logファイル作成のディレクトリ指定
	sprintf(filename_log, "..\\result_neko\\%2d-%02d%02d-%02d%02d%02d\\log.txt",pnow->tm_year+1900,pnow->tm_mon + 1,pnow->tm_mday,pnow->tm_hour,pnow->tm_min,pnow->tm_sec);	//logファイル作成のディレクトリ指定
	if((fp_date=fopen(filename_log,"w"))==NULL){printf("logファイルが開けません");exit(1);}
	fprintf(fp_date,"Time       : %s",date);						//時間
	fprintf(fp_date,"使用データ : %s\n",inputdate_directory);		//使用した畳み込み済みデータ
	fprintf(fp_date,"保存先     : %s\n",date_directory);			//保存先
	fclose(fp_date);


	printf("使用データ : %s\n",inputdate_directory);				//使用した畳み込み済みデータ
	//printf("保存先     : %s\n",date_directory);						//保存先
	printf("logファイル %s を保存しました\n",filename_log);

	printf("%d回目処理完了\n",repeat);
	Sleep(1000);
	}																//閉じ"for(int repeat=0;repeat<6;++repeat)"
	
	return 0;
}
