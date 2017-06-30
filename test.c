#include <stdio.h>
#include <string.h>

int main(void) {
	char swag[20] = {'\0'};
	fgets(swag, 20, stdin);
	printf("%s", swag);
	printf("%d", *swag);
}