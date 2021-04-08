#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Otr {
    int start;
    int finish;
};

struct Path {
    Otr otr;
    Path* next;
};

struct Answer {
    int count; //количество отрезков
    Path* path;
};

bool compare(Otr& first, Otr& second) {
    if (first.start < second.start) return true;
    if (first.start == second.start) return first.finish < second.finish;
    return false;
}

int main() {
    int n; cin >> n;
    auto otrs = vector<Otr>(n);
    //вектор, хранящий в себе значение ответов для отрезка, который заканчивается в этой точке
    auto answer = vector<Answer>(1999);
    for (int i = 0; i < n; i++) {
        cin >> otrs[i].start >> otrs[i].finish;
        if (otrs[i].start > otrs[i].finish) {
            swap(otrs[i].start, otrs[i].finish);
        }

        //для удобства работы с индексами
        otrs[i].start += 999;
        otrs[i].finish += 999;
        answer[i].count = 0;
        answer[i].path = NULL;
    }


    sort(otrs.begin(), otrs.end(), compare);

    for (auto otr : otrs) {
        //текущий лучший ответ
        Answer maxAnswer = answer[otr.start];

        //Для кождого отрезка проходим все ячейки от 0 до начала
        //находим там лучший ответ, который у нас уже есть

        for (int i = otr.start - 1; i >= 0; i--) {
            if (maxAnswer.count < answer[i].count) {
                maxAnswer = answer[i];
            }
        }

        //в ответ для точки конца отрезка кладём новый ответ, в который кладём новый путь
        //новый путь = старый путь(последовательность отрезков) + новый отрезок +
        // + указатель на этот отрезок + count++;
        
        Path* newPath = new Path;
        newPath->next = maxAnswer.path;
        newPath->otr = otr;

        answer[otr.finish].path = newPath;
        answer[otr.finish].count = maxAnswer.count + 1;
    } 

    //находим лучший ответ
    Answer maxAnswer = answer[1998];
    for (int i = 0; i < 1998; i++) {
        if (maxAnswer.count < answer[i].count) {
            maxAnswer = answer[i];
        }
    }

    //проходим односязный список в обратном порядке
    Otr* otrList = new Otr[maxAnswer.count];
    Path* iterablePath = maxAnswer.path;
    int lastIndex = maxAnswer.count - 1;
    while (iterablePath) {
        otrList[lastIndex] = iterablePath->otr;
        iterablePath = iterablePath->next;
        lastIndex--;
    }

    //выводим ответ на экран
    cout << maxAnswer.count << endl;
    for (int i = 0; i < maxAnswer.count; i++) {
        cout << otrList[i].start - 999 << ' ' << otrList[i].finish - 999 << endl;
    }
    return 0;
}