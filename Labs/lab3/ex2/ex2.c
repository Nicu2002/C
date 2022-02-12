#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

void menu(int n, int m, int **arr);

void alocare(int n, int m, int **arr);
void initialize_kb(int n, int m, int **arr);
void initialize_rand(int n, int m, int **arr);
void afisare(int n, int m, int **arr);
void freemem(int n, int m, int **arr);

void swap(int *a, int *b);
int max_num(int n, int *column);
int min_num(int n, int *column);
int get_next_gap(int gap);
void update_matrix(int n, int m, int **arr, int *column, int column_index);

void sort_menu(int n, int m, int sort_direction, int **arr);

void bubble_sort(int m, int *column, int sort_direction);

void selection_sort(int m,int *column, int sort_direction);

void insertion_sort(int m,int *column, int sort_direction);

void quick_sort_ascend(int *column, int inf, int sup);
int partition_ascend(int *column, int inf, int sup);

void quick_sort_descend(int *column, int inf, int sup);
int partition_descend(int *column, int inf, int sup);

void merge_sort(int *column, int left, int right);
void merge(int *column, int left, int mid, int right);

void shell_sort(int m, int *column);

void counting_sort(int n, int *column, int sort_direction);
void counting_sort_for_radix(int n, int *column, int sort_direction, int exp);

void radix_sort(int n, int *column, int sort_direction);

void comb_sort(int n, int *column, int sort_direction);

void main() {
    int** arr = NULL;
    int n, m;
    printf("input n :");
    scanf("%d", &n);
    printf("input m :");
    scanf("%d", &m);

    menu(n, m, arr);
}

void menu(int n, int m, int **arr) {
    int option;
    printf("\n		---- Menu ----  \n");
	printf("	1.Alocarea dinamica a memoriei pentru arr \n");
	printf("	2.Introducerea datelor de la tastatura\n");
	printf("	3.Completarea cu valori random \n");
	printf("	41.Sortarea ascendent pe coloane\n");
	printf("	42.Sortare descendent pe coloane\n");
	printf("	5.Afisarea arr N \n");
	printf("	0.Exit");
	printf("\nChoose number : ");	scanf("%i", &option);

	switch (option) {
	case 1:
		alocare(n, m, arr);
        break;
	case 2:
        initialize_kb(n, m, arr);
        break;
    case 3:
        initialize_rand(n, m, arr);
		break;
	case 41:
        sort_menu(n, m, 1, arr);
        menu(n, m, arr);
		break;
	case 42:
        sort_menu(n, m, -1, arr);
        menu(n, m, arr);
		break;
	case 5:
		afisare(n, m, arr);
		menu(n, m, arr);
		break;
	case 0:
		printf("---- exit ... ----");
		freemem(n, m, arr);
		exit(1);
		break;
	default:
		printf("---- error! ----");
		menu(n, m, arr);
		break;
    }
}

void alocare(int n, int m, int** arr) {
    arr = malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++){
        arr[i] = calloc(m, sizeof(int));
    }
    if(arr == NULL){
        printf("---- error alocare ----");
    }
    else{
        printf("---- succes ----");
    }
    menu(n, m, arr);
}

void initialize_kb(int n, int m, int **arr) {
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            printf("arr[%d][%d] = ", i, j);
            scanf("%d", *(arr + i) + j);
        }
    }
    menu(n, m, arr);
}

void initialize_rand(int n, int m, int **arr) {
    srand(time(NULL));
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            *(*(arr + i) + j) = rand() % 100 - 50;
        }
    }
    menu(n, m, arr);
}

void afisare(int n, int m, int** arr) {
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            printf("%d\t", *(*(arr + i) + j));
        }
        printf("\n");
    }
    menu(n, m, arr);
}

void freemem(int n, int m, int **arr) {
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

void sort_menu(int n, int m, int sort_direction, int **arr) {
	int option;
    int *column;
    column = calloc(n, sizeof(int));
	printf("\nAlegeti algoritmul de sortare : \n");
	printf("1. Bubble sort.\n");
	printf("2. Selection sort.\n");
	printf("3. Insertion sort.\n");
	printf("4. Quick sort.\n");
    printf("5. Counting sort.\n");
    printf("6. Radix sort.\n");
    printf("7. Comb sort.\n");
	if (sort_direction == 1){
		printf("8. Merge sort.\n");
		printf("9. Shell sort.\n");
	}
	printf("0. Main menu");
	printf("\nOption :");
	scanf("%d", &option);
    switch(option) {
		case 1:
            for(int i = 0; i < m; i++){
                for (int j = 0; j < n; j++){
                    *(column + j) = *(*(arr + j) + i);
                }
                bubble_sort(n, column, sort_direction);
                update_matrix(n, m, arr, column, i);
            }
            menu(n, m, arr);
            break;
		case 2:
            for(int i = 0; i < m; i++){
                for (int j = 0; j < n; j++){
                    *(column + j) = *(*(arr + j) + i);
                }
                selection_sort(n, column, sort_direction);
                update_matrix(n, m, arr, column, i);
            }
            menu(n, m, arr);
			break;
		case 3:
            for(int i = 0; i < m; i++){
                for (int j = 0; j < n; j++){
                    *(column + j) = *(*(arr + j) + i);
                }
                insertion_sort(n, column, sort_direction);
                update_matrix(n, m, arr, column, i);
            } 
            menu(n, m, arr);
			break;
		case 4:
			if(sort_direction == 1){
                for(int i = 0; i < m; i++){
                    for (int j = 0; j < n; j++){
                        *(column + j) = *(*(arr + j) + i);
                    }
                    quick_sort_ascend(column, 0, n - 1);
                    update_matrix(n, m, arr, column, i);
                }
			}
			else{
				for(int i = 0; i < m; i++){
                    for (int j = 0; j < n; j++){
                        *(column + j) = *(*(arr + j) + i);
                    }
                    quick_sort_descend(column, 0, n - 1);
                    update_matrix(n, m, arr, column, i);
			    }
            }
			menu(n, m, arr);
			break;
        case 5:
            for(int i = 0; i < m; i++){
                for (int j = 0; j < n; j++){
                    *(column + j) = *(*(arr + j) + i);
                }
                counting_sort(n, column, sort_direction);
                update_matrix(n, m, arr, column, i);
            }
            menu(n, m, arr);
			break;
        case 6:
            for(int i = 0; i < m; i++){
                for (int j = 0; j < n; j++){
                    *(column + j) = *(*(arr + j) + i);
                }
                radix_sort(n, column, sort_direction);
                update_matrix(n, m, arr, column, i);
		    }
            menu(n, m, arr);
			break;
        case 7:
            for(int i = 0; i < m; i++){
                for (int j = 0; j < n; j++){
                    *(column + j) = *(*(arr + j) + i);
                }
                comb_sort(n, column, sort_direction);
                update_matrix(n, m, arr, column, i);
			}
            menu(n, m, arr);
			break;
		case 8:
			if(sort_direction == 1) {
                for(int i = 0; i < m; i++){
                    for (int j = 0; j < n; j++){
                        *(column + j) = *(*(arr + j) + i);
                    }
                    merge_sort(column, 0, n - 1);
                    update_matrix(n, m, arr, column, i);
			    }
				menu(n, m, arr);
			}
			else {
				printf("\n**** option error! ****\n");
				sort_menu(n, m, sort_direction, arr);
			}
			break;
		case 9:
			if(sort_direction == 1) {
                for(int i = 0; i < m; i++){
                    for (int j = 0; j < n; j++){
                        *(column + j) = *(*(arr + j) + i);
                    }
                    shell_sort(n, column);
                    update_matrix(n, m, arr, column, i);
			    }
				menu(n, m, arr);
			}
			else {
				printf("\n**** option error! ****\n");
				sort_menu(n, m, sort_direction, arr);
			}
			break;
		case 0:
			menu(n, m, arr);
			break;
		default:
			printf("\n**** option error! ****\n");
			sort_menu(n, m, sort_direction, arr);
			break;
	}
}

void update_matrix(int n, int m, int **arr, int *column, int column_index) {
    for (int j = 0; j < n; j++) {
        *(*(arr + j) + column_index) = *(column + j);
    }
}

void bubble_sort(int m, int *column, int sort_direction) {
	if(sort_direction == 1){
		for (int i = 0; i < m - 1; i++) {
			for (int j = 0; j < m - i - 1; j++){
				if(*(column + j) > *(column + j + 1)) {
					swap(column + j, column + j + 1);
				}
			}
		}
	}
	else {
		for (int i = 0; i < m - 1; i++) {
			for (int j = 0; j < m - i - 1; j++){
				if(*(column + j) < *(column + j + 1)) {
					swap(column + j, column + j + 1);
				}
			}
		}
	}
}

void selection_sort(int m, int *column, int sort_direction) {
	if(sort_direction == 1){
		for (int i = 0; i < m - 1; i++) {
			for (int j = i + 1; j < m; j++){
				if(*(column + i) > *(column + j)) {
					swap(column + i, column + j);
				}
			}
		}
	}
	else {
		for (int i = 0; i < m - 1; i++) {
			for (int j = i + 1; j < m ; j++){
				if(*(column + i) < *(column + j)) {
					swap(column + i, column + j );
				}
			}
		}
	}
}

void insertion_sort(int m, int *column, int sort_direction) {
	int key, j;
	if(sort_direction == 1){
		for (int i = 1; i < m; i++){
			key = *(column + i);
			j = i - 1;
			while (j >= 0 && *(column + j) > key) {
				*(column + j + 1) = *(column + j);
				j--;
			}
			*(column + j + 1) = key;
		}
	}
	else {
		for (int i = 1; i < m; i++){
			key = *(column + i);
			j = i - 1;
			while (j >= 0 && *(column + j) < key) {
				*(column + j + 1) = *(column + j);
				j--;
			}
			*(column + j + 1) = key;
		}
	}
}

void quick_sort_ascend(int *column, int inf, int sup) {
	if(inf < sup) {
		int pi = partition_ascend(column, inf, sup);
		quick_sort_ascend(column, inf, pi - 1);
		quick_sort_ascend(column, pi + 1, sup);
	}
}

int partition_ascend(int *column, int inf, int sup) {
	int pivot = *(column + sup);
	int i = inf - 1;

	for (int j = inf; j < sup; j++){
		if(*(column + j) < pivot) {
			i++;
			swap(column + i, column + j);
		}
	}
	swap(column + i + 1, column + sup);
	return i + 1;
}

void quick_sort_descend(int *column, int inf, int sup) {
	if(inf < sup) {
		int pi = partition_descend(column, inf, sup);
		quick_sort_descend(column, inf, pi - 1);
		quick_sort_descend(column, pi + 1, sup);
	}
}

int partition_descend(int *column, int inf, int sup) {
	int pivot = *(column + sup);
	int i = inf - 1;

	for (int j = inf; j < sup; j++){
		if(*(column + j) > pivot) {
			i++;
			swap(column + i, column + j);
		}
	}
	swap(column + i + 1, column + sup);
	return i + 1;
}

void merge_sort(int *column, int left, int right) {
	if (left < right) {
		int mid = left + (right - left) / 2;

		merge_sort(column, left, mid);
		merge_sort(column, mid + 1, right);

		merge(column, left, mid, right);
	}
}

void merge(int *column, int left, int mid, int right) {
	int i, j, k;
	int n1 = mid - left + 1;
	int n2 = right - mid;

	int *Left;
	int *Right;

	Left = calloc(n1, sizeof(int));
	Right = calloc(n2, sizeof(int));

	for (i = 0; i < n1; i++){
		*(Left + i) = *(column + left + i);
	}
	for (j = 0; j < n2; j++) {
        *(Right + j) = *(column + mid + j + 1);
    }
	i = 0;
	j = 0;
	k = left;
	while(i < n1 && j < n2) {
		if(*(Left + i) <= *(Right + j)){
			*(column + k) = *(Left + i);
			i++;
		}
		else {
			*(column + k) = *(Right + j);
			j++;
		}
		k++;
	}

	while(i < n1){
		*(column + k) = *(Left + i);
		i++;
		k++;
	}
	while(j < n2){
		*(column + k) = *(Right + j);
		j++;
		k++;
	}
}


void shell_sort(int m, int *column) {
	for (int gap = m / 2; gap > 0; gap /= 2) {
		for (int i = gap; i < m; i++){
			int temp = *(column + i);
			int j;
			for (j = i; j >= gap && *(column + j - gap) > temp; j -= gap) {
				*(column + j) = *(column + j - gap);
			}
			*(column + j) = temp;
		}
	}
}

int max_num(int n, int *column) {
    int max = *column;
    for (int i = 1; i < n; i++) {
        if(max < *(column + i)){
            max = *(column + i);
        }
    }
    return max;
}

int min_num (int n, int *column) {
    int min = *column;
    for (int i = 1; i < n; i++) {
        if(min > *(column + i)){
            min = *(column + i);
        }
    }
    return min;
}

void counting_sort(int n, int *column, int sort_direction) {
    int *sorted_arr, *count_arr;
    sorted_arr = calloc(n, sizeof(int));
    count_arr = calloc(max_num(n, column) - min_num(n, column) + 1, sizeof(int));

    for (int i = 0; i < n; i++){
        ++*(count_arr + *(column + i) - min_num(n, column));
    }
    for (int i = 1; i <= max_num(n, column) - min_num(n, column); i++) {
        *(count_arr + i) += *(count_arr + i - 1);
    }
    for (int i = 0; i < n; i++) {
        *(sorted_arr + *(count_arr + *(column + i) - min_num(n, column)) - 1) = *(column + i);
        --*(count_arr + *(column + i) - min_num(n, column));
    }
    if(sort_direction == 1) {
        for (int i = 0; i < n; i++) {
            *(column + i) = *(sorted_arr + i);
        }
    }
    else {
        for (int i = 0; i < n; i++) {
            *(column + n - 1 - i) = *(sorted_arr + i);
        }
    }
}

void counting_sort_for_radix(int n, int *column, int sort_direction, int exp) {
    int *sorted_arr;
    sorted_arr = calloc(n, sizeof(int));
    int count_arr[20] = {0};
    if(sort_direction == 1) {
        for (int i = 0; *(column + i); i++){
            ++count_arr[(*(column + i) / exp) % 10 - min_num(n, column)];
        }
    }
    else {
        for (int i = 0; *(column + i); i++){
            ++count_arr[9 - (*(column + i) / exp) % 10 + min_num(n, column)];
        }
    }
    for (int i = 1; i < 20; i++) {
        count_arr[i] += count_arr[i - 1];
    }
    if(sort_direction == 1) {
        for (int i = n - 1; i >= 0; i--) {
            *(sorted_arr + count_arr[(*(column + i) / exp) % 10 - min_num(n, column)] - 1) = *(column + i);
            --count_arr[(*(column + i) / exp) % 10 - min_num(n, column)];
        }
    }
    else {
        for (int i = n - 1; i >= 0; i--) {
            *(sorted_arr + count_arr[9 - (*(column + i) / exp) % 10] - 1) = *(column + i);
            --count_arr[9 - (*(column + i) / exp) % 10];
        }
    }
    for (int i = 0; *(column + i); i++) {
        *(column + i) = *(sorted_arr + i);
    }
}

void radix_sort(int n, int *column, int sort_direction) {
    int m = max_num(n, column);

    for (int exp = 1; m / exp > 0; exp *= 10) {
        counting_sort_for_radix(n, column, sort_direction, exp);
    }
}

void comb_sort(int n, int *column, int sort_direction) {
    int gap = n;

    bool swapped = true;

    while(gap != 1 || swapped == true) {
        gap = get_next_gap(gap);

        swapped = false;
        if(sort_direction == 1) {
            for (int i = 0; i < n - gap; i++) {
                if(*(column + i) > *(column + i + gap)) {
                    swap(column + i, column + i + gap);
                    swapped = true;
                }
            }
        }
        else {
            for (int i = 0; i < n - gap; i++) {
                if(*(column + i) < *(column + i + gap)) {
                    swap(column + i, column + i + gap);
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

