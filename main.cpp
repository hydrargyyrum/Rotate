
#include <vector>
#include <iostream>

using namespace std;


class matrix {
private:
	vector<vector<double>> _matrix;

public:
	matrix(int n) {
		_matrix = vector<vector<double>>(n, vector<double>(n));
	}

	int size() const {
		return _matrix.size();
	}

	/*void print() {
		const matrix& m = *this;
		int n = m.size();
		cout << "====>" << endl;;
		for (int j = 0; j < n; j++) {
			for (int i = 0; i < n; i++) {
				cout << m.get(i, j) << " ";
			}
			cout << endl;
		}
	} */

	matrix operator*(const matrix& matrixAnother) {
		const matrix& m1 = *this;
		const matrix& m2 = matrixAnother;
		const int n = m1.size();
		matrix m3(n);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				double sum = 0;
				for (int k = 0; k < n; k++) {
					sum += m1.get(k, i) * m2.get(j, k);
				}
				m3.set(i, j, sum);
			}
		}
		return m3;
	}

	vector<double> operator*(const vector<double>& v) {
		matrix & m = *this;
		const int n = m.size();
		vector<double> vResult(n);
		for (int i = 0; i < n; i++) {
			double sum = 0;
			for (int j = 0; j < n; j++) {
				sum += m.get(i, j) * v[j];
			}
			vResult[i] = sum;
		}
		return vResult;
	}

	void set(int i, int j, double e) { _matrix[i][j] = e; }
	double get(int i, int j) const { return _matrix[i][j]; }


	static matrix identity(int n) {
		matrix m(n);
		for (int i = 0; i < n; i++) {
			m.set(i, i, 1);
		}
		return m;
	}
};

matrix matrixRotate(double a) {
	vector<double> v {
		cos(a), sin(a), -sin(a),
		-sin(a), cos(a), sin(a),
		sin(a), -sin(a), cos(a)
	};

	// translate vector to matrix
	matrix m(3);
	for (int k = 0; k < v.size(); k++) {
		int i = k % 3;
		int j = k / 3;
		m.set(i, j, v[k]);
	}
	return m;
}

vector<double> rotateCoord(int coordIdx, vector<double> v, double angle) {
	matrix e = matrix::identity(3);
	e.set(coordIdx, coordIdx, 0);
	matrix r = matrixRotate(angle);
	matrix tmp = e * r * e;
	tmp.set(coordIdx, coordIdx, 1);
	vector<double> result = tmp * v;
	return result;
}


vector<double> rotateX(vector<double> v, double angle) {
	return rotateCoord(0, v, angle);
}

vector<double> rotateY(vector<double> v, double angle) {
	return rotateCoord(1, v, angle);
}

vector<double> rotateZ(vector<double> v,  double angle) {
	return rotateCoord(2, v, angle);
}


void printVec(vector<double> x) {
	cout << "=====> vec" << endl;
	for (int i = 0; i < x.size(); i++) {
		cout << x[i] << " ";
	}
	cout << endl;
}


int main()
{
	vector<double> v{ 1, 1, 1 };
	double angle = 6.28;
	//double angle = 0;
	//printVec(rotateX(v, angle));
	//printVec(rotateY(v, angle));
	printVec(rotateZ(rotateY(v, angle), angle));
	cin.get();
	cin.get();
}