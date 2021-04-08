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
    int readInt1, readInt2;             //����� � ������ ������� �������
    vector<pair<int, int>> segments;    //�������
    vector<int> solutionInd;            //������� ���������� ��������
    cin >> M;
    //���� ����� ���������, ����������
    while ((cin >> readInt1 >> readInt2) && !(readInt1 == 0 && readInt2 == 0)) {
        segments.push_back(make_pair(readInt1, readInt2));
    }

    //��������� �� ����� �������
    sort(segments.begin(), segments.end(), compare);
    //���� ��� ��������
    if (segments.empty()) {
        cout << "No solution" << endl;
        return 0;
    }

    int currEnd = 0;    //������� ���������� ����� (������ ����������)
    int segInd = 0;     //������� �������, ������� �� ���������
    int ansInd = -1;    //������ ������� �������, ������� ������ � �����
    int maxEnd = 0;     //������������ ������, ������� ���� � ������

    //���� ���� �������
    while (segInd < segments.size()) {
        //���� ���� ������� � ���� ������ ������� �� ����������� ������� ������ �����
        while (segInd < segments.size() && segments[segInd].first <= currEnd) {
            //���� �� ����� �������, ������� ����� ��������, �� ���������� ���
            if (segments[segInd].second > maxEnd) {
                maxEnd = segments[segInd].second;
                ansInd = segInd;
            }

            segInd++;
        }
        //���������� ������ ������� � ����� (��� ������)
        solutionInd.push_back(ansInd);
        currEnd = maxEnd;

        //�������� ������ � ������
        if (currEnd >= M || segments[segInd].first > currEnd)
            break;
    }
    if (solutionInd.empty() || currEnd < M) {
        cout << "No solution" << endl;
    }
    else {
        //����� ������
        cout << solutionInd.size() << " " << endl;
        for (int i = 0; i < solutionInd.size(); i++) {
            cout << segments[solutionInd[i]].first << " " << segments[solutionInd[i]].second << endl;
        }
    }

    return 0;
}
