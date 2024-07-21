class Solution {
    vector<pair<int,int>> direction={{1,0},{0,1},{-1,0},{0,-1}};
    bool dfs1(int row,int col,vector<vector<int>>& blocked,vector<vector<int>>& vis,vector<int>& cell,vector<int>& destination,int& row_offset,int& col_offset){
        if(abs(cell[1]-col)>=blocked.size() || abs(cell[0]-row)>=blocked.size()){
            return true;
        }
        if(row==destination[0] && col==destination[1]){
            return true;
        }
        vis[row+row_offset][col+col_offset]=1;
        int r;
        int c;
        for(auto i:direction){
            r=row+i.first;
            c=col+i.second;
            if(r>=0 && c>=0 && r<1e6 && c<1e6 && vis[r+row_offset][c+col_offset]==0){
                if(dfs1(r,c,blocked,vis,cell,destination,row_offset,col_offset)){
                    return true;
                }
            }
        }
        return false;
    }

    bool is_not_trapped(vector<vector<int>>& blocked, vector<int>& cell,vector<int>& destination){
        vector<vector<int>> vis(blocked.size()*2+1,vector<int> (blocked.size()*2+1,0));
        int row_offset=blocked.size()-cell[0];
        int col_offset=blocked.size()-cell[1];
        for(auto it:blocked){
            int r=it[0]+row_offset;
            int c=it[1]+col_offset;
            if(r>=0 && c>=0 && r<blocked.size()*2+1 && c<blocked.size()*2+1){
                vis[r][c]=1;
            } 
        }
        return dfs1(cell[0],cell[1],blocked,vis,cell,destination,row_offset,col_offset);
    }
public:
    bool isEscapePossible(vector<vector<int>>& blocked, vector<int>& source, vector<int>& target) {
        return is_not_trapped(blocked,source,target) && is_not_trapped(blocked,target,source);
    }
};
