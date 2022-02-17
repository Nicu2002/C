#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define k 321

void menu(int n, int **arr);
void aloc(int n, int **arr);
void read_kb(int n, int **arr);
void read_random(int n, int **arr);
void exit_program(int **arr, int n);
void print_arr(int n, int **arr);

void quick_sort(int *vect, int inf, int sup);
int partition(int *vect, int inf, int sup);
void shell_sort(int n, int *vect);

void manipulate_arr(int n, int **arr);
void swap(int *a, int *b);
int test_condition(int n, int **arr);

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

    int *vect = NULL;
    vect = calloc(n, sizeof(int));

    if(test_condition(n, arr) == 1) {
        for (int i = 0; i < n; i++) {
            *(vect + i) = *(*(arr + i) + i);
        }
        printf("\n(produsul el primei coloane e > k)-->");
        quick_sort(vect, 0, n - 1);
        for (int i = 0; i < n; i++) {
            *(*(arr + i) + i) = *(vect + i);
        }
    }
    else {
        for (int i = 0; i < n; i++) {
            *(vect + i) = *(*(arr + i) + n - 1 - i);
        }
        printf("\n(produsul el primei coloane e < k)-->");
        shell_sort(n, vect);
        for (int i = 0; i < n; i++) {
            *(*(arr + i) + n - 1 - i) = *(vect + n - 1 - i);
        }
    }

    printf("Final : ");
    print_arr(n, arr);
    for (int i = 0; i < n; i++) {
        printf(" %d ", *(vect + i));
    }
    menu(n, arr);
}

int test_condition(int n, int **arr) {
    int column_produs = 1;
    for (int i = 0; i < n; i++) {
        column_produs *= *(*(arr + i));
    }
    if(column_produs > k) {
        return 1;
    }
    return 0;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void quick_sort(int *vect, int inf, int sup) {
	if(inf < sup) {
		int pi = partition(vect, inf, sup);
		quick_sort(vect, inf, pi - 1);
		quick_sort(vect, pi + 1, sup);
	}
}

int partition(int *vect, int inf, int sup) {
	int pivot = *(vect + sup);
	int i = inf - 1;

	for (int j = inf; j < sup; j++){
		if(*(vect + j) < pivot) {
			i++;
			swap(vect + i, vect + j);
		}
	}
	swap(vect + i + 1, vect + sup);
	return i + 1;
}

void shell_sort(int n, int *vect) {
	for (int gap = n / 2; gap > 0; gap /= 2) {
		for (int i = gap; i < n; i++){
			int temp = *(vect + i);
			int j;
			for (j = i; j >= gap && *(vect + j - gap) > temp; j -= gap) {
				*(vect + j) = *(vect + j - gap);
			}
			*(vect + j) = temp;
		}
	}
}