//
// Created by Wutianliang on 2018/11/19.
//

#ifndef UNTITLED2_LIST_H
#define UNTITLED2_LIST_H
//储存结构
typedef struct Node{
    char ISBM[30];
    char BookName[50];//设置50为了防止溢出
    float price;
    struct Node *next;
    int length;
}Node, *linklist;

void Create_list(linklist *L1);//创建链表
void Insert_Value(linklist *L1,char ISBM[],char BookName[],float price);//头部插入结点
int Search_ISBM(linklist *L1,char ISBM[]);//搜索ISBM，返回结点位置
int Search_BookName(linklist *L1,char BookName[]);//搜索书名，返回结点位置
int Get_List_length(linklist *L1);//获取链表长度
void Delete_List(linklist *L1);//删除链表
void Delete_Node(linklist *L1, int n); //删除结点
void Change_Node_price(linklist *L1, int n, float price); //根据结点位置改变价格
void Change_Node_price_By_ISBM(linklist *L1, char ISBM[], float price); //根据ISBM改变价格
void Delete_Node_By_BookName(linklist *L1, char BookName[]); //通过书名删除结点
void Delete_Node_By_ISBM(linklist *L1, char ISBM[]); //通过ISBM删除结点
void bubbleSort(linklist *L1); //冒泡排序
int Import_Data(linklist *L1);//从book.txt导入数据
void Print_List(linklist *L1);//打印输出全部图书数据
void choose(linklist *L);//菜单选择列表
#endif //UNTITLED2_LIST_H
