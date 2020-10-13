#include <stdio.h>
#include <stdlib.h>

typedef int HeapType;
typedef long long int AnsType;
typedef _Bool cmpType;

typedef struct _heap{
    HeapType * data;
    cmpType (*cmp)(HeapType *,HeapType*);
    int size;
    int max_size;
    AnsType sum;
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

void updateMid(Heap *,HeapType,Heap *,HeapType *);

HeapType readNum();//快速输入
void printNum(AnsType x);//快速输出
void printZeros();

int abs(int x){ //消除分支预测_
    int y = x >> 31;
    return (x+y) ^ y;
}


int main() {
    int T;
    scanf("%d",&T);
    Heap * xa = heap_make(270000,greater);
    Heap * ya = heap_make(270000,greater);
    Heap * xb = heap_make(270000,less);
    Heap * yb = heap_make(270000,less);
    for(int i=1;i<=T;i++){
        int n;
        scanf("%d",&n);
        printf("Case: %d\n",i);
        heap_clear(xa);  heap_clear(ya);
        heap_clear(xb);  heap_clear(yb);
        HeapType tx,ty,midx,midy;
        AnsType d=0;
        for(int j=0;j<n;j++){
            tx = readNum();
            updateMid(xa,tx,xb,&midx);
            ty = readNum();
            updateMid(ya,ty,yb,&midy);
//            d += abs(midx-tx) + abs(midy-ty);
            //另一种维护方式
            d = midx * (xa->size - xb->size) + xb->sum - xa->sum;
            d+= midy * (ya->size - yb->size) + yb->sum - ya->sum;
            printNum(d);
            printZeros();
        }
    }
    return 0;
}

void updateMid(Heap * g,HeapType in,Heap * l,HeapType * mid){
    //正确状态：左边数目等于右边数目，或者左边数目比右边多一个，这样中位数就一定是大顶堆的堆顶
    if(g->size == l->size){
        //元素个数左边等于右边，一定有一个元素插到左边
        if(g->size == 0){ //一定都是零
            heap_push(g,in);
        }else{ //一定都不是零，那么来看谁来插到左边
            if(heap_top(l) <= in){//右堆顶元素插到左边，新元素插回右边。
                heap_push(g,heap_top(l));
                heap_pop(l);
                heap_push(l,in);
            }else{ //新元素直接插到左边
                heap_push(g,in);
            }
        }
    }else{
        //适当的维护方式，使得左边必然多于右边，一定只多一个，现在考虑哪个元素插到右边
        if(heap_top(g) >= in){ //左堆顶元素插到右边，新元素插回左边
            heap_push(l,heap_top(g));
            heap_pop(g);
            heap_push(g,in);
        }else{ //新元素直接插到右边
            heap_push(l,in);
        }
    }
    *mid = heap_top(g);
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
    h->sum += elem;
}

void heap_pop(Heap * h){
    if(h->size <= 1){
        h->size = 0;
        h->sum = 0;
        return;
    }
    if(h->size == 2){
        h->data[0] = h->data[1];
        h->size--;
        h->sum = h->data[0];
        return;
    }
    h->sum -= heap_top(h);
    HeapType tmpEnd = h->data[h->size-1];
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
    h -> sum =0;
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
    h->size = 0;
    h->sum = 0;
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

void printNum(AnsType x) {
    if(x < 0) putchar('-'), x = -x;
    if(x > 9) printNum(x / 10);
    putchar(x % 10 + '0');
}
void printZeros(){
    puts(".0000");
}
