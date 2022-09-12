#ifndef FOO_DOT_H    
#define FOO_DOT_H    

typedef struct Stat {
    char name[15];
    char capital[15];
    int surface;
    int population;
    int PIT;
    struct Stat *next;
} Stat;

void initList(int n);
void initData();
void showData();
void searchBySurface();
void modifyByPosition();
void findLastPosition();
void swap(int a, int b);
void sortList(int n);

#endif 