#include "Terminal.h"

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
	int i = 0;
	int n = 0;
	while (termData->transactionDate[i])
	{
		i++;
	}
	if (i > 10 || i < 10 || i == 0)
	{
		printf("Wrong date");
		return WRONG_DATE;
	}
	for (int i = 0; i < 2; i++)
	{
		if (termData->transactionDate[i] >= 48 && termData->transactionDate[i] <= 57)
		{
			n++;
		}
	}
	if (termData->transactionDate[2] == 47)
	{
		n++;
	}
	for (int i = 3; i < 5; i++)
	{
		if (termData->transactionDate[i] >= 48 && termData->transactionDate[i] <= 57)
		{
			n++;
		}
	}
	if (termData->transactionDate[5] == 47)
	{
		n++;
	}
	for (int i = 6; i < 10; i++)
	{
		if (termData->transactionDate[i] >= 48 && termData->transactionDate[i] <= 57)
		{
			n++;
		}
	}
	if (n == 10)
	{
		return TERMINAL_OK;
	}
	else
	{
		printf("Wrong date");
		return WRONG_DATE;
	}
}

EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData)
{
	int Yc1 = cardData->cardExpirationDate[3] - '0';
	int Yc2 = cardData->cardExpirationDate[4] - '0';
	int Yt1 = termData->transactionDate[8] - '0';
	int Yt2 = termData->transactionDate[9] - '0';
	int Yc = (Yc1 * 10) + (Yc2);
	int Yt = (Yt1 * 10) + Yt2;
	if (Yc < Yt)
	{
		printf("Expired card");
		return EXPIRED_CARD;
	}
	else if (Yc > Yt)
	{
		return TERMINAL_OK;
	}
	else
	{
		int Mc1 = cardData->cardExpirationDate[0] - '0';
		int Mc2 = cardData->cardExpirationDate[1] - '0';
		int Mt1 = termData->transactionDate[3] - '0';
		int Mt2 = termData->transactionDate[4] - '0'; 
		int Mc = (Mc1 * 10) + (Mc2);
		int Mt = (Mt1 * 10) + Mt2;			
		if (Mc < Mt)			  
		{
			printf("Expired card");
			return EXPIRED_CARD;
		}
		else
		{
			return TERMINAL_OK;

		}
	}
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
	if (termData->transAmount <= 0)
	{
		printf("Invalid amount");
		return INVALID_AMOUNT;
	}
	else
	{
		return TERMINAL_OK;
	}
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
	if (termData->transAmount > termData->maxTransAmount)
	{
		printf("EXCEED the maximum amount");
		return EXCEED_MAX_AMOUNT;
	}
	else
	{
		return TERMINAL_OK;
	}
}

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData, float maxAmount)
{
	termData->maxTransAmount = maxAmount;
	if (termData->maxTransAmount <= 0)
	{
		printf("Invalid the maximum amount");
		return INVALID_MAX_AMOUNT;
	}
	else
	{
		return TERMINAL_OK;
	}
}

EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData)
{
	int test[20];
	for (int i = 0; i < 20; i++)
	{
		int x = cardData->primaryAccountNumber[i] - '0';
		if (i % 2 == 0)
		{
			test[i] = x * 2;
		}
		else
		{
			test[i] = x;
		}
		if (test[i] >= 10)
		{
			int u = test[i] % 10;
			int t = test[i] / 10;
			test[i] = u + t;
		}
	}
	int sum =0;
	for (int i = 0; i < 20; i++)
	{
		sum = sum + test[i];
	}
	printf("\n");
	if (sum % 10 == 0)
	{
		return TERMINAL_OK;
	}
	else
	{
		printf("Invalid card");
		return INVALID_CARD;
	}
}

void getTransactionDateTest(void)
{
	char x[] = "Abdallah Ahmed Abbass\n";
	printf("Tester name: ");
	printf(x, "\n");
	printf("Function name: ");
	printf("getCardExpiryDate. \n");
	char test1[] = "10/09/2000";
	char test2[] = "12312";
	char test3[] = "0123";
	ST_terminalData_t object{};
	printf("Test case 1:\n");
	for (int i = 0; i < (sizeof(test1) / sizeof(test1[0])); i++)
	{
		object.transactionDate[i] = test1[i];
	}
	EN_terminalError_t T1 = getTransactionDate(&object);
	printf("Input Data: ");
	printf("%s", test1);
	printf("\n");
	printf("Expected result: ");
	printf("%d", CARD_OK);
	printf("\n");
	printf("Actual result: ");
	printf("%d", T1);
	printf("\n");


	printf("Test case 2:\n");
	for (int i = 0; i < (sizeof(test2) / sizeof(test2[0])); i++)
	{
		object.transactionDate[i] = test2[i];
	}
	EN_terminalError_t T2 = getTransactionDate(&object);
	printf("Input Data: ");
	printf("%s", test2);
	printf("\n");
	printf("Expected result: ");
	printf("%d", WRONG_DATE);
	printf("\n");
	printf("Actual result: ");
	printf("%d", T2);
	printf("\n");


	printf("Test case 3:\n");
	for (int i = 0; i < (sizeof(test3) / sizeof(test3[0])); i++)
	{
		object.transactionDate[i] = test3[i];
	}
	EN_terminalError_t T3 = getTransactionDate(&object);
	printf("Input Data: ");
	printf("%s", test3);
	printf("\n");
	printf("Expected result: ");
	printf("%d", WRONG_DATE);
	printf("\n");
	printf("Actual result: ");
	printf("%d", T3);
	printf("\n");
}

void isCardExpriedTest(void)
{
	char x[] = "Abdallah Ahmed Abbass\n";
	printf("Tester name: ");
	printf(x, "\n");
	printf("Function name: ");
	printf("getCardExpiryDate. \n");
	char test1[] = "10/09/2000";
	char test2[] = "10/03/2025";
	char test3[] = "10/12/2022";
	ST_terminalData_t object{};
	ST_cardData_t card{};
	char testc[] = "10/09";
	for (int i = 0; i < (sizeof(testc) / sizeof(testc[0])); i++)
	{
		card.cardExpirationDate[i] = testc[i];
	}
	printf("Test case 1:\n");
	for (int i = 0; i < (sizeof(test1) / sizeof(test1[0])); i++)
	{
		object.transactionDate[i] = test1[i];
	}
	EN_terminalError_t T1 = isCardExpired(&card,&object);
	printf("Input Data: ");
	printf("%s", test1);
	printf("\n");
	printf("Expected result: ");
	printf("%d", TERMINAL_OK);
	printf("\n");
	printf("Actual result: ");
	printf("%d", T1);
	printf("\n");


	printf("Test case 2:\n");
	for (int i = 0; i < (sizeof(test2) / sizeof(test2[0])); i++)
	{
		object.transactionDate[i] = test2[i];
	}
	EN_terminalError_t T2 = isCardExpired(&card, &object);
	printf("Input Data: ");
	printf("%s", test2);
	printf("\n");
	printf("Expected result: ");
	printf("%d", TERMINAL_OK);
	printf("\n");
	printf("Actual result: ");
	printf("%d", T2);
	printf("\n");


	printf("Test case 3:\n");
	for (int i = 0; i < (sizeof(test3) / sizeof(test3[0])); i++)
	{
		object.transactionDate[i] = test3[i];
	}
	EN_terminalError_t T3 = isCardExpired(&card, &object);
	printf("Input Data: ");
	printf("%s", test3);
	printf("\n");
	printf("Expected result: ");
	printf("%d", EXPIRED_CARD);
	printf("\n");
	printf("Actual result: ");
	printf("%d", T3);
	printf("\n");
}

void getTransactionAmountTest(void)
{
	char x[] = "Abdallah Ahmed Abbass\n";
	printf("Tester name: ");
	printf(x, "\n");
	printf("Function name: ");
	printf("getCardExpiryDate. \n");
	int test1 = 1000;
	int test2 = 0;
	int test3 = -1;
	ST_terminalData_t object{};
	printf("Test case 1:\n");
	object.transAmount = test1;
	EN_terminalError_t T1 = getTransactionAmount(&object);
	printf("Input Data: ");
	printf("%d", test1);
	printf("\n");
	printf("Expected result: ");
	printf("%d", CARD_OK);
	printf("\n");
	printf("Actual result: ");
	printf("%d", T1);
	printf("\n");


	printf("Test case 2:\n");
	object.transAmount = test2;
	EN_terminalError_t T2 = getTransactionAmount(&object);
	printf("Input Data: ");
	printf("%d", test2);
	printf("\n");
	printf("Expected result: ");
	printf("%d", INVALID_AMOUNT);
	printf("\n");
	printf("Actual result: ");
	printf("%d", T2);
	printf("\n");


	printf("Test case 3:\n");
	object.transAmount = test3;
	EN_terminalError_t T3 = getTransactionAmount(&object);
	printf("Input Data: ");
	printf("%d", test3);
	printf("\n");
	printf("Expected result: ");
	printf("%d", INVALID_AMOUNT);
	printf("\n");
	printf("Actual result: ");
	printf("%d", T3);
	printf("\n");
}

void isBelowMaxAmountTest(void)
{
	char x[] = "Abdallah Ahmed Abbass\n";
	printf("Tester name: ");
	printf(x, "\n");
	printf("Function name: ");
	printf("getCardExpiryDate. \n");
	int test1 = 1000;
	int test2 = 200;
	int test3 = 50;
	ST_terminalData_t object{};
	printf("Test case 1:\n");
	object.transAmount = test1;
	object.maxTransAmount = 250;
	EN_terminalError_t T1 = isBelowMaxAmount(&object);
	printf("Input Data: ");
	printf("%d", test1);
	printf("\n");
	printf("Expected result: ");
	printf("%d", EXCEED_MAX_AMOUNT);
	printf("\n");
	printf("Actual result: ");
	printf("%d", T1);
	printf("\n");


	printf("Test case 2:\n");
	object.transAmount = test2;
	EN_terminalError_t T2 = isBelowMaxAmount(&object);
	printf("Input Data: ");
	printf("%d", test2);
	printf("\n");
	printf("Expected result: ");
	printf("%d", CARD_OK);
	printf("\n");
	printf("Actual result: ");
	printf("%d", T2);
	printf("\n");


	printf("Test case 3:\n");
	object.transAmount = test3;
	EN_terminalError_t T3 = isBelowMaxAmount(&object);
	printf("Input Data: ");
	printf("%d", test3);
	printf("\n");
	printf("Expected result: ");
	printf("%d", CARD_OK);
	printf("\n");
	printf("Actual result: ");
	printf("%d", T3);
	printf("\n");
}

void setMaxAmountTest(void)
{
	char x[] = "Abdallah Ahmed Abbass\n";
	printf("Tester name: ");
	printf(x, "\n");
	printf("Function name: ");
	printf("getCardExpiryDate. \n");
	int test1 = 1000;
	int test2 = 0;
	int test3 = -1;
	ST_terminalData_t object{};
	printf("Test case 1:\n");
	object.maxTransAmount = test1;
	EN_terminalError_t T1 = setMaxAmount(&object, test1);
	printf("Input Data: ");
	printf("%d", test1);
	printf("\n");
	printf("Expected result: ");
	printf("%d", CARD_OK);
	printf("\n");
	printf("Actual result: ");
	printf("%d", T1);
	printf("\n");


	printf("Test case 2:\n");
	object.maxTransAmount = test2;
	EN_terminalError_t T2 = setMaxAmount(&object, test2);
	printf("Input Data: ");
	printf("%d", test2);
	printf("\n");
	printf("Expected result: ");
	printf("%d", INVALID_MAX_AMOUNT);
	printf("\n");
	printf("Actual result: ");
	printf("%d", T2);
	printf("\n");


	printf("Test case 3:\n");
	object.maxTransAmount = test3;
	EN_terminalError_t T3 = setMaxAmount(&object, test3);
	printf("Input Data: ");
	printf("%d", test3);
	printf("\n");
	printf("Expected result: ");
	printf("%d", INVALID_MAX_AMOUNT);
	printf("\n");
	printf("Actual result: ");
	printf("%d", T3);
	printf("\n");
}

void isValidCardPANTest(void)
{
	char x[] = "Abdallah Ahmed Abbass\n";
	printf("Tester name: ");
	printf(x, "\n");
	printf("Function name: ");
	printf("getCardExpiryDate. \n");
	char test1[] = "33795135611087950000";
	char test2[] = "10000000000000000000";
	ST_cardData_t object{};
	printf("Test case 1:\n");
	for (int i = 0; i < (sizeof(test1) / sizeof(test1[0])); i++)
	{
		object.primaryAccountNumber[i] = test1[i];
	}
	EN_terminalError_t T1 = isValidCardPAN(&object);
	printf("Input Data: ");
	printf("%s", test1);
	printf("\n");
	printf("Expected result: ");
	printf("%d", TERMINAL_OK);
	printf("\n");
	printf("Actual result: ");
	printf("%d", T1);
	printf("\n");


	printf("Test case 2:\n");
	for (int i = 0; i < (sizeof(test2) / sizeof(test2[0])); i++)
	{
		object.primaryAccountNumber[i] = test2[i];
	}
	EN_terminalError_t T2 = isValidCardPAN(&object);
	printf("Input Data: ");
	printf("%s", test2);
	printf("\n");
	printf("Expected result: ");
	printf("%d", INVALID_CARD);
	printf("\n");
	printf("Actual result: ");
	printf("%d", T2);
	printf("\n");

}
