#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define M 50//学生总数
#define LEN sizeof(struct stu) //结构体长度LEN

void Input();//录入1
void show();//浏览2
void Search();//查询3
void Sort();//排序4
void change();//修改6
void del();//删除5
void menu();//菜单
int recor();//记录次数
void remenu();//返回菜单

FILE* fp;//文件指针

struct time
{
	int year;//年
	int month;//月
};
struct stu
{
	char num[20]; //学号
	char name[20]; //姓名

	int age; //年龄
	char sex[5]; //性别
	struct time birthday; //出生年月
	char add[50]; //地址
	unsigned  long long phone; //电话
	char E_mail[20]; //E - mail

}people[M];

void print(int i)
{

	printf("%7s", people[i].num);
	printf("%8s", people[i].name);
	printf("%6d", people[i].age);
	printf("%7s", people[i].sex);
	printf("\t%d年%d月", people[i].birthday.year, people[i].birthday.month);
	printf("%35s", people[i].add);
	printf("%20lld", people[i].phone);
	printf("%20s", people[i].E_mail);
	printf("\n");
}

void menu()//菜单
{
	system("cls");//清屏
	printf("\t\t\t\t|-----------------menu---------------------|\n");
	printf("\t\t\t\t|------------1.录入----2.浏览--------------|\n");
	printf("\t\t\t\t|------------3.查询----4.排序--------------|\n");
	printf("\t\t\t\t|------------5.删除----6.修改--------------|\n");
	printf("\t\t\t\t|---------------0.退出菜单-----------------|\n");
	printf("\t\t\t\t|------------------------------------------|\n");
	printf("\t\t\t\t|-------------点击进入(0-6)----------------|\n");
	int num;
	while (1)//选择功能
	{
		scanf_s("%d", &num);
		if (num == 0)
			printf("\t\t\t\t|---------------0.退出菜单-----------------|\n"), exit(0);//退出结束程序
		switch (num)/*1.录入2.修改 3.班级4.分析5.查询6.成绩*/
		{
		case 1:	Input();	break;//录入
		case 2:	show();		break;//浏览
		case 3:	Search();	break;//搜索
		case 4:	Sort(); 	break;//排序
		case 5:	del();		break;//删除
		case 6:	change();	break;//修改
		default: printf("请再0-6之间选择");
		}
	}
}

void remenu()//返回菜单
{
	char end[2];
	printf("----返回菜单按 Y 或者 y----\n ");   scanf("%s", end);
	if (strcmp(end, "y") == 0 || strcmp(end, "Y") == 0)
		system("cls"), menu();
	else printf("------结束程序-------"), exit(0);
}
int recor()//统计人数
{
	int m = 0;
	if ((fp = fopen("D:\\date", "ab+")) == NULL)//读写追加
		printf("\t\t\t\t不能打开\n"), exit(0);
	while (!feof(fp))//统计已录入人数  feof(fp)文件结束 返回值！=0
	{
		if (fread(&people[m], LEN, 1, fp) == 1)
			m++;
	}
	fclose(fp);
	return m;
}