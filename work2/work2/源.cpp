#include "stdio.h"
#include "stdlib.h"
#include<string.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int status;
typedef int ElemType; //数据元素类型定义

#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef int ElemType;
typedef struct LNode{  //单链表（链式结构）结点的定义
	ElemType data;
	struct LNode *next;
}LNode, *LinkList;
typedef struct{  //线性表的管理表定义
	struct {
		char name[30];
		LinkList L;
	} elem[10];
	int length;
	int listsize;
}LISTS;
status InitList(LinkList &L)
// 1.线性表L不存在，构造一个空的线性表，返回OK，否则返回INFEASIBLE。
{
	if (L != NULL)return INFEASIBLE;
	L = (LNode*)malloc(sizeof(LNode));
	L->next = NULL;
	L->data = 0;
	return OK;
}
status DestroyList(LinkList &L)
// 2.如果线性表L存在，销毁线性表L，释放数据元素的空间，返回OK，否则返回INFEASIBLE。
{
	if (L == NULL)return INFEASIBLE;
	LinkList p = L->next;
	while (p != NULL){
		free(L);
		L = p;
		p = L->next;
	}
	free(L);
	L = NULL;
	return OK;
}

status ClearList(LinkList &L)
// 3.如果线性表L存在，删除线性表L中的所有元素，返回OK，否则返回INFEASIBLE。
{
	
	if (L == NULL)return INFEASIBLE;

	LinkList p1 = L->next, L1 = L;
	while (p1 != NULL){
		L1 = p1;
		p1 = L1->next;
		free(L1);
	}
	L->next = NULL;
	return OK;
}
status ListEmpty(LinkList L)
// 4.如果线性表L存在，判断线性表L是否为空，空就返回TRUE，否则返回FALSE；如果线性表L不存在，返回INFEASIBLE。
{
	if (L == NULL)return INFEASIBLE;
	if (L->next == NULL)return TRUE;
	return FALSE;
}
int ListLength(LinkList L)
// 5.如果线性表L存在，返回线性表L的长度，否则返回INFEASIBLE。
{
	if (L == NULL)return INFEASIBLE;
	int n = 0;
	while (L = L->next)n++;
	return n;
}
status GetElem(LinkList L, int i, ElemType &e)
// 6.如果线性表L存在，获取线性表L的第i个元素，保存在e中，返回OK；如果i不合法，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
	if (L == NULL)return INFEASIBLE;
	if (i<1)return ERROR;
	for (int j = 0; j<i; j++){
		L = L->next;
		if (L == NULL)return ERROR;
	}
	e = L->data;
	return OK;
}
status LocateElem(LinkList L, ElemType e)
// 7.如果线性表L存在，查找元素e在线性表L中的位置序号；如果e不存在，返回ERROR；当线性表L不存在时，返回INFEASIBLE。
{
	if (L == NULL)return INFEASIBLE;
	int i = 0;
	while (L->next != NULL){
		L = L->next;
		i++;
		if (L->data == e)return i;
	}
	return ERROR;
}
status PriorElem(LinkList L, ElemType e, ElemType &pre)
// 8.如果线性表L存在，获取线性表L中元素e的前驱，保存在pre中，返回OK；如果没有前驱，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
	if (L == NULL)return INFEASIBLE;
	while (L->next != NULL){
		if (L->next->data == e){
			if (L->data == 0)return ERROR;
			pre = L->data;
			return OK;
		}
		L = L->next;
	}
	return ERROR;
}
status NextElem(LinkList L, ElemType e, ElemType &next)
// 9.如果线性表L存在，获取线性表L元素e的后继，保存在next中，返回OK；如果没有后继，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
	if (L == NULL)return INFEASIBLE;
	L = L->next;
	if (L == NULL)return ERROR;
	while (L->next != NULL){
		if (L->data == e){
			next = L->next->data;
			return OK;
		}
		L = L->next;
	}
	return ERROR;
}
status ListInsert(LinkList &L, int i, ElemType e)
// 10.如果线性表L存在，将元素e插入到线性表L的第i个元素之前，返回OK；当插入位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
	if (L == NULL)return INFEASIBLE;
	if (i <= 0)return ERROR;
	LinkList p1 = L, p2;
	for (int j = 1; j<i; j++){
		p1 = p1->next;
		if (p1 == NULL)return ERROR;
	}
	p2 = (LinkList)malloc(sizeof(LNode));
	p2->data = e;
	p2->next = p1->next;
	p1->next = p2;
	return OK;
}
status ListDelete(LinkList &L, int i, ElemType &e)
// 11.如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK；当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
	if (L == NULL)return INFEASIBLE;
	if (i <= 0)return ERROR;
	LinkList p1 = L, p2;
	for (int j = 1; j<i; j++){
		p1 = p1->next;
		if (p1->next == NULL)return ERROR;
	}
	p2 = p1->next;
	p1->next = p2->next;
	e = p2->data;
	free(p2);
	return OK;
}
status ListTraverse(LinkList L)
// 12.如果线性表L存在，依次显示线性表中的元素，每个元素间空一格，返回OK；如果线性表L不存在，返回INFEASIBLE。
{
	if (L == NULL)return INFEASIBLE;
	L = L->next;
	while (L != NULL){
		printf("%d ", L->data);
		L = L->next;
	}
	return OK;
}
status reverseList(LinkList &L){
//13.链表反转，返回OK，若链表不存在返回INFEASIBLE；若链表为空返回ERROR；
	if (L == NULL)return INFEASIBLE;
	if (L->next == NULL)return ERROR;
	LinkList L1 = L->next;
	if (L1->next == NULL)return OK;
	LinkList L2 = L1->next;
	if (L2->next == NULL){
		L2->next = L1;
		L1->next = NULL;
		L->next = L2;
		return OK;
	}
	LinkList L3 = L2->next;
	L1->next = NULL;
	do{
		L2->next = L1;
		L1 = L2;
		L2 = L3;
		L3 = L3->next;
	} while (L3 != NULL);
	L2->next = L1;
	L->next = L2;
	return OK;
}
status RemoveNthFromEnd(LinkList&L, int n){
//14.删除倒数	n个节点，若成功返回结点值，若线性表为空返回INFEASIBLE，删除失败返回ERROR。
	if (L == NULL)return INFEASIBLE;
	if (n <= 0)return ERROR;
	int length = ListLength(L);
	if (length < n)return ERROR;
	
	LinkList L1 = L;
	for (int i = 0; i < length - n; i++){
		L1 = L1->next;
	}
	LinkList L2 = L1->next;
	L1->next = L2->next;
	int ans = L2->data;
	free(L2);
	return ans;
}
status sortList(LinkList &L){
//15线性表排序，成功返回OK，不存在返回INFEASIBLE，空表返回ERROR;
	if (L == NULL)return INFEASIBLE;
	if (L->next == NULL)return ERROR;
	LinkList L1 = L->next,L2=L1,L3;
	int min;
	while (L1 != NULL){
		min = L1->data;
		L3 = L1;
		L2 = L1;
		while (L2 != NULL){
			if (L2->data < min){
				min = L2->data;
				L3 = L2;
			}
			L2 = L2->next;
		}L3->data = L1->data;
		L1->data = min;
		L1 = L1->next;
	}
	return OK;
}
status  SaveList(LinkList L, char FileName[])
// 如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
{
	if (L == NULL)return INFEASIBLE;
	FILE *fp = fopen(FileName, "w");
	L = L->next;
	while (L != NULL){
		fprintf(fp, "%d ", L->data);
		L = L->next;
	}
	fclose(fp);
	return OK;
}
status  LoadList(LinkList &L, char FileName[])
// 如果线性表L不存在，将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。
{
	if (L != NULL)return INFEASIBLE;
	InitList(L);
	FILE *fp = fopen(FileName, "r");
	int c,i=1;
	while (fscanf(fp, "%d", &c) != EOF){
		ListInsert(L, i++, c);
	}
	fclose(fp);
	return OK;
}
status AddList(LISTS &Lists, char ListName[])
// 18.只需要在Lists中增加一个名称为ListName的空线性表，线性表数据又后台测试程序插入。
{

	strcpy(Lists.elem[Lists.length].name, ListName);
	Lists.elem[Lists.length].L = NULL;
	InitList(Lists.elem[Lists.length].L);
	Lists.length++;
	return OK;
}

status RemoveList(LISTS &Lists, char ListName[])
//19.Lists中删除一个名称为ListName的线性表
{
	for (int i = 0; i<Lists.length; i++){
		if (strcmp(Lists.elem[i].name, ListName) == 0){
			DestroyList(Lists.elem[i].L);
			for (int j = i + 1; j<Lists.length; j++){
				Lists.elem[j - 1] = Lists.elem[j];
			}
			Lists.length--;
			return OK;
		}
	}
	return ERROR;
}
int LocateList(LISTS Lists, char ListName[])
// 20.在Lists中查找一个名称为ListName的线性表，成功返回逻辑序号，否则返回0
{
	for (int i = 0; i<Lists.length; i++){
		if (strcmp(Lists.elem[i].name, ListName) == 0){

			return i + 1;
		}
	}
	return 0;
}


void main(void){
	LinkList L=NULL;
	LISTS Lists;
	Lists.length = 0;
	Lists.listsize = 10;
	char name[30];
	int op = 1, isLists = 0;
	int i, e, now, pre, next, k;
	while (op){
		system("cls");	printf("\n\n");
		printf("      Menu for Linear Table On Sequence Structure \n");
		printf("-------------------------------------------------\n");
		printf("    	  1. InitList       2. DestroyList\n");
		printf("    	  3. ClearList      4. ListEmpty\n");
		printf("    	  5. ListLength     6. GetElem \n");
		printf("    	  7. LocateElem     8. PriorElem\n");
		printf("    	  9. NextElem      10. ListInsert\n");
		printf("    	 11. ListDelete    12. ListTrabverse\n");
		printf("    	 13. reverseList   14. RemoveNthFromEnd\n");
		printf("    	 15. sortList      16. SaveList\n");
		printf("    	 17. LoadList      18. AddList\n");
		printf("    	 19. RemoveList    20. LocateList\n");
		printf("    	 21. GotoLists                   \n");
		printf("    	  0.  Exit\n");
		printf("-------------------------------------------------\n");
		printf("    请选择你的操作[0~12]:");
		scanf("%d", &op);
		switch (op){
		case 1:
			if (InitList(L) == OK) printf("线性表创建成功！\n");
			else printf("线性表创建失败！\n");
			getchar(); getchar();
			break;
		case 2:
			if (DestroyList(L) == OK)printf("线性表销毁成功！\n");
			else printf("线性表销毁失败！\n");
			getchar(); getchar();
			break;
		case 3:
			if (isLists){
				printf("请输入线性表名");
				scanf("%s", name);
				now = LocateList(Lists, name);
				if (ClearList(Lists.elem[now - 1].L) == OK)printf("线性表清空成功！\n");
				else printf("线性表清空失败！\n");
			}
			else{
				if (ClearList(L) == OK)printf("线性表清空成功！\n");
				else printf("线性表清空失败！\n");

			}

			getchar(); getchar();
			break;
		case 4:
			if (isLists){
				printf("请输入线性表名");
				scanf("%s", name);
				now = LocateList(Lists, name);
				now = ListEmpty(Lists.elem[now - 1].L);
			}
			else {
				now = ListEmpty(L);
			}

			if (now == INFEASIBLE)printf("线性表不存在");
			else if (now == TRUE)printf("线性表为空");
			else printf("线性表不为空");
			getchar(); getchar();
			break;
		case 5:
			if (isLists){
				printf("请输入线性表名");
				scanf("%s", name);
				now = LocateList(Lists, name);
				now = ListLength(Lists.elem[now - 1].L);
			}
			else {
				now = ListLength(L);
			}
			if (now == INFEASIBLE)printf("线性表不存在");
			else printf("线性表长度为%d", now);
			getchar(); getchar();
			break;
		case 6:
			if (isLists){
				printf("请输入线性表名");
				scanf("%s", name);
				now = LocateList(Lists, name);
				printf("请输入元素序号");
				scanf("%d", &i);
				now = GetElem(Lists.elem[now - 1].L, i, e);
			}
			else {
				printf("请输入元素序号");
				scanf("%d", &i);
				now = GetElem(L, i, e);
			}
			if (now == INFEASIBLE)printf("线性表不存在");
			else if (now == ERROR)printf("无该序号元素");
			printf("第%d号元素为%d", i, e);
			getchar(); getchar();
			break;
		case 7:
			if (isLists){
				printf("请输入线性表名");
				scanf("%s", name);
				now = LocateList(Lists, name);
				printf("请输入元素");
				scanf("%d", &e);

				now = LocateElem(Lists.elem[now - 1].L, e);
			}
			else {
				printf("请输入元素");
				scanf("%d", &e);
				now = LocateElem(L, e);
			}
			if (now == INFEASIBLE)printf("线性表不存在");
			else if (now == ERROR)printf("无该元素");
			else printf("元素序号为%d", now);
			getchar(); getchar();
			break;
		case 8:
			if (isLists){
				printf("请输入线性表名");
				scanf("%s", name);
				now = LocateList(Lists, name);
				printf("请输入元素");
				scanf("%d", &e);
				now = PriorElem(Lists.elem[now - 1].L, e, pre);
			}
			else {
				printf("请输入元素");
				scanf("%d", &e);
				now = PriorElem(L, e, pre);
			}
			if (now == INFEASIBLE)printf("线性表不存在");
			else  if (now == ERROR)printf("无该元素前驱");
			else printf("元素前驱为%d", pre);
			getchar(); getchar();
			break;
		case 9:
			if (isLists){
				printf("请输入线性表名");
				scanf("%s", name);
				now = LocateList(Lists, name);
				printf("请输入元素");
				scanf("%d", &e);
				now = NextElem(Lists.elem[now - 1].L, e, pre);
			}
			else {
				printf("请输入元素");
				scanf("%d", &e);
				now = NextElem(L, e, next);
			}
			if (now == INFEASIBLE)printf("线性表不存在");
			else  if (now == ERROR)printf("无该元素后继");
			else printf("元素后继为%d", next);
			getchar(); getchar();
			break;
		case 10:
			if (isLists){
				printf("请输入线性表名");
				scanf("%s", name);
				now = LocateList(Lists, name);
				printf("请输入序号i和元素e");
				scanf("%d%d", &i, &e);
				now = ListInsert(Lists.elem[now - 1].L, i, e);
			}
			else {
				printf("请输入序号i和元素e");
				scanf("%d%d", &i, &e);
				now = ListInsert(L, i, e);
			}

			if (now == INFEASIBLE)printf("线性表不存在");
			else  if (now == ERROR)printf("插入失败");
			else printf("插入成功");
			getchar(); getchar();
			break;
		case 11:
			if (isLists){
				printf("请输入线性表名");
				scanf("%s", name);
				now = LocateList(Lists, name);
				printf("请输入序号");
				scanf("%d", &i);
				now = ListDelete(Lists.elem[now - 1].L, i, e);
			}
			else {
				printf("请输入序号");
				scanf("%d", &i);
				now = ListDelete(L, i, e);
			}
			if (now == INFEASIBLE)printf("线性表不存在");
			else  if (now == ERROR)printf("删除失败");
			else printf("已删除第%d元素%d", i, e);
			getchar(); getchar();
			break;
		case 12:if (isLists){
			printf("请输入线性表名");
			scanf("%s", name);
			now = LocateList(Lists, name);
			if (!ListTraverse(Lists.elem[now - 1].L)) printf("线性表是空表！\n");
		}
				else {
					if (!ListTraverse(L)) printf("线性表不存在！\n");
				}
				getchar(); getchar();
				break;
		case 13:
			if (isLists){
			printf("请输入线性表名");
			scanf("%s", name);
			now = LocateList(Lists, name);
			now = reverseList(Lists.elem[now - 1].L);
		      }
		    else {
			    now = reverseList(L);
			  }
			if (now == INFEASIBLE) printf("线性表不存在！\n");
			else if (now == ERROR)printf("线性表是空表");
			else printf("翻转成功");
			getchar(); getchar();
			break;
		case 14:
			if (isLists){
				printf("请输入线性表名");
				scanf("%s", name);
				now = LocateList(Lists, name);
				printf("请输入n的值");
				scanf("%d", &k);
				now = RemoveNthFromEnd(Lists.elem[now - 1].L,k);
			}
			else {
				printf("请输入n的值");
				scanf("%d", &k);
				now = RemoveNthFromEnd(L, k);
			}
			
			if (now == INFEASIBLE) printf("线性表是空表！\n");
			else if (now == ERROR)printf("删除失败！");
			else printf("已删除倒数第%d个结点%d",k,now);
			getchar(); getchar();
			break;
		case 15:
			if (isLists){
				printf("请输入线性表名");
				scanf("%s", name);
				now = LocateList(Lists, name);
				now = sortList(Lists.elem[now - 1].L);
			}
			else {
				now = sortList(L);
			}
			if (now == INFEASIBLE) printf("线性表不存在！\n");
			else if (now == ERROR)printf("线性表是空表");
			else printf("排序成功");
			getchar(); getchar();
			break;
		case 16:
			if (isLists){
				printf("请输入线性表名");
				scanf("%s", name);
				now = LocateList(Lists, name);
				now = SaveList(Lists.elem[now - 1].L, "text");
			}
			else {
				now = SaveList(L, "text");
			}
			if (now == INFEASIBLE) printf("不能对不存在的线性表进行写文件操作！");
			else printf("写入完成");
			getchar(); getchar();
			break;
		case 17:
			if (isLists){
				printf("请输入线性表名");
				scanf("%s", name);
				now = LocateList(Lists, name);
				now = LoadList(Lists.elem[now - 1].L, "text");
			}
			else {
				now = LoadList(L, "text");
			}
			if (now == INFEASIBLE)printf("不能对已存在的线性表进行读文件操作！");
			else printf("读取完成");
			getchar(); getchar();
			break;
		case 18:
			printf("请输入要插入的线性表名");
			scanf("%s", name);
			AddList(Lists, name);
			printf("插入成功");
			getchar(); getchar();
			break;
		case 19:
			printf("请输入要删除的线性表名");
			scanf("%s", name);
			now = RemoveList(Lists, name);
			if (now == OK)printf("删除成功");
			else printf("删除失败");
			getchar(); getchar();
			break;
		case 20:
			printf("请输入要查找的线性表名");
			scanf("%s", name);
			now = LocateList(Lists, name);
			if (now == 0)printf("查找失败");
			else printf("线性表逻辑序号为%d", now);
			getchar(); getchar();
			break;
		case 21:
			if (isLists){
				isLists = 0;
				printf("退出多线性表模式");
			}
			else {
				isLists = 1;
				printf("进入多线性表模式");
			}
			getchar(); getchar();
			break;
		case 0:
			break;
		}//end of switch
	}//end of while
	printf("欢迎下次再使用本系统！\n");
}//end of main()


