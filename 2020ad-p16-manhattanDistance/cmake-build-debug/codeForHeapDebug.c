int T;
scanf("%d",&T);
Heap * xa = heap_make(250001,greater);
Heap * ya = heap_make(250001,greater);
Heap * xb = heap_make(250001,less);
Heap * yb = heap_make(250001,less);

for(int i=1;i<=T;i++){
int n;
scanf("%d",&n);
printf("Case: %d\n",i);
heap_clear(xa);
heap_clear(ya);
heap_clear(xb);
heap_clear(yb);
HeapType tx = readNum(),ty = readNum();
double midx = tx,midy = ty;
_Bool isCmbX = 0,isCmbY=0;
double d = (midx - tx > 0 ? midx - tx : tx - midx) + (midy - ty > 0 ? midy - ty : ty - midy);
printf("%.4lf\n", d);
for(int j=0;j<n-1;j++){
tx = readNum();
updateMid(xa,tx,xb,&midx,&isCmbX);
ty = readNum();
updateMid(ya,ty,yb,&midy,&isCmbY);
d += (midx - tx > 0 ? midx - tx : tx - midx) + (midy - ty > 0 ? midy - ty : ty - midy);
printf("%.4lf\n", d);
}
}
return 0;