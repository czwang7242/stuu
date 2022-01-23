#include <iostream>
#include <string.h>
#include <malloc.h>
#include <fstream>
#include <sstream>
#include <windows.h>
using namespace std;

//学生数据
typedef struct StuSql
{
	char name[30];	   //姓名
	char sex[20];	   //性别
	char province[30]; //省份
	int number;		   //学号
	double score;	   //成绩
	int year;		   //年份
	int month;		   //月份
	int day;		   //日期
	struct StuSql *link;
} STUDENT;

//导入
void load() //导入动画
{
	cout << "正在导入中...";
	Sleep(800);
	printf("\33[2K\r还有3s...");
	Sleep(800);
	printf("\33[2K\r还有2s...");
	Sleep(800);
	printf("\33[2K\r还有1s...");
	Sleep(800);
	printf("\33[2K\rdata.txt导入成功！\n");
	cout << endl;
}
STUDENT *init_stu()
{
	STUDENT *h = (STUDENT *)malloc(sizeof(STUDENT)); //定义头结点
	STUDENT *p = h;									 //指向头结点
	string temp;
	string etc[2];

	ifstream myfile("data.txt");
	getline(myfile, etc[0]);
	getline(myfile, etc[1]); //把前两行读走
	while (myfile.good())
	{
		STUDENT *line = (STUDENT *)malloc(sizeof(STUDENT));
		myfile >> line->number;
		myfile >> line->name;
		myfile >> line->sex;
		myfile >> line->province;
		myfile >> temp; //源文件是字符串要切割后转成int
		line->year = atoi(temp.substr(0, 4).c_str());
		line->month = atoi(temp.substr(5, 2).c_str());
		line->day = atoi(temp.substr(8, 2).c_str());
		myfile >> line->score;
		line->link = NULL; //创造新节点
		p->link = line;	   // p起粘合剂的作用，把h和数据块链接起来
		p = p->link;
	}
	myfile.close();
	return h;
}

//帮助
void help()
{
	cout << "---------------------------------------------------------------------------------\n"
		 << "load data.txt\n"
		 << "从当前目录装入文件data.txt,并显示\n\n"
		 << "sort grade\n"
		 << "按“成绩”排序，并显示\n"
		 << "类似地，还可以是学号sort number,姓名sort name,性别sort sex,省份sort province,出生年月日sort birthday\n\n"
		 << "select number name\n"
		 << "只显示学号，姓名两列，显示的列还可以其他任意\n\n"
		 << "select number name where grade>60\n"
		 << "只显示学号，姓名两列，只包含成绩> 60的行\n\n"
		 << "select * where age>21 sex=male\n"
		 << "显示所有列，只包含年龄>21且性别=男的行\n"
		 << "其它的组合，从上边类推\n\n"
		 << "exit\n"
		 << "退出程序\n"
		 << "---------------------------------------------------------------------------------\n"
		 << endl;
}

// sort输出
void sort_out(STUDENT *pStu)
{
	STUDENT *p = pStu;
	while (p->link)
	{
		p = p->link;
		cout << p->number << "    ";
		cout << p->name << "	";
		cout << p->sex << "	";
		cout << p->province << "	";
		cout << p->year << "-" << p->month << "-" << p->day << "	";
		cout << p->score << endl;
	}
	cout << endl;
}

//冒泡的元素交换
void Func(STUDENT *p)
{
	STUDENT *temp;
	temp = (STUDENT *)malloc(sizeof(STUDENT));

	strcpy(temp->name, p->name);
	strcpy(p->name, p->link->name);
	strcpy(p->link->name, temp->name);
	temp->number = p->number;
	p->number = p->link->number;
	p->link->number = temp->number;
	temp->score = p->score;
	p->score = p->link->score;
	p->link->score = temp->score;
	temp->year = p->year;
	temp->month = p->month;
	temp->day = p->day;
	p->year = p->link->year;
	p->month = p->link->month;
	p->day = p->link->day;
	p->link->year = temp->year;
	p->link->month = temp->month;
	p->link->day = temp->day;
	strcpy(temp->province, p->province);
	strcpy(p->province, p->link->province);
	strcpy(p->link->province, temp->province);
	strcpy(temp->sex, p->sex);
	strcpy(p->sex, p->link->sex);
	strcpy(p->link->sex, temp->sex);
}

//排序
void pFunc_1(STUDENT *pStu, int n) //名字排序
{
	STUDENT *p;
	p = pStu; //这个pStu实际上是h头结点

	for (int j = 1; j < n; j++) //冒泡排序
	{
		p = pStu->link; //每次冒泡过程完毕后，必须返回结点1
		for (int i = n - 1; i >= j; i--)
		{
			if (strcmp(p->name, p->link->name) > 0) //注意这里需要注明>0，不能直接写表达式
			{
				Func(p);
			}
			p = p->link;
		}
	}

	sort_out(pStu);
}
void pFunc_2(STUDENT *pStu, int n) //学号排序
{
	STUDENT *p;
	p = pStu;

	for (int j = 1; j < n; j++)
	{
		p = pStu->link;
		for (int i = n - 1; i >= j; i--)
		{
			if ((p->number) > (p->link->number))
			{
				Func(p);
			}
			p = p->link;
		}
	}

	sort_out(pStu);
}
void pFunc_3(STUDENT *pStu, int n) //分数排序
{
	STUDENT *p;
	p = pStu;

	for (int j = 1; j < n; j++)
	{
		p = pStu->link;
		for (int i = n - 1; i >= j; i--)
		{
			if ((p->score) > (p->link->score))
			{
				Func(p);
			}
			p = p->link;
		}
	}

	sort_out(pStu);
}
void pFunc_4(STUDENT *pStu, int n) //生日排序
{
	STUDENT *p;
	p = pStu;

	for (int j = 1; j < n; j++)
	{
		p = pStu->link;
		for (int i = n - 1; i >= j; i--)
		{
			if ((p->year) > (p->link->year))
			{
				Func(p);
			}
			if ((p->year) == (p->link->year) && (p->month) > (p->link->month))
			{
				Func(p);
			}
			if ((p->year) == (p->link->year) && (p->month) == (p->link->month) && (p->day) > (p->link->day))
			{
				Func(p);
			}
			p = p->link;
		}
	}

	sort_out(pStu);
}
void pFunc_5(STUDENT *pStu, int n) //省份排序
{
	STUDENT *p;
	p = pStu;

	for (int j = 1; j < n; j++)
	{
		p = pStu->link;
		for (int i = n - 1; i >= j; i--)
		{
			if (strcmp(p->province, p->link->province) > 0)
			{
				Func(p);
			}
			p = p->link;
		}
	}

	sort_out(pStu);
}
void pFunc_6(STUDENT *pStu, int n) //性别排序
{
	STUDENT *p;
	p = pStu;

	for (int j = 1; j < n; j++)
	{
		p = pStu->link;
		for (int i = n - 1; i >= j; i--)
		{
			if (strcmp(p->sex, p->link->sex) > 0)
			{
				Func(p);
			}
			p = p->link;
		}
	}

	sort_out(pStu);
}

//为了同时返回数组及其长度
typedef struct Array
{
	int length;
	int array[7];
} arr;

//求交集
arr join(arr a, arr b)
{
	arr c;
	int i, j, k = 0;

	if (b.length == 0)
	{
		return a;
	}
	if (a.length == 0 && b.length != 0)
	{
		return b;
	}

	for (i = 0; i < a.length; i++)
	{
		for (j = 0; j < b.length; j++)
		{
			if (a.array[i] == b.array[j])
			{
				c.array[k] = a.array[i];
				k++;
			}
		}
	}
	c.length = k;
	return c;
}

// select输出
void select(int flag[], string str[][6], arr W)
{
	static int snum = 0;
	int i = 1, j = 1, k = 0;
	for (i = 1; i < 10; i++)
	{
		if (flag[i] != 0)
		{
			snum++;
		}
		else
		{
			break;
		}
	}
	for (k = 0; k < W.length; k++)
	{
		for (j = 1; j < snum + 1; j++)
		{
			cout << str[W.array[k]][flag[j] - 1] << "	";
		}
		cout << endl;
	}
	cout << endl;
}

//清空string数组op
inline void restring(string op[])
{
	for (int i = 0; i < 20; i++)
	{
		string().swap(op[i]);
	}
}

//导入文件前判断用户的输入
void ojudge(string op[])
{
	if (op[0].compare("help") == 0)
	{
		if (op[1].compare("") == 0)
		{
			help();
		}
		else
		{
			cout << "请正确输入命令！" << endl;
		}
	}
	else if (op[0].compare("load") == 0 && op[1].compare("data.txt") == 0 && op[2].compare("") == 0)
	{
		if (op[1].compare("data.txt") == 0 && op[2].compare("") == 0)
		{
			load();
		}
		else
		{
			cout << "请正确输入命令！" << endl;
		}
	}
	else if (op[0].compare("exit") == 0)
	{
		if (op[1].compare("") == 0)
		{
			exit(0);
		}
		else
		{
			cout << "请正确输入命令！" << endl;
		}
	}
	else
	{
		cout << "请先正确导入文件！" << endl;
	}
}

//计算年龄
int AGE(int Y, int M, int D)
{
	SYSTEMTIME timenow;
	GetLocalTime(&timenow); //获取系统时间
	int NY = timenow.wYear, NM = timenow.wMonth, ND = timenow.wDay;

	if (Y < NY)
	{
		if (M < NM || (M == NM && D < ND))
		{
			return NY - Y - 1;
		}
		else if (M > NM || (M == NM && D >= ND))
		{
			return NY - Y;
		}
	}
	else
	{
		cout << "Error!" << endl;
	}
	return 0;
}

//处理用户的输入
void pan(string op[], STUDENT *pStu, int n)
{
	int flag[10] = {0}; //标志显示哪一列
	int xuehao;			//用户输入的学号
	int age;			//用户输入的年龄
	float fenshu;		//用户输入的分数
	arr A;				//标志显示哪一行性别
	arr B;				//标志显示哪一行分数
	arr C;				//标志显示哪一行学号
	arr D;				//标志显示哪一行生日

	//存data.txt的数据,供select使用
	string str[7][6];
	string etc[2];
	ifstream myfile("data.txt");
	getline(myfile, etc[0]);
	getline(myfile, etc[1]);
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 6; j++)
			myfile >> str[i][j];
	}
	myfile.close();

	//识别sort
	if (op[0].compare("sort") == 0)
	{
		if (op[1].compare("name") == 0)
		{
			pFunc_1(pStu, n);
		}
		else if (op[1].compare("number") == 0)
		{
			pFunc_2(pStu, n);
		}
		else if (op[1].compare("score") == 0)
		{
			pFunc_3(pStu, n);
		}
		else if (op[1].compare("birthday") == 0)
		{
			pFunc_4(pStu, n);
		}
		else if (op[1].compare("province") == 0)
		{
			pFunc_5(pStu, n);
		}
		else if (op[1].compare("sex") == 0)
		{
			pFunc_6(pStu, n);
		}
		else
		{
			cout << "请正确输入命令！" << endl;
		}
	}
	//识别select
	else if (op[0].compare("select") == 0 && op[1] != "")
	{
		for (int i = 1; i < 10; i++) //从op[0]开始遍历op数组
		{
			if (op[i].compare("name") == 0)
			{
				flag[i] = 2;
			}
			if (op[i].compare("number") == 0)
			{
				flag[i] = 1;
			}
			if (op[i].compare("sex") == 0)
			{
				flag[i] = 3;
			}
			if (op[i].compare("province") == 0)
			{
				flag[i] = 4;
			}
			if (op[i].compare("score") == 0)
			{
				flag[i] = 6;
			}
			if (op[i].compare("birthday") == 0)
			{
				flag[i] = 5;
			}
			if (op[i].compare("*") == 0)
			{
				flag[1] = 1;
				flag[2] = 2;
				flag[3] = 3;
				flag[4] = 4;
				flag[5] = 5;
				flag[6] = 6;
				break;
			}
		}
		for (int i = 2; i < 10; i++) //从op[2]开始遍历，提高一点效率
		{
			if (op[i].compare("where") == 0)
			{
				int j = 0;
				for (j = i + 1; j < 10; j++) //从找到where的地方后开始遍历
				{
					if (op[j].substr(0, 4).compare("sex=") == 0)
					{
						n = 0;
						if (op[j].substr(4, 6).compare("male") == 0)
						{
							for (int m = 0; m < 7; m++)
							{
								if (str[m][2].compare("男") == 0)
								{
									A.array[A.length] = m;
									A.length++;
								}
							}
						}
						else if (op[j].substr(4, 6).compare("female") == 0)
						{
							for (int m = 0; m < 7; m++)
							{
								if (str[m][2].compare("女") == 0)
								{
									A.array[A.length] = m;
									A.length++;
								}
							}
						}
						else
						{
							cout << "请正确输入命令！";
						}
					}
					if (op[j].substr(0, 5).compare("score") == 0)
					{
						n = 0;
						fenshu = atof(op[j].substr(6, 6).c_str());
						if ((op[j])[5] == 60)
						{
							for (int m = 0; m < 7; m++)
							{
								if (atoi(str[m][5].c_str()) < fenshu)
								{
									B.array[B.length] = m;
									B.length++;
								}
							}
						}
						else if ((op[j])[5] == 61)
						{
							for (int m = 0; m < 7; m++)
							{
								if (atoi(str[m][5].c_str()) == fenshu)
								{
									B.array[B.length] = m;
									B.length++;
								}
							}
						}
						else if ((op[j])[5] == 62)
						{
							for (int m = 0; m < 7; m++)
							{
								if (atoi(str[m][5].c_str()) > fenshu)
								{
									B.array[B.length] = m;
									B.length++;
								}
							}
						}
						else
						{
							cout << "请正确输入命令！";
						}
					}
					if (op[j].substr(0, 6).compare("number") == 0)
					{
						n = 0;
						xuehao = atoi(op[j].substr(7, 4).c_str());
						if ((op[j])[6] == 60)
						{
							for (int m = 0; m < 7; m++)
							{
								if (atoi(str[m][0].c_str()) < xuehao)
								{
									C.array[C.length] = m;
									C.length++;
								}
							}
						}
						else if ((op[j])[6] == 61)
						{
							for (int m = 0; m < 7; m++)
							{
								if (atoi(str[m][0].c_str()) == xuehao)
								{
									C.array[C.length] = m;
									C.length++;
								}
							}
						}
						else if ((op[j])[6] == 62)
						{
							for (int m = 0; m < 7; m++)
							{
								if (atoi(str[m][0].c_str()) > xuehao)
								{
									C.array[C.length] = m;
									C.length++;
								}
							}
						}
						else
						{
							cout << "请正确输入命令！";
						}
					}
					if (op[j].substr(0, 3).compare("age") == 0)
					{
						n = 0;
						age = atoi(op[j].substr(4, 2).c_str());
						if ((op[j])[3] == 60)
						{
							for (int m = 0; m < 7; m++)
							{
								if (AGE(atoi(str[m][4].substr(0, 4).c_str()), atoi(str[m][4].substr(5, 2).c_str()), atoi(str[m][4].substr(8, 2).c_str()) < age))
								{
									D.array[D.length] = m;
									D.length++;
								}
							}
						}
						else if ((op[j])[3] == 61)
						{
							for (int m = 0; m < 7; m++)
							{
								if (AGE(atoi(str[m][4].substr(0, 4).c_str()), atoi(str[m][4].substr(5, 2).c_str()), atoi(str[m][4].substr(8, 2).c_str()) == age))
								{
									D.array[D.length] = m;
									D.length++;
								}
							}
						}
						else if ((op[j])[3] == 62)
						{
							for (int m = 0; m < 7; m++)
							{
								if (AGE(atoi(str[m][4].substr(0, 4).c_str()), atoi(str[m][4].substr(5, 2).c_str()), atoi(str[m][4].substr(8, 2).c_str()) > age))
								{
									D.array[D.length] = m;
									D.length++;
								}
							}
						}
						else
						{
							cout << "请正确输入命令！";
						}
					}
				}
			}
		}
		arr W = join(A, join(B, join(C, D))); // ABCD的交集
		select(flag, str, W);
	}
	//识别help
	else if (op[0].compare("help") == 0)
	{
		help();
	}
	//识别exit
	else if (op[0].compare("exit") == 0)
	{
		exit(0);
	}
	//输入错误
	else
	{
		cout << "请正确输入命令！" << endl;
	}
}

int main()
{
	int n = 7;	   //一共7个学生
	string op[20]; //用户输入的命令
	int i = 0;	   //遍历op的辅助
	char sf;	   //吃空格，吃换行
	STUDENT *h;	   //头结点

	h = init_stu();

	//输入load命令前
	while (1)
	{
		cout << "请输入命令(输入help显示帮助信息) : " << endl;
		do
		{
			cin >> op[i];
			scanf("%c", &sf);
			i++;
		} while (sf != '\n');
		ojudge(op);
		if (op[0].compare("load") == 0 && op[1].compare("data.txt") == 0 && op[2].compare("") == 0)
		{
			break;
		}
		i = 0;
		restring(op);
	}

	//输入load后
	while (1)
	{
		i = 0;
		restring(op);
		cout << "请输入命令(输入help显示帮助信息) : " << endl;
		do
		{
			cin >> op[i];
			scanf("%c", &sf);
			i++;
		} while (sf != '\n');
		pan(op, h, n);
	}
	return 0;
}
