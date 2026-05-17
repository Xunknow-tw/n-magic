#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <sstream>

// 函數：顯示 (n+1)*(n+1) 的表格（用於魔術方陣）
void displayMagicGrid(const std::vector<std::vector<int> >& grid, int n) {
    std::cout << "\n--- 魔術方陣結果 (最後一列與最後一行為加總) ---\n";
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) {
            std::cout << std::setw(6) << grid[i][j];
        }
        std::cout << "\n";
        if (i == n - 1) {
            std::cout << std::string((n + 1) * 6, '-') << "\n";
        }
    }
    std::cout << "\n"; // 多空一行方便連續閱讀
}

// 函數：顯示一般的 n*n 表格（用於手動填寫模式）
void displayNormalGrid(const std::vector<std::vector<int> >& grid, int n) {
    std::cout << "\n--- 當前表格狀態 ---\n    ";
    for (int j = 0; j < n; ++j) std::cout << std::setw(4) << j;
    std::cout << "\n    " << std::string(n * 4, '-') << "\n";
    for (int i = 0; i < n; ++i) {
        std::cout << std::setw(2) << i << " |";
        for (int j = 0; j < n; ++j) {
            std::cout << std::setw(4) << grid[i][j];
        }
        std::cout << "\n";
    }
    std::cout << "--------------------\n\n";
}

// 輔助函數：用奇數羅伯法填寫子矩陣
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
    // 外層大迴圈：讓程式能一直重複使用
    while (true) {
        std::string inputLine;
        std::cout << "請輸入指令 (例如 '3', '3 null', 或輸入 '+-0' 結束程式): ";
        std::getline(std::cin, inputLine);

        // 1. 優先檢查是否為結束指令
        if (inputLine == "+-0") {
            std::cout << "收到結束指令，程式已退出。\n";
            break; 
        }

        // 跳過空白輸入
        if (inputLine.empty()) continue;

        std::stringstream ss(inputLine);
        int n;
        std::string suffix = "";

        // 解析數字
        if (!(ss >> n)) {
            std::cout << "輸入錯誤，請重新輸入！\n\n";
            continue;
        }
        ss >> suffix; // 嘗試讀取後面的 null

        // ==========================================
        // 模式 A：使用者輸入 n+null (n > 0) -> 建立空表格
        // ==========================================
        if (suffix == "null") {
            if (n <= 0) {
                std::cout << "錯誤：n 必須大於 0\n\n";
                continue;
            }

            std::vector<std::vector<int> > grid(n, std::vector<int>(n, 0));
            std::cout << "\n[系統] 已建立 " << n << "x" << n << " 的空表格。\n";
            displayNormalGrid(grid, n);

            while (true) {
                int row, col, val;
                std::cout << "請輸入座標與數值 (列 行 數值) [輸入 -1 -1 -1 返回主選單]: ";
                std::cin >> row >> col >> val;

                if (row == -1 && col == -1 && val == -1) {
                    std::cin.ignore(); // 清除快取，避免影響下一次的 getline
                    std::cout << "已返回主選單。\n\n";
                    break;
                }

                if (row >= 0 && row < n && col >= 0 && col < n) {
                    grid[row][col] = val;
                    displayNormalGrid(grid, n);
                } else {
                    std::cout << "錯誤：座標超出範圍，請重新輸入。\n";
                }
            }
            continue; // 跳過下方的魔術方陣邏輯，回到最外層迴圈
        }

        // ==========================================
        // 模式 B：自動生成魔術方陣模式 (單純輸入 n)
        // ==========================================
        if (n < 3) {
            std::cout << "Doesn't exist\n\n";
            continue;
        }

        // 建立 (n+1) * (n+1) 的魔術方陣二維陣列
        std::vector<std::vector<int> > grid(n + 1, std::vector<int>(n + 1, 0));

        // 1. 奇數魔術方陣
        if (n % 2 != 0) {
            fillOddMagic(grid, n, 0, 0, 1);
        }
        // 2. 雙偶數魔術方陣
        else if (n % 4 == 0) {
            int count = 1;
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) grid[i][j] = count++;
            }
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if ((i % 4 == j % 4) || ((i % 4 + j % 4) == 3)) {
                        grid[i][j] = (n * n + 1) - grid[i][j];
                    }
                }
            }
        }
        // 3. 單偶數魔術方陣
        else {
            int half = n / 2;
            int sub_size = half * half;

            fillOddMagic(grid, half, 0, 0, 1);                  // A
            fillOddMagic(grid, half, half, half, sub_size + 1); // B
            fillOddMagic(grid, half, 0, half, 2 * sub_size + 1); // C
            fillOddMagic(grid, half, half, 0, 3 * sub_size + 1); // D

            int k = (n - 2) / 4;
            for (int i = 0; i < half; ++i) {
                for (int j = 0; j < half; ++j) {
                    if (j < k) {
                        if (i == half / 2) continue;
                        std::swap(grid[i][j], grid[i + half][j]);
                    }
                    if (j >= half - k + 1) {
                        std::swap(grid[i][j], grid[i + half][j]);
                    }
                }
            }
            std::swap(grid[half / 2][k], grid[half / 2 + half][k]);

            for (int i = 0; i < half; ++i) {
                for (int j = half; j < half + k - 1; ++j) {
                    std::swap(grid[i][j], grid[i + half][j]);
                }
            }
        }

        // --- 計算第 n+1 row 和 column 的加總 ---
        for (int i = 0; i < n; ++i) {
            int row_sum = 0;
            for (int j = 0; j < n; ++j) row_sum += grid[i][j];
            grid[i][n] = row_sum;
        }

        for (int j = 0; j < n; ++j) {
            int col_sum = 0;
            for (int i = 0; i < n; ++i) col_sum += grid[i][j];
            grid[n][j] = col_sum;
        }

        int diagonal_sum = 0;
        for (int i = 0; i < n; ++i) diagonal_sum += grid[i][i];
        grid[n][n] = diagonal_sum;

        // 顯示結果
        displayMagicGrid(grid, n);
    }

    return 0;
}
