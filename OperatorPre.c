#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#define MAX 1001

char input[MAX];
int Tinput=-1;
char sym[MAX];
int Tsym=-1;

int matrix[6][6]={//矩阵 大于1 小于-1 等于0 出错-2 
	/*1*/ 1,-1,-1,-1, 1, 1,
	/*2*/ 1, 1,-1,-1, 1, 1,
	/*3*/ 1, 1,-2,-2, 1, 1,
	/*4*/-1,-1,-1,-1, 0,-2,
	/*5*/ 1, 1,-2,-2, 1, 1,
	/*6*/-1,-1,-1,-1,-2,-2};
int is_zhongjie(char a){
	if(a=='+'||a=='*'||a=='i'||a=='('||a==')'||a=='#'){
		return 1;
	}
	else{
		return 0;
	}
}
char first_sym(){//符号表从右往左第一个终结符 
	int tem=Tsym;
	while(!is_zhongjie(sym[tem])){
		tem--;
	}
	return sym[tem];
}
int find(char a){//返回这个终结符在矩阵中的位置 
	if(a=='+'){
		return 0;
	}
	else if(a=='*'){
		return 1;
	}
	else if(a=='i'){
		return 2;
	}
	else if(a=='('){
		return 3;
	}
	else if(a==')'){
		return 4;
	}
	else if(a=='#'){
		return 5;
	}
	else{
		return -1;
	}
}
//void pushinput(char a){//push 可能要改 
//	if(Tinput=MAX-1){
//		printf("error:input stack is full.\n");
//		return;
//	}
//	else if(Tinput>=MAX){
//		printf("error:input stack is overfull.\n");
//		return;
//	}
//	else{
//		input[++Tinput]=a;
//		return;
//	}
//}
char popinput(){//pop 可能要改 
	char tmp=input[Tinput];
	if(tmp=='#'){
		printf("error: first of input is #.\n");
		return '#';
	}
	Tinput++;
	return tmp;
}
void pushsym(char a){
	if(Tsym==MAX-1){
		printf("error: sym stack is full.\n");
		return;
	}
	else if(Tsym>=MAX){
		printf("error: sym stack is overfull.\n");
		return ;
	}
	else{
		sym[++Tsym]=a;
//		printf("压栈:%c.\n",a);
		return;
	}
}
char popsym(){
	char tmp;
	if(Tsym<0){
		printf("error: sym stack is empty.\n");
		return ;
	}
	tmp=sym[Tsym];
	if(tmp=='#'){
		printf("error: first of sym is #.\n");
		return '#';
	}
	sym[Tsym]='\0';
	Tsym--;
	return tmp;
}
int de_compare(){
	return matrix[find(first_sym())][find(input[Tinput])];
}
void plus_statute(){
	if(sym[Tsym-1]=='+'&&sym[Tsym]=='E'&&sym[Tsym-2]=='E'){
		popsym();
		popsym();
		popsym();
		pushsym('E');
	}
	else{
//		printf("规约出错.\n");
		printf("RE\n");
		exit(0); 
//		return ;
	}
}
void mul_statute(){
	if(sym[Tsym-1]=='*'&&sym[Tsym]=='E'&&sym[Tsym-2]=='E'){
		popsym();
		popsym();
		popsym();
		pushsym('E');
	}
	else{
//		printf("规约出错.\n");
		printf("RE\n");
		exit(0);
//		return ;
	}
}
void right_statute(){
	if(sym[Tsym-1]=='E'&&sym[Tsym]==')'&&sym[Tsym-2]=='('){
		popsym();
		popsym();
		popsym();
		pushsym('E');
	}
	else{
//		printf("规约出错.\n");
		printf("RE\n");
		exit(0);
//		return ;
	}
}
void i_statute(){
	if(sym[Tsym]=='i'){
		popsym();
		pushsym('E');
	}
	else{
//		printf("规约出错.\n");
		printf("RE\n");
		exit(0);
//		return ;
	}
}
void move_in(){
//	printf("移进\n");
	char tmp=popinput();
	if(tmp=='#'){
		printf("error: first of input is #.\n");
		return;
	}
	pushsym(tmp);
//	printf("压栈: %c.\n",tmp);
	printf("I%c\n",tmp);
	return ;
}
void statute(){
//	printf("规约\n");
	if(first_sym()=='+'){
		plus_statute();
		printf("R\n");
	}
	else if(first_sym()=='*'){
		mul_statute();
		printf("R\n");
	}
	else if(first_sym()==')'){
		right_statute();
		printf("R\n");
	}
	else if(first_sym()=='i'){
		i_statute();
		printf("R\n");
	}
	else if(first_sym()=='#'){
		printf("first of sym[] is #,but it still statute.\n");
	}
	else{
		printf("error: unknown char.\n");
	}
}
int main(int argc, char* argv[]){
	int i, j;
	char ch;
	
//	FILE *file=fopen("ceshi.txt","r");
	FILE *file=fopen(argv[1],"r");
	if(file==NULL){
		printf("open error!\n");
		return 0;
	}
	fgets(input, MAX,file);
//	printf("%s\n", input);
//	printf("input's length is %d byte.\n", strlen(input));
	input[strlen(input)]='\0';
	input[strlen(input)-1]='#';
//	printf("%s\n", input);
//	printf("input's length is %d byte.\n", strlen(input));
	Tinput=0;
	
	sym[0]='#';
	Tsym=0;
//	printf("%d", de_compare());
	while(1){
		if(first_sym()=='#'&&input[Tinput]=='#'){
//			printf("Accept!");
			break;
		}
	if(de_compare()==-2){
//			printf("error:E\n");
			printf("E\n");
			break;
		}
		
		if(de_compare()==-1||de_compare()==0){//等于或者小于就 移进 
			move_in(); 
		}
		else if(de_compare()==1){//大于就 规约 
			statute(); 
		}
	}
	
	
	
	
	fclose(file); 
	
	return 0;
}
