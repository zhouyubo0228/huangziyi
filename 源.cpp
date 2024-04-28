#include <iostream>
using namespace std;
int main()
{
	int r, p;//资源总数、进程数
	bool is_security_all = true;//判断是否存在安全进程
	bool is_security_process = true;//判断当前进程是否安全
	bool is_test;//判断当前进程是否已经被检测
	int process_test = 0;//已经被检测的进程数
	cout << "请输入资源总数、进程数：" << endl;
	cin >> r >> p;
	/*定义一个一维数组用来存放当前可用资源数*/
	int* available = new int[r];
	/*定义一个二维数组用来存放每个进程所需得最大资源数*/
	int** max = new int* [p];
	for (int i = 0; i < p; i++)
		max[i] = new int[r];
	/*定义一个二维数组用来存放每个进程已分配的资源数*/
	int** allocation = new int* [p];
	for (int i = 0; i < p; i++)
		allocation[i] = new int[r];
	/*定义一个二维数组用来存放每个进程需求的资源数*/
	int** need = new int* [p];
	for (int i = 0; i < p; i++)
		need[i] = new int[r];
	/*定义一个一维数组用来存放当前安全序列中各种资源的个数*/
	int* work = new int[r];
	/*定义一个一维数组来记录安全序列*/
	int* path = new int[p];
	cout << "请输入已分配给每个进程的各种资源数" << endl;;
	for (int i = 0; i < p; i++)
		for (int j = 0; j < r; j++)
			cin >> allocation[i][j];
	cout << "请输入每个进程所需的最大各种资源数" << endl;;
	for (int i = 0; i < p; i++)
		for (int j = 0; j < r; j++)
			cin >> max[i][j];
	cout << "请输入当前系统剩余的各种资源数" << endl;
	for (int i = 0; i < r; i++)
		cin >> available[i];
	/*每个进程需求的资源数*/
	for (int i = 0; i < p; i++)
		for (int j = 0; j < r; j++)
			need[i][j] = max[i][j] - allocation[i][j];
	/*检测是否存在安全序列*/
	for (int i = 0; i < r; i++)//当前安全序列中各种资源的总数
		work[i] = available[i];
	int iterator;//每次检测一个安全进程的迭代变量
	while (process_test < p && is_security_all == true)//序列安全且所有进程还未检测完毕
	{
		for (iterator = 0; iterator < p; iterator++)//查找哪一个进程还未被检测，且每次检测一个安全进程
		{
			is_security_process = true;//假设当前进程是安全的
			is_test = false;//假设当前进程还未被检测
			for (int j = 0; j < process_test; j++)//确认是否被检测过了
				if (path[j] == iterator)
				{
					is_test = true;
					break;
				}
			if (is_test == false)//如果未被检测过
			{

				for (int z = 0; z < r; z++)//检测当前进程是否安全
					if (need[iterator][z] > work[z])
					{
						is_security_process = false;
						break;
					}
				if (is_security_process == true)//如果当前进程安全，将其加入安全序列中
				{
					path[process_test] = iterator;
					process_test++;
					for (int y = 0; y < r; y++)//更新当前序列各种资源的work值
						work[y] += allocation[iterator][y];
					break;//中断此次安全进程检测
				}
			}
		}
		if (iterator == p && process_test < p)//如果序列检测完毕或不存在安全进程，更新is_security_all的值
			is_security_all = false;
	}
	if (is_security_all)//存在安全序列
	{
		cout << "存在安全序列：";
		for (int i = 0; i < p; i++)
			cout << path[i] + 1 << " ";
		cout << endl;
	}
	else
		cout << "不存在安全序列" << endl;
}