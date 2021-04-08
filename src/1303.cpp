#include <cstdio>
#include <climits>
#include <cstdlib>
#include <algorithm>
#include <list>
#include <vector>
#include <iostream>

using namespace std;

bool compare(const pair<int, int>& left, const pair<int, int>& right) {
    return left.first <= right.first;
}

int main() {
    int M;
    int readInt1, readInt2;             //левая и правая граница отрезка
    vector<pair<int, int>> segments;    //отрезки
    vector<int> solutionInd;            //индексы правильных отрезков
    cin >> M;
    //пока можем считывать, записываем
    while ((cin >> readInt1 >> readInt2) && !(readInt1 == 0 && readInt2 == 0)) {
        segments.push_back(make_pair(readInt1, readInt2));
    }

    //сортируем по левой границе
    sort(segments.begin(), segments.end(), compare);
    //если нет отрезков
    if (segments.empty()) {
        cout << "No solution" << endl;
        return 0;
    }

    int currEnd = 0; 	//текущая координата конца (правой координаты)
	int segInd = 0; 	//текущий сегмент, который мы проверяем
	int ansInd = -1; 	//индекс лучшего отрезка, который пойдет в ответ
	int maxEnd = 0; 	//Максимальная длинна, которая есть у ответа

    //пока есть отрезки
    while (segInd < segments.size()) {
        //пока есть отрезки и пока начало отрезка не превосходит текущую правую точку
        while (segInd < segments.size() && segments[segInd].first <= currEnd) {
            //если мы нашли отрезок, который лучше подходит, то записываем его
            if (segments[segInd].second > maxEnd) {
                maxEnd = segments[segInd].second;
                ansInd = segInd;
            }

            segInd++;
        }
        //записываем лучший отрезок в ответ (его индекс)
        solutionInd.push_back(ansInd);
        currEnd = maxEnd;

        //проверка предел и разрыв
        if (currEnd >= M || segments[segInd].first > currEnd)
            break;
    }
    if (solutionInd.empty() || currEnd < M) {
        cout << "No solution" << endl;
    }
    else {
        //вывод ответа
        cout << solutionInd.size() << " " << endl;
        for (int i = 0; i < solutionInd.size(); i++) {
            cout << segments[solutionInd[i]].first << " " << segments[solutionInd[i]].second << endl;
        }
    }

    return 0;
}
