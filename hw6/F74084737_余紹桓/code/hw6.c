#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define LEFT_WIN 1
#define RIGHT_WIN 2
#define BOTH_WIN 0

/*******************************************************************************

參考網址 : https://www.cnblogs.com/lanhaicode/p/11321243.html

參考建議 : 基本上只有比較的部分改變 (該題用字串且使用字典依據)
           其餘都照著網址上的就可以了

該題內容 : AVL樹的插入節點、走訪

建議     : main函式很亂，主要只是在處理  特別情況的換行跟空格

*******************************************************************************/
typedef struct Data_pack{
    char phone[11];
    char name[25];
}Data;

typedef struct AVL_TreeNode{
    int height;                 // 平衡因子
    Data *pack;                 // 我的資料是用struct Data來存(複製Data的字串時要小心)
    struct AVL_TreeNode* L;
    struct AVL_TreeNode* R;

}AVL_Tree;
int Get_Node_Height(AVL_Tree* now)                      // 更新節點高度用
{
    if(now == NULL)
        return 0;
    if(now->L==NULL && now->R==NULL)
        return 1;
    if(Get_Node_Height(now->L) > Get_Node_Height(now->R))
        return now->L->height+1;
    else
        return now->R->height+1;

}
int compare_name(const char *a ,const char *b)          // 兩個字串間的比較(字典依據)
{                                                       // LEFT_WIN : a >  b
    int i;                                              // RIGHT_WIN : a <  b
    for(i=0; a[i]!='\0' && b[i]!='\0'; ++i)             // BOTH_WIN : a == b
        if(a[i] > b[i]) return LEFT_WIN;           // a > b
        else if(a[i] < b[i]) return RIGHT_WIN;     // a < b
    if(a[i]!='\0')return LEFT_WIN;                 // 若a後面還有資料 則回傳a>b
    if(b[i]!='\0')return RIGHT_WIN;                // 若b後面還有資料 則回傳a<b

    return BOTH_WIN;
}
int compare_data(const Data *a ,const Data *b)          //用於Data之間的比較
{
    return compare_name(a->name , b->name);             //分兩部分寫 只是為了結構分明
}
Data* Create_Data(char* name , char* phone)             //該函式只是給struct Data用的
{
    int i=0;
    Data *tmp = (Data*)malloc(sizeof(Data));
    for(i=0; name[i]!='\0'; ++i)                        // 複製字串時要小心
        tmp->name[i] = name[i];                         // 不能直接用 tmp->name = name
    tmp->name[i] = name[i];                             // 要用迴圈一個一個給

    for(i=0; phone[i]!='\0'; ++i)
        tmp->phone[i] = phone[i];
    tmp->phone[i] = phone[i];
    return tmp;
}

AVL_Tree* LL_rotate(AVL_Tree *now)                      //LL的旋轉方式
{
    AVL_Tree *tmp = now->L;                             //LL代表左邊比較重(比較深)
    now->L = tmp->R;                                    //所以要做一次順時針旋轉
    tmp->R = now;
    now->height = Get_Node_Height(now);                 //並更新旋轉後高度
    tmp->height = Get_Node_Height(tmp);
    return tmp;
}

AVL_Tree* RR_rotate(AVL_Tree *now)                      //RR的旋轉方式
{
    AVL_Tree *tmp = now->R;                             //RR代表右邊比較重(比較深)
    now->R = tmp->L;                                    //所以要做一次逆時針旋轉
    tmp->L = now;
    now->height = Get_Node_Height(now);                 //並更新旋轉後的高度
    tmp->height = Get_Node_Height(tmp);
    return tmp;
}


AVL_Tree* LR_rotate(AVL_Tree *now)                      // LR的旋轉方式
{
    now->L = RR_rotate(now->L);                         // 先對左子樹 作RR旋轉
    now = LL_rotate(now);                               // 再對自己   作LL旋轉
    return now;
}

AVL_Tree* RL_rotate(AVL_Tree *now)                      // RL的旋轉方式
{
    now->R = LL_rotate(now->R);                         // 先對右子樹 作LL旋轉
    now = RR_rotate(now);                               // 再對自己   作RR旋轉
    return now;
}
void pre_order(AVL_Tree *now)
{
    static int first_printf = 1;                        // first_print只是為了過冠霖測資
    if(now==NULL)return;
    if(first_printf)
        first_printf=0;
    else
        printf(" ");
    printf("%s",now->pack->name);
    pre_order(now->L);
    pre_order(now->R);

}
AVL_Tree* Insert_AVL_Node(AVL_Tree *now , Data *tmp)
{
    if(now==NULL)                                       // 如果目前節點是空的
    {
        now = (AVL_Tree*)malloc(sizeof(AVL_Tree));      // 開始新增節點
        now->L   = NULL;
        now->R  = NULL;
        now->pack = tmp;
        now->height = Get_Node_Height(now);             // 更新高度
    }
    else{
        if(compare_data(tmp , now->pack ) == LEFT_WIN)  // 如果tmp的值比now->pack大
        {
            now->R = Insert_AVL_Node(now->R , tmp);     // 先插入節點
            now->height = Get_Node_Height(now);         // 再更新高度

            if(Get_Node_Height(now->R) - Get_Node_Height(now->L) > 1) // 若失衡(右比左深2)
            {
                if(Get_Node_Height(now->R->R) > Get_Node_Height(now->R->L) ) // 處理RR情況
                    now = RR_rotate(now);
                else                                                        // 處理RL情況
                    now = RL_rotate(now);
            }
        }
        else if(compare_data(tmp , now->pack ) == RIGHT_WIN) // 如果tmp的值比now->pack小
        {
            now->L = Insert_AVL_Node(now->L , tmp);     // 先插入節點
            now->height = Get_Node_Height(now);         // 再更新高度

            if(Get_Node_Height(now->L) - Get_Node_Height(now->R) > 1) // 若失衡(左比右深2)
            {
                if(Get_Node_Height(now->L->L) > Get_Node_Height(now->L->R) ) // LL情況
                    now = LL_rotate(now);
                else                                                        // LR情況
                    now = LR_rotate(now);
            }
        }

        return now;
    }
    return now;
}
AVL_Tree* Search_AVL_Node(AVL_Tree* now , char *name)
{
    if(now == NULL)return NULL;                     // 走到樹外面 且 還沒搜到 則回傳NULL

    if(compare_name(name , now->pack->name) == LEFT_WIN )   // 如果name的值比now大
    {
        return Search_AVL_Node(now->R , name);      // 往右邊遞迴搜尋
    }
    else if (compare_name(name , now->pack->name) == RIGHT_WIN ) // 如果name的值比now小
    {
        return Search_AVL_Node(now->L , name);      // 往左邊遞迴搜尋
    }
    else
        return now;                                 // 找到了，回傳當前節點位址
}
int main()
{
    int first_printf=1;
    AVL_Tree *head = NULL;
    char word1[100] , word2[100], tmp;
    scanf("%c",&tmp);
    if(getchar()=='\r')
        getchar();
    while(tmp!='E')                         // 這裡的處理輸入有點亂，只是為了過冠霖測資
    {
        if(tmp=='D'){
            scanf("%s",word1);
            if(word1[1]!='\0'){
                first_printf=0;
                scanf("%s",word2);
                if(getchar()=='\r')
                    getchar();
                Data *p = Create_Data(word1 , word2);
                head = Insert_AVL_Node(head , p);
            }
            else{
                tmp=word1[0];
                pre_order(head);
            }
        }
        if(tmp=='S'){
            scanf("%s",word1);
            if(word1[1]!='\0'){
                if(getchar()=='\r')
                    getchar();


                AVL_Tree *tmp = Search_AVL_Node(head , word1);

                if(first_printf)
                    first_printf=0;
                else
                    printf("\n");

                if(tmp==NULL)
                    printf("%s null",word1);
                else
                    printf("%s %s",word1,tmp->pack->phone);
            }
            else
                tmp=word1[0];
        }
    }
    return 0;
}
