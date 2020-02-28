#include<bits/stdc++.h>
using namespace std;
int n, cnt;
vector<string>task, solver, score;
void read()
{
    freopen("data.in", "r", stdin);
    freopen("table.out", "w", stdout);
    cin >> cnt >> n;
    string Task, Score, Solver;
    for (int i = 0; i < n; i++)
    {
        cin >> Task >> Score >> Solver;
        task.push_back(Task);
        solver.push_back(Solver);
        score.push_back(Score);
    }
}
string gen(int num, string s, string name)
{
    string res = "<a " + s + "=";
    res += "\"";
    if (s == "href") res += "#";
    res += to_string(cnt) + (char)('A' + num) + "\">";
    res += name;
    res += "</a>";
    return res;
}
void write()
{
    cout << "| Solver |";
    for (string s : solver) cout << " " << s << " |";
    cout << '\n';

    for (int i = 0; i <= n; i++) cout << "| :-: ";
    cout << "|\n";

    cout << "| Task |";
    for (int i = 0; i < n; i++) cout << " " << gen(i + 1, "href", task[i]) << " |";
    cout << '\n';

    cout << "| Score/Rating |";
    for (string s : score) cout << " " << s <<" |";
    cout << '\n';

    cout << "| Tag |";
    for (int i = 0; i < n; i++) cout << " |";
    cout << '\n';

    for (int i = 0; i < n; i++)
        cout << "\n### " + gen(i + 1, "name", task[i]) << '\n'; 
}
int main()
{
    read();
    write();
    return 0;
}