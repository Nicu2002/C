#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

void menu(int n, int **arr);
void aloc(int n, int **arr);
void read_kb(int n, int **arr);
void read_random(int n, int **arr);
void exit_program(int **arr, int n);
void print_arr(int n, int **arr);

void min_indices(int n, int **arr, int **indices, int *counter);
void selection_sort(int n, int *vect);
void insertion_sort(int n, int *vect);

void manipulate_arr(int n, int **arr);
void swap(int *a, int *b);
int test_condition(int n, int **arr, int **indices);

void main() {
    int n, **arr = NULL;

    printf("input n : ");
    scanf("%d", &n);
    
    if(n >= 0) {
        menu(n, arr);
    }
    else {
        printf("Numarul trebuie sa fie pozitiv sau 0 !\n");
        main();
    }
}

void menu(int n, int **arr) {
    int option;
    printf("\n---- menu ----\n");
    printf("\n1.Alocarea memoriei.\n");
    printf("2.Citirea de la tastatura a array-ului.\n");
    printf("3.Completarea random a array-ului.\n");
    printf("4.Sortarea conform conditiei.\n");
    printf("0.Exit.\n");

    printf("-- optiunea aleasa : ");
    scanf("%d", &option);

    switch(option) {
        case 1:
            aloc(n, arr);
            break;
        case 2:
            read_kb(n, arr);
            break;
        case 3:
            read_random(n, arr);
            break;
        case 4:
            manipulate_arr(n, arr);
            break;
        case 0:
            exit_program(arr, n);
    }
}

void aloc(int n, int **arr) {
    arr = malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        arr[i] = calloc(n, sizeof(int));
    }
    menu(n, arr);
}

void read_kb(int n, int **arr) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++){
            printf("arr[%d][%d] = ", i, j);
            scanf("%d", *(arr + i) + j);
        }
    }
    print_arr(n, arr);
    menu(n, arr);
}

void read_random(int n, int **arr) {
    srand(time(NULL));
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++) {
            *(*(arr + i) + j) = rand() % 100 - 50;
        }
    }
    printf(">>>> Initial vector : ");
    print_arr(n, arr);
    menu(n, arr);
}

void print_arr(int n, int **arr) {
    printf("\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%3d ", *(*(arr + i) + j));
        }
        printf("\n");
    }
}

void exit_program(int **arr, int n) {
    printf("\n...exit...");
    for (int i = 0; i < n; i++) {
        free(arr[i]);
    }
    free(arr);
    exit(1);
}

void manipulate_arr(int n, int **arr) {
    printf("Initial : ");
    print_arr(n, arr);
    int **indices = NULL;
    indices = malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        indices[i] = calloc(2, sizeof(int));
    }
    int *vect = NULL;
    vect = calloc(n, sizeof(int));

    if(test_condition(n, arr, indices) == -1) {
        for (int i = 0; *(*(indices + i)); i++) {
            for (int j = 0; j < n; j++) {
                *(vect + j) = *(*(arr + *(*(indices + i))) + j);
            }
            selection_sort(n, vect);
            for (int k = 0; k < n; k++) {
                *(*(arr + *(*(indices + i))) + k) = *(vect + k);
            }
        }
        printf("\n(macar o data el minim e pe linie impara)-->");
    }
    else {
        for (int i = 0; *(*(indices + i)); i++) {
            for (int j = 0; j < n; j++) {
                *(vect + j) = *(*(arr + j) + *(*(indices + i) + 1));
            }
            insertion_sort(n, vect);
            for (int k = 0; k < n; k++) {
                *(*(arr + k) + *(*(indices + i) + 1)) = *(vect + k);
            }
        }
        printf("\n(elementul minim nu e pe linie impara niciodata)-->");
    }

    printf("Final : ");
    print_arr(n, arr);
    menu(n, arr);
}

void min_indices(int n, int **arr, int **indices, int *counter) {
    int min = **arr;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if(min > *(*(arr + i) + j)) {
                min = *(*(arr + i) + j);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if(*(*(arr + i) + j) == min) {
                *(*(indices + *counter)) = i;
                *(*(indices + *counter) + 1) = j;
                *counter = *counter + 1;
            }
        }
    }
}

int test_condition(int n, int **arr, int **indices) {
    int counter = 0;
    min_indices(n, arr, indices, &counter);
    for (int i = 0; i < counter; i++) {
        if(*(*(indices + i)) % 2 == 0 || *(*(indices + i)) == 0) {
            return -1;
        }
    }
    return 1;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void selection_sort(int n, int *vect) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if(*(vect + i) > *(vect + j)) {
                swap(vect + i, vect + j);
            }
        }
    }
}

void insertion_sort(int n, int *vect) {
	int key, j;
	for (int i = 1; i < n; i++){
		key = *(vect + i);
		j = i - 1;
		while (j >= 0 && *(vect + j) < key) {
			*(vect + j + 1) = *(vect + j);
			j--;
		}
		*(vect + j + 1) = key;
	}
}