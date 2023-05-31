#include<stdio.h>
#include<math.h>
int main(){
    float net_income,monthly_sal,liquidity,savings,investments,budget,expenditure,liq_time;
    int temp;

    //user input for net income
    printf("Enter your net income: ");
    scanf("%f",&net_income);

    monthly_sal=(net_income/12);
    printf("your average monthly salary is: %.2f\n",monthly_sal);

    printf("Enter how many months of liquidity would you like to keep *recommended 2 or 3*: ");
    scanf("%d",&temp);

    liquidity=temp*monthly_sal;
    printf("your liquidity is %.2f\n",liquidity);

    printf("It is advised to keep 15%% for saving until liquidity is achieved\n");
    printf("10%% is advised to be put towards investments\nand the rest 75%% is used for spending\n");
    savings=0.15*monthly_sal;//monthly savings
    investments=0.1*monthly_sal;//monthly investments
    budget=0.75*monthly_sal;//monthly budget
    printf("Your monthly savings are: %.2f\n",savings);
    printf("Your monthly investments are: %.2f\n",investments);
    printf("Your budget is: %.2f\n",budget);
    liq_time=ceil(liquidity/savings);
    printf("%.2f\n",liq_time);
    printf("Enter you expenditure: ");
    scanf("%f",&expenditure);


}
