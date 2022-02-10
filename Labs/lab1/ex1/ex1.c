#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void initialize_rand(int n, int* Note);
void initialize_kb(int n, int* Note);
void menu(int n, int* Note);
void alocare(int n, int* Note);
void afisare(int n, int* Note);
void freemem(int n, int* Note);

void swap(int *a, int *b);

void sort_menu(int n, int *Note, int sort_direction);

void bubble_sort(int n, int *Note, int sort_direction);

void selection_sort(int n, int *Note, int sort_direction);

void insertion_sort(int n, int *Note, int sort_direction);

void quick_sort_ascend(int *Note, int inf, int sup);
int partition_ascend(int *Note, int inf, int sup);

void quick_sort_descend(int *Note, int inf, int sup);
int partition_descend(int *Note, int inf, int sup);

void merge_sort(int *Note, int left, int right);
void merge(int *Note, int left, int mid, int right);

void shell_sort(int n, int *Note);

void main() {
	int* Note = NULL, n;
	printf("input n : ");
	scanf("%d", &n);
	if(n >=1 && n <= 30){
		menu(n, Note);
	}
}

void menu(int n, int* Note) {
	int option;
	printf("\n		---- Menu ----  \n");
	printf("	1.Alocarea dinamica a memoriei \n");
	printf("	2.Introducerea datelor de la tastatura\n");
	printf("	3.Completarea cu valori random \n");
	printf("	41.Sortarea crescator\n");
	printf("	42.Sortarea descrescator\n");
	printf("	5.Afisarea\n");
	printf("	0.Exit");
	printf("\nChoose number : ");	scanf("%i", &option);
	
	switch (option) {
		case 1: 
			alocare(n, Note);
			break;
		case 2:
			initialize_kb(n, Note);
			break;
		case 3:
			initialize_rand(n, Note);
			break;
		case 41:
			sort_menu(n, Note, 1);
			break;
		case 42:
			sort_menu(n, Note, -1);
			break;
		case 5:
			afisare(n, Note);
			break;
		case 0:
			printf("---- exit ... ----");
			freemem(n, Note);
			exit(1);
		default:
			printf("---- error! ----");
			menu(n, Note);
			break;
	}
}

void alocare(int n, int* Note) {
	Note = calloc(n, sizeof(int));
	if (Note == NULL) {
		printf("---- erorr alocare ----");
	}
	else {
		printf("---- Alocation success ----");
	}
	menu(n, Note);
}

void initialize_rand(int n, int *Note) {
	srand(time(NULL));
	for (int i = 0; i < n; i++) {
		*(Note + i) = rand() % 10 + 1;
	}
	printf("\n---- Initialization success ----");
	menu(n, Note);
}

void initialize_kb(int n, int* Note) {
	for (int i = 0; i < n; i++) {
		printf(" Note[%d] ", i);	scanf("%d", Note + i);
	}
	printf("\n---- Initialization success ----");
	menu(n, Note);
}

void afisare(int n, int* Note) {
	printf("---- Afisare ----\n");
	for (int i = 0; i < n; i++) {
		printf("%d ", *(Note + i));
	}
	menu(n, Note);
}

void freemem(int n, int* Note) {
	free(Note);
}

void swap(int *a, int *b) {
	int aux = *a;
	*a = *b;
	*b = aux;
}

void sort_menu(int n, int *Note, int sort_direction) {
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
			bubble_sort(n, Note, sort_direction);
			break;
		case 2:
			selection_sort(n, Note, sort_direction);
			break;
		case 3:
			insertion_sort(n, Note, sort_direction);
			break;
		case 4:
			if(sort_direction == 1){
				quick_sort_ascend(Note, 0, n - 1);
			}
			else{
				quick_sort_descend(Note, 0, n - 1);
			}
			menu(n, Note);
			break;
		case 5:
			if(sort_direction == 1) {
				merge_sort(Note, 0, n - 1);
				menu(n, Note);
			}
			else {
				printf("\n**** option error! ****\n");
				sort_menu(n, Note, sort_direction);
			}
			break;
		case 6:
			if(sort_direction == 1) {
				shell_sort(n, Note);
				menu(n, Note);
			}
			else {
				printf("\n**** option error! ****\n");
				sort_menu(n, Note, sort_direction);
			}
			break;
		case 0:
			menu(n, Note);
			break;
		default:
			printf("\n**** option error! ****\n");
			sort_menu(n, Note, sort_direction);
			break;
	}
}

void bubble_sort(int n, int *Note, int sort_direction) {
	if(sort_direction == 1){
		for (int i = 0; i < n - 1; i++) {
			for (int j = 0; j < n - i - 1; j++){
				if(*(Note + j) > *(Note + j + 1)) {
					swap(Note + j, Note + j + 1);
				}
			}
		}
	}
	else {
		for (int i = 0; i < n - 1; i++) {
			for (int j = 0; j < n - i - 1; j++){
				if(*(Note + j) < *(Note + j + 1)) {
					swap(Note + j, Note + j + 1);
				}
			}
		}
	}
	menu(n, Note);
}

void selection_sort(int n, int *Note, int sort_direction) {
	if(sort_direction == 1){
		for (int i = 0; i < n - 1; i++) {
			for (int j = i + 1; j < n; j++){
				if(*(Note + i) > *(Note + j)) {
					swap(Note + i, Note + j);
				}
			}
		}
	}
	else {
		for (int i = 0; i < n - 1; i++) {
			for (int j = i + 1; j < n ; j++){
				if(*(Note + i) < *(Note + j)) {
					swap(Note + i, Note + j );
				}
			}
		}
	}
	menu(n, Note);
}

void insertion_sort(int n, int *Note, int sort_direction) {
	int key, j;
	if(sort_direction == 1){
		for (int i = 1; i < n; i++){
			key = *(Note + i);
			j = i - 1;
			while (j >= 0 && *(Note + j) > key) {
				*(Note + j + 1) = *(Note + j);
				j--;
			}
			*(Note + j + 1) = key;
		}
	}
	else {
		for (int i = 1; i < n; i++){
			key = *(Note + i);
			j = i - 1;
			while (j >= 0 && *(Note + j) < key) {
				*(Note + j + 1) = *(Note + j);
				j--;
			}
			*(Note + j + 1) = key;
		}
	}
	menu(n, Note);
}

void quick_sort_ascend(int *Note, int inf, int sup) {
	if(inf < sup) {
		int pi = partition_ascend(Note, inf, sup);
		quick_sort_ascend(Note, inf, pi - 1);
		quick_sort_ascend(Note, pi + 1, sup);
	}
}

int partition_ascend(int *Note, int inf, int sup) {
	int pivot = *(Note + sup);
	int i = inf - 1;

	for (int j = inf; j < sup; j++){
		if(*(Note + j) < pivot) {
			i++;
			swap(Note + i, Note + j);
		}
	}
	swap(Note + i + 1, Note + sup);
	return i + 1;
}

void quick_sort_descend(int *Note, int inf, int sup) {
	if(inf < sup) {
		int pi = partition_descend(Note, inf, sup);
		quick_sort_descend(Note, inf, pi - 1);
		quick_sort_descend(Note, pi + 1, sup);
	}
}

int partition_descend(int *Note, int inf, int sup) {
	int pivot = *(Note + sup);
	int i = inf - 1;

	for (int j = inf; j < sup; j++){
		if(*(Note + j) > pivot) {
			i++;
			swap(Note + i, Note + j);
		}
	}
	swap(Note + i + 1, Note + sup);
	return i + 1;
}

void merge_sort(int *Note, int left, int right) {
	if (left < right) {
		int mid = left + (right - left) / 2;

		merge_sort(Note, left, mid);
		merge_sort(Note, mid + 1, right);

		merge(Note, left, mid, right);
	}
}

void merge(int *Note, int left, int mid, int right) {
	int i, j, k;
	int n1 = mid - left + 1;
	int n2 = right - mid;

	int *Left;
	int *Right;

	Left = calloc(n1, sizeof(int));
	Right = calloc(n2, sizeof(int));

	for (i = 0; i < n1; i++){
		*(Left + i) = *(Note + left + i);
	}
	for (j = 0; j < n2; j++) {
		*(Right + j) = *(Note + mid + j + 1);
	}
	i = 0;
	j = 0;
	k = left;
	while(i < n1 && j < n2) {
		if(*(Left + i) <= *(Right + j)){
			*(Note + k) = *(Left + i);
			i++;
		}
		else {
			*(Note + k) = *(Right + j);
			j++;
		}
		k++;
	}

	while(i < n1){
		*(Note + k) = *(Left + i);
		i++;
		k++;
	}
	while(j < n2){
		*(Note + k) = *(Right + j);
		j++;
		k++;
	}
}


void shell_sort(int n, int *Note) {
	for (int gap = n / 2; gap > 0; gap /= 2) {
		for (int i = gap; i < n; i++){
			int temp = *(Note + i);
			int j;
			for (j = i; j >= gap && *(Note + j - gap) > temp; j -= gap) {
				*(Note + j) = *(Note + j - gap);
			}
			*(Note + j) = temp;
		}
	}
}