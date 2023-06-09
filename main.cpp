#include <stdio.h>
#include <string.h>
#include <stdlib.h> //exit(0)函数在stdlib.h这个库中

#define _CRT_SECURE_NO_WARNINGS //防止fscanf报错
#define N 100 //最多存储2000人的数据
int count = 0;//count 表示数组实际数据

struct Student {
    char num[20]; //学号
    char name[20]; //姓名
    char classnum[20]; //班级
    int age; //年龄
    char sex[20]; //性别
    char date[20]; //出生年月
    char addr[20]; //地址
    char tele[20]; //电话
    int course_sum; //课程数
    int score[10]; //每门课的成绩
}; //定义结构体类型：学生信息

struct Student stu[N]; //定义结构体类型数组
struct Student *p = stu; //定义指向结构体数组元素的指针变量用于作实参

void Menu(); //菜单界面
void Add(struct Student stu[]);  //录入学生信息
void Show(struct Student stu[], int count); //浏览学生信息
void S_Menu(); //查询菜单界面
void Search_num(struct Student stu[], int count);//按学号查询学生信息
void Search_class(struct Student stu[], int count);//按班级查询学生信息
void Search_sex(struct Student stu[], int count);//按班级查询学生信息
void Delete(struct Student stu[], int count);//删除学生信息
void Modify(struct Student stu[], int count);//修改学生信息
void Show_fail(struct Student stu[], int count);//统计不及格学生信息
void Show_good(struct Student stu[], int count);//统计优等生学生信息

//两个文件访问函数
void initial();//初始化，读文件记录File_Student.txt到数组
void Save(struct Student stu[], int count);


int main() {
    initial();//读文件记录File_Student.txt到结构体数组
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
                printf("输入错误");
                break;
        }
    }
}

//

void initial() {
    printf("初始化文件\n");
    int i = 0;
    FILE *fp;
    fp = fopen("FILE_Student.txt", "r");
    if (fp == NULL) {
        printf("文件打开失败!\n");
        printf("初始化文件");
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
    printf("读取成功!\n");
}

void Save(struct Student stu[], int count) {
    FILE *fp;//定义文件结构体指针
    fopen_s(&fp, "FILE_Student.txt", "wb");//生成"FILE_Student.txt"文件
    if (fp == NULL) {
        printf("打开文件失败\n");
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
    }//将学生信息按表的格式输出到fp文件中
    fclose(fp);//关闭文件
    printf("学生数据保存成功。\n");
}

void Menu() {
    {
        printf("__________________________\n");
        printf("学生信息管理系统\n");
        printf("1、录入学生信息\n");
        printf("2、浏览学生信息\n");
        printf("3、查询学生信息\n");
        printf("4、删除学生信息\n");
        printf("5、修改学生信息\n");
        printf("6、汇总不及格学生信息\n");
        printf("7、统计优等生学生信息\n");
        printf("0、退出系统\n");
        printf("__________________________\n");
        printf("请选择（0-7）：");
    }
}

void Add(struct Student stu[]) {
    int i = 0;
    char choose;
    printf("请输入学生的信息：\n");
    do {
        i = count;
        printf("学号：");
        scanf_s("%s", &stu[i].num, 20);
        printf("名字：");
        scanf_s("%s", &stu[i].name, 20);
        printf("班级：");
        scanf_s("%s", &stu[i].classnum, 20);
        printf("年龄：");
        scanf_s("%d", &stu[i].age);
        printf("性别：");
        scanf_s("%s", &stu[i].sex, 20);
        printf("出生日期：");
        scanf_s("%s", &stu[i].date, 20);
        printf("电话：");
        scanf_s("%s", &stu[i].tele, 20);
        printf("地址：");
        scanf_s("%s", &stu[i].addr, 20);
        printf("课程数：");
        scanf_s("%d", &stu[i].course_sum);
        for (int j = 0; j < stu[i].course_sum; j++) {
            printf("第%d门课程成绩：", j + 1);
            scanf_s("%d", &stu[i].score[j]);
        }
        printf("是否继续？(Y/N)\n");
        getchar();//吸收回车
        scanf_s("%c", &choose, 1);
        count++;
    } while (choose == 'Y');
    //该算法可以实现循环地从控制台输入学生信息，无数量限制，
    //当输入完当前学生信息时，系统会提示是否继续输入，如继续输入，
    //输入Y，输入其他即表明不继续输入。
    printf("当前学生数量为%d\n", count);
    Save(p, count);//保存到文件中
}

void Show(struct Student stu[], int count) {
    printf("共有%d个学生信息\n", count);
    if (count == 0)//count表示录入的学生数
    {
        printf("******目前没有还信息******\n");
    } else {
        printf("学号\t姓名\t性别\t班级\t年龄\t日期\t电话\t地址\t各科成绩\n");
        for (int i = 0; i < count; i++) {
            printf("%s\t%s\t%s\t%s\t%d\t%s\t%s\t%s", stu[i].num, stu[i].name, stu[i].sex, stu[i].classnum, stu[i].age,
                   stu[i].date, stu[i].tele, stu[i].addr);
            for (int j = 0; j < stu[i].course_sum; j++) {
                printf(" \t%d", stu[i].score[j]);
            }
            printf("\n");
//            break;
        }
    }// \t为制表符 可以将输出的结果按照一定的间隔对齐
}


void Delete(struct Student stu[], int count) {
    char num[20];
    printf("请输入学生的学号：");
    scanf_s("%s", num, 20);
    num[19] = '\0';
    for (int i = 0; i < count; i++) {
        if (strcmp(num, stu[i].num) == 0) {
            for (int j = i; j < count - 1; j++) {
                stu[j] = stu[j + 1];
            }//从第j条信息开始，后面一个覆盖前面一个，即实现对第j条信息的删除
            count--;
            printf("该学生已删除\n");
            break;
        }
    }
    Save(stu, count);
}

void Modify(struct Student stu[], int count) {
    char num[20];
    printf("请选择你要修改的学生信息的学号：\n");
    scanf_s("%s", num, 20);
    num[19] = '\0';
    for (int i = 0; i < count; i++)//通过遍历结构体数组，比较学号信息，进而实现信息修改
    {
        if (strcmp(num, stu[i].num) == 0) {
            printf("请输入修改后的学号：");
            scanf_s("%s", &stu[i].num, 20);
            printf("请输入修改后的名字：");
            scanf_s("%s", &stu[i].name, 20);
            printf("请输入修改后的班级：");
            scanf_s("%s", &stu[i].classnum, 20);
            printf("请输入修改后的年龄：");
            scanf_s("%d", &stu[i].age);
            printf("请输入修改后的性别：");
            scanf_s("%s", &stu[i].sex, 20);
            printf("请输入修改后的出生日期：");
            scanf_s("%s", &stu[i].date, 20);
            printf("请输入修改后的电话：");
            scanf_s("%s", &stu[i].tele, 20);
            printf("请输入修改后的地址：");
            scanf_s("%s", &stu[i].addr, 20);
            printf("请输入修改后的课程数：");
            scanf_s("%d", &stu[i].course_sum);
            for (int j = 0; j < stu[i].course_sum; j++) {
                printf("请输入修改后的第%d门课程成绩：", j + 1);
                scanf_s("%d", &stu[i].score[j]);
            }
            printf("修改后的信息如下：\n");
            printf("学号\t姓名\t性别\t班级\t年龄\t日期\t电话\t地址\t各科成绩\n");
            printf("%s\t%s\t%s\t%s\t%d\t%s\t%s\t%s", stu[i].num, stu[i].name, stu[i].sex, stu[i].classnum, stu[i].age,
                   stu[i].date, stu[i].tele, stu[i].addr);
            for (int j = 0; j < stu[i].course_sum; j++) {
                printf(" \t%d", stu[i].score[j]);
            }
            printf("\n");
        }
    }
    Save(stu, count);//修改完成后对将其保存在文件中
}

void S_Menu() {
    int input = 0;
    printf("__________________________\n");
    printf("查询菜单\n");
    printf("1、按学号查询\n");
    printf("2、按班级查询\n");
    printf("3、按性别查询\n");
    printf("__________________________\n");
    printf("请选择（1-3）：");
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
            printf("输入错误");
            break;
    }
}

void Search_num(struct Student stu[], int count) {
    char num[20];
    int i;
    int find = 0;//定义find，0表示没找到，1表示找到
    printf("输入学生学号：\n");
    scanf_s("%s", &num, 20);
    printf("搜索结果如下：\n");
    for (i = 0; i < count; i++)//通过遍历结构体数组，比较学号信息，从而实现查找
    {
        if (strcmp(num, stu[i].num) == 0) {
            printf("学号\t姓名\t性别\t班级\t年龄\t日期\t电话\t地址\t各科成绩\n");
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
        printf("没有找到相关信息！\n");
    }
}

void Search_sex(struct Student stu[], int count) {
    char sex[20];
    int i;
    int find = 0;
    printf("输入性别：\n");
    scanf_s("%s", &sex, 20);
    printf("查询结果如下：\n");
    printf("学号\t姓名\t性别\t班级\t年龄\t日期\t电话\t地址\t各科成绩\n");
    for (i = 0; i < count; i++)//通过遍历结构体数组，比较性别信息，从而实现查找
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
        printf("没有找到相关信息！\n");
    }
}

void Search_class(struct Student stu[], int count) {
    char classnum[20];
    int i;
    int find = 0;
    printf("输入班级：\n");
    scanf_s("%s", &classnum, 20);
    printf("查询结果如下：\n");
    printf("学号\t姓名\t性别\t班级\t年龄\t日期\t电话\t地址\t各科成绩\n");
    for (i = 0; i < count; i++)//通过遍历结构体数组，比较班级信息，从而实现查找
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
        printf("没有找到相关信息！\n");
    }
}


void Show_fail(struct Student stu[], int count) {
    int flag = 0;//用flag标记在遍历数组过程中该学生是否不及格，不及格置1
    if (count == 0) {
        printf("******目前没有还信息********\n");
    } else {
        printf("学号\t姓名\t性别\t班级\t年龄\t日期\t电话\t地址\t各科成绩\n");//打印表头
        for (int i = 0; i < count; i++) {
            flag = 0;
            for (int j = 0; j < stu[i].course_sum; j++) {
                if (stu[i].score[j] < 60)
                    flag = 1;//单科小于60分即不及格
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

void Show_good(struct Student stu[], int count)//显示优等生信息
{
    FILE *fp;//定义文件结构体指针
    fopen_s(&fp, "Show_good.txt", "wb");//打开文件
    if (fp == NULL) {
        printf("can not open file\n");
        exit(0);
    }
    float ave[100];//定义一个ave数组用于存储每个学生的成绩平均值
    float sum = 0;
    for (int i = 0; i < count; i++) {
        sum = 0;
        for (int j = 0; j < stu[i].course_sum; j++) {
            sum = sum + stu[i].score[j];
        }
        ave[i] = sum / stu[i].course_sum;
    }//求每个学生的成绩平均值
    int flag = 0;
    for (int i = 0; i < count; i++) {
        flag = 0;
        if (ave[i] >= 80)//平均成绩大于80
            flag = 1;
        else if (ave[i] >= 60 && ave[i] < 80) {
            for (int j = 0; j < stu[i].course_sum; j++) {
                if (stu[i].score[j] >= 90)//平均成绩及格，单科成绩上90
                    flag = 1;
            }
        } else if (ave[i] < 60) {
            for (int j = 0; j < stu[i].course_sum; j++) {
                if (stu[i].score[j] == 100)//平均成绩不及格，但单科满分
                    flag = 1;
            }
        }//因为单科成绩条件的判断需要单独用循环来判断，无法将优等生的判断条件写在一个判断语句中
        //所以按照条件一一判断，先判断平均成绩，再判断单科成绩上90，再判断满分100，使用多个if else语句，满足任一一个条件，flag都置为1，即可以实现功能。
        if (flag == 1) {
            printf("学号\t姓名\t性别\t班级\t年龄\t日期\t电话\t地址\t各科成绩\n");
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
        }//打印出优等生学生信息，并且将其输出到fp文件
    }
    fclose(fp);
    printf("优等生数据保存成功。\n");
}//按优等生条件筛选出优等生的条目存入单独文件，并输出到屏幕

