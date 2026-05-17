#include <iostream>
#include <vector>
#include <iomanip>

// 函數：顯示 (n+1)*(n+1) 的表格
void displayMagicGrid(const std::vector<std::vector<int> >& grid, int n) {
    std::cout << "\n--- 偶數魔術方陣結果 (最後一列與最後一行為加總) ---\n";
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) {
            std::cout << std::setw(6) << grid[i][j];
        }
        std::cout << "\n";
        if (i == n - 1) {
            std::cout << std::string((n + 1) * 6, '-') << "\n";
        }
    }
}

// 輔助函數：用奇數羅伯法填寫子矩陣（用於單偶數）
void fillOddMagic(std::vector<std::vector<int> >& grid, int n, int start_row, int start_col, int start_val) {
    int row = 0;
    int col = n / 2;
    for (int i = 0; i < n * n; ++i) {
        grid[start_row + row][start_col + col] = start_val + i;
        int next_row = (row - 1 + n) % n;
        int next_col = (col + 1) % n;
        if (grid[start_row + next_row][start_col + next_col] != 0) {
            row = (row + 1) % n;
        } else {
            row = next_row;
            col = next_col;
        }
    }
}

int main() {
    int n = 0;
    std::cout << "請輸入偶數大小 n (必須 > 2 且為偶數): ";
    std::cin >> n;

    // 檢查防呆機制：如果 n < 3 或不是偶數
    if (n < 3 || n % 2 != 0) {
        std::cout << "不存在\n";
        return 0;
    }

    // 建立 (n+1) * (n+1) 的二維陣列
    std::vector<std::vector<int> > grid(n + 1, std::vector<int>(n + 1, 0));

    // ==========================================
    // 情況一：雙偶數 (Double Even, 例如 4, 8, 12...)
    // ==========================================
    if (n % 4 == 0) {
        // 1. 依序填入 1 到 n^2
        int count = 1;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                grid[i][j] = count++;
            }
        }
        // 2. 對角線翻轉
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                // 判斷是否落在 4x4 小方塊的對角線上
                if ((i % 4 == j % 4) || ((i % 4 + j % 4) == 3)) {
                    grid[i][j] = (n * n + 1) - grid[i][j];
                }
            }
        }
    }
    // ==========================================
    // 情況二：單偶數 (Single Even, 例如 6, 10, 14...)
    // ==========================================
    else {
        int half = n / 2;
        int sub_size = half * half;

        // 填寫四個子矩陣 A, B, C, D
        fillOddMagic(grid, half, 0, 0, 1);            // A 區塊 (左上)
        fillOddMagic(grid, half, half, half, sub_size + 1); // B 區塊 (右下)
        fillOddMagic(grid, half, 0, half, 2 * sub_size + 1); // C 區塊 (右上)
        fillOddMagic(grid, half, half, 0, 3 * sub_size + 1); // D 區塊 (左下)

        int k = (n - 2) / 4;

        // A 區塊與 D 區塊交換特定行
        for (int i = 0; i < half; ++i) {
            for (int j = 0; j < half; ++j) {
                // 左側 k 行的交換規則
                if (j < k) {
                    if (i == half / 2) continue; // 置中列留到後面特別處理
                    std::swap(grid[i][j], grid[i + half][j]);
                }
                // 右側 k-1 行的交換規則 (當 n > 6 時才會觸發)
                if (j >= half - k + 1) {
                    std::swap(grid[i][j], grid[i + half][j]);
                }
            }
        }
        // 特別處理 A 區與 D 區的中間列凸起部交換
        std::swap(grid[half / 2][k], grid[half / 2 + half][k]);

        // C 區塊與 B 區塊交換右側的 k-1 行
        for (int i = 0; i < half; ++i) {
            for (int j = half; j < half + k - 1; ++j) {
                std::swap(grid[i][j], grid[i + half][j]);
            }
        }
    }

    // ==========================================
    // 後續處理：計算第 n+1 row 和 column 的加總
    // ==========================================
    // 計算每列總和並存入 grid[i][n]
    for (int i = 0; i < n; ++i) {
        int row_sum = 0;
        for (int j = 0; j < n; ++j) {
            row_sum += grid[i][j];
        }
        grid[i][n] = row_sum;
    }

    // 計算每行總和並存入 grid[n][j]
    for (int j = 0; j < n; ++j) {
        int col_sum = 0;
        for (int i = 0; i < n; ++i) {
            col_sum += grid[i][j];
        }
        grid[n][j] = col_sum;
    }

    // 右下角最後一格 grid[n][n] 填入主對角線總和
    int diagonal_sum = 0;
    for (int i = 0; i < n; ++i) {
        diagonal_sum += grid[i][i];
    }
    grid[n][n] = diagonal_sum;

    // 顯示結果
    displayMagicGrid(grid, n);

    return 0;
}
