#include <stdlib.h>
#include <stdio.h>

struct _retire_info{
    int months;
    double contribution;
    double rate_of_return;
    };
typedef struct _retire_info retire_info;

double balance(double current_balance,double rate,double contribution){
    double balance;
    balance = current_balance+current_balance*rate+contribution;
    return balance;
    }

void retirement (int startAge, double initial, retire_info working, retire_info retired){
    double cur_balance = initial;
    int cur_age=startAge;
    for(int i=0;i<working.months;i++){
         printf("Age %3d month %2d you have $%.2lf\n",cur_age/12,cur_age%12,cur_balance);
	 cur_balance = balance(cur_balance,working.rate_of_return,working.contribution);
	 cur_age++;
    }
   
    for(int j=0;j<retired.months;j++){
        printf("Age %3d month %2d you have $%.2lf\n",cur_age/12,cur_age%12,cur_balance);
	cur_balance = balance(cur_balance,retired.rate_of_return,retired.contribution);
        cur_age++;
    }
 }
   
int main(void){
     retire_info working;
     retire_info retired;
     working.months = 489;
     working.contribution=1000;
     working.rate_of_return=0.045/12;
     retired.months = 384;
     retired.contribution=-4000;
     retired.rate_of_return=0.01/12;
     int starting_months=327;
     double starting_savings=21345;
     retirement(starting_months,starting_savings,working,retired);
     return EXIT_SUCCESS;
}
