//------In the name of God

#include<stdio.h>
#include<conio.h>
/////////////////////////////////////

struct bigNumber {
	int digits[1000];
	int count_of_digits;
	int sign;
};
/////////////////////////////////////
struct bigNumber input1(void);
struct bigNumber input2(void);
int len(char*);
struct bigNumber zero();
void showBigNumber(struct bigNumber);
int maximum(int,int);
int iszero(struct bigNumber);
struct bigNumber convertToBigNumber(char*);
int compare(struct bigNumber, struct bigNumber);
struct bigNumber SUM(struct bigNumber, struct bigNumber);
struct bigNumber sum_without_sign(struct bigNumber, struct bigNumber);
struct bigNumber subtraction_without_sign(struct bigNumber, struct bigNumber);
struct bigNumber SUBTRACT(struct bigNumber, struct bigNumber);
struct bigNumber MULTIPLICATION(struct bigNumber, struct bigNumber);
struct bigNumber DIVIDE(struct bigNumber, struct bigNumber);
struct bigNumber POWER(struct bigNumber, struct bigNumber);
struct bigNumber FACTORIAL(struct bigNumber);
struct bigNumber increment(struct bigNumber);
struct bigNumber decrement(struct bigNumber);

//////////////////////////////////////////
int main() {
	printf("Welcome ...\n");
while(1){
	int instruction;

	printf("please select your operation \n");

	printf("1) press number 1 for sum\n");
	printf("2) press number 2 for subtraction\n");
	printf("3) press number 3 for multiplication\n");
	printf("4) press number 4 for division \n");
	printf("5) press number 5 for power \n");
	printf("6) press number 6 for factorial \n");

	scanf("%d", &instruction);

	struct bigNumber result;

	if (instruction == 1) {
		struct bigNumber num1 =input1();
		struct bigNumber num2 =input2();
		result = SUM(num1, num2);
	}

	if (instruction == 2) {
		struct bigNumber num1 =input1();
		struct bigNumber num2 =input2();
		result = SUBTRACT(num1, num2);
	}

	if (instruction == 3) {
		struct bigNumber num1 =input1();
		struct bigNumber num2 =input2();
		result = MULTIPLICATION(num1, num2);
	}

	if (instruction == 4) {
		struct bigNumber num1 =input1();
		struct bigNumber num2 =input2();
		result = DIVIDE(num1, num2);
	}
	if (instruction == 5) {
		struct bigNumber num1 =input1();
		struct bigNumber num2 =input2();
		result = POWER(num1, num2);
	}

	if (instruction == 6) {
		struct bigNumber num1 =input1();
		result = FACTORIAL(num1);

	}

	printf("result = ");
	showBigNumber(result);
}
	getch();
	return 0;
}

///////////////////////////////////////////
struct bigNumber input1(void){

	char number1[1000];

	printf("please enter number #1\n");
	scanf("%s", number1);
	struct bigNumber num1 = convertToBigNumber(number1);
	return num1;
}
struct bigNumber input2(void){

	char number2[1000];

	printf("please enter number #2\n");
	scanf("%s", number2);
	struct bigNumber num2 = convertToBigNumber(number2);
	return num2;
}

///////////////////////////////////////////
int len(char *a) {
	int l = 0;
	while (a[l] != '\0')
		l++;
	return l;
}
/////////////////////////////////////
int maximum(int a, int b) {
	if (a > b)
		return a;
	return b;
}
/////////////////////////////////////
struct bigNumber convertToBigNumber(char *number) {
	struct bigNumber result;
	int start_position =0;
	if(number[0]=='-'){
		result.sign = -1;
		start_position =1;
		result.count_of_digits = len(number)-1;
	}
	else if (number[0]=='+'){
		start_position =1;
		result.sign = 1;
		result.count_of_digits = len(number) -1;	
	}
	else{
		start_position =0;
		result.sign = 1;
		result.count_of_digits = len(number);	
	}

	int i=0;
	for (i = 0; i < result.count_of_digits ; i++)
		result.digits[i] = number[(result.count_of_digits+start_position) -i-1 ] - 48;

	return result;
}
/////////////////////////////////////

int iszero(struct bigNumber num) {
	int i;
	for (i = 0; i < num.count_of_digits; i++)
		if (num.digits[i] != 0)
			return 0;
	return 1;
}
/////////////////////////////////////
//without sign
int compare(struct bigNumber num1, struct bigNumber num2) {
	int i;
	if (num1.count_of_digits == num2.count_of_digits)
		for (i = 0; i < num1.count_of_digits; i++) {
			if (num1.digits[i] > num2.digits[i])
				return 1;
			if (num1.digits[i] < num2.digits[i])
				return -1;
		}
		if (num1.count_of_digits > num2.count_of_digits)
			return 1;
		if (num1.count_of_digits < num2.count_of_digits)
			return -1;
		return 0;
}
/////////////////////////////////////

void showBigNumber(struct bigNumber num) {
	int i;

	if (num.sign == -1)
		printf("-");

	for (i = num.count_of_digits - 1; i > -1; i--)
		printf("%d", num.digits[i]);

	printf("\n");
}
/////////////////////////////////////
//without sign
struct bigNumber increment(struct bigNumber num) {
	struct bigNumber result;
	result.count_of_digits = num.count_of_digits;
	int i, carry = 1;
	for (i = 0; i < num.count_of_digits; i++) {
		result.digits[i] = (num.digits[i] + carry) % 10;
		carry = (num.digits[i]  + carry) / 10;
	}
	if (carry > 0) {
		result.digits[i] = carry;
		result.count_of_digits++;
	}
	return result;
}
/////////////////////////////////////
//without sign
struct bigNumber decrement(struct bigNumber num) {
	struct bigNumber result;
	result.count_of_digits = num.count_of_digits;
	result.sign=1;

	int i;
	int carry = -1;
	if (iszero(num) == 1) {
		for (i = 0; i < num.count_of_digits; i++) {
			result.digits[i] = 0;
		}
	} else {
		for (i = 0; i < num.count_of_digits; i++) {
			result.digits[i] = num.digits[i] + carry;
			if (result.digits[i] < 0) {
				carry = -1;
				result.digits[i] += 10;
			} //end of if
			else {
				carry = 0;
			}
		} //end of for
	}

	if (result.digits[result.count_of_digits-1] ==0){
		result.count_of_digits--;
		if(result.count_of_digits==0)
			result=zero();
		return result;
	}


	return result;
}
///////////////////////////////////
//without sign
struct bigNumber sum_without_sign(struct bigNumber n1, struct bigNumber n2) {
	struct bigNumber result;

	int carry = 0;
	int i = 0, a, b;
	int temp = 0;
	int max = maximum(n1.count_of_digits, n2.count_of_digits);

	while (i < max) {

		if (i >= n1.count_of_digits)
			a = 0;
		else
			a = n1.digits[i];

		if (i >= n2.count_of_digits)
			b = 0;
		else
			b = n2.digits[i];
		temp = carry + a + b;
		carry = temp / 10;
		result.digits[i] = temp % 10;
		i++;
	} //end of while

	if (carry > 0) {
		result.digits[i] = carry;
		result.count_of_digits = max + 1;
	} else 
		result.count_of_digits = max;
	result.sign=1;
	return result;	
}
/////////////////////////////////////////////
struct bigNumber zero()
{
	struct bigNumber result;
	result.count_of_digits =1;
	result.digits[0] =0;
	return result;
}
//without sign
struct bigNumber subtraction_without_sign(struct bigNumber n1, struct bigNumber n2) {

	if (compare(n1, n2) ==0)
		return zero();

	struct bigNumber result;
	int carry = 0;
	int countDigit = 0;

	int temp = 0;
	int i =0;
	int a =0;
	int b=0;
	int max = maximum(n1.count_of_digits, n2.count_of_digits);
	while (i < max) {
		if (i >= n1.count_of_digits)
			a = 0;
		else
			a = n1.digits[i];

		if (i >= n2.count_of_digits)
			b = 0;
		else
			b = n2.digits[i];

		temp = carry + a - b;

		if (temp < 0) {
			temp += 10;
			carry = -1;
		} else {
			carry = 0;
		}
		result.digits[i] = temp % 10;
		if (result.digits[i] != 0) {
			countDigit = i + 1;
		}
		i++;
	} //end of while

	result.count_of_digits = countDigit;
	result.sign=1;
	return result;

}
////////////////////////////////////////////////
struct bigNumber SUM(struct bigNumber n1, struct bigNumber n2){
	struct bigNumber result;
	int c=compare(n1,n2);

	if(n1.sign==-1 && n2.sign==-1){
		result=sum_without_sign(n1,n2);
		result.sign=-1;
	}
	if(n1.sign== 1 && n2.sign== 1){
		result=sum_without_sign(n1,n2);
		result.sign=1;
	}
	if(n1.sign==-1 && n2.sign==1){

		if(c==1){
			result=subtraction_without_sign(n1,n2);
			result.sign=-1;
		}

		if(c==0){
			result=zero();
		}
		if(c==-1){
			result=subtraction_without_sign(n2,n1);
			result.sign=1;
		}
	}
	if(n1.sign== 1 && n2.sign==-1){

		if(c==1){
			result=subtraction_without_sign(n1,n2);
			result.sign=1;
		}

		if(c==0){
			result=zero();
		}
		if(c==-1){
			result=subtraction_without_sign(n2,n1);
			result.sign=-1;
		}
	}
	return result;
}
/////////////////////////////////////////////////////
struct bigNumber SUBTRACT(struct bigNumber n1, struct bigNumber n2){
	struct bigNumber result;
	int c=compare(n1,n2);

	if(n1.sign==-1 && n2.sign==1){
		result=sum_without_sign(n1,n2);
		result.sign=-1;
	}
	if(n1.sign== 1 && n2.sign==-1){
		result=sum_without_sign(n1,n2);
		result.sign=1;
	}
	if(n1.sign==-1 && n2.sign==-1){

		if(c==1){
			result=subtraction_without_sign(n1,n2);
			result.sign=-1;
		}

		if(c==0){
			result=zero();
		}
		if(c==-1){
			result=subtraction_without_sign(n2,n1);
			result.sign=1;
		}
	}
	if(n1.sign== 1 && n2.sign== 1){

		if(c==1){
			result=subtraction_without_sign(n1,n2);
			result.sign=1;
		}

		if(c==0){
			result=zero();
		}
		if(c==-1){
			result=subtraction_without_sign(n2,n1);
			result.sign=-1;
		}
	}
	return result;
}
/////////////////////////////////////////////////////////////

struct bigNumber MULTIPLICATION(struct bigNumber n1, struct bigNumber n2) {
	struct bigNumber r;
	r.count_of_digits = n1.count_of_digits;

	int s=0;
	if((n1.sign==1 && n2.sign==1) || (n1.sign==-1 && n2.sign==-1))
		s=1;
	else
		s=-1;

	int i;
	for (i = 0; i < n1.count_of_digits; i++)
		r.digits[i] = 0;

	while (iszero(n2) == 0) {
		r = sum_without_sign(r, n1);
		n2 = decrement(n2);
	} // end of while
	r.sign=s;
	return r;

}
///////////////////////////////

struct bigNumber DIVIDE(struct bigNumber n1, struct bigNumber n2) {

	struct bigNumber r;
	r.count_of_digits = n1.count_of_digits;

	int i;

	if (compare(n1, n2) == -1) {
		r=zero();
		return r;
	}
	if (compare(n1, n2) == 0) {
		for (i = 0; i < n1.count_of_digits; i++)
			r.digits[i] = 1;
		r.count_of_digits = 1;
		return r;
	}
	if (compare(n1, n2) == 1) {
		if((n1.sign==1 && n2.sign==1) || (n1.sign==-1 && n2.sign==-1)){
			r=zero();
			while (compare(n1, n2) != -1) {
				n1 = subtraction_without_sign(n1, n2);
				r = increment(r);
			} // end of while
			r.sign=1;
			return r;
		} //end of if
		else{
			
		//	for (i = 0; i < n1.count_of_digits; i++)
		//		r.digits[i] = 0;
			r=zero();
			while (compare(n1, n2) != -1) {
				n1 = subtraction_without_sign(n1, n2);
				r = increment(r);
			} // end of while
			r.sign=-1;
			return r;
		} //end of else
	}


}
//////////////////////////////////

struct bigNumber POWER(struct bigNumber n1, struct bigNumber n2) {
	struct bigNumber r;
	r.sign=1;
	r = n1;
	n2 = decrement(n2);
	while (iszero(n2) == 0) {
		r = MULTIPLICATION(r, n1);
		n2 = decrement(n2);
	}
	return r;
}
/////////////////////////////////////
struct bigNumber FACTORIAL(struct bigNumber n) {
	struct bigNumber r;
	r = n;
	int i;
	if (iszero(n) == 1) {
		for (i = 0; i < n.count_of_digits; i++)
			r.digits[i] = 1;
		r.count_of_digits = 1;
	}

	n = decrement(n);
	while (iszero(n) == 0) {
		r = MULTIPLICATION(r, n);
		n = decrement(n);
	}

	return r;
}