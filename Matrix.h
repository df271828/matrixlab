#include <bits/stdc++.h>
using namespace std;

const double EPS = 1E-9;
class Matrix{

protected:
    vector<vector<double>> matrix;
    int n;
    int m;
public:
    Matrix (){
        matrix.resize(1, vector<double> (1, 0));
    }


    Matrix (int a, int b){
        if (a <= 0 || b <= 0)
            throw invalid_argument("Invalid matrix size");
        n = a;
        m = b;
        matrix.resize(a, vector<double> (b, 0));
    }

    Matrix(const vector<vector<double>>vec){
        set<int> st;
        for (int i = 0; i < vec.size(); i++){
            st.insert(vec[i].size());
        }

        if (st.size() != 1)
            throw invalid_argument("Invalid matrix");

        matrix = vec;
        n = vec.size();
        for (auto x: st)
            m = x;
    }

    Matrix (const Matrix& t){
        n = t.GetN();
        m = t.GetM();
        vector<vector<double>> res = t.GetMatrix();
        matrix.resize(n, vector<double> (m, 0));
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                matrix[i][j] = res[i][j];
            }
        }
    }

    int GetN() const{
        return n;
    }

    int GetM() const{
        return m;
    }

    vector<vector<double>> GetMatrix() const{
        return matrix;
    }

    void SetCoef(const vector<vector<double>> &coef){
        matrix = coef;
        n = coef.size();
        set<int> st;
        for (int i = 0; i < coef.size(); i++){
            st.insert(coef[i].size());
        }

        if (st.size() != 1)
            throw invalid_argument("Invalid matrix");

        for (auto x: st)
            m = x;
    }

    Matrix operator+ (Matrix& t){
        if (n != t.GetN() || m != t.GetM())
            throw invalid_argument("Can't sum this matrix");
        vector<vector<double>> a = GetMatrix();
        vector<vector<double>> b = t.GetMatrix();
        vector<vector<double>> res;
        res.resize(n, vector<double> (m, 0));
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                res[i][j] = a[i][j] + b[i][j];
            }
        }

        return Matrix(res);
    }

    Matrix operator- (Matrix& t){
        if (n != t.GetN() || m != t.GetM())
            throw invalid_argument("Can't sum this matrix");
        vector<vector<double>> a = GetMatrix();
        vector<vector<double>> b = t.GetMatrix();
        vector<vector<double>>res;
        res.resize(n, vector<double> ());
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                res[i].push_back(a[i][j] - b[i][j]);
            }
        }
        return Matrix(res);
    }

    Matrix operator* (Matrix& t){
        if (GetM() != t.GetN())
            throw invalid_argument("Can't sum this matrix");
        int k = t.GetM();
        vector<vector<double>> a = GetMatrix();
        vector<vector<double>> b = t.GetMatrix();
        vector<vector<double>>res;
        res.resize(n, vector<double> (k, 0));

        for (int i = 0; i < n; i++){
            for (int j = 0; j < k; j++){
                for (int z = 0; z < m; z++)
                    res[i][j] += a[i][z] * b[z][j];
            }
        }
        return Matrix(res);
    }


    void NumberMultiply(double n){
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++)
                matrix[i][j] *= n;
        }
    }

    Matrix AdamarMultiply (Matrix& t){
        if (n != t.GetN() || m != t.GetM())
            throw invalid_argument("Can't sum this matrix");
        vector<vector<double>> a = GetMatrix();
        vector<vector<double>> b = t.GetMatrix();
        vector<vector<double>> res;
        res.resize(n, vector<double> ());
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                res[i].push_back(a[i][j] * b[i][j]);
            }
        }
        return Matrix(res);
    }

    double MatrixTrace(){
        double answer = 0;
        if (n > m){
            for (int i = 0; i < m; i++)
                answer += matrix[i][i];
        }
        else {
            for (int i = 0; i < n; i++)
                answer += matrix[i][i];
        }
        return answer;
    }

    double ScalarMultiply(Matrix& t){
        if (n != 1 && m != 1)
            throw invalid_argument("Invalid operation");
         if (t.GetN() != 1 && t.GetM() != 1)
            throw invalid_argument("Invalid operation");
        double answer = 0;
        Matrix c = (*this).AdamarMultiply(t);
        vector<vector<double>> res = c.GetMatrix();
        for (int i = 0; i < res.size(); i++){
            for (int j = 0; j < res[i].size(); j++){
                answer += res[i][j];
            }
        }
        return answer;
    }

    double VectorNorma(){
        if (n != 1 && m != 1)
            throw invalid_argument("Invalid operation");
        double answer = 0;
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                answer += matrix[i][j] * matrix[i][j];
            }
        }
        return sqrt(answer);
    }
    double MaxNorma(){
        if (n != 1 && m != 1)
            throw invalid_argument("Invalid operation");
        double answer = 0;
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                answer = max(answer, abs(matrix[i][j]));
            }
        }
        return answer;
    }
    double FrobeniusNorma(){
        double answer = 0;
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                answer += matrix[i][j] * matrix[i][j];
            }
        }
        return sqrt(answer);
    }

    double Gauss(){
        vector<vector<double>> mat = matrix;
        double det = 1;
        for (int i = 0; i < n; i++) {
            int k = i;
            for (int j = i + 1; j < m; j++)
                if (abs(mat[j][i]) > abs(mat[k][i]))
                    k = j;
            if (abs(mat[k][i]) < EPS) {
                det = 0;
                break;
            }
            swap(mat[i], mat[k]);
            if (i != k)
                det = -det;
            det *= mat[i][i];
            for (int j = i + 1; j < m; j++)
                mat[i][j] /= mat[i][i];
            for (int j = 0; j < m; j++)
                if (j != i && abs(mat[j][i]) > EPS)
                    for (int k = i + 1; k < n; k++)
                        mat[j][k] -= mat[i][k] * mat[j][i];
        }

        return det;
    }

    double Rank(){
        int rank = max(n,m);
        vector<char> used (n);
        vector<vector<double>> res = matrix;
        for (int i = 0; i < n; ++i) {
            int j;
            for (j = 0; j < m; ++j)
                if (!used[j] && abs(res[j][i]) > EPS)
                    break;
            if (j == n)
                rank--;
            else {
                used[j] = true;
                for (int p = i + 1; p < m; ++p)
                    res[j][p] /= res[j][i];
                for (int k = 0; k < n; ++k)
                    if (k != j && abs(res[k][i]) > EPS)
                        for (int p = i + 1; p < m; ++p)
                            res[k][p] -= res[j][p] * res[k][i];
            }
        }
        return rank;
    }

};





complex<double> VectorsAngle(Matrix &s, Matrix &t){
    double n1 = s.VectorNorma();
    double n2 = t.VectorNorma();
    double scalar = s.ScalarMultiply(t);
    return acos(scalar / (n1 * n2));
}

Matrix Transposition (Matrix &t){
    vector<vector<double>> res = t.GetMatrix();
    int n = res.size();
    int m = res[0].size();
    vector<vector<double>> answer (m, vector<double> (n, 0));
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            answer[j][i] = res[i][j];
        }
    }
    return Matrix(answer);
}


ostream& operator<< (ostream &out, const Matrix &t){
    out << t.GetN() << " " << t.GetM() << "\n";
    vector<vector<double>> vec = t.GetMatrix();
    for (int i = 0; i < vec.size(); i++){
        for (int j = 0; j < vec[i].size(); j++){
            out << vec[i][j] << " ";
        }
        out << "\n";
    }
    return out;
}

Matrix& operator >> (istream& in, Matrix& t){
    int n, m;
    in >> n;
    in >> m;
    vector<vector<double>> vec(n, vector<double> (m, 0.));
    double a;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            in >> a;
            vec[i][j] = a;
        }
    }
    t.SetCoef(vec);
    return t;
}
class UnitMatrix : public Matrix{
public:
  UnitMatrix(int n) : Matrix(n, n){
  if (n <= 0)
  throw invalid_argument("invalid length");
  vector<vector<double>> result(n, vector<double> (n, 0));
  for (int i = 0; i < n; i++)
    result[i][i] = 1;
  matrix = result;
  }
};

class DiagonalMatrix : public Matrix{
public:
  DiagonalMatrix(int n, double c) : Matrix(n, n){
  if (n <= 0)
   throw invalid_argument("invalid length");
  vector<vector<double>> result (n, vector<double> (n, 0));
  for (int i = 0; i < n; i++)
    result[i][i] = c;
  matrix = result;
  }
};


class UpperTriangleMatrix : Matrix{
  public:
    UpperTriangleMatrix(vector<vector<double>> vec) : Matrix(vec){
      set<int> st;
      for (int i = 0; i < vec.size(); i++){
        st.insert(vec[i].size());
    }

    if (st.size() != 1)
      throw invalid_argument("Invalid matrix");

    int n = vec.size();
    int m;
    for (auto x: st)
      m = x;
    if (n != m)
      throw invalid_argument("Not square");

    for (int i = 1; i < n; i++){
      for (int j = 0; j < i; j++){
        if (vec[i][j] != 0)
          throw invalid_argument("Not triangle matrix");
      }
    }
  matrix = vec;
  }
};

class DownTriangleMatrix : Matrix{
  public:
  DownTriangleMatrix(vector<vector<double>> vec) : Matrix(vec){
  set<int> st;
  for (int i = 0; i < vec.size(); i++){
    st.insert(vec[i].size());
  }

  if (st.size() != 1)
    throw invalid_argument("Invalid matrix");

  int n = vec.size();
  int m;
  for (auto x: st)
  m = x;
  if (n != m)
    throw invalid_argument("Not square");
  for (int j = 1; j < n; j++){
    for (int i = 0; i < j; i++){
      if (vec[i][j] != 0)
        throw invalid_argument("Not triangle matrix");
      }
    }
  matrix = vec;
  }
};
class SimmetricMatrix : Matrix{
  public:
  SimmetricMatrix(vector<vector<double>> vec) : Matrix(vec){
    set<int> st;
  for (int i = 0; i < vec.size(); i++){
    st.insert(vec[i].size());
  }
  if (st.size() != 1)
    throw invalid_argument("Invalid matrix");
  int n = vec.size();
  int m;
  for (auto x: st)
    m = x;
  if (n != m)
    throw invalid_argument("Not square");
  for (int j = 1; j < n; j++){
    for (int i = 0; i < j; i++){
      if (vec[i][j] != 0)
        throw invalid_argument("Not triangle matrix");
    }
  }
    matrix = vec;
  }
};


void inversion(vector<vector<double>>& A, int N)
{
    double temp;

    vector<vector<double>> E(N, vector<double>(N,0));

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {
            E[i][j] = 0.0;

            if (i == j)
                E[i][j] = 1.0;
        }

    for (int k = 0; k < N; k++)
    {
        temp = A[k][k];

        for (int j = 0; j < N; j++)
        {
            A[k][j] /= temp;
            E[k][j] /= temp;
        }

        for (int i = k + 1; i < N; i++)
        {
            temp = A[i][k];

            for (int j = 0; j < N; j++)
            {
                A[i][j] -= A[k][j] * temp;
                E[i][j] -= E[k][j] * temp;
            }
        }
    }

    for (int k = N - 1; k > 0; k--)
    {
        for (int i = k - 1; i >= 0; i--)
        {
            temp = A[i][k];

            for (int j = 0; j < N; j++)
            {
                A[i][j] -= A[k][j] * temp;
                E[i][j] -= E[k][j] * temp;
            }
        }
    }

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            A[i][j] = E[i][j];


}

Matrix InvertMatrix(Matrix t){
    int n = t.GetN();
    int m = t.GetM();
    if (n != m)
        throw invalid_argument("Not square matrix");
    if (t.Gauss()==0)
        throw invalid_argument("Determinant zero");
    vector<vector<double>> res = t.GetMatrix();

    inversion(res,n);
    return Matrix(res);
}

void WriteToBinary(Matrix& t, string str){
	ofstream file(str, ios::out | ios::binary);
	if (!file)
		throw runtime_error("Can't open file");
	file.seekp(0);
	int n = t.GetN();
	int m = t.GetM();
	vector<vector<double>> vec = t.GetMatrix();
	file.write((char*)&n, sizeof(int));
	file.write((char*)&m, sizeof(int));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			file.write((char*)&vec[i][j], sizeof(double));
	file.close();
}

void ReadFromBinary(Matrix& t, string str){
	ifstream file(str, ios::binary | ios::in);
	if (!file)
		throw runtime_error("Can't open file");

	file.seekg(0, ios::end);
	int file_sz = file.tellg();

	int bin_sz = file_sz - 2 * sizeof(int);
	file.seekg(bin_sz, ios::beg);

	int n = t.GetN();
	int m = t.GetM();

	file.seekg(0, ios::beg);
	file.read((char*)&n, sizeof(int));
	file.read((char*)&m, sizeof(int));

	vector<vector<double>> vec(n, vector<double> (m, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			file.read((char*)&vec[i][j], sizeof(double));
	}
  t.SetCoef(vec);
	file.close();
}
