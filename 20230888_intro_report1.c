#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int scores[10];
    int sum = 0;
    float average;

    srand(time(NULL));

    for (int i = 0; i < 10; i++) {
        scores[i] = rand() % 101;
        sum += scores[i];
        printf("학생 %d의 성적: %d\n", i+1, scores[i]);
    }

    average = (float)sum / 10;

    printf("전체 학생의 합계: %d\n", sum);
    printf("전체 학생의 평균 점수: %.2f\n", average);

    return 0;
}
