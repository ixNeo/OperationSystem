#include <iostream>
#include <algorithm>
#include <ctime>
#include <deque>
#include <iterator>
#include <iomanip>

// 操作系统的三个页面置换算法
using namespace std;

const int store = 4;
const int sum_visit = 20;
const int seed = 2256460;

bool find_e(deque<int> d, int e) {

	deque<int>::iterator t;
	for (t = d.begin(); t != d.end();t++) {
		if (*t == e)
			return true;
		else
			continue;
	}
	
	if (t == d.end())
		return false;
}

int FIFO() {

	int cnt = 0;
	int tmp = store;
	deque<int> d;
	int visit[sum_visit];

	srand(seed);
	
	cout << "the visit array is " << endl;
	for (int i = 0; i < sum_visit; i++) {
		visit[i] = rand() % 7;
		cout << setw(6) << visit[i];
	}
	cout << endl;
	//cout << "*****************" << endl;
		

	for (int i = 0; i < sum_visit; i++) {

		if (find_e(d, visit[i])) {
			cout << "visited and aleadly existed : " << visit[i] << endl;
			cnt++;
			//cout << "***************" << endl;
		}
		else if (tmp > 0 && !find_e(d,visit[i]) ){
			d.push_back(visit[i]);
			tmp--;
			cout << "visit and will push: " << visit[i] << endl;
		}
		else {
			deque<int>::iterator t=d.begin();
			int exist = *t;
			d.pop_front();
			d.push_back(visit[i]);
			cout << "visit: " << visit[i] << "  and alter : " << exist << endl;
			//cout << "***************" << endl;
		}
	}
	return cnt;
	
}


int get_index(int visit[],int e) {
	for (int i = 0; i < sum_visit; i++) {
		if (visit[i] == e)
			return i;
	}

}

bool find_ea(int d[], int e) {
	int i = 0;
	for (i = 0; i < store;i++) {
		if (d[i] == e)
			return true;
		else
			continue;
	}

	if (i == store)
		return false;
}

int LRU() {
	int cnt = 0;
	int m[store];
	int order[store];
	for (int i = 0; i < store; i++) {
		m[i] = -1;
		order[i] = -1;
	}
	int tmp = store;
	int visit[sum_visit];
	
	srand(seed);
	cout << "the visit array is " << endl;
	for (int i = 0; i < sum_visit; i++) {
		visit[i] = rand() % 7;
		cout << setw(6) << visit[i];
	}
	cout << endl;

	int i = 0;
	tmp = store;

	int sum = 3;
	for (i = 0; i < sum_visit; i++) {

		for (int i = 0; i < store; i++) {
			order[i] = -1;
		}
		for (int i = 0; i < store; i++) {
			cout << m[i];
		}
		if (tmp > 0 && !find_ea(m, visit[i])){			
			m[store-tmp] = visit[i];
			tmp--;
			cout << "visit and will push: " << visit[i] << endl;
		}
		else if (find_ea(m, visit[i])) {
			cout << "visited and aleadly existed : " << visit[i] << endl;
			cnt++;
		}
		else {
			int s = 0;
			int f = 1;
			for(int k=i-1;k>=0 && f;k--)
				for (int j = 0;  (j<store) && f; j++) {
					if (order[j] == 1)
						continue;
					if (visit[k] == m[j]) {
						if (s != store-1) {
							order[j] = 1;
							s++;
							break;
						}							
						cout << "visit: " << visit[i] << "  and alter : " << m[j] << endl;
						m[j] = visit[i];
						f = 0; 
					}
				}
		}
	}
	return cnt;
}

int OPT() {
	int cnt = 0;
	int m[store];
	int order[store];
	for (int i = 0; i < store; i++) {
		m[i] = -1;
		order[i] = -1;
	}
	int tmp = store;
	int visit[sum_visit];

	srand(seed);
	cout << "the visit array is " << endl;
	for (int i = 0; i < sum_visit; i++) {
		visit[i] = rand() % 7;
		cout << setw(6) << visit[i];
	}
	cout << endl;

	int i = 0;
	tmp = store;

	int sum = 3;
	for (i = 0; i < sum_visit; i++) {

		for (int i = 0; i < store; i++) {
			order[i] = -1;
		}
		for (int i = 0; i < store; i++) {
			cout << m[i];
		}
		if (tmp > 0 && !find_ea(m, visit[i])) {
			m[store - tmp] = visit[i];
			tmp--;
			cout << "visit and will push: " << visit[i] << endl;
		}
		else if (find_ea(m, visit[i])) {
			cout << "visited and aleadly existed : " << visit[i] << endl;
			cnt++;
		}
		else {
			int s = 0;
			int f = 1;
			int times[store];
			int maxindex = 0;
			for (int i = 0; i < store; i++)
				times[i] = -1;
			int j = 0;
			for (int k = i + 1; k < sum_visit && f; k++)
				for (j = 0; (j<store) && f; j++) {
					if (order[j] == 1)
						continue;
					if (visit[k] == m[j]) {
						times[maxindex] = j;
						maxindex++;
						order[j] = 1;	
						if (maxindex == 3)
							f = 0;						
					}						
				}
			if (maxindex == 0) 
				j = rand() % store;
			else
				j = times[maxindex - 1];
			cout << "visit: " << visit[i] << "  and alter : " << m[j] << endl;
			m[j] = visit[i];
			
		}		
	}
	return cnt;
}


int main() {

	cout << "shot" << 1.0*FIFO()/sum_visit << endl;
	cout << "********************" << endl;

	cout << "shot" << 1.0*LRU()/sum_visit << endl;
	
	cout << "********************" << endl;
	cout << "shot" << 1.0*OPT()/sum_visit << endl;
	
	return 0;
}