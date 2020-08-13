#include"tou.h"

void main()//主函数
{
	menu();
}

void Input()//录入学生信息  1功能
{
	system("cls");//清屏
	int m, i, count;//录入人数
	char join[2];//确定录入
	printf("本次需录入： 人\n");
	scanf("%d", &count);//录入count次
	for (i = 0; i < count; i++)
	{
		printf("确定录入请按 Y 或者 y\n ");
		scanf("%s", join);
		if (strcmp(join, "y") == 0 || strcmp(join, "Y") == 0)
		{
			printf("请输入:学号 姓名\n");
			scanf("%s", people[i].num);
			scanf("%s", people[i].name);
			printf("请输入:年龄 性别\n");
			scanf("%d", &people[i].age);  scanf("%s", people[i].sex);
			printf("请输入:出生年 月\n");
			scanf("%d", &people[i].birthday.year);  scanf("%d", &people[i].birthday.month);
			printf("请输入:地址 电话 邮箱\n");
			scanf("%s", people[i].add);  scanf("%lld", &people[i].phone);
			scanf("%s", people[i].E_mail);
			if ((fp = fopen("D:\\date", "ab")) == NULL)//读写追加
				printf("\t\t\t\t----不能打开----\n"), exit(0);
			if (fwrite(&people[i], LEN, 1, fp) == 1)
				printf("----录入成功----\n");//文件录入信息
			fclose(fp);
			recor();
		}
	}
	count = recor();
	printf("----已记录学生总数%d----\n", count);
	remenu();//返回菜单
}

void show()//功能2 浏览
{
	char join[2];
	system("cls");//清屏
	int i, count;
	count = recor();
	printf("\n");
	if ((fp = fopen("D:\\date", "rb")) == NULL)//读取文件
		printf("\t\t\t\t不能打开\n"), exit(0);
	printf("学号\t  姓名\t 年龄\t性别\t出生年 月\t\t地址\t\t\t\t电话\t\t邮箱\n");
	for (i = 0; i < count; i++)
	{
		fread(&people[i], LEN, 1, fp);
		print(i);
	}
	fclose(fp);
	remenu();
}

void Search()//功能3 搜索
{
	system("cls");//清屏
	char name3[20], num6[20];
	int count, i,n;
	count = recor();//统计已录入人数
	printf("----已记录学生总数%d----\n", count);
	printf("----1.按学号查找----\n----2.按名字查找----\n");
	scanf("%d", &n);
	switch (n)//选择查找
	{
	case 1:	printf("-----请输入学号-----\n"), scanf("%s", num6); break;//按学号 功能3-1
	case 2:	printf("-----请输入名字-----\n"), scanf("%s", name3);	break;//按名字3.2
	}
	if ((fp = fopen("D:\\date", "rb")) == NULL)//读取文件
		printf("\t\t\t\t不能打开\n"), exit(0);
	for (i = 0; i < count; i++)
	{
		if (strcmp(people[i].num, num6) == 0 || strcmp(people[i].name, name3) == 0)//输出
		{
			printf("学号\t姓名\t年龄\t性别\t\t出生年 月\t\t地址\t\t\t电话\t\t邮箱\n");
			print(i); break;
		}
	}
	if (i == count)printf("-----未记录该学生信息-----\n");
	fclose(fp);
	remenu();//返回菜单
}

void Sort()//排序 功能4
{
	system("cls");//清屏
	struct stu t[M];//交换结构体信息
	int i, j, count;
	count = recor();//统计
	for (i = 0; i < count - 1; i++)//冒泡法
	{
		for (j = 0; j < count - i - 1; j++)
		{
			if (strcmp(people[j].num, people[j + 1].num) > 0)
			{
				t[0] = people[j + 1];
				people[j + 1] = people[j];
				people[j] = t[0];
			}
		}
	}
	if ((fp = fopen("D:\\date", "wb")) == NULL)//只写
		printf("\t\t\t\t不能打开\n"), exit(0);
	for (j = 0; j < count; j++)//录入
		if (fwrite(&people[j], LEN, 1, fp) != 1)//fwrite返回值  size count
			printf("出错\n");
	fclose(fp);
	show();//功能2
}

void del() //功能5 删除 
{
	system("cls");//清屏
	int c, men;//删除人数
	int x, i, j;//选择，循环条件
	char name2[20], join[2], num2[20];
	int count;
	count = recor();//统计
	printf("-----1.学号\n-----2.姓名\n");
	scanf("%d", &x);
	printf("删除人数：\n");
	scanf("%d", &men);
	for (c = 0; c < men; c++)
	{
		switch (x)
		{
		case 1:printf("请输入待删除学生的学号："), scanf("%s", num2); break;
		case 2:	printf("请输入待删除学生的姓名："), scanf("%s", name2); break;												 break;
		default:printf("请在1-2选择");
		}
		for (i = 0; i < count; i++)
		{
			if (strcmp(people[i].num, num2) == 0 || strcmp(people[i].name, name2) == 0)
			{
				printf("学号\t  姓名\t年龄\t性别\t\t出生年 月\t\t地址\t\t\t\t电话\t\t邮箱\n");
				print(i); break;
			}
		}
		if (i == count)printf("-----未记录该学号-----\n");
		else
		{
			printf("----确定删除按 Y/y ----\n");
			scanf("%s", join);
			if (strcmp(join, "y") == 0 || strcmp(join, "Y") == 0)
			{
				for (j = i; j < count; j++, i++)
				{
					people[j] = people[i + 1];
				}//把后一个人移前1位
				count--;//统计-1
				printf("--------删除成功--------\n");
				printf("----已记录学生总数% d----\n", count);
				if ((fp = fopen("D:\\date", "wb")) == NULL)//只写
					printf("\t\t\t\t不能打开\n"), exit(0);
				for (j = 0; j < count; j++)//录入
					if (fwrite(&people[j], LEN, 1, fp) != 1)//fwrite返回值  size count
						printf("出错\n");
			}
		}
		fclose(fp);
	}remenu();//返回菜单
}

void change() //功能6 修改
{
	system("cls");//清屏
	char name6[20], in[2], num6[20];
	int k, date_1, j, i, count;
	count = recor();//统计
	printf("请输入修改学生： 1.学号 2.姓名:\n");
	scanf("%d", &j);//选择输入信息
	switch (j)
	{
	case 1:printf("学生学号:"), scanf("%s", num6); break;
	case 2:printf("学生姓名:"), scanf("%s", name6); break;
	default:printf("请在1-2之间选择\n");
	}
	for (i = 0; i < count; i++)//显示要修改的学生信息
	{
		if (strcmp(people[i].name, name6) == 0 || strcmp(people[i].num, num6) == 0)
		{
			printf("学号\t  姓名\t 年龄\t性别\t出生年 月\t\t地址\t\t\t\t电话\t\t邮箱\n");
			print(i); break;
		}
	}
	if (i == count)
	{
		printf("----未录入该学生信息\n----按Y/y返回菜单\n");
		scanf("%s", in);
		if (strcmp(in, "y") == 0 || strcmp(in, "Y") == 0)
			menu();
		else
			exit(0);
	}
	else
	{
		printf("|-----选择修改信息----|\n"); printf("|-----0.返回菜单-----|\n");
		printf("|----1.学号-2.姓名----|\n"); printf("|----3.年龄-4.性别----|\n");
		printf("|----5.生日-6.地址----|\n"); printf("|----7.电话-8.邮箱----|\n");
		scanf("%d", &date_1);
		switch (date_1)//选择修改信息
		{
		case 0: menu(); break;//返回菜单
		case 1:	printf("请输入:学号 \n"), scanf("%s", people[i].num);		break;
		case 2:	printf("请输入: 姓名\n"), scanf("%s", people[i].name);		break;
		case 3:	printf("请输入:年龄\n"), scanf("%d", &people[i].age);		break;
		case 4:	printf("请输入:性别\n"), scanf("%s", people[i].sex);			break;
		case 5:	printf("请输入:生日\n"),
			scanf("%d", &people[i].birthday.year),
			scanf("%d", &people[i].birthday.month); 	break;
		case 6:	printf("请输入:地址\n"), scanf("%s", people[i].add);			break;
		case 7:	printf("请输入:电话\n"), scanf("%lld", &people[i].phone);	break;
		case 8:	printf("请输入:邮箱\n"), scanf("%s", people[i].E_mail);		break;
		default: printf("请再0-8之间选择");
		}
		printf("----修改成功----\n");
		if ((fp = fopen("D:\\date", "wb")) == NULL)//只写
			printf("\t\t\t\t不能打开\n"), exit(0);
		for (j = 0; j < count; j++)//录入
			if (fwrite(&people[j], LEN, 1, fp) != 1)//fwrite返回值  size count
				printf("出错\n");
		fclose(fp);
		remenu();//返回菜单
	}
}