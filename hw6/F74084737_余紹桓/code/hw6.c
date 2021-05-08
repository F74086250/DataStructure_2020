#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define LEFT_WIN 1
#define RIGHT_WIN 2
#define BOTH_WIN 0

/*******************************************************************************

�ѦҺ��} : https://www.cnblogs.com/lanhaicode/p/11321243.html

�Ѧҫ�ĳ : �򥻤W�u��������������� (���D�Φr��B�ϥΦr��̾�)
           ��l���ӵۺ��}�W���N�i�H�F

���D���e : AVL�𪺴��J�`�I�B���X

��ĳ     : main�禡�ܶáA�D�n�u�O�b�B�z  �S�O���p�������Ů�

*******************************************************************************/
typedef struct Data_pack{
    char phone[11];
    char name[25];
}Data;

typedef struct AVL_TreeNode{
    int height;                 // ���Ŧ]�l
    Data *pack;                 // �ڪ���ƬO��struct Data�Ӧs(�ƻsData���r��ɭn�p��)
    struct AVL_TreeNode* L;
    struct AVL_TreeNode* R;

}AVL_Tree;
int Get_Node_Height(AVL_Tree* now)                      // ��s�`�I���ץ�
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
int compare_name(const char *a ,const char *b)          // ��Ӧr�궡�����(�r��̾�)
{                                                       // LEFT_WIN : a >  b
    int i;                                              // RIGHT_WIN : a <  b
    for(i=0; a[i]!='\0' && b[i]!='\0'; ++i)             // BOTH_WIN : a == b
        if(a[i] > b[i]) return LEFT_WIN;           // a > b
        else if(a[i] < b[i]) return RIGHT_WIN;     // a < b
    if(a[i]!='\0')return LEFT_WIN;                 // �Ya�᭱�٦���� �h�^��a>b
    if(b[i]!='\0')return RIGHT_WIN;                // �Yb�᭱�٦���� �h�^��a<b

    return BOTH_WIN;
}
int compare_data(const Data *a ,const Data *b)          //�Ω�Data���������
{
    return compare_name(a->name , b->name);             //���ⳡ���g �u�O���F���c����
}
Data* Create_Data(char* name , char* phone)             //�Ө禡�u�O��struct Data�Ϊ�
{
    int i=0;
    Data *tmp = (Data*)malloc(sizeof(Data));
    for(i=0; name[i]!='\0'; ++i)                        // �ƻs�r��ɭn�p��
        tmp->name[i] = name[i];                         // ���ઽ���� tmp->name = name
    tmp->name[i] = name[i];                             // �n�ΰj��@�Ӥ@�ӵ�

    for(i=0; phone[i]!='\0'; ++i)
        tmp->phone[i] = phone[i];
    tmp->phone[i] = phone[i];
    return tmp;
}

AVL_Tree* LL_rotate(AVL_Tree *now)                      //LL������覡
{
    AVL_Tree *tmp = now->L;                             //LL�N��������(����`)
    now->L = tmp->R;                                    //�ҥH�n���@�����ɰw����
    tmp->R = now;
    now->height = Get_Node_Height(now);                 //�ç�s����ᰪ��
    tmp->height = Get_Node_Height(tmp);
    return tmp;
}

AVL_Tree* RR_rotate(AVL_Tree *now)                      //RR������覡
{
    AVL_Tree *tmp = now->R;                             //RR�N��k������(����`)
    now->R = tmp->L;                                    //�ҥH�n���@���f�ɰw����
    tmp->L = now;
    now->height = Get_Node_Height(now);                 //�ç�s����᪺����
    tmp->height = Get_Node_Height(tmp);
    return tmp;
}


AVL_Tree* LR_rotate(AVL_Tree *now)                      // LR������覡
{
    now->L = RR_rotate(now->L);                         // ���索�l�� �@RR����
    now = LL_rotate(now);                               // �A��ۤv   �@LL����
    return now;
}

AVL_Tree* RL_rotate(AVL_Tree *now)                      // RL������覡
{
    now->R = LL_rotate(now->R);                         // ����k�l�� �@LL����
    now = RR_rotate(now);                               // �A��ۤv   �@RR����
    return now;
}
void pre_order(AVL_Tree *now)
{
    static int first_printf = 1;                        // first_print�u�O���F�L�a�M����
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
    if(now==NULL)                                       // �p�G�ثe�`�I�O�Ū�
    {
        now = (AVL_Tree*)malloc(sizeof(AVL_Tree));      // �}�l�s�W�`�I
        now->L   = NULL;
        now->R  = NULL;
        now->pack = tmp;
        now->height = Get_Node_Height(now);             // ��s����
    }
    else{
        if(compare_data(tmp , now->pack ) == LEFT_WIN)  // �p�Gtmp���Ȥ�now->pack�j
        {
            now->R = Insert_AVL_Node(now->R , tmp);     // �����J�`�I
            now->height = Get_Node_Height(now);         // �A��s����

            if(Get_Node_Height(now->R) - Get_Node_Height(now->L) > 1) // �Y����(�k�񥪲`2)
            {
                if(Get_Node_Height(now->R->R) > Get_Node_Height(now->R->L) ) // �B�zRR���p
                    now = RR_rotate(now);
                else                                                        // �B�zRL���p
                    now = RL_rotate(now);
            }
        }
        else if(compare_data(tmp , now->pack ) == RIGHT_WIN) // �p�Gtmp���Ȥ�now->pack�p
        {
            now->L = Insert_AVL_Node(now->L , tmp);     // �����J�`�I
            now->height = Get_Node_Height(now);         // �A��s����

            if(Get_Node_Height(now->L) - Get_Node_Height(now->R) > 1) // �Y����(����k�`2)
            {
                if(Get_Node_Height(now->L->L) > Get_Node_Height(now->L->R) ) // LL���p
                    now = LL_rotate(now);
                else                                                        // LR���p
                    now = LR_rotate(now);
            }
        }

        return now;
    }
    return now;
}
AVL_Tree* Search_AVL_Node(AVL_Tree* now , char *name)
{
    if(now == NULL)return NULL;                     // �����~�� �B �٨S�j�� �h�^��NULL

    if(compare_name(name , now->pack->name) == LEFT_WIN )   // �p�Gname���Ȥ�now�j
    {
        return Search_AVL_Node(now->R , name);      // ���k�仼�j�j�M
    }
    else if (compare_name(name , now->pack->name) == RIGHT_WIN ) // �p�Gname���Ȥ�now�p
    {
        return Search_AVL_Node(now->L , name);      // �����仼�j�j�M
    }
    else
        return now;                                 // ���F�A�^�Ƿ�e�`�I��}
}
int main()
{
    int first_printf=1;
    AVL_Tree *head = NULL;
    char word1[100] , word2[100], tmp;
    scanf("%c",&tmp);
    if(getchar()=='\r')
        getchar();
    while(tmp!='E')                         // �o�̪��B�z��J���I�áA�u�O���F�L�a�M����
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
