#include <stdio.h>
#include <string.h>
#include <stdlib.h> //exit(0)������stdlib.h�������

#define _CRT_SECURE_NO_WARNINGS //��ֹfscanf����
#define N 100 //���洢2000�˵�����
int count = 0;//count ��ʾ����ʵ������

struct Student {
    char num[20]; //ѧ��
    char name[20]; //����
    char classnum[20]; //�༶
    int age; //����
    char sex[20]; //�Ա�
    char date[20]; //��������
    char addr[20]; //��ַ
    char tele[20]; //�绰
    int course_sum; //�γ���
    int score[10]; //ÿ�ſεĳɼ�
}; //����ṹ�����ͣ�ѧ����Ϣ

struct Student stu[N]; //����ṹ����������
struct Student *p = stu; //����ָ��ṹ������Ԫ�ص�ָ�����������ʵ��

void Menu(); //�˵�����
void Add(struct Student stu[]);  //¼��ѧ����Ϣ
void Show(struct Student stu[], int count); //���ѧ����Ϣ
void S_Menu(); //��ѯ�˵�����
void Search_num(struct Student stu[], int count);//��ѧ�Ų�ѯѧ����Ϣ
void Search_class(struct Student stu[], int count);//���༶��ѯѧ����Ϣ
void Search_sex(struct Student stu[], int count);//���༶��ѯѧ����Ϣ
void Delete(struct Student stu[], int count);//ɾ��ѧ����Ϣ
void Modify(struct Student stu[], int count);//�޸�ѧ����Ϣ
void Show_fail(struct Student stu[], int count);//ͳ�Ʋ�����ѧ����Ϣ
void Show_good(struct Student stu[], int count);//ͳ���ŵ���ѧ����Ϣ

//�����ļ����ʺ���
void initial();//��ʼ�������ļ���¼File_Student.txt������
void Save(struct Student stu[], int count);


int main() {
    initial();//���ļ���¼File_Student.txt���ṹ������
    int input = 0;
    while (1) {
        Menu();
        scanf_s("%d", &input);
        switch (input) {
            case 0:
                Save(p, count);
                exit(0);
            case 1:
                Add(p);
                break;
            case 2:
                Show(p, count);
                break;
            case 3:
                S_Menu();
                break;
            case 4:
                Delete(p, count);
                break;
            case 5:
                Modify(p, count);
                break;
            case 6:
                Show_fail(p, count);
                break;
            case 7:
                Show_good(p, count);
                break;
            default:
                printf("�������");
                break;
        }
    }
}

//

void initial() {
    printf("��ʼ���ļ�\n");
    int i = 0;
    FILE *fp;
    fp = fopen("FILE_Student.txt", "r");
    if (fp == NULL) {
        printf("�ļ���ʧ��!\n");
        printf("��ʼ���ļ�");
        fp = fopen("FILE_Student.txt", "w");
    }

    while (fscanf(fp, "%s\t%s\t%s\t%d\t%s\t%s\t%s\t%s\t%d",
                  stu[i].num, stu[i].name, stu[i].classnum,
                  &stu[i].age, stu[i].sex, stu[i].date,
                  stu[i].tele, stu[i].addr, &stu[i].course_sum) != EOF) {
        for (int j = 0; j < stu[i].course_sum; j++) {
            fscanf(fp, "\t%d", &stu[i].score[j]);
//            printf("%d", stu[i].score[j]);
        }
        fscanf(fp, "\n");
        i++;
    }
    count = i;
    fclose(fp);
    printf("��ȡ�ɹ�!\n");
}

void Save(struct Student stu[], int count) {
    FILE *fp;//�����ļ��ṹ��ָ��
    fopen_s(&fp, "FILE_Student.txt", "wb");//����"FILE_Student.txt"�ļ�
    if (fp == NULL) {
        printf("���ļ�ʧ��\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s\t%s\t%s\t%d\t%s\t%s\t%s\t%s\t%d", stu[i].num, stu[i].name, stu[i].classnum, stu[i].age,
                stu[i].sex, stu[i].date, stu[i].tele, stu[i].addr, stu[i].course_sum);
        for (int j = 0; j < stu[i].course_sum; j++) {
            fprintf(fp, "\t%d", stu[i].score[j]);
        }
        if (i != count - 1) {
            fprintf(fp, "\n");
        }
    }//��ѧ����Ϣ����ĸ�ʽ�����fp�ļ���
    fclose(fp);//�ر��ļ�
    printf("ѧ�����ݱ���ɹ���\n");
}

void Menu() {
    {
        printf("__________________________\n");
        printf("ѧ����Ϣ����ϵͳ\n");
        printf("1��¼��ѧ����Ϣ\n");
        printf("2�����ѧ����Ϣ\n");
        printf("3����ѯѧ����Ϣ\n");
        printf("4��ɾ��ѧ����Ϣ\n");
        printf("5���޸�ѧ����Ϣ\n");
        printf("6�����ܲ�����ѧ����Ϣ\n");
        printf("7��ͳ���ŵ���ѧ����Ϣ\n");
        printf("0���˳�ϵͳ\n");
        printf("__________________________\n");
        printf("��ѡ��0-7����");
    }
}

void Add(struct Student stu[]) {
    int i = 0;
    char choose;
    printf("������ѧ������Ϣ��\n");
    do {
        i = count;
        printf("ѧ�ţ�");
        scanf_s("%s", &stu[i].num, 20);
        printf("���֣�");
        scanf_s("%s", &stu[i].name, 20);
        printf("�༶��");
        scanf_s("%s", &stu[i].classnum, 20);
        printf("���䣺");
        scanf_s("%d", &stu[i].age);
        printf("�Ա�");
        scanf_s("%s", &stu[i].sex, 20);
        printf("�������ڣ�");
        scanf_s("%s", &stu[i].date, 20);
        printf("�绰��");
        scanf_s("%s", &stu[i].tele, 20);
        printf("��ַ��");
        scanf_s("%s", &stu[i].addr, 20);
        printf("�γ�����");
        scanf_s("%d", &stu[i].course_sum);
        for (int j = 0; j < stu[i].course_sum; j++) {
            printf("��%d�ſγ̳ɼ���", j + 1);
            scanf_s("%d", &stu[i].score[j]);
        }
        printf("�Ƿ������(Y/N)\n");
        getchar();//���ջس�
        scanf_s("%c", &choose, 1);
        count++;
    } while (choose == 'Y');
    //���㷨����ʵ��ѭ���شӿ���̨����ѧ����Ϣ�����������ƣ�
    //�������굱ǰѧ����Ϣʱ��ϵͳ����ʾ�Ƿ�������룬��������룬
    //����Y�������������������������롣
    printf("��ǰѧ������Ϊ%d\n", count);
    Save(p, count);//���浽�ļ���
}

void Show(struct Student stu[], int count) {
    printf("����%d��ѧ����Ϣ\n", count);
    if (count == 0)//count��ʾ¼���ѧ����
    {
        printf("******Ŀǰû�л���Ϣ******\n");
    } else {
        printf("ѧ��\t����\t�Ա�\t�༶\t����\t����\t�绰\t��ַ\t���Ƴɼ�\n");
        for (int i = 0; i < count; i++) {
            printf("%s\t%s\t%s\t%s\t%d\t%s\t%s\t%s", stu[i].num, stu[i].name, stu[i].sex, stu[i].classnum, stu[i].age,
                   stu[i].date, stu[i].tele, stu[i].addr);
            for (int j = 0; j < stu[i].course_sum; j++) {
                printf(" \t%d", stu[i].score[j]);
            }
            printf("\n");
//            break;
        }
    }// \tΪ�Ʊ�� ���Խ�����Ľ������һ���ļ������
}


void Delete(struct Student stu[], int count) {
    char num[20];
    printf("������ѧ����ѧ�ţ�");
    scanf_s("%s", num, 20);
    num[19] = '\0';
    for (int i = 0; i < count; i++) {
        if (strcmp(num, stu[i].num) == 0) {
            for (int j = i; j < count - 1; j++) {
                stu[j] = stu[j + 1];
            }//�ӵ�j����Ϣ��ʼ������һ������ǰ��һ������ʵ�ֶԵ�j����Ϣ��ɾ��
            count--;
            printf("��ѧ����ɾ��\n");
            break;
        }
    }
    Save(stu, count);
}

void Modify(struct Student stu[], int count) {
    char num[20];
    printf("��ѡ����Ҫ�޸ĵ�ѧ����Ϣ��ѧ�ţ�\n");
    scanf_s("%s", num, 20);
    num[19] = '\0';
    for (int i = 0; i < count; i++)//ͨ�������ṹ�����飬�Ƚ�ѧ����Ϣ������ʵ����Ϣ�޸�
    {
        if (strcmp(num, stu[i].num) == 0) {
            printf("�������޸ĺ��ѧ�ţ�");
            scanf_s("%s", &stu[i].num, 20);
            printf("�������޸ĺ�����֣�");
            scanf_s("%s", &stu[i].name, 20);
            printf("�������޸ĺ�İ༶��");
            scanf_s("%s", &stu[i].classnum, 20);
            printf("�������޸ĺ�����䣺");
            scanf_s("%d", &stu[i].age);
            printf("�������޸ĺ���Ա�");
            scanf_s("%s", &stu[i].sex, 20);
            printf("�������޸ĺ�ĳ������ڣ�");
            scanf_s("%s", &stu[i].date, 20);
            printf("�������޸ĺ�ĵ绰��");
            scanf_s("%s", &stu[i].tele, 20);
            printf("�������޸ĺ�ĵ�ַ��");
            scanf_s("%s", &stu[i].addr, 20);
            printf("�������޸ĺ�Ŀγ�����");
            scanf_s("%d", &stu[i].course_sum);
            for (int j = 0; j < stu[i].course_sum; j++) {
                printf("�������޸ĺ�ĵ�%d�ſγ̳ɼ���", j + 1);
                scanf_s("%d", &stu[i].score[j]);
            }
            printf("�޸ĺ����Ϣ���£�\n");
            printf("ѧ��\t����\t�Ա�\t�༶\t����\t����\t�绰\t��ַ\t���Ƴɼ�\n");
            printf("%s\t%s\t%s\t%s\t%d\t%s\t%s\t%s", stu[i].num, stu[i].name, stu[i].sex, stu[i].classnum, stu[i].age,
                   stu[i].date, stu[i].tele, stu[i].addr);
            for (int j = 0; j < stu[i].course_sum; j++) {
                printf(" \t%d", stu[i].score[j]);
            }
            printf("\n");
        }
    }
    Save(stu, count);//�޸���ɺ�Խ��䱣�����ļ���
}

void S_Menu() {
    int input = 0;
    printf("__________________________\n");
    printf("��ѯ�˵�\n");
    printf("1����ѧ�Ų�ѯ\n");
    printf("2�����༶��ѯ\n");
    printf("3�����Ա��ѯ\n");
    printf("__________________________\n");
    printf("��ѡ��1-3����");
    scanf_s("%d", &input);
    switch (input) {
        case 1:
            Search_num(p, count);
            break;
        case 2:
            Search_class(p, count);
            break;
        case 3:
            Search_sex(p, count);
            break;
        default:
            printf("�������");
            break;
    }
}

void Search_num(struct Student stu[], int count) {
    char num[20];
    int i;
    int find = 0;//����find��0��ʾû�ҵ���1��ʾ�ҵ�
    printf("����ѧ��ѧ�ţ�\n");
    scanf_s("%s", &num, 20);
    printf("����������£�\n");
    for (i = 0; i < count; i++)//ͨ�������ṹ�����飬�Ƚ�ѧ����Ϣ���Ӷ�ʵ�ֲ���
    {
        if (strcmp(num, stu[i].num) == 0) {
            printf("ѧ��\t����\t�Ա�\t�༶\t����\t����\t�绰\t��ַ\t���Ƴɼ�\n");
            printf("%s\t%s\t%s\t%s\t%d\t%s\t%s\t%s", stu[i].num, stu[i].name, stu[i].sex, stu[i].classnum, stu[i].age,
                   stu[i].date, stu[i].tele, stu[i].addr);
            for (int j = 0; j < stu[i].course_sum; j++) {
                printf(" \t%d", stu[i].score[j]);
            }
            printf("\n");
            find = 1;
            break;
        }
    }
    if (find == 0) {
        printf("û���ҵ������Ϣ��\n");
    }
}

void Search_sex(struct Student stu[], int count) {
    char sex[20];
    int i;
    int find = 0;
    printf("�����Ա�\n");
    scanf_s("%s", &sex, 20);
    printf("��ѯ������£�\n");
    printf("ѧ��\t����\t�Ա�\t�༶\t����\t����\t�绰\t��ַ\t���Ƴɼ�\n");
    for (i = 0; i < count; i++)//ͨ�������ṹ�����飬�Ƚ��Ա���Ϣ���Ӷ�ʵ�ֲ���
    {
        if (strcmp(sex, stu[i].sex) == 0) {
            printf("%s\t%s\t%s\t%s\t%d\t%s\t%s\t%s", stu[i].num, stu[i].name, stu[i].sex, stu[i].classnum, stu[i].age,
                   stu[i].date, stu[i].tele, stu[i].addr);
            for (int j = 0; j < stu[i].course_sum; j++) {
                printf(" \t%d", stu[i].score[j]);
            }
            printf("\n");
            find = 1;
        }
    }
    if (find == 0) {
        printf("û���ҵ������Ϣ��\n");
    }
}

void Search_class(struct Student stu[], int count) {
    char classnum[20];
    int i;
    int find = 0;
    printf("����༶��\n");
    scanf_s("%s", &classnum, 20);
    printf("��ѯ������£�\n");
    printf("ѧ��\t����\t�Ա�\t�༶\t����\t����\t�绰\t��ַ\t���Ƴɼ�\n");
    for (i = 0; i < count; i++)//ͨ�������ṹ�����飬�Ƚϰ༶��Ϣ���Ӷ�ʵ�ֲ���
    {
        if (strcmp(classnum, stu[i].classnum) == 0) {
            printf("%s\t%s\t%s\t%s\t%d\t%s\t%s\t%s", stu[i].num, stu[i].name, stu[i].sex, stu[i].classnum, stu[i].age,
                   stu[i].date, stu[i].tele, stu[i].addr);
            for (int j = 0; j < stu[i].course_sum; j++) {
                printf(" \t%d", stu[i].score[j]);
            }
            printf("\n");
            find = 1;
        }
    }
    if (find == 0) {
        printf("û���ҵ������Ϣ��\n");
    }
}


void Show_fail(struct Student stu[], int count) {
    int flag = 0;//��flag����ڱ�����������и�ѧ���Ƿ񲻼��񣬲�������1
    if (count == 0) {
        printf("******Ŀǰû�л���Ϣ********\n");
    } else {
        printf("ѧ��\t����\t�Ա�\t�༶\t����\t����\t�绰\t��ַ\t���Ƴɼ�\n");//��ӡ��ͷ
        for (int i = 0; i < count; i++) {
            flag = 0;
            for (int j = 0; j < stu[i].course_sum; j++) {
                if (stu[i].score[j] < 60)
                    flag = 1;//����С��60�ּ�������
            }
            if (flag == 1) {
                printf("%s\t%s\t%s\t%s\t%d\t%s\t%s\t%s", stu[i].num, stu[i].name, stu[i].sex, stu[i].classnum,
                       stu[i].age, stu[i].date, stu[i].tele, stu[i].addr);
                for (int j = 0; j < stu[i].course_sum; j++) {
                    printf(" \t%d", stu[i].score[j]);
                }
                printf("\n");
            }
        }
    }
}

void Show_good(struct Student stu[], int count)//��ʾ�ŵ�����Ϣ
{
    FILE *fp;//�����ļ��ṹ��ָ��
    fopen_s(&fp, "Show_good.txt", "wb");//���ļ�
    if (fp == NULL) {
        printf("can not open file\n");
        exit(0);
    }
    float ave[100];//����һ��ave�������ڴ洢ÿ��ѧ���ĳɼ�ƽ��ֵ
    float sum = 0;
    for (int i = 0; i < count; i++) {
        sum = 0;
        for (int j = 0; j < stu[i].course_sum; j++) {
            sum = sum + stu[i].score[j];
        }
        ave[i] = sum / stu[i].course_sum;
    }//��ÿ��ѧ���ĳɼ�ƽ��ֵ
    int flag = 0;
    for (int i = 0; i < count; i++) {
        flag = 0;
        if (ave[i] >= 80)//ƽ���ɼ�����80
            flag = 1;
        else if (ave[i] >= 60 && ave[i] < 80) {
            for (int j = 0; j < stu[i].course_sum; j++) {
                if (stu[i].score[j] >= 90)//ƽ���ɼ����񣬵��Ƴɼ���90
                    flag = 1;
            }
        } else if (ave[i] < 60) {
            for (int j = 0; j < stu[i].course_sum; j++) {
                if (stu[i].score[j] == 100)//ƽ���ɼ������񣬵���������
                    flag = 1;
            }
        }//��Ϊ���Ƴɼ��������ж���Ҫ������ѭ�����жϣ��޷����ŵ������ж�����д��һ���ж������
        //���԰�������һһ�жϣ����ж�ƽ���ɼ������жϵ��Ƴɼ���90�����ж�����100��ʹ�ö��if else��䣬������һһ��������flag����Ϊ1��������ʵ�ֹ��ܡ�
        if (flag == 1) {
            printf("ѧ��\t����\t�Ա�\t�༶\t����\t����\t�绰\t��ַ\t���Ƴɼ�\n");
            printf("%s\t%s\t%s\t%s\t%d\t%s\t%s\t%s", stu[i].num, stu[i].name, stu[i].sex, stu[i].classnum, stu[i].age,
                   stu[i].date, stu[i].tele, stu[i].addr);
            for (int j = 0; j < stu[i].course_sum; j++) {
                printf(" \t%d", stu[i].score[j]);
            }
            printf("\n");
            fprintf(fp, "%s\t%s\t%s\t%d\t%s\t%s\t%s\t%s\t%d", stu[i].num, stu[i].name, stu[i].classnum, stu[i].age,
                    stu[i].sex, stu[i].date, stu[i].tele, stu[i].addr, stu[i].course_sum);
            for (int j = 0; j < stu[i].course_sum; j++) {
                fprintf(fp, "\t%d", stu[i].score[j]);
            }
            fprintf(fp, "\n");
        }//��ӡ���ŵ���ѧ����Ϣ�����ҽ��������fp�ļ�
    }
    fclose(fp);
    printf("�ŵ������ݱ���ɹ���\n");
}//���ŵ�������ɸѡ���ŵ�������Ŀ���뵥���ļ������������Ļ

