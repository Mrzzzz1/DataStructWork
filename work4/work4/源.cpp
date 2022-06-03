#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAX_VERTEX_NUM 20
typedef int status;
typedef int KeyType;
typedef enum { DG, DN, UDG, UDN } GraphKind;
typedef struct {
	KeyType  key;
	char others[20];
} VertexType; //顶点类型定义


typedef struct ArcNode {         //表结点类型定义
	int adjvex;              //顶点位置编号 
	struct ArcNode  *nextarc;	   //下一个表结点指针
} ArcNode;
typedef struct VNode{				//头结点及其数组类型定义
	VertexType data;       	//顶点信息
	ArcNode *firstarc;      	 //指向第一条弧
} VNode, AdjList[MAX_VERTEX_NUM];
typedef  struct {  //邻接表的类型定义
	AdjList vertices;     	 //头结点数组
	int vexnum, arcnum;   	  //顶点数、弧数
	GraphKind  kind;        //图的类型
} ALGraph;
typedef struct{  //线性表的管理表定义
	struct {
		char name[30];
		ALGraph G;
	} elem[10];
	int length;
	int listsize;
}LISTS;


status CreateCraph(ALGraph &G, VertexType V[], KeyType VR[][2])
/*1. 根据V和VR构造图T并返回OK，如果V和VR不正确，返回ERROR
如果有相同的关键字，返回ERROR。此题允许通过增加其它函数辅助实现本关任务*/
{
	//G.vexnum,arcnum;   	  //顶点数、弧数
	G.kind = UDG;
	int i = 0;
	while (V[i].key != -1){
		for (int j = 0; j<i; j++){
			if (V[j].key == V[i].key)return ERROR;
		}
		G.vertices[i].data = V[i];
		G.vertices[i].firstarc = NULL;
		i++;
	}
	G.vexnum = i;
	if (i == 0 || i>20)return ERROR;
	i = 0;
	while (VR[i][0] != -1){
		i++;
	}
	G.arcnum = i;
	for (i = i - 1; i >= 0; i--){
		int j, k;
		for (j = 0; j<G.vexnum; j++){
			if (VR[i][0] == V[j].key)break;
		}
		if (j >= G.vexnum)return ERROR;
		for (k = 0; k<G.vexnum; k++){
			if (VR[i][1] == V[k].key)break;
		}
		if (k >= G.vexnum)return ERROR;
		if (G.vertices[j].firstarc == NULL){
			G.vertices[j].firstarc = (ArcNode *)malloc(sizeof(ArcNode));
			G.vertices[j].firstarc->adjvex = k;
			G.vertices[j].firstarc->nextarc = NULL;
		}
		else
		{
			ArcNode *p = G.vertices[j].firstarc;
			while (p->nextarc != NULL)p = p->nextarc;
			p->nextarc = (ArcNode *)malloc(sizeof(ArcNode));
			p->nextarc->adjvex = k;
			p->nextarc->nextarc = NULL;
		}
		if (G.vertices[k].firstarc == NULL){
			G.vertices[k].firstarc = (ArcNode *)malloc(sizeof(ArcNode));
			G.vertices[k].firstarc->adjvex = j;
			G.vertices[k].firstarc->nextarc = NULL;
		}
		else
		{
			ArcNode *p = G.vertices[k].firstarc;
			while (p->nextarc != NULL)p = p->nextarc;
			p->nextarc = (ArcNode *)malloc(sizeof(ArcNode));
			p->nextarc->adjvex = j;
			p->nextarc->nextarc = NULL;
		}
	}

	return OK;
}
status DestroyGraph(ALGraph &G)
/*2. 销毁无向图G,删除G的全部顶点和边*/
{
	for (int i = 0; i<G.vexnum; i++){
		if (G.vertices[i].firstarc != NULL&&G.vertices[i].firstarc->nextarc != NULL){
			ArcNode *p1 = G.vertices[i].firstarc;
			ArcNode *p2 = G.vertices[i].firstarc->nextarc;
			G.vertices[i].firstarc = NULL;
			do{
				free(p1);
				p1 = p2;
				p2 = p2->nextarc;
			} while (p2 != NULL);
			free(p1);
		}
		else{
			if (G.vertices[i].firstarc != NULL){
				free(G.vertices[i].firstarc);
				G.vertices[i].firstarc = NULL;
			}
		}
	}
	G.vexnum = 0;
	G.arcnum = 0;
	return OK;
}
int LocateVex(ALGraph G, KeyType u)
//3. 根据u在图G中查找顶点，查找成功返回位序，否则返回-1；
{
	for (int i = 0; i<G.vexnum; i++){
		if (G.vertices[i].data.key == u)return i;
	}
	return -1;
}

status PutVex(ALGraph &G, KeyType u, VertexType value)
//4. 根据u在图G中查找顶点，查找成功将该顶点值修改成value，返回OK；
//如果查找失败或关键字不唯一，返回ERROR
{
	if (u != value.key){
		for (int i = 0; i<G.vexnum; i++){
			if (G.vertices[i].data.key == value.key)return ERROR;
		}
	}
	for (int i = 0; i<G.vexnum; i++){
		if (G.vertices[i].data.key == u){
			G.vertices[i].data = value;
			return OK;
		}
	}
	return ERROR;
}

int FirstAdjVex(ALGraph G, KeyType u)
//5. 根据u在图G中查找顶点，查找成功返回顶点u的第一邻接顶点位序，否则返回-1；
{
	for (int i = 0; i<G.vexnum; i++){
		if (G.vertices[i].data.key == u){
			if (G.vertices[i].firstarc != NULL){
				return G.vertices[i].firstarc->adjvex;
			}
		}
	}
	return -1;
}

int NextAdjVex(ALGraph G, KeyType v, KeyType w)
//6. 根据u在图G中查找顶点，查找成功返回顶点v的邻接顶点相对于w的下一邻接顶点的位序，查找失败返回-1；
{
	ArcNode *p;
	for (int i = 0; i<G.vexnum; i++){
		if (G.vertices[i].data.key == v){
			//printf("%d",i);
			if (G.vertices[i].firstarc != NULL){
				p = G.vertices[i].firstarc;
				while (p != NULL){
					if (G.vertices[p->adjvex].data.key == w)break;
					else p = p->nextarc;
				}
				//printf("%d ",p->adjvex);
				if (p != NULL){
					if (p->nextarc != NULL){
						//printf("%d ",p->nextarc->adjvex);
						return p->nextarc->adjvex;
					}
				}
			}
			// break;
		}
	}
	return -1;
}

status InsertVex(ALGraph &G, VertexType v)
//7. 在图G中插入顶点v，成功返回OK,否则返回ERROR
{
	if (G.vexnum == 20)return ERROR;
	for (int i = 0; i<G.vexnum; i++){
		if (G.vertices[i].data.key == v.key)
			return ERROR;
	}
	G.vertices[G.vexnum].firstarc = NULL;
	G.vertices[G.vexnum++].data = v;
	return OK;
}

status DeleteVex(ALGraph &G, KeyType v)
//8. 在图G中删除关键字v对应的顶点以及相关的弧，成功返回OK,否则返回ERROR
{
	int i = 0;
	if (G.vexnum <= 1)return ERROR;
	for (i = 0; i<G.vexnum; i++){
		if (G.vertices[i].data.key == v)break;
	}
	if (i == G.vexnum)return ERROR;
	int num = i;
	if (G.vertices[i].firstarc != NULL&&G.vertices[i].firstarc->nextarc != NULL){
		ArcNode *p1 = G.vertices[i].firstarc;
		ArcNode *p2 = G.vertices[i].firstarc->nextarc;
		G.vertices[i].firstarc = NULL;
		do{
			free(p1);
			G.arcnum--;
			p1 = p2;
			p2 = p2->nextarc;
		} while (p2 != NULL);
		free(p1);
		G.arcnum--;

	}
	else{
		if (G.vertices[i].firstarc != NULL){
			free(G.vertices[i].firstarc);
			G.arcnum--;
			G.vertices[i].firstarc = NULL;
		}
	}
	for (int j = i; j<G.vexnum; j++){
		G.vertices[j] = G.vertices[j + 1];
	}
	G.vexnum--;
	for (int i = 0; i<G.vexnum; i++){
		if (G.vertices[i].firstarc != NULL&&G.vertices[i].firstarc->nextarc != NULL){
			ArcNode *p1 = G.vertices[i].firstarc;
			ArcNode *p2 = G.vertices[i].firstarc->nextarc;
			if (p1->adjvex == num){
				free(p1);
				G.vertices[i].firstarc = p2;
				p1 = p2;
				p2 = p2->nextarc;
			}
			if (p1->adjvex>num){
				G.vertices[i].firstarc->adjvex--;
			}
			while (p2 != NULL){
				if (p2->adjvex == num){
					p1->nextarc = p2->nextarc;
					free(p2);
					p2 = p1->nextarc;
				}
				else if (p2->adjvex>num){
					p2->adjvex--;
					p1 = p2; p2 = p2->nextarc;
				}
				else{
					p1 = p2;
					p2 = p2->nextarc;
				}
			}
		}
		else{
			if (G.vertices[i].firstarc != NULL){
				if (G.vertices[i].firstarc->adjvex == num){
					free(G.vertices[i].firstarc);
					G.vertices[i].firstarc = NULL;
				}
				else if (G.vertices[i].firstarc->adjvex>num){
					G.vertices[i].firstarc->adjvex--;
				}

			}
		}
	}

	return OK;
}

status InsertArc(ALGraph &G, KeyType v, KeyType w)
//9. 在图G中增加弧<v,w>，成功返回OK,否则返回ERROR
{
	int ver1 = -1, ver2 = -1;
	for (int i = 0; i<G.vexnum; i++){
		if (G.vertices[i].data.key == v)ver1 = i;
		if (G.vertices[i].data.key == w)ver2 = i;
	}
	if (ver1<0 || ver2<0)return ERROR;
	ArcNode *p2 = G.vertices[ver1].firstarc;
	while (p2 != NULL){
		if (p2->adjvex == ver2)return ERROR;
		p2 = p2->nextarc;
	}
	ArcNode *p = (ArcNode*)malloc(sizeof(ArcNode));
	p->adjvex = ver2;
	p->nextarc = G.vertices[ver1].firstarc;
	G.vertices[ver1].firstarc = p;
	ArcNode *p1 = (ArcNode*)malloc(sizeof(ArcNode));
	p1->adjvex = ver1;
	p1->nextarc = G.vertices[ver2].firstarc;
	G.vertices[ver2].firstarc = p1;
	G.arcnum++;
	return OK;
}

status DeleteArc(ALGraph &G, KeyType v, KeyType w)
//10. 在图G中删除弧<v,w>，成功返回OK,否则返回ERROR
{
	int flag = 0;
	int ver1 = -1, ver2 = -1;
	for (int i = 0; i<G.vexnum; i++){
		if (G.vertices[i].data.key == v)ver1 = i;
		if (G.vertices[i].data.key == w)ver2 = i;
	}
	if (ver1<0 || ver2<0)return ERROR;
	if (G.vertices[ver1].firstarc == NULL || G.vertices[ver2].firstarc == NULL)return ERROR;
	ArcNode *p2 = G.vertices[ver1].firstarc;
	if (p2 == NULL)return ERROR;
	if (G.vertices[ver1].firstarc->adjvex == ver2){
		G.vertices[ver1].firstarc = p2->nextarc;
		free(p2);
		flag = 1;
	}
	else{
		while (p2->nextarc != NULL){
			if (p2->nextarc->adjvex == ver2){
				ArcNode *p4 = p2->nextarc;
				p2->nextarc = p2->nextarc->nextarc;
				free(p4);

				flag = 1;
				break;
			}
			p2 = p2->nextarc;
		}
	}
	if (flag == 0)return ERROR;
	ArcNode *p1 = G.vertices[ver2].firstarc;
	if (G.vertices[ver2].firstarc->adjvex == ver1){
		G.vertices[ver2].firstarc = G.vertices[ver2].firstarc->nextarc;
		free(p1);
	}
	else{
		while (p1->nextarc != NULL){
			if (p1->nextarc->adjvex == ver1){
				ArcNode *p4 = p1->nextarc;
				p1->nextarc = p1->nextarc->nextarc;
				free(p4);
				break;
			}
			p2 = p2->nextarc;
		}

	}
	G.arcnum--;
	return OK;
}
void visit(VertexType v)
{
	printf(" %d %s", v.key, v.others);
}

int flag[25];
void DFS(ALGraph &G, int now, void(*visit)(VertexType)){
	if (flag[now])return;
	flag[now] = 1;
	visit(G.vertices[now].data);
	ArcNode *p = G.vertices[now].firstarc;
	while (p != NULL){
		DFS(G, p->adjvex, visit);
		p = p->nextarc;
	}

}
status DFSTraverse(ALGraph &G, void(*visit)(VertexType))
//11. 对图G进行深度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
{
	for (int i = 0; i<G.vexnum; i++)flag[i] = 0;
	for (int i = 0; i<G.vexnum; i++)
		DFS(G, i, visit);
	return OK;
}

//int flag[25];
void BFS(ALGraph &G, int now, void(*visit)(VertexType)){
	int visitnow[25];
	for (int i = 0; i<25; i++)visitnow[i] = 0;
	int willBFS = 0;
	ArcNode *p = G.vertices[now].firstarc;
	while (p != NULL){
		if (flag[p->adjvex] == 0){
			visit(G.vertices[p->adjvex].data);
			flag[p->adjvex] = 1;
			visitnow[willBFS++] = p->adjvex;
		}
		p = p->nextarc;
	}
	willBFS = 0;
	while (visitnow[willBFS]){
		BFS(G, visitnow[willBFS++], visit);
	}

}
status BFSTraverse(ALGraph &G, void(*visit)(VertexType))
//12. 对图G进行广度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
{
	for (int i = 0; i<G.vexnum; i++)flag[i] = 0;
	for (int i = 0; i<G.vexnum; i++){
		if (flag[i] == 0){
			visit(G.vertices[i].data);
			flag[i] = 1;
			BFS(G, i, visit);
		}
	}
	return OK;
}
void BFSforVerticesSetLessThanK(ALGraph &G, int now, void(*visit)(VertexType),int dis,int k){
	if (dis == k-1)return;
	int visitnow[25];
	for (int i = 0; i<25; i++)visitnow[i] = 0;
	int willBFS = 0;
	ArcNode *p = G.vertices[now].firstarc;
	while (p != NULL){
		if (flag[p->adjvex] == 0){
			visit(G.vertices[p->adjvex].data);
			flag[p->adjvex] = 1;
			visitnow[willBFS++] = p->adjvex;
		}
		p = p->nextarc;
	}
	willBFS = 0;
	while (visitnow[willBFS]){
		BFSforVerticesSetLessThanK(G, visitnow[willBFS++], visit, dis+1, k);
	}
}

void VerticesSetLessThanK(ALGraph G, int  v, int k){
	//13.返回与顶点v距离小于k的顶点集合
	for (int i = 0; i < 25; i++)flag[i] = 0;
	int now = 0;
	for (now = 0; now < G.vexnum; now++){
		if (G.vertices[now].data.key == v)break;
	}
	if (now >= G.vexnum){
		printf("无关键字为v的结点\n");
		return;
	}
	flag[now] = 1;
	BFSforVerticesSetLessThanK(G, now, visit, 0, k);
}
int flag1 = 0;
void BFSforShortestPathLength(ALGraph &G, int from,int to, int dis){
	if (flag1==1)return;
	int visitnow[25];
	for (int i = 0; i<25; i++)visitnow[i] = 0;
	int willBFS = 0;
	ArcNode *p = G.vertices[from].firstarc;
	while (p != NULL){
		if (flag[p->adjvex] == 0){
			if (p->adjvex == to){
				printf("最短路径长度为%d", dis);
				flag1 = 1;
			}
			flag[p->adjvex] = 1;
			visitnow[willBFS++] = p->adjvex;
		}
		p = p->nextarc;
	}
	willBFS = 0;
	while (visitnow[willBFS]){
		BFSforShortestPathLength(G, visitnow[willBFS++], to, dis + 1);
	}

}
void ShortestPathLength(ALGraph G, int u, int v){
	for (int i = 0; i < 25; i++)flag[i] = 0;
	int from = LocateVex(G, u);
	int to = LocateVex(G, v);
	if (from == -1 || to == -1){
		flag1 = 1;
		printf("输入了不存在的顶点");
			return;
	}
	if (u == v){
		flag1 = 1;
		printf("输入了同一个顶点");
			return;
	}
	flag1 = 0;
	BFSforShortestPathLength(G, from, to, 1);
}
void visit1(VertexType i){
	return;
}
status ConnectedComponentsNums(ALGraph &G, void(*visit)(VertexType))
//15. 对图G进行广度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
{
	int ans = 0;
	for (int i = 0; i<G.vexnum; i++)flag[i] = 0;
	for (int i = 0; i<G.vexnum; i++){
		if (flag[i] == 0){
			ans++;
			visit(G.vertices[i].data);
			flag[i] = 1;
			BFS(G, i, visit);
		}
	}
	return ans;
}
status SaveList(ALGraph G, char FileName[])
// 16.如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
{
	if (G.vexnum==0)return INFEASIBLE;
	FILE *fp = fopen(FileName, "w");
	fprintf(fp, "%d %d %d ", G.kind, G.vexnum, G.arcnum);
	for (int i = 0; i < G.vexnum; i++){
		fprintf(fp, "%d %s ", G.vertices[i].data.key, G.vertices[i].data.others);
		ArcNode *p = G.vertices[i].firstarc;
		while (p != NULL){
			fprintf(fp, "%d  ", p->adjvex);
			p = p->nextarc;
		}
		fprintf(fp, "%d ",-1);
	}
	fclose(fp);
	return OK;
}
status  LoadList(ALGraph &G, char FileName[])
// 17.如果线性表L不存在，将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。
{
	if (G.vexnum != 0)return INFEASIBLE;
	FILE *fp = fopen(FileName, "r");
	fscanf(fp, "%d %d %d", &G.kind, &G.vexnum, &G.arcnum);
	for (int i = 0; i < G.vexnum; i++){
		int next;
		fscanf(fp, "%d %s ", &G.vertices[i].data.key, G.vertices[i].data.others);
		fscanf(fp, "%d", &next);
		ArcNode *p;
		if (next != -1){
		G.vertices[i].firstarc = (ArcNode *)malloc(sizeof(ArcNode));
		G.vertices[i].firstarc->adjvex = next;
p = G.vertices[i].firstarc;
		}
		else {
			G.vertices[i].firstarc = NULL;
			continue;
		}
		fscanf(fp, "%d", &next);
		while (next != -1){
			p->nextarc = (ArcNode *)malloc(sizeof(ArcNode));
			p->nextarc->adjvex = next;
			p = p->nextarc;
			fscanf(fp, "%d", &next);
		}
		p->nextarc = NULL;
	}

	fclose(fp);
	return OK;
}
status AddList(LISTS &Lists, char ListName[])
// 18.只需要在Lists中增加一个名称为ListName的空线性表，线性表数据又后台测试程序插入。
{

	strcpy(Lists.elem[Lists.length].name, ListName);
	Lists.elem[Lists.length].G.vexnum = 0;
	Lists.length++;
	return OK;
}

status RemoveList(LISTS &Lists, char ListName[])
//19.Lists中删除一个名称为ListName的线性表
{
	for (int i = 0; i < Lists.length; i++){
		if (strcmp(Lists.elem[i].name, ListName) == 0){
			DestroyGraph(Lists.elem[i].G);
			for (int j = i + 1; j < Lists.length; j++){
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
	for (int i = 0; i < Lists.length; i++){
		if (strcmp(Lists.elem[i].name, ListName) == 0){

			return i + 1;
		}
	}
	return 0;
}

void main(void){
	ALGraph G;
	VertexType V[30], value;
	KeyType VR[100][2];
	LISTS Lists;
	Lists.length = 0;
	Lists.listsize = 10;
	char name[30];
	int op = 1, isLists = 0;
	int i = 0, j, now, u, v, w, k;
	while (op){
		system("cls");	printf("\n\n");
		printf("      Menu for Linear Table On Sequence Structure \n");
		printf("-------------------------------------------------\n");
		printf("    	  1. CreateCraph             2. DestroyGraph\n");
		printf("    	  3. LocateVex               4.PutVex\n");
		printf("    	  5. FirstAdjVex             6.NextAdjVex \n");
		printf("    	  7. InsertVex               8. DeleteVex\n");
		printf("    	  9. InsertArc              10. DeleteArc\n");
		printf("    	 11. DFSTraverse            12. BFSTraverse\n");
		printf("    	 13. VerticesSetLessThanK   14. ShortestPathLength\n");
		printf("    	 15. ConnectedComponentsNums16. SaveList\n");
		printf("    	 17. LoadList               18. AddList\n");
		printf("    	 19. RemoveList             20. LocateList\n");
		printf("    	 21. GotoLists                   \n");
		printf("    	  0.  Exit\n");
		printf("-------------------------------------------------\n");
		printf("    请选择你的操作[0~21]:");
		scanf("%d", &op);
		switch (op){
		case 1:
			printf("请输入图的顶点集和边集！");
			i = 0;
			do {
				scanf("%d%s", &V[i].key, V[i].others);
			} while (V[i++].key != -1);
			i = 0;
			do {
				scanf("%d%d", &VR[i][0], &VR[i][1]);
			} while (VR[i++][0] != -1);
			if (isLists){
				printf("请输入图名");
				scanf("%s", name);
				now = LocateList(Lists, name);
				if (now == 0){
					printf("未找到此图");
					getchar(); getchar();
					break;
				}
				now = CreateCraph(Lists.elem[now - 1].G, V,VR);
				if (now == ERROR)Lists.elem[now - 1].G.vexnum = 0;;
			}
			else now = CreateCraph(G, V, VR);
			if (now == ERROR) printf("输入数据错，无法创建");
			else printf("创建成功！\n");
			getchar(); getchar();
			break;
		case 2:
			if (isLists){
				printf("请输入图名");
				scanf("%s", name);
				now = LocateList(Lists, name);
				if (now == 0){
					printf("未找到此图");
					getchar(); getchar();
					break;
				}
				if (Lists.elem[now - 1].G.vexnum == 0)printf("图为空！");
				else{
					DestroyGraph(Lists.elem[now - 1].G);
					printf("销毁成功！");
				}
			}
			else
			{
				if (G.vexnum == 0)printf("图为空！");
			else{
				DestroyGraph(G);
				printf("销毁成功！");

			}
			
			}
			getchar(); getchar();
			break;
		case 3:
			if (isLists){
				printf("请输入图名");
				scanf("%s", name);
				printf("请输入顶点的key");
				scanf("%d", &u);
				now = LocateList(Lists, name);
				if (now == 0){
					printf("未找到此图");
					getchar(); getchar();
					break;
				}
				now = LocateVex(Lists.elem[now - 1].G, u);
				if (now != -1)
					printf("%d %s", G.vertices[now].data.key, G.vertices[now].data.others);
				else
					printf("查找失败");
				
			}
			else{
				printf("请输入顶点的key");
				scanf("%d", &u);
				now = LocateVex(G, u);
				if (now != -1)
					printf("%d %s", G.vertices[now].data.key, G.vertices[now].data.others);
				else
					printf("查找失败");

			}
			getchar(); getchar();
			break;
		case 4:
			if (isLists){
				printf("请输入图名");
				scanf("%s", name);
				now = LocateList(Lists, name);
				if (now == 0){
					printf("未找到此图");
					getchar(); getchar();
					break;
				}
				printf("请输入顶点的key");
				scanf("%d", &u);
				printf("请输入新的key和others");
				scanf("%d%s", &value.key, value.others);
				now = PutVex(Lists.elem[now - 1].G, u, value);
			}
			else {
				printf("请输入顶点的key");
				scanf("%d", &u);
				printf("请输入新的key和others");
				scanf("%d%s", &value.key, value.others);
				now = PutVex(G, u, value);
			}

			if (now == OK)
				printf("赋值成功");
			else
				printf("赋值操作失败");
			getchar(); getchar();
			break;
		case 5:
			if (isLists){
				printf("请输入图名");
				scanf("%s", name);
				now = LocateList(Lists, name);
				if (now == 0){
					printf("未找到此图");
					getchar(); getchar();
					break;
				}
				printf("请输入顶点的key");
				scanf("%d", &u);
				now = FirstAdjVex(Lists.elem[now - 1].G, u);
			}
			else {
				printf("请输入顶点的key");
				scanf("%d", &u);
				now = FirstAdjVex(G, u);
			}
			if (now != -1)
				printf("%d %s", G.vertices[now].data.key, G.vertices[now].data.others);
			else
				printf("查找失败");
			getchar(); getchar();
			break;
		case 6:
			if (isLists){
				printf("请输入图名");
				scanf("%s", name);
				now = LocateList(Lists, name);
				if (now == 0){
					printf("未找到此图");
					getchar(); getchar();
					break;
				}
				printf("请输入两个顶点的位序");
				scanf("%d%d", &v, &w);
				i = NextAdjVex(Lists.elem[now - 1].G, v, w);
			}
			else {
				printf("请输入两个顶点的位序");
				scanf("%d%d", &v, &w);
				now = NextAdjVex(G, v, w);
			}
			if (now != -1)
				printf("%d %s", G.vertices[now].data.key, G.vertices[now].data.others);
			else
				printf("查找失败");
			getchar(); getchar();
			break;
		case 7:
			if (isLists){
				printf("请输入图名");
				scanf("%s", name);
				now = LocateList(Lists, name);
				if (now == 0){
					printf("未找到此图");
					getchar(); getchar();
					break;
				}
				printf("请输入顶点的key和others");
				scanf("%d%s", &value.key, value.others);
				now = InsertVex(Lists.elem[now - 1].G, value);
			}
			else {
				printf("请输入顶点的key和others");
				scanf("%d%s", &value.key, value.others);
				now = InsertVex(G, value);
			}
			if (now == OK)printf("插入成功");
			else printf("插入失败！");
			getchar(); getchar();
			break;
		case 8:
			if (isLists){
				printf("请输入图名");
				scanf("%s", name);
				now = LocateList(Lists, name);
				if (now == 0){
					printf("未找到此图");
					getchar(); getchar();
					break;
				}
				printf("请输入顶点的key");
				scanf("%d", &v);
				now = DeleteVex(Lists.elem[now - 1].G, v);
			}
			else {
				printf("请输入顶点的key");
				scanf("%d", &v);
				now = DeleteVex(G, v);
			}
			if (now == OK)printf("删除成功"); 
			else printf("删除失败");
			getchar(); getchar();
			break;
		case 9:
			if (isLists){
				printf("请输入图名");
				scanf("%s", name);
				now = LocateList(Lists, name);
				if (now == 0){
					printf("未找到此图");
					getchar(); getchar();
					break;
				}
				printf("请输入弧的两个顶点");
				scanf("%d%d", &v, &w);
				now = InsertArc(Lists.elem[now - 1].G, v, w);
			}
			else {
				printf("请输入弧的两个顶点");
				scanf("%d%d", &v, &w);
				now = InsertArc(G, v, w);
			}
			if (now == OK)printf("插入成功");
			else printf("插入失败");
			getchar(); getchar();
			break;
		case 10:
			if (isLists){
				printf("请输入图名");
				scanf("%s", name);
				now = LocateList(Lists, name);
				if (now == 0){
					printf("未找到此图");
					getchar(); getchar();
					break;
				}
				printf("请输入弧的两个顶点");
				scanf("%d%d", &v, &w);
				now = DeleteArc(Lists.elem[now - 1].G, v, w);
			}
			else {
				printf("请输入弧的两个顶点");
				scanf("%d%d", &v, &w);
				now = DeleteArc(G, v, w);
			}

			if (now == OK)printf("删除成功");
			else printf("删除失败");
			getchar(); getchar();
			break;
		case 11:
			if (isLists){
				printf("请输入线性表名");
				scanf("%s", name);
				now = LocateList(Lists, name);
				if (now == 0){
					printf("未找到此图");
					getchar(); getchar();
					break;
				}
				if (G.vexnum == 0)printf("图为空！");
				else	DFSTraverse(Lists.elem[now - 1].G, visit);
			}
			else {
				if (G.vexnum == 0)printf("图为空！");
                else	DFSTraverse(G, visit);
			}
			getchar(); getchar();
			break;
		case 12:if (isLists){
			printf("请输入图名");
			scanf("%s", name);
			now = LocateList(Lists, name);
			if (now == 0){
				printf("未找到此图");
				getchar(); getchar();
				break;
			}
			if (G.vexnum == 0)printf("图为空！");
			else BFSTraverse(Lists.elem[now - 1].G, visit);
		}
		        else {
					if (G.vexnum == 0)printf("图为空！");
					else BFSTraverse(G, visit);
				}
				getchar(); getchar();
				break;
		case 13:
			if (isLists){
				printf("请输入图名");
				scanf("%s", name);
				now = LocateList(Lists, name);
				if (now == 0){
					printf("未找到此图");
					getchar(); getchar();
					break;
				}
				printf("请输入顶点的key和距离小于的k");
				scanf("%d %d", &v, &k);
				VerticesSetLessThanK(Lists.elem[now - 1].G, v, k);
			}
			else {
				printf("请输入顶点的key和距离小于的k");
				scanf("%d %d", &v, &k);
				VerticesSetLessThanK(G, v, k);
			}
			getchar(); getchar();
			break;
		case 14:
			if (isLists){
				printf("请输入图名");
				scanf("%s", name);
				now = LocateList(Lists, name);
				if (now == 0){
					printf("未找到此图");
					getchar(); getchar();
					break;
				}
				printf("请输入两个顶点的key值");
				scanf("%d %d", &u, &v);
				ShortestPathLength(Lists.elem[now - 1].G, u, v);
			}
			else {
				printf("请输入两个顶点的key值");
				scanf("%d %d", &u,&v);
				ShortestPathLength(G, u, v);
			}
			if (flag1 == 0)printf("节点间不连通");
			getchar(); getchar();
			break;
		case 15:
			if (isLists){
				printf("请输入图名");
				scanf("%s", name);
				now = LocateList(Lists, name);
				if (now == 0){
					printf("未找到此图");
					getchar(); getchar();
					break;
				}
				now = ConnectedComponentsNums(Lists.elem[now - 1].G, visit1);
			}
			else {
				now=ConnectedComponentsNums(G, visit1);
			}
			printf("连通分量个数为%d", now);
			getchar(); getchar();
			break;
		case 16:
			if (isLists){
				printf("请输入图名");
				scanf("%s", name);
				now = LocateList(Lists, name);
				if (now == 0){
					printf("未找到此图");
					getchar(); getchar();
					break;
				}
				now = SaveList(G, "text");
			}
			else {
				now = SaveList(G, "text");
			}
			if (now == INFEASIBLE) printf("不能对不存在的图进行写文件操作！");
			else printf("写入完成");
			getchar(); getchar();
			break;
		case 17:
			if (isLists){
				printf("请输入图名");
				scanf("%s", name);
				now = LocateList(Lists, name);
				if (now == 0){
					printf("未找到此图");
					getchar(); getchar();
					break;
				}
				now = LoadList(G, "text");
			}
			else {
				now = LoadList(G, "text");
			}
			if (now == INFEASIBLE)printf("不能对已存在的图进行读文件操作！");
			else printf("读取完成");
			getchar(); getchar();
			break;
		case 18:
			printf("请输入要插入的图名");
			scanf("%s", name);
			AddList(Lists, name);
			printf("插入成功");
			getchar(); getchar();
			break;
		case 19:
			printf("请输入要删除的图名");
			scanf("%s", name);
			now = RemoveList(Lists, name);
			if (now == OK)printf("删除成功");
			else printf("删除失败");
			getchar(); getchar();
			break;
		case 20:
			printf("请输入要查找的图名");
			scanf("%s", name);
			now = LocateList(Lists, name);
			if (now == 0)printf("查找失败");
			else printf("图逻辑序号为%d", now);
			getchar(); getchar();
			break;
		case 21:
			if (isLists){
				isLists = 0;
				printf("退出多图模式");
			}
			else {
				isLists = 1;
				printf("进入多图模式");
			}
			getchar(); getchar();
			break;
		case 0:
			break;
		}//end of switch
	}//end of while
	printf("欢迎下次再使用本系统！\n");
}//end of main()






