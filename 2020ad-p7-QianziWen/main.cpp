#include <iostream>

#include <cstring>

using namespace std;

typedef unsigned char Byte;

int utf_8_To_Unicode(Byte in[3]){
    int result=0;
    switch(in[0] >> 5){
        case 6: //˫�ֽں���
            result |= ( in[1] ^ ( 1 << 7 ) );
            result |= ( in[0] ^ ( 3 << 6 ) ) << 6;
            break;
        case 7: //���ֽں���
            result |= ( in[2] ^ ( 1 << 7 ) );
            result |= ( in[1] ^ ( 1 << 7 ) ) << 6;
            result |= ( in[0] ^ ( 7 << 5 ) ) << 12;
            break;
    }
    return result;
}
char * unicode_to_utf_8(int in){
    char * result = new char[4];
    memset(result,0, sizeof(char)*3);
    if(in & (31 << 11)){//�������һ�����ֽ���
        result[2] = (1 << 7) | (in & 63);
        in = in >> 6;
        result[1] = (1 << 7) | (in & 63);
        in = in >> 6;
        result[0] = (7 << 5) | (in & 15);
        //end
        result[3]= '\0';
    }else{
        result[1] = (1<<7) | (in & 63);
        in = in >> 6;
        result[0] = (3 << 6) | (in & 31);
        //end
        result[2]= '\0';
    }
    return result;
}
int main() {
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    Byte inputCache,cnTmp[3];s
    inputCache = getchar();
    int map[65550];
    memset(map,0,sizeof(map));
    while(inputCache != 255){
        if((inputCache >> 7) == 0){ //��ȡ����ascii���ڵ��ַ���ֱ������
            inputCache = getchar();
            continue;
        }
        if((inputCache >> 6) == 3){ //��ȡ���˺��ֿ�ͷ
            memset(cnTmp,0, sizeof(cnTmp));
            cnTmp[0] = inputCache;
            inputCache = getchar();
            for(int i=1;(inputCache >> 6) == 2; i++){ //��ȡ������ֵ�ʣ�ಿ��
                cnTmp[i] = inputCache;
                inputCache = getchar();
            }
//            ���ڿ��Դ������������
            map[utf_8_To_Unicode(cnTmp)]++;
        }
    }
    int outputTimes=0;
    for(int i=0;i<65550;i++){
        if(map[i]>1){
            outputTimes++;
            printf("%s 0x%04x %d\n",unicode_to_utf_8(i),i,map[i]);
        }
    }
    if(outputTimes==0){
        cout << "No repeat!" << endl;
    }
}