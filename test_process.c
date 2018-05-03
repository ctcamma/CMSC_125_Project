/**

 	Modified by: Christian T. Camma
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

void inputPrompt(){							// main menu function
	printf(">> ");
}

int isNumber(char word[]){
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

int arithFunction(char* arr[100], int size){
	float sum,diff,product,quotient,power,base;
	int modulo;
	int n=2,index=0,number;
	if(size==1){
		printf("expected argument after %s\n",arr[0]);
		return 0;
	}else{
		if(isNumber(arr[1])==1){
			printf("operation for command is not specified\n");
			return 0;
		}else{
			if(strcmp(arr[1],"-add")==0){					// addition operation
				if(checkSize(size)==1){
					sum=atof(arr[n]);
					n++;
					while(n<size){
						if(isNumber(arr[n])==0){
							printf("expected number data type in operand %d\n",(n-1));
							return 0;
						}
						sum+=atof(arr[n]);
						n++;
					}
					if(sum-(int)sum==0){
						number = (int)sum;
						printf("%d\n",number);
					}else{
						printf("%f\n",sum);	
					}
					return sum;
				}else if(checkSize(size)==2){
					printf("expected at least 2 operands\n");
					return 0;
				}else{
					printf("expected arguments after %s\n",arr[1]);
					return 0;
				}
				
			}else if(strcmp(arr[1],"-sub")==0){				// subtraction operation
				if(checkSize(size)==1){
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
				}else if(checkSize(size)==2){
					printf("expected at least 2 operands\n");
					return 0;
				}else{
					printf("expected arguments after %s\n",arr[1]);
					return 0;
				}
			}else if(strcmp(arr[1],"-mul")==0){				// multiplication operation
				if(checkSize(size)==1){
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
				}else if(checkSize(size)==2){
					printf("expected at least 2 operands\n");
					return 0;
				}else{
					printf("expected arguments after %s\n",arr[1]);
					return 0;
				}
			}else if(strcmp(arr[1],"-div")==0){				// division operation
				if(checkSize(size)==1){
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
					power=atof(arr[size-1]);
					base=atof(arr[size-2]);
					n=size-2;
					while(n>=2){
						if(isIntNumber(arr[n])==0){
							printf("expected number data type in operand %d\n",(n-1));
							return 0;
						}
						power=pow(base,power);
						base=atof(arr[n]);
						printf("%f\n",power);
						n--;
					}
					if(power-(int)power==0){
						number = (int)power;
						printf("%d\n",number);
					}else{
						printf("%f\n",power);	
					}
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
		}else{
			printf("%s: command not found\n",argsArr[0]);
		}
		inputPrompt();
		getchar();
		scanf("%[^\n]s", command);
	}
	printf("program terminated\n");
}
		