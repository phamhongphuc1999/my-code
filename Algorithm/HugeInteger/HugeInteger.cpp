#include "HugeInteger.h"

string AddHugeInteger(string num1, string num2) {
	int len1 = num1.length(), len2 = num2.length();
	while (len1 < len2) {
		num1 = '0' + num1;
		len1++;
	}
	while (len1 > len2) {
		num2 = '0' + num2;
		len2++;
	}
	string result = "";
	int memory = 0, sum;
	len1--;
	while (len1 >= 0) {
		sum = (num1[len1] - '0') + (num2[len1] - '0') + memory;
		if (sum > 10) memory = 1;
		else memory = 0;
		result = (char)(sum % 10 + '0') + result;
		len1--;
	}
	if (memory == 1) return '1' + result;
	return result;
}

string AddHugeInteger(string nums[], int size, int maxLength) {
	for (int i = 0; i < size; i++)
		while (nums[i].length() < maxLength)
			nums[i] = '0' + nums[i];
	string result = "";
	int index = maxLength - 1, memory = 0, sum;
	while (index >= 0) {
		sum = 0;
		for (int i = 0; i < size; i++) sum += memory + nums[i][index] - '0';
		memory = sum / 10;
		result = (char)(sum % 10 + '0') + result;
	}
	int temp = 0;
	while ((temp = memory % 10) > 0) result = (char)(temp + '0') + result;
	return result;
}

string SubtractInteger(string num1, string num2) {
	int len1 = num1.length(), len2 = num2.length();
	while (len1 < len2) {
		num1 = '0' + num1;
		len1++;
	}
	while (len2 < len1) {
		num2 = '0' + num2;
		len2++;
	}
	string result = "";
	int memory = 0, subtract;
	len1--;
	while (len1 >= 0) {
		int c1 = num1[len1] - '0';
		int c2 = num2[len1] - '0';
		subtract = c1 - c2 - memory;
		memory = 0;
		if (subtract < 0) {
			subtract += 10;
			memory = 1;
		}
		result = (char)(memory + '0') + result;
	}
	if (memory == 1) {
		int temp = 10 - (result[0] - '0');
		result[0] = (char)(temp + '0');
		result = '-' + result;
	}
	return result;
}
