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

int method_num, arr_size, mode_num; // render_select_scene() ����
int delay_time; // ������ ������ ������ �ð�

int arr[MAX_ARR_SIZE]; // ���� �迭
int prs_arr[(MAX_ARR_SIZE + 1) * (MAX_ARR_SIZE + 1)][MAX_ARR_SIZE]; // ���� �迭
int prs_size = 0; // ���� �迭�� ���� ���� (prs_arr�� �� ����)

typedef struct _Edge {
    int node1;
    int node2;
    int cost;
}Edge;

Edge edge_arr[MAX_EDGE_SIZE]; // ���� ����
int edge_size = 0; // ���� �� ũ��
int vertex_size = 0; // ��� �� ũ��

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
    printf("                �ƹ� Ű�� ���� �����Ͻÿ�.                     \n");

    while (kbhit() != 1) {
        // nothing to do
        // https://m.blog.naver.com/sharonichoya/220875372940
        // �ƹ� Ű�� ���� �� �Ѿ
    }
    char key = getch(); // �Է� ���� ����.

    system("cls"); // �͹̳� â�� ������ ��� ����
}

void render_select_scene() {
    while (1) {
        // ���� ������ ���� ���� �Է�
        printf("� ������ �����ϰڽ��ϱ�?\n");
        printf("1. ��������\n");
        printf("2. ��������\n");
        printf("3. ��������\n");
        printf("4. �� ����\n");
        printf("5. �� ����\n");
        printf("6. �պ� ����\n");
        printf("\n");
        printf("7. DFS\n");
        printf("8. BFS\n");
        printf("\n");
        printf("-1�� �Է� �� ���α׷��� ����˴ϴ�.\n\n");

        // �˰��� ���� �Է�
        printf("�˰��� ��ȣ: ");
        method_num = get_select();

        // ���α׷� ���� ����
        if (method_num == -1) {
            system("cls");
            exit(-1);
        }

        if (method_num >= 1 && method_num <= 6) {
            // ���� ������ ���� ���� ���
            printf("\n\n");
            printf("���� ���� (1~30): ");

            // ���� ���� �Է�
            printf("number of numbers: ");
            arr_size = get_select();

            // ��� ������ ���� ���� ���
            // ���� ����� ������ Ÿ���� �� ª��
            printf("\n\n");
            printf("1. ���� ����, ���� ���\n");
            printf("2. ���� ����, �Ϲ� ���\n");
            printf("3. ���� ����, ���� ���\n");
            printf("4. ���� ����, �Ϲ� ���\n");
            // ��� ���� �Է�
            printf("mode: ");
            mode_num = get_select();
        }
        else if (method_num >= 7) {
            // ��� ������ ���� ���� ���
            // ���� ����� ������ Ÿ���� �� ª��
            printf("\n\n");
            printf("1. ���� ���\n");
            printf("2. �Ϲ� ���\n");
            // ��� ���� �Է�
            printf("mode: ");
            mode_num = get_select();
        }


        // �Է��� ����� �Ǿ����� üũ
        if (method_num < 1 || method_num > 8) {
            printf("\n\n Error with sort input");
            Sleep(3000); // 3000ms(3��) ��ٸ�
            system("cls"); // �͹̳� â�� ������ ��� ����
            continue;
        }
        if (method_num >= 1 && method_num <= 6) {
            if (arr_size < 1 || arr_size > 30) {
                printf("\n\n Error with number of numbers");
                Sleep(3000); // 3000ms(3��) ��ٸ�
                system("cls"); // �͹̳� â�� ������ ��� ����
                continue;
            }
            if (mode_num < 1 || mode_num > 4) {
                printf("\n\n Error with mode input");
                Sleep(3000); // 3000ms(3��) ��ٸ�
                system("cls"); // �͹̳� â�� ������ ��� ����
                continue;
            }
        }
        else if (method_num >= 7 && method_num <= 8) {
            if (mode_num < 1 || mode_num > 2) {
                printf("\n\n Error with mode input");
                Sleep(3000); // 3000ms(3��) ��ٸ�
                system("cls"); // �͹̳� â�� ������ ��� ����
                continue;
            }
        }

        // ��� ��� �� �Ʒ� ����
        printf("\ninput okay. 3�� �ڿ� �����մϴ�.");
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

// ��� ����, ���� ������ �������� arr ����
void set_arr() {
    // arr�� ���Ҹ� ��� 0���� �ʱ�ȭ
    // �� ���� �� memset ���� �� �� ���� (���� �� �� ������ �غ� ��)
    for (int i = 0; i < MAX_ARR_SIZE; i++) {
        arr[i] = 0;
    }

    // prs_arr�� ���Ҹ� ��� 0���� �ʱ�ȭ
    // �� ���� �� memset ���� �� �� ���� (���� �� �� ������ �غ� ��)
    for (int i = 0; i < (MAX_ARR_SIZE + 1) * (MAX_ARR_SIZE + 1); i++) {
        for (int j = 0; j < MAX_ARR_SIZE; j++) {
            prs_arr[i][j] = 0;
        }
    }

    // ���� �迭�� ũ�⸦ 0���� ����
    prs_size = 0;

    // arr ���� ��ġ
    if (mode_num == 1 || mode_num == 2) {
        for (int i = 0; i < arr_size; i++) {
            arr[i] = arr_size - i;
        }
    }

    // arr ���� ��ġ
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

    // dfs ���� �ʱ�ȭ
    for (int i = 0; i < MAX_VERTEX_SIZE; i++) {
        dfs_result[i] = 0;
    }
    dfs_result_size = 0;

    // bfs ���� �ʱ�ȭ
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

        // �߰� ��� ���� ����
        for (int j = 0; j < arr_size; j++) {
            prs_arr[prs_size][j] = arr[j];
        }
        prs_size++;
        // �߰� ��� ���� ����
    }
}

void selection_sort() {
    int i, j;
    for (i = 0; i < arr_size - 1; i++) {
        // ���� �ּҰ� Ž�� ����
        int mini = 10000000;
        int mini_idx = 0;
        for (j = i + 1; j < arr_size; j++) {
            if (arr[j] < mini) {
                mini = arr[j];
                mini_idx = j;
            }
        }
        // ���� �ּҰ� Ž�� ����

        // swap ����
        int temp = arr[mini_idx];
        arr[mini_idx] = arr[i];
        arr[i] = temp;
        // swap ����

        // �߰� ��� ���� ����
        for (int j = 0; j < arr_size; j++) {
            prs_arr[prs_size][j] = arr[j];
        }
        prs_size++;
        // �߰� ��� ���� ����
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
        // �߰� ��� ���� ����
        for (int j = 0; j < arr_size; j++) {
            prs_arr[prs_size][j] = arr[j];
        }
        prs_size++;
        // �߰� ��� ���� ����
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
    // heap�� ����
    for (int i = arr_size / 2 - 1; i >= 0; i--) {
        heapify(i, arr_size);
    }

    for (int i = arr_size - 1; i >= 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(0, i);
        // �߰� ��� ���� ����
        for (int j = 0; j < arr_size; j++) {
            prs_arr[arr_size - i - 1][j] = arr[j];
        }
        prs_size++;
        // �߰� ��� ���� ����
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

    // �߰� ��� ���� ����
    for (int i = 0; i < arr_size; i++) {
        prs_arr[prs_size][i] = arr[i];
    }
    prs_size++;
    // �߰� ��� ���� ����

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

    // �߰� ��� ���� ����
    for (int i = 0; i < arr_size; i++) {
        prs_arr[prs_size][i] = arr[i];
    }
    prs_size++;
    // �߰� ��� ���� ����
}

void merge_sort() {
    merge(0, arr_size - 1);
}

void render_sort() {
    switch (method_num) {
    case 1:
        insertion_sort();
        printf("1. �������� ���\n");
        break;
    case 2:
        selection_sort();
        printf("2. �������� ���\n");
        break;
    case 3:
        bubble_sort();
        printf("3. �������� ���\n");
        break;
    case 4:
        heap_sort();
        printf("4. �� ���� ���\n");
    case 5:
        quick_sort();
        printf("5. �� ���� ���\n");
    case 6:
        merge_sort();
        printf("6. ���� ���� ���\n");
    default:
        break;
    }

    for (int i = 0; i < prs_size; i++) {
        for (int j = 0; j < arr_size; j++) {
            printf("%d ", prs_arr[i][j]);
        }
        printf("\n");
        // ���� ����
        if (mode_num == 1 || mode_num == 3) {
            Sleep(100);
        }
        // �Ϲ� ����
        else if (mode_num == 2 || mode_num == 4) {
            Sleep(500);
        }
    }
    printf("\n\n�ƹ� Ű�� ���� �����Ͻÿ�.\n");
    while (kbhit() != 1) {
        // nothing to do
        // https://m.blog.naver.com/sharonichoya/220875372940
        // �ƹ� Ű�� ���� �� �Ѿ
    }
    char key = getch(); // �Է� ���� ����.

    system("cls"); // �͹̳� â�� ������ ��� ����
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
    printf("�׷��� ����\n\n");
    for (int i = 0; i < edge_size; i++) {
        printf("%d -- %d\n", edge_arr[i].node1, edge_arr[i].node2);
    }
    printf("\n\n");

    dfs();
    printf("7. DFS ���: ");
    for (int i = 0; i < dfs_result_size; i++) {
        printf("%d ", dfs_result[i]);
        // ���� ����
        if (mode_num == 1) {
            Sleep(100);
        }
        // �Ϲ� ����
        else if (mode_num == 2) {
            Sleep(500);
        }
    }
    printf("\n");

    printf("\n\n�ƹ� Ű�� ���� �����Ͻÿ�.\n");
    while (kbhit() != 1) {
        // nothing to do
        // https://m.blog.naver.com/sharonichoya/220875372940
        // �ƹ� Ű�� ���� �� �Ѿ
    }
    char key = getch(); // �Է� ���� ����.

    system("cls"); // �͹̳� â�� ������ ��� ����

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
    printf("�׷��� ����\n\n");
    for (int i = 0; i < edge_size; i++) {
        printf("%d -- %d\n", edge_arr[i].node1, edge_arr[i].node2);
    }
    printf("\n\n");

    bfs();
    printf("8. BFS ���: ");
    for (int i = 0; i < bfs_result_size; i++) {
        printf("%d ", bfs_result[i]);
        // ���� ����
        if (mode_num == 1) {
            Sleep(100);
        }
        // �Ϲ� ����
        else if (mode_num == 2) {
            Sleep(500);
        }
    }
    printf("\n");

    printf("\n\n�ƹ� Ű�� ���� �����Ͻÿ�.\n");
    while (kbhit() != 1) {
        // nothing to do
        // https://m.blog.naver.com/sharonichoya/220875372940
        // �ƹ� Ű�� ���� �� �Ѿ
    }
    char key = getch(); // �Է� ���� ����.

    system("cls"); // �͹̳� â�� ������ ��� ����
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