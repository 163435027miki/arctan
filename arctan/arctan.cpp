#include<fstream>
#include<iostream>
#include<string>
#include<sstream> //�����X�g���[��
#include<math.h>
#include<time.h>//���Ԃ�p����
#include <direct.h>//�t�H���_���쐬��
#include<stdio.h>
#include <windows.h>

#define PI 3.14159265

using namespace std;



int main(){
//////////////////��`///////////////////////////////////////////////////////////////////////////////////////////
	double V0[255];
	double V90[255];


	char inputdate_directory[255];					//inputdate�̏ꏊ
	

	char *Input_Filename1_s = "\\V(0).csv";			//���̓t�@�C�����̎w��
	char *Input_Filename3_s = "\\V(90).csv";

	
	char *math_name1_s = "arctan.csv";				//�o�͌��ʂ̃t�@�C�����̎w��
	//char *math_name2_s = "V_sqrt.csv";
	//char *math_name3_s = "Cos_similarity.csv";
	//char *math_name4_s = "Angle.csv";
	char *math_name5_s = "threshold_high.csv";
	//char *math_name6_s = "use_Rvector_flag.csv";
	//char *math_name7_s = "use_Rvector_number.csv";
	char *math_name8_s = "threshold2.csv";
	char *math_name9_s = "threshold_low.csv";
	//char *math_name10_s = "newfunction.csv";						//�o�͑��₷�p1/7



	char Input_Filename1[255];						//���̓t�@�C�����E���͌��̐ݒ�
	char Input_Filename3[255];


													//�o�̓t�@�C�����E�o�͐�̐ݒ�
	char math_name1[64];							//����						
	//char math_name2[64];							//�����d��V�̑傫��
	//char math_name3[64];							//cos�ގ��x
	//char math_name4[64];							//�p�x�D�ŏI����
	char math_name5[64];							//threshold_high
	//char math_name6[64];							//use_Rvector_flag(�����d���̍ŏ��̈ʒu)
	//char math_name7[64];							//use_Rvector_number(���ςł��悤�����x�N�g���̔ԍ��j
	char math_name8[64];							//2��臒l�����
	char math_name9[64];							//threshold(use_Rvector_flag�̉����d��V�̑傫���j
	//char math_name10[64];							//�o�͑��₷�p2/7
	
	

	int threshold_high_flag[255];
	int threshold_low_flag[255];
	double threshold_high;
	double threshold_low;
	double threshold_low_abs;
	double threshold_high_abs;
	double Angle[255];								//�p�x
	//double Angle_accuracy[255];
	

	FILE *fp_arctan,*fp_threshold_low,*fp_threshold_high,*fp_threshold2;;//,*fp_V_sqrt,*fp_Cos_similarity,*fp_Angle,*fp_Angle2,*fp_use_Rvector_flag,*fp_use_Rvector_number,

	//FILE *fp_newfunction;									//�o�͑��₷�p3

	int i=1,j=1;
	int count_property=0;
	int count_Allproperty=0;
/////////////////////////////////�����ݒ�1 : input�ݒ�//////////////////////////////////////////////////////////////////

	int count_small=1,count_large=1;
	int image_width;						//���͉摜�̉���
	int image_wide;							//���͉摜�̉���+1
	int All_property[10];					//��L�̏���ǂݍ��ޗp



	std::ifstream propety_dire("..\\property\\simulation17-0615_circle-1\\property_100k.txt");		//�����������͂���΂悢



	char propety[255];
	char Allpropety[255];
	char inputdate_directory1[255];
	char inputdate_directory2[255];
	char inputdate_directory3[255];
	char inputdate_directory4[255];
	char inputdate_directory5[255];
	char inputdate_directory6[255];			//�J�Ԃ����𑝂₵����1/4

	//�v���p�e�Btxt�t�@�C���̓ǂݍ���
    if (propety_dire.fail())
    {
        printf("property�e�L�X�g��ǂݎ�邱�Ƃ��ł��܂���\n");
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
		if(count_property==6)sprintf(inputdate_directory6,propety);			//�J�Ԃ����𑝂₵����2/4

		++count_property;
    }

	std::string tmp_Allpropety;
	std::istringstream stream_Allpropety(Allpropety);
	while(getline(stream_Allpropety,tmp_Allpropety,',')){

		int All_tmp_property=stof(tmp_Allpropety); //stof(string str) : string��int�ɕϊ�
		All_property[count_Allproperty]=All_tmp_property;

		if(count_Allproperty==0)image_width=All_property[count_Allproperty];
		//if(count_Allproperty==1)direction_number=All_property[count_Allproperty];
		

		++count_Allproperty;
	}

	image_wide=image_width+1;				//���͉摜�̉���+1
	for(int repeat=0;repeat<6;++repeat){

	

	printf("repeat = %d\n",repeat);
	

	
	//�J�Ԃ��w���i15�������j
	/*char kaku[128]={0};
	kakudo=repeat*15;
	sprintf(kaku,"%d",kakudo);
	printf("kaku = %s\n",kaku);
	char inputdate_directory_folder[255];
	sprintf(inputdate_directory_folder,"..\\inputdate\\Simulation16-0704\\�f�J�[�l��-�l�H�摜\\");
	strcpy(inputdate_directory, inputdate_directory_folder);
    strcat(inputdate_directory, kaku);
	*/

	if(repeat==0)sprintf(inputdate_directory,inputdate_directory1);	//input�����ݍ��݃f�[�^�̃t�H���_�w��
	if(repeat==1)sprintf(inputdate_directory,inputdate_directory2);	//input�����ݍ��݃f�[�^�̃t�H���_�w��
	if(repeat==2)sprintf(inputdate_directory,inputdate_directory3);	//input�����ݍ��݃f�[�^�̃t�H���_�w��
	if(repeat==3)sprintf(inputdate_directory,inputdate_directory4);	//input�����ݍ��݃f�[�^�̃t�H���_�w��
	if(repeat==4)sprintf(inputdate_directory,inputdate_directory5);	//input�����ݍ��݃f�[�^�̃t�H���_�w��
	if(repeat==5)sprintf(inputdate_directory,inputdate_directory6);	//input�����ݍ��݃f�[�^�̃t�H���_�w��

	//�蓮�w��p
	/*
	if(repeat==0)sprintf(inputdate_directory,"..\\inputdate\\Simulation16-0906\\3�~3sobel\\conv3_sobel_real3_sd0");	//input�����ݍ��݃f�[�^�̃t�H���_�w��
	if(repeat==1)sprintf(inputdate_directory,"..\\inputdate\\Simulation16-0906\\3�~3sobel\\conv3_sobel_real3_sd10");	//input�����ݍ��݃f�[�^�̃t�H���_�w��
	if(repeat==2)sprintf(inputdate_directory,"..\\inputdate\\Simulation16-0906\\3�~3sobel\\conv3_sobel_real3_sd20");	//input�����ݍ��݃f�[�^�̃t�H���_�w��
	if(repeat==3)sprintf(inputdate_directory,"..\\inputdate\\Simulation16-0906\\3�~3sobel\\conv3_sobel_real3_sd30");	//input�����ݍ��݃f�[�^�̃t�H���_�w��
	if(repeat==4)sprintf(inputdate_directory,"..\\inputdate\\Simulation16-0906\\3�~3sobel\\conv3_sobel_real3_sd40");	//input�����ݍ��݃f�[�^�̃t�H���_�w��
	if(repeat==5)sprintf(inputdate_directory,"..\\inputdate\\Simulation16-0906\\3�~3sobel\\conv3_sobel_real3_sd50");	//input�����ݍ��݃f�[�^�̃t�H���_�w��
	*/
	//�J�ւ����w���(���R�摜)
	/*if(repeat==0){
		//sprintf(inputrvector_directory,"..\\Rvector\\15�~15-1.5-255-0-abs");				//input����Rvector�t�H���_�w��
		//sprintf(inputdate_directory,"..\\inputdate\\simulation16-0628\\1.5");		//input�����ݍ��݃f�[�^�̃t�H���_�w��
	}*/
	
	
	
/////////////////////////////////����/////////////////////////////////////////////////////////////////////////////////////
	//���s�����̕\��
	time_t now = time(NULL);
    struct tm *pnow = localtime(&now);
	char date[128]="";
	sprintf(date,"%2d/%2d/%2d - %d:%d:%d\n",pnow->tm_year+1900,pnow->tm_mon + 1,pnow->tm_mday,pnow->tm_hour,pnow->tm_min,pnow->tm_sec);
	printf(date);

	//���ʂ�ۑ�����t�H���_�̐���
	//�t�H���_���͎��s�����ɂȂ�
	char date_directory[128];
	sprintf(date_directory,"..\\result_neko\\%2d-%02d%02d-%02d%02d%02d\\",pnow->tm_year+1900,pnow->tm_mon + 1,pnow->tm_mday,pnow->tm_hour,pnow->tm_min,pnow->tm_sec);
	 if(_mkdir(date_directory)==0){
        printf("�t�H���_ %s ���쐬���܂���\n",date_directory);
    }else{
        printf("�t�H���_�쐬�Ɏ��s���܂����B\n");
    }

	
////////////////////////////���o�̓f�B���N�g���̍쐬(C���̂��߉���)//////////////////////////////////////////////////////////////////////////////
	
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

	//strcpy(math_name10, date_directory);					//�o�͑��₷�p4/7
    //strcat(math_name10, math_name10_s);

////////////////////////////�t�@�C���̓ǂݍ���//////////////////////////////////////////////////////////////////////////////


	//Input
	ifstream V_0(Input_Filename1);
	ifstream V_90(Input_Filename3);
	

////////////////////////�G���[�o��/////////////////////////////////////////////////////////////////////////////////////////////

	if(!V_0){cout<<"���̓G���[ V(0).csv������܂���";return 1;}
	if(!V_90){cout<<"���̓G���[ V(90).csv������܂���";return 1;}

	
/////////////////////////�o�̓t�@�C�����J��///////////////////////////////////////////////////////////////////////////////////
	if((fp_arctan=fopen(math_name1,"w"))==NULL){cout<<"���̓G���[ arctan.csv���J���܂���";exit(1);}
	/*if((fp_V_sqrt=fopen(math_name2,"w"))==NULL){cout<<"���̓G���[ V_sqrt.csv���J���܂���";exit(1);}
	if((fp_Cos_similarity=fopen(math_name3,"w"))==NULL){cout<<"���̓G���[ Cos_similarity.csv���J���܂���";exit(1);}
	if((fp_Angle=fopen(math_name4,"w"))==NULL){cout<<"���̓G���[ Angle.csv���J���܂���";exit(1);}*/
	if((fp_threshold_high=fopen(math_name5,"w"))==NULL){cout<<"���̓G���[ threshold_high.csv���J���܂���";exit(1);}
	//if((fp_use_Rvector_flag=fopen(math_name6,"w"))==NULL){cout<<"���̓G���[ use_Rvector_flag.csv���J���܂���";exit(1);}
	//if((fp_use_Rvector_number=fopen(math_name7,"w"))==NULL){cout<<"���̓G���[ use_Rvector_number.csv���J���܂���";exit(1);}
	if((fp_threshold2=fopen(math_name8,"w"))==NULL){cout<<"���̓G���[ threshold2.csv���J���܂���";exit(1);}
	if((fp_threshold_low=fopen(math_name9,"w"))==NULL){cout<<"���̓G���[ threshold.csv���J���܂���";exit(1);}
	//if((fp_newfanction=fopen(math_name10,"w"))==NULL){cout<<"���̓G���[ newfunction.csv���J���܂���";exit(1);}	//�o�͑��₷�p5/7


	


	


///////////////////////�����d����csv�̓ǂݍ���//////////////////////////////////////////////////////////////////////////////////////////
		i=1;
		string str_0,str_90;

		while(getline(V_0,str_0)){					//���̃��[�v���ł��ׂĂ��s��
			count_small=1;count_large=1;			//������


///////////////���낢���`�D�����ł��Ȃ��Ƃ����Ȃ�///////////////////////////////////////////////////////////////////////////
        string token_V_0;
        istringstream stream_V_0(str_0);
		
		getline(V_90,str_90);	string token_V_90;	istringstream stream_V_90(str_90);
	
		

//////////////////////////�z��ɑ��//////////////////////////////////////////////////////////////////////////////////////////////////
        while(getline(stream_V_0,token_V_0,',')){	 			//��s�ǂݎ��DV0�̂݁C�J��Ԃ��͈͎̔w��ɗp����

			double tmp_V_0=stof(token_V_0);//�����𐔎��ɕϊ� ���������ҁH
			V0[count_small]=tmp_V_0;				//�z��ɑ��
			//V0[count_small]=V0[count_small];
			//printf("%lf",V0[count_small]);
       
			getline(stream_V_90,token_V_90,',');
			double tmp_V_90=stof(token_V_90);
			V90[count_small]=tmp_V_90;
			//V90[count_small]=V90[count_small];


////�召����/////////////////////////////////////////////////////////////////////			
			if(V0[count_small]>=V90[count_small]){
				threshold_high_flag[count_small]=1;			//V�̑召��r
				threshold_low_flag[count_small]=3;
			}else{
				threshold_high_flag[count_small]=3;
				threshold_low_flag[count_small]=1;
				}

			count_small++;							//��s�ǂ݂Ƃ����Ƃ��p�̃J�E���g

			


////////////////////break�������L��//////////////////////////////////////////////////////////////////////////////////////////////////////////
			if(count_small==image_wide){
				count_large++;
				break;
				}
			}
////////////////////////////�v�Z����//////////////////////////////////////////////////////////////////////////////////////////////

			for(j=1;j<image_wide;++j){						//��s���v�Z����
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
				
/////////////////////////�v�Z�I���/////////////////////////////////////////////////////////////////////////////////////////////

//////////////�t�@�C���ւ̏�������(��s���������݁j/////////////////////////////////////////////
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

			

			//fprintf(fp_newfunction,"%lf,",);									//�o�͑��₷�p6/7
			//if(j==image_width){fprintf(fp_newfunction,"\n");}




///////////////////////////�������ݏI���/////////////////////////////////////////////////////////			
			
			}																//���@�v�Z�����t�� "for(j=1;j<image_wide;++j){"
		}																	//���@�����d����csv�̓ǂݎ��t�߁@"while(getline(V_0,str_0)){"
	//�t�@�C�������
	fclose(fp_arctan);
	/*fclose(fp_V_sqrt);
	fclose(fp_Cos_similarity);
	fclose(fp_Angle);*/
	fclose(fp_threshold_high);
	fclose(fp_threshold2);
	fclose(fp_threshold_low);
	//fclose(fp_newfunction);													//�o�͑��₷�p7/7 + log

////////////////////////log�t�@�C���̍쐬//////////////////////////////////////////////////////////////////////////
	FILE *fp_date;
	char filename_log[128];
	//sprintf(filename_log, "..\\log\\log-%2d-%02d%02d-%02d%02d%02d.txt",pnow->tm_year+1900,pnow->tm_mon + 1,pnow->tm_mday,pnow->tm_hour,pnow->tm_min,pnow->tm_sec);	//log�t�@�C���쐬�̃f�B���N�g���w��
	sprintf(filename_log, "..\\result_neko\\%2d-%02d%02d-%02d%02d%02d\\log.txt",pnow->tm_year+1900,pnow->tm_mon + 1,pnow->tm_mday,pnow->tm_hour,pnow->tm_min,pnow->tm_sec);	//log�t�@�C���쐬�̃f�B���N�g���w��
	if((fp_date=fopen(filename_log,"w"))==NULL){printf("log�t�@�C�����J���܂���");exit(1);}
	fprintf(fp_date,"Time       : %s",date);						//����
	fprintf(fp_date,"�g�p�f�[�^ : %s\n",inputdate_directory);		//�g�p������ݍ��ݍς݃f�[�^
	fprintf(fp_date,"�ۑ���     : %s\n",date_directory);			//�ۑ���
	fclose(fp_date);


	printf("�g�p�f�[�^ : %s\n",inputdate_directory);				//�g�p������ݍ��ݍς݃f�[�^
	//printf("�ۑ���     : %s\n",date_directory);						//�ۑ���
	printf("log�t�@�C�� %s ��ۑ����܂���\n",filename_log);

	printf("%d��ڏ�������\n",repeat);
	Sleep(1000);
	}																//��"for(int repeat=0;repeat<6;++repeat)"
	
	return 0;
}
