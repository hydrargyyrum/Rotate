#include <iostream>
#include <vector>
#include <functional>

using namespace std;


class TEuler {
public:
	vector<vector<double>> Integrate(int t0, int tk, int dt, vector<double> x0, function<double(int, double)> f);
	vector<double> OneStep(vector<double> xi, double dt, function<double(int, double)> f);
};


vector<vector<double>> TEuler::Integrate(int t0, int tk, int dt, vector<double> x0, function<double(int, double)> f) {
	vector<vector<double>> matrix;
	matrix.push_back(x0);
	for (int t = t0; t <= tk; t += dt) {
		vector<double>& xi = matrix.back();
		vector<double> xip1 = OneStep(xi, dt, f);
		matrix.push_back(xip1);
	}
	return matrix;
}

vector<double> TEuler::OneStep(vector<double> xi, double dt, function<double(int, double)> f) {
	const int n = xi.size();
	vector<double> xip1(n);
	for (int i = 0; i < n; i++) {
		xip1[i] = xi[i] + f(i, dt) * dt;
	}
	return xip1;
}


double f(int i, double dt) {
	switch (i) {
	case 0:
		return i+1;
	case 1:
		return -i;
	default:
		return i + 3;
	}
}
vector<double> x0() {
	vector<double> x0{ 1,2,3 };
	return x0;
}



void eulerTest() {
	TEuler euler;
	auto matrix = euler.Integrate(0, 10, 1, x0(), f);
	for (int i = 0; i < matrix.size(); i++) {
		vector<double> vec = matrix[i];
		cout << "x[" << i << "] = { ";
		for (int j = 0; j < vec.size(); j++) {
			cout << vec[j] << " ";
		}
		cout << "}" << endl;
	}
	cin.get();
	cin.get();
}