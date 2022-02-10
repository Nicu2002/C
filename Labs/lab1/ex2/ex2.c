#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void initialize_rand(int n, int* arr);
void initialize_kb(int n, int* arr);
void menu(int n, int* arr);
void alocare(int n, int* arr);
void manipulate(int n, int* arr);
void afisare(int n, int* arr);
void freemem(int n, int* arr);

void swap(int *a, int *b);
void merge_sides(int *left_arr, int *right_arr, int t, int n, int *arr);

void sort_menu(int *right_arr, int *left_arr, int t, int n, int *arr);

void bubble_sort(int *right_arr, int *left_arr, int t, int n);

void selection_sort(int *right_arr, int *left_arr, int t, int n);

void insertion_sort(int *right_arr, int *left_arr, int t, int n);

void quick_sort_ascend(int *left_arr, int inf, int sup);
int partition_ascend(int *left_arr, int inf, int sup);

void quick_sort_descend(int *right_arr, int inf, int sup);
int partition_descend(int *right_arr, int inf, int sup);

void main() {
	int arr[50], n;
	printf("input n : ");
	scanf("%d", &n);

	menu(n, arr);
}

void menu(int n,int* arr) {
	int option;
	printf("\n		---- Menu ----  \n");
	printf("	1.Alocarea dinamica a memoriei \n");
	printf("	2.Introducerea datelor de la tastatura\n");
	printf("	3.Completarea cu valori random \n");
	printf("	4. Manipularea cu vectorul\n");
	printf("	5.Afisarea\n");
	printf("	0.Exit");
	printf("\nChoose number : ");	scanf("%i", &option);

	switch (option) {
	case 1:
		alocare(n, arr);
		break;
	case 2:
		initialize_kb(n, arr);
		break;
	case 3:
		initialize_rand(n, arr);
		break;
	case 4:
		manipulate(n, arr);
		break;
	case 5:
		afisare(n, arr);
		break;
	case 0:
		printf("---- exit ... ----");
		freemem(n, arr);
		exit(1);
	default:
		printf("---- error! ----");
		menu(n, arr);
	}
}

void alocare(int n, int* arr) {
	arr = malloc(n * sizeof(int));
	for (int i = 0; i < n; i++) {
		*(arr + i) = 0;
	}
	if (arr == NULL) {
		printf("---- erorr alocare ----");
	}
	else {
		printf("---- Alocation success ----");
	}
	menu(n, arr);
}

void initialize_rand(int n, int* arr) {
	srand(time(NULL));
	for (int i = 0; i < n; i++) {
		*(arr + i) = rand() % 100 - 50;
	}
	printf("\n---- Initialization success ----");
	menu(n, arr);
}

void initialize_kb(int n, int* arr) {
	for (int i = 0; i < n; i++) {
		printf(" arr[%d] ", i);	scanf("%d", arr + i);
	}
	printf("\n---- Initialization success ----");
	menu(n, arr);
}

void manipulate(int n, int* arr) {
	int t;
	printf("\ninput t : ");		scanf("%d", &t);
	int *right_arr, *left_arr;

	left_arr = calloc(t, sizeof(int));
	right_arr = calloc(n - t, sizeof(int));

	for (int i = 0; i < n; i++) {
		if (i < t) {
			*(left_arr + i) = *(arr + i);
		}
		else {
			*(right_arr + i - t) = *(arr + i);
		}
	}

	sort_menu(right_arr, left_arr, t, n, arr);

}

void afisare(int n, int* arr) {
	printf("---- Afisare ----\n");
	for (int i = 0; i < n; i++) {
		printf("%d ", *(arr + i));
	}
	menu(n, arr);
}

void freemem(int n, int* arr) {
	free(arr);
}

void swap(int *a, int *b) {
	int aux = *a;
	*a = *b;
	*b = aux;
}

void sort_menu(int *right_arr, int *left_arr, int t, int n, int* arr) {
	int option;
	printf("\nAlegeti algoritmul de sortare : \n");
	printf("1. Bubble sort.\n");
	printf("2. Selection sort.\n");
	printf("3. Insertion sort.\n");
	printf("4. Quick sort.\n");
	printf("0. Main menu");
	printf("\nOption :");
	scanf("%d", &option);

	switch(option) {
		case 1:
			bubble_sort(right_arr, left_arr, t, n);
			merge_sides(left_arr, right_arr, t, n, arr);
			menu(n, arr);
			break;
		case 2:
			selection_sort(right_arr, left_arr, t, n);
			merge_sides(left_arr, right_arr, t, n, arr);
			menu(n, arr);
			break;
		case 3:
			insertion_sort(right_arr, left_arr, t, n);
			merge_sides(left_arr, right_arr, t, n, arr);
			menu(n, arr);
			break;
		case 4:
			quick_sort_ascend(left_arr, 0, t - 1);
			quick_sort_descend(right_arr, 0, n - t - 1);
			merge_sides(left_arr, right_arr, t, n, arr);
			menu(n, arr);
			break;
		case 0:
			menu(n, arr);
			break;
		default:
			printf("\n**** option error! ****\n");
			sort_menu(right_arr, left_arr, t, n, arr);
			break;
	}
}

void bubble_sort(int *right_arr, int *left_arr, int t, int n) {
	for (int i = 0; i < t - 1; i++) {
		for (int j = 0; j < t - i - 1; j++){
			if(*(left_arr + j) > *(left_arr + j + 1)) {
				swap(left_arr + j, left_arr + j + 1);
			}
		}
	}
	for (int i = 0; i < n - t - 1; i++) {
		for (int j = 0; j < n - t - i - 1; j++){
			if(*(right_arr + j) < *(right_arr + j + 1)) {
				swap(right_arr + j, right_arr + j + 1);
			}
		}
	}
}

void selection_sort(int *right_arr, int *left_arr, int t, int n) {
	for (int i = 0; i < t - 1; i++) {
		for (int j = i + 1; j < t; j++){
			if(*(left_arr + i) > *(left_arr + j)) {
				swap(left_arr + i, left_arr + j);
			}
		}
	}
	for (int i = 0; i < n - t - 1; i++) {
		for (int j = i + 1; j < n - t ; j++){
			if(*(right_arr + i) < *(right_arr + j)) {
				swap(right_arr + i, right_arr + j );
			}
		}
	}
}

void insertion_sort(int *right_arr, int *left_arr, int t, int n) {
	int key, j;
	for (int i = 1; i < t; i++){
		key = *(left_arr + i);
		j = i - 1;
		while (j >= 0 && *(left_arr + j) > key) {
			*(left_arr + j + 1) = *(left_arr + j);
			j--;
		}
		*(left_arr + j + 1) = key;
	}
	for (int i = 1; i < n - t; i++){
		key = *(right_arr + i);
		j = i - 1;
		while (j >= 0 && *(right_arr + j) < key) {
			*(right_arr + j + 1) = *(right_arr + j);
			j--;
		}
		*(right_arr + j + 1) = key;
	}
}

void quick_sort_ascend(int *left_arr, int inf, int sup) {
	if(inf < sup) {
		int pi = partition_ascend(left_arr, inf, sup);
		quick_sort_ascend(left_arr, inf, pi - 1);
		quick_sort_ascend(left_arr, pi + 1, sup);
	}
}

int partition_ascend(int *left_arr, int inf, int sup) {
	int pivot = *(left_arr + sup);
	int i = inf - 1;

	for (int j = inf; j < sup; j++){
		if(*(left_arr + j) < pivot) {
			i++;
			swap(left_arr + i, left_arr + j);
		}
	}
	swap(left_arr + i + 1, left_arr + sup);
	return i + 1;
}

void quick_sort_descend(int *right_arr, int inf, int sup) {
	if(inf < sup) {
		int pi = partition_descend(right_arr, inf, sup);
		quick_sort_descend(right_arr, inf, pi - 1);
		quick_sort_descend(right_arr, pi + 1, sup);
	}
}

int partition_descend(int *right_arr, int inf, int sup) {
	int pivot = *(right_arr + sup);
	int i = inf - 1;

	for (int j = inf; j < sup; j++){
		if(*(right_arr + j) > pivot) {
			i++;
			swap(right_arr + i, right_arr + j);
		}
	}
	swap(right_arr + i + 1, right_arr + sup);
	return i + 1;
}

void merge_sides(int *left_arr, int *right_arr, int t, int n, int *arr) {
	int k = 0;
	for (int i = 0; i < t; i++) {
		*(arr + k) = *(left_arr + i);
		k++;
	}
	for (int i = 0; i < n - t; i++) {
		*(arr + k) = *(right_arr + i);
		k++;
	}
}