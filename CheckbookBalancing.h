//***********************************************************************************************************
//Programming Assignment 03
//Programmer: Dustin Sherer
//Completed: 02/10/2022
//Status: Completed
//
//This program is designed to help balance a checkbook at the end of the month, by having the user enter the initial balance followed by transactions.
// For each transaction, there should be a valid transaction type: C - process a check, D - process a deposit, E - do end of the month processing and exit program.
// Each transaction will print: 
//      (1) transaction type (and amount if applicable) 
//      (2) the resulting account balance 
//      (3) type and amount of new service charges 
//      (4) total service charges up to that point
//***********************************************************************************************************

#pragma once

//global constants
const float lowAcctBalThresh = 1000.00f;    // threshold for low account balance charge
const float lowAcctBalCharge = 10.00f;		// charge amount for low account balance
const float negAcctBalThresh = 0.0f;		// threshold for negative account balance charge
const float negAcctBalCharge = 30.0f;		// charge amount for negative account balance
const float checkProcessChrg = 0.35f;		// charge amount for each check processed

//functions
void TransactionLoop(float& balance);
void ChooseTransaction(char transType, float currentBalance, float transAmount = 0.0f);
float ProcessCheck(float transAmount, float currentBalance);
float ProcessDeposit(float transAmount, float currentBalance);
void ProcessEndOfMonth(float currentBalance);
void UpdateServiceCharges(char transType, float currentBalance, float previousBalance = 0.0f);
float EnterBeginningBalance();
void PrintTransInstructions();
bool isTransAmountValid(float transactionAmount);
void FormatToDollar(float dollarAmount);
void EndProcess(bool isEndMonth);
