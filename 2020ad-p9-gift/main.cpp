#include <iostream>

using namespace std;

class Node{
public:
    char data;
    Node * next;
    Node(int defaultnum=0):data(defaultnum){
        this->next=NULL;
    }
};

class List{
public:
    Node * head;
    Node * tail;
    List():head(NULL),tail(NULL){}
    void push(char data){
        if(head){
            tail->next = new Node(data);
            tail = tail->next;
        }else{
            head = new Node(data);
            tail = head;
        }
    }
    void pop(){
        if(head){
            tail->next = NULL;
            if(tail == head){
                delete head;
                tail = head = NULL;
            }else{
                Node * p = head->next;
                delete head;
                head = p;
            }
        }
    }
    ~List(){
        while(head){
            pop();
        }
    }

    static List * copy(List * source){
        List * target = new List();
        for(Node * p = source->head;p!=NULL;p=p->next){
            target->push(p->data);
        }
        return target;
    }
};

int main() {
    List * shelf = new List();
    List * target = new List();
    int target_cnt=0;
    char c=getchar();
    while(c>='a' && c <='z'){
        shelf->push(c);
        c=getchar();
    }
    while(c<'a' || c >'z'){
        c=getchar();
    }
    while(c>='a' && c <='z'){
        target->push(c);
        target_cnt++;
        c=getchar();
    }
    target->tail->next = target->head;
    Node * p0 = target->head;
    List * shelf_bak;
    for(int target_cnt_bak = target_cnt; target_cnt_bak>0;){
        target_cnt_bak = target_cnt;
        shelf_bak = List::copy(shelf);
        Node * p = p0;
        for(int i=0;i<2;i++){
            for(Node * pp = shelf_bak->head ; pp!=NULL && target_cnt_bak > 0 && pp->data!='0'; pp=pp->next){
                if(pp!=NULL){
                    if(p->data == pp->data){
                        pp->data = '0';
                        target_cnt_bak--;
                        p = p->next;
                    }
                }
            }
        }
        if(target_cnt_bak>0){
            delete shelf_bak;
        }
        p0 = p0->next;
    }


    int i=1;
    for(Node * p = shelf_bak->head; p!=NULL ; p=p->next){
        if(p->data == '0'){
            cout << i ;
            target_cnt--;
            if(target_cnt!=0){
                cout << " ";
            }else{
                cout << endl;
            }
        }
        i++;
    }
    return 0;
}
