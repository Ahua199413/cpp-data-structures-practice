#pragma once
#include <iostream>
#include <string>

// ==========================================================
// ANSI 顏色代碼定義
// ==========================================================
#define ANSI_COLOR_RED "\x1b[31m"    // 失敗 (FAIL)
#define ANSI_COLOR_GREEN "\x1b[32m"  // 通過 (PASS)
#define ANSI_COLOR_YELLOW "\x1b[33m" // 警告/總結 (Summary)
#define ANSI_COLOR_CYAN "\x1b[36m"   // 標題 (Title)
#define ANSI_COLOR_RESET "\x1b[0m"   // 重置顏色 (必須加在結尾)
// ==========================================================
// 全域計數器
inline int g_tests_run = 0;
inline int g_tests_failed = 0;

// 測試套件名稱
inline std::string g_current_suite = "";

// 測試比較巨集 (保持不變)
#define TEST_EQUAL(expected, actual, test_name)                                     \
    do                                                                              \
    {                                                                               \
        g_tests_run++;                                                              \
        if ((expected) == (actual))                                                 \
        {                                                                           \
            std::cout << ANSI_COLOR_GREEN << "[PASS]" << ANSI_COLOR_RESET           \
                      << " [" << g_current_suite << "] " << test_name << std::endl; \
        }                                                                           \
        else                                                                        \
        {                                                                           \
            g_tests_failed++;                                                       \
            std::cerr << ANSI_COLOR_RED << "[FAIL]" << ANSI_COLOR_RESET             \
                      << " [" << g_current_suite << "] " << test_name               \
                      << " - Expected: " << (expected)                              \
                      << ", Actual: " << (actual) << std::endl;                     \
        }                                                                           \
    } while (0)

// 測試異常巨集 (保持不變)
#define TEST_EXCEPTION(statement, ExceptionType, test_name)                                                                                             \
    do                                                                                                                                                  \
    {                                                                                                                                                   \
        g_tests_run++;                                                                                                                                  \
        bool caught = false;                                                                                                                            \
        try                                                                                                                                             \
        {                                                                                                                                               \
            statement;                                                                                                                                  \
        }                                                                                                                                               \
        catch (const ExceptionType &e)                                                                                                                  \
        {                                                                                                                                               \
            caught = true;                                                                                                                              \
            std::cout << ANSI_COLOR_GREEN << "[PASS]" << ANSI_COLOR_RESET                                                                               \
                      << " [" << g_current_suite << "] " << test_name << " (Caught " << #ExceptionType << ")" << std::endl;                             \
        }                                                                                                                                               \
        catch (...)                                                                                                                                     \
        {                                                                                                                                               \
        }                                                                                                                                               \
        if (!caught)                                                                                                                                    \
        {                                                                                                                                               \
            g_tests_failed++;                                                                                                                           \
            std::cerr << ANSI_COLOR_RED << "[FAIL]" << ANSI_COLOR_RESET                                                                                 \
                      << " [" << g_current_suite << "] " << test_name << " - Expected exception " << #ExceptionType << " was not thrown." << std::endl; \
        }                                                                                                                                               \
    } while (0)

// ==========================================================
// 測試套件管理巨集 (公用方法)
// 這是您在 main.cpp 中組織測試的方法
// ==========================================================

// 開始一個測試套件 (例如：TEST_SUITE(Core_Logic_Test))
#define TEST_SUITE(suite_name)                                                                   \
    void suite_name()                                                                            \
    {                                                                                            \
        g_current_suite = #suite_name;                                                           \
        std::cout << ANSI_COLOR_CYAN << "\n======================================" << std::endl; \
        std::cout << "Starting Test Suite: " << g_current_suite << std::endl;                    \
        std::cout << "======================================" << ANSI_COLOR_RESET << std::endl;

// 結束測試套件 (在函式末尾呼叫)
#define END_SUITE }

// 測試報告函式 (更新顏色輸出)
void print_test_report()
{
    int passed = g_tests_run - g_tests_failed;

    // 如果有失敗，總結報告標題為紅色；否則為綠色
    const char *report_color = (g_tests_failed > 0) ? ANSI_COLOR_RED : ANSI_COLOR_GREEN;

    std::cout << report_color << "\n=======================================" << std::endl;
    std::cout << "Final Test Report" << std::endl;
    std::cout << "---------------------------------------" << std::endl;
    std::cout << "Total Tests Run: " << ANSI_COLOR_RESET << g_tests_run << report_color << std::endl;

    // 通過數目是綠色
    std::cout << "Tests Passed: " << ANSI_COLOR_GREEN << passed << report_color << std::endl;

    // 失敗數目是紅色 (如果 > 0)
    std::cout << "Tests Failed: " << ((g_tests_failed > 0) ? ANSI_COLOR_RED : ANSI_COLOR_GREEN) << g_tests_failed << report_color << std::endl;
    std::cout << "=======================================" << ANSI_COLOR_RESET << std::endl;
}