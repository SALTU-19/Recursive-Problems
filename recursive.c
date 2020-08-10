#include<stdio.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>
#define CARD 52
#define CITYCOUNT 6
#define SIZE1 4
#define SIZE2 3
int numPathsHome(int street, int avenue){//Number of ways which we can use to go was found.
	if (street == 1){ 
        return 1; 
	}
	else if(avenue == 1){
		return 1;
	}
	else{
    	return numPathsHome(street - 1, avenue) + numPathsHome(street, avenue - 1);
    }
}
struct card { 
	const char *face; 
	const char *suit; 
};
void mix(int mixed[CARD]){//52 different random numbers were collected in an array.
	int i=0,j,flag=0,a;
	srand(time(NULL));
	while(i!=CARD){
		flag=0;
		a=rand()%51;
		for(j=0;j<10;j++){
			if(a == mixed[j]){
				flag = 1;
				break;
			}
		}
		if(flag == 1){
			continue;
		}
		else{
			mixed[i] = a;  
		}
		i++;
	}

}
void mixed_and_print(){//the cards were mixed and printed!
	int i=0,j,mixed[CARD];
	mix(mixed);
	struct card cards[CARD];
	char faces[4][10] = {"Hearts", "Diamonds", "Clubs", "Spades"};
	char suits[13][10] = {"Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King" };
	while(i!=CARD){
		for(j=0;j<4;j++){
			cards[i].face = faces[j];
			i++;
		}
	}
	i=0;
	while(i!=CARD){
		for(j=0;j<13;j++){
			cards[i].suit = suits[j];
			i++;
		}
	}
	for(i=0;i<CARD;i++){
		printf("%d. %s of %s\n",i+1,cards[mixed[i]].suit,cards[mixed[i]].face);
	}

}
struct Hospital
{
    char* name;
    char citiesServed[3];
};

int n=SIZE1;
int r;
int checkResult(char _cities[6], struct Hospital result[4]){
    int i=0,x=0,y=0,count=0;
    char tempCities[CITYCOUNT],correctResult[CITYCOUNT];
    strcpy(tempCities,_cities);
    while(i<CITYCOUNT){
        while(x<SIZE1){
            while(y<SIZE2){
                if(tempCities[i]==result[x].citiesServed[y]){
                    tempCities[i]='0';
                }
                y++;
            }
            y=0;
            x++;
        }
        x=0;
        i++;
    }
    i=0;
    while(i<CITYCOUNT){
        correctResult[i]='0';
        i++;
    }
    i=0;
    while(i<CITYCOUNT){
        if(tempCities[i]==correctResult[i]) count++;
        i++;
    }
    if(count==CITYCOUNT) return 1;
    else return -1;
}
int canOfferCovidCoverage(char _cities[6],char _locations[4][3], int _numHospitals,struct Hospital results[4]){
    int temp_n=n,temp_r=r,x=0,y=0,result=0;
    for (int i = n; i >= r; i --){
        while(y<SIZE2){
            results[r-1].citiesServed[y]=_locations[i-1][y];
            y++;
        }
        x=0;y=0;
        if(r > 1){
            n=i-1;
            r--;
            result=canOfferCovidCoverage(_cities, _locations, _numHospitals, results);//recursive function
            if (result==1) return result;
            n=temp_n;
            r=temp_r;
        }
        else{
            result=checkResult(_cities,results);//checks whether the combination is correct.
            if(result==1){
                printf("\nYes, can offer health care to all!\n\n");
                for (int i = 0; i < _numHospitals; i ++) {
                    printf("Hospital - %d\n",i+1);
                    printf("Hospital locations: ");
                    while(y<SIZE2){
                        printf("%c",results[i].citiesServed[y]);
                        y++;
                    }
                    printf("\n");
                    y=0;
                }
                printf("\n");
                return 1;
            }
        }
    }
    n=temp_n;
    r=temp_r;
    return result;
}
void COVID_19_Health_Coverage(){
	char cities[6] = {'A','B','C','D','E','F'};
    char locations[4][3] = {{'A','B','C'},{'A','C','D'},{'B','F'},{'C','E','F'}};
    struct Hospital results[4];
    int _numHospitals,result;
    printf("Enter the maximum number of hospitals that can be constructed:");
    scanf("%d",&_numHospitals);
    r=_numHospitals;
    result=canOfferCovidCoverage(cities, locations,_numHospitals, results);
    if(result!=1) printf("No, some cities are not covered.\n");

}
int main(){
	int x,y,result,selection;
	printf("\n1.Stay Home Problem\n2.COVID-19 Health Coverage\n3.Mix cards\n4.Exit\n");
	printf("Please select an option:");
	scanf("%d",&selection);
	printf("\n");
	switch(selection){
		case 1:
			printf("Enter the street number: ");
			scanf("%d",&x);
			printf("Enter the avenue number: ");
			scanf("%d",&y);
			result = numPathsHome(x,y);
			printf("Number of optimal paths to take back home: %d\n",result);
			break;
		case 2:
			COVID_19_Health_Coverage();
			break;
		case 3:
			mixed_and_print();
			break;
		case 4:
			printf("Quitting...\n");
			break;
		default:
			printf("Invalid value!\n");
			break;

	}
	return 0;
}