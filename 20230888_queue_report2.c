#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define SIZE 10

typedef struct{
    char documentName[50];
    int numPages;
} JobList;

typedef struct{
    JobList queue[SIZE];
    int front;
    int rear;
} PrintQueue;

void initQueue(PrintQueue *q){
    q->front = 0;
    q->rear = 0;
}

bool isEmpty(PrintQueue *q){
    return q->front == q->rear;
}

bool isFull(PrintQueue *q){
    return (q->rear + 1) % SIZE == q->front;
}

bool enqueue(PrintQueue *q, char *documentName, int numPages){
    // 1. 페이지 수 50장 제한 조건 추가 (큐에 추가되기 전 거부)
    if (numPages > 50) {
        printf("페이지 수가 50장을 초과했습니다. 작업 '%s'을(를) 추가할 수 없습니다.\n", documentName);
        return false;
    }

    if(isFull(q)){
        printf("대기열이 가득 찼습니다. 작업을 추가할 수 없습니다.\n");
        return false;
    }
    
    strcpy(q->queue[q->rear].documentName, documentName);
    q->queue[q->rear].numPages = numPages;
    q->rear = (q->rear + 1) % SIZE;
    
    // 오타 수정: %S -> %s
    printf("작업 '%s' (%d 페이지)가 대기열에 추가되었습니다.\n", documentName, numPages);
    return true;
}

JobList dequeue(PrintQueue *q){
    if(isEmpty(q)){
        printf("대기열이 비어 있습니다. 작업이 없습니다.\n");
        JobList emptyJob = {"", 0};
        return emptyJob;
    }
    JobList job = q->queue[q->front];
    q->front = (q->front + 1) % SIZE;
    return job;
}

// 2. 인쇄 취소 기능 추가
void cancelJob(PrintQueue *q, char *documentName) {
    if(isEmpty(q)){
        printf("대기열이 비어 있습니다. 취소할 문서가 없습니다.\n");
        return;
    }

    int current = q->front;
    int foundIndex = -1;
    int numElements = (q->rear - q->front + SIZE) % SIZE;

    // 대기열에서 문서 찾기
    for (int i = 0; i < numElements; i++) {
        if (strcmp(q->queue[current].documentName, documentName) == 0) {
            foundIndex = current;
            break;
        }
        current = (current + 1) % SIZE;
    }

    if (foundIndex == -1) {
        printf("해당 문서가 없습니다.\n");
        return;
    }

    // 문서가 존재하면, 해당 위치 뒤의 작업들을 한 칸씩 앞으로 이동
    int shiftCurrent = foundIndex;
    int shiftNext = (shiftCurrent + 1) % SIZE;

    while (shiftNext != q->rear) {
        q->queue[shiftCurrent] = q->queue[shiftNext];
        shiftCurrent = shiftNext;
        shiftNext = (shiftNext + 1) % SIZE;
    }

    // rear 위치 업데이트
    q->rear = shiftCurrent;
    printf("작업 '%s'이(가) 대기열에서 취소되었습니다.\n", documentName);
}

// 3. 대기열 전체 비우기 기능 추가
void clearQueue(PrintQueue *q) {
    initQueue(q); // front와 rear를 0으로 되돌려 초기화
    printf("대기열 초기화\n");
}

// 함수명 중복 에러 방지를 위해 PrintQueue -> displayQueue로 변경
void displayQueue(PrintQueue *q){
    if(isEmpty(q)){
        printf("대기열이 비어 있습니다.\n");
        return;
    }
    printf("현재 대기 중인 작업:\n");
    int i = q->front;
    while(i != q->rear){
        printf("- %s (%d 페이지)\n", q->queue[i].documentName, q->queue[i].numPages);
        i = (i + 1) % SIZE;
    }
}

int main(){
    PrintQueue q;
    initQueue(&q);
    
    int choice;
    char documentName[50];
    int numPages;
    
    while(true){
        printf("\n1. 작업 추가\n2. 작업 처리\n3. 대기열 출력\n4. 인쇄 취소\n5. 대기열 비우기\n6. 종료\n선택: ");
        scanf("%d", &choice);
        
        switch(choice){
            case 1:
                printf("문서 이름: ");
                scanf("%s", documentName);
                printf("페이지 수: ");
                scanf("%d", &numPages);
                enqueue(&q, documentName, numPages);
                break;
            case 2:
                {
                    JobList job = dequeue(&q);
                    if(strlen(job.documentName) > 0){
                        printf("작업 '%s' (%d 페이지)를 처리 중입니다...\n", job.documentName, job.numPages);
                    }
                }
                break;
            case 3:
                displayQueue(&q);
                break;
            case 4:
                // 인쇄 취소 메뉴 연결
                printf("취소할 문서 이름: ");
                scanf("%s", documentName);
                cancelJob(&q, documentName);
                break;
            case 5:
                // 대기열 비우기 메뉴 연결
                clearQueue(&q);
                break;
            case 6:
                printf("프로그램을 종료합니다.\n");
                return 0;
            default:
                printf("잘못된 입력입니다. 다시 선택해 주세요.\n");
                break;
        }
    }
    return 0;
}