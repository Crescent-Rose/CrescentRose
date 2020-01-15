#include <bits/stdc++.h>
using namespace std;

char ss[100];

int id(char ch) {
    if (islower(ch)) return ch - 'a';
    else if (isupper(ch)) return ch - 'A' + 26;
    else return -1;
}

const int P = 52;

int sub(int a, int b) {
    int r = a - b; return r < 0 ? r + P : r;
}

string decypher(const string& orig, const string& key) {
    string decy(orig.size(), '*');
    for (int i = 0; i != (int)orig.size(); ++i)
        decy[i] = ss[sub(id(orig[i]), id(key[i % key.size()]))];
    return decy;
}

int main()
{
    for (int i = 0; i != 26; ++i) ss[i] = 'a' + i;
    for (int i = 0; i != 26; ++i) ss[i + 26] = 'A' + i;
    ios::sync_with_stdio(0); cin.tie(0);
    int n, m; cin >> n >> m;
    vector<pair<int, int> > qv(m);
    for (int i = 0; i != qv.size(); ++i)
        cin >> qv[i].first >> qv[i].second;
    vector<string> sv(n);
    for (int i = 0; i != sv.size(); ++i)
        cin >> sv[i];
    reverse(qv.begin(), qv.end());
    for (int i = 0; i != m; ++i)
        sv[qv[i].second - 1] = decypher(sv[qv[i].second - 1], sv[qv[i].first - 1]);
    for (int i = 0; i != n; ++i)
        cout << sv[i] << endl;
    return 0;
}
