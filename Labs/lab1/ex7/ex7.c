#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void menu(int n, int **arr, int *diagonala);

void alocare(int n, int **arr, int *diagonala);
void initialize_kb(int n, int **arr, int *diagonala);
void initialize_rand(int n, int **arr, int *diagonala);
void afisare(int n, int **arr, int *diagonala);
void freemem(int n, int **arr);

void swap(int *a, int *b);

void sort_menu(int n, int *diagonala, int sort_direction, int **arr);

void bubble_sort(int n, int *diagonala, int sort_direction);

void selection_sort(int n, int *diagonala, int sort_direction);

void insertion_sort(int n, int *diagonala, int sort_direction);

void quick_sort_ascend(int *diagonala, int inf, int sup);
int partition_ascend(int *diagonala, int inf, int sup);

void quick_sort_descend(int *diagonala, int inf, int sup);
int partition_descend(int *diagonala, int inf, int sup);

void merge_sort(int *diagonala, int left, int right);
void merge(int *diagonala, int left, int mid, int right);

void shell_sort(int n, int *diagonala);

void main() {
    int** arr = NULL;
    int n;
    int *diagonala;
    printf("input n :");
    scanf("%d", &n);

    menu(n, arr, diagonala);
}

void menu(int n, int **arr, int *diagonala) {
    int option;
    printf("\n		---- Menu ----  \n");
	printf("	1.Alocarea dinamica a memoriei pentru arr \n");
	printf("	2.Introducerea datelor de la tastatura\n");
	printf("	3.Completarea cu valori random \n");
	printf("	41.Sortarea ascendent pe diagonala secundara\n");
	printf("	42.Sortare descendent pe diagonala secundara\n");
	printf("	5.Afisarea arr N \n");
	printf("	0.Exit");
	printf("\nChoose number : ");	scanf("%i", &option);

	switch (option) {
	case 1:
		alocare(n, arr, diagonala);
        break;
	case 2:
        initialize_kb(n, arr, diagonala);
        break;
    case 3:
        initialize_rand(n, arr, diagonala);
		break;
	case 41:
        sort_menu(n, diagonala, 1, arr);
        menu(n, arr, diagonala);
		break;
	case 42:
        sort_menu(n, diagonala, -1, arr);
        menu(n, arr, diagonala);
		break;
	case 5:
		afisare(n, arr, diagonala);
		menu(n, arr, diagonala);
		break;
	case 0:
		printf("---- exit ... ----");
		freemem(n, arr);
		exit(1);
		break;
	default:
		printf("---- error! ----");
		menu(n, arr, diagonala);
		break;
    }
}

void alocare(int n, int** arr, int *diagonala) {
    arr = malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++){
        arr[i] = calloc(n, sizeof(int));
    }
    if(arr == NULL){
        printf("---- error alocare ----");
    }
    else{
        printf("---- succes ----");
    }
    menu(n, arr, diagonala);
}

void initialize_kb(int n, int **arr, int *diagonala) {
    diagonala = calloc(n, sizeof(int));
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            printf("arr[%d][%d] = ", i, j);
            scanf("%d", *(arr + i) + j);
        }
    }
    for (int i = 0; i < n; i++) {
        *(diagonala + i) = *(*(arr + i) + i);
    }
    menu(n, arr, diagonala);
}

void initialize_rand(int n, int **arr, int *diagonala) {
    diagonala = calloc(n, sizeof(int));
    srand(time(NULL));
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            *(*(arr + i) + j) = rand() % 100 - 50;
        }
    }
    for (int i = 0; i < n; i++) {
        *(diagonala + i) = *(*(arr + n - i - 1) + i);
    }
    menu(n, arr, diagonala);
}

void afisare(int n, int** arr, int *diagonala) {
    for(int i = 0; i < n; i++){
        *(*(arr + n - i - 1) + i) = *(diagonala + i);
    }
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            printf("%d\t", *(*(arr + i) + j));
        }
        printf("\n");
    }
    menu(n, arr, diagonala);
}

void freemem(int n, int **arr) {
    for (int i = 0; i < n; i++){
        free(arr[i]);
    }
    free(arr);
}

void swap(int *a, int *b) {
	int aux = *a;
	*a = *b;
	*b = aux;
}

void sort_menu(int n, int *diagonala, int sort_direction, int **arr) {
	int option;
	printf("\nAlegeti algoritmul de sortare : \n");
	printf("1. Bubble sort.\n");
	printf("2. Selection sort.\n");
	printf("3. Insertion sort.\n");
	printf("4. Quick sort.\n");
	if (sort_direction == 1){
		printf("5. Merge sort.\n");
		printf("6. Shell sort.\n");
	}
	printf("0. Main menu");
	printf("\nOption :");
	scanf("%d", &option);

	switch(option) {
		case 1:
			bubble_sort(n, diagonala, sort_direction);
            menu(n, arr, diagonala);
            break;
		case 2:
			selection_sort(n, diagonala, sort_direction);
            menu(n, arr, diagonala);
			break;
		case 3:
			insertion_sort(n, diagonala, sort_direction);
            menu(n, arr, diagonala);
			break;
		case 4:
			if(sort_direction == 1){
				quick_sort_ascend(diagonala, 0, n - 1);
			}
			else{
				quick_sort_descend(diagonala, 0, n - 1);
			}
			menu(n, arr, diagonala);
			break;
		case 5:
			if(sort_direction == 1) {
				merge_sort(diagonala, 0, n - 1);
				menu(n, arr, diagonala);
			}
			else {
				printf("\n**** option error! ****\n");
				sort_menu(n, diagonala, sort_direction, arr);
			}
			break;
		case 6:
			if(sort_direction == 1) {
				shell_sort(n, diagonala);
				menu(n, arr, diagonala);
			}
			else {
				printf("\n**** option error! ****\n");
				sort_menu(n, diagonala, sort_direction, arr);
			}
			break;
		case 0:
			menu(n, arr, diagonala);
			break;
		default:
			printf("\n**** option error! ****\n");
			sort_menu(n, diagonala, sort_direction, arr);
			break;
	}
}

void bubble_sort(int n, int *diagonala, int sort_direction) {
	if(sort_direction == 1){
		for (int i = 0; i < n - 1; i++) {
			for (int j = 0; j < n - i - 1; j++){
				if(*(diagonala + j) > *(diagonala + j + 1)) {
					swap(diagonala + j, diagonala + j + 1);
				}
			}
		}
	}
	else {
		for (int i = 0; i < n - 1; i++) {
			for (int j = 0; j < n - i - 1; j++){
				if(*(diagonala + j) < *(diagonala + j + 1)) {
					swap(diagonala + j, diagonala + j + 1);
				}
			}
		}
	}
}

void selection_sort(int n, int *diagonala, int sort_direction) {
	if(sort_direction == 1){
		for (int i = 0; i < n - 1; i++) {
			for (int j = i + 1; j < n; j++){
				if(*(diagonala + i) > *(diagonala + j)) {
					swap(diagonala + i, diagonala + j);
				}
			}
		}
	}
	else {
		for (int i = 0; i < n - 1; i++) {
			for (int j = i + 1; j < n ; j++){
				if(*(diagonala + i) < *(diagonala + j)) {
					swap(diagonala + i, diagonala + j );
				}
			}
		}
	}
}

void insertion_sort(int n, int *diagonala, int sort_direction) {
	int key, j;
	if(sort_direction == 1){
		for (int i = 1; i < n; i++){
			key = *(diagonala + i);
			j = i - 1;
			while (j >= 0 && *(diagonala + j) > key) {
				*(diagonala + j + 1) = *(diagonala + j);
				j--;
			}
			*(diagonala + j + 1) = key;
		}
	}
	else {
		for (int i = 1; i < n; i++){
			key = *(diagonala + i);
			j = i - 1;
			while (j >= 0 && *(diagonala + j) < key) {
				*(diagonala + j + 1) = *(diagonala + j);
				j--;
			}
			*(diagonala + j + 1) = key;
		}
	}
}

void quick_sort_ascend(int *diagonala, int inf, int sup) {
	if(inf < sup) {
		int pi = partition_ascend(diagonala, inf, sup);
		quick_sort_ascend(diagonala, inf, pi - 1);
		quick_sort_ascend(diagonala, pi + 1, sup);
	}
}

int partition_ascend(int *diagonala, int inf, int sup) {
	int pivot = *(diagonala + sup);
	int i = inf - 1;

	for (int j = inf; j < sup; j++){
		if(*(diagonala + j) < pivot) {
			i++;
			swap(diagonala + i, diagonala + j);
		}
	}
	swap(diagonala + i + 1, diagonala + sup);
	return i + 1;
}

void quick_sort_descend(int *diagonala, int inf, int sup) {
	if(inf < sup) {
		int pi = partition_descend(diagonala, inf, sup);
		quick_sort_descend(diagonala, inf, pi - 1);
		quick_sort_descend(diagonala, pi + 1, sup);
	}
}

int partition_descend(int *diagonala, int inf, int sup) {
	int pivot = *(diagonala + sup);
	int i = inf - 1;

	for (int j = inf; j < sup; j++){
		if(*(diagonala + j) > pivot) {
			i++;
			swap(diagonala + i, diagonala + j);
		}
	}
	swap(diagonala + i + 1, diagonala + sup);
	return i + 1;
}

void merge_sort(int *diagonala, int left, int right) {
	if (left < right) {
		int mid = left + (right - left) / 2;

		merge_sort(diagonala, left, mid);
		merge_sort(diagonala, mid + 1, right);

		merge(diagonala, left, mid, right);
	}
}

void merge(int *diagonala, int left, int mid, int right) {
	int i, j, k;
	int n1 = mid - left + 1;
	int n2 = right - mid;

	int *Left;
	int *Right;

	Left = calloc(n1, sizeof(int));
	Right = calloc(n2, sizeof(int));

	for (i = 0; i < n1; i++){
		*(Left + i) = *(diagonala + left + i);
	}
	for (j = 0; j < n2; j++) {
		*(Right + j) = *(diagonala + mid + j + 1);
	}
	i = 0;
	j = 0;
	k = left;
	while(i < n1 && j < n2) {
		if(*(Left + i) <= *(Right + j)){
			*(diagonala + k) = *(Left + i);
			i++;
		}
		else {
			*(diagonala + k) = *(Right + j);
			j++;
		}
		k++;
	}

	while(i < n1){
		*(diagonala + k) = *(Left + i);
		i++;
		k++;
	}
	while(j < n2){
		*(diagonala + k) = *(Right + j);
		j++;
		k++;
	}
}


void shell_sort(int n, int *diagonala) {
	for (int gap = n / 2; gap > 0; gap /= 2) {
		for (int i = gap; i < n; i++){
			int temp = *(diagonala + i);
			int j;
			for (j = i; j >= gap && *(diagonala + j - gap) > temp; j -= gap) {
				*(diagonala + j) = *(diagonala + j - gap);
			}
			*(diagonala + j) = temp;
		}
	}
}