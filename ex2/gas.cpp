#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

struct road {      
    int cityA;
    int cityB;
    int length;    //gas needed
};

struct city {
    int *adjacent_list;
    int adjacent_cnt;
};

bool compare_length (road a, road b){return (a.length < b.length);}

void remove_from_adjacent (city &cityA, int cityB)
{
    for(int i = 0; i < cityA.adjacent_cnt; i++)
        if(cityA.adjacent_list[i] == cityB)
        {
            cityA.adjacent_cnt --;
            for(int j = i; j < cityA.adjacent_cnt; j++)
                cityA.adjacent_list[j] = cityA.adjacent_list[j+1];
        }
}

void DFS (int current_city, int city_cnt, city *cities, bool *visited)
{
    visited[current_city] = true;
    for (int i = 0; i < cities[current_city].adjacent_cnt; i++)
    {
        int next_city = cities[current_city].adjacent_list[i];
        if (!visited[next_city]) DFS(next_city, city_cnt, cities, visited);
    }
}

bool try_remove_longest_road (int city_cnt, city *cities, int road_cnt, road *roads)
{
    int cityA = roads[road_cnt - 1].cityA;
    int cityB = roads[road_cnt - 1].cityB;

    remove_from_adjacent (cities[cityA], cityB);
    remove_from_adjacent (cities[cityB], cityA);

    bool *visited = new bool[city_cnt];
    for (int i = 1; i < city_cnt; i++) visited[i] = false;

    DFS (cityA, city_cnt, cities, visited);                      //DFS search for cityB
    /*if (visited[cityB]) 
    {
        cout << "Road Removed:" << cityA << "-" << cityB << endl;  
        for (int j = 1; j < city_cnt; j++)
        {
            cout << "Adjecents from (" << j << "):";
            for (int i = 0; i < cities[j].adjacent_cnt; i++)
                cout << cities[j].adjacent_list[i] << ",";
            cout << endl;
        }
    }*/
    return visited[cityB];
}

int get_min_tank (int city_cnt, city *cities, int road_cnt, road *roads)
{
    sort (roads, roads + road_cnt, compare_length);                       //sort roads in ascending length order

    while (try_remove_longest_road (city_cnt, cities, road_cnt, roads))   //remove the longest road if the resulting                                                                   
        road_cnt --;                                                      //cities graph is still connected
    
    return roads[road_cnt - 1].length;
}

int main (int argc, char** argv)
{
    //Get file in buffer
    string filename = argv[1];
    ifstream text(filename);
    stringstream buffer;
    buffer << text.rdbuf();

    //Get input from buffer
    int city_cnt;
    int road_cnt;
    buffer >> city_cnt >> road_cnt;
    road *roads = new road[road_cnt];
    city *cities = new city[++ city_cnt];   //cities[0] is of no use

    for (int i = 0; i < city_cnt; i++) 
    {
        cities[i].adjacent_list = new int[city_cnt];
        cities[i].adjacent_cnt = 0;
    }
    for (int i = 0; i < road_cnt; i++)
    {
        int cityA, cityB;
        buffer >> cityA >> cityB >> roads[i].length;
        roads[i].cityA = cityA;
        roads[i].cityB = cityB;
        cities[cityA].adjacent_list [cities[cityA].adjacent_cnt ++] = cityB;
        cities[cityB].adjacent_list [cities[cityB].adjacent_cnt ++] = cityA;
    }
    
    //Calculate and print minimum tank size
    int min_tank_size = get_min_tank (city_cnt, cities, road_cnt, roads);
    cout << min_tank_size << endl;
}