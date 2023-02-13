#include "common.h"

#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> r( 20, vector<int>(20, 0) );
        int k = 1;
        int x, y;
        int xmin = 0;
        int ymin = 0;
        int xmax = n;
        int ymax = n;
        int sqr = n * n;
        bool isx = true, isplus = true;
        while (k <= sqr) {
            if (isx && isplus) {
                for (x = xmin, y = ymin; x < xmax; ++x) {
                    r[y][x] = k++;
                }
                ++ymin;
                isx = false;
                isplus = true;
            }
            else if (!isx && isplus) {
                for (x = xmax - 1, y = ymin; y < ymax; ++y) {
                    r[y][x] = k++;
                }
                --xmax;
                isx = true;
                isplus = false;
            }
            else if (isx && !isplus) {
                for (x = xmax - 1, y = ymax - 1; x >= xmin; --x) {
                    r[y][x] = k++;
                }
                --ymax;
                isx = false;
                isplus = false;
            }
            else {
                for (x = xmin, y = ymax - 1; y >= ymin; --y) {
                    r[y][x] = k++;
                }
                ++xmin;
                isx = true;
                isplus = true;
            }
        }
        return r;
    }
};

void lc_tset() {
    Solution sln;
    vector<vector<int>> vv = sln.generateMatrix(3);
}