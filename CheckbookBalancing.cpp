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

#include <iostream>
#include <iomanip>
#include <string.h>
#include "CheckbookBalancing.h"

int main()
{
    //variables
    float beginningBalance = 0.0f;          // var to store user's beginning balance
    static float workingBalance = 0.0f;     // var to store working balance during running of program
    bool CalcAgain = false;                 // bool to keep track is user wants to calculate another month


    std::cout << "Checkbook Balancing Program Revisited\n\n";

    beginningBalance = EnterBeginningBalance();
    workingBalance = beginningBalance;

    PrintTransInstructions();
    TransactionLoop(workingBalance);
    EndProcess(CalcAgain);

}

// **************************************************************************************************************************
// function TransactionLoop()
//      Main Transaction Loop
//      -responsible for allowing the user to enter Check/Deposit transactions until they wish to process end of the month.     
// **************************************************************************************************************************
void TransactionLoop(float& inBalance)
{
    char transactionType;
    float transactionAmount;
    std::cout << "\n\nEnter a transaction: ";
    std::cin >> transactionType;

    if (transactionType == 'E' || transactionType == 'e')
    {
		ChooseTransaction(transactionType, inBalance);
        return;
    }
    else if (transactionType == 'C' || transactionType == 'c' || transactionType == 'D' || transactionType == 'd')
    {
        std::cin >> transactionAmount;
		ChooseTransaction(transactionType, inBalance, transactionAmount);
		return;
    }
    else
    {
        std::cout << "\n-----Please enter a valid transaction-----\n\n";
        PrintTransInstructions();
        TransactionLoop(inBalance);
    }
}
// **************************************************************************************************************************
// function ChooseTransaction()
//      Directs to the relevant function to process a transaction
//      Dependent on which transaction is requested, the transaction amount, and if they are each valid 
// **************************************************************************************************************************
void ChooseTransaction(char transType, float currentBalance, float transAmount /*= 0.0f*/)
{
    static float previousBalance; // declare variable to hold value of balance after last transaction

    // directs to ProcessCheck() if user requests check transaction and transaction amount is positive
    if ((transType == 'C' || transType == 'c') && isTransAmountValid(transAmount))
    {
        previousBalance = ProcessCheck(transAmount, currentBalance);
        TransactionLoop(previousBalance);
    }
    // directs to ProcessDeposit() if user requests deposit transaction and transaction amount is positive
    else if ((transType == 'D' || transType == 'd') && isTransAmountValid(transAmount))
    {
        previousBalance = ProcessDeposit(transAmount, currentBalance);
        TransactionLoop(previousBalance);
    }
    // directs to ProcessEndOfMMonth() if user requests end of month transaction
    else if (transType == 'E' || transType == 'e')
    {
        ProcessEndOfMonth(currentBalance);
    }
    // when user enters invalid transaction type or amount, reprints instructions, then directs back to transaction loop
    else
    {
        std::cout << "\n-----Please enter a valid transaction-----\n\n";
        PrintTransInstructions();
        TransactionLoop(previousBalance);
    }
    return;
}

// **************************************************************************************************************************
// TODO float ProcessCheck(float transAmount, float currentBalance)
//      to be called in ChooseTransaction() when user selects to process a check
//      will return important info to user: 
//      (1) transaction amount
//      (2) resulting Balance
//      (3) updates to service charges
// **************************************************************************************************************************
float ProcessCheck(float transAmount, float currentBalance)
{
    // declares variable to store/calculate new balance after processing check
    float newBalance;
    newBalance = currentBalance - transAmount;

    // prints amount being processed for check
    std::cout << "Processing check for: ";
    FormatToDollar(transAmount);

    // prints new balance
    std::cout << "\nBalance: ";
    FormatToDollar(newBalance);

    // calls to update user on new-individual, and current-total service charges
    UpdateServiceCharges('C', newBalance, currentBalance);

    return newBalance;
}

// **************************************************************************************************************************
// TODO float ProcessDeposit(float transAmount, float currentBalance)
//      to be called in ChooseTransaction() when user selects to process a deposit
//      (1) transaction amount
//      (2) resulting Balance
//      (3) updates to service charges
// **************************************************************************************************************************
float ProcessDeposit(float transAmount, float currentBalance)
{
    // declares variable to store/calculate new balance after processing deposit
	float newBalance;
	newBalance = currentBalance + transAmount;

    // prints amount being processed for deposit
	std::cout << "Processing deposit for: ";
	FormatToDollar(transAmount);

    // prints new balance
	std::cout << "\nBalance: ";
	FormatToDollar(newBalance);

    // calls to update user on current-total service charges
	UpdateServiceCharges('D', newBalance, currentBalance);

	return newBalance;
}

// **************************************************************************************************************************
// function ProcessEndOfMonth()
//      to be called in ChooseTransaction() when user selects to perform end of month processing
//      (1) print "Processing end of the month
//      (2) call UpdateServiceCharges() to calculate and print final balance after service charges are applied
// **************************************************************************************************************************
void ProcessEndOfMonth(float currentBalance)
{
    std::cout << "Processing end of month";
    UpdateServiceCharges('E', currentBalance);
}

// **************************************************************************************************************************
// function UpdateServiceCharges()
//          to be called by Process*transaction type*() functions to update totalServiceCharge variable
//          (IMPORTANT) Service charges will not be APPLIED to workingBalance until ProcessEndOfMonth() called
// 
//      static int numChecks = 0;
//      static int numNegBal = 0;
//      static float totalServiceCharge = 0.0f;    // var for continual accrual of total service charges through the end of month transaction
//      static bool lowBalance = false;            // var to store if workingBalance is ever below $1000 at any time during month
//***********************************************************************************************************
void UpdateServiceCharges(char transType, float currentBalance, float previousBalance /*= 0.0f*/)
{
	static int numChecks = 0;
	static int numNegBal = 0;
    static int numLowBal = 0;
	static float totalServiceCharge = 0.0f;
    bool wasAcctBalanceLow = false;

    // depending on transaction type, prints and/or calculates service charges
    switch (transType)
    {
        // processes/prints service charges associated with check transactions
        case 'C':
            // tracks how many checks are processed
            numChecks++;

            // prints check service charge notice each check
            std::cout << "\nService charge: ";
            FormatToDollar(checkProcessChrg);
            std::cout << " for a check";

			// checks if check brings balance below low balance threshold
			if (currentBalance < lowAcctBalThresh)
			{
				numLowBal++;
                wasAcctBalanceLow = true;

				// only prints out low balance service charge message the first time balance is below low balance threshold
				if (wasAcctBalanceLow && (numLowBal <= 1))
				{
					std::cout << "\nService charge: ";
					FormatToDollar(lowAcctBalCharge);
					std::cout << " for balance below ";
                    FormatToDollar(lowAcctBalThresh);
				}
			}

			// prints, and increments number of insufficient funds charges if check brings funds into negative, and including if it brings balance further negative
			if ((currentBalance < negAcctBalThresh) && (currentBalance < previousBalance))
			{
                numNegBal++;
				std::cout << "\nService charge: ";
				FormatToDollar(negAcctBalCharge);
				std::cout << " for insufficient funds.";
			}

            // updates, then prints out total of service charges up to that transaction
            totalServiceCharge = (numChecks * checkProcessChrg) + (numNegBal * negAcctBalCharge) + (wasAcctBalanceLow * lowAcctBalCharge);
            std::cout << "\nTotal service charges: ";
            FormatToDollar(totalServiceCharge);
            break;

        // prints current amount of service charges when deposit is processed
        case 'D':
            // prints out total of service charges up to that transaction
            std::cout << "\nTotal service charges: ";
            FormatToDollar(totalServiceCharge);
            break;

        // calculates, then prints final balance after service charges are applied
		case 'E':
            // updates current balance to final balance by deducting all accumulated service charges
            float endBalance;
            endBalance = currentBalance - totalServiceCharge;

            // prints out final balance
            std::cout << "\nFinal balance: ";
            FormatToDollar(endBalance);
			break;

        // error message for testing, should not print under normal operation
        default:
            std::cout << "\nSOMETHING WENT WRONG";
			PrintTransInstructions();
			TransactionLoop(currentBalance);
            break;
    }
    return;
}

// **************************************************************************************************************************
// TODO float EnterBeginningBalance()
//      to be called by main() to ask user for beginning balance, then returns it to fuction who called it
// **************************************************************************************************************************
float EnterBeginningBalance()
{
    float beginningBalance = 0.0f;

    std::cout << "\nEnter the beginning balance:";
    std::cin >> beginningBalance;
    std::cout << "\n\n";

    return beginningBalance;
}

// **************************************************************************************************************************
// TODO void PrintTransInstructions()
//      Outputs instructions for entering transactions, then returns to function who called it
// **************************************************************************************************************************
void PrintTransInstructions()
{
    std::cout << "==========================================================================";
    std::cout << "\n For desired transaction input, please enter as follows:\n";
    std::cout << "\n  transaction: 'Letter'->  KEY  -> amount ->  KEY";
    std::cout << "\n--------------------------------------------------------------------------";
    std::cout << "\n   check:         'C'  -> SPACE -> amount -> ENTER";
    std::cout << "\n   deposit:       'D'  -> SPACE -> amount -> ENTER";
    std::cout << "\n   end-of-month:  'E'  -> ENTER";
    std::cout << "\n==========================================================================";
    return;
}

// **************************************************************************************************************************
// TODO bool isTransAmountValid(float transactionAmount)
//      to be called by Process*transaction type*() functions to verify user enters positive number for transaction
//      (1) if transactionAmount is greater than 0 -> return true
//      (2) else -> return false
// **************************************************************************************************************************
bool isTransAmountValid(float transactionAmount)
{
    if (transactionAmount > 0)
    {
        return true;
    }
    else {return false;}
}

// **************************************************************************************************************************
// TODO void FormatToDollar()
//      takes float and prints out in dollar format, then returns to function who called it
// **************************************************************************************************************************
void FormatToDollar(float dollarAmount)
{
    std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(2);
    std::cout << "$" << dollarAmount;
    return;
}

// **************************************************************************************************************************
// function EndProcess()
//      used to prevent cmd-line from instant-closing, and gives user option to calculate another month
// **************************************************************************************************************************
void EndProcess(bool isUserDone)
{
	if (!isUserDone)
	{
		char answer;
		std::cout << "\n\nDo you wish to calculate another month? (Y/N)" << std::endl;
		std::cin >> answer;
		if ((answer == 'N') || (answer == 'n'))
		{
			isUserDone = true;
            return;
		}
		else if ((answer == 'Y') || (answer == 'y'))
		{
			std::cout << std::endl;
			main();
            return;
		}
		else
		{
			isUserDone = false;
            return;
		}
	}
    return;
}