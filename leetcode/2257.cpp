#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

// 스코프가 지정된 열거형(enum class) 정의
enum class CellState {
    UNOCCUPIED = 0,
    OCCUPIED = 1,
    GUARD = 10,
    WALL = 20
};

class Solution {
    // 방향 배열 (오른쪽, 왼쪽, 위, 아래)
    const int dx[4] = {0, 0, -1, 1};
    const int dy[4] = {1, -1, 0, 0};
    
    // 보호 구역 표시 함수
    void markGuarded(int r, int c, int dir, vector<vector<CellState>>& tmpMap, int m, int n) {
        int nr = r + dy[dir];
        int nc = c + dx[dir];
        while(nr >= 0 && nr < m && nc >= 0 && nc < n) {
            if(tmpMap[nr][nc] == CellState::WALL || tmpMap[nr][nc] == CellState::GUARD) break;
            if(tmpMap[nr][nc] == CellState::UNOCCUPIED) {
                tmpMap[nr][nc] = CellState::OCCUPIED;
            }
            nr += dy[dir];
            nc += dx[dir];
        }
    }

public:
    int countUnguarded(int m, int n, vector<vector<int>>& guards, vector<vector<int>>& walls) {
        // 초기 맵 설정
        vector<vector<CellState>> tmpMap(m, vector<CellState>(n, CellState::UNOCCUPIED));

        // 가드 위치 설정
        for(const auto& guardPos : guards) {
            int row = guardPos[0];
            int col = guardPos[1];
            if(row < 0 || row >= m || col < 0 || col >= n) continue;
            tmpMap[row][col] = CellState::GUARD;
        }

        // 벽 위치 설정
        for(const auto& wallPos : walls) {
            int row = wallPos[0];
            int col = wallPos[1];
            if(row < 0 || row >= m || col < 0 || col >= n) continue;
            tmpMap[row][col] = CellState::WALL;
        }

        // 각 가드에서 보호 구역 표시
        for(int r = 0; r < m; ++r) {
            for(int c = 0; c < n; ++c) {
                if(tmpMap[r][c] == CellState::GUARD) {
                    for(int dir = 0; dir < 4; dir++) {
                        markGuarded(r, c, dir, tmpMap, m, n);
                    }
                }
            }
        }

        // 보호받지 못한 영역 계산
        int unguarded = 0;
        for(int r = 0; r < m; ++r) {
            for(int c = 0; c < n; ++c) {
                if(tmpMap[r][c] == CellState::UNOCCUPIED) {
                    unguarded++;
                }
            }
        }

        return unguarded;
    }
};