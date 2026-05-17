#include <iostream>
#include <vector>
#include <iomanip> // 用於美化輸出排版

// 函數：顯示當前的 n*n 表格
void displayGrid(const std::vector<std::vector<int> >& grid, int n) {
    std::cout << "\n--- 當前表格狀態 ---\n";
    
    // 顯示行號 (Column Index)
    std::cout << "    ";
    for (int j = 0; j < n; ++j) {
        std::cout << std::setw(4) << j;
    }
    std::cout << "\n    " << std::string(n * 4, '-') << "\n";

    // 顯示內容與列號 (Row Index)
    for (int i = 0; i < n; ++i) {
        std::cout << std::setw(2) << i << " |";
        for (int j = 0; j < n; ++j) {
            std::cout << std::setw(4) << grid[i][j];
        }
        std::cout << "\n";
    }
    std::cout << "--------------------\n";
}

int main() {
    int n = 0;
    std::cout << "請輸入表格大小 n (產生 n*n 個格子): ";
    std::cin >> n;

    if (n <= 0) {
        std::cerr << "錯誤：表格大小必須大於 0。\n";
        return 1;
    }

    // 1. 建立 n*n 的空表格，初始值皆為 0
    std::vector<std::vector<int> > grid(n, std::vector<int>(n, 0));
    std::cout << "\n[系統] 已建立 " << n << " x " << n << " 的空表格。";
    displayGrid(grid, n);

    // 2. 讓 Coding (程式) 自動在格子內輸入數字
    // 範例：程式自動將對角線上的格子填入 8
    //std::cout << "\n[系統訊息] 執行程式內部寫入：將對角線格子填入 8...\n";
    //for (int i = 0; i < n; ++i) {
    //    grid[i][i] = 8; // 程式直接透過索引修改數值
    //}
    //displayGrid(grid, n);

    // 3. 讓使用者（人）在格子內輸入數字
    std::cout << "\n現在您可以手動修改格子內的數字。\n";
    while (true) {
        int row, col, val;
        std::cout << "請輸入要修改的座標 (列 行) 與 數值 [輸入 -1 -1 -1 結束]: ";
        std::cin >> row >> col >> val;

        // 結束條件
        if (row == -1 && col == -1 && val == -1) {
            std::cout << "程式結束。\n";
            break;
        }

        // 檢查座標邊界，避免記憶體溢位
        if (row >= 0 && row < n && col >= 0 && col < n) {
            grid[row][col] = val; // 將人輸入的數字寫入指定格子
            displayGrid(grid, n);
        } else {
            std::cout << "錯誤：座標超出範圍，請重新輸入（座標範圍為 0 到 " << n - 1 << "）。\n";
        }
    }

    return 0;
}
