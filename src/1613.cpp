#include <string>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <iostream>

using namespace std;

//���������, ����������� i-�� �����
struct city
{
	int value;
	int number;
};


//��� ���������� ����������
//�� �������� � ��������
//false - ������ �������
//true - ������ ������� �� ����
bool comp(city l, city r)
{
	//������� ��������� �� ������ �� ���������� ����� ��������� ��� ������ �� ���
	if (l.value == r.value)
	{
		return l.number < r.number; //��������� �� ����������� ������ ������
	}
	return l.value < r.value;		//��������� �� ���-�� ������������ �����
}

ostream& operator << (ostream& stream, city& a)
{
	stream << a.number << " " << a.value;
	return stream;
}

//������� ��������� �������
bool Query(int l, int r, int x, vector<city> &input_city, city *arr)
{
	//�������� �� ��, ��� �� ���� ���������� �����
	if (l == r && arr[l - 1].value == x)
	{
		return true;
	}
	
	//������� ������ ������� ��� ���� (x, l)
	int Left = lower_bound(input_city.begin(), input_city.end(), city({ x , l }), comp) - input_city.begin();
	//cout << "Left is: " << Left << endl;
	//cout << "Left: " << (*lower_bound(input_city.begin(), input_city.end(), city({ x , l }), comp)) << endl;
	//cout << "Right : " << (*upper_bound(input_city.begin(), input_city.end(), city({ x , r }), comp)) << endl;
	
	//������� ������� ������� ��� ���� (x, r)
	int Right = upper_bound(input_city.begin(), input_city.end(), city({ x , r }), comp) - input_city.begin();
	/*cout << "Right is: " << Right << endl;*/

	//return true;
	//return Left < Right;
	return Left == Right ? false : true;
}



int main()
{
	vector<city> d;		//������ �������
	vector<bool> ans;	//������ �������

	int n;
	cin >> n;

	

	city *arr = new city[n];	//��������������� ������

	for (int i = 1; i <= n; i++)
	{
		int x;
		cin >> x;
		d.push_back({ x, i }); //�������� � ������ �����, ����� � ����������� value = x, number = i
		arr[i - 1].value = x;
		arr[i - 1].number = i;
	}

	int q;
	cin >> q;
	int l, r, x;
	//�������� ������ �� ����������� �������
	
	sort(d.begin(), d.end(), comp);

	//���� ������� �� �����������
	while (q--)
	{
		cin >> l >> r >> x;
		//��������� ��������� ���������� ������� Query � ������ �������
		ans.push_back(Query(l, r, x, d, arr)); 
	}


	//������ �����
	for (int item : ans)
		cout << item;
	return 0;
}