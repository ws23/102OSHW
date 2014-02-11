#include <stdio.h>
#include <time.h>
#define ID 410121021

int main(){
	long long distance = (long long)ID * 100;
	long long count = 0;

	srand(time(NULL));
	while(distance>0){
		distance -= rand()%101;
		count++;
	}
	printf("%lld\n", count);
	return 0;
}
