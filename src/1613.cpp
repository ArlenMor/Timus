#include <string>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <iostream>

using namespace std;

//структура, описывающая i-ый город
struct city
{
	int value;
	int number;
};



bool comp(city l, city r)
{
	//сначала проверяем не равное ли количество людей перевезли два города за год
	if (l.value == r.value)
	{
		return l.number < r.number; //сортируем по возрастанию номера города
	}
	return l.value < r.value;		//сортируем по кол-ву перевезенных людей
}

ostream& operator << (ostream& stream, city& a)
{
	stream << a.number << " " << a.value;
	return stream;
}

//функция обработки запроса
bool Query(int l, int r, int x, vector<city> &input_city, city *arr)
{
	//проверка на то, что мы ищем конкретный город
	if (l == r && arr[l - 1].value == x)
	{
		return true;
	}
	
	//находим нижнюю границу для пары (x, l)
	int Left = lower_bound(input_city.begin(), input_city.end(), city({ x , l }), comp) - input_city.begin();
	//cout << "Left is: " << Left << endl;
	//cout << "Left: " << (*lower_bound(input_city.begin(), input_city.end(), city({ x , l }), comp)) << endl;
	//cout << "Right : " << (*upper_bound(input_city.begin(), input_city.end(), city({ x , r }), comp)) << endl;
	
	//находим верхнюю границу для пары (x, r)
	int Right = upper_bound(input_city.begin(), input_city.end(), city({ x , r }), comp) - input_city.begin();
	/*cout << "Right is: " << Right << endl;*/

	//return true;
	//return Left < Right;
	return Left == Right ? false : true;
}



int main()
{
	vector<city> d;		//вектор городов
	vector<bool> ans;	//вектор ответов

	int n;
	cin >> n;

	

	city *arr = new city[n];	//вспомогательный массив

	for (int i = 1; i <= n; i++)
	{
		int x;
		cin >> x;
		d.push_back({ x, i }); //положить в список город, город с параметрами value = x, number = i
		arr[i - 1].value = x;
		arr[i - 1].number = i;
	}

	int q;
	cin >> q;
	int l, r, x;
	//сортирую массив по возрастанию городов
	
	sort(d.begin(), d.end(), comp);

	//пока запросы не завершились
	while (q--)
	{
		cin >> l >> r >> x;
		//записываю результат выполнения функции Query в вектор ответов
		ans.push_back(Query(l, r, x, d, arr)); 
	}


	//вывожу ответ
	for (int item : ans)
		cout << item;
	return 0;
}