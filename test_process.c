/**

 	Modified by: Christian T. Camma, Jonah B. Catindig
 	Section: CMSC 125 T-2L
 **/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>		// package for letting dynamic number of arguments in parameter passing
#include <sys/wait.h> 	//includes the prototype for the wait() function

typedef struct history{
	char inputCommand[100];
	struct history *next;
}HIST;

void inputPrompt(){							// main menu function
	printf(">> ");
}

void commandLog(char* arr[100]){

}

int modeIsNumber(char word[]){
	int length = strlen(word);
	int index,decimalPointNum=0;
	for(index=0;index<length;index++){
		if((isdigit(word[index])==0 && word[index]!='.')||(word[index]=='.' && decimalPointNum!=0)){		// if the element is not a number
			return 0;	
		}else if(word[index]=='.' && decimalPointNum==0){													// accepts a decimal point character for floating-point numbers
			decimalPointNum++;
		}
	}
	return 1;
}

int isNumber(char word[]){
	int length = strlen(word);
	int index,decimalPointNum=0;
	for(index=0;index<length;index++){
		if(word[0]=='-'){
		}else if((isdigit(word[index])==0 && word[index]!='.')||(word[index]=='.' && decimalPointNum!=0)){		// if the element is not a number
			return 0;	
		}else if(word[index]=='.' && decimalPointNum==0){													// accepts a decimal point character for floating-point numbers
			decimalPointNum++;
		}
	}
	return 1;
}

int isIntNumber(char word[]){
	int length = strlen(word);
	int index;
	for(index=0;index<length;index++){
		if(isdigit(word[index])==0){		// if the element is not an integer
			return 0;
		}
	}
	return 1;
}

int checkSize(int size){					// checks the input if it has an appropriate length for operations and its corresponding operands
	if(size==2){
		return 0;
	}else if(size==3){
		return 2;
	}else{
		return 1;
	}
}

float addition(char* arr[100], int size){
	int number,n=2;
	float sum=0;
	while(n<size){
		if(isNumber(arr[n])==0){
			printf("expected number data type in operand %d\n",(n-1));
			return 0;
		}
		else{
			sum+=atof(arr[n]);
		}
		n++;
	}
	if(sum-(int)sum==0){
		number = (int)sum;
		printf("%d\n",number);
	}else{
		printf("%f\n",sum);	
	}
	return sum;
}

float subtraction(char* arr[100], int size){
	int number,n=2;
	float diff;
	diff=atof(arr[n]);
	n++;
	while(n<size){
		if(isNumber(arr[n])==0){
			printf("expected number data type in operand %d\n",(n-1));
			return 0;
		}
		diff-=atof(arr[n]);
		n++;
	}
	if(diff-(int)diff==0){
		number = (int)diff;
		printf("%d\n",number);
	}else{
		printf("%f\n",diff);	
	}
	return diff;
}

float multiplication(char* arr[100], int size){
	int number,n=2;
	float product;
	product=atof(arr[n]);
	n++;
	while(n<size){
		if(isNumber(arr[n])==0){
			printf("expected number data type in operand %d\n",(n-1));
			return 0;
		}
		product=product*atof(arr[n]);
		n++;
	}
	if(product-(int)product==0){
		number = (int)product;
		printf("%d\n",number);
	}else{
		printf("%f\n",product);	
	}
	return product;
}

float division(char* arr[100], int size){
	int number,n=2;
	float quotient;
	quotient=atof(arr[n]);
	n++;
	while(n<size){
		if(isNumber(arr[n])==0){
			printf("expected number data type in operand %d\n",(n-1));
			return 0;
		}
		quotient=quotient/atof(arr[n]);
		n++;
	}
	if(quotient-(int)quotient==0){
		number = (int)quotient;
		printf("%d\n",number);
	}else{
		printf("%f\n",quotient);	
	}
	return quotient;
}

float exponentiation(char* arr[100], int size){
	int number,n=2;
	double power,base;
	power=atof(arr[size-1]);
	base=atof(arr[size-2]);
	n=size-2;
	while(n>=2){
		if(isNumber(arr[n])==0){
			printf("expected number data type in operand %d\n",(n-1));
			return 0;
		}
		power=pow(base,power);
		base=atof(arr[n]);
		if(base<0){
			power=power-(power*2);
		}
		n--;
	}
	if(power-(long int)power==0){
		number = (int)power;	
		printf("%d\n",number);
	}else{
		printf("%f\n",power);	
	}
	return power;
}

int modulo(char* arr[100], int size){
	int modulo,number,n=2;
	modulo=atoi(arr[n]);
	n++;
	while(n<size){
		if(isIntNumber(arr[n])==0){
			printf("expected integer data type in operand %d\n",(n-1));
			return 0;
		}
		modulo=modulo%atoi(arr[n]);
		n++;
	}
	if(modulo-(int)modulo==0){
		number = (int)modulo;
		printf("%d\n",number);
	}else{
		printf("%d\n",modulo);	
	}
	return modulo;
}

float mean(char* arr[100], int size){
	int n = 2;
	int number = 2;
	float meanAns;
	float sum = 0;
	while(n < size){
		if(isNumber(arr[n]) == 0){
			printf("expected number data type in operand %d\n",(n - 1));
			return 0;
		}
		else{
			sum += atof(arr[n]);
		}
		n++;
	}
	meanAns = sum / (size - 2);
	if(meanAns - (int) meanAns == 0){
		number = (int) meanAns;
		printf("%d\n", number);
	}
	else{
		meanAns = sum / (size - 2);
		printf("%f\n", meanAns);
	}
	return meanAns;
}

float median(char* arr[100], int size){
	int medArrSize = size - 2;
	float medArr[medArrSize];
	float temp = (float) medArrSize / 2;
	float medAns = 0;
	int number;
	int middle = 0;
	int i, j;
	int n = 2;
	
	n++;
	while (n < size){
		if(isNumber(arr[n])==0){
			printf("expected number data type in operand %d\n",(n - 1));
			return 0;
		}
		n++;
	}

	for (i = 0; i < medArrSize; i++){
		medArr[i] = atof(arr[i + 2]);
	}

	if (temp - (int) temp > 0){
		middle = (int) temp;
	} 
	else{
		middle = (int) temp - 1;
	}

	for (i = 0; i < medArrSize; i++){
		for (j = i + 1; j < medArrSize; j++){
			if (medArr[i] > medArr[j] && j < size - 2){
				temp = medArr[i];
				medArr[i] = medArr[j];
				medArr[j] = temp;
			}
		}
	}
	if (medArrSize % 2 == 1){
		medAns = medArr[middle];
	}
	else{
		medAns = (medArr[middle] + medArr[middle + 1]) / 2;
	}
	
	if (medAns - (int) medAns == 0){
		number = (int) medAns;
		printf("%d\n", number);
	}
	else{
		printf("%f\n", medAns);
	}

	return medArr[middle];
}

float mode(char* arr[], int size){
	int modArrSize = size - 2;
	float modArr[modArrSize];
	float medAns = 0;
	int number;
	int middle = 0;
	int i, j;
	int n = 2;
	float modAns = 0;
	int maxCount = 0;

	n++;
	while (n < size){
		if(isNumber(arr[n])==0){
			printf("expected number data type in operand %d\n",(n - 1));
			return 0;
		}
		n++;
	}

	for (i = 0; i < modArrSize; i++){
		modArr[i] = atof(arr[i + 2]);
	}

	for (i = 0; i < modArrSize; i++) {
	    int count = 0;
	    for (j = 0; j < modArrSize; j++){
	       	if (modArr[j] == modArr[i]){
	       		count = count + 1;
	   		}
	    }
	    if (count > maxCount) {
	       	maxCount = count;
	       	modAns = modArr[i];
	    }
   	}

   	if (maxCount == 1){
   		printf("No mode.\n");
   	}

   	else{
   		if (modAns - (int) modAns == 0){
			number = (int) modAns;
			printf("%d\n", number);
		}
		else{
			printf("%f\n", modAns);
		}
   	}
   	return modAns;
}

int arithFunction(char* arr[100], int size){
	float answer;
	int answerMod;
	int number;
	if(size==1){
		printf("expected argument after %s\n",arr[0]);
		return 0;
	}else{
		if(modeIsNumber(arr[1])==1){
			printf("operation for command is not specified\n");
			return 0;
		}else{
			if(strcmp(arr[1],"-add")==0){					// addition operation
				if(checkSize(size)==1){
					answer=addition(arr,size);
					return 0;
				}else if(checkSize(size)==2){
					printf("expected at least 2 operands\n");
					return 0;
				}else{
					printf("expected arguments after %s\n",arr[1]);
					return 0;
				}
				
			}else if(strcmp(arr[1],"-sub")==0){				// subtraction operation
				if(checkSize(size)==1){
					answer=subtraction(arr,size);
					return 0;
				}else if(checkSize(size)==2){
					printf("expected at least 2 operands\n");
					return 0;
				}else{
					printf("expected arguments after %s\n",arr[1]);
					return 0;
				}
			}else if(strcmp(arr[1],"-mul")==0){				// multiplication operation
				if(checkSize(size)==1){
					answer=multiplication(arr,size);
					return 0;
				}else if(checkSize(size)==2){
					printf("expected at least 2 operands\n");
					return 0;
				}else{
					printf("expected arguments after %s\n",arr[1]);
					return 0;
				}
			}else if(strcmp(arr[1],"-div")==0){				// division operation
				if(checkSize(size)==1){
					answer=division(arr,size);
					return 0;
				}else if(checkSize(size)==2){
					printf("expected at least 2 operands\n");
					return 0;
				}else{
					printf("expected arguments after %s\n",arr[1]);
					return 0;
				}
			}else if(strcmp(arr[1],"-pow")==0){				// modulo operation
				if(checkSize(size)==1){
					answer=exponentiation(arr,size);
					return 0;
				}else if(checkSize(size)==2){
					printf("expected at least 2 operands\n");
					return 0;
				}else{
					printf("expected arguments after %s\n",arr[1]);
					return 0;
				}
			}else if(strcmp(arr[1],"-mod")==0){				// modulo operation
				if(checkSize(size)==1){
					answerMod=modulo(arr,size);
					return 0;
				}else if(checkSize(size)==2){
					printf("expected at least 2 operands\n");
					return 0;
				}else{
					printf("expected arguments after %s\n",arr[1]);
					return 0;
				}
			}else{
				printf("%s: mode of operation not found\n",arr[1]);
				return 0;
			}
		}
	}
}

int statFunction(char* arr[100], int size){
	float answer;
	int n=2,index=0,number;
	if(size==1){
		printf("expected argument after %s\n",arr[0]);
		return 0;
	}else{
		if(modeIsNumber(arr[1])==1){
			printf("operation for command is not specified\n");
			return 0;
		}else{
			if(strcmp(arr[1],"-mn")==0||strcmp(arr[1],"-mean")==0){					// addition operation
				if(checkSize(size)==1){
					answer = mean(arr, size);
					return 0;
				}else if(checkSize(size)==2){
					printf("expected at least 2 operands\n");
					return 0;
				}else{
					printf("expected arguments after %s\n",arr[1]);
					return 0;
				}
				
			}else if(strcmp(arr[1],"-md")==0||strcmp(arr[1],"-median")==0){	
				if(checkSize(size)==1){
					answer = median(arr, size);
					return 0;
				}else if(checkSize(size)==2){
					printf("expected at least 2 operands\n");
					return 0;
				}else{
					printf("expected arguments after %s\n",arr[1]);
					return 0;
				}
				
			}else if(strcmp(arr[1],"-mo")==0||strcmp(arr[1],"-mode")==0){					// addition operation
				if(checkSize(size)==1){
					answer = mode(arr, size);
					return 0;
				}else if(checkSize(size)==2){
					printf("expected at least 2 operands\n");
					return 0;
				}else{
					printf("expected arguments after %s\n",arr[1]);
					return 0;
				}
				
			}else{
				printf("%s: mode of operation not found\n",arr[1]);
				return 0;
			}
		}
	}
}

int main()
{
	pid_t pid1, checker; 
	int i=0, flag = 0, numOfArgs = 0,index=0;
	char command[100],tempCommand[100];									// variable for input string
	char *tempArg;
	char* initCommand[5] = {"","","","",NULL};
	char* command4[5] = {"","","","",NULL};
	char* com;

	inputPrompt();
	scanf("%[^\n]s", command);
	while(strcmp(command,"quit")!=0 && strcmp(command,"q")!=0 && strcmp(command,"exit")!=0){
		checker = wait(NULL); //the wait() function returns the PID of the terminated child.
		strcpy(tempCommand,command);
		int size=0;
		com = strtok(command," ");
		while(com != NULL){
			com = strtok(NULL," ");
			size++;
		}
		char* argsArr[100];
		i=0;
		argsArr[i] = strtok(tempCommand," ");
		while(argsArr[i]!=NULL){
			argsArr[++i]=strtok(NULL," ");
		}
		if(strcmp(argsArr[0],"arith")==0){
			int num = arithFunction(argsArr,size);
		}else if(strcmp(argsArr[0],"stat")==0){
			int num = statFunction(argsArr,size);
		}else{
			printf("%s: command not found\n",argsArr[0]);
		}
		inputPrompt();
		getchar();
		scanf("%[^\n]s", command);
	}
	printf("program terminated\n");
}
		