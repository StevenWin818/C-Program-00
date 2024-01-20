#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4244)
#pragma warning(disable:4477)
typedef struct
{
    char  num[20];//ѧ��
    char  name[20];//����
    int   absences;//����
    float homeworks[9];//�Ŵοκ���ҵ
    float ave;//�κ���ҵƽ����
    float project;//����ҵ����
    float exam;//��ĩ���Է���
    float total;//ѧ�������ɼ�
}Stu;

Stu stu[100]; // ���������100��ѧ��
int stu_count = 0; // ��ǰ��ѧ������

void save()
{
    FILE* file;
    errno_t err = fopen_s(&file, "stu.txt", "w");
    if (err != 0 || file == NULL) {
        printf("�޷����ļ�\n");
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
        printf("ѧ�������Ѵ�����\n");
        return;
    }

    printf("������ѧ����ѧ�ţ�");
    scanf_s("%s", stu[stu_count].num, sizeof(stu[stu_count].num));

    printf("������ѧ����������");
    scanf_s("%s", stu[stu_count].name, sizeof(stu[stu_count].name));

    // ��ʼ��������Ϣ
    stu[stu_count].absences = 0;
    for (int i = 0; i < 9; i++) {
        stu[stu_count].homeworks[i] = 0.0;
    }
    stu[stu_count].ave = 0.0;
    stu[stu_count].project = 0.0;
    stu[stu_count].exam = 0.0;
    stu[stu_count].total = 0.0;

    stu_count++;

    printf("ѧ����Ϣ�ѳɹ����\n");
}

void input()
{
    char x[20];
    int in = -1;
    printf("������ѧ����ѧ�Ż�������");
    scanf_s("%s", x, sizeof(x));

    // ���Ҹ�ѧ��
    for (int i = 0; i < stu_count; i++) {
        if ((strcmp(stu[i].num, x) == 0) || (strcmp(stu[i].name, x) == 0))
        {
            in = i;
            break;
        }
    }

    if (in == -1) {
        printf("δ�ҵ���ѧ��\n");
        return;
    }

    printf("��������δ�����");
    scanf_s("%d", &stu[in].absences);

    printf("������Ŵοκ���ҵ�ɼ������ƽ���֣�");
    float sum = 0.0;
    for (int i = 0; i < 9; i++) {
        scanf_s("%f", &stu[in].homeworks[i]);
        sum += stu[in].homeworks[i];
    }
    stu[in].ave = sum / 9.0;

    printf("���������ҵ�ɼ���");
    scanf_s("%f", &stu[in].project);

    printf("��������ĩ���Գɼ���");
    scanf_s("%f", &stu[in].exam);

    // ���������ɼ�
    stu[in].total = stu[in].ave * 0.15 + stu[in].project * 0.15 + stu[in].exam * 0.7;

    printf("ѧ����Ϣ�ѳɹ�¼��\n");
}

void search()
{
    char x[20];
    int in = -1;
    printf("������ѧ����ѧ�Ż�������");
    scanf_s("%s", x, sizeof(x));

    // ���Ҹ�ѧ��
    for (int i = 0; i < stu_count; i++) {
        if ((strcmp(stu[i].num, x) == 0) || (strcmp(stu[i].name, x) == 0))
        {
            in = i;
            break;
        }
    }

    if (in == -1) {
        printf("δ�ҵ���ѧ��\n");
    }
    else {
        printf("ѧ�ţ�%s\n", stu[in].num);
        printf("������%s\n", stu[in].name);
        printf("���δ�����%d\n", stu[in].absences);
        printf("�κ���ҵ�ɼ���");
        for (int i = 0; i < 9; i++)
            printf("%.1f ", stu[in].homeworks[i]);
        printf("\n");
        printf("�κ���ҵƽ���֣�%.1f\n", stu[in].ave);
        printf("����ҵ�ɼ���%.1f\n", stu[in].project);
        printf("��ĩ���Գɼ���%.1f\n", stu[in].exam);
        printf("�����ɼ���%.1f\n", stu[in].total);
    }
}

void rectify()
{
    char x[20];
    int in = -1;
    printf("������ѧ����ѧ�Ż�������");
    scanf_s("%s", x, sizeof(x));
    // ���Ҹ�ѧ��
    for (int i = 0; i < stu_count; i++) {
        if ((strcmp(stu[i].num, x) == 0)|| (strcmp(stu[i].name, x) == 0)) 
        {
                in = i;
                break;
        }
    }
    
   
    if (in == -1) {
        printf("δ�ҵ���ѧ��\n");
    }
    else {
        printf("��ѡ��Ҫ�޸ĵ���Ϣ��\n");
        printf("1.���δ���\n2.�κ���ҵ�ɼ�\n3.����ҵ�ɼ�\n4.��ĩ���Գɼ�\n");
        int info_choice;
        scanf_s("%d", &info_choice);
        float sum = 0.0; // ��sum�ĸ�ֵ�ƶ�������
        switch (info_choice) {
        case 1:
            printf("�������µĿ��δ�����");
            scanf_s("%d", &stu[in].absences);
            break;
        case 2:
            printf("������Ҫ�޸���һ�εĿκ���ҵ�ɼ���1-9����");
            int hw_num;
            scanf_s("%d", &hw_num);
            if (hw_num < 1 || hw_num > 9) {
                printf("��������ȷѡ��(1-9)\n");
                return;
            }
            printf("�������µĵ�%d�οκ���ҵ�ɼ���", hw_num);
            scanf_s("%f", &stu[in].homeworks[hw_num - 1]);

            
            for (int i = 0; i < 9; i++) {
                sum += stu[in].homeworks[i];
            }
            stu[in].ave = sum / 9.0;
            break;
        case 3:
            printf("�������µĴ���ҵ�ɼ���");
            scanf_s("%f", &stu[in].project);
            break;
        case 4:
            printf("�������µ���ĩ���Գɼ���");
            scanf_s("%f", &stu[in].exam);
            break;
        default:
            printf("��������ȷѡ��(1-4)\n");
            return;
        }
        // ���������ɼ�
        stu[in].total = stu[in].ave * 0.15 + stu[in].project * 0.15 + stu[in].exam * 0.7;

        printf("ѧ����Ϣ�ѳɹ��޸�\n");
    }
}
void print_all()
{
    if (stu_count == 0) {
        printf("û��ѧ����Ϣ\n");
        return;
    }

    for (int i = 0; i < stu_count; i++) {
        printf("ѧ�ţ�%s\n", stu[i].num);
        printf("������%s\n", stu[i].name);
        printf("���δ�����%d\n", stu[i].absences);
        printf("�κ���ҵ�ɼ���");
        for (int j = 0; j < 9; j++)
            printf("%.1f ", stu[i].homeworks[j]);
        printf("\n");
        printf("�κ���ҵƽ���֣�%.1f\n", stu[i].ave);
        printf("����ҵ�ɼ���%.1f\n", stu[i].project);
        printf("��ĩ���Գɼ���%.1f\n", stu[i].exam);
        printf("�����ɼ���%.1f\n", stu[i].total);
        printf("--------------------\n");
    }
}

void delete_stu()
{
    char x[20];
    int in = -1;
    printf("������ѧ����ѧ�Ż�������");
    scanf_s("%s", x, sizeof(x));

    // ���Ҹ�ѧ��
    for (int i = 0; i < stu_count; i++) {
        if ((strcmp(stu[i].num, x) == 0) || (strcmp(stu[i].name, x) == 0))
        {
            in = i;
            break;
        }
    }

    if (in == -1) {
        printf("δ�ҵ���ѧ��\n");
    }
    else {
        printf("��ȷ��Ҫɾ��ѧ��Ϊ%s������Ϊ%s��ѧ����(1ȷ�ϣ�2ȡ��)\n", stu[in].num, stu[in].name);
        int confirm_choice;
        scanf_s("%d", &confirm_choice);

        if (confirm_choice == 1) {
            // ɾ����ѧ��
            for (int i = in; i < stu_count - 1; i++) 
                stu[i] = stu[i + 1];
            stu_count--;
            printf("ѧ����Ϣ�ѳɹ�ɾ��\n");
        }
        else if (confirm_choice == 2) {
            printf("��ȡ��ɾ��\n");
        }
        else {
            printf("��������ȷѡ��(1-2)\n");
        }
    }
}

void menu()
{
    printf("\t|----------ѧ���ɼ�����ϵͳ---------|\n");
    printf("\t| 1.���ѧ��                        |\n");
    printf("\t| 2.¼����Ϣ                        |\n");
    printf("\t| 3.����ѧ��                        |\n");
    printf("\t| 4.�޸�����                        |\n");
    printf("\t| 5.��ӡ��Ϣ                        |\n");
    printf("\t| 6.ɾ��ѧ��                        |\n");
    printf("\t| 7.�˳�����                        |\n");
    printf("\t| ������ѡ��1-7����               |\n");
    printf("\t|-----------------------------------|\n\t");
}

int main()
{
    int sel;
    // ��������ʱ�Զ�����ѧ����Ϣ
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
            break; // �˳�����
        else
            printf("��������ȷѡ��(1-7)\n");
        // ÿһ��������Զ�����ѧ����Ϣ
        save();
        system("pause");
        system("cls");
    }
    return 0;
}