#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>

#define MAX_PORTFOLIO_SIZE 100
#define MAX_FILENAME_LENGTH 100
#define MAX_LINE_LENGTH 100

typedef struct {
    char symbol[10];
    int quantity;
    double price;
} Stock;

typedef struct {
    Stock stocks[MAX_PORTFOLIO_SIZE];
    int size;
} Portfolio;

double calculateDownsideRisk(const double *returns, int numReturns, double riskFreeRate);
double calculateSortinoRatio(const double *returns, int numReturns, double riskFreeRate);
double calculateTreynorRatio(double beta, double portfolioReturn, double riskFreeRate);
double calculatePortfolioValue(const Portfolio *portfolio);
double calculateROI(const Portfolio *portfolio, double initialInvestment);
double calculateAnnualizedReturn(const Portfolio *portfolio, double initialInvestment, int numYears);
double calculateStandardDeviation(const double *returns, int numReturns);
double calculateSharpeRatio(const double *returns, int numReturns, double riskFreeRate);
double calculateBeta(const double *portfolioReturns, const double *benchmarkReturns, int numReturns);
double calculateAlpha(double beta, double portfolioReturn, double riskFreeRate, double benchmarkReturn);
double calculateInformationRatio(const double *portfolioReturns, const double *benchmarkReturns, int numReturns);
double calculateMaximumDrawdown(const double *returns, int numReturns);
double calculatePortfolioTurnover(const double *transactionReturns, int numReturns);
double calculateCAGR(const double *cashFlows, int numYears);

void importReturnsData(double *returns, int *numReturns, const char *filename);
void importCSVPortfolioData(Portfolio *portfolio, const char *filename);
void inputBenchmarkReturns(double *benchmarkReturns, int numYears);
void inputTransactionHistory(double *transactionReturns, int numReturns);
void inputPortfolioHoldings(Portfolio *portfolio);

float tot_tax(float amt);
float deductions(float amt);
float ltcg();
float stcg(float amt);
float net_income();
int main(){
    float net_sal,monthly_sal,liquidity,savings,investments,budget,expenditure,liq_time,tot_savings=0,tot_investment=0,yearly_investment=0;
    int temp,time_months,numYears,i=0;
    printf("It is advised to keep 15%% for saving until liquidity is achieved\n");
    printf("10%% is advised to be put towards investments\nand the rest 75%% is used for spending\n");
    printf("For how many months do you want to input data for: ");
    scanf("%d",&time_months);
    numYears=ceil(time_months/12);
    double cashFlows[numYears];
    for(int count=1;count<=time_months;count++){
        if(count%12==1){
            printf("Enter values for this financial year\n");
            //inputing values for a new year
            net_sal=net_income();
            monthly_sal=net_sal/12;
            printf("your average monthly salary is: %.2f\n",monthly_sal);
            printf("How many monthly salary worth of liquidity do you want to hold: ");
            scanf("%d",&temp);
            liquidity=temp*monthly_sal;
            printf("It is advised to keep 15%% for saving until liquidity is achieved\n");
            printf("10%% is advised to be put towards investments\nand the rest 75%% is used for spending\n");
            budget=0.75*monthly_sal;//monthly budget
            printf("Your budget is: %.2f\n",budget);
            if(count!=1){
                cashFlows[i++]=yearly_investment;
                yearly_investment=0;
            }}
        //taking expenditure input
        printf("Enter you expenditure for month %d: ",count);
        scanf("%f",&expenditure);
        if (tot_savings<liquidity){
            savings=0.15*monthly_sal;
            investments=0.1*monthly_sal+budget-expenditure;
        }
        else{
            investments=0.25*monthly_sal+budget-expenditure;
            savings=0;
        }
        tot_savings+=savings;
        yearly_investment+=investments;
        tot_investment+=investments;
        printf("Your monthly savings are: %.2f\n",savings);
        printf("Your monthly investments are: %.2f\n",investments);}
    if(time_months%12!=0){
        cashFlows[i]=yearly_investment;
    }
    printf("Your total investments are: %.2f\n",tot_investment);
    printf("Your total savings are: %.2f\n",tot_savings);
    if(tot_savings>=liquidity){
        printf("You have achieved desired liquidity\n");
    }

    Portfolio myPortfolio;

    printf("=== Portfolio Analysis System ===\n");

    // Input portfolio holdings
    printf("\n== Portfolio Holdings ==\n");
    inputPortfolioHoldings(&myPortfolio);

    // Calculate initial investment
    double initialInvestment = calculatePortfolioValue(&myPortfolio);

    // Ask user for benchmark returns
    double benchmarkReturns[numYears];
    printf("\n== Benchmark Returns ==\n");
    inputBenchmarkReturns(benchmarkReturns, numYears);

    // Ask user for transaction history returns
    int numReturns;
    printf("\n== Transaction History ==\n");
    printf("Enter the number of transaction history returns: ");
    scanf("%d", &numReturns);

    double transactionReturns[numReturns];
    inputTransactionHistory(transactionReturns, numReturns);

    // Ask user for risk-free rate
    double riskFreeRate;
    printf("\n== Risk-Free Rate ==\n");
    printf("Enter the risk-free rate: ");
    scanf("%lf", &riskFreeRate);

    // Calculate and display performance metrics
    printf("\n=== Performance Metrics ===\n");

    double roi = calculateROI(&myPortfolio, initialInvestment);
    printf("ROI: %.2f%%\n", roi * 100);

    double annualizedReturn = calculateAnnualizedReturn(&myPortfolio, initialInvestment, numYears);
    printf("Annualized Return: %.2f%%\n", annualizedReturn * 100);

    double stdDev = calculateStandardDeviation(transactionReturns, numReturns);
    printf("Standard Deviation: %.2f\n", stdDev);

    double sharpeRatio = calculateSharpeRatio(transactionReturns, numReturns, riskFreeRate);
    printf("Sharpe Ratio: %.2f\n", sharpeRatio);

    double beta = calculateBeta(transactionReturns, benchmarkReturns, numReturns);
    printf("Beta: %.2f\n", beta);

    double alpha = calculateAlpha(beta, annualizedReturn, riskFreeRate, benchmarkReturns[numYears - 1]);
    printf("Alpha: %.2f\n", alpha);

    double informationRatio = calculateInformationRatio(transactionReturns, benchmarkReturns, numReturns);
    printf("Information Ratio: %.2f\n", informationRatio);

    double maximumDrawdown = calculateMaximumDrawdown(transactionReturns, numReturns);
    printf("Maximum Drawdown: %.2f%%\n", maximumDrawdown * 100);

    double portfolioTurnover = calculatePortfolioTurnover(transactionReturns, numReturns);
    printf("Portfolio Turnover: %.2f\n", portfolioTurnover);

    double cagr = calculateCAGR(cashFlows, numYears);
    printf("CAGR: %.2f%%\n", cagr * 100);

    double sortinoRatio = calculateSortinoRatio(transactionReturns, numReturns, riskFreeRate);
    printf("Sortino Ratio: %.2f\n", sortinoRatio);

    double treynorRatio = calculateTreynorRatio(beta, annualizedReturn, riskFreeRate);
    printf("Treynor Ratio: %.2f\n", treynorRatio);

    double downsideRisk = calculateDownsideRisk(transactionReturns, numReturns, riskFreeRate);
    printf("Downside Risk: %.2f\n", downsideRisk);


    printf("press any key to exit: ");
    char tem;
    scanf("\n%c",&tem);

    return 0;
    
}
float tot_tax(float amt){
    //calculation of tax based on indian tax bracket system 
    float tax=0;
    char ans;

    //Long Term Capital Gains
    printf("Did you incur any LTCG [y / n]: ");
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

    //Short Term Capital Gains
    printf("Did you incur any STCG [y / n]: ");
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

float stcg(float amt){
    float tax;
    tax=amt*0.15;
    return tax;
}

float deductions(float amt){
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
            sal=(amt/12);
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
    else if((ans=='y')||(ans=='Y')){
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
        printf("Enter amout of donations made that are 100%% deductible: ");
        scanf("%f",&temp);
        ded+=temp;
        printf("Enter amout of donations made that are 50%% deductible: ");
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
    printf("Do you have any asset depreciation? [y/n]: ");
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
float net_income(){
    float gross_sal,deduction,taxable_sal,net_sal,tax;
    //user input for annual salary
    printf("enter your gross annual salary: ");
    scanf("%f/n",&gross_sal);

    deduction=deductions(gross_sal);//total deduction to income
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
    return net_sal;
    }

double calculateDownsideRisk(const double *returns, int numReturns, double riskFreeRate) {
    double sum = 0.0;
    int numDownsideReturns = 0;
    for (int i = 0; i < numReturns; i++) {
        if (returns[i] < riskFreeRate) {
            sum += pow(returns[i] - riskFreeRate, 2);
            numDownsideReturns++;
        }
    }
    return sqrt(sum / numDownsideReturns);
}


double calculateSortinoRatio(const double *returns, int numReturns, double riskFreeRate) {
    double meanReturn = 0.0;
    double downsideRisk = calculateDownsideRisk(returns, numReturns, riskFreeRate);
    for (int i = 0; i < numReturns; i++) {
        meanReturn += returns[i];
    }
    meanReturn /= numReturns;
    return (meanReturn - riskFreeRate) / downsideRisk;
}

double calculateTreynorRatio(double beta, double portfolioReturn, double riskFreeRate) {
    return (portfolioReturn - riskFreeRate) / beta;
}




double calculatePortfolioValue(const Portfolio *portfolio) {
    double value = 0.0;
    for (int i = 0; i < portfolio->size; i++) {
        value += portfolio->stocks[i].quantity * portfolio->stocks[i].price;
    }
    return value;
}

double calculateROI(const Portfolio *portfolio, double initialInvestment) {
    double currentValue = calculatePortfolioValue(portfolio);
    return (currentValue - initialInvestment) / initialInvestment;
}

double calculateAnnualizedReturn(const Portfolio *portfolio, double initialInvestment, int numYears) {
    double roi = calculateROI(portfolio, initialInvestment);
    return pow(1.0 + roi, 1.0 / numYears) - 1.0;
}

double calculateStandardDeviation(const double *returns, int numReturns) {
    double sum = 0.0;
    double mean = 0.0;
    for (int i = 0; i < numReturns; i++) {
        mean += returns[i];
    }
    mean /= numReturns;
    for (int i = 0; i < numReturns; i++) {
        sum += pow(returns[i] - mean, 2);
    }
    return sqrt(sum / numReturns);
}

double calculateSharpeRatio(const double *returns, int numReturns, double riskFreeRate) {
    double meanReturn = 0.0;
    double stdDev = calculateStandardDeviation(returns, numReturns);
    for (int i = 0; i < numReturns; i++) {
        meanReturn += returns[i];
    }
    meanReturn /= numReturns;
    return (meanReturn - riskFreeRate) / stdDev;
}

double calculateBeta(const double *portfolioReturns, const double *benchmarkReturns, int numReturns) {
    double portfolioMean = 0.0;
    double benchmarkMean = 0.0;
    for (int i = 0; i < numReturns; i++) {
        portfolioMean += portfolioReturns[i];
        benchmarkMean += benchmarkReturns[i];
    }
    portfolioMean /= numReturns;
    benchmarkMean /= numReturns;

    double portfolioCov = 0.0;
    double benchmarkCov = 0.0;
    double portfolioVariance = 0.0;
    double benchmarkVariance = 0.0;
    for (int i = 0; i < numReturns; i++) {
        double portfolioDiff = portfolioReturns[i] - portfolioMean;
        double benchmarkDiff = benchmarkReturns[i] - benchmarkMean;
        portfolioCov += portfolioDiff * benchmarkDiff;
        portfolioVariance += pow(portfolioDiff, 2);
        benchmarkVariance += pow(benchmarkDiff, 2);
    }
    portfolioCov /= numReturns;
    portfolioVariance /= numReturns;
    benchmarkVariance /= numReturns;

    return portfolioCov / benchmarkVariance;
}

double calculateAlpha(double beta, double portfolioReturn, double riskFreeRate, double benchmarkReturn) {
    return portfolioReturn - (riskFreeRate + beta * (benchmarkReturn - riskFreeRate));
}

double calculateInformationRatio(const double *portfolioReturns, const double *benchmarkReturns, int numReturns) {
    double excessReturns[numReturns];
    for (int i = 0; i < numReturns; i++) {
        excessReturns[i] = portfolioReturns[i] - benchmarkReturns[i];
    }
    double stdDev = calculateStandardDeviation(excessReturns, numReturns);
    return (portfolioReturns[numReturns - 1] - benchmarkReturns[numReturns - 1]) / stdDev;
}

double calculateMaximumDrawdown(const double *returns, int numReturns) {
    double maxDrawdown = 0.0;
    double peak = returns[0];
    for (int i = 1; i < numReturns; i++) {
        if (returns[i] > peak) {
            peak = returns[i];
        } else {
            double drawdown = (peak - returns[i]) / peak;
            if (drawdown > maxDrawdown) {
                maxDrawdown = drawdown;
            }
        }
    }
    return maxDrawdown;
}

double calculatePortfolioTurnover(const double *transactionReturns, int numReturns) {
    double sum = 0.0;
    for (int i = 0; i < numReturns; i++) {
        sum += fabs(transactionReturns[i]);
    }
    return sum;
}

double calculateCAGR(const double *cashFlows, int numYears) {
    double totalReturn = 1.0;
    for (int i = 0; i < numYears; i++) {
        totalReturn *= (1.0 + cashFlows[i]);
    }
    return pow(totalReturn, 1.0 / numYears) - 1.0;
}

void importReturnsData(double *returns, int *numReturns, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", filename);
        return;
    }

    char line[MAX_LINE_LENGTH];
    *numReturns = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        sscanf(line, "%lf", &returns[*numReturns]);
        (*numReturns)++;
    }

    fclose(file);
}

void importCSVPortfolioData(Portfolio *portfolio, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", filename);
        return;
    }

    char line[MAX_LINE_LENGTH];
    int lineCount = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        if (lineCount >= MAX_PORTFOLIO_SIZE) {
            printf("Maximum portfolio size exceeded. Only the first %d stocks will be imported.\n", MAX_PORTFOLIO_SIZE);
            break;
        }

        char *symbol = strtok(line, ",");
        char *quantityStr = strtok(NULL, ",");
        char *priceStr = strtok(NULL, ",");

        if (symbol != NULL && quantityStr != NULL && priceStr != NULL) {
            strncpy(portfolio->stocks[lineCount].symbol, symbol, sizeof(portfolio->stocks[lineCount].symbol));
            portfolio->stocks[lineCount].quantity = atoi(quantityStr);
            portfolio->stocks[lineCount].price = atof(priceStr);
            lineCount++;
        }
    }

    portfolio->size = lineCount;

    fclose(file);
}

void inputCashFlows(double *cashFlows, int numYears) {
    for (int i = 0; i < numYears; i++) {
        printf("Enter cash flow for year %d: ", i + 1);
        scanf("%lf", &cashFlows[i]);
    }
}

void inputBenchmarkReturns(double *benchmarkReturns, int numYears) {
    for (int i = 0; i < numYears; i++) {
        printf("Enter benchmark return for year %d: ", i + 1);
        scanf("%lf", &benchmarkReturns[i]);
    }
}

void inputTransactionHistory(double *transactionReturns, int numReturns) {
    char filename[MAX_FILENAME_LENGTH];
    printf("Enter the filename for the transaction history data: ");
    scanf("%s", filename);

    importReturnsData(transactionReturns, &numReturns, filename);
}

void inputPortfolioHoldings(Portfolio *portfolio) {
    char filename[MAX_FILENAME_LENGTH];
    printf("Enter the filename for the portfolio holdings data: ");
    scanf("%s", filename);

    importCSVPortfolioData(portfolio, filename);
}
