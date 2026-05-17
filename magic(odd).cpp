#include <iostream>
#include <vector>
#include <iomanip>

// 函數：顯示 (n+1)*(n+1) 的表格
void displayMagicGrid(const std::vector<std::vector<int> >& grid, int n) {
    std::cout << "\n--- 魔術方陣結果 (最後一列與最後一行為加總) ---\n";
    
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) {
            // 使用 std::setw(5) 讓數字對齊，最後一列/最後一欄加個分隔視覺效果
            if (i == n || j == n) {
                // 顯示加總格（可以稍微做點區隔，這裡用括號表示加總）
                std::cout << std::setw(5) << grid[i][j];
            } else {
                std::cout << std::setw(5) << grid[i][j];
            }
        }
        std::cout << "\n";
        if (i == n - 1) {
            std::cout << std::string((n + 1) * 5, '-') << "\n"; // 分隔線
        }
    }
}

int main() {
    int n = 0;
    std::cout << "請輸入魔術方陣大小 n (必須 > 2 且目前以奇數為主): ";
    std::cin >> n;

    // 檢查防呆機制：如果 n < 3 則輸出不存在
    if (n < 3) {
        std::cout << "不存在\n";
        return 0;
    }

    // 建立 (n+1) * (n+1) 的二維陣列，全部預設為 0
    // 第 n 列 (Index n) 和第 n 行 (Index n) 用來放加總
    std::vector<std::vector<int> > grid(n + 1, std::vector<int>(n + 1, 0));

    // --- Coding 內部自動寫入：產生 n*n 魔術方陣 (以羅伯法為例) ---
    int row = 0;
    int col = n / 2; // 第一個數放在第一列正中間
    
    for (int i = 1; i <= n * n; ++i) {
        grid[row][col] = i;

        // 預計往右上方移動
        int next_row = (row - 1 + n) % n;
        int next_col = (col + 1) % n;

        // 如果右上方的格子已經有填數字了
        if (grid[next_row][next_col] != 0) {
            row = (row + 1) % n; // 改填在目前格子的正下方
        } else {
            row = next_row;
            col = next_col;
        }
    }

    // --- Coding 內部自動計算：第 n+1 row 和 column 的加總 ---
    // 計算每一列的總和，存入該列的最後一格 (grid[i][n])
    for (int i = 0; i < n; ++i) {
        int row_sum = 0;
        for (int j = 0; j < n; ++j) {
            row_sum += grid[i][j];
        }
        grid[i][n] = row_sum;
    }

    // 計算每一行的總和，存入該行的最後一格 (grid[n][j])
    for (int j = 0; j < n; ++j) {
        int col_sum = 0;
        for (int i = 0; i < n; ++i) {
            col_sum += grid[i][j];
        }
        grid[n][j] = col_sum;
    }

    // 右下角最後一格 (grid[n][n])：填入對角線總和（或是總列和的加總，數值會一樣）
    int diagonal_sum = 0;
    for (int i = 0; i < n; ++i) {
        diagonal_sum += grid[i][i];
    }
    grid[n][n] = diagonal_sum;

    // 顯示最終結果
    displayMagicGrid(grid, n);

    return 0;
}
