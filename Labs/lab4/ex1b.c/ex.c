#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

void menu(int n, int *vect);
void aloc(int n, int *vect);
void read_kb(int n, int *vect);
void read_random(int n, int *vect);
void exit_program(int *vect);
void print_vect(int n, int *vect);

void swap(int *a, int *b);

int test_condition(int n, int *vect);
void manipulate_vect(int n, int *vect);

void radix_sort(int n, int *vect);
void counting_sort_for_radix(int n, int *vect, int exp);

void comb_sort(int n, int *vect);
int get_next_gap(int gap);

int max_num(int n, int *vect);
int min_num(int n, int *vect);


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
        printf("\n(suma numerelor pare e mai mica)-->");
        radix_sort(n, vect);
    }
    else {
        printf("\n(suma numerelor pare e mai mare)-->");
        comb_sort(n, vect);
    }

    printf("Final : ");
    print_vect(n, vect);
    menu(n, vect);
}

int test_condition(int n, int *vect) {
    int sum_odd = 0;
    int sum_even = 0;
    int even_counter = 0;
    for (int i = 0; i < n; i++) {
        if(*(vect + i) % 2 == 0) {
            sum_odd += *(vect + i);
        }
        else {
            sum_even += *(vect + i);
            even_counter++;
        }
    }
    if(even_counter == 0) {
        return 0;
    }
    else if(sum_odd < sum_even / even_counter) {
        return 1;
    }
    return 0;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
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

void counting_sort_for_radix(int n, int *vect, int exp) {
    int *sorted_arr;
    sorted_arr = calloc(n, sizeof(int));
    int count_arr[10] = {0};
    for (int i = 0; *(vect + i); i++){
        ++count_arr[9 - (*(vect + i) / exp) % 10];
    }
    for (int i = 1; i < 10; i++) {
        count_arr[i] += count_arr[i - 1];
    }
    for (int i = n - 1; i >= 0; i--) {
        *(sorted_arr + count_arr[9 - (*(vect + i) / exp) % 10] - 1) = *(vect + i);
        --count_arr[9 - (*(vect + i) / exp) % 10];
    }
    for (int i = 0; *(vect + i); i++) {
        *(vect + i) = *(sorted_arr + i);
    }
}

void radix_sort(int n, int *vect) {
    int min_value = min_num(n, vect);
    for (int i = 0; i < n; i++) {
        *(vect + i) = *(vect + i) - min_value + 1;
    }
    
    int m = max_num(n, vect);
    for (int exp = 1; m / exp > 0; exp *= 10) {
        counting_sort_for_radix(n, vect, exp);
    }
    for (int i = 0; i < n; i++) {
        *(vect + i) = *(vect + i) + min_value - 1;
    }
}

void comb_sort(int n, int *vect) {
    int gap = n;

    bool swapped = true;

    while(gap != 1 || swapped == true) {
        gap = get_next_gap(gap);

        swapped = false;
        for (int i = 0; i < n - gap; i++) {
            if(*(vect + i) > *(vect + i + gap)) {
                swap(vect + i, vect + i + gap);
                swapped = true;
            }
        }
    }
}

int get_next_gap(int gap) {
    gap = (gap * 10) / 13;

    if(gap < 1) {
        return 1;
    }
    return gap;
}