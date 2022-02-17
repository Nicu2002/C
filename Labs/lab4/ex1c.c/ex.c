#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>

void menu(int n, int *vect);
void aloc(int n, int *vect);
void read_kb(int n, int *vect);
void read_random(int n, int *vect);
void exit_program(int *vect);
void print_vect(int n, int *vect);

void manipulate_vect(int n, int *vect);
void swap(int *a, int *b);
bool isPrim(int number);
int test_condition(int n, int *vect);

void merge_sort(int *vect, int left, int right);
void bubble_sort(int n, int *vect);
void merge(int *vect, int left, int mid, int right);

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
    if(test_condition(n, vect) != 1) {
        printf("\n(in vector sunt cel putin 2 numere prime)-->");
        merge_sort(vect, 0, n - 1);
    }
    else {
        printf("\n(in vector este maxim un element prim)-->");
        bubble_sort(n, vect);
    }

    printf("Final : ");
    print_vect(n, vect);
    menu(n, vect);
}

int test_condition(int n, int *vect) {
    int counter = 0, i = 0;
    while(counter < 2 && i < n) {
        if(isPrim(*(vect + i)) == true) {
            counter++;
        }
        i++;
    }
    if(counter < 2) {
        return 1;
    }
    return -1;
}

bool isPrim(int number) {
    bool result = true;
	if(number > 1) {
		for (int i = 2; i <= (int)sqrt(number); i++) {
			if(number % i == 0) {
				result = false;
				break;
			}
		}
	}
	else {
		result = false;
	}
	return result;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void merge_sort(int *vect, int left, int right) {
	if (left < right) {
		int mid = left + (right - left) / 2;

		merge_sort(vect, left, mid);
		merge_sort(vect, mid + 1, right);

		merge(vect, left, mid, right);
	}
}

void merge(int *vect, int left, int mid, int right) {
	int i, j, k;
	int n1 = mid - left + 1;
	int n2 = right - mid;

	int *Left;
	int *Right;

	Left = calloc(n1, sizeof(int));
	Right = calloc(n2, sizeof(int));

	for (i = 0; i < n1; i++){
		*(Left + i) = *(vect + left + i);
	}
	for (j = 0; j < n2; j++) {
		*(Right + j) = *(vect + mid + j + 1);
	}
	i = 0;
	j = 0;
	k = left;
	while(i < n1 && j < n2) {
		if(*(Left + i) <= *(Right + j)){
			*(vect + k) = *(Left + i);
			i++;
		}
		else {
			*(vect + k) = *(Right + j);
			j++;
		}
		k++;
	}

	while(i < n1){
		*(vect + k) = *(Left + i);
		i++;
		k++;
	}
	while(j < n2){
		*(vect + k) = *(Right + j);
		j++;
		k++;
	}
}

void bubble_sort(int n, int *vect) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if(*(vect + j) < *(vect + j + 1)){
                swap(vect + j, vect + j + 1);
            }
        }
    }
}