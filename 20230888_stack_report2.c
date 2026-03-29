#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

typedef struct{
    int data[MAX];
    int top;
} Stack;

void initStack(Stack *s){
    s->top = -1;
}

int isEmpty(Stack *s){
    return s->top == -1;
}

int isfull(Stack *s){
    return s->top == MAX -1;
}

void push(Stack *s, int value){
    if(isfull(s)){
        printf("Stack overflow! Cannot push %d\n", value);
        return;
    }
    s->data[++(s->top)] = value;
}

int pop(Stack *s){
    if (isEmpty(s)){
        printf("Stack underflow! Cannot pop\n");
        return -1;
    }
    return s->data[(s->top)--];
}

int peek(Stack *s){
    if(isEmpty(s)){
        printf("Stack is empty! Cannot peek\n");
        return -1;
    }
    return s->data[s->top]; 
}

void display(Stack *s){
    if(isEmpty(s)){
        printf("Stack is empty!\n");
        return;
    }
    printf("Stack contents: ");
    for(int i = 0; i <= s->top; i++){
        printf("%d", s->data[i]);
    }
    printf("\n");
}

int isMatching(char open, char close){
    if(open == '(' && close == ')') return 1;
    if(open == '[' && close == ']') return 1;
    if(open == '{' && close == '}') return 1;
    return 0;
}

int main(){
    Stack s;
    char str[MAX];
    initStack(&s);
    int isValid = 1;
    printf("문자열 입력: ");
    fgets(str, MAX, stdin);
    str[strcspn(str, "\n")] = '\0';
    
    
    for(int i=0;str[i] != '\0';i++){
        char ch = str[i];
        if(ch == '('|| ch == '[' || ch == '{'){
            push(&s, ch);
        }else if(ch == ')'|| ch == ']' || ch == '}'){
            if(isEmpty(&s) || !isMatching(pop(&s), ch)){
                isValid = 0;
                break;
            }
        }
    }
    if(!isEmpty(&s)) isValid = 0;
    
    if(isValid) printf("유효한 괄호\n");
    else printf("유효하지 않은 괄호\n");
    
    return 0;
}
