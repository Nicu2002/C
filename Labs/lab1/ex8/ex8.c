#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void menu(int n, int m, int **arr);

void alocare(int n, int m, int **arr);
void initialize_kb(int n, int m, int **arr);
void initialize_rand(int n, int m, int **arr);
void afisare(int n, int m, int **arr);
void freemem(int n, int m, int **arr);

void swap(int *a, int *b);

void sort_menu(int n, int m, int sort_direction, int **arr);

void bubble_sort(int m, int *line, int sort_direction);

void selection_sort(int m,int *line, int sort_direction);

void insertion_sort(int m,int *line, int sort_direction);

void quick_sort_ascend(int *line, int inf, int sup);
int partition_ascend(int *line, int inf, int sup);

void quick_sort_descend(int *line, int inf, int sup);
int partition_descend(int *line, int inf, int sup);

void merge_sort(int *line, int left, int right);
void merge(int *line, int left, int mid, int right);

void shell_sort(int m, int *line);

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
	printf("	41.Sortarea ascendent pe linii\n");
	printf("	42.Sortare descendent pe linii\n");
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
            for (int i = 0; i < n; i++){
                bubble_sort(m, *(arr + i), sort_direction);
            }
                menu(n, m, arr);
            break;
		case 2:
            for (int i = 0; i < n; i++){
                selection_sort(m, *(arr + i), sort_direction);
            }
            menu(n, m, arr);
			break;
		case 3:
            for (int i = 0; i < n; i++){
                insertion_sort(m, *(arr + i), sort_direction);
            }
            menu(n, m, arr);
			break;
		case 4:
			if(sort_direction == 1){
                for (int i = 0; i < n; i++){
                    quick_sort_ascend(*(arr + i), 0, m - 1);
                }
			}
			else{
				for (int i = 0; i < n; i++){
                    quick_sort_descend(*(arr + i), 0, m - 1);
                }
			}
			menu(n, m, arr);
			break;
		case 5:
			if(sort_direction == 1) {
                for (int i = 0; i < n; i++){
                    merge_sort(*(arr + i), 0, m - 1);
                }
				menu(n, m, arr);
			}
			else {
				printf("\n**** option error! ****\n");
				sort_menu(n, m, sort_direction, arr);
			}
			break;
		case 6:
			if(sort_direction == 1) {
                for (int i = 0; i < n; i++){
                    shell_sort(m, *(arr + i));
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

void bubble_sort(int m, int *line, int sort_direction) {
	if(sort_direction == 1){
		for (int i = 0; i < m - 1; i++) {
			for (int j = 0; j < m - i - 1; j++){
				if(*(line + j) > *(line + j + 1)) {
					swap(line + j, line + j + 1);
				}
			}
		}
	}
	else {
		for (int i = 0; i < m - 1; i++) {
			for (int j = 0; j < m - i - 1; j++){
				if(*(line + j) < *(line + j + 1)) {
					swap(line + j, line + j + 1);
				}
			}
		}
	}
}

void selection_sort(int m, int *line, int sort_direction) {
	if(sort_direction == 1){
		for (int i = 0; i < m - 1; i++) {
			for (int j = i + 1; j < m; j++){
				if(*(line + i) > *(line + j)) {
					swap(line + i, line + j);
				}
			}
		}
	}
	else {
		for (int i = 0; i < m - 1; i++) {
			for (int j = i + 1; j < m ; j++){
				if(*(line + i) < *(line + j)) {
					swap(line + i, line + j );
				}
			}
		}
	}
}

void insertion_sort(int m, int *line, int sort_direction) {
	int key, j;
	if(sort_direction == 1){
		for (int i = 1; i < m; i++){
			key = *(line + i);
			j = i - 1;
			while (j >= 0 && *(line + j) > key) {
				*(line + j + 1) = *(line + j);
				j--;
			}
			*(line + j + 1) = key;
		}
	}
	else {
		for (int i = 1; i < m; i++){
			key = *(line + i);
			j = i - 1;
			while (j >= 0 && *(line + j) < key) {
				*(line + j + 1) = *(line + j);
				j--;
			}
			*(line + j + 1) = key;
		}
	}
}

void quick_sort_ascend(int *line, int inf, int sup) {
	if(inf < sup) {
		int pi = partition_ascend(line, inf, sup);
		quick_sort_ascend(line, inf, pi - 1);
		quick_sort_ascend(line, pi + 1, sup);
	}
}

int partition_ascend(int *line, int inf, int sup) {
	int pivot = *(line + sup);
	int i = inf - 1;

	for (int j = inf; j < sup; j++){
		if(*(line + j) < pivot) {
			i++;
			swap(line + i, line + j);
		}
	}
	swap(line + i + 1, line + sup);
	return i + 1;
}

void quick_sort_descend(int *line, int inf, int sup) {
	if(inf < sup) {
		int pi = partition_descend(line, inf, sup);
		quick_sort_descend(line, inf, pi - 1);
		quick_sort_descend(line, pi + 1, sup);
	}
}

int partition_descend(int *line, int inf, int sup) {
	int pivot = *(line + sup);
	int i = inf - 1;

	for (int j = inf; j < sup; j++){
		if(*(line + j) > pivot) {
			i++;
			swap(line + i, line + j);
		}
	}
	swap(line + i + 1, line + sup);
	return i + 1;
}

void merge_sort(int *line, int left, int right) {
	if (left < right) {
		int mid = left + (right - left) / 2;

		merge_sort(line, left, mid);
		merge_sort(line, mid + 1, right);

		merge(line, left, mid, right);
	}
}

void merge(int *line, int left, int mid, int right) {
	int i, j, k;
	int n1 = mid - left + 1;
	int n2 = right - mid;

	int *Left;
	int *Right;

	Left = calloc(n1, sizeof(int));
	Right = calloc(n2, sizeof(int));

	for (i = 0; i < n1; i++){
		*(Left + i) = *(line + left + i);
	}
	for (j = 0; j < n2; j++) {
        *(Right + j) = *(line + mid + j + 1);
    }
	i = 0;
	j = 0;
	k = left;
	while(i < n1 && j < n2) {
		if(*(Left + i) <= *(Right + j)){
			*(line + k) = *(Left + i);
			i++;
		}
		else {
			*(line + k) = *(Right + j);
			j++;
		}
		k++;
	}

	while(i < n1){
		*(line + k) = *(Left + i);
		i++;
		k++;
	}
	while(j < n2){
		*(line + k) = *(Right + j);
		j++;
		k++;
	}
}


void shell_sort(int m, int *line) {
	for (int gap = m / 2; gap > 0; gap /= 2) {
		for (int i = gap; i < m; i++){
			int temp = *(line + i);
			int j;
			for (j = i; j >= gap && *(line + j - gap) > temp; j -= gap) {
				*(line + j) = *(line + j - gap);
			}
			*(line + j) = temp;
		}
	}
}