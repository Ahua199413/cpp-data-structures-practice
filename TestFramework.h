#pragma once
#include <iostream>
#include <string>

// 全域計數器
static int g_tests_run = 0;
static int g_tests_failed = 0;

// 測試套件名稱
static std::string g_current_suite = "";

// 測試比較巨集 (保持不變)
#define TEST_EQUAL(expected, actual, test_name) \
    do { \
        g_tests_run++; \
        if ((expected) == (actual)) { \
            std::cout << "[PASS] [" << g_current_suite << "] " << test_name << std::endl; \
        } else { \
            g_tests_failed++; \
            std::cerr << "[FAIL] [" << g_current_suite << "] " << test_name \
                      << " - Expected: " << (expected) \
                      << ", Actual: " << (actual) << std::endl; \
        } \
    } while (0)

// 測試異常巨集 (保持不變)
#define TEST_EXCEPTION(statement, ExceptionType, test_name) \
    do { \
        g_tests_run++; \
        bool caught = false; \
        try { \
            statement; \
        } catch (const ExceptionType& e) { \
            caught = true; \
            std::cout << "[PASS] [" << g_current_suite << "] " << test_name << " (Caught " << #ExceptionType << ")" << std::endl; \
        } catch (...) {} \
        if (!caught) { \
            g_tests_failed++; \
            std::cerr << "[FAIL] [" << g_current_suite << "] " << test_name << " - Expected exception " << #ExceptionType << " was not thrown." << std::endl; \
        } \
    } while (0)

// ==========================================================
// 測試套件管理巨集 (公用方法)
// 這是您在 main.cpp 中組織測試的方法
// ==========================================================

// 開始一個測試套件 (例如：TEST_SUITE(Core_Logic_Test))
#define TEST_SUITE(suite_name) \
    void suite_name() { \
        g_current_suite = #suite_name; \
        std::cout << "\n======================================" << std::endl; \
        std::cout << "Starting Test Suite: " << g_current_suite << std::endl; \
        std::cout << "======================================" << std::endl;

// 結束測試套件 (在函式末尾呼叫)
#define END_SUITE }

// 測試報告函式 (保持不變)
void print_test_report() {
    std::cout << "\n=======================================" << std::endl;
    std::cout << "Final Test Report" << std::endl;
    std::cout << "---------------------------------------" << std::endl;
    std::cout << "Total Tests Run: " << g_tests_run << std::endl;
    std::cout << "Tests Passed: " << (g_tests_run - g_tests_failed) << std::endl;
    std::cout << "Tests Failed: " << g_tests_failed << std::endl;
    std::cout << "=======================================" << std::endl;
}