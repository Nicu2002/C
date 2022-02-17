#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void menu(int n, int *vect);
void aloc(int n, int *vect);
void read_kb(int n, int *vect);
void read_random(int n, int *vect);
void exit_program(int *vect);
void print_vect(int n, int *vect);

void swap(int *a, int *b);

int test_condition(int n, int *vect);
void manipulate_vect(int n, int *vect);
void heap_sort(int n, int *vect);
void heapify(int *vect, int n, int i);

int max_num(int n, int *vect);
int min_num(int n, int *vect);
void counting_sort(int n, int *vect);

void main() {
    int n, *vect = NULL;

    printf("input n : ");
    scanf("%d", &n);
    
    if(n % 2 != 0) {
        menu(n, vect);
    }
    else {
        printf("Numarul trebuie sa fie impar !\n");
        main();
    }
}

void menu(int n, int *vect) {
    int option;
    printf("\n---- menu ----\n");
    printf("\n1.Alocarea memoriei.\n");
    printf("2.Citirea de la tastatura a vectorului.\n");
    printf("3.Completarea random a vectorului.\n");
    printf("4.Sortarea conform conditiei.\n");
    printf("0.Exit.\n");

    printf("-- optiunea aleasa : ");
    scanf("%d", &option);

    switch(option) {
        case 1:
            aloc(n, vect);
            break;
        case 2:
            read_kb(n, vect);
            break;
        case 3:
            read_random(n, vect);
            break;
        case 4:
            manipulate_vect(n, vect);
            break;
        case 0:
            exit_program(vect);
    }
}

void aloc(int n, int *vect) {
    vect = calloc(n, sizeof(int));
    menu(n, vect);
}

void read_kb(int n, int *vect) {
    for (int i = 0; i < n; i++) {
        printf("vect[%d] = ", i);
        scanf("%d", vect + i);
    }
    print_vect(n, vect);
    menu(n, vect);
}

void read_random(int n, int *vect) {
    srand(time(NULL));
    for (int i = 0; i < n; i++){
        *(vect + i) = rand() % 100 - 50;
    }
    printf(">>>> Initial vector : ");
    print_vect(n, vect);
    menu(n, vect);
}

void print_vect(int n, int *vect) {
    for (int i = 0; i < n; i++) {
        printf("%d ", *(vect + i));
    }
}

void exit_program(int *vect) {
    printf("\n...exit...");
    free(vect);
    exit(1);
}

void manipulate_vect(int n, int *vect) {
    printf("Initial : ");
    print_vect(n, vect);
    if(test_condition(n, vect) == 1) {
        printf("\n(primul numar negativ este pe pozitie para)-->");
        heap_sort(n, vect);
    }
    else {
        printf("\n(primul numar negativ este pe pozitie impara)-->");
        counting_sort(n, vect);
    }

    printf("Final : ");
    print_vect(n, vect);
    menu(n, vect);
}

int test_condition(int n, int *vect) {
    for (int i = 0; i < n; i++) {
        if(*(vect + i) < 0) {
            if(i % 2 != 0) {
                return 1;
            }
            else {
                return 0;
            }
        }
    }
    return 0;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heap_sort(int n, int *vect) {
    // crearea heapului
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(vect, n, i);
    }
    //sortarea
    for (int i = n - 1; i > 0; i--) {
        swap(vect, vect + i);

        heapify(vect, i, 0);
    }
}

void heapify(int *vect, int n, int i) {
    int max_node = i;
    int left_node = 2 * i + 1;
    int right_node = 2 * i + 2;

    if(left_node < n && *(vect + left_node) > *(vect + max_node)) {
        max_node = left_node;
    }
    if(right_node < n && *(vect + right_node) > *(vect + max_node)) {
        max_node = right_node;
    }

    if(max_node != i) {
        swap(vect + max_node, vect + i);

        heapify(vect, n, max_node);
    }
}

int max_num(int n, int *vect) {
    int max = *vect;
    for (int i = 1; i < n; i++) {
        if(max < *(vect + i)){
            max = *(vect + i);
        }
    }
    return max;
}

int min_num (int n, int *vect) {
    int min = *vect;
    for (int i = 1; i < n; i++) {
        if(min > *(vect + i)){
            min = *(vect + i);
        }
    }
    return min;
}

void counting_sort(int n, int *vect) {
    int *sorted_vect;
    int *count;

    sorted_vect = calloc(n, sizeof(int));
    count = calloc(max_num(n, vect) - min_num(n ,vect)+ 1, sizeof(int));

    for (int i = 0; *(vect + i); i++) {
        ++*(count + *(vect + i) - min_num(n, vect));
    }
    for (int i = 1; i <= max_num(n, vect) - min_num(n, vect); i++) {
        *(count + i) += *(count + i - 1);
    }
    for (int i = 0; *(vect + i); i++) {
        *(sorted_vect + *(count + *(vect + i) - min_num(n, vect)) - 1) = *(vect + i);
        --*(count + *(vect + i) - min_num(n, vect));
    }
    for (int i = 0; *(vect + i); i++) {
        *(vect + n - 1 - i) = *(sorted_vect + i);
    }
}