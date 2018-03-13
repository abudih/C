/*
 *Andrew Budihardja
 */

#include<stdio.h>

//24 bits per pixel, 8 bits per byte, 3 bytes per pixel

int main(){

	char bmpField[2],bmpField2[2];
	char rest_of_header_part1[12],rest_of_header_part2[28],
	rest_of_header2_part1[12],rest_of_header2_part2[28];

	int rawFileSize,rawFileSize2;
	int width,width2;
	int height,height2;
	int trueFileSize,trueFileSize2;


	FILE *infile = fopen("in1.bmp","rb");
	FILE *infile2 = fopen("MARBLES.bmp","rb");
	FILE *outfile = fopen("blend.bmp","wb");
	FILE *outfile2 = fopen("checker.bmp","wb");

	//read file 1
	fread(bmpField, sizeof(char), 2, infile);
	fread(&rawFileSize,sizeof(int),1,infile);

	fread(rest_of_header_part1,sizeof(char),12,infile);
	fread(&width,sizeof(int),1,infile);
	fread(&height,sizeof(int),1,infile);
	fread(rest_of_header_part2,sizeof(char),28,infile);

	trueFileSize=width*height*3;
	unsigned char firstImage[height][width*3];
	fread(firstImage,sizeof(char),trueFileSize,infile);

	printf("raw file size= %d\n",rawFileSize);
	printf("width= %d\n",width);
	printf("height= %d\n",height);
	printf("true file size= %d\n",trueFileSize);

	//read file 2
	fread(bmpField2, sizeof(char), 2, infile2);
	fread(&rawFileSize2,sizeof(int),1,infile2);

	fread(rest_of_header2_part1,sizeof(char),12,infile2);
	fread(&width2,sizeof(int),1,infile2);
	fread(&height2,sizeof(int),1,infile2);
	fread(rest_of_header2_part2,sizeof(char),28,infile2);

	trueFileSize2=width2*height2*3;
	unsigned char secondImage[height2][width2*3];
	fread(secondImage,sizeof(char),trueFileSize2,infile2);

	printf("\n");
	printf("raw file size2= %d\n",rawFileSize2);
	printf("width2= %d\n",width2);
	printf("height2= %d\n",height2);
	printf("true file size2= %d\n",trueFileSize2);

	//blend-assume the 2 images are the same size and dimensions
	unsigned char blend[height][width*3];

	for(int i=0;i<height;i++){
		for(int j=0;j<width*3;j++){

			int average = (firstImage[i][j]+secondImage[i][j])/2;

			blend[i][j]=average;
		}
	}
	//checker
	unsigned char checker[height][width*3];
	int width_per_square=(width*3)/8;
	int height_per_square=height/8;

	int temp=1;
	int counteri=1;
	int counterj=1;
	for(int i=0;i<height;i++){

		for(int j=0;j<width*3;j++){

			if(temp%2==0){
				if(counterj%width_per_square==0){
					for(int k=counterj;k<counteri+width_per_square+1;k++){
						checker[i][j]=firstImage[i][k];

					k++;
				}

			}else{
					checker[i][j]=secondImage[i][j];
			}
					counterj++;
			}else{

				if(counteri%width_per_square==0){
					for(int s=counteri;s<counteri+width_per_square+1;s++){
//										if(counteri>width*3){
//											break;
//										}
						checker[i][j]=secondImage[i][s];
						s++;
					}

				}else{
					checker[i][j]=firstImage[i][j];
				}
				counteri++;

				if(counterj%width_per_square==0){

					for(int k=counterj;k<counterj+width_per_square+1;k++){
						checker[i][j]=secondImage[i][k];
						printf("width=%d k=%d\n",width*3,k);
						j++;
					}
				}else{

					checker[i][j]=firstImage[i][j];
				}

				counterj++;
			}
//			counterj=counterj-counterj+1;
		}
		if(i%height_per_square-1==0&&i>1){
			printf("touch\n");
			temp=temp+1;
		}


//		if(i%height_per_square==0&&(i!=0)){
//			printf("%d ",i);
//			for(int k=counteri;k<counteri+height_per_square+1;k++){
//				checker[i][temp]=secondImage[k][temp];
//				printf("run ");
//			}
//			i=i+height_per_square;
//		}else{
//			printf("%d ",i);
//			checker[i][temp]=firstImage[i][temp];
//		}
//		printf("\n");
//		counteri++;
//
//		temp++;

	}

	//write the file
	fwrite(bmpField, sizeof(char), 2, outfile);
	fwrite(&rawFileSize, sizeof(int), 1, outfile);
	fwrite(rest_of_header_part1, sizeof(char), 12, outfile);
	fwrite(&width,sizeof(int),1,outfile);
	fwrite(&height,sizeof(int),1,outfile);
	fwrite(rest_of_header_part2,sizeof(char),28,outfile);
	fwrite(blend,sizeof(char),trueFileSize,outfile);

	fwrite(bmpField, sizeof(char), 2, outfile2);
	fwrite(&rawFileSize, sizeof(int), 1, outfile2);
	fwrite(rest_of_header_part1, sizeof(char), 12, outfile2);
	fwrite(&width,sizeof(int),1,outfile2);
	fwrite(&height,sizeof(int),1,outfile2);
	fwrite(rest_of_header_part2,sizeof(char),28,outfile2);
	fwrite(checker,sizeof(char),trueFileSize,outfile2);


	fclose(infile);
	fclose(outfile);
	return 0;

}
