#include <stdio.h>
#include <stdlib.h>
#include <time.h>


double calculateAverage(int scores[], int size);
int getStudentScore(int scores[], int size, int studentNumber);
void printScore(int scores[], int size, double average, int option);


int main() {
    int scores[30];
    int studentNumber;
    double average;

    srand(time(0));

    for (int i = 0; i < 30; i++) {
        scores[i] = rand() % 101;
    }

    average = calculateAverage(scores, 30);
    printf("학급 평균 점수: %.2f\n", average);

    printf("학생 번호를 입력하세요 (1 ~ 30): ");
    scanf("%d", &studentNumber);

    int score = getStudentScore(scores, 30, studentNumber);
    if (score != -1) {
        printf("%d번 학생의 점수: %d\n", studentNumber, score);
    } else {
        printf("유효하지 않은 학생 번호입니다.\n");
    }
    
    printScore(scores, 30, average, 0);
    printScore(scores, 30, average, 1);
    printScore(scores, 30, average, 2);
    
    return 0;
}

// 평균 계산 함수
double calculateAverage(int scores[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += scores[i];
    }
    return sum / (double)size;
}

// 특정 학생 점수 검색 함수
int getStudentScore(int scores[], int size, int studentNumber) {
    if (studentNumber >= 1 && studentNumber <= size) {
        return scores[studentNumber - 1];
    } else {
        return -1; // 유효하지 않은 학생 번호
    }
}

// 학생 성적 출력 함수
void printScore(int scores[], int size, double average, int option) {
    switch(option){
        case 0:
            for(int i = 0; i < size; i++){
                printf("학생번호: %d, 점수 %d\n", i+1, scores[i]);
            }
            break;
        case 1:
            printf("평균이상 학생\n");
            for(int i = 0; i < size; i++){
                if(scores[i] >= average) printf("학생번호 : %d, 점수 %d\n", i+1, scores[i]);
            }
            break;
        case 2:
            printf("평균미만 학생\n");
            for(int i = 0; i < size; i++){
                if(scores[i] < average) printf("학생번호 : %d, 점수 %d\n", i+1, scores[i]);
            }
            break;
        default:
            printf("유효하지 않은 옵션입니다. \n");
            break;
            
    }  
    
    
    
}