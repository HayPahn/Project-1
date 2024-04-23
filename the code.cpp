#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>   


typedef struct{
	int point;
}Point;

void SD(FILE* f, Point &a){
	f=fopen("Save","wb");
	fwrite(&a,sizeof(Point),1,f);
	fclose(f);
}

void UD(FILE* f, Point &a){
	f=fopen("Save","rb");
	fread(&a,sizeof(Point),1,f);
	fclose(f);
}

void Ch(int &pp, char option, int a[], int b[], int &flag1, int &boss, Point &d){
	if(option=='w') pp-=28; if(option=='s') pp+=28;
	if(option=='a') pp-=1; if(option=='d') pp+=1;
	for(int i=0; i<7; i++){
		if(a[i]==pp){
			if((d.point-1)>=0){
				a[i]=9999; d.point+=5; break;
			}else{
				flag1+=1;
			}
		}
	}
	for(int i=0; i<4; i++){
		if(b[i]==pp){
			if((d.point-10)>=0){
				b[i]=9999; d.point+=10; break;
			}else{
				flag1+=1;
			}
		}
	}
	if(pp==504){
		if(d.point-100>=0){
			boss=999; flag1+=2;
		}else{
			flag1+=1;
		}
	}
	FILE* f;
	SD(f,d);
}

void MapGen(char map[20][30], int a[], int b[], int boss, int pp){
	int flag=0, flag2=0;
	for(int r=0; r<20; r++){
		for(int c=0; c<30; c++){
			if(r==0) printf("#"); if(r>0 && r<19 && c==0) printf("#");
			if(r>0 && r<19 && c==29) printf("#"); if(r==19) printf("#");
			if(r>=1 && r<=18 && c>=1 && c<=28){
				flag2=0;
				if(((r-1)*28)+c==pp){
					printf("A"); flag2++;
				}
				for(int i=0; i<7; i++){
					if(((r-1)*28)+c==a[i]){
						printf("o"); flag2++; break;
					}
				}
				for(int i=0; i<4; i++){
					if(((r-1)*28)+c==b[i]){
						printf("0"); flag2++; break;
					}
				}
				if(((r-1)*28)+c==boss){
					printf("X"); flag2++;
				}
				if(flag2<1) printf(" ");
			}
			flag++;
			if(flag==30){
				printf("\n"); flag=0;
			}
		}
	}
}

int main(){
	char map[20][30], option;
	int flag=0, flag1=0;
	int a[7], b[4], pp=477, boss=504, temp, count1=0;
	Point d; d.point=1;
	FILE* f;
	UD(f,d);
	for(int i=0; i<7; i++){
	    a[i]=rand()%(17*28);
    }
	for(int i=0; i<4;){
		temp=rand()%(17*28);
		count1=0;
		for(int j=0; j<7; j++){
			if(temp==a[j]){
				break;
			}else{
				count1++;
			}
		}
		if(count1==7){
			b[i]=temp; i++;
		}
	}
	while(flag1<1){
		MapGen(map,a,b,boss,pp);
		printf("How to play:You are A. You can move by typing a sequence of words(Ex:dwasdwasdwada). When you move past an enemy, if you-r point is equal or higher than them, they will be consumed and you will get additional points, else you will die. Beat the boss(X) to win the game");
		printf("\n\nPoints of A:%d \\ Points of o:1 \\ Points of 0:10 \\ Points of X:100",d.point);
		printf("\nOptions: ");
		printf("\n1.Quit(q) 2.Move:Up(w) Down(s) Left(a) Right(d) 3.Generate new enemies(g)");
		printf("\nChoose:"); scanf("%c",&option);
		switch(option){
			case 'q':
				flag1++;
				system("cls");
				break;
			case 'g':
				for(int i=0; i<7; i++){
					a[i]=rand()%(17*28);
				}
				for(int i=0; i<4;){
					temp=rand()%(17*28);
					count1=0;
	                for(int j=0; j<7; j++){
	                	if(temp==a[j]){
	                        break;
			            }else{
				            count1++;
			            }
					}
					if(count1==7){
		                b[i]=temp; i++;
	 	            }
				}
				MapGen(map,a,b,boss,pp);
				break;
			case 'w':
				system("cls");
				Ch(pp,option,a,b,flag1,boss,d);
				MapGen(map,a,b,boss,pp);
				break;
			case 's':
				system("cls");
				Ch(pp,option,a,b,flag1,boss,d);
				MapGen(map,a,b,boss,pp);
				break;
			case 'a':
				system("cls");
				Ch(pp,option,a,b,flag1,boss,d);
				MapGen(map,a,b,boss,pp);
				break;
			case 'd':
				system("cls");
				Ch(pp,option,a,b,flag1,boss,d);
				MapGen(map,a,b,boss,pp);
				break;
				
		}
		system("cls");
	}
	if(flag1==1){
		printf("Sorry, you lost");
		Point g; g.point=1;
		SD(f,g);
		getch();	
	}
	if(flag1==2){
		printf("\nCongrats, you won");
		getch();
	}
	return 0;
}
