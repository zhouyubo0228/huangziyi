#include <iostream>
using namespace std;
int main()
{
	int r, p;//��Դ������������
	bool is_security_all = true;//�ж��Ƿ���ڰ�ȫ����
	bool is_security_process = true;//�жϵ�ǰ�����Ƿ�ȫ
	bool is_test;//�жϵ�ǰ�����Ƿ��Ѿ������
	int process_test = 0;//�Ѿ������Ľ�����
	cout << "��������Դ��������������" << endl;
	cin >> r >> p;
	/*����һ��һά����������ŵ�ǰ������Դ��*/
	int* available = new int[r];
	/*����һ����ά�����������ÿ����������������Դ��*/
	int** max = new int* [p];
	for (int i = 0; i < p; i++)
		max[i] = new int[r];
	/*����һ����ά�����������ÿ�������ѷ������Դ��*/
	int** allocation = new int* [p];
	for (int i = 0; i < p; i++)
		allocation[i] = new int[r];
	/*����һ����ά�����������ÿ�������������Դ��*/
	int** need = new int* [p];
	for (int i = 0; i < p; i++)
		need[i] = new int[r];
	/*����һ��һά����������ŵ�ǰ��ȫ�����и�����Դ�ĸ���*/
	int* work = new int[r];
	/*����һ��һά��������¼��ȫ����*/
	int* path = new int[p];
	cout << "�������ѷ����ÿ�����̵ĸ�����Դ��" << endl;;
	for (int i = 0; i < p; i++)
		for (int j = 0; j < r; j++)
			cin >> allocation[i][j];
	cout << "������ÿ�������������������Դ��" << endl;;
	for (int i = 0; i < p; i++)
		for (int j = 0; j < r; j++)
			cin >> max[i][j];
	cout << "�����뵱ǰϵͳʣ��ĸ�����Դ��" << endl;
	for (int i = 0; i < r; i++)
		cin >> available[i];
	/*ÿ�������������Դ��*/
	for (int i = 0; i < p; i++)
		for (int j = 0; j < r; j++)
			need[i][j] = max[i][j] - allocation[i][j];
	/*����Ƿ���ڰ�ȫ����*/
	for (int i = 0; i < r; i++)//��ǰ��ȫ�����и�����Դ������
		work[i] = available[i];
	int iterator;//ÿ�μ��һ����ȫ���̵ĵ�������
	while (process_test < p && is_security_all == true)//���а�ȫ�����н��̻�δ������
	{
		for (iterator = 0; iterator < p; iterator++)//������һ�����̻�δ����⣬��ÿ�μ��һ����ȫ����
		{
			is_security_process = true;//���赱ǰ�����ǰ�ȫ��
			is_test = false;//���赱ǰ���̻�δ�����
			for (int j = 0; j < process_test; j++)//ȷ���Ƿ񱻼�����
				if (path[j] == iterator)
				{
					is_test = true;
					break;
				}
			if (is_test == false)//���δ������
			{

				for (int z = 0; z < r; z++)//��⵱ǰ�����Ƿ�ȫ
					if (need[iterator][z] > work[z])
					{
						is_security_process = false;
						break;
					}
				if (is_security_process == true)//�����ǰ���̰�ȫ��������밲ȫ������
				{
					path[process_test] = iterator;
					process_test++;
					for (int y = 0; y < r; y++)//���µ�ǰ���и�����Դ��workֵ
						work[y] += allocation[iterator][y];
					break;//�жϴ˴ΰ�ȫ���̼��
				}
			}
		}
		if (iterator == p && process_test < p)//������м����ϻ򲻴��ڰ�ȫ���̣�����is_security_all��ֵ
			is_security_all = false;
	}
	if (is_security_all)//���ڰ�ȫ����
	{
		cout << "���ڰ�ȫ���У�";
		for (int i = 0; i < p; i++)
			cout << path[i] + 1 << " ";
		cout << endl;
	}
	else
		cout << "�����ڰ�ȫ����" << endl;
}