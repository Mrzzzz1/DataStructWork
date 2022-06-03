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
typedef int ElemType; //����Ԫ�����Ͷ���

#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef int ElemType;
typedef struct{  //˳���˳��ṹ���Ķ���
    ElemType * elem;
    int length;
    int listsize;
}SqList;
typedef struct{  //���Ա�Ĺ������
    struct {
        char name[30];
        SqList L;
    } elem[10];
    int length;
    int listsize;
}LISTS;
status lex(FILE *fp, char word[])   //��������ĸ�ͱ�ʶ��
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
    if (!fp) { printf("�ļ���ʧ��"); return FALSE; }
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
// 1.���Ա�L�����ڣ�����һ���յ����Ա�����OK�����򷵻�INFEASIBLE��
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
// 2.������Ա�L���ڣ��������Ա�L���ͷ�����Ԫ�صĿռ䣬����OK�����򷵻�INFEASIBLE��
{
    if (L.elem != NULL){
        free(L.elem);
        L.elem = NULL;
        return OK;
    }
    return INFEASIBLE;
}
status ClearList(SqList& L)
// 3.������Ա�L���ڣ�ɾ�����Ա�L�е�����Ԫ�أ�����OK�����򷵻�INFEASIBLE��
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
//4. ������Ա�L���ڣ��ж����Ա�L�Ƿ�Ϊ�գ��վͷ���TRUE�����򷵻�FALSE��������Ա�L�����ڣ�����INFEASIBLE��
{
    if (L.elem == NULL)return INFEASIBLE;
    if (L.length == 0)return TRUE;
    return FALSE;
}
status ListLength(SqList L)
//5. ������Ա�L���ڣ��������Ա�L�ĳ��ȣ����򷵻�INFEASIBLE��
{
    if (L.elem == NULL)return INFEASIBLE;
    return L.length;
}
status GetElem(SqList L, int i, ElemType &e)
//6. ������Ա�L���ڣ���ȡ���Ա�L�ĵ�i��Ԫ�أ�������e�У�����OK�����i���Ϸ�������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    if (L.elem == NULL)return INFEASIBLE;
    if (i<1 || i>L.length)return FALSE;
    e = L.elem[i - 1];
    return OK;
}
int LocateElem(SqList L, ElemType e)
//7. ������Ա�L���ڣ�����Ԫ��e�����Ա�L�е�λ����Ų����ظ���ţ����e�����ڣ�����0�������Ա�L������ʱ������INFEASIBLE����-1����
{
    if (L.elem == NULL)return INFEASIBLE;
    for (int i = 0; i<L.length; i++){
        if (e == L.elem[i])return i + 1;
    }
    return FALSE;
}
status PriorElem(SqList L, ElemType e, ElemType &pre)
// 8.������Ա�L���ڣ���ȡ���Ա�L��Ԫ��e��ǰ����������pre�У�����OK�����û��ǰ��������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
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
// 9.������Ա�L���ڣ���ȡ���Ա�LԪ��e�ĺ�̣�������next�У�����OK�����û�к�̣�����ERROR��������Ա�L�����ڣ�����INFEASIBLE��
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
// 10.������Ա�L���ڣ���Ԫ��e���뵽���Ա�L�ĵ�i��Ԫ��֮ǰ������OK��������λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
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
// 11.������Ա�L���ڣ�ɾ�����Ա�L�ĵ�i��Ԫ�أ���������e�У�����OK����ɾ��λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    if (L.elem == NULL)return INFEASIBLE;
    if (i>L.length || i <= 0)return ERROR;
    e = L.elem[i - 1];
    for (int j = i - 1; j<L.length - 1; j++)L.elem[j] = L.elem[j + 1];
    L.length--;
    return OK;
}
status ListTraverse(SqList L)
// 12.������Ա�L���ڣ�������ʾ���Ա��е�Ԫ�أ�ÿ��Ԫ�ؼ��һ�񣬷���OK��������Ա�L�����ڣ�����INFEASIBLE��
{
    if (L.elem == NULL)return INFEASIBLE;
    for (int i = 0; i<L.length; i++){
        printf("%d", L.elem[i]);
        if (i != L.length - 1)printf(" ");
    }
    return OK;
}
int MaxSubArray(SqList L){
    //13.��������������
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
//14.��Ϊk�����������顣
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
//15.��������
    if (low < high)
    {
        int i = low;
        int j = high;
        int k = arr[low];
        while (i < j)
        {
            while (i < j && arr[j] >= k)     // ���������ҵ�һ��С��k����
            {
                j--;
            }

            if (i < j)
            {
                arr[i++] = arr[j];
            }

            while (i < j && arr[i] < k)      // ���������ҵ�һ�����ڵ���k����
            {
                i++;
            }

            if (i < j)
            {
                arr[j--] = arr[i];
            }
        }

        arr[i] = k;

        // �ݹ����
        QuickSort(arr, low, i - 1);     // ����k���
        QuickSort(arr, i + 1, high);    // ����k�ұ�
    }
}
status  SaveList(SqList L, char FileName[])
// 16.������Ա�L���ڣ������Ա�L�ĵ�Ԫ��д��FileName�ļ��У�����OK�����򷵻�INFEASIBLE��
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
// 17.������Ա�L�����ڣ���FileName�ļ��е����ݶ��뵽���Ա�L�У�����OK�����򷵻�INFEASIBLE��
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
// 18.ֻ��Ҫ��Lists������һ������ΪListName�Ŀ����Ա����Ա������ֺ�̨���Գ�����롣
{

    strcpy(Lists.elem[Lists.length].name, ListName);
    Lists.elem[Lists.length].L.elem = (ElemType*)malloc(sizeof(ElemType)*LIST_INIT_SIZE);
    Lists.elem[Lists.length].L.length = 0;
    Lists.elem[Lists.length].L.listsize = LIST_INIT_SIZE;
    Lists.length++;
    return OK;
}

status RemoveList(LISTS &Lists, char ListName[])
//19.Lists��ɾ��һ������ΪListName�����Ա�
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
        printf("    ��ѡ����Ĳ���[0~21]:");
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
                if (ClearList(Lists.elem[now-1].L) == OK)printf("���Ա���ճɹ���\n");
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
                now=ListEmpty(L);
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
                now = NextElem(L, e, pre);
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
             if (!ListTraverse(L)) printf("���Ա��ǿձ�\n");
            }
            getchar(); getchar();
            break;
        case 13:
            if (isLists){
                printf("���������Ա���");
                scanf("%s", name);
                now = LocateList(Lists, name);
                now = MaxSubArray(Lists.elem[now - 1].L);
            }
            else {
                now = MaxSubArray(L);
            }
            if (now == INFEASIBLE) printf("���Ա��ǿձ�\n");
            else printf("��������Ϊ%d", now);
            getchar(); getchar();
            break;
        case 14:
            if (isLists){
                printf("���������Ա���");
                scanf("%s", name);
                now = LocateList(Lists, name);
                printf("������k��ֵ");
                scanf("%d", &k);
                now = SubArrayNum(Lists.elem[now - 1].L, k);
            }
            else {
                printf("������k��ֵ");
                scanf("%d", &k);
                now = SubArrayNum(L, k);
            }
            if (now == INFEASIBLE) printf("���Ա��ǿձ�\n");
            else printf("��Ϊ%d��������������%d��", k, now);
            getchar(); getchar();
            break;
        case 15:
            if (L.length == 0)printf("���Ա��ǿձ�\n");
            else {
                QuickSort(L.elem, 0, L.length - 1);
                printf("�������");
            } 
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