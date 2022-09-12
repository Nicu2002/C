#ifndef FOO_DOT_H    
#define FOO_DOT_H    

typedef struct StatData {
    char name[15];
    char capital[15];
    int surface;
    int population;
    int PIT;
} StatData;

typedef struct Stat {
    StatData data;
    struct Stat *next;
} Stat;

typedef struct Queue {
    Stat *head, *tail;
} Queue;

void initList(int n);
void initData();
void showData();
void searchBySurface();
void modifyByPosition();
void findLastPosition();
void swap(Stat *a, Stat *b);
void sortList(int n);

#endif 