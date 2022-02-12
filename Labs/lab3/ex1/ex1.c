#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <stdbool.h>

void initialize_rand(int n, int* N, int m, int* M, int* res_arr);
void initialize_kb(int n, int* N, int m, int* M);
void menu(int m, int n, int* M, int* N, int* res_arr, int* res_ptr);
void alocare(int n, int* N, int m, int* M, int* res_arr, int* res_ptr);
void create_resArr(int n, int* N, int m, int* M, int* res_arr, int* res_ptr);
void afisare(int number, int* arr);
void freemem(int* N, int* M, int* res_arr);

void swap(int *a, int *b);
int max_num(int n, int *arr);

void sort_menu(int m, int n, int *M, int *N, int *res_arr, int *res_ptr, int sort_direction);

void bubble_sort(int n, int *arr, int sort_direction);

void selection_sort(int n, int *arr, int sort_direction);

void insertion_sort(int n, int *arr, int sort_direction);

void quick_sort_ascend(int inf, int sup, int *arr);
int partition_ascend(int inf, int sup, int *arr);

void quick_sort_descend(int inf, int sup, int *arr);
int partition_descend(int inf, int sup, int *arr);

void merge_sort(int *arr, int left, int right);
void merge(int *arr, int left, int mid, int right);

void shell_sort(int n, int *Note);

void counting_sort(int n, int *arr, int sort_direction);
void counting_sort_for_radix(int n, int *arr, int sort_direction, int exp);

void radix_sort(int n, int *arr, int sort_direction);

void comb_sort(int n, int *arr, int sort_direction);
int get_next_gap(int gap);

void main() {
	int* M = NULL;
	int* N = NULL;
	int* res_arr = NULL;
	int m, n, num_res = 0;
	printf("input m : ");	scanf("%d", &m);
	printf("input n : ");	scanf("%d", &n);

	menu(m, n, M, N, res_arr, &num_res);
}

void menu(int m, int n, int* M, int* N, int* res_arr, int* res_ptr) {
	int option;
	printf("\n		---- Menu ----  \n");
	printf("	1.Alocarea dinamica a memoriei pentru M si N \n");
	printf("	2.Introducerea datelor de la tastatura\n");
	printf("	3.Completarea cu valori random \n");
	printf("	4.Completarea res_arr \n");
	printf("	41.Sortare ascendent res_arr \n");
	printf("	42.Sortare descendent res_arr \n");
	printf("	51.Afisarea vectorului N \n");
	printf("	52.Afisarea vectorului M \n");
	printf("	53.Afisarea vectorului res_arr \n");
	printf("	0.Exit");
	printf("\nChoose number : ");	scanf("%i", &option);

	switch (option) {
	case 1:
		alocare(n, N, m, M, res_arr, res_ptr);
		break;
	case 2:
		initialize_kb(n, N, m, M);
		menu(m, n, M, N, res_arr, res_ptr);
		break;
	case 3:
		initialize_rand(n, N, m, M, res_arr);
		menu(m, n, M, N, res_arr, res_ptr);
		break;
	case 4:
		create_resArr(n, N, m, M, res_arr, res_ptr);
		menu(m, n, M, N, res_arr, res_ptr);
		break;
	case 41:
		sort_menu(m, n, M, N, res_arr, res_ptr, 1);
		break;
	case 42:
		sort_menu(m, n, M, N, res_arr, res_ptr, -1);
		break;
	case 51:
		afisare(n, N);
		menu(m, n, M, N, res_arr, res_ptr);
		break;
	case 52:
		afisare(m, M);
		menu(m, n, M, N, res_arr, res_ptr);
		break;
	case 53:
		afisare(*res_ptr, res_arr);
		menu(m, n, M, N, res_arr, res_ptr);
		break;
	case 0:
		printf("---- exit ... ----");
		freemem(N, M, res_arr);
		exit(1);
		break;
	default:
		printf("---- error! ----");
		menu(m, n, M, N, res_arr, res_ptr);
		break;
	}
}

void alocare(int n, int* N, int m, int* M, int* res_arr, int* res_ptr) {
	N = calloc(n, sizeof(int));
	M = calloc(m, sizeof(int));
	res_arr = calloc(n + m, sizeof(int));

	if (N == NULL || M == NULL || res_arr == NULL) {
		printf("---- erorr alocare ----");
	}
	else {
		printf("---- Alocation success ----");
	}
	menu(m, n, M, N, res_arr, res_ptr);
}

void initialize_rand(int n, int* N, int m, int* M, int* res_arr) {
	srand(time(NULL));
	for (int i = 0; i < n; i++) {
		*(N + i) = rand() % 100 - 50;
	}
	for (int i = 0; i < m; i++) {
		*(M + i) = rand() % 100 - 50;
	}
	printf("\n---- Initialization success ----");
}

void initialize_kb(int n, int* N, int m, int* M) {
	for (int i = 0; i < n; i++) {
		printf(" N[%d] ", i);	scanf("%d", N + i);
	}
	for (int i = 0; i < m; i++) {
		printf(" M[%d] ", i);	scanf("%d", M + i);
	}
	printf("\n---- Initialization success ----");
}

void create_resArr(int n, int* N, int m, int* M, int* res_arr, int* res_ptr) {
	for (int i = 0; i < n; i++) {
		if (*(N + i) % 2 == 0 && *(N + i) > 0) {
			*(res_arr + *res_ptr) = *(N + i);
			*res_ptr = *res_ptr + 1;
		}
	}
	for (int i = 0; i < m; i++) {
		if (*(M + i) % 2 != 0 && *(M + i) > 0) {
			*(res_arr + *res_ptr) = *(M + i);
			*res_ptr = *res_ptr + 1;
		}
	}
	printf("---- Success ----%d", *res_ptr);
}

void afisare(int number, int* arr) {
	printf("---- Afisare ---- \n");
	for (int i = 0; i < number; i++) {
		printf("%d ", *(arr + i));
	}
}

void freemem(int* N, int* M, int* res_arr) {
	free(N);
	free(M);
	free(res_arr);
}

void swap(int *a, int *b) {
	int aux = *a;
	*a = *b;
	*b = aux;
}

void sort_menu(int m, int n, int* M, int* N, int* res_arr, int* res_ptr, int sort_direction) {
	int option;
	printf("\nAlegeti algoritmul de sortare : \n");
	printf("1. Bubble sort.\n");
	printf("2. Selection sort.\n");
	printf("3. Insertion sort.\n");
	printf("4. Quick sort.\n");
    printf("5. Radix sort.\n");
    printf("6. Counting sort.\n");
    printf("7. Comp sort.\n");
	if(sort_direction == 1) {
		printf("8. Merge sort.\n");
		printf("9. Shell sort.\n");
	}
	printf("0. Main menu");
	printf("\nOption :");
	scanf("%d", &option);

	switch(option) {
		case 1:
			bubble_sort(*res_ptr, res_arr, sort_direction);
			menu(m, n, M, N, res_arr, res_ptr);
			break;
		case 2:
			selection_sort(*res_ptr, res_arr, sort_direction);
			menu(m, n, M, N, res_arr, res_ptr);
			break;
		case 3:
			insertion_sort(*res_ptr, res_arr, sort_direction);
			menu(m, n, M, N, res_arr, res_ptr);
			break;
		case 4:
			if(sort_direction == 1) {
				quick_sort_ascend(0, *res_ptr - 1, res_arr);
			}
			else {
				quick_sort_descend(0, *res_ptr - 1, res_arr);
			}
			menu(m, n, M, N, res_arr, res_ptr);
			break;
        case 5:
            radix_sort(*res_ptr, res_arr, sort_direction);
            menu(m, n, M, N, res_arr, res_ptr);
			break;
        case 6:
            counting_sort(*res_ptr, res_arr, sort_direction);
            menu(m, n, M, N, res_arr, res_ptr);
			break;
        case 7:
			comb_sort(*res_ptr, res_arr, sort_direction);
			menu(m, n, M, N, res_arr, res_ptr);
			break;
		case 8:
			if(sort_direction == 1) {
				merge_sort(res_arr, 0, *res_ptr - 1);
				menu(m, n, M, N, res_arr, res_ptr);
			}
			else {
				printf("**** option error ****");
				sort_menu(m, n, M, N, res_arr, res_ptr, sort_direction);
			}
			break;
		case 9:
			if(sort_direction == 1) {
				shell_sort(*res_ptr, res_arr);
				menu(m, n, M, N, res_arr, res_ptr);
			}
			else {
				printf("**** option error ****");
				sort_menu(m, n, M, N, res_arr, res_ptr, sort_direction);
			}
			break;
		case 0:
			menu(m, n, M, N, res_arr, res_ptr);
			break;
		default:
			printf("\n**** option error! ****\n");
			sort_menu(m, n, M, N, res_arr, res_ptr, sort_direction);
			break;
	}
}

void bubble_sort(int n, int *arr, int sort_direction) {
	if(sort_direction == 1){
		for (int i = 0; i < n - 1; i++) {
			for (int j = 0; j < n - i - 1; j++){
				if(*(arr + j) > *(arr + j + 1)) {
					swap(arr + j, arr + j + 1);
				}
			}
		}
	}
	else {
		for (int i = 0; i < n - 1; i++) {
			for (int j = 0; j < n - i - 1; j++){
				if(*(arr + j) < *(arr + j + 1)) {
					swap(arr + j, arr + j + 1);
				}
			}
		}
	}
}

void selection_sort(int n, int *arr, int sort_direction) {
	if(sort_direction == 1){
		for (int i = 0; i < n - 1; i++) {
			for (int j = i + 1; j < n; j++){
				if(*(arr + i) > *(arr + j)) {
					swap(arr + i, arr + j);
				}
			}
		}
	}
	else {
		for (int i = 0; i < n - 1; i++) {
			for (int j = i + 1; j < n ; j++){
				if(*(arr + i) < *(arr + j)) {
					swap(arr + i, arr + j );
				}
			}
		}
	}
}

void insertion_sort(int n, int *arr, int sort_direction) {
	int key, j;
	if(sort_direction == 1){
		for (int i = 1; i < n; i++){
			key = *(arr + i);
			j = i - 1;
			while (j >= 0 && *(arr + j) > key) {
				*(arr + j + 1) = *(arr + j);
				j--;
			}
			*(arr + j + 1) = key;
		}
	}
	else {
		for (int i = 1; i < n; i++){
			key = *(arr + i);
			j = i - 1;
			while (j >= 0 && *(arr + j) < key) {
				*(arr + j + 1) = *(arr + j);
				j--;
			}
			*(arr + j + 1) = key;
		}
	}
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

void quick_sort_descend(int inf, int sup, int *arr) {
	if(inf < sup) {
		int pi = partition_descend(inf, sup, arr);
		quick_sort_descend(inf, pi - 1, arr);
		quick_sort_descend(pi + 1, sup, arr);
	}
}

int partition_descend(int inf, int sup, int *arr) {
	int pivot = *(arr + sup);
	int i = inf - 1;

	for (int j = inf; j < sup; j++){
		if(*(arr + j) > pivot) {
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

int max_num(int n, int *arr) {
    int max = *arr;
    for (int i = 1; i < n; i++) {
        if(max < *(arr + i)){
            max = *(arr + i);
        }
    }
    return max;
}

void counting_sort(int n, int *arr, int sort_direction) {
    int *sorted_arr, *count_arr;
    sorted_arr = calloc(n, sizeof(int));
    count_arr = calloc(max_num(n, arr) + 1, sizeof(int));

    for (int i = 0; *(arr + i); i++){
        ++*(count_arr + *(arr + i));
    }
    for (int i = 1; i <= max_num(n, arr); i++) {
        *(count_arr + i) += *(count_arr + i - 1);
    }
    for (int i = 0; *(arr + i); i++) {
        *(sorted_arr + *(count_arr + *(arr + i)) - 1) = *(arr + i);
        --*(count_arr + *(arr + i));
    }
    if(sort_direction == 1) {
        for (int i = 0; *(arr + i); i++) {
            *(arr + i) = *(sorted_arr + i);
        }
    }
    else {
        for (int i = 0; *(arr + i); i++) {
            *(arr + n - 1 - i) = *(sorted_arr + i);
        }
    }
}

void counting_sort_for_radix(int n, int *arr, int sort_direction, int exp) {
    int *sorted_arr;
    sorted_arr = calloc(n, sizeof(int));
    int count_arr[10] = {0};
    if(sort_direction == 1) {
        for (int i = 0; *(arr + i); i++){
            ++count_arr[(*(arr + i) / exp) % 10];
        }
    }
    else {
        for (int i = 0; *(arr + i); i++){
            ++count_arr[9 - (*(arr + i) / exp) % 10];
        }
    }
    for (int i = 1; i < 10; i++) {
        count_arr[i] += count_arr[i - 1];
    }
    if(sort_direction == 1) {
        for (int i = n - 1; i >= 0; i--) {
            *(sorted_arr + count_arr[(*(arr + i) / exp) % 10] - 1) = *(arr + i);
            --count_arr[(*(arr + i) / exp) % 10];
        }
    }
    else {
        for (int i = n - 1; i >= 0; i--) {
            *(sorted_arr + count_arr[9 - (*(arr + i) / exp) % 10] - 1) = *(arr + i);
            --count_arr[9 - (*(arr + i) / exp) % 10];
        }
    }
    for (int i = 0; *(arr + i); i++) {
        *(arr + i) = *(sorted_arr + i);
    }
}

void radix_sort(int n, int *arr, int sort_direction) {
    int m = max_num(n, arr);

    for (int exp = 1; m / exp > 0; exp *= 10) {
        counting_sort_for_radix(n, arr, sort_direction, exp);
    }
}

void comb_sort(int n, int *arr, int sort_direction) {
    int gap = n;

    bool swapped = true;

    while(gap != 1 || swapped == true) {
        gap = get_next_gap(gap);

        swapped = false;
        if(sort_direction == 1) {
            for (int i = 0; i < n - gap; i++) {
                if(*(arr + i) > *(arr + i + gap)) {
                    swap(arr + i, arr + i + gap);
                    swapped = true;
                }
            }
        }
        else {
            for (int i = 0; i < n - gap; i++) {
                if(*(arr + i) < *(arr + i + gap)) {
                    swap(arr + i, arr + i + gap);
                    swapped = true;
                }
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