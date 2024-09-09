#include "Application.h"


void appStart(void)
{
	//Card
	ST_cardData_t C1{ "Abdallah Abbas Ramadan","3776149263527130","11/22" };
	if (getCardHolderName(&C1) || getCardExpiryDate(&C1) || getCardPAN(&C1))
	{
		return;
	}
	///////////////////////////////////////////////////////////////////////////////////
	//Terminal 
	ST_terminalData_t TR1{ 100,1000,"10/10/2022" };
	if (getTransactionDate(&TR1) || isCardExpired(&C1, &TR1) || getTransactionAmount(&TR1) || isBelowMaxAmount(&TR1))
	{
		return;
	}
	///////////////////////////////////////////////////////////////////////////////////
	//Server

	ST_accountsDB_t A1{ 10000, BLOCKED, "3776149263527130" };
	ST_transaction_t T{ { "Abdallah Abbas Ramadan","3776149263527130","11/22" },{100,1000,"10/09/2000"},APPROVED,50 };
	if (recieveTransactionData(&T) || isValidAccount(&C1, &A1) || isBlockedAccount(&A1) || isAmountAvailable(&TR1, &A1))
	{
		return;
	}
	A1.balance = A1.balance - T.terminalData.transAmount;
	printf("Transaction Done Succesfully\n");
	printf("%f", A1.balance);
	saveTransaction(&T);
}
