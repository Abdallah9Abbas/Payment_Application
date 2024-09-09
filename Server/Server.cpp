#include "Server.h"

ST_accountsDB_t accountsDB[255] = {};
ST_transaction_t transazction[255] = { 0 };

void assign()
{
	ST_accountsDB_t A1{ 10000, RUNNING, "3776149263527130" };
	ST_accountsDB_t A2{ 200, BLOCKED, "379719524036967" };
	ST_accountsDB_t A3{ 90000, RUNNING, "373395927392905" };
	ST_accountsDB_t A4{ 100000, BLOCKED, "370608826148761" };
	ST_accountsDB_t A5{ 1000, RUNNING, "374804471855877" };
	accountsDB[0] = A1;
	accountsDB[2] = A2;
	accountsDB[3] = A3;
	accountsDB[4] = A4;
	accountsDB[5] = A5;
}
EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{
	int i = 0;
	bool found = false;
	int No = 0;
	for (int i = 0; i < 255; i++)
	{
		int equal = 0;
		for (int j = 0; j < 20; j++)
		{
			if (accountsDB[i].primaryAccountNumber[j] == transData->cardHolderData.primaryAccountNumber[j])
			{
				equal++;
			}
		}
		if (equal ==20)
		{
			found = true;
			No = i;
			break;
		}
	}
	if (!found)
	{
		printf("Fraud card");
		return FRAUD_CARD;
	}
	if (accountsDB[No].balance < transData->terminalData.transAmount)
	{
		printf("Declined insuffecient fund");
		return DECLINED_INSUFFECIENT_FUND;
	}
	if (accountsDB[No].state == BLOCKED)
	{
		printf("Declined stolen card");
		return DECLINED_STOLEN_CARD;
	}
	if (transazction[i].transactionSequenceNumber > 255)
	{
		printf("Internal server error");
		return INTERNAL_SERVER_ERROR;
	}
	return APPROVED;

}
EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence)
{
	bool found = false;
	int No = NULL;

	int equal = 0;
	for (int j = 0; j < 20; j++)
	{
		if (accountRefrence->primaryAccountNumber[j] == cardData->primaryAccountNumber[j])
		{
			equal++;
		}
	}
	if (equal == 20)
	{
		found = true;
		return SERVER_OK;
	}
	if (!found)
	{
		accountRefrence = NULL;
		printf("Account not found");
		return ACCOUNT_NOT_FOUND;
	}
}
EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence)
{
	if (accountRefrence->state == BLOCKED)
	{
		printf("Blocked account");
		return BLOCKED_ACCOUNT;
	}
	else
	{
		return SERVER_OK;
	}
}
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence)
{
	if (termData->transAmount > accountRefrence->balance)
	{
		printf("Low balance");
		return LOW_BALANCE;
	}
	else
	{
		return SERVER_OK;
	}
}
EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
	//Assuming the sequence start with 1
	//transData->cardHolderData.
	//transData->terminalData.transAmount;
	int	i = 0;
	while (transazction[i].transactionSequenceNumber != 0)
	{
		i++;
	} 
	transData->transactionSequenceNumber = i + 1;
	transazction[i + 1] = *transData;
	return SERVER_OK;
}
void listSavedTransactions(void)
{
	ST_transaction_t T{ { "Abdallah Abbas Ramadan","377614263527130","11/22" },{100,1000,"10/09/2000"},APPROVED,50 };
	transazction[0] = T;
	for (int i = 0; i < 255; i++)
	{
		if (transazction[i].transactionSequenceNumber!=0)
		{
			printf("####################################\n");
			printf("Transaction Sequence Number: ");
			printf("%d", transazction[i].transactionSequenceNumber);
			printf("\n");
			printf("Transaction Date: ");
			printf("%s", transazction[i].terminalData.transactionDate);
			printf("\n");
			printf("Transaction Amount: ");
			printf("%f", transazction[i].terminalData.transAmount);
			printf("\n");
			printf("Transaction State: ");
			printf("%d", transazction[i].transState);
			printf("\n");
			printf("Terminal Max Amount: ");
			printf("%f", transazction[i].terminalData.maxTransAmount);
			printf("\n");
			printf("Cardholder Name: ");
			printf("%s", transazction[i].cardHolderData.cardHolderName);
			printf("\n");
			printf("PAN: ");
			printf("%s", transazction[i].cardHolderData.primaryAccountNumber);
			printf("\n");
			printf("Card Expiration Date: ");
			printf("%s", transazction[i].cardHolderData.cardExpirationDate);
			printf("\n");
			printf("####################################\n");
		}
	}
}
void recieveTransactionDataTest(void)
{
	assign();
	ST_transaction_t T{ { "Abdallah Abbas Ramadan","377614263527130","11/22" },{100,1000,"10/09/2000"},APPROVED,50};
	EN_transState_t E = recieveTransactionData(&T);
	char x[] = "Abdallah Ahmed Abbass\n";
	printf("Tester name: ");
	printf(x, "\n");
	printf("Function name: ");
	printf("recieveTransactionData. \n");
	printf("Test case 1:\n");
	printf("Input Data: ");
	printf("Expected result: ");
	printf("%d", APPROVED);
	printf("\n");
	printf("Actual result: ");
	printf("%d", E);
	printf("\n");
	printf("Test case 2:\n");
	printf("Input Data: ");
	printf("Expected result: ");
	printf("%d", FRAUD_CARD);
	printf("\n");
	printf("Actual result: ");
	ST_transaction_t T1{ { "Abdallah Abbas Ramadan","100","11/22" },{100,1000,"10/09/2000"},APPROVED,50 };
	EN_transState_t E2 = recieveTransactionData(&T1);
	printf("%d", E2);
	printf("\n");

}

void isValidAccountTest(void)
{
	ST_cardData_t C1{ "Abdallah Abbas Ramadan","377614263527130","11/22" };
	ST_cardData_t C2{ "Abdallah Abbas Ramadan","377914263527130","11/22" };
	ST_accountsDB_t A1{ 10000, RUNNING, "377614263527130" };
	EN_serverError_t E1 = isValidAccount(&C1, &A1);
	EN_serverError_t E2 = isValidAccount(&C2, &A1);
	char x[] = "Abdallah Ahmed Abbass\n";
	printf("Tester name: ");
	printf(x, "\n");
	printf("Function name: ");
	printf("isValidAccount. \n");
	printf("Test case 1:\n");
	printf("Input Data: ");
	printf("Expected result: ");
	printf("%d", SERVER_OK);
	printf("\n");
	printf("Actual result: ");
	printf("%d", E1);
	printf("\n");
	printf("Test case 2:\n");
	printf("Input Data: ");
	printf("Expected result: ");
	printf("%d", ACCOUNT_NOT_FOUND);
	printf("\n");
	printf("Actual result: ");
	printf("%d", E2);
	printf("\n");
}

void isBlockedAccountTest(void)
{
	ST_accountsDB_t A1{ 10000, RUNNING, "377614263527130" };
	ST_accountsDB_t A2{ 200, BLOCKED, "379719524036967" };
	EN_serverError_t E1 = isBlockedAccount(&A1);
	EN_serverError_t E2 = isBlockedAccount(&A2);
	char x[] = "Abdallah Ahmed Abbass\n";
	printf("Tester name: ");
	printf(x, "\n");
	printf("Function name: ");
	printf("isBlockedAccount. \n");
	printf("Test case 1:\n");
	printf("Input Data: ");
	printf("Expected result: ");
	printf("%d", SERVER_OK);
	printf("\n");
	printf("Actual result: ");
	printf("%d", E1);
	printf("\n");
	printf("Test case 2:\n");
	printf("Input Data: ");
	printf("Expected result: ");
	printf("%d", BLOCKED_ACCOUNT);
	printf("\n");
	printf("Actual result: ");
	printf("%d", E2);
	printf("\n");

}

void isAmountAvailableTest(void)
{
	ST_accountsDB_t A1{ 10000, RUNNING, "377614263527130" };
	ST_accountsDB_t A2{ 200, BLOCKED, "379719524036967" };
	ST_terminalData_t T1{ 500, 1000, "10/09/2000" };
	EN_serverError_t E1 = isAmountAvailable(&T1,&A1);
	EN_serverError_t E2 = isAmountAvailable(&T1, &A2);
	char x[] = "Abdallah Ahmed Abbass\n";
	printf("Tester name: ");
	printf(x, "\n");
	printf("Function name: ");
	printf("isAmountAvailable. \n");
	printf("Test case 1:\n");
	printf("Input Data: ");
	printf("Expected result: ");
	printf("%d", SERVER_OK);
	printf("\n");
	printf("Actual result: ");
	printf("%d", E1);
	printf("\n");
	printf("Test case 2:\n");
	printf("Input Data: ");
	printf("Expected result: ");
	printf("%d", LOW_BALANCE);
	printf("\n");
	printf("Actual result: ");
	printf("%d", E2);
	printf("\n");

}

void saveTransactionTest(void)
{
	ST_transaction_t T{ { "Abdallah Abbas Ramadan","377614263527130","11/22" },{100,1000,"10/09/2000"},APPROVED,50 };
	EN_serverError_t E = saveTransaction(&T);
	char x[] = "Abdallah Ahmed Abbass\n";
	printf("Tester name: ");
	printf(x, "\n");
	printf("Function name: ");
	printf("saveTransaction. \n");
	printf("Test case 1:\n");
	printf("Input Data: ");
	printf("Expected result: ");
	printf("%d", SERVER_OK);
	printf("\n");
	printf("Actual result: ");
	printf("%d", E);
	printf("\n");
}

void listSavedTransactionsTest(void)
{
	listSavedTransactions();
}
