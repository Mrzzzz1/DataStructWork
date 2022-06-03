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
typedef int ElemType; //����Ԫ�����Ͷ���

#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef int ElemType;
typedef struct LNode{  //��������ʽ�ṹ�����Ķ���
	ElemType data;
	struct LNode *next;
}LNode, *LinkList;
typedef struct{  //���Ա�Ĺ������
	struct {
		char name[30];
		LinkList L;
	} elem[10];
	int length;
	int listsize;
}LISTS;
status InitList(LinkList &L)
// 1.���Ա�L�����ڣ�����һ���յ����Ա�����OK�����򷵻�INFEASIBLE��
{
	if (L != NULL)return INFEASIBLE;
	L = (LNode*)malloc(sizeof(LNode));
	L->next = NULL;
	L->data = 0;
	return OK;
}
status DestroyList(LinkList &L)
// 2.������Ա�L���ڣ��������Ա�L���ͷ�����Ԫ�صĿռ䣬����OK�����򷵻�INFEASIBLE��
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
// 3.������Ա�L���ڣ�ɾ�����Ա�L�е�����Ԫ�أ�����OK�����򷵻�INFEASIBLE��
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
// 4.������Ա�L���ڣ��ж����Ա�L�Ƿ�Ϊ�գ��վͷ���TRUE�����򷵻�FALSE��������Ա�L�����ڣ�����INFEASIBLE��
{
	if (L == NULL)return INFEASIBLE;
	if (L->next == NULL)return TRUE;
	return FALSE;
}
int ListLength(LinkList L)
// 5.������Ա�L���ڣ��������Ա�L�ĳ��ȣ����򷵻�INFEASIBLE��
{
	if (L == NULL)return INFEASIBLE;
	int n = 0;
	while (L = L->next)n++;
	return n;
}
status GetElem(LinkList L, int i, ElemType &e)
// 6.������Ա�L���ڣ���ȡ���Ա�L�ĵ�i��Ԫ�أ�������e�У�����OK�����i���Ϸ�������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
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
// 7.������Ա�L���ڣ�����Ԫ��e�����Ա�L�е�λ����ţ����e�����ڣ�����ERROR�������Ա�L������ʱ������INFEASIBLE��
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
// 8.������Ա�L���ڣ���ȡ���Ա�L��Ԫ��e��ǰ����������pre�У�����OK�����û��ǰ��������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
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
// 9.������Ա�L���ڣ���ȡ���Ա�LԪ��e�ĺ�̣�������next�У�����OK�����û�к�̣�����ERROR��������Ա�L�����ڣ�����INFEASIBLE��
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
// 10.������Ա�L���ڣ���Ԫ��e���뵽���Ա�L�ĵ�i��Ԫ��֮ǰ������OK��������λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
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
// 11.������Ա�L���ڣ�ɾ�����Ա�L�ĵ�i��Ԫ�أ���������e�У�����OK����ɾ��λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
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
// 12.������Ա�L���ڣ�������ʾ���Ա��е�Ԫ�أ�ÿ��Ԫ�ؼ��һ�񣬷���OK��������Ա�L�����ڣ�����INFEASIBLE��
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
//13.����ת������OK�����������ڷ���INFEASIBLE��������Ϊ�շ���ERROR��
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
//14.ɾ������	n���ڵ㣬���ɹ����ؽ��ֵ�������Ա�Ϊ�շ���INFEASIBLE��ɾ��ʧ�ܷ���ERROR��
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
//15���Ա����򣬳ɹ�����OK�������ڷ���INFEASIBLE���ձ���ERROR;
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
// ������Ա�L���ڣ������Ա�L�ĵ�Ԫ��д��FileName�ļ��У�����OK�����򷵻�INFEASIBLE��
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
// ������Ա�L�����ڣ���FileName�ļ��е����ݶ��뵽���Ա�L�У�����OK�����򷵻�INFEASIBLE��
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
// 18.ֻ��Ҫ��Lists������һ������ΪListName�Ŀ����Ա����Ա������ֺ�̨���Գ�����롣
{

	strcpy(Lists.elem[Lists.length].name, ListName);
	Lists.elem[Lists.length].L = NULL;
	InitList(Lists.elem[Lists.length].L);
	Lists.length++;
	return OK;
}

status RemoveList(LISTS &Lists, char ListName[])
//19.Lists��ɾ��һ������ΪListName�����Ա�
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
// 20.��Lists�в���һ������ΪListName�����Ա��ɹ������߼���ţ����򷵻�0
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
		printf("    ��ѡ����Ĳ���[0~12]:");
		scanf("%d", &op);
		switch (op){
		case 1:
			if (InitList(L) == OK) printf("���Ա����ɹ���\n");
			else printf("���Ա���ʧ�ܣ�\n");
			getchar(); getchar();
			break;
		case 2:
			if (DestroyList(L) == OK)printf("���Ա����ٳɹ���\n");
			else printf("���Ա�����ʧ�ܣ�\n");
			getchar(); getchar();
			break;
		case 3:
			if (isLists){
				printf("���������Ա���");
				scanf("%s", name);
				now = LocateList(Lists, name);
				if (ClearList(Lists.elem[now - 1].L) == OK)printf("���Ա���ճɹ���\n");
				else printf("���Ա����ʧ�ܣ�\n");
			}
			else{
				if (ClearList(L) == OK)printf("���Ա���ճɹ���\n");
				else printf("���Ա����ʧ�ܣ�\n");

			}

			getchar(); getchar();
			break;
		case 4:
			if (isLists){
				printf("���������Ա���");
				scanf("%s", name);
				now = LocateList(Lists, name);
				now = ListEmpty(Lists.elem[now - 1].L);
			}
			else {
				now = ListEmpty(L);
			}

			if (now == INFEASIBLE)printf("���Ա�����");
			else if (now == TRUE)printf("���Ա�Ϊ��");
			else printf("���Ա�Ϊ��");
			getchar(); getchar();
			break;
		case 5:
			if (isLists){
				printf("���������Ա���");
				scanf("%s", name);
				now = LocateList(Lists, name);
				now = ListLength(Lists.elem[now - 1].L);
			}
			else {
				now = ListLength(L);
			}
			if (now == INFEASIBLE)printf("���Ա�����");
			else printf("���Ա���Ϊ%d", now);
			getchar(); getchar();
			break;
		case 6:
			if (isLists){
				printf("���������Ա���");
				scanf("%s", name);
				now = LocateList(Lists, name);
				printf("������Ԫ�����");
				scanf("%d", &i);
				now = GetElem(Lists.elem[now - 1].L, i, e);
			}
			else {
				printf("������Ԫ�����");
				scanf("%d", &i);
				now = GetElem(L, i, e);
			}
			if (now == INFEASIBLE)printf("���Ա�����");
			else if (now == ERROR)printf("�޸����Ԫ��");
			printf("��%d��Ԫ��Ϊ%d", i, e);
			getchar(); getchar();
			break;
		case 7:
			if (isLists){
				printf("���������Ա���");
				scanf("%s", name);
				now = LocateList(Lists, name);
				printf("������Ԫ��");
				scanf("%d", &e);

				now = LocateElem(Lists.elem[now - 1].L, e);
			}
			else {
				printf("������Ԫ��");
				scanf("%d", &e);
				now = LocateElem(L, e);
			}
			if (now == INFEASIBLE)printf("���Ա�����");
			else if (now == ERROR)printf("�޸�Ԫ��");
			else printf("Ԫ�����Ϊ%d", now);
			getchar(); getchar();
			break;
		case 8:
			if (isLists){
				printf("���������Ա���");
				scanf("%s", name);
				now = LocateList(Lists, name);
				printf("������Ԫ��");
				scanf("%d", &e);
				now = PriorElem(Lists.elem[now - 1].L, e, pre);
			}
			else {
				printf("������Ԫ��");
				scanf("%d", &e);
				now = PriorElem(L, e, pre);
			}
			if (now == INFEASIBLE)printf("���Ա�����");
			else  if (now == ERROR)printf("�޸�Ԫ��ǰ��");
			else printf("Ԫ��ǰ��Ϊ%d", pre);
			getchar(); getchar();
			break;
		case 9:
			if (isLists){
				printf("���������Ա���");
				scanf("%s", name);
				now = LocateList(Lists, name);
				printf("������Ԫ��");
				scanf("%d", &e);
				now = NextElem(Lists.elem[now - 1].L, e, pre);
			}
			else {
				printf("������Ԫ��");
				scanf("%d", &e);
				now = NextElem(L, e, next);
			}
			if (now == INFEASIBLE)printf("���Ա�����");
			else  if (now == ERROR)printf("�޸�Ԫ�غ��");
			else printf("Ԫ�غ��Ϊ%d", next);
			getchar(); getchar();
			break;
		case 10:
			if (isLists){
				printf("���������Ա���");
				scanf("%s", name);
				now = LocateList(Lists, name);
				printf("���������i��Ԫ��e");
				scanf("%d%d", &i, &e);
				now = ListInsert(Lists.elem[now - 1].L, i, e);
			}
			else {
				printf("���������i��Ԫ��e");
				scanf("%d%d", &i, &e);
				now = ListInsert(L, i, e);
			}

			if (now == INFEASIBLE)printf("���Ա�����");
			else  if (now == ERROR)printf("����ʧ��");
			else printf("����ɹ�");
			getchar(); getchar();
			break;
		case 11:
			if (isLists){
				printf("���������Ա���");
				scanf("%s", name);
				now = LocateList(Lists, name);
				printf("���������");
				scanf("%d", &i);
				now = ListDelete(Lists.elem[now - 1].L, i, e);
			}
			else {
				printf("���������");
				scanf("%d", &i);
				now = ListDelete(L, i, e);
			}
			if (now == INFEASIBLE)printf("���Ա�����");
			else  if (now == ERROR)printf("ɾ��ʧ��");
			else printf("��ɾ����%dԪ��%d", i, e);
			getchar(); getchar();
			break;
		case 12:if (isLists){
			printf("���������Ա���");
			scanf("%s", name);
			now = LocateList(Lists, name);
			if (!ListTraverse(Lists.elem[now - 1].L)) printf("���Ա��ǿձ�\n");
		}
				else {
					if (!ListTraverse(L)) printf("���Ա����ڣ�\n");
				}
				getchar(); getchar();
				break;
		case 13:
			if (isLists){
			printf("���������Ա���");
			scanf("%s", name);
			now = LocateList(Lists, name);
			now = reverseList(Lists.elem[now - 1].L);
		      }
		    else {
			    now = reverseList(L);
			  }
			if (now == INFEASIBLE) printf("���Ա����ڣ�\n");
			else if (now == ERROR)printf("���Ա��ǿձ�");
			else printf("��ת�ɹ�");
			getchar(); getchar();
			break;
		case 14:
			if (isLists){
				printf("���������Ա���");
				scanf("%s", name);
				now = LocateList(Lists, name);
				printf("������n��ֵ");
				scanf("%d", &k);
				now = RemoveNthFromEnd(Lists.elem[now - 1].L,k);
			}
			else {
				printf("������n��ֵ");
				scanf("%d", &k);
				now = RemoveNthFromEnd(L, k);
			}
			
			if (now == INFEASIBLE) printf("���Ա��ǿձ�\n");
			else if (now == ERROR)printf("ɾ��ʧ�ܣ�");
			else printf("��ɾ��������%d�����%d",k,now);
			getchar(); getchar();
			break;
		case 15:
			if (isLists){
				printf("���������Ա���");
				scanf("%s", name);
				now = LocateList(Lists, name);
				now = sortList(Lists.elem[now - 1].L);
			}
			else {
				now = sortList(L);
			}
			if (now == INFEASIBLE) printf("���Ա����ڣ�\n");
			else if (now == ERROR)printf("���Ա��ǿձ�");
			else printf("����ɹ�");
			getchar(); getchar();
			break;
		case 16:
			if (isLists){
				printf("���������Ա���");
				scanf("%s", name);
				now = LocateList(Lists, name);
				now = SaveList(Lists.elem[now - 1].L, "text");
			}
			else {
				now = SaveList(L, "text");
			}
			if (now == INFEASIBLE) printf("���ܶԲ����ڵ����Ա����д�ļ�������");
			else printf("д�����");
			getchar(); getchar();
			break;
		case 17:
			if (isLists){
				printf("���������Ա���");
				scanf("%s", name);
				now = LocateList(Lists, name);
				now = LoadList(Lists.elem[now - 1].L, "text");
			}
			else {
				now = LoadList(L, "text");
			}
			if (now == INFEASIBLE)printf("���ܶ��Ѵ��ڵ����Ա���ж��ļ�������");
			else printf("��ȡ���");
			getchar(); getchar();
			break;
		case 18:
			printf("������Ҫ��������Ա���");
			scanf("%s", name);
			AddList(Lists, name);
			printf("����ɹ�");
			getchar(); getchar();
			break;
		case 19:
			printf("������Ҫɾ�������Ա���");
			scanf("%s", name);
			now = RemoveList(Lists, name);
			if (now == OK)printf("ɾ���ɹ�");
			else printf("ɾ��ʧ��");
			getchar(); getchar();
			break;
		case 20:
			printf("������Ҫ���ҵ����Ա���");
			scanf("%s", name);
			now = LocateList(Lists, name);
			if (now == 0)printf("����ʧ��");
			else printf("���Ա��߼����Ϊ%d", now);
			getchar(); getchar();
			break;
		case 21:
			if (isLists){
				isLists = 0;
				printf("�˳������Ա�ģʽ");
			}
			else {
				isLists = 1;
				printf("��������Ա�ģʽ");
			}
			getchar(); getchar();
			break;
		case 0:
			break;
		}//end of switch
	}//end of while
	printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
}//end of main()


