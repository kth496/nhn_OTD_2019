#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <math.h>   // pow, sqrt
#include <stdlib.h> // abs
using namespace std;

bool validation(vector<tuple<int, int>> &me_par_relation, vector<tuple<int, int, int, int>> node, tuple<int, int, int, int> newone);
float ed(int x1, int y1, int x2, int y2);
void make_adj_matrix(int N, int (*map)[101], vector<tuple<int, int>> &me_par_relation);
void findroute(string *ans_str, int *answer, const int obj, int past, int cur_loc, int length, string route_info, const int (*map)[101]);

int main()
{
    // start input and check validation logic
    int N, sp, ep;
    scanf("%d", &N);
    vector<tuple<int, int, int, int>> node;
    tuple<int, int> init = make_tuple(0, 10000);
    vector<tuple<int, int>> me_par_relation(101, init);

    for (int i = 0; i < N; i++)
    {
        int C, X, Y, R;
        scanf("%d %d %d %d", &C, &X, &Y, &R);
        if (i == 0)
        {
            node.push_back(make_tuple(C, X, Y, R));
            continue;
        }
        tuple<int, int, int, int> tmp;
        tmp = make_tuple(C, X, Y, R);
        if (validation(me_par_relation, node, tmp))
        {
            node.push_back(make_tuple(C, X, Y, R));
        }
        else
        {
            printf("-1");
            return 0;
        }
        for (auto j : node)
        {
            int c, x, y, r;
            c = get<0>(j);
        }
    }
    scanf("%d %d", &sp, &ep);
    // end input logic

    int adj_mat[101][101] = {
        0,
    };

    make_adj_matrix(N, adj_mat, me_par_relation);

    // find route
    int ans_v = 1000;
    string ans_str = to_string(sp);
    string starting_location = to_string(sp);
    findroute(&ans_str, &ans_v, ep, sp, sp, 1, starting_location, adj_mat);
    cout << ans_str << endl;

    return 0;
}

bool validation(vector<tuple<int, int>> &me_par_relation, vector<tuple<int, int, int, int>> node, tuple<int, int, int, int> newone)
{
    int new_c, new_x, new_y, new_r, chk;
    new_c = get<0>(newone);
    new_x = get<1>(newone);
    new_y = get<2>(newone);
    new_r = get<3>(newone);
    for (auto i : node)
    {
        int old_c, old_x, old_y, old_r;
        old_c = get<0>(i);
        old_x = get<1>(i);
        old_y = get<2>(i);
        old_r = get<3>(i);

        int tmp_inner_radi_distance = abs(old_r - new_r);
        int tmp_outer_radi_distance = abs(old_r + new_r);
        float inner_radi_distance = (float)tmp_inner_radi_distance;
        float outer_radi_distance = (float)tmp_outer_radi_distance;
        float ed_distance;
        ed_distance = ed(old_x, old_y, new_x, new_y);
        if (outer_radi_distance < ed_distance)
        {
            continue;
        }
        else if (inner_radi_distance > ed_distance)
        {
            if (new_r > old_r)
            {
                int existing_r;
                existing_r = get<1>(me_par_relation[old_c]);
                if (new_r < existing_r)
                {
                    tuple<int, int> tmp_data;
                    tmp_data = make_tuple(new_c, new_r);
                    me_par_relation[old_c] = tmp_data;
                }
            }
            else
            {
                tuple<int, int> tmp_data;
                tmp_data = make_tuple(old_c, old_r);
                me_par_relation[new_c] = tmp_data;
            }
            continue;
        }

        else
        {
            return false;
        }
    }
    return true;
}

float ed(int x1, int y1, int x2, int y2)
{
    return sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
}

void make_adj_matrix(int N, int (*map)[101], vector<tuple<int, int>> &me_par_relation)
{
    for (int j = 0; j < N + 1; j++)
    {
        int cur = j;
        int par = get<0>(me_par_relation[j]);
        int rad = get<1>(me_par_relation[j]);
        map[cur][par] = 1;
        map[par][cur] = 1;
    }
    map[0][0] = 0;
    return;
}

void findroute(string *ans_str, int *answer, const int obj, int past, int cur_loc, int length, string route_info, const int (*map)[101])
{
    if (cur_loc == obj)
    {
        int curanswer = *answer;
        if (curanswer > length)
        {
            *answer = length;
            *ans_str = route_info;
            return;
        }
        else
        {
            return;
        }
    }
    for (int i = 0; i < 101; i++)
    {
        if ((map[cur_loc][i] == 1) && (i != past))
        {
            string ret_str = route_info + " " + to_string(i);
            findroute(ans_str, answer, obj, cur_loc, i, length + 1, ret_str, map);
        }
    }
}