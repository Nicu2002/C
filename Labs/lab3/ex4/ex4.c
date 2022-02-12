#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

void menu(int n, int **arr, int **res_arr, int *vect);

void alocare(int n, int **arr, int **res_arr, int *vect);
void initialize_kb(int n, int **arr, int **res_arr, int *vect);
void initialize_rand(int n, int **arr, int **res_arr, int *vect);
void afisare(int n, int **arr, int **res_arr, int *vect);
void freemem(int n, int **arr);
void complete_vect(int **arr, int *vect, int n);

void swap(int *a, int *b);
int max_num(int n, int *vect);
int min_num(int n, int *vect);
int get_next_gap(int gap);
void assemble_matrix(int n, int **res_arr, int *vect, int variant);

void sort_menu(int n, int sort_direction, int **arr, int **res_arr, int *vect, int variant);

void bubble_sort(int n, int *vect, int sort_direction);

void selection_sort(int n, int *vect, int sort_direction);

void insertion_sort(int n, int *vect, int sort_direction);

void quick_sort_ascend(int *vect, int inf, int sup);
int partition_ascend(int *vect, int inf, int sup);

void quick_sort_descend(int *vect, int inf, int sup);
int partition_descend(int *vect, int inf, int sup);

void merge_sort(int *vect, int left, int right);
void merge(int *vect, int left, int mid, int right);

void shell_sort(int n, int *vect);

void counting_sort(int n, int *vect, int sort_direction);
void counting_sort_for_radix(int n, int *vect, int sort_direction, int exp);

void radix_sort(int n, int *vect, int sort_direction);

void comb_sort(int n, int *vect, int sort_direction);

void main() {
    int** arr = NULL;
    int** res_arr = NULL;
    int n;
    int *vect;
    printf("input n :");
    scanf("%d", &n);
    menu(n, arr, res_arr, vect);
}

void menu(int n, int **arr, int **res_arr, int *vect) {
    int option;
    printf("\n		---- Menu ----  \n");
	printf("	1.Alocarea dinamica a memoriei. \n");
	printf("	2.Introducerea datelor de la tastatura.\n");
	printf("	3.Completarea cu valori random. \n");
    printf("	4.Afisarea matricii initiale. \n");
	printf("	61.Create matrix a).\n");
	printf("	62.Create matrix b).\n");
    printf("	63.Create matrix c).\n");
	printf("	64.Create matrix d).\n");
    printf("	5.Afisarea matricii finale. \n");
	printf("	0.Exit.");
	printf("\nChoose number : ");	scanf("%d", &option);

	switch (option) {
        case 1:
            alocare(n, arr, res_arr, vect);
            break;
        case 2:
            initialize_kb(n, arr, res_arr, vect);
            break;
        case 3:
            initialize_rand(n, arr, res_arr, vect);
            break;
        case 4:
            afisare(n, arr, res_arr, vect);
            menu(n, arr, res_arr, vect);
            break;
        case 5:
            afisare(n, res_arr, res_arr, vect);
            menu(n, arr, res_arr, vect);
            break;
        case 61:
            sort_menu(n, 1, arr, res_arr, vect, 1);
            menu(n, arr, res_arr, vect);
            break;
        case 62:
            sort_menu(n, -1, arr, res_arr, vect, 1);
            menu(n, arr, res_arr, vect);
            break;
        case 63:
            sort_menu(n, 1, arr, res_arr, vect, 2);
            menu(n, arr, res_arr, vect);
            break;
        case 64:
            sort_menu(n, -1, arr, res_arr, vect, 2);
            menu(n, arr, res_arr, vect);
            break;
        case 0:
            printf("---- exit ... ----");
            freemem(n, arr);
            exit(1);
            break;
        default:
            printf("---- error! ----");
            menu(n, arr, res_arr, vect);
            break;
    }
}

void alocare(int n, int **arr, int **res_arr, int *vect) {
    arr = malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++){
        arr[i] = calloc(n, sizeof(int));
    }
    res_arr = malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++){
        res_arr[i] = calloc(n, sizeof(int));
    }
    vect = calloc(n * n, sizeof(int));
    if(arr == NULL){
        printf("---- error alocare ----");
    }
    else{
        printf("---- succes ----");
    }
    menu(n, arr, res_arr, vect);
}

void initialize_kb(int n, int **arr, int **res_arr, int *vect) {
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            printf("arr[%d][%d] = ", i, j);
            scanf("%d", *(arr + i) + j);
        }
    }
    complete_vect(arr, vect, n);
    menu(n, arr, res_arr, vect);
}

void initialize_rand(int n, int **arr, int **res_arr, int *vect) {
    srand(time(NULL));
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            *(*(arr + i) + j) = rand() % 100 - 50;
        }
    }
    complete_vect(arr, vect, n);
    menu(n, arr, res_arr, vect);
}

void afisare(int n, int** arr, int **res_arr, int *vect) {
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            printf("%d\t", *(*(arr + i) + j));
        }
        printf("\n");
    }
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

void complete_vect(int **arr, int *vect, int n) {
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++) {
            *(vect + i * n + j) = *(*(arr + i) + j);
        }
    }
}

void sort_menu(int n, int sort_direction, int **arr, int **res_arr, int *vect, int variant) {
	int option;
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
            bubble_sort(n * n, vect, sort_direction);
            assemble_matrix(n, res_arr, vect, variant);
            menu(n, arr, res_arr, vect);
            break;
		case 2:
            selection_sort(n * n, vect, sort_direction);
            assemble_matrix(n, res_arr, vect, variant);
            menu(n, arr, res_arr, vect);
			break;
		case 3:
            for (int i = 0; i < 4 * n - 4; i++){
                printf("%d ", *(vect + i));
            }
            insertion_sort(n * n, vect, sort_direction);
            assemble_matrix(n, res_arr, vect, variant);
            menu(n, arr, res_arr, vect);
			break;
		case 4:
			if(sort_direction == 1){
                quick_sort_ascend(vect, 0, n * n - 1);
                assemble_matrix(n, res_arr, vect, variant);
			}
			else{
                quick_sort_descend(vect, 0, n * n - 1);
                assemble_matrix(n, res_arr, vect, variant);
            }
			menu(n, arr, res_arr, vect);
			break;
        case 5:
            counting_sort(n * n, vect, sort_direction);
            assemble_matrix(n, res_arr, vect, variant);
            menu(n, arr, res_arr, vect);
			break;
        case 6:
            radix_sort(n * n, vect, sort_direction);
            assemble_matrix(n, res_arr, vect, variant);
            menu(n, arr, res_arr, vect);
			break;
        case 7:
            comb_sort(n * n, vect, sort_direction);
            assemble_matrix(n, res_arr, vect, variant);
            menu(n, arr, res_arr, vect);
			break;
		case 8:
			if(sort_direction == 1) {
                merge_sort(vect, 0, n * n - 1);
                assemble_matrix(n, res_arr, vect, variant);
				menu(n, arr, res_arr, vect);
			}
			else {
				printf("\n**** option error! ****\n");
				sort_menu(n, sort_direction, arr, res_arr, vect, variant);
			}
			break;
		case 9:
			if(sort_direction == 1) {
                shell_sort(n * n, vect);
                assemble_matrix(n, res_arr, vect, variant);
				menu(n, arr, res_arr, vect);
			}
			else {
				printf("\n**** option error! ****\n");
				sort_menu(n, sort_direction, arr, res_arr, vect, variant);
			}
			break;
		case 0:
			menu(n, arr, res_arr, vect);
			break;
		default:
			printf("\n**** option error! ****\n");
			sort_menu(n, sort_direction, arr, res_arr, vect, variant);
			break;
	}
}

void assemble_matrix(int n, int **res_arr, int *vect, int variant) {
    if(variant == 1) {
        int direction = 1;
        for (int i = 0; i < n; i++){
            if(direction == 1) {
                for (int j = 0; j < n; j++){
                    *(*(res_arr + i) + j) = *(vect + n * i + j);
                }
                direction = -1;
            }
            else {
                for (int j = n - 1; j >= 0; j--){
                    *(*(res_arr + i) + j) = *(vect + n * (i + 1) - j - 1);
                }
                direction = 1;
            } 
        }
    }
    else {
        int layers_num;
        int counter = 0;
        if(n % 2 == 0) {
            layers_num = n / 2;
        }
        else{
            layers_num = n / 2 + 1;
            *(*(res_arr + layers_num - 1) + layers_num - 1) = *(vect + n * n - 1);
        }
        for (int i = 0; i < layers_num; i++){
            for (int j = i; j < n - i - 1; j++) {
                *(*(res_arr + i) + j) = *(vect + counter);
                counter++;
            }
            for (int j = i; j < n - i - 1; j++) {
                *(*(res_arr + j) + n - i - 1) = *(vect + counter);
                counter++;
            }
            for (int j = n - i - 1; j > i; j--) {
                *(*(res_arr + n - i - 1) + j) = *(vect + counter);
                counter++;
            }
            for (int j = n - i - 1; j > i; j--) {
                *(*(res_arr + j) + i) = *(vect + counter);
                counter++;
            }
        }
    }
}

void bubble_sort(int n, int *vect, int sort_direction) {
	if(sort_direction == 1){
		for (int i = 0; i < n - 1; i++) {
			for (int j = 0; j < n - i - 1; j++){
				if(*(vect + j) > *(vect + j + 1)) {
					swap(vect + j, vect + j + 1);
				}
			}
		}
	}
	else {
		for (int i = 0; i < n - 1; i++) {
			for (int j = 0; j < n - i - 1; j++){
				if(*(vect + j) < *(vect + j + 1)) {
					swap(vect + j, vect + j + 1);
				}
			}
		}
	}
}

void selection_sort(int n, int *vect, int sort_direction) {
	if(sort_direction == 1){
		for (int i = 0; i < n - 1; i++) {
			for (int j = i + 1; j < n; j++){
				if(*(vect + i) > *(vect + j)) {
					swap(vect + i, vect + j);
				}
			}
		}
	}
	else {
		for (int i = 0; i < n - 1; i++) {
			for (int j = i + 1; j < n ; j++){
				if(*(vect + i) < *(vect + j)) {
					swap(vect + i, vect + j );
				}
			}
		}
	}
}

void insertion_sort(int n, int *vect, int sort_direction) {
	int key, j;
	if(sort_direction == 1){
		for (int i = 1; i < n; i++){
			key = *(vect + i);
			j = i - 1;
			while (j >= 0 && *(vect + j) > key) {
				*(vect + j + 1) = *(vect + j);
				j--;
			}
			*(vect + j + 1) = key;
		}
	}
	else {
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
}

void quick_sort_ascend(int *vect, int inf, int sup) {
	if(inf < sup) {
		int pi = partition_ascend(vect, inf, sup);
		quick_sort_ascend(vect, inf, pi - 1);
		quick_sort_ascend(vect, pi + 1, sup);
	}
}

int partition_ascend(int *vect, int inf, int sup) {
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

void quick_sort_descend(int *vect, int inf, int sup) {
	if(inf < sup) {
		int pi = partition_descend(vect, inf, sup);
		quick_sort_descend(vect, inf, pi - 1);
		quick_sort_descend(vect, pi + 1, sup);
	}
}

int partition_descend(int *vect, int inf, int sup) {
	int pivot = *(vect + sup);
	int i = inf - 1;

	for (int j = inf; j < sup; j++){
		if(*(vect + j) > pivot) {
			i++;
			swap(vect + i, vect + j);
		}
	}
	swap(vect + i + 1, vect + sup);
	return i + 1;
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

void counting_sort(int n, int *vect, int sort_direction) {
    int *sorted_arr, *count_arr;
    sorted_arr = calloc(n, sizeof(int));
    count_arr = calloc(max_num(n, vect) - min_num(n, vect) + 1, sizeof(int));

    for (int i = 0; i < n; i++){
        ++*(count_arr + *(vect + i) - min_num(n, vect));
    }
    for (int i = 1; i <= max_num(n, vect) - min_num(n, vect); i++) {
        *(count_arr + i) += *(count_arr + i - 1);
    }
    for (int i = 0; i < n; i++) {
        *(sorted_arr + *(count_arr + *(vect + i) - min_num(n, vect)) - 1) = *(vect + i);
        --*(count_arr + *(vect + i) - min_num(n, vect));
    }
    if(sort_direction == 1) {
        for (int i = 0; i < n; i++) {
            *(vect + i) = *(sorted_arr + i);
        }
    }
    else {
        for (int i = 0; i < n; i++) {
            *(vect + n - 1 - i) = *(sorted_arr + i);
        }
    }
}

void counting_sort_for_radix(int n, int *vect, int sort_direction, int exp) {
    int *sorted_arr;
    sorted_arr = calloc(n, sizeof(int));
    int count_arr[20] = {0};
    if(sort_direction == 1) {
        for (int i = 0; *(vect + i); i++){
            ++count_arr[(*(vect + i) / exp) % 10 - min_num(n, vect)];
        }
    }
    else {
        for (int i = 0; *(vect + i); i++){
            ++count_arr[9 - (*(vect + i) / exp) % 10 + min_num(n, vect)];
        }
    }
    for (int i = 1; i < 20; i++) {
        count_arr[i] += count_arr[i - 1];
    }
    if(sort_direction == 1) {
        for (int i = n - 1; i >= 0; i--) {
            *(sorted_arr + count_arr[(*(vect + i) / exp) % 10 - min_num(n, vect)] - 1) = *(vect + i);
            --count_arr[(*(vect + i) / exp) % 10 - min_num(n, vect)];
        }
    }
    else {
        for (int i = n - 1; i >= 0; i--) {
            *(sorted_arr + count_arr[9 - (*(vect + i) / exp) % 10] - 1) = *(vect + i);
            --count_arr[9 - (*(vect + i) / exp) % 10];
        }
    }
    for (int i = 0; *(vect + i); i++) {
        *(vect + i) = *(sorted_arr + i);
    }
}

void radix_sort(int n, int *vect, int sort_direction) {
    int m = max_num(n, vect);

    for (int exp = 1; m / exp > 0; exp *= 10) {
        counting_sort_for_radix(n, vect, sort_direction, exp);
    }
}

void comb_sort(int n, int *vect, int sort_direction) {
    int gap = n;

    bool swapped = true;

    while(gap != 1 || swapped == true) {
        gap = get_next_gap(gap);

        swapped = false;
        if(sort_direction == 1) {
            for (int i = 0; i < n - gap; i++) {
                if(*(vect + i) > *(vect + i + gap)) {
                    swap(vect + i, vect + i + gap);
                    swapped = true;
                }
            }
        }
        else {
            for (int i = 0; i < n - gap; i++) {
                if(*(vect + i) < *(vect + i + gap)) {
                    swap(vect + i, vect + i + gap);
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
