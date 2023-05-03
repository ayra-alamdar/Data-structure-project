#pragma once
bool isValid(int x, int y, int n, int m) {
     return x >= 0 && x < n && y >= 0 && y < m;
}

void printPath(List<List<int>>& parent, int x, int y) {
     if (x <= -1 || y <= -1) {
          return;
     }
     printPath(parent, parent[x][y] / 100, parent[x][y] % 100);
     cout << "(" << x << "," << y << ") ";
}
// Find shortest path function
void FloydfindShortestPath(List<List<int>>& matrix) {
     int n = matrix.size();
     int m = matrix[0].size();

     List<List<int>> dist(n);
     for (int i = 0; i < n; i++)
     {
          List<int> obj(n);
          for (int j = 0; j < n; j++)
          {
               obj.push_back(INT_MAX);
          }
          dist.push_back(obj);
     }
     List<List<int>> parent(n);
     for (int i = 0; i < n; i++)
     {
          List<int> obj(n);
          for (int j = 0; j < n; j++)
          {
               obj.push_back(-1);
          }
          parent.push_back(obj);
     }


     CustomPriorityQueue<pair<int, pair<int, int>>> pq;
     pq.push({ matrix[0][0], {0, 0} });
     dist[0].set(0, matrix[0][0]);

     int dx[] = { 0, 1 };
     int dy[] = { 1, 0 };

     while (!pq.empty()) {
          int x = pq.top().second.first;
          int y = pq.top().second.second;
          int d = pq.top().first;
          pq.pop();

          if (d > dist[x][y]) {
               continue;
          }

          for (int i = 0; i < 2; i++) {
               int nx = x + dx[i];
               int ny = y + dy[i];
               if (isValid(nx, ny, n, m) && matrix[nx][ny] >= 0) 
               {
                    int newDist = dist[x][y] + matrix[nx][ny];
                    if (newDist < dist[nx][ny])
                    {
                         dist[nx].set(ny, newDist);
                         parent[nx].set(ny, x * 100 + y);
                         pq.push({ newDist, {nx, ny} });
                    }
               }
          }
     }

     if (dist[n - 1][m - 1] == INT_MAX) {
          cout << "There is no valid path." << endl;
     }
     else {
          cout << "The shortest path is: ";
          printPath(parent, n - 1, m - 1);
          cout << endl << "The path cost is: " << dist[n - 1][m - 1] << endl;
     }
}
// Find shortest path function from a specific location
void FloydfindShortestPath(List<List<int>>& matrix, int startX, int startY) {
     int n = matrix.size();
     int m = matrix[0].size();

     List<List<int>> dist(n);
     for (int i = 0; i < n; i++)
     {
          List<int> obj(n);
          for (int j = 0; j < n; j++)
          {
               obj.push_back(INT_MAX);
          }
          dist.push_back(obj);
     }
     List<List<int>> parent(n);
     for (int i = 0; i < n; i++)
     {
          List<int> obj(n);
          for (int j = 0; j < n; j++)
          {
               obj.push_back(-1);
          }
          parent.push_back(obj);
     }


     CustomPriorityQueue<pair<int, pair<int, int>>> pq;
     pq.push({ matrix[startX][startY], {startX, startY} });
     dist[startX].set(startY, matrix[startX][startY]);

     int dx[] = { 0, 1 };
     int dy[] = { 1, 0 };

     while (!pq.empty()) {
          int x = pq.top().second.first;
          int y = pq.top().second.second;
          int d = pq.top().first;
          pq.pop();

          if (d > dist[x][y]) {
               continue;
          }

          for (int i = 0; i < 2; i++) {
               int nx = x + dx[i];
               int ny = y + dy[i];
               if (isValid(nx, ny, n, m) && matrix[nx][ny] >= 0)
               {
                    int newDist = dist[x][y] + matrix[nx][ny];
                    if (newDist < dist[nx][ny])
                    {
                         dist[nx].set(ny, newDist);
                         parent[nx].set(ny, x * 100 + y);
                         pq.push({ newDist, {nx, ny} });
                    }
               }
          }
     }

     if (dist[n - 1][m - 1] == INT_MAX) {
          cout << "There is no valid path." << endl;
     }
     else {
          cout << "The shortest path is: ";
          printPath(parent, n - 1, m - 1);
          cout << endl << "The path cost is: " << dist[n - 1][m - 1] << endl;
     }
}
