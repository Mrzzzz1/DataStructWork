#include<stdio.h>
#include <stdlib.h>
#include<ctype.h>
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
typedef struct{  //顺序表（顺序结构）的定义
    ElemType * elem;
    int length;
    int listsize;
}SqList;
typedef struct{  //线性表的管理表定义
    struct {
        char name[30];
        SqList L;
    } elem[10];
    int length;
    int listsize;
}LISTS;
status lex(FILE *fp, char word[])   //仅查找字母型标识符
{
    char c, c1, i;
    while ((c = fgetc(fp)) != EOF && !feof(fp))
    {
        if (isspace(c)) continue;
        if (c == '/')
        {
            c == fgetc(fp);
            if (c == EOF) return ERROR;
            if (c == '/')
            {
                while ((c = fgetc(fp)) != '\n')
                    if (c == EOF) return ERROR;
                continue;
            }
            if (c == '*')
            {
                c = fgetc(fp);
                if (c == EOF) return ERROR;
                do
                {
                    c1 = c;
                    c = fgetc(fp);
                    if (c == EOF) return ERROR;
                } while (c1 != '*' || c != '/');
                continue;
            }
        }
        if (!isalpha(c)) continue;
        i = 0;
        do {
            word[i++] = c;
        } while (isalpha(c = fgetc(fp)));
        if (isspace(c) || !(c >= '0' && c <= '9') || c == EOF)
        {
            word[i] = '\0';
            return OK;
        }
    }
    return ERROR;
}
status match(char fileName[], char keyword[])
{
    FILE *fp;
    char word[50];
    fp = fopen(fileName, "r");
    if (!fp) { printf("文件打开失败"); return FALSE; }
    while (lex(fp, word) == OK){
        if (strcmp(keyword, word))
            continue;
        fclose(fp);
        return TRUE;
    }
    fclose(fp);
    return FALSE;
}


status InitList(SqList& L)
// 1.线性表L不存在，构造一个空的线性表，返回OK，否则返回INFEASIBLE。
{
    if (L.elem == NULL){
        L.elem = (ElemType*)malloc(sizeof(ElemType)*LIST_INIT_SIZE);
        L.length = 0;
        L.listsize = LIST_INIT_SIZE;
        return OK;
    }
    return INFEASIBLE;
}
status DestroyList(SqList& L)
// 2.如果线性表L存在，销毁线性表L，释放数据元素的空间，返回OK，否则返回INFEASIBLE。
{
    if (L.elem != NULL){
        free(L.elem);
        L.elem = NULL;
        return OK;
    }
    return INFEASIBLE;
}
status ClearList(SqList& L)
// 3.如果线性表L存在，删除线性表L中的所有元素，返回OK，否则返回INFEASIBLE。
{
    if (L.elem != NULL){
        for (int i = 0; i<L.length; i++){
            L.elem[i] = 0;
        }
        L.length = 0;
        return OK;
    }
    return INFEASIBLE;
}
status ListEmpty(SqList L)
//4. 如果线性表L存在，判断线性表L是否为空，空就返回TRUE，否则返回FALSE；如果线性表L不存在，返回INFEASIBLE。
{
    if (L.elem == NULL)return INFEASIBLE;
    if (L.length == 0)return TRUE;
    return FALSE;
}
status ListLength(SqList L)
//5. 如果线性表L存在，返回线性表L的长度，否则返回INFEASIBLE。
{
    if (L.elem == NULL)return INFEASIBLE;
    return L.length;
}
status GetElem(SqList L, int i, ElemType &e)
//6. 如果线性表L存在，获取线性表L的第i个元素，保存在e中，返回OK；如果i不合法，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if (L.elem == NULL)return INFEASIBLE;
    if (i<1 || i>L.length)return FALSE;
    e = L.elem[i - 1];
    return OK;
}
int LocateElem(SqList L, ElemType e)
//7. 如果线性表L存在，查找元素e在线性表L中的位置序号并返回该序号；如果e不存在，返回0；当线性表L不存在时，返回INFEASIBLE（即-1）。
{
    if (L.elem == NULL)return INFEASIBLE;
    for (int i = 0; i<L.length; i++){
        if (e == L.elem[i])return i + 1;
    }
    return FALSE;
}
status PriorElem(SqList L, ElemType e, ElemType &pre)
// 8.如果线性表L存在，获取线性表L中元素e的前驱，保存在pre中，返回OK；如果没有前驱，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if (L.elem == NULL)return INFEASIBLE;
    for (int i = 1; i<L.length; i++){
        if (L.elem[i] == e){
            pre = L.elem[i - 1];
            return OK;
        }
    }
    return FALSE;
}
status NextElem(SqList L, ElemType e, ElemType &next)
// 9.如果线性表L存在，获取线性表L元素e的后继，保存在next中，返回OK；如果没有后继，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{

    if (L.elem == NULL)return INFEASIBLE;
    for (int i = 0; i<L.length - 1; i++){
        if (L.elem[i] == e){
            next = L.elem[i + 1];
            return OK;
        }
    }
    return FALSE;
}
status ListInsert(SqList &L, int i, ElemType e)
// 10.如果线性表L存在，将元素e插入到线性表L的第i个元素之前，返回OK；当插入位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if (L.elem == NULL)return INFEASIBLE;
    if (i>L.length + 1 || i <= 0)return FALSE;
    if (L.length == L.listsize){
        ElemType* newbase = (ElemType*)realloc(L.elem, (L.listsize + LISTINCREMENT)*sizeof(ElemType));
        L.elem = newbase;
    }
    for (int j = L.length; j >= i - 1; j--){
        L.elem[j] = L.elem[j - 1];
    }
    L.elem[i - 1] = e;
    L.length++;
    return OK;
}
status ListDelete(SqList &L, int i, ElemType &e)
// 11.如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK；当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if (L.elem == NULL)return INFEASIBLE;
    if (i>L.length || i <= 0)return ERROR;
    e = L.elem[i - 1];
    for (int j = i - 1; j<L.length - 1; j++)L.elem[j] = L.elem[j + 1];
    L.length--;
    return OK;
}
status ListTraverse(SqList L)
// 12.如果线性表L存在，依次显示线性表中的元素，每个元素间空一格，返回OK；如果线性表L不存在，返回INFEASIBLE。
{
    if (L.elem == NULL)return INFEASIBLE;
    for (int i = 0; i<L.length; i++){
        printf("%d", L.elem[i]);
        if (i != L.length - 1)printf(" ");
    }
    return OK;
}
int MaxSubArray(SqList L){
    //13.最大连续子数组和
    if (L.elem == NULL)return INFEASIBLE;
    int i;
    int MaxSum = -9999999;
    int ThisSum = 0;
    for (i = 0; i < L.length; i++)
    {
        ThisSum += L.elem[i];
        if (ThisSum > MaxSum)
        {
            MaxSum = ThisSum;
        }
        if (ThisSum < 0)
        {
            ThisSum = 0;
        }
    }
    return MaxSum;
}
int SubArrayNum(SqList L, int k){
//14.和为k的连续子数组。
    if (L.elem == NULL)return INFEASIBLE;
    int ans = 0;
    for (int i = 0; i < L.length; i++){
        int sum=0;
        for (int j = i; j < L.length; j++){
            sum += L.elem[j];
            if (sum == k)ans++;
        }
    }
    return ans;
}
void QuickSort(int *arr, int low, int high)
{
//15.快速排序
    if (low < high)
    {
        int i = low;
        int j = high;
        int k = arr[low];
        while (i < j)
        {
            while (i < j && arr[j] >= k)     // 从右向左找第一个小于k的数
            {
                j--;
            }

            if (i < j)
            {
                arr[i++] = arr[j];
            }

            while (i < j && arr[i] < k)      // 从左向右找第一个大于等于k的数
            {
                i++;
            }

            if (i < j)
            {
                arr[j--] = arr[i];
            }
        }

        arr[i] = k;

        // 递归调用
        QuickSort(arr, low, i - 1);     // 排序k左边
        QuickSort(arr, i + 1, high);    // 排序k右边
    }
}
status  SaveList(SqList L, char FileName[])
// 16.如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
{
    if (L.elem == NULL)return INFEASIBLE;
    FILE *fp = fopen(FileName, "w");
    for (int i = 0; i<L.length; i++){
        fprintf(fp, "%d ", L.elem[i]);
    }
    fclose(fp);
    return OK;


}
status  LoadList(SqList &L, char FileName[])
// 17.如果线性表L不存在，将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。
{
    if (L.elem != NULL)return INFEASIBLE;
    L.elem = (ElemType*)malloc(sizeof(ElemType)*LIST_INIT_SIZE);
    L.length = 0;
    L.listsize = LIST_INIT_SIZE;
    FILE *fp = fopen(FileName, "r");
    int c;
    while (fscanf(fp, "%d", &c) != EOF){
        L.elem[(L.length)++] = c;
    }

    fclose(fp);
    return OK;
}

status AddList(LISTS &Lists, char ListName[])
// 18.只需要在Lists中增加一个名称为ListName的空线性表，线性表数据又后台测试程序插入。
{

    strcpy(Lists.elem[Lists.length].name, ListName);
    Lists.elem[Lists.length].L.elem = (ElemType*)malloc(sizeof(ElemType)*LIST_INIT_SIZE);
    Lists.elem[Lists.length].L.length = 0;
    Lists.elem[Lists.length].L.listsize = LIST_INIT_SIZE;
    Lists.length++;
    return OK;
}

status RemoveList(LISTS &Lists, char ListName[])
//19.Lists中删除一个名称为ListName的线性表
{
    for (int i = 0; i<Lists.length; i++){
        if (strcmp(Lists.elem[i].name, ListName) == 0){
            free(Lists.elem[i].L.elem);
            Lists.elem[i].L.elem = NULL;
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
    SqList L;  
    L.elem = NULL;
    L.length = 0;
    L.listsize = 0;
    LISTS Lists;
    Lists.length = 0;
    Lists.listsize = 10;
    char name[30];
    int op = 1,isLists=0;
    int i, e,now,pre,next,k;

    while (op){
        system("cls");    printf("\n\n");
        printf("      Menu for Linear Table On Sequence Structure \n");
        printf("-------------------------------------------------\n");
        printf("          1. InitList       2. DestroyList\n");
        printf("          3. ClearList      4. ListEmpty\n");
        printf("          5. ListLength     6. GetElem \n");
        printf("          7. LocateElem     8. PriorElem\n");
        printf("          9. NextElem      10. ListInsert\n");
        printf("         11. ListDelete    12. ListTrabverse\n");
        printf("         13. MaxSubArray   14. SubArrayNum\n");
        printf("         15. sortList      16. SaveList\n");
        printf("         17. LoadList      18. AddList\n");
        printf("         19. RemoveList    20. LocateList\n");
        printf("         21. GotoLists                   \n");
        printf("          0.  Exit\n");
        printf("-------------------------------------------------\n");
        printf("    请选择你的操作[0~21]:");
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
                if (ClearList(Lists.elem[now-1].L) == OK)printf("线性表清空成功！\n");
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
                now=ListEmpty(L);
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
                now = NextElem(L, e, pre);
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
             if (!ListTraverse(L)) printf("线性表是空表！\n");
            }
            getchar(); getchar();
            break;
        case 13:
            if (isLists){
                printf("请输入线性表名");
                scanf("%s", name);
                now = LocateList(Lists, name);
                now = MaxSubArray(Lists.elem[now - 1].L);
            }
            else {
                now = MaxSubArray(L);
            }
            if (now == INFEASIBLE) printf("线性表是空表！\n");
            else printf("最大数组和为%d", now);
            getchar(); getchar();
            break;
        case 14:
            if (isLists){
                printf("请输入线性表名");
                scanf("%s", name);
                now = LocateList(Lists, name);
                printf("请输入k的值");
                scanf("%d", &k);
                now = SubArrayNum(Lists.elem[now - 1].L, k);
            }
            else {
                printf("请输入k的值");
                scanf("%d", &k);
                now = SubArrayNum(L, k);
            }
            if (now == INFEASIBLE) printf("线性表是空表！\n");
            else printf("和为%d的连续子数组有%d个", k, now);
            getchar(); getchar();
            break;
        case 15:
            if (L.length == 0)printf("线性表是空表！\n");
            else {
                QuickSort(L.elem, 0, L.length - 1);
                printf("排序完成");
            } 
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