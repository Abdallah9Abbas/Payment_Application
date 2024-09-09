#include"Card.h"

EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	int i = 0;
	while (cardData->cardHolderName[i])
	{
		i++;
	}
	if (i > 24 || i < 20 || i==0)
	{
		printf("Wrong name!");
		return WRONG_NAME;
	}
	else
	{
		return CARD_OK;
	}

}

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
	int i = 0;
	int n = 0;
	while (cardData->cardExpirationDate[i])
	{
		i++;
	}
	if (i > 5 || i < 5 || i == 0)
	{
		printf("Wrong expirey date");
		return WRONG_EXP_DATE;
	}
	for (int i = 0; i < 2; i++)
	{
		if (cardData->cardExpirationDate[i] >= 48 && cardData->cardExpirationDate[i] <= 57)
		{
			n++;
		}
	}
	if (cardData->cardExpirationDate[2] == 47)
	{
		n++;
	}
	for (int i = 3; i < 5; i++)
	{
		if (cardData->cardExpirationDate[i] >= 48 && cardData->cardExpirationDate[i] <= 57)
		{
			n++;
		}
	}
	if (n == 5)
	{
		return CARD_OK;
	}
	else
	{
		printf("Wrong expirey date");
		return WRONG_EXP_DATE;
	}

}

EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	int i = 0;
	while (cardData->primaryAccountNumber[i])
	{
		i++;
	}
	//printf("%d", i);
	if (i > 19 || i < 16)
	{
		printf("Wrong PAN");
		return WRONG_PAN;
	}
	else
	{
		return CARD_OK;
	}
}

void getCardHolderNameTest(void)
{
	char x[] = "Abdallah Ahmed Abbass\n";
	printf("Tester name: ");
	printf(x,"\n");
	printf("Function name: ");
	printf("getCardHolderName. \n");
	char test1[] = "Abdallah Abbas Ramadan";	 
	char test2[] = "Abdallah";
	char test3[] = "Abdallah Abbas";
	ST_cardData_t object{};
	printf("Test case 1:\n");
	for (int i = 0; i < (sizeof(test1)/sizeof(test1[0])); i++)
	{
		object.cardHolderName[i] = test1[i];
	}
	EN_cardError_t T1 = getCardHolderName(&object);
	printf("Input Data: ");
	printf("%s",test1);
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
		object.cardHolderName[i] = test2[i];
	}
	EN_cardError_t T2 = getCardHolderName(&object);
	printf("Input Data: ");
	printf("%s", test2);
	printf("\n");
	printf("Expected result: ");
	printf("%d", WRONG_NAME);
	printf("\n");
	printf("Actual result: ");
	printf("%d", T2);
	printf("\n");


	printf("Test case 3:\n");
	for (int i = 0; i < (sizeof(test3) / sizeof(test3[0])); i++)
	{
		object.cardHolderName[i] = test3[i];
	}
	EN_cardError_t T3 = getCardHolderName(&object);
	printf("Input Data: ");
	printf("%s", test3);
	printf("\n");
	printf("Expected result: ");
	printf("%d", WRONG_NAME);
	printf("\n");
	printf("Actual result: ");
	printf("%d", T3);
	printf("\n");
}

void getCardPANTest(void)
{
	char x[] = "Abdallah Ahmed Abbass\n";
	printf("Tester name: ");
	printf(x, "\n");
	printf("Function name: ");
	printf("getCardPAN. \n");
	char test1[] = "012345678912345678";
	char test2[] = "01234567891234567892";
	char test3[] = "012345";
	ST_cardData_t object{};
	printf("Test case 1:\n");
	for (int i = 0; i < (sizeof(test1) / sizeof(test1[0])); i++)
	{
		object.primaryAccountNumber[i] = test1[i];
	}
	EN_cardError_t T1 = getCardPAN(&object);
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
		object.primaryAccountNumber[i] = test2[i];
	}
	EN_cardError_t T2 = getCardPAN(&object);
	printf("Input Data: ");
	printf("%s", test2);
	printf("\n");
	printf("Expected result: ");
	printf("%d", WRONG_PAN);
	printf("\n");
	printf("Actual result: ");
	printf("%d", T2);
	printf("\n");


	printf("Test case 3:\n");
	for (int i = 0; i < (sizeof(test3) / sizeof(test3[0])); i++)
	{
		object.primaryAccountNumber[i] = test3[i];
	}
	EN_cardError_t T3 = getCardPAN(&object);
	printf("Input Data: ");
	printf("%s", test3);
	printf("\n");
	printf("Expected result: ");
	printf("%d", WRONG_PAN);
	printf("\n");
	printf("Actual result: ");
	printf("%d", T3);
	printf("\n");
}




void getCardExpiryDateTest(void)
{
	char x[] = "Abdallah Ahmed Abbass\n";
	printf("Tester name: ");
	printf(x, "\n");
	printf("Function name: ");
	printf("getCardExpiryDate. \n");
	char test1[] = "11/22";
	char test2[] = "12312";
	char test3[] = "0123";
	ST_cardData_t object{};
	printf("Test case 1:\n");
	for (int i = 0; i < (sizeof(test1) / sizeof(test1[0])); i++)
	{
		object.cardExpirationDate[i] = test1[i];
	}
	EN_cardError_t T1 = getCardExpiryDate(&object);
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
		object.cardExpirationDate[i] = test2[i];
	}
	EN_cardError_t T2 = getCardExpiryDate(&object);
	printf("Input Data: ");
	printf("%s", test2);
	printf("\n");
	printf("Expected result: ");
	printf("%d", WRONG_EXP_DATE);
	printf("\n");
	printf("Actual result: ");
	printf("%d", T2);
	printf("\n");


	printf("Test case 3:\n");
	for (int i = 0; i < (sizeof(test3) / sizeof(test3[0])); i++)
	{
		object.cardExpirationDate[i] = test3[i];
	}
	EN_cardError_t T3 = getCardExpiryDate(&object);
	printf("Input Data: ");
	printf("%s", test3);
	printf("\n");
	printf("Expected result: ");
	printf("%d", WRONG_EXP_DATE);
	printf("\n");
	printf("Actual result: ");
	printf("%d", T3);
	printf("\n");
}


