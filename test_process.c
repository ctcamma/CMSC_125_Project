/**

 	Modified by: 
 		Christian T. Camma
 		Jonah B. Catindig
 	Section: CMSC 125 T-2L

	Project Description: 
		The program behaves like a terminal/command prompt that accepts
	the following commands:
		arith <mode> <arguments>
		stat <mode> <arguments>
		min <argument/s>
		max <argument/s>
	which returns specific values that each commands represents.

	constraints:
		there is no default mode for arith and stat commands
		arguments only accepts numbers
		arith commands allows a minimum number of 2 arguments
 **/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>		// package for letting dynamic number of arguments in parameter passing
#include <sys/wait.h> 	//includes the prototype for the wait() function
#define RESET "\033[0m"
#define RED "\033[31m"

typedef struct history{
	char inputCommand[100];
	int commandCount;
	int valid;
	struct history *next;
}HIST;

void inputPrompt(){							// main menu function
	printf(">> ");
}

// void commandLog(HIST *head, ){
// 	HIST *temp;
// 	temp = head;					//temp points to whatever head ois pointing to
// 	while (temp->next != NULL){
// 		temp = temp->next;
// 	}
// 	temp->next = malloc(sizeof(single));	//memory allocation
// 	printf("Enter a number: ");
// 	scanf("%d", &temp->next->num);
// 	temp->next->next = NULL;		//marks the end of the linked list

// 	printf("Ouput: ");
// 	temp = head;					//temp points again to whatever head is pointing to
// 	while (temp != NULL){
// 		printf("%d ", temp->num);	//prints the output
// 		temp = temp->next;			//proceeds to the next node
// 	}
// 	printf("\n");
// }

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

int addition(char* arr[100], int size){
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
	return 1;
}

int subtraction(char* arr[100], int size){
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
	return 1;
}

int multiplication(char* arr[100], int size){
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
	return 1;
}

int division(char* arr[100], int size){
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
	return 1;
}

int exponentiation(char* arr[100], int size){
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
	return 1;
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
	return 1;
}

int mean(char* arr[100], int size){
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
	return 1;
}

int median(char* arr[100], int size){
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

	return 1;
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
	if(size==3){									// if the input has one operand, it will be the mode
		if(isNumber(arr[2])==0){
			printf("expected number data type in operand 1\n");
			return 0;
		}else{
			modAns=atof(arr[2]);
		   	if (modAns - (int) modAns == 0){
				number = (int) modAns;
				printf("%d\n", number);
			}
			else{
				printf("%f\n", modAns);
			}
			return 1;
		} 
	}else{
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
	   		printf("No mode\n");
	   		return 0;
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
	   	return 1;
	}
}

int arithFunction(char* arr[100], int size){
	int answer;
	int answerMod;
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
					return answer;
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
					return answer;
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
					return answer;
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
					return answer;
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
					return answer;
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
					return answer;
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
	int answer;
	if(size==1){
		printf("expected argument after %s\n",arr[0]);
		return 0;
	}else{
		if(modeIsNumber(arr[1])==1){
			printf("operation for command is not specified\n");
			return 0;
		}else{
			if(strcmp(arr[1],"-mn")==0||strcmp(arr[1],"-mean")==0){					// addition operation
				if(size>2){
					answer = mean(arr, size);
					return answer;
				}else{
					printf("expected arguments after %s\n",arr[1]);
					return 0;
				}
				
			}else if(strcmp(arr[1],"-md")==0||strcmp(arr[1],"-median")==0){	
				if(size>2){
					answer = median(arr, size);
					return answer;
				}else{
					printf("expected arguments after %s\n",arr[1]);
					return 0;
				}
				
			}else if(strcmp(arr[1],"-mo")==0||strcmp(arr[1],"-mode")==0){					// addition operation
				if(size>2){
					answer = mode(arr, size);
					return answer;
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

float minimum(char* arr[100], int size){
	int number,n=1;
	float min=19999998;
	while(n<size){
		if(isNumber(arr[n])==0){
			printf("expected number data type in operand %d\n",(n));
			return 0;
		}
		else{
			if(atof(arr[n])<min){
				min=atof(arr[n]);
			}
		}
		n++;
	}
	if(min-(int)min==0){
		number = (int)min;
		printf("%d\n",number);
	}else{
		printf("%f\n",min);	
	}
	return 1;
}

int maximum(char* arr[100], int size){
	int number,n=1;
	float max=-19999998;
	while(n<size){
		if(isNumber(arr[n])==0){
			printf("expected number data type in operand %d\n",(n));
			return 0;
		}
		else{
			if(atof(arr[n])>max){
				max=atof(arr[n]);
			}
		}
		n++;
	}
	if(max-(int)max==0){
		number = (int)max;
		printf("%d\n",number);
	}else{
		printf("%f\n",max);	
	}
	return 1;
}

int minFunction(char* arr[100], int size){
	int number;
	if(size==1){
		printf("expected argument after %s\n",arr[0]);
		return 0;
	}else{
		number = minimum(arr,size);
		return number;
	}
}

int maxFunction(char* arr[100], int size){
	int number;
	if(size==1){
		printf("expected argument after %s\n",arr[0]);
		return 0;
	}else{
		number = maximum(arr,size);
		return 1;
	}
}

int viewHistory(HIST *head, HIST *tail){
	HIST *temp;
	temp = head;
	while (temp != NULL){
		if(temp->valid==1){
			printf("%d. %s\n", temp->commandCount, temp->inputCommand);
			temp = temp->next;
		}else{
			printf("%d.",temp->commandCount);
			printf(RED" %s\n" RESET, temp->inputCommand);
			temp = temp->next;
		}		
	}
}

int main()
{
	pid_t pid1, checker; 
	int i=0, flag = 0, numOfArgs = 0,index=0;
	char command[100],tempCommand[100],commandToHistory[100];
	char* com;
	int count = 0,valid=0,skipCommandHistory=0;
	HIST *head = NULL, *tail;

	inputPrompt();
	strcpy(command,"");
	scanf("%[^\n]s", command);
	
	while(strcmp(command,"quit")!=0 && strcmp(command,"q")!=0 && strcmp(command,"exit")!=0){
		pid1 = fork();	
		if (pid1 > 0){
			checker = wait(NULL); 						//the wait() function returns the PID of the terminated child.
		}
		else if (pid1 == 0){
			if(strcmp(command,"")==0){					// if there is no input command
				printf("Expected command\n");
				skipCommandHistory=1;
				valid=0;
			}else{										// user input command
				skipCommandHistory=0;
				strcpy(tempCommand,command);
				strcpy(commandToHistory,command);
				int size=0;
				com = strtok(command," ");				// transfers each word in command to array of string separated by space character
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
				if(strcmp(argsArr[0],"arith")==0){				// arithmetic command
					valid = arithFunction(argsArr,size);
				}else if(strcmp(argsArr[0],"stat")==0){			// statistics command
					valid = statFunction(argsArr,size);
				}else if(strcmp(argsArr[0],"min")==0){			// minimum command
					valid = minFunction(argsArr,size);
				}else if(strcmp(argsArr[0],"max")==0){			// maximum command
					valid = maxFunction(argsArr,size);
				}else if(strcmp(argsArr[0], "history") == 0){
					viewHistory(head, tail);
					valid=1;
				}else if(strcmp(argsArr[0], "cut") == 0){
					strcpy(argsArr[0], "mv");
					execvp(argsArr[0], argsArr);
					pid1 = 0;
				}else if(strcmp(argsArr[0], "cat") == 0){
					execvp(argsArr[0], argsArr);
					pid1 = 0;
				}else{											// input command is not supported by the program
					printf("%s: Command not found\n",argsArr[0]);
					valid=0;
				}
			}

			if(count==0 && skipCommandHistory==0){
				if (head == NULL){		//creates a head node
					head = malloc(sizeof(HIST));
					strcpy(head->inputCommand, commandToHistory);
					head->commandCount = count + 1;
					head->valid=valid;
					head->next = NULL;
					count = count + 1;
				}
			}
			else if (count >= 1 && skipCommandHistory==0){
				HIST *temp = head;
				while (temp->next != NULL){
					temp = temp->next;
				}
				temp->next = malloc(sizeof(HIST));
				strcpy(temp->next->inputCommand, commandToHistory);
				temp->next->commandCount = count + 1;
				temp->next->valid = valid;
				temp->next->next = NULL;

				count = count + 1;
			}
			inputPrompt();
			getchar();
			strcpy(command,"");							// update command value to empty string
			scanf("%[^\n]s", command);					// accepts new command
		}
	}
	printf("Program terminated\n");
}
		