//***********************************************************************************************************
//Programming Assignment 02
//Programmer: Dustin Sherer
//Completed: 02/5/2022
//Status: complete
//
//This program is designed to help balance a checkbook at the end of the month, by having the user enter the initial balance followed by transactions.
// For each transaction, there should be a valid transaction type: C - process a check, D - process a deposit, E - do end of the month processing and exit program.
//***********************************************************************************************************

#pragma once

int main();

double EnterInitialBalance();
double ChooseTransaction(double AccountBalance, int ChecksProcessed);
double CheckTransaction(double trAccountBalance, int trChecksProcessed);
double ProcessCheck(double cAccountBalance, double checkAmount);
double ProcessDeposit(double dAccountBalance, double depositAmount);
double ProcessEndMonth(double eAccountBalance, int ChecksProcessed);
double AdjustBalance(double aAccountBalance, double transactionAmount);
double ServiceCharges(int ChecksProcessed);
void EndProcess(bool isEndMonth);