#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

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

int main() {
    Portfolio myPortfolio;

    printf("=== Portfolio Analysis System ===\n");

    // Input portfolio holdings
    printf("\n== Portfolio Holdings ==\n");
    inputPortfolioHoldings(&myPortfolio);

    // Calculate initial investment
    double initialInvestment = calculatePortfolioValue(&myPortfolio);

    // Ask user for cash flows
    int numYears;
    printf("\n== Cash Flows ==\n");
    printf("Enter the number of years for cash flows: ");
    scanf("%d", &numYears);

    double cashFlows[numYears];
    inputCashFlows(cashFlows, numYears);

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

    return 0;
}
