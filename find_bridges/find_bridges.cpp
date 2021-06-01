#include <iostream>
#include <fstream>
using namespace std;

ifstream file;
const char* f_path = "matr.txt";
//const char* f_path = "matr2.txt";

double** read_matrix(const char* file_path, int& n, int& m)
{
	ifstream in(file_path);

	if (in.is_open())
	{
		//how many numbers in the file (matrix)
		int count = 0;//quantity of numbers
		int temp;

		while (!in.eof())//till the end of the file
		{
			in >> temp;//reading of numbers without saving
			count++;
		}

		//to find out how many numbers in the first row
		in.seekg(0, ios::beg);//to the file beginning
		in.clear();

		int count_space = 0;//number of spaces
		char symbol;
		while (!in.eof())//to be on the save side - no longer than end of the file
		{
			in.get(symbol);//reading each next symbol
			if (symbol == ' ') count_space++;
			if (symbol == '\n') break;//if the row is finished, than stop
		}
		//cout << count_space << endl;

		//beginning of the file
		in.seekg(0, ios::beg);
		in.clear();

		int _n = count / (count_space + 1);//number of rows
		n = _n;
		int _m = count_space + 1;//number of columns
		m = _m;
		double** x;//the matrix
		x = new double* [_n];
		for (int i = 0; i < _n; i++) x[i] = new double[_m];

		//reading the matrix
		for (int i = 0; i < _n; i++)
			for (int j = 0; j < _m; j++)
				in >> x[i][j];

		in.close();
		return x;
	}
	else
	{
		cout << "Error: wrong file path";
	}
}

int n; //number of vertices

double** adj_mx = read_matrix(f_path, n, n);

int timer;
int* enter = new int[n];
int* ret = new int[n];
bool* used = new bool[n];


int min(int a, int b)
{
    if (a < b)
        return a;
    return b;
}

void dfs_bridges(int v, int p = -1)
{
    used[v] = true;
    enter[v] = ret[v] = timer++;
    for (int i = 0; i < n; ++i)
    {
        if (adj_mx[v][i] != 0)
        {
            int to = i;
            if (to == p)  continue;
            if (used[to]) ret[v] = min(ret[v], enter[to]);
            else
            {
                dfs_bridges(to, v);
                ret[v] = min(ret[v], ret[to]);
                if (ret[to] > enter[v]) cout << "bridge: (" << v << " , " << to << ")\n";
            }
        }
    }
}

void find_bridges()
{
    timer = 0;
    for (int i = 0; i < n; ++i)
    {
        used[i] = false;
    }
    for (int i = 0; i < n; ++i)
    {
        if (!used[i]) dfs_bridges(i);
    }
}

int main()
{
    find_bridges();
    return 0;
}