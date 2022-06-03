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
typedef int KeyType;
typedef struct {
	KeyType  key;
	char others[20];
} TElemType; //二叉树结点类型定义

typedef struct BiTNode{  //二叉链表结点的定义
	TElemType  data;
	int depth;
	BiTNode* fa;
	int pathLength;
	struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;
typedef struct{  //线性表的管理表定义
	struct {
		char name[30];
		BiTree T;
	} elem[10];
	int length;
	int listsize;
}LISTS;
void visit(BiTree T){
	printf("%d %s  ", T->data.key, T->data.others);
	/*printf("depth:%d  ", T->depth);.
	if (T->fa)printf("fa: %d\n", T->fa->data.key);*/
	/*else printf("fa: NULL\n");*/
}
status CreateBiTree(BiTree &T, TElemType definition[], int depth, BiTree fa,bool root)
/*1. 根据带空枝的二叉树先根遍历序列definition构造一棵二叉树，将根节点指针赋值给T并返回OK，
如果有相同的关键字，返回ERROR。此题允许通过增加其它函数辅助实现本关任务*/
{
	static int i = 0;
	if (root)i = 0;
	if (definition[i].key != 0){
		for (int j = 0; j<i; j++){
			if (definition[j].key == definition[i].key){
				return ERROR;
			}
		}
		T = (BiTree)malloc(sizeof(BiTNode));
		T->data = definition[i++];
		T->fa = fa;
		T->depth = depth;
		if (CreateBiTree(T->lchild, definition,depth+1,T,0) == OK) {
			if (CreateBiTree(T->rchild, definition,depth+1,T,0) == OK)
				return OK;
			else return ERROR;
		}
		else {
			CreateBiTree(T->rchild, definition,depth+1,T,0);
			return ERROR;
		}
	}
	else {
		T = NULL;
		i++;
	}
	return OK;
}

status ClearBiTree(BiTree &T)
//2. 将二叉树设置成空，并删除所有结点，释放结点空间
{
	if (T){
		if (T->lchild)ClearBiTree(T->lchild);
		if (T->rchild)ClearBiTree(T->rchild);
		free(T);
	}
	T = NULL;
	return OK;
}
int max(int a, int b){
	return a>b ? a : b;
}
int BiTreeDepth(BiTree T)
//3. 求二叉树T的深度
{
	if (!T)return 0;
	return max(BiTreeDepth(T->lchild), BiTreeDepth(T->rchild)) + 1;
}
BiTNode* LocateNode(BiTree T, KeyType e)
//4. 查找结点
{
	if (!T)return NULL;
	if ((T->data).key == e)return T;
	BiTNode* p;
	if ((p = LocateNode(T->lchild, e)) == NULL){
		if ((p = LocateNode(T->rchild, e)) == NULL)return NULL;
		else return p;
	}
	else return p;
}

status Assign(BiTree &T, KeyType e, TElemType value)
//5. 实现结点赋值。此题允许通过增加其它函数辅助实现本关任务
{
	if (value.key != e)
		if (LocateNode(T, value.key))return ERROR;
	BiTNode* p = LocateNode(T, e);
	if (p){
		p->data = value;
		return OK;
	}
	return ERROR;
}
BiTNode* GetSibling(BiTree T, KeyType e)
//6. 实现获得兄弟结点
{
	if (!T)return NULL;
	if (T->lchild != NULL&&T->lchild->data.key == e)return T->rchild;
	if (T->rchild != NULL&&T->rchild->data.key == e)return T->lchild;
	BiTNode* p;
	if ((p = GetSibling(T->lchild, e)) == NULL){
		if ((p = GetSibling(T->rchild, e)) == NULL) return NULL;
		else return p;
	}
	else return p;

}
status PreOrderTraverseForInsert(BiTree T)
// 先序遍历二叉树T
{
	T->depth++;
	if (T->lchild != NULL)PreOrderTraverseForInsert(T->lchild);
	if (T->rchild != NULL)PreOrderTraverseForInsert(T->rchild);
	return OK;
}
status InsertNode(BiTree &T, KeyType e, int LR, TElemType c)
//7. 插入结点。此题允许通过增加其它函数辅助实现本关任务
{
	if (LocateNode(T, c.key) != NULL)return ERROR;
	BiTree p = (BiTree)malloc(sizeof(BiTNode));
	p->data = c;
	p->rchild = NULL;
	p->lchild = NULL;
	if (LR == -1){
		p->fa = NULL;
		p->rchild = T;
		p->depth = 1;
		PreOrderTraverseForInsert(T);
		T->fa = p;
		T = p;

		return OK;
	}
	BiTree p1;
	p1 = LocateNode(T, e);
	if (p1 == NULL)return ERROR;
	p->fa = p1;
	p->depth = p1->depth + 1;
	if (LR == 0){
		if (p1->lchild){
			p1->lchild->fa = p;
			PreOrderTraverseForInsert(p1->lchild);
		}
		p->rchild = p1->lchild;
		p1->lchild = p;
		return OK;
	}
	else {
		if (p1->rchild){
			p1->rchild->fa = p;
			PreOrderTraverseForInsert(p1->rchild);
		}
		p->rchild = p1->rchild;
		p1->rchild = p;
		return OK;
	}
}
BiTNode* GetFa(BiTree T, KeyType e)
//实现获得父结点
{
	if (!T)return NULL;
	if (T->lchild != NULL&&T->lchild->data.key == e)return T;
	if (T->rchild != NULL&&T->rchild->data.key == e)return T;
	BiTNode* p;
	if ((p = GetFa(T->lchild, e)) == NULL){
		if ((p = GetFa(T->rchild, e)) == NULL) return NULL;
		else return p;
	}
	else return p;
	/********** End **********/
}
status PreOrderTraverseForDelete(BiTree T,int i)
//先序遍历二叉树T
{
	T->depth+=i;
	if (T->lchild != NULL)PreOrderTraverseForDelete(T->lchild,i);
	if (T->rchild != NULL)PreOrderTraverseForDelete(T->rchild,i);
	return OK;
}
status DeleteNode(BiTree &T, KeyType e)
//8. 删除结点。此题允许通过增加其它函数辅助实现本关任务
{
	// 请在这里补充代码，完成本关任务
	/********** Begin *********/
	if (T->data.key == e){
		if (T->lchild == NULL&&T->rchild == NULL)T = NULL;
		else if (T->rchild == NULL){
			BiTNode* p = T->lchild;
			free(T);
			T = p;
			T->fa = NULL;
			PreOrderTraverseForDelete(T,-1);
		}
		else if (T->lchild == NULL){
			BiTNode* p = T->rchild;
			free(T);
			T = p;
			T->fa = NULL;
			PreOrderTraverseForDelete(T,-1);
		}
		else {
			BiTNode* p = T->lchild;
			BiTNode* p3 = T->lchild;
			PreOrderTraverseForDelete(T->lchild,-1);
			while (p3->rchild != NULL)p3 = p3->rchild;
			PreOrderTraverseForDelete(T->rchild, p3->depth-1);
			T->rchild->fa = p3;
			p3->rchild = T->rchild;
			free(T);
			T = p;
		}
		return OK;
	}
	BiTNode* p = GetFa(T, e);
	if (p == NULL)return ERROR;
	if (p->lchild&&p->lchild->data.key == e){
		BiTNode* p2 = p->lchild;
		if (p2->lchild == NULL&&p2->rchild == NULL){
			free(p2);
			p->lchild = NULL;
		}
		else if (p2->lchild == NULL){
			p->lchild = p2->rchild;
			p2->rchild->fa = p;
			PreOrderTraverseForDelete(p2->rchild, -1);
			free(p2);
		}
		else if (p2->rchild == NULL){
			p2->lchild->fa = p;
			PreOrderTraverseForDelete(p2->lchild, -1);
			p->lchild = p2->lchild;
			free(p2);
		}
		else {
			p->lchild = p2->lchild;
			p2->lchild->fa = p;
			PreOrderTraverseForDelete(p2->lchild, -1);
			BiTNode* p3 = p2->lchild;
			while (p3->rchild != NULL)p3 = p3->rchild;
			p2->rchild->fa = p3;
			PreOrderTraverseForDelete(p2->rchild, p3->depth-p2->depth);
			p3->rchild = p2->rchild;
			free(p2);
		}
	}
	else{
		BiTNode* p2 = p->rchild;
		if (p2->lchild == NULL&&p2->rchild == NULL){
			free(p2);
			p->rchild = NULL;
		}
		else if (p2->lchild == NULL){
			p2->rchild->fa = p;
			PreOrderTraverseForDelete(p2->rchild, -1);
			p->rchild = p2->rchild;
			free(p2);
		}
		else if (p2->rchild == NULL){
			p2->lchild->fa = p;
			PreOrderTraverseForDelete(p2->lchild, -1);
			p->rchild = p2->lchild;
			free(p2);
		}
		else {
			p->rchild = p2->lchild;
			p2->lchild->fa = p;
			PreOrderTraverseForDelete(p2->lchild, -1);
			BiTNode* p3 = p2->lchild;
			while (p3->rchild != NULL)p3 = p3->rchild;
			p3->rchild = p2->rchild;
			p2->rchild->fa = p3;
			PreOrderTraverseForDelete(p2->rchild, p3->depth-p2->depth);
			free(p2);
		}

	}
	return OK;
}
status PreOrderTraverse(BiTree T, void(*visit)(BiTree))
//9. 先序遍历二叉树T
{
	visit(T);
	if (T->lchild != NULL)PreOrderTraverse(T->lchild, visit);
	if (T->rchild != NULL)PreOrderTraverse(T->rchild, visit);
	return OK;
}
status InOrderTraverse(BiTree T, void(*visit)(BiTree))
//10. 中序遍历二叉树T
{
	BiTree stack[100];
	int i = 0;
	if (T == NULL)return ERROR;
	while (T != NULL || i>0){
		if (T != NULL){
			stack[i++] = T;
			T = T->lchild;
		}
		else {
			BiTree p = stack[--i];
			visit(p);
			T = p->rchild;
		}
	}
	return OK;
}
status PostOrderTraverse(BiTree T, void(*visit)(BiTree))
//11. 后序遍历二叉树T
{
	if (T->lchild != NULL)PostOrderTraverse(T->lchild, visit);
	if (T->rchild != NULL)PostOrderTraverse(T->rchild, visit);
	visit(T);
	return OK;
}
status LevelOrderTraverse(BiTree T, void(*visit)(BiTree))
//12. 按层遍历二叉树T
{
	BiTree queue[10];
	int i = 0, j = 0;
	visit(T);
	if (T->lchild != NULL){
		queue[j++] = T->lchild;
	}
	if (T->rchild != NULL){
		queue[j++] = T->rchild;
	}
	while (i<j){
		BiTree p = queue[i++];
		visit(p);
		if (p->lchild != NULL){
			queue[j++] = p->lchild;
		}
		if (p->rchild != NULL){
			queue[j++] = p->rchild;
		}
	}
	return OK;
}
status PreOrderTraverseForMax(BiTree &T, int &ans)

{
	if(T->fa!=NULL)T->pathLength = T->fa->pathLength + T->data.key;
	if (T->lchild == NULL&&T->rchild == NULL)ans = ans>T->pathLength ? ans : T->pathLength;
	if (T->lchild != NULL)PreOrderTraverseForMax(T->lchild, ans);
	if (T->rchild != NULL)PreOrderTraverseForMax(T->rchild, ans);
	return OK;
}
int MaxPathSum(BiTree &T){
//15.最大路径和：函数名称是MaxPathSum(T)，初始条件是二叉树T存在；操作结果是返回根节点到叶子结点的最大路径和；
    int ans = 0;
	T->pathLength = T->data.key;
	PreOrderTraverseForMax(T, ans);
	return ans;
}
BiTree LowestCommonAncestor(BiTree T, KeyType e1, KeyType e2){
//16.最近公共祖先：函数名称是LowestCommonAncestor(T, e1, e2)；初始条件是二叉树T存在；操作结果是该二叉树中e1节点和e2节点的最近公共祖先；
	BiTree t1 = LocateNode(T, e1);
	BiTree t2 = LocateNode(T, e2);
	while (t1->data.key != t2->data.key){
		if (t1->depth > t2->depth)t1 = t1->fa;
		else if (t2->depth > t1->depth)t2 = t2->fa;
		else {
			t1 = t1->fa;
			t2 = t2->fa;
		}
	}
	return t1;
}
status PreOrderTraverseForInvertTree(BiTree &T)

{
	BiTree tmp = T->rchild;
	T->rchild = T->lchild;
	T->lchild = tmp;
	if (T->lchild != NULL)PreOrderTraverseForInvertTree(T->lchild);
	if (T->rchild != NULL)PreOrderTraverseForInvertTree(T->rchild);
	return OK;
}
void InvertTree(BiTree &T){
//17.翻转二叉树：函数名称是InvertTree(T)，初始条件是线性表L已存在；操作结果是将T翻转，使其所有节点的左右节点互换；
	PreOrderTraverseForInvertTree(T);
}
status PreOrderTraverseForSave(BiTree T, FILE *fp)
//先序遍历二叉树T
{
	if (T){
		fprintf(fp, "%d %s ", T->data.key,T->data.others);
		PreOrderTraverseForSave(T->lchild, fp);
		PreOrderTraverseForSave(T->rchild, fp);
	}
	else fprintf(fp, "%d %s ", -1,"z");
	return OK;
}
status SaveList(BiTree T, char FileName[])
// 如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
{
	if (T == NULL)return INFEASIBLE;
	FILE *fp = fopen(FileName, "w");
	PreOrderTraverseForSave(T, fp);
	fclose(fp);
	return OK;
}
status CreateBiTreeForLoad(BiTree &T, FILE *fp, int depth, BiTree fa)
/*1. 根据带空枝的二叉树先根遍历序列definition构造一棵二叉树，将根节点指针赋值给T并返回OK，
如果有相同的关键字，返回ERROR。此题允许通过增加其它函数辅助实现本关任务*/
{   
	    int c;
	    char a[10];
	    if (fscanf(fp, "%d", &c) != EOF); else return OK;
	    fscanf(fp, "%s", a);
		if (c == -1){
			T = NULL;
			return OK;
		}
		T = (BiTree)malloc(sizeof(BiTNode));
		T->data.key = c;
		strcpy(T->data.others, a);
		T->fa = fa;
		T->depth = depth;
		CreateBiTreeForLoad(T->lchild, fp, depth + 1, T);
		CreateBiTreeForLoad(T->rchild, fp, depth + 1, T);
	return OK;
}
status  LoadList(BiTree &T, char FileName[])
// 如果线性表L不存在，将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。
{
	if (T != NULL)return INFEASIBLE;
	FILE *fp = fopen(FileName, "r");
	CreateBiTreeForLoad(T, fp, 1, NULL);
	fclose(fp);
	return OK;
}
status AddList(LISTS &Lists, char ListName[])
// 18.只需要在Lists中增加一个名称为ListName的空线性表，线性表数据又后台测试程序插入。
{

	strcpy(Lists.elem[Lists.length].name, ListName);
	Lists.elem[Lists.length].T = NULL;
	Lists.length++;
	return OK;
}

status RemoveList(LISTS &Lists, char ListName[])
//19.Lists中删除一个名称为ListName的线性表
{
	for (int i = 0; i<Lists.length; i++){
		if (strcmp(Lists.elem[i].name, ListName) == 0){
			ClearBiTree(Lists.elem[i].T);
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
	TElemType definition[100],newe;
	BiTree T=NULL,nowT;
	LISTS Lists;
	Lists.length = 0;
	Lists.listsize = 10;
	char name[30];
	int op = 1, isLists = 0;
	int i, e, now, pre, next, k, ans, key, newKey,LR;
	while (op){
		system("cls");	printf("\n\n");
		printf("      Menu for Linear Table On Sequence Structure \n");
		printf("-------------------------------------------------\n");
		printf("    	  1. CreateBiTree          2. ClearBiTree\n");
		printf("    	  3. BiTreeEmpty           4. BiTreeDepth\n");
		printf("    	  5. LocateNode            6. Assign \n");
		printf("    	  7. GetSibling            8. InsertNode\n");
		printf("    	  9. DeleteNode           10. PreOrderTraverse\n");
		printf("    	 11. InOrderTraverse      12. PostOrderTraverse\n");
		printf("    	 13. LevelOrderTraverse   14. MaxPathSum\n");
		printf("    	 15. LowestCommonAncestor 16. InvertTree\n");
		printf("    	 17. SaveList             18. LoadList\n");
		printf("    	 19. AddList              20. RemoveList\n");
		printf("    	 21. LocateList           22.  GotoLists           \n");
		printf("    	  0.  Exit\n");
		printf("-------------------------------------------------\n");
		printf("    请选择你的操作[0~12]:");
		scanf("%d", &op);
		switch (op){
		case 1:
			i = 0;
			printf("请输入树结点");
			do {
				scanf("%d %s", &definition[i].key, definition[i].others);
			} while (definition[i++].key != -1);
			if (isLists){
				printf("请输入二叉树名");
				scanf("%s", name);
				now = LocateList(Lists, name);
				ans = CreateBiTree(Lists.elem[now-1].T, definition, 1,NULL,1);
				if (ans == ERROR)Lists.elem[now - 1].T = NULL;
			}
			else {
				ans = CreateBiTree(T, definition,1,NULL,1);
				if (ans == ERROR)T = NULL;
			}
			if (ans == OK) printf("二叉树创建成功！\n");
			else {
				printf("关键字不唯一！\n");
			}
			getchar(); getchar();
			break;
		case 2:
			if (isLists){
				printf("请输入二叉树名");
				scanf("%s", name);
				now = LocateList(Lists, name);
				ClearBiTree(Lists.elem[now - 1].T);
				if (!Lists.elem[now - 1].T)printf("清空二叉树成功！\n");
				else printf("ERROR！\n");
			}
			else{
				ClearBiTree(T);
				if (!T)printf("清空二叉树成功！\n");
				else printf("ERROR！\n");
			}
			getchar(); getchar();
			break;
		case 3:
			if (isLists){
				printf("请输入二叉树名");
				scanf("%s", name);
				now = LocateList(Lists, name);
				if (!Lists.elem[now - 1].T)printf("二叉树为空！\n");
				else printf("二叉树不为空！\n");
			}
			else{
				if (!T)printf("二叉树为空！");
				else printf("二叉树不为空！\n");
			}
			getchar(); getchar();
			break;
		case 4:
			if (isLists){
				printf("请输入二叉树名");
				scanf("%s", name);
				now = LocateList(Lists, name);
				now = BiTreeDepth(Lists.elem[now - 1].T);
			}
			else {
				now = BiTreeDepth(T);
			}

			if (now == 0)printf("二叉树为空");
			
			else printf("二叉树深度为%d",now);
			getchar(); getchar();
			break;
		case 5:
			if (isLists){
				printf("请输入二叉树名");
				scanf("%s", name);
				printf("请输入结点的key");
				scanf("%d", &key);
				now = LocateList(Lists, name);
				nowT = LocateNode(Lists.elem[now - 1].T, key);
			}
			else {
				printf("请输入结点的key");
				scanf("%d", &key);
				nowT = LocateNode(T, key);
			}
			if (nowT == NULL)printf("未找到该结点");
			else printf("key为%d结点的others为%s",key,nowT->data.others);
			getchar(); getchar();
			break;
		case 6:
			if (isLists){
				printf("请输入二叉树名");
				scanf("%s", name);
				now = LocateList(Lists, name);
				printf("请输入结点的key");
				scanf("%d", &key);
				printf("请输入结点的新key和others");
				scanf("%d %s", &newe.key, newe.others);
				now = Assign(Lists.elem[now - 1].T, key, newe);
			}
			else {
				printf("请输入结点的key");
				scanf("%d", &key);
				printf("请输入结点的新key和others");
				scanf("%d %s", &newe.key, newe.others);
				now = Assign(T, key, newe);
			}
			if (now == ERROR)printf("赋值失败");
			else printf("赋值成功！");
			getchar(); getchar();
			break;
		case 7:
			if (isLists){
				printf("请输入二叉树名");
				scanf("%s", name);
				now = LocateList(Lists, name);
				printf("请输入结点的key");
				scanf("%d", &key);
				nowT=GetSibling(Lists.elem[now - 1].T, key);
			}
			else {
				printf("请输入结点的key");
				scanf("%d", &key);
				nowT = GetSibling(T, key);
			}
			if (nowT == NULL)printf("未找到兄弟结点");
			else printf("兄弟结点key为%d，others为%s", nowT->data.key, nowT->data.others);
			getchar(); getchar();
			break;
		case 8:
			if (isLists){
				printf("请输入二叉树名");
				scanf("%s", name);
				now = LocateList(Lists, name);
				printf("请输入插入结点父节点的key");
				scanf("%d", &e);
				printf("请输入LR");
				scanf("%d", &LR);
				printf("请输入插入结点的key和others");
				scanf("%d %s", &newe.key, newe.others);
				now = InsertNode(Lists.elem[now - 1].T, e,LR, newe);
			}
			else {
				printf("请输入插入结点父节点的key");
				scanf("%d", &e);
				printf("请输入LR");
				scanf("%d", &LR);
				printf("请输入插入结点的key和others");
				scanf("%d %s", &newe.key, newe.others);
				now = InsertNode(T, e, LR, newe);
			}
			if (now == ERROR)printf("插入失败");
			else printf("插入成功！");
			getchar(); getchar();
			break;
		case 9:
			if (isLists){
				printf("请输入二叉树名");
				scanf("%s", name);
				now = LocateList(Lists, name);
				printf("请输入结点的key");
				scanf("%d", &e);
				now = DeleteNode(Lists.elem[now - 1].T, e);
			}
			else {
				printf("请输入结点的key");
				scanf("%d", &e);
				now = DeleteNode(T, e);
			}
			if (now == ERROR)printf("删除失败");
			else printf("删除成功");
			getchar(); getchar();
			break;
		case 10:
			if (isLists){
				printf("请输入二叉树名");
				scanf("%s", name);
				now = LocateList(Lists, name);
				if (now == 0)printf("无该二叉树");
				else if (Lists.elem[now - 1].T == NULL)printf("二叉树为空！");
				else now = PreOrderTraverse(Lists.elem[now - 1].T, visit);
			}
			else {
				if (T == NULL)printf("二叉树为空！");
				else now = PreOrderTraverse(T, visit);
			}
			getchar(); getchar();
			break;
		case 11:
			if (isLists){
				printf("请输入二叉树名");
				scanf("%s", name);
				now = LocateList(Lists, name); 
				if (now == 0)printf("无该二叉树");
				else if (Lists.elem[now - 1].T == NULL)printf("二叉树为空！");
				else
				now = InOrderTraverse(Lists.elem[now - 1].T, visit);
			}
			else {
				if (T == NULL)printf("二叉树为空！");
				else now = InOrderTraverse(T, visit);
			}
			getchar(); getchar();
			break;
		case 12:if (isLists){
			printf("请输入二叉树名");
			scanf("%s", name);
			now = LocateList(Lists, name);
			if (now == 0)printf("无该二叉树");
			else if (Lists.elem[now - 1].T == NULL)printf("二叉树为空！");
			else
			now = PostOrderTraverse(Lists.elem[now - 1].T, visit);
		     } else {
			if (T == NULL)printf("二叉树为空！");
			else now = PostOrderTraverse(T, visit);
				    }
				getchar(); getchar();
				break;
		case 13:
			if (isLists){
				printf("请输入二叉树名");
				scanf("%s", name);
				now = LocateList(Lists, name);
				if (now == 0)printf("无该二叉树");
				else if (Lists.elem[now - 1].T == NULL)printf("二叉树为空！");
				else
				now = LevelOrderTraverse(Lists.elem[now - 1].T, visit);
			}
			else {
				if (T == NULL)printf("二叉树为空！");
				else
				now = LevelOrderTraverse(T, visit);
			}
			getchar(); getchar();
			break;
		case 14:
			if (isLists){
				printf("请输入二叉树名");
				scanf("%s", name);
				now = LocateList(Lists, name);
				now = MaxPathSum(Lists.elem[now - 1].T);
			}
			else {
				now = MaxPathSum(T);
			}
			printf("最大路径和为%d", now);
			getchar(); getchar();
			break;
		case 15:
			if (isLists){
				printf("请输入二叉树名");
				scanf("%s", name);
				now = LocateList(Lists, name);
				printf("请输入两个结点的key");
				scanf("%d %d", &key, &e);
				nowT = LowestCommonAncestor(Lists.elem[now - 1].T, key, e);
			}
			else {
				printf("请输入两个结点的key");
				scanf("%d %d", &key, &e);
				nowT = LowestCommonAncestor(T, key, e);
			}
			printf("共同祖先的key为%d,others为%s",nowT->data.key,nowT->data.others);
			getchar(); getchar();
			break;
		case 16:if (isLists){
			printf("请输入二叉树名");
			scanf("%s", name);
			now = LocateList(Lists, name);
			InvertTree(Lists.elem[now - 1].T);
		}
	    else {
			InvertTree(T);
			}
		printf("翻转成功！");
			getchar(); getchar();
			break;
		case 17:
			if (isLists){
				printf("请输入二叉树名");
				scanf("%s", name);
				now = LocateList(Lists, name);
				now = SaveList(Lists.elem[now - 1].T, "text");
			}
			else {
				now = SaveList(T, "text");
			}
			if (now == INFEASIBLE) printf("不能对不存在的二叉树进行写文件操作！");
			else printf("写入完成");
			getchar(); getchar();
			break;
		case 18:
			if (isLists){
				printf("请输入线性表名");
				scanf("%s", name);
				now = LocateList(Lists, name);
				now = LoadList(Lists.elem[now - 1].T, "text");
			}
			else {
				now = LoadList(T, "text");
			}
			if (now == INFEASIBLE)printf("不能对已存在的二叉树进行读文件操作！");
			else printf("读取完成");
			getchar(); getchar();
			break;
		case 19:
			printf("请输入要插入的二叉树名");
			scanf("%s", name);
			AddList(Lists, name);
			printf("插入成功");
			getchar(); getchar();
			break;
		case 20:
			printf("请输入要删除的二叉树名");
			scanf("%s", name);
			now = RemoveList(Lists, name);
			if (now == OK)printf("删除成功");
			else printf("删除失败");
			getchar(); getchar();
			break;
		case 21:
			printf("请输入要查找的二叉树名");
			scanf("%s", name);
			now = LocateList(Lists, name);
			if (now == 0)printf("查找失败");
			else printf("二叉树逻辑序号为%d", now);
			getchar(); getchar();
			break;
		case 22:
			if (isLists){
				isLists = 0;
				printf("退出多二叉树模式");
			}
			else {
				isLists = 1;
				printf("进入多二叉树模式");
			}
			getchar(); getchar();
			break;
		case 0:
			break;
		}//end of switch
	}//end of while
	printf("欢迎下次再使用本系统！\n");
}//end of main()






