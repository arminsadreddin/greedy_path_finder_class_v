#include <QCoreApplication>
#include <iostream>
#include <vector>
using namespace std;
char my_map[6][5] = {
    {' ','#',' ','#',' '},
    {' ',' ',' ',' ',' '},
    {' ','#','#','#','#'},
    {' ',' ',' ',' ',' '},
    {' ','#','#','#',' '},
    {' ',' ',' ',' ',' '},
};
int my_x = 1;
int my_y = 5;
int goal_x = 4;
int goal_y = 0;
struct node{
    int x;
    int y;
    vector<pair<int , int> > path;
};
vector<node> open_list;
vector<node> visited_list;
void open_child(node tmp);
bool is_in_field(node tmp);
bool is_wall(node tmp);
bool is_in_visited(node tmp);
node get_best_node();
int get_node_error(node tmp);
bool is_final_node(node tmp);
int main()
{
    node cur_node;
    cur_node.x = my_x;
    cur_node.y = my_y;
    open_list.push_back(cur_node);
    while(!open_list.empty()){
        cur_node = get_best_node();
        ////
        if(is_final_node(cur_node)){
            break;
        }
        ///
        open_child(cur_node);
    }

    cout << "------------" << endl;
    for(int i = 0 ; i < cur_node.path.size() ; i++){
        cout << cur_node.path.at(i).first << " , " << cur_node.path.at(i).second << endl;
    }


}
void open_child(node tmp){

    node t1 = tmp;
    pair<int , int> path_head;
    path_head.first = tmp.x;
    path_head.second = tmp.y;
    t1.path.push_back(path_head);
    t1.x -=1;


    node t2 = tmp;
    t2.x+=1;
    t2.path.push_back(path_head);


    node t3 = tmp;
    t3.y-=1;
    t3.path.push_back(path_head);


    node t4 = tmp;
    t4.y+=1;
    t4.path.push_back(path_head);


    if(is_in_field(t1)){
        if(!is_wall(t1)){
            if(!is_in_visited(t1)){
                open_list.push_back(t1);
            }
        }
    }
    if(is_in_field(t2)){
        if(!is_wall(t2)){
            if(!is_in_visited(t2)){
                open_list.push_back(t2);
            }
        }
    }
    if(is_in_field(t3)){
        if(!is_wall(t3)){
            if(!is_in_visited(t3)){
                open_list.push_back(t3);
            }
        }
    }
    if(is_in_field(t4)){
        if(!is_wall(t4)){
            if(!is_in_visited(t4)){
                open_list.push_back(t4);
            }
        }
    }


}
bool is_in_field(node tmp){
    if(tmp.x < 0 || tmp.x > 4){
        return false;
    }

    if(tmp.y < 0 || tmp.y > 5){
        return false;
    }
    return true;
}
bool is_wall(node tmp){
    if(my_map[tmp.y][tmp.x] == '#'){
        return true;
    }
    return false;
}
bool is_in_visited(node tmp){
    for(int i = 0 ; i < visited_list.size() ; i++){
        if(visited_list.at(i).x == tmp.x && visited_list.at(i).y == tmp.y){
            return true;
        }
    }
    return false;
}
node get_best_node(){
    double min_error = 9999;
    int best_node_index = 0;
    for(int i = 0 ; i < open_list.size() ; i++){
        node tmp = open_list.at(i);
        double tmp_error = get_node_error(tmp);
        if(tmp_error < min_error){
            min_error = tmp_error;
            best_node_index = i;
        }
    }


    node ret_node = open_list.at(best_node_index);
    open_list.erase(open_list.begin() + best_node_index);
    visited_list.push_back(ret_node);
    cout << ret_node.x << " , " << ret_node.y << endl;
    return ret_node;

}
int get_node_error(node tmp){
    return abs(tmp.x-goal_x) + abs(tmp.y-goal_y);
}
bool is_final_node(node tmp){
    if(tmp.x == goal_x && tmp.y == goal_y){
        return true;
    }
    return false;
}









