#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4244)
#pragma warning(disable:4477)
typedef struct
{
    char  num[20];//学号
    char  name[20];//姓名
    int   absences;//旷课
    float homeworks[9];//九次课后作业
    float ave;//课后作业平均分
    float project;//大作业分数
    float exam;//期末考试分数
    float total;//学生总评成绩
}Stu;

Stu stu[100]; // 假设最多有100个学生
int stu_count = 0; // 当前的学生数量

void save()
{
    FILE* file;
    errno_t err = fopen_s(&file, "stu.txt", "w");
    if (err != 0 || file == NULL) {
        printf("无法打开文件\n");
        return;
    }

    for (int i = 0; i < stu_count; i++) {
        fprintf(file, "%s %s %d ", stu[i].num, stu[i].name, stu[i].absences);
        for (int j = 0; j < 9; j++) {
            fprintf(file, "%.1f ", stu[i].homeworks[j]);
        }
        fprintf(file, "%.1f %.1f %.1f %.1f\n", stu[i].ave, stu[i].project, stu[i].exam, stu[i].total);
    }

    fclose(file);
}

void load()
{
    FILE* file;
    errno_t err = fopen_s(&file, "stu.txt", "r");
    if (err != 0 || file == NULL)
        return;

    stu_count = 0;

    while (fscanf_s(file, "%s %s %d", stu[stu_count].num, sizeof(stu[stu_count].num), stu[stu_count].name, sizeof(stu[stu_count].name), &stu[stu_count].absences) != EOF) {
        for (int j = 0; j < 9; j++)
            fscanf_s(file, "%f", &stu[stu_count].homeworks[j]);
        fscanf_s(file, "%f %f %f %f\n", &stu[stu_count].ave, &stu[stu_count].project, &stu[stu_count].exam, &stu[stu_count].total);

        stu_count++;

        if (stu_count >= 100) {
            break;
        }
    }

    fclose(file);
}


void add()
{
    if (stu_count >= 100) {
        printf("学生数量已达上限\n");
        return;
    }

    printf("请输入学生的学号：");
    scanf_s("%s", stu[stu_count].num, sizeof(stu[stu_count].num));

    printf("请输入学生的姓名：");
    scanf_s("%s", stu[stu_count].name, sizeof(stu[stu_count].name));

    // 初始化其他信息
    stu[stu_count].absences = 0;
    for (int i = 0; i < 9; i++) {
        stu[stu_count].homeworks[i] = 0.0;
    }
    stu[stu_count].ave = 0.0;
    stu[stu_count].project = 0.0;
    stu[stu_count].exam = 0.0;
    stu[stu_count].total = 0.0;

    stu_count++;

    printf("学生信息已成功添加\n");
}

void input()
{
    char x[20];
    int in = -1;
    printf("请输入学生的学号或姓名：");
    scanf_s("%s", x, sizeof(x));

    // 查找该学生
    for (int i = 0; i < stu_count; i++) {
        if ((strcmp(stu[i].num, x) == 0) || (strcmp(stu[i].name, x) == 0))
        {
            in = i;
            break;
        }
    }

    if (in == -1) {
        printf("未找到该学生\n");
        return;
    }

    printf("请输入旷课次数：");
    scanf_s("%d", &stu[in].absences);

    printf("请输入九次课后作业成绩并求出平均分：");
    float sum = 0.0;
    for (int i = 0; i < 9; i++) {
        scanf_s("%f", &stu[in].homeworks[i]);
        sum += stu[in].homeworks[i];
    }
    stu[in].ave = sum / 9.0;

    printf("请输入大作业成绩：");
    scanf_s("%f", &stu[in].project);

    printf("请输入期末考试成绩：");
    scanf_s("%f", &stu[in].exam);

    // 计算总评成绩
    stu[in].total = stu[in].ave * 0.15 + stu[in].project * 0.15 + stu[in].exam * 0.7;

    printf("学生信息已成功录入\n");
}

void search()
{
    char x[20];
    int in = -1;
    printf("请输入学生的学号或姓名：");
    scanf_s("%s", x, sizeof(x));

    // 查找该学生
    for (int i = 0; i < stu_count; i++) {
        if ((strcmp(stu[i].num, x) == 0) || (strcmp(stu[i].name, x) == 0))
        {
            in = i;
            break;
        }
    }

    if (in == -1) {
        printf("未找到该学生\n");
    }
    else {
        printf("学号：%s\n", stu[in].num);
        printf("姓名：%s\n", stu[in].name);
        printf("旷课次数：%d\n", stu[in].absences);
        printf("课后作业成绩：");
        for (int i = 0; i < 9; i++)
            printf("%.1f ", stu[in].homeworks[i]);
        printf("\n");
        printf("课后作业平均分：%.1f\n", stu[in].ave);
        printf("大作业成绩：%.1f\n", stu[in].project);
        printf("期末考试成绩：%.1f\n", stu[in].exam);
        printf("总评成绩：%.1f\n", stu[in].total);
    }
}

void rectify()
{
    char x[20];
    int in = -1;
    printf("请输入学生的学号或姓名：");
    scanf_s("%s", x, sizeof(x));
    // 查找该学生
    for (int i = 0; i < stu_count; i++) {
        if ((strcmp(stu[i].num, x) == 0)|| (strcmp(stu[i].name, x) == 0)) 
        {
                in = i;
                break;
        }
    }
    
   
    if (in == -1) {
        printf("未找到该学生\n");
    }
    else {
        printf("请选择要修改的信息：\n");
        printf("1.旷课次数\n2.课后作业成绩\n3.大作业成绩\n4.期末考试成绩\n");
        int info_choice;
        scanf_s("%d", &info_choice);
        float sum = 0.0; // 将sum的赋值移动到这里
        switch (info_choice) {
        case 1:
            printf("请输入新的旷课次数：");
            scanf_s("%d", &stu[in].absences);
            break;
        case 2:
            printf("请输入要修改哪一次的课后作业成绩（1-9）：");
            int hw_num;
            scanf_s("%d", &hw_num);
            if (hw_num < 1 || hw_num > 9) {
                printf("请输入正确选项(1-9)\n");
                return;
            }
            printf("请输入新的第%d次课后作业成绩：", hw_num);
            scanf_s("%f", &stu[in].homeworks[hw_num - 1]);

            
            for (int i = 0; i < 9; i++) {
                sum += stu[in].homeworks[i];
            }
            stu[in].ave = sum / 9.0;
            break;
        case 3:
            printf("请输入新的大作业成绩：");
            scanf_s("%f", &stu[in].project);
            break;
        case 4:
            printf("请输入新的期末考试成绩：");
            scanf_s("%f", &stu[in].exam);
            break;
        default:
            printf("请输入正确选项(1-4)\n");
            return;
        }
        // 计算总评成绩
        stu[in].total = stu[in].ave * 0.15 + stu[in].project * 0.15 + stu[in].exam * 0.7;

        printf("学生信息已成功修改\n");
    }
}
void print_all()
{
    if (stu_count == 0) {
        printf("没有学生信息\n");
        return;
    }

    for (int i = 0; i < stu_count; i++) {
        printf("学号：%s\n", stu[i].num);
        printf("姓名：%s\n", stu[i].name);
        printf("旷课次数：%d\n", stu[i].absences);
        printf("课后作业成绩：");
        for (int j = 0; j < 9; j++)
            printf("%.1f ", stu[i].homeworks[j]);
        printf("\n");
        printf("课后作业平均分：%.1f\n", stu[i].ave);
        printf("大作业成绩：%.1f\n", stu[i].project);
        printf("期末考试成绩：%.1f\n", stu[i].exam);
        printf("总评成绩：%.1f\n", stu[i].total);
        printf("--------------------\n");
    }
}

void delete_stu()
{
    char x[20];
    int in = -1;
    printf("请输入学生的学号或姓名：");
    scanf_s("%s", x, sizeof(x));

    // 查找该学生
    for (int i = 0; i < stu_count; i++) {
        if ((strcmp(stu[i].num, x) == 0) || (strcmp(stu[i].name, x) == 0))
        {
            in = i;
            break;
        }
    }

    if (in == -1) {
        printf("未找到该学生\n");
    }
    else {
        printf("你确定要删除学号为%s，姓名为%s的学生吗？(1确认，2取消)\n", stu[in].num, stu[in].name);
        int confirm_choice;
        scanf_s("%d", &confirm_choice);

        if (confirm_choice == 1) {
            // 删除该学生
            for (int i = in; i < stu_count - 1; i++) 
                stu[i] = stu[i + 1];
            stu_count--;
            printf("学生信息已成功删除\n");
        }
        else if (confirm_choice == 2) {
            printf("已取消删除\n");
        }
        else {
            printf("请输入正确选项(1-2)\n");
        }
    }
}

void menu()
{
    printf("\t|----------学生成绩管理系统---------|\n");
    printf("\t| 1.添加学生                        |\n");
    printf("\t| 2.录入信息                        |\n");
    printf("\t| 3.查找学生                        |\n");
    printf("\t| 4.修改其信                        |\n");
    printf("\t| 5.打印信息                        |\n");
    printf("\t| 6.删除学生                        |\n");
    printf("\t| 7.退出程序                        |\n");
    printf("\t| 请输入选择（1-7）：               |\n");
    printf("\t|-----------------------------------|\n\t");
}

int main()
{
    int sel;
    // 程序启动时自动加载学生信息
    load();
    while (1)
    {
        menu();
        scanf_s("%d", &sel);
        if (sel == 1)
            add();
        else if (sel == 2)
            input();
        else if (sel == 3)
            search();
        else if (sel == 4)
            rectify();
        else if (sel == 5)
            print_all();
        else if (sel == 6)
            delete_stu();
        else if (sel == 7)
            break; // 退出程序
        else
            printf("请输入正确选项(1-7)\n");
        // 每一项操作后自动保存学生信息
        save();
        system("pause");
        system("cls");
    }
    return 0;
}