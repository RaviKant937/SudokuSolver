#include<bits/stdc++.h>
using namespace std;
void print_err() {
	cerr << "\n";
}
template <class T, class... Arg>
void print_err(T x, Arg&&... args) {
	cerr << x << " ";
	print_err(args...);
}
#ifdef local
#define debug(...) print_err(__VA_ARGS__)
#else
#define debug(...)
#endif
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
// #define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
#define mod 1000000007
#define ll long long int
#define ff first
#define ss second
#define pb push_back
#define mp make_pair
#define pll pair<ll,ll>
#define vl vector<ll>
#define vpll vector<pair<ll,ll>>
#define mll map<ll,ll>
#define mllrev map<ll,ll,greater<int>>
#define ps(x,y) fixed<<setprecision(y)<<x
#define w(t) ll t;cin>>t;while(t--)
#define fo(i,n) for(ll i=0;i<n;++i)
#define foab(i,a,b) for(ll i=a;i<b;++i)
#define fastio ios_base::sync_with_stdio(NULL);cin.tie(NULL);cout.tie(NULL);
bool isbipartite = false;
class Graph {
public:
	list<ll> *adj_list;
	ll v;
	Graph(ll v) {
		this->v = v;
		adj_list = new list<ll>[v];
	}
	void add_edge(ll u, ll v, bool bidirectional = true) {
		adj_list[u].push_back(v);
		if (bidirectional) {
			adj_list[v].push_back(u);
		}
	}
	void print();
	void connected_compo();
	void dfs(ll v, int visited[], ll parent, ll col);
	void bfs(ll v, bool visited[]);
};
bool issolved = false;
//is it safe to place a number at a given position
bool sudokuhelper(vector<vector<ll>> &vect, ll row, ll col, ll value) {
	fo(i, 9) {
		if (vect[row][i] == value || vect[i][col] == value) {
			return false;
		}
	}
	ll subrow = (row / 3) * 3, subcol = (col / 3) * 3;//To reach 3*3 samll grid
	fo(i, 3) {
		fo(j, 3) {
			if (vect[subrow + i][subcol + j] == value) {
				return false;
			}
		}
	}
	return true;
}
void sudokusolver(vector<vector<ll>> &vect, ll row, ll col) {
	if (row == 8 and col == 9) {
		//printing final sudoku
		fo(i, 9) {
			fo(j, 9) {
				cout << vect[i][j] << " ";
			}
			cout << endl;
		}
		issolved = true;
		return ;
	}
	if (issolved) {
		return;
	}
	//Row Fully Filled
	if (col == 9) {
		sudokusolver(vect, row + 1, 0);
		return;
	}
	//Place Already Filled
	if (vect[row][col] != 0) {
		sudokusolver(vect, row, col + 1);
		return;
	}
	//Recursive case
	fo(i, 9) {
		if (sudokuhelper(vect, row, col, i + 1)) {
			vect[row][col] = i + 1;
			sudokusolver(vect, row, col + 1);
			vect[row][col] = 0;//Backtracking Step
			if (issolved) {
				return;
			}
		}
	}
	return ;
}
void solve() {
	vector<vector<ll>>vect(9, vector<ll>(9, 0));//9*9 Matrix As A input
	ll temp;
	fo(i, 9) {
		fo(j, 9) {
			cin >> temp;
			vect[i][j] = temp;
		}
	}
	sudokusolver(vect, 0, 0);
	return ;
}
//it is final that only one solution exist
int main() {
	fastio
#ifdef local
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	freopen("error.txt", "w", stderr);
#endif
	w(t) {
		issolved = false;
		solve();
		cout << endl;
	}
	return 0;
}