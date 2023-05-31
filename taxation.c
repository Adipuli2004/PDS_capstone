#include<stdio.h>
float tot_tax(float amt);
float deductions();
float ltcg();
float stcg();

int main(){
    float gross_sal,deduction,taxable_sal,net_sal,tax;
    //user input for annual salary
    printf("enter your gross annual salary: ");
    scanf("%f/n",&gross_sal);

    deduction=deductions();//total deduction to income
    taxable_sal=gross_sal-deduction;//total taxable income
    if(taxable_sal<0){
        taxable_sal=0;
    }
    tax=tot_tax(taxable_sal);//calculating total tax
    net_sal=gross_sal-tax;//net income

    //outputing data
    printf("Your gross salary is : %.2f\n",gross_sal);
    printf("Your deductions are  : %.2f\n",deduction);
    printf("Your taxable income is : %.2f\n",taxable_sal);
    printf("Your taxes is : %.2f\n",tax);
    printf("Your net salary is : %.2f\n",net_sal);

    return 0;
}
float tot_tax(float amt){
    //calculation of tax based on indian tax bracket system 
    float tax=0;
    char ans;

    //LTCG
    printf("Did you incur any LTCG [y / n]");
    scanf("\n%c",&ans);
    if((ans=='y')||(ans=='Y')){
        float temp;
        printf("Enter total ammount of capital gains you made: ");
        scanf("%f",&temp);
        amt-=temp;
        tax+=ltcg(temp);
    }
    else if((ans=='n')||(ans=='N')){
        ans='y';
        printf("OK\n");
    }
    else{
        ans='y';
        printf("invalid input\n");
    }

    //STCG
    printf("Did you incur any STCG [y / n]");
    scanf("\n%c",&ans);
    if((ans=='y')||(ans=='Y')){
        float temp;
        printf("Enter total ammount of capital gains you made: ");
        scanf("%f",&temp);
        amt-=temp;
        tax+=stcg(temp);
    }
    else if((ans=='n')||(ans=='N')){
        printf("OK\n");
    }
    else{
        printf("invalid input\n");
    }

    //tax bracket calculation
    if(amt>1500000){
        tax+=(amt-1500000)*0.3;
        amt=1500000;
    }
    if(amt>1200000){
        tax+=(amt-1200000)*0.2;
        amt=1200000;
    }
    if(amt>900000){
        tax+=(amt-900000)*0.15;
        amt=900000;
    }
    if(amt>600000){
        tax+=(amt-600000)*0.1;
        amt=600000;
    }
    if(amt>300000){
        tax+=(amt-300000)*0.05;
        amt=300000;
    }
    return tax;
}

float ltcg(){
    float amt1,amt2,tax;
    printf("How much long term capital gains have you made at\n 10%% tax bracket: ");
    scanf("%f",&amt1);
    printf("20%% tax bracket: ");
    scanf("%f",&amt2);
    tax=amt1*0.1+amt2*0.2;
    return tax;
}

float stcg(){
    float amt;
    printf("How much short term capital gains have you made: ");
    scanf("%f",&amt);
    float tax;
    tax=amt*0.15;
    return tax;
}

float deductions(){
    float ded,temp;
    char ans;

    //education loan interest deduction
    printf("do you have educational loan deduction? [y/n]: ");
    scanf("\n%c",&ans);
    if((ans=='Y')||(ans=='y')){
        printf("Enter interest on loan paid: ");
        scanf("%f",&temp);
        ded+=temp;
    }
    else if((ans=='n')||(ans=='N')){
        ans='y';
        printf("OK\n");
    }
    else{
        ans='y';
        printf("invalid input\n");
    }

    //tution fee reduction of atmost two children
    printf("do you have tution fee deduction? [y/n]: ");
    scanf("\n%c",&ans);
    if((ans=='Y')||(ans=='y')){
        int num;
        printf("Enter number of children you have: ");
        scanf("%d",&num);
        if(num>2){
            printf("Enter tution fees paid for two children: ");
        scanf("%f",&temp);}
        else{
        printf("Enter tution fees paid: ");
        scanf("%f",&temp);}
        ded+=temp;}
    
    else if((ans=='n')||(ans=='N')){
        ans='y';
        printf("OK\n");
    }
    else{
        ans='y';
        printf("invalid input\n");
    }

    //HRA dedcution least of 5000,rent-10%of salary or 25% of salary
    printf("do you receive HRA? [y/n]: ");
    scanf("\n%c",&ans);
    if((ans=='N')||(ans=='n')){
        printf("do you rent a house? [y/n]: ");
        scanf("\n%c",&ans);
        if((ans=='Y')||(ans=='y')){
            float sal,rent;
            printf("Enter your monthly salary: ");
            scanf("%f",&sal);
            printf("Enter monthly rent paid : ");
            scanf("%f",&rent);
            if((rent-0.1*sal)<5000 &&((rent-0.1*sal)<0.25*sal)){
                if((rent-0.1*sal)>0){
                    temp=rent-0.1*sal;
                }
            }
            else if((rent-0.1*sal)>5000 && (5000<0.25*sal)){
                temp=5000;
            }
            else{
                temp=0.25*sal;
            }
            ded+=12*temp;
        }
        else if((ans=='Y')||(ans=='y')){
            ans='y';
            printf("OK\n");
        }
        else{
            ans='y';
            printf("invalid input\n");
        }
    }
    else if((ans=='n')||(ans=='N')){
        ans='y';
        printf("OK\n");
    }
    else{
        printf("invalid input\n");
    }
    
    //charitable donation deductions
    printf("have you made any charitable donations? [y/n]: ");
    scanf("\n%c",&ans);
    if((ans=='Y')||(ans=='y')){
        printf("Enter amout of donations made that are 100 deductible: ");
        scanf("%f",&temp);
        ded+=temp;
        printf("Enter amout of donations made that are 50 deductible: ");
        scanf("%f",&temp);
        ded+=0.5*temp;
    }
    else if((ans=='n')||(ans=='N')){
        ans='y';
        printf("OK\n");
    }
    else{
        ans='y';
        printf("invalid input\n");
    }

    //standard deduction of 50,000
    printf("do you qualify for standard dedcution? [y/n]: ");
    scanf("\n%c",&ans);
    if((ans=='Y')||(ans=='y')){
        ded+=50000;
    }
    else if((ans=='n')||(ans=='N')){
        ans='y';
        printf("OK\n");
    }
    else{
        ans='y';
        printf("invalid input\n");
    }

    //asset depreciation reduction
    printf("Do you have any asset depreciation? [y/n: ");
    scanf("\n%c",&ans);
    if((ans=='Y')||(ans=='y')){
        printf("Enter amount of depreciation: ");
        scanf("%f",&temp);
        ded+=temp;
    }
    else if((ans=='n')||(ans=='N')){
        ans='y';
        printf("OK\n");
    }
    else{
        ans='y';
        printf("invalid input\n");
    }
    return ded;
}