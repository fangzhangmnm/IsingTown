#include "stdafx.h"
#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <string>
#include <random>
using namespace std;
class Ising {
	int _boundary;
	int _totalBui;
	int *_map,*_con;
	int _totalCon_double;
	mt19937 rndEng;
	int* _snap;
public:
	int size;
	int boundary;
	int maxD;
	int& map(int x, int y) { return _map[x*size + y]; }
	int totalCon() { return _totalCon_double / 2; }
	int totalBui() { return _totalBui; }
	Ising(int size,int maxD) :size(size),maxD(maxD) {
		_map = new int[size*size];
		memset(_map, 0, size*size * sizeof(int));
		_con = new int[size*size];
		memset(_con, 0, size*size * sizeof(int));
		_totalCon_double = 0;
		_totalBui = 0;
		_snap = new int[(2 * size*size + 2)];
		boundary = 0;
	}
	void snapshoot() {
		memcpy(_snap, _map, size*size * sizeof(int));
		memcpy(_snap+size*size, _con, size*size * sizeof(int));
		_snap[size*size * 2] = _totalCon_double;
		_snap[size*size * 2+1] = _totalBui;
	}
	void rollback() {
		memcpy(_map, _snap, size*size * sizeof(int));
		memcpy( _con,_snap + size * size, size*size * sizeof(int));
		_totalCon_double = _snap[size*size * 2];
		_totalBui = _snap[size*size * 2+1];
	}
	~Ising() {
		delete[]_map;
		delete[]_con;
		delete[]_snap;
	}
	template<class F>
	void bfs_var(int x0, int y0,int maxD,F f) {
		const int d[4][2] = { 0,1,0,-1,1,0,-1,0 };
		int* o = new int[size*size];
		memset(o, -1, size*size * sizeof(int));
		queue<pair<int, int> > q;
		q.push(make_pair(x0, y0));
		o[x0*size + y0] = 0;
		while (!q.empty()) {
			int x = q.front().first, y = q.front().second; q.pop();
			int di = o[x*size + y];
			int mi = _map[x*size + y];
			if (di > maxD)
				return;
			if (mi !=0) {
				f(x, y);
				if (di > 0)
					continue;
			}
			else if (di == 0)
				f(x, y);
			for (int i = 0; i < 4; ++i) {
				int x1 = x + d[i][0], y1 = y + d[i][1];
				if(x1>=0 && x1<size && y1>=0 && y1<size)
					if (o[x1*size + y1] == -1) {
						o[x1*size + y1] = di + 1;
						q.push(make_pair(x1, y1));
					}
			}
		}
		delete[]o;
	}
	void updateCon(int x,int y) {
		bfs_var(x, y, maxD,[&](int x,int y){
			int newCon = -1;
			bfs_var(x, y, maxD, [&](int x, int y) {
				newCon += 1;
			});
			if (_map[x*size + y] == 0)
				newCon = 0;
			_totalCon_double += newCon - _con[x*size+y];
			_con[x*size + y] = newCon;
		});
	}
	void printMap() {
		for (int i = 0; i < size; ++i) {
			for (int j = 0; j < size; ++j) {
				int mi= _map[i*size + j];
				if (mi == 0)cout << "□";
				if (mi > 0)cout << "■";
			}
			cout << endl;
		}
	}
	void printCon() {
		for (int i = 0; i < size; ++i) {
			for (int j = 0; j < size; ++j) {
				int ci = _con[i*size + j];
				int c0 = ci % 10; int c1 = (ci - c0) % 10;
				cout << c1 << c0;
			}
			cout << endl;
		}
	}
	template<class F>
	void isingStep(F f) {
		uniform_int_distribution<int> distr(0, size - 1);
		uniform_real_distribution<float> distr2(0.f, 1.f);
		int x = distr(rndEng), y = distr(rndEng);
		snapshoot();
		float oldE = f(totalCon(),totalBui());
		if (_map[x*size + y] == 0) {
			_map[x*size + y] = 1;
			_totalBui += 1;
		}
		else {
			_map[x*size + y] = 0;
			_totalBui -= 1;
		}
		updateCon(x, y);
		float newE = f(totalCon(), totalBui());
		if (distr2(rndEng) > exp((oldE - newE))) {
			rollback();
		}
	}
};


int main()
{
	cout << "size maxD:";
	int size, maxD;
	cin >> size >> maxD;
	Ising ising(size,maxD);
	while (1) {
		float beta1,beta2=0,sigma,sigmaa; int num,iter;
		cout << "beta1 sigma sigmaa num iter:";
		cin >> beta1 >>sigma>>sigmaa>>num>> iter;
		for (int i = 0; i < iter; ++i) {
			ising.isingStep([&](float con, float bui) {
				return con * beta1 + bui * beta2 + sigmaa * exp(-(bui - num)*(bui - num) / (2 * sigma*sigma));
			});
		}
		system("cls");
		ising.printMap();
		cout << ising.totalCon() << endl;
		cout << ising.totalBui() <<"/"<< ising.size*ising.size << endl;
	}

	system("pause");
    return 0;
}

