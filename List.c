//
// Created by Wutianliang on 2018/11/19.
//

#include "List.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/malloc.h>
#include <strings.h>

//创建链表
void Create_list(linklist *L1){
    (*L1) = (linklist)malloc(sizeof(Node));
    (*L1)->next = NULL;
    (*L1)->length=0;
}

//头部插入结点
void Insert_Value(linklist *L1,char ISBM[],char BookName[],float price){
    Node *p;
    p = (linklist)malloc(sizeof(Node)); //新建一个结点并分配空间
    //赋值ISBM,数组，我只想到用这种方法了，会增大复杂度
    for(int j = 0 ;j < strlen(ISBM); j++){
        p->ISBM[j] = ISBM[j];
    }
    //赋值价格
    p->price = price;
    //赋值书名，数组，会增大复杂度
    for(int i = 0 ;i < strlen(BookName); i++){
        p->BookName[i] = BookName[i];
    }
    //头部插入
    p->next = (*L1)->next;
    (*L1)->next= p;
    //计数
    (*L1)->length=((*L1)->length)+1;
}


//搜索ISBM，返回结点位置
int Search_ISBM(linklist *L1,char ISBM[]){
    Node *p;
    p = (*L1)->next;
    for(int i = 0;i < (*L1)->length; i++){
        if (!strcasecmp(p->ISBM, ISBM))
        {
            printf("图书位置:%d\n",i);
            return i;
            break;
        } else{
            p = p->next;
        }

    }
    printf("查找内容不存在\n");
    return  -1;
}

//搜索书名，返回结点位置
int Search_BookName(linklist *L1,char BookName[]){
    Node *p;
    p = (*L1)->next;
    for(int i = 0;i < (*L1)->length; i++){
        if (!strcasecmp(p->BookName, BookName))
        {
            printf("图书位置:%d\n",i);
            return i;
            break;
        } else{
            p = p->next;
        }

    }
    printf("查找内容不存在\n");
    return  -1;
}

//获取链表长度
int Get_List_length(linklist *L1){
    return  (*L1)->length;
}


//删除链表
void Delete_List(linklist *L1){
        free(*L1);
}

//删除结点
void Delete_Node(linklist *L1, int n){
 if((*L1)->length>=n) {
     Node *p;
     Node *pre;//记录p遍历的前一个结点
     p = (*L1)->next;
     for (int i = 0; i < n; i++) {
         pre = p;//把p给pre
         p = p->next;
     }
     if ((*L1)->length == n) {
         //如果是尾结点
         pre->next = NULL;
     } else {
         //如果不是尾结点
         pre->next = p->next;
     }
     (*L1)->length = ((*L1)->length)-1;
 }

}

//根据结点位置改变价格
void Change_Node_price(linklist *L1, int n, float price){
    if((*L1)->length>=n) {
        Node *p;
        p = (*L1)->next;
        for (int i = 0; i < n; i++) {
            p = p->next;
        }
        p->price = price;
    }

}

//根据ISBM改变价格
void Change_Node_price_By_ISBM(linklist *L1, char ISBM[], float price){
    int n = Search_ISBM(L1,ISBM);
    Change_Node_price(L1, n, price);
    printf("修改价格成功！！");
}

//通过书名删除结点
void Delete_Node_By_BookName(linklist *L1, char BookName[]){
    int n = Search_BookName(L1,BookName);
    if(!(n==-1)){
        Delete_Node(L1,n);
        printf("成功删除！");
    }
}

//通过ISBM删除结点
void Delete_Node_By_ISBM(linklist *L1, char ISBM[]){
    int n = Search_ISBM(L1, ISBM);
    if(!(n==-1)){
        Delete_Node(L1,n);
        printf("成功删除！");
    }
}
//冒泡排序
void bubbleSort(linklist *L1)
{
    if(((*L1) -> next == NULL) || ((*L1) -> next -> next == NULL))
    {
        return;
    }

    Node *head, * pre, * cur, *next, * end, * temp;
    head = (*L1);
    end = NULL;
    //从链表头开始将较大值往后沉
    while(head -> next != end)
    {
        for(pre = head, cur = pre -> next, next = cur -> next; next != end; pre = pre -> next, cur = cur -> next, next = next -> next)
        {
            //相邻的节点比较
            if(cur -> price  > next -> price)
            {
                cur -> next = next -> next;
                pre -> next = next;
                next -> next = cur;
                temp = next;
                next = cur;
                cur = temp;
            }
        }
        end = cur;
    }
}

//导入Book.txt数据
int Import_Data(linklist *L1){
    char BookName[30];
    char ISBM[20];
    char price[8];
     FILE *fp = fopen("/Volumes/DATA_MAC/user/hsmac/CLionProjects/untitled2/book.txt","r");
     if(!fp){
         printf("没有找到该文件，文件打开失败！");
         return -1;
     } else {
         //循环到文件尾行
         while (!feof(fp)) {
             fscanf(fp, "%s %s %s", ISBM,BookName, price);
             Insert_Value(L1,ISBM,BookName,atoi(price));
         }
         fclose(fp);
         printf("导入完毕！\n");
         return 0;
     }
 }

 //打印全部图书信息
void Print_List(linklist *L1){
    Node *p;
    p = (*L1)->next;
    for(int i = 0;i < (*L1)->length; i++){
            printf("ISBM:%s 书名:%s 价格:%f\n",p->ISBM,p->BookName,p->price);
            p = p ->next;
        }

}

//菜单选择列表
void choose(linklist *L)
{
    int n, a = 1;//n用来控制选择操作类型，a控制循环，以-1终止
    char BookName[10];
    char ISBM[20];
    char price[10];
    while (a>0)
    {
        //菜单模块直接显示
        printf("\n\n");
        printf("\t\t 图书管理系统\n");
        printf("\t\t\n");
        printf("\t\t\t1.从Book本地文件导入图书信息\n");
        printf("\t\t\t2.通过书名查找链表结点位置\n");
        printf("\t\t\t3.通过ISBM查找链表结点位置\n");
        printf("\t\t\t4.添加一条图书信息\n");
        printf("\t\t\t5.通过书名删除图书信息\n");
        printf("\t\t\t6.通过ISBM删除图书信息\n");
        printf("\t\t\t7.通过ISBM修改对应图书价格\n");
        printf("\t\t\t8.按图书价格排序链表\n");
        printf("\t\t\t9.统计图书数量\n");
        printf("\t\t\t10.打印图书列表\n");
        printf("\t\t\t11.退出\n");
        printf("\t\t--------------------------\n");
        printf("请输入你的选择:");
        scanf("%d", &n);//选择操作
        switch (n)//各操作数字对应菜单数字，通过n确定操作类型
        {
            case 1://从Book本地文件导入图书信息
                Import_Data(&L);
                break;
            case 2://通过书名查找链表结点位置
                printf("请输入书名：");
                scanf("%s",BookName);
                Search_BookName(&L,BookName);
                break;
            case 3://通过ISBM查找链表结点位置
                printf("请输入ISBM：");
                scanf("%s",ISBM);
                Search_ISBM(&L,ISBM);
                break;
            case 4://添加一条图书信息
                printf("请输入ISBM：");
                scanf("%s",ISBM);
                printf("请输入书名：");
                scanf("%s",BookName);
                printf("请输入价格：");
                scanf("%s",price);
                Insert_Value(&L,ISBM,BookName,atoi(price));//price类型转float
                break;
            case 5://通过书名删除图书信息
                printf("请输入书名：");
                scanf("%s",BookName);
                Delete_Node_By_BookName(&L,BookName);
                break;
            case 6://通过ISBM删除图书信息
                printf("请输入ISBM：");
                scanf("%s",ISBM);
                Delete_Node_By_ISBM(&L,ISBM);
                break;
            case 7://通过ISBM修改对应图书价格
                printf("请输入ISBM：");
                scanf("%s",ISBM);
                printf("请输入价格：");
                scanf("%s",price);
                Change_Node_price_By_ISBM(&L,ISBM,atoi(price));
                break;
            case 8://按图书价格排序链表
                bubbleSort(&L);
                printf("排序完毕。");
                break;
            case 9://统计图书数量
                printf("图书总数量:%d\n",Get_List_length(&L));
                break;
            case 10://打印图书列表
                Print_List(&L);
                break;
            default:
                a = -1;//跳出循环条件
                Delete_List(&L);//删除链表
                break;
        }
    }
}