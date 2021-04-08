#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	long long n;
	unsigned long long digits[10];

	cin >> n;


	//два частных случая
	if (0 == n)
	{
		cout << 10;
		return 0;
	}

	if (1 == n)
	{
		cout << 1;
		return 0;
	}

	//начинаемм со старших цифр, потому что нужно найти минимальное число
	//соответственно, идем от больших к меньшим
	for (int i = 9; i > 1; --i)
	{
		digits[i] = 0;
		while (n % i == 0) //если нашли такую цифру, которая делится нацело
		{
			n = n / i;
			digits[i]++; //записываем его
		}
	}

	//если мы нашли число, то выводим его
	if (n == 1)
	{
		for (int i = 2; i <= 9; ++i)
			while (digits[i])
			{
				digits[i]--;
				cout << i;
			}
	}
	//иначе -1
	else
		cout << -1;

	return 0;
}