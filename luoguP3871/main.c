#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int HeapType;
typedef _Bool cmpType;

typedef struct _heap{
    HeapType * data;
    cmpType (*cmp)(HeapType *,HeapType*);
    int size;
    int max_size;
}Heap;


void heap_push(Heap *,HeapType);
void heap_pop(Heap *);
_Bool heap_empty(Heap *);
HeapType heap_top(Heap *);
Heap * heap_make(int max_size , cmpType (*cmp)(HeapType *,HeapType *));
void heap_delete(Heap *);
void heap_clear(Heap *);
void swap(HeapType *,HeapType *);
void heap_print(Heap *);
cmpType greater(HeapType *,HeapType *); //降序，即最大堆
cmpType less(HeapType *,HeapType *); //升序，即最小堆

void updateMid(Heap *,HeapType,Heap *,double *,_Bool *);
HeapType readNum();



int main() {
    Heap*xa = heap_make(60000,greater);
    Heap*xb = heap_make(60000,less);
    int n=0;
    scanf("%d",&n);

    _Bool isCom = 0;
    int tx = readNum();
    double mid = tx;

    for(;n>1;n--){
        tx = readNum();
        updateMid(xa, tx, xb,&mid,&isCom);
    }
    char tc[5];
    scanf("%d",&n);
    for(;n>0;n--){
        scanf("%s",tc);
        if(tc[0]=='m'){
            printf("%d\n",(int)mid);
        }else{
            tx = readNum();
            updateMid(xa, tx, xb,&mid,&isCom);
        }

    }
    return 0;
}

void updateMid(Heap * g,HeapType in,Heap * l,double * mid,_Bool * isCom){
    if(*isCom){
        if(in > *mid){
            if(in > heap_top(l)){
                *mid = heap_top(l);
                heap_pop(l);
                heap_push(l,in);
            }else{
                *mid = in;
            }
        }else{
            if(in < heap_top(g)){
                *mid = heap_top(g);
                heap_pop(g);
                heap_push(g,in);
            }else{
                *mid = in;
            }
        }
        *isCom = 0;
    }else{
        if(in > *mid){
            heap_push(g,(int)*mid);
            heap_push(l,in);
        }else{
            heap_push(l,(int)*mid);
            heap_push(g,in);
        }
        *isCom = 1;
        *mid = heap_top(g);
    }
}
void heap_print(Heap *h){
    for(int i=0;i<h->size;i++){
        printf("%d ",h->data[i]);
    }
    printf("\n");
}
void heap_push(Heap *h ,HeapType elem){
    h->data[h->size] = elem;
    h->size++;
    for(int i = h->size; i>1 ; i/=2){
        if( (*h->cmp)(h->data+i-1 , h->data+i/2-1) ){
            swap(h->data+i-1 , h->data+i/2-1);
        }else{
            break;
        }
    }
}
void heap_pop(Heap * h){
    if(h->size <=0) return;
    if(h->size <= 2){
        h->data[0] = h->data[1];
        h->size--;
        return;
    }
    HeapType  tmpEnd = h->data[h->size-1];
    h->size --;
    int i=1;

    while(i*2 <= h->size){
        if(i*2+1 <= h->size){ //如果绝对位置（非下标位置）i的子节点存在右支
            if((*h->cmp)( h->data+i*2-1,h->data+i*2)){
                //如果左枝满足进位条件
                h->data[i-1] = h->data[i*2-1];
                i=i*2;
            }else{
                //如果右枝满足进位条件
                h->data[i-1] = h->data[i*2];
                i=i*2+1;
            }
        }else{//如果绝对位置（非下标位置）i的子节点只有左枝
            h->data[i-1] = h->data[i*2-1];
            i *= 2; //直接进即可。下面写的就是对的
        }
    }
    h->data[i-1] = tmpEnd;
    for(int j = i; j>1 ; j/=2){
        if( (*h->cmp)(h->data+j-1 , h->data+j/2-1) ){
            swap(h->data+j-1 , h->data+j/2-1);
        }else{
            break;
        }
    }
}
void swap(HeapType * i,HeapType * j){
    *j = *i ^ *j;
    *i = *i ^ *j;
    *j = *i ^ *j;
}
HeapType heap_top(Heap * h){
    return *(h->data);
}
Heap * heap_make( int max_size, cmpType (*cmp)(HeapType*,HeapType*)){
    Heap * h = (Heap *)malloc(sizeof(Heap));
    h -> data = (HeapType *)malloc(sizeof(HeapType)*max_size);
    h -> size = 0;
    h ->max_size = max_size;
    h ->cmp = cmp;
    return h;
}
void heap_delete(Heap *h){
    free(h->data);
    free(h);
}
_Bool heap_empty(Heap * h){
    return (h->size <= 0);
}
void heap_clear(Heap *h){
    h->size=0;
}
cmpType greater(HeapType *i,HeapType *j){
    return *i>*j;
}
cmpType less(HeapType *i,HeapType *j){
    return *i<*j;
}

HeapType readNum(){
    int tmpChar = getchar();
    HeapType tmpNum=0;
    HeapType signal=1;
    while((tmpChar < '0' || tmpChar > '9' || tmpChar == ' ' || tmpChar == '\n')&&tmpChar!='-') tmpChar=getchar();
    if(tmpChar == '-'){
        signal = -1;
        tmpChar = getchar();
    }
    while(tmpChar >= '0' && tmpChar <= '9'){
        tmpNum = tmpNum*10 + tmpChar - '0';
        tmpChar=getchar();
    }
    return tmpNum*signal;
}