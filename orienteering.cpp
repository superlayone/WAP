#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <memory.h>
#include <queue>

using namespace std;
int dp[1 << 18][20];
struct Point{
    int x;
    int y;
    Point(){}
    Point(int X,int Y):x(X),y(Y){}
};
class Orienteering {

    public:
        void    main();
        int     bfs(Point a,Point b);
        bool    canGo(Point now);
        void    getDist();
    private:
        int     width;
        int     height;
        char    data[101][101];
        int     dataVisited[101][101];
        int     atNum;
        Point   tag[20];
        Point   start;
        Point   goal;
        int     dist[20][20];
        bool    unreachable;
};
void Orienteering::getDist(){
    memset(dist,0,sizeof(dist));
    int ret;
    for(int i = 0; i < (atNum+2); i++){
        for(int j = i+1; j < (atNum+2); j++){
            if((ret = bfs(tag[i],tag[j])) != -1){
                dist[i][j] = ret;
                dist[j][i] = ret;
            }else{
                dist[i][j] = -1;
                dist[j][i] = -1;
            }
            if(dist[0][j] == -1){
                unreachable = true;
                break;
            }
        }
        if(dist[i][atNum+1] == -1){
            unreachable = true;
            break;
        }
    }
}
bool Orienteering::canGo(Point now){
    if(now.x < 0 || now.x > width-1 || now.y < 0 || now.y > height-1 || data[now.y][now.x] == '#' || dataVisited[now.y][now.x]){
        return false;
    }
    return true;
}
int Orienteering::bfs(Point startP,Point endP){
    memset(dataVisited,0,sizeof(dataVisited));
    queue<Point> q;
    q.push(startP);
    dataVisited[startP.y][startP.x] = 1;
    while(!q.empty()){
        Point qfront = q.front();
        q.pop();
        if(qfront.x == endP.x && qfront.y == endP.y){
            return dataVisited[qfront.y][qfront.x]-1;
        }
        Point up = Point(qfront.x,qfront.y-1);
        if(canGo(up)){
            q.push(up);
            dataVisited[up.y][up.x] = dataVisited[qfront.y][qfront.x]+1;
        }
        Point down = Point(qfront.x,qfront.y+1);
        if(canGo(down)){
            q.push(down);
            dataVisited[down.y][down.x] = dataVisited[qfront.y][qfront.x]+1;
        }
        Point left = Point(qfront.x-1,qfront.y);
        if(canGo(left)){
            q.push(left);
            dataVisited[left.y][left.x] = dataVisited[qfront.y][qfront.x]+1;
        }
        Point right = Point(qfront.x+1,qfront.y);
        if(canGo(right)){
            q.push(right);
            dataVisited[right.y][right.x] = dataVisited[qfront.y][qfront.x]+1;
        }
    }
    return -1;
}
void Orienteering::main(){
    cin>>width>>height;
    memset(data,0,sizeof(data));
    atNum = 0;
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            cin>>data[i][j];
            if(data[i][j] == '@'){
                tag[++atNum] = Point(j,i);
            }
            if(data[i][j] == 'S'){
                start = Point(j,i);
            }
            if(data[i][j] == 'G'){
                goal = Point(j,i);
            }
        }
    }
    tag[0] = start;
    tag[atNum+1] = goal;
    unreachable = false;
    getDist();
    //S or G is unreachable
    if(unreachable){
        cout<<-1<<endl;
        return;
    }
    //No '@' character
    if(atNum == 0){
        cout<<dist[0][1]<<endl;
        return;
    }
    //else calculate
    memset(dp,-1,sizeof(dp));
    int full = 1 << atNum;
    for(int i = 0; i < atNum ; i++){
        dp[(1 << i)][i+1] = dist[0][i+1];
    }
    for(int i = 0; i < full; i++){
        for(int j = 1; j <= atNum; j++){
            if((i & (1 << (j - 1))) == 0 || dp[i][j] == -1){
                continue;
            }
            for(int k = 1; k <= atNum; k++){
                if(i & (1 << (k - 1)) || dist[j][k] == -1){
                    continue;
                }
                if(dp[i | (1 << (k - 1))][k] == -1 || dp[i | (1 << (k - 1))][k] > (dp[i][j] + dist[j][k])){
                    dp[i | (1 << (k - 1))][k] = dp[i][j] + dist[j][k];
                }
            }
        }
    }
    int ret = -1;
    for(int i = 1; i <= atNum; i++){
        if(dp[full-1][i] != -1 && dist[atNum+1][i] != -1){
            if(ret == -1 || ret > (dp[full - 1][i] + dist[atNum + 1][i])){
                ret = dp[full - 1][i] + dist[atNum + 1][i];
            }
        }
    }
    cout<<ret<<endl;
}
int main()
{
    Orienteering o;
    o.main();
    return 0;
}
