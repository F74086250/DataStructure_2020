#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
typedef struct edge{
    int node_index;
    int weight;
    struct edge* next;
}Edge;

typedef struct input{
    int pre_node;
    int link_node;
    int weight;
}Input;

typedef struct link{
    int count;
    Edge *next;
}Link;

typedef struct stack{
    int Link_index;
    struct stack* next;
}Stack;

void Stack_push(Stack **p , int index)
{
    Stack* temp = (Stack*)malloc(sizeof(Stack));
    temp->Link_index = index;
    temp->next = *p;
    *p = temp;
}

int Stack_pop(Stack **p)
{
    int index = (*p)->Link_index;
    *p = (*p)->next;
    return index;
}


void Link_Add ( Link *father , Link *child , int node_index , int weight)
{
    Edge *p = (Edge*)malloc(sizeof(Edge));
    p->next = father->next;
    p->weight = weight;
    p->node_index = node_index;
    father->next  = p;
    child->count+= 1;
}
void Initial_link(Link *E , Link *L)
{
    E->count = 0;
    E->next = NULL;
    L->count = 0;
    L->next = NULL;
}

void Print_Link(Link target[], int n)
{
    int i;
    Edge *p;
    for(i=0; i<=n; i++)
    {
        p = target[i].next;
        printf("%d link : " , i);
        while(p!=NULL)
        {
            printf("%d ",p->node_index);
            p = p->next;
        }
        printf("count = %d\n",target[i].count);
    }
}

void Find_Early(Link Early_Link[] , int Early_value[] , int node_size)
{
    int now_index;
    Stack *Link_Stack = NULL;
    Stack_push(&Link_Stack , 0);
    while(Link_Stack!=NULL)
    {
            now_index = Stack_pop(&Link_Stack);          // index表示目前在哪個節點
            Edge *p = Early_Link[now_index].next;       // 開始遍歷每個Edge
            //printf("現在開始遍歷%d\n",now_index);
            while(p!=NULL)
            {
                int result = Early_value[now_index] + p->weight;

                if( Early_value[p->node_index] < result){
                    //printf("Early_value[%d] = %d\t",p->node_index , result);
                    Early_value[p->node_index] = result;
                }

                Early_Link[p->node_index].count -= 1;
                if( Early_Link[p->node_index].count ==0 ){
                    //printf("將%d加入stack",p->node_index);
                    Stack_push(&Link_Stack , p->node_index);
                }
                //printf("\n");
                p = p->next;
            }
    }

}
void Find_Late(Link Late_Link[] , int Late_value[] , int node_size)
{
    int now_index;
    Stack *Link_Stack = NULL;
    Stack_push(&Link_Stack , node_size);
    while(Link_Stack!=NULL)
    {
            now_index = Stack_pop(&Link_Stack);          // index表示目前在哪個節點
            Edge *p = Late_Link[now_index].next;       // 開始遍歷每個Edge
            //printf("現在開始遍歷%d\n",now_index);
            while(p!=NULL)
            {
                int result = Late_value[now_index] - p->weight;

                if( Late_value[p->node_index] > result){
                    //printf("Late_value[%d] = %d\t",p->node_index , result);
                    Late_value[p->node_index] = result;
                }

                Late_Link[p->node_index].count -= 1;
                if( Late_Link[p->node_index].count ==0 ){
                    //printf("將%d加入stack",p->node_index);
                    Stack_push(&Link_Stack , p->node_index);
                }
                //printf("\n");
                p = p->next;
            }
    }
}
void Output(Input A[],int Early_value[],int Late_Value[],int path_size)
{
    int L , R , Early , Late;
    int ans[path_size] , length=0;
    int first_print=1;
    for(int i=0; i<path_size; i++){
        L = A[i].pre_node;
        R = A[i].link_node;
        Early = Early_value[L];
        Late  = Late_Value[R]-A[i].weight;
        printf("%d %d %d\n" , i , Early , Late);
        if(Early == Late)
            ans[length++] = i;
    }
    for(int i=0; i<length ; i++){
        if(!first_print)
            printf(" ");
        else
            first_print=0;
        printf("%d",ans[i]);
    }
}
int main()
{
    int i,n , node_size=0;
    int t1,t2,t3,t4;
    int Early_value[101] ;
    int Late_value [101] ;
    Link  Early_link[101];
    Link  Late_link [101];
    Input A[1000];

    scanf("%d",&n);
    for(i=0 ; i<101 ; i++){
        Initial_link(&Early_link[i] , &Late_link[i]);
        Early_value[i] = 0;
        Late_value [i] = 0;             // 晚點才會放最大路徑的值
    }
    for(i=0 ; i<n ; i++)
    {
        scanf("%d%d%d%d",&t1,&t2,&t3,&t4);
        A[i].pre_node  = t2;
        A[i].link_node = t3;
        A[i].weight    = t4;
        Link_Add(&Early_link[t2], &Early_link[t3], t3 , t4);
        Link_Add(&Late_link[t3] , &Late_link[t2], t2 , t4);
        if(node_size<t3)
            node_size = t3;

    }

    Find_Early(Early_link , Early_value , node_size);
    for(i=0 ; i<=node_size ; i++)
        Late_value[i] = Early_value[node_size];
    Find_Late (Late_link  , Late_value  , node_size);

    Output(A , Early_value , Late_value , n);
}
