#include <stdio.h>

int city_team[500] = {0};
int road_length[500][500] = {0};
int city_step[500];
int min_length = 0x7FFFFFFF, road_kind = 0;
int max_team = 0;
int city;

void search(int c1, int c2, int length, int team);

int main(void)
{
    int n, m, c1, c2;
    int i, x, y, l;

    scanf("%d %d %d %d", &n, &m, &c1, &c2);
    city = n;
    for(i = 0; i < n; i++)
        scanf("%d", &city_team[i]);
    for(i = 0; i < m; i++)
    {
        scanf("%d %d %d", &x, &y, &l);
        road_length[x][y] = road_length[y][x] = l;
    }
    city_step[c1] = 1;
    search(c1, c2, 0, city_team[c1]);
    printf("%d %d\n", road_kind, max_team);

    return 0;
}

void search(int c1, int c2, int length, int team)
{
    int i;

    if(length > min_length)
        return;
    if(c1 == c2)
    {
        if(length < min_length)
        {
            min_length =  length;
            road_kind = 1;
            max_team = team;
        }
        else if( length == min_length)
            road_kind++;
        if(team > max_team)
            max_team = team;
        return;
    }
    for(i = 0; i < city; i++)
    {
        if(city_step[i] == 1 || road_length[c1][i] == 0)
            continue;
        city_step[i] = 1;
        search(i, c2, length + road_length[c1][i], team + city_team[i]);
        city_step[i] = 0;
    }

    return;
}
