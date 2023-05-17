#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <tuple>
#include <string>
#include <algorithm>

using namespace std;

using ll = long long;
using vb = vector<bool>;
using vvb = vector<vb>;
using vi = vector<int>;
using vvi = vector<vi>;
using vl = vector<ll>;
using vvl = vector<vl>;
using pii = pair<int, int>;
using vii = vector<pii>;
using pll = pair<ll, ll>;
using vll = vector<pll>;
using Adj = vector<vll>;

constexpr auto inf = ll{ 99'987'654'321 };

ll n, m;
Adj adj;
ll b, e;
vl ansvec;
ll ans;

void solve() {
	auto dist = vl(n + 1, inf);
	dist[b] = 0;

	using T = tuple<ll, ll, vl>;

	auto q = priority_queue<T, vector<T>, greater<T>>{};
	q.push({ 0, b, vl{b} });

	while (!q.empty()) {
		const auto& [_, x, vec] = T{ q.top() };
		q.pop();

		if (e == x) {
			ansvec = vl{ vec };
			ans = dist[e];
			break;
		}

		for (const auto& [y, d] : adj[x]) {
			const auto& newDist = dist[x] + d;
			if (newDist < dist[y]) {
				dist[y] = newDist;
				auto nextVec = vl{ vec };
				nextVec.push_back(y);
				q.push({ dist[y], y, nextVec });
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	cin >> n >> m;
	adj = Adj(n + 1, vll{});
	while (0 < (m--)) {
		ll a, b, c;
		cin >> a >> b >> c;
		adj[a].push_back({ b, c });
	}
	cin >> b >> e;
	solve();

	cout << ans << '\n'
		<< ansvec.size() << '\n';
	for (const auto& x : ansvec) {
		cout << x << ' ';
	}

	return 0;
}
