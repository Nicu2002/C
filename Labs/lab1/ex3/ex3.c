#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void initialize_rand(int n, int* arr);
void initialize_kb(int n, int* arr);
void menu(int n, int* arr);
void alocare(int n, int* arr);
void sort(int n, int* arr);
void calc_m(int n, int* arr);
void afisare(int n, int* arr);
void freemem(int n, int* arr);

void swap(int *a, int *b);
void merge_sides(int n, int *arr);

void sort_menu(int n, int *arr);

void bubble_sort(int n, int *arr);

void selection_sort(int n, int *arr);

void insertion_sort(int n, int *arr);

void quick_sort_ascend(int inf, int sup, int *arr);
int partition_ascend(int inf, int sup, int *arr);

void merge_sort(int *arr, int left, int right);
void merge(int *arr, int left, int mid, int right);

void shell_sort(int n, int *Note);

void main() {
	int arr[50], n;
	printf("input n : ");
	scanf("%d", &n);

	menu(n, arr);
}

void menu(int n, int* arr) {
	int option;
	printf("\n		---- Menu ----  \n");
	printf("	1.Alocarea dinamica a memoriei \n");
	printf("	2.Introducerea datelor de la tastatura\n");
	printf("	3.Completarea cu valori random \n");
	printf("	4. Sortare si calculul MA si Medianei \n");
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
		sort_menu(n, arr);
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

void calc_m(int n,int* arr) {
	double sum = 0;
	for (int i = 0; i < n; i++) {
		sum += *(arr + i);
	}
	double Ma = sum / n;
	double Mediana;
	if (n % 2 != 0) {
		Mediana = *(arr + n / 2);
	}
	else {
		Mediana = (*(arr + n / 2) + *(arr + n / 2 - 1)) / 2.0;
	}
	printf("Ma : %lg, Mediana : %lg", Ma, Mediana);
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

void sort_menu(int n, int *arr) {
	int option;
	printf("\nAlegeti algoritmul de sortare : \n");
	printf("1. Bubble sort.\n");
	printf("2. Selection sort.\n");
	printf("3. Insertion sort.\n");
	printf("4. Quick sort.\n");
	printf("5. Merge sort.\n");
	printf("6. Shell sort.\n");
	printf("0. Main menu");
	printf("\nOption :");
	scanf("%d", &option);

	switch(option) {
		case 1:
			bubble_sort(n, arr);
			calc_m(n, arr);
			menu(n, arr);
			break;
		case 2:
			selection_sort(n, arr);
			calc_m(n, arr);
			menu(n, arr);
			break;
		case 3:
			insertion_sort(n, arr);
			calc_m(n, arr);
			menu(n, arr);
			break;
		case 4:
			quick_sort_ascend(0, n - 1, arr);
			calc_m(n, arr);
			menu(n, arr);
			break;
		case 5:
			merge_sort(arr, 0, n - 1);
			calc_m(n, arr);
			menu(n, arr);
			break;
		case 6:
			shell_sort(n, arr);
			calc_m(n, arr);
			menu(n, arr);
			break;
		case 0:
			menu(n, arr);
			break;
		default:
			printf("\n**** option error! ****\n");
			sort_menu(n, arr);
			break;
	}
}

void bubble_sort(int n, int *arr) {
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - i - 1; j++){
			if(*(arr + j) > *(arr + j + 1)) {
				swap(arr + j, arr + j + 1);
			}
		}
	}
	menu(n, arr);
}

void selection_sort(int n, int *arr) {
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++){
			if(*(arr + i) > *(arr + j)) {
				swap(arr + i, arr + j);
			}
		}
	}
	menu(n, arr);
}

void insertion_sort(int n, int *arr) {
	int key, j;
	for (int i = 1; i < n; i++){
		key = *(arr + i);
		j = i - 1;
		while (j >= 0 && *(arr + j) > key) {
			*(arr + j + 1) = *(arr + j);
			j--;
		}
		*(arr + j + 1) = key;
	}
	menu(n, arr);
}

void quick_sort_ascend(int inf, int sup, int *arr) {
	if(inf < sup) {
		int pi = partition_ascend(inf, sup, arr);
		quick_sort_ascend(inf, pi - 1, arr);
		quick_sort_ascend(pi + 1, sup, arr);
	}
}

int partition_ascend(int inf, int sup, int *arr) {
	int pivot = *(arr + sup);
	int i = inf - 1;

	for (int j = inf; j < sup; j++){
		if(*(arr + j) < pivot) {
			i++;
			swap(arr + i, arr + j);
		}
	}
	swap(arr + i + 1, arr + sup);
	return i + 1;
}

void merge_sort(int *arr, int left, int right) {
	if (left < right) {
		int mid = left + (right - left) / 2;

		merge_sort(arr, left, mid);
		merge_sort(arr, mid + 1, right);

		merge(arr, left, mid, right);
	}
}

void merge(int *arr, int left, int mid, int right) {
	int i, j, k;
	int n1 = mid - left + 1;
	int n2 = right - mid;

	int *Left;
	int *Right;

	Left = calloc(n1, sizeof(int));
	Right = calloc(n2, sizeof(int));

	for (i = 0; i < n1; i++){
		*(Left + i) = *(arr + left + i);
	}
	for (j = 0; j < n2; j++) {
		*(Right + j) = *(arr + mid + j + 1);
	}
	i = 0;
	j = 0;
	k = left;
	while(i < n1 && j < n2) {
		if(*(Left + i) <= *(Right + j)){
			*(arr + k) = *(Left + i);
			i++;
		}
		else {
			*(arr + k) = *(Right + j);
			j++;
		}
		k++;
	}

	while(i < n1){
		*(arr + k) = *(Left + i);
		i++;
		k++;
	}
	while(j < n2){
		*(arr + k) = *(Right + j);
		j++;
		k++;
	}
}


void shell_sort(int n, int *arr) {
	for (int gap = n / 2; gap > 0; gap /= 2) {
		for (int i = gap; i < n; i++){
			int temp = *(arr + i);
			int j;
			for (j = i; j >= gap && *(arr + j - gap) > temp; j -= gap) {
				*(arr + j) = *(arr + j - gap);
			}
			*(arr + j) = temp;
		}
	}
}