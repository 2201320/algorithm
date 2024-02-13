#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#pragma warning(disable:4996)

#define MAX_ARR_SIZE 30
#define MAX_VERTEX_SIZE 10
#define MAX_EDGE_SIZE 30

void gotoxy(int x, int y);

void init_scene();
int get_select();
void render_select_scene();

void render_sort();
void render_dfs();
void render_bfs();

void set_arr();
void set_graph();

void insertion_sort();
void selection_sort();
void bubble_sort();
void render_sort();
void heapify(int pos, int siz);
void heap_sort();
void quick_sort_sub(int left, int right);
void quick_sort();
void combine(int left, int mid, int right);
void merge(int left, int right);
void merge_sort();

void dfs();
void dfs_sub(int cur);

void bfs();
void bfs_queue_push(int val);
int bfs_queue_pop();
int bfs_queue_size();

int method_num, arr_size, mode_num; // render_select_scene() 참조
int delay_time; // 과정과 과정간 딜레이 시간

int arr[MAX_ARR_SIZE]; // 메인 배열
int prs_arr[(MAX_ARR_SIZE + 1) * (MAX_ARR_SIZE + 1)][MAX_ARR_SIZE]; // 과정 배열
int prs_size = 0; // 과정 배열의 과정 개수 (prs_arr의 행 개수)

typedef struct _Edge {
    int node1;
    int node2;
    int cost;
}Edge;

Edge edge_arr[MAX_EDGE_SIZE]; // 간선 정보
int edge_size = 0; // 간선 총 크기
int vertex_size = 0; // 노드 총 크기

int graph_arr[MAX_VERTEX_SIZE][MAX_VERTEX_SIZE] = { 0 };
int visit_vertex_arr[MAX_VERTEX_SIZE] = { 0 };

int dfs_result[MAX_VERTEX_SIZE] = { 0 };
int dfs_result_size = 0;

int bfs_result[MAX_VERTEX_SIZE] = { 0 };
int bfs_result_size = 0;
int bfs_queue[MAX_VERTEX_SIZE] = { 0 };
int bfs_queue_front = 0;
int bfs_queue_rear = 0;


void gotoxy(int x, int y) {
    COORD pos = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void init_scene() {
    printf("       .__                       .__  __  .__              \n");
    printf("_____  |  |    ____   ___________|__|/  |_|  |__   _____   \n");
    printf("\\__  \\ |  |   / ___\\ /  _ \\_  __ \\  \\   __\\  |  \\ /     \\ \n");
    printf(" / __ \\|  |__/ /_/  >  <_> )  | \\/  ||  | |   Y  \\  Y Y  \\ \n");
    printf("(____  /____/\\___  / \\____/|__|  |__||__| |___|  /__|_|  / \n");
    printf("     \\/     /_____/                            \\/      \\/  \n");
    printf("\n\n");
    printf("                아무 키나 눌러 실행하시오.                     \n");

    while (kbhit() != 1) {
        // nothing to do
        // https://m.blog.naver.com/sharonichoya/220875372940
        // 아무 키나 받을 시 넘어감
    }
    char key = getch(); // 입력 버퍼 비우기.

    system("cls"); // 터미널 창의 내용을 모두 지움
}

void render_select_scene() {
    while (1) {
        // 정렬 종류에 대한 정보 입력
        printf("어떤 정렬을 실행하겠습니까?\n");
        printf("1. 삽입정렬\n");
        printf("2. 선택정렬\n");
        printf("3. 버블정렬\n");
        printf("4. 힙 정렬\n");
        printf("5. 퀵 정렬\n");
        printf("6. 합병 정렬\n");
        printf("\n");
        printf("7. DFS\n");
        printf("8. BFS\n");
        printf("\n");
        printf("-1을 입력 시 프로그램이 종료됩니다.\n\n");

        // 알고리즘 종류 입력
        printf("알고리즘 번호: ");
        method_num = get_select();

        // 프로그램 종료 여부
        if (method_num == -1) {
            system("cls");
            exit(-1);
        }

        if (method_num >= 1 && method_num <= 6) {
            // 숫자 개수에 대한 정보 출력
            printf("\n\n");
            printf("숫자 개수 (1~30): ");

            // 숫자 개수 입력
            printf("number of numbers: ");
            arr_size = get_select();

            // 모드 종류에 대한 정보 출력
            // 빠른 출력은 딜레이 타임이 더 짧음
            printf("\n\n");
            printf("1. 순차 숫자, 빠른 출력\n");
            printf("2. 순차 숫자, 일반 출력\n");
            printf("3. 랜덤 숫자, 빠른 출력\n");
            printf("4. 랜덤 숫자, 일반 출력\n");
            // 모드 종류 입력
            printf("mode: ");
            mode_num = get_select();
        }
        else if (method_num >= 7) {
            // 모드 종류에 대한 정보 출력
            // 빠른 출력은 딜레이 타임이 더 짧음
            printf("\n\n");
            printf("1. 빠른 출력\n");
            printf("2. 일반 출력\n");
            // 모드 종류 입력
            printf("mode: ");
            mode_num = get_select();
        }


        // 입력이 제대로 되었는지 체크
        if (method_num < 1 || method_num > 8) {
            printf("\n\n Error with sort input");
            Sleep(3000); // 3000ms(3초) 기다림
            system("cls"); // 터미널 창의 내용을 모두 지움
            continue;
        }
        if (method_num >= 1 && method_num <= 6) {
            if (arr_size < 1 || arr_size > 30) {
                printf("\n\n Error with number of numbers");
                Sleep(3000); // 3000ms(3초) 기다림
                system("cls"); // 터미널 창의 내용을 모두 지움
                continue;
            }
            if (mode_num < 1 || mode_num > 4) {
                printf("\n\n Error with mode input");
                Sleep(3000); // 3000ms(3초) 기다림
                system("cls"); // 터미널 창의 내용을 모두 지움
                continue;
            }
        }
        else if (method_num >= 7 && method_num <= 8) {
            if (mode_num < 1 || mode_num > 2) {
                printf("\n\n Error with mode input");
                Sleep(3000); // 3000ms(3초) 기다림
                system("cls"); // 터미널 창의 내용을 모두 지움
                continue;
            }
        }

        // 모두 통과 시 아래 실행
        printf("\ninput okay. 3초 뒤에 실행합니다.");
        Sleep(3000);
        system("cls");
        break;
    }

}

int get_select() {
    int select_num;
    scanf("%d", &select_num);
    return select_num;
}

// 모드 종류, 숫자 개수를 바탕으로 arr 설정
void set_arr() {
    // arr의 원소를 모두 0으로 초기화
    // 더 빠른 건 memset 쓰는 게 더 빠름 (향후 할 수 있으면 해볼 것)
    for (int i = 0; i < MAX_ARR_SIZE; i++) {
        arr[i] = 0;
    }

    // prs_arr의 원소를 모두 0으로 초기화
    // 더 빠른 건 memset 쓰는 게 더 빠름 (향후 할 수 있으면 해볼 것)
    for (int i = 0; i < (MAX_ARR_SIZE + 1) * (MAX_ARR_SIZE + 1); i++) {
        for (int j = 0; j < MAX_ARR_SIZE; j++) {
            prs_arr[i][j] = 0;
        }
    }

    // 과정 배열의 크기를 0으로 세팅
    prs_size = 0;

    // arr 순차 배치
    if (mode_num == 1 || mode_num == 2) {
        for (int i = 0; i < arr_size; i++) {
            arr[i] = arr_size - i;
        }
    }

    // arr 랜덤 배치
    if (mode_num == 3 || mode_num == 4) {
        for (int i = 0; i < arr_size; i++) {
            arr[i] = rand() % (10 * MAX_ARR_SIZE);
        }
    }
}

// https://www.geeksforgeeks.org/prims-minimum-spanning-tree-mst-greedy-algo-5/
void set_graph() {
    edge_arr[0].node1 = 0; edge_arr[0].node2 = 1; edge_arr[0].cost = 4;
    edge_arr[1].node1 = 0; edge_arr[1].node2 = 7; edge_arr[1].cost = 8;
    edge_arr[2].node1 = 1; edge_arr[2].node2 = 2; edge_arr[2].cost = 8;
    edge_arr[3].node1 = 1; edge_arr[3].node2 = 7; edge_arr[3].cost = 11;
    edge_arr[4].node1 = 2; edge_arr[4].node2 = 3; edge_arr[4].cost = 7;
    edge_arr[5].node1 = 2; edge_arr[5].node2 = 5; edge_arr[5].cost = 4;
    edge_arr[6].node1 = 2; edge_arr[6].node2 = 8; edge_arr[6].cost = 2;
    edge_arr[7].node1 = 3; edge_arr[7].node2 = 4; edge_arr[7].cost = 9;
    edge_arr[8].node1 = 3; edge_arr[8].node2 = 5; edge_arr[8].cost = 14;
    edge_arr[9].node1 = 4; edge_arr[9].node2 = 5; edge_arr[9].cost = 10;
    edge_arr[10].node1 = 5; edge_arr[10].node2 = 6; edge_arr[10].cost = 2;
    edge_arr[11].node1 = 6; edge_arr[11].node2 = 7; edge_arr[11].cost = 1;
    edge_arr[12].node1 = 6; edge_arr[12].node2 = 8; edge_arr[12].cost = 6;
    edge_arr[13].node1 = 7; edge_arr[13].node2 = 8; edge_arr[13].cost = 7;

    vertex_size = 9;
    edge_size = 13;

    for (int i = 0; i < MAX_VERTEX_SIZE; i++) {
        for (int j = 0; j < MAX_VERTEX_SIZE; j++) {
            graph_arr[i][j] = 0;
        }
    }

    for (int i = 0; i < MAX_VERTEX_SIZE; i++) {
        visit_vertex_arr[i] = 0;
    }

    // dfs 관련 초기화
    for (int i = 0; i < MAX_VERTEX_SIZE; i++) {
        dfs_result[i] = 0;
    }
    dfs_result_size = 0;

    // bfs 관련 초기화
    for (int i = 0; i < MAX_VERTEX_SIZE; i++) {
        bfs_result[i] = 0;
    }
    bfs_result_size = 0;
    for (int i = 0; i < MAX_VERTEX_SIZE; i++) {
        bfs_queue[i] = 0;
    }
    bfs_queue_front = 0;
    bfs_queue_rear = 0;

    return;
}

void insertion_sort() {
    int i, j;
    for (i = 1; i < arr_size; i++) {
        int key = arr[i];
        for (j = i - 1; j >= 0; j--) {
            if (arr[j] < key) {
                break;
            }
            else {
                arr[j + 1] = arr[j];
            }
        }
        arr[j + 1] = key;

        // 중간 결과 기입 시작
        for (int j = 0; j < arr_size; j++) {
            prs_arr[prs_size][j] = arr[j];
        }
        prs_size++;
        // 중간 결과 기입 종료
    }
}

void selection_sort() {
    int i, j;
    for (i = 0; i < arr_size - 1; i++) {
        // 구간 최소값 탐색 시작
        int mini = 10000000;
        int mini_idx = 0;
        for (j = i + 1; j < arr_size; j++) {
            if (arr[j] < mini) {
                mini = arr[j];
                mini_idx = j;
            }
        }
        // 구간 최소값 탐색 종료

        // swap 시작
        int temp = arr[mini_idx];
        arr[mini_idx] = arr[i];
        arr[i] = temp;
        // swap 종료

        // 중간 결과 기입 시작
        for (int j = 0; j < arr_size; j++) {
            prs_arr[prs_size][j] = arr[j];
        }
        prs_size++;
        // 중간 결과 기입 종료
    }
}

void bubble_sort() {
    int i, j;
    for (i = arr_size - 1; i > 0; i--) {
        for (j = 0; j < i; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
        // 중간 결과 기입 시작
        for (int j = 0; j < arr_size; j++) {
            prs_arr[prs_size][j] = arr[j];
        }
        prs_size++;
        // 중간 결과 기입 종료
    }
}

void heapify(int pos, int siz) {
    int left = pos * 2 + 1;
    int right = pos * 2 + 2;
    int maxi = pos;
    if (left < siz && arr[left] > arr[maxi]) {
        maxi = left;
    }
    if (right < siz && arr[right] > arr[maxi]) {
        maxi = right;
    }
    if (maxi != pos) {
        int temp = arr[pos];
        arr[pos] = arr[maxi];
        arr[maxi] = temp;
        heapify(maxi, siz);
    }
}

void heap_sort() {
    // heap을 생성
    for (int i = arr_size / 2 - 1; i >= 0; i--) {
        heapify(i, arr_size);
    }

    for (int i = arr_size - 1; i >= 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(0, i);
        // 중간 결과 기입 시작
        for (int j = 0; j < arr_size; j++) {
            prs_arr[arr_size - i - 1][j] = arr[j];
        }
        prs_size++;
        // 중간 결과 기입 종료
    }
}

void quick_sort_sub(int left, int right) {
    int l = left;
    int r = right;
    int pivot = arr[(l + r) / 2];

    do {
        while (arr[l] < pivot) {
            l++;
        }
        while (arr[r] > pivot) {
            r--;
        }
        if (l <= r) {
            int temp = arr[l];
            arr[l] = arr[r];
            arr[r] = temp;
            l++;
            r--;
        }
    } while (l <= r);

    // 중간 결과 기입 시작
    for (int i = 0; i < arr_size; i++) {
        prs_arr[prs_size][i] = arr[i];
    }
    prs_size++;
    // 중간 결과 기입 종료

    if (left < r) {
        quick_sort_sub(left, r);
    }
    if (l < right) {
        quick_sort_sub(l, right);
    }
}

void quick_sort() {
    quick_sort_sub(0, arr_size - 1);
}

void combine(int left, int mid, int right) {
    int temp_arr[MAX_ARR_SIZE] = { 0 };
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp_arr[k] = arr[i];
            i++;
            k++;
        }
        else {
            temp_arr[k] = arr[j];
            k++;
            j++;
        }
    }

    if (i > mid) {
        for (j = j; j <= right; j++) {
            temp_arr[k] = arr[j];
            k++;
        }
    }
    else {
        for (i = i; i <= mid; i++) {
            temp_arr[k] = arr[i];
            k++;
        }
    }

    for (int x = left; x <= right; x++) {
        arr[x] = temp_arr[x];
    }
}

void merge(int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        merge(left, mid);
        merge(mid + 1, right);
        combine(left, mid, right);
    }

    // 중간 결과 기입 시작
    for (int i = 0; i < arr_size; i++) {
        prs_arr[prs_size][i] = arr[i];
    }
    prs_size++;
    // 중간 결과 기입 종료
}

void merge_sort() {
    merge(0, arr_size - 1);
}

void render_sort() {
    switch (method_num) {
    case 1:
        insertion_sort();
        printf("1. 삽입정렬 결과\n");
        break;
    case 2:
        selection_sort();
        printf("2. 선택정렬 결과\n");
        break;
    case 3:
        bubble_sort();
        printf("3. 버블정렬 결과\n");
        break;
    case 4:
        heap_sort();
        printf("4. 힙 정렬 결과\n");
    case 5:
        quick_sort();
        printf("5. 퀵 정렬 결과\n");
    case 6:
        merge_sort();
        printf("6. 머지 정렬 결과\n");
    default:
        break;
    }

    for (int i = 0; i < prs_size; i++) {
        for (int j = 0; j < arr_size; j++) {
            printf("%d ", prs_arr[i][j]);
        }
        printf("\n");
        // 빠른 실행
        if (mode_num == 1 || mode_num == 3) {
            Sleep(100);
        }
        // 일반 실행
        else if (mode_num == 2 || mode_num == 4) {
            Sleep(500);
        }
    }
    printf("\n\n아무 키나 눌러 종료하시오.\n");
    while (kbhit() != 1) {
        // nothing to do
        // https://m.blog.naver.com/sharonichoya/220875372940
        // 아무 키나 받을 시 넘어감
    }
    char key = getch(); // 입력 버퍼 비우기.

    system("cls"); // 터미널 창의 내용을 모두 지움
}

void dfs() {
    for (int i = 0; i < edge_size; i++) {
        graph_arr[edge_arr[i].node1][edge_arr[i].node2] = 1;
        graph_arr[edge_arr[i].node2][edge_arr[i].node1] = 1;
    }

    dfs_sub(0);
}

void dfs_sub(int cur) {
    visit_vertex_arr[cur] = 1;
    dfs_result[dfs_result_size] = cur;
    dfs_result_size++;
    for (int i = 0; i < vertex_size; i++) {
        if (graph_arr[cur][i] == 1 && visit_vertex_arr[i] == 0) {
            dfs_sub(i);
        }
    }
}

void render_dfs() {
    printf("그래프 정보\n\n");
    for (int i = 0; i < edge_size; i++) {
        printf("%d -- %d\n", edge_arr[i].node1, edge_arr[i].node2);
    }
    printf("\n\n");

    dfs();
    printf("7. DFS 결과: ");
    for (int i = 0; i < dfs_result_size; i++) {
        printf("%d ", dfs_result[i]);
        // 빠른 실행
        if (mode_num == 1) {
            Sleep(100);
        }
        // 일반 실행
        else if (mode_num == 2) {
            Sleep(500);
        }
    }
    printf("\n");

    printf("\n\n아무 키나 눌러 종료하시오.\n");
    while (kbhit() != 1) {
        // nothing to do
        // https://m.blog.naver.com/sharonichoya/220875372940
        // 아무 키나 받을 시 넘어감
    }
    char key = getch(); // 입력 버퍼 비우기.

    system("cls"); // 터미널 창의 내용을 모두 지움

}

void bfs() {
    for (int i = 0; i < edge_size; i++) {
        graph_arr[edge_arr[i].node1][edge_arr[i].node2] = 1;
        graph_arr[edge_arr[i].node2][edge_arr[i].node1] = 1;
    }

    bfs_queue_push(0);
    visit_vertex_arr[0] = 1;
    while (bfs_queue_size() > 0) {
        int top = bfs_queue_pop();
        if (top == -1) {
            break;
        }
        bfs_result[bfs_result_size] = top;
        bfs_result_size++;

        for (int i = 0; i < MAX_VERTEX_SIZE; i++) {
            if (visit_vertex_arr[i] == 0 && graph_arr[top][i] == 1) {
                visit_vertex_arr[i] = 1;
                bfs_queue_push(i);
            }
        }
    }
}

void bfs_queue_push(int val) {
    if (bfs_queue_front == (bfs_queue_rear + 1) % MAX_VERTEX_SIZE) {
        printf("overflow with queue!\n");
        exit(-1);
        return;
    }
    bfs_queue[bfs_queue_rear] = val;
    bfs_queue_rear = (bfs_queue_rear + 1) % MAX_VERTEX_SIZE;
}

int bfs_queue_pop() {
    if (bfs_queue_front == bfs_queue_rear) {
        return -1;
    }
    int ret_idx = bfs_queue_front;
    bfs_queue_front = (bfs_queue_front + 1) % MAX_VERTEX_SIZE;
    return bfs_queue[ret_idx];
}

int bfs_queue_size() {
    return (bfs_queue_rear - bfs_queue_front) % MAX_VERTEX_SIZE;
}

void render_bfs() {
    printf("그래프 정보\n\n");
    for (int i = 0; i < edge_size; i++) {
        printf("%d -- %d\n", edge_arr[i].node1, edge_arr[i].node2);
    }
    printf("\n\n");

    bfs();
    printf("8. BFS 결과: ");
    for (int i = 0; i < bfs_result_size; i++) {
        printf("%d ", bfs_result[i]);
        // 빠른 실행
        if (mode_num == 1) {
            Sleep(100);
        }
        // 일반 실행
        else if (mode_num == 2) {
            Sleep(500);
        }
    }
    printf("\n");

    printf("\n\n아무 키나 눌러 종료하시오.\n");
    while (kbhit() != 1) {
        // nothing to do
        // https://m.blog.naver.com/sharonichoya/220875372940
        // 아무 키나 받을 시 넘어감
    }
    char key = getch(); // 입력 버퍼 비우기.

    system("cls"); // 터미널 창의 내용을 모두 지움
}

int main() {
    init_scene();
    while (1) {
        render_select_scene();
        set_arr();
        set_graph();
        if (method_num >= 1 && method_num <= 6) {
            render_sort();
        }
        else if (method_num == 7) {
            render_dfs();
        }
        else if (method_num == 8) {
            render_bfs();
        }
    }
}