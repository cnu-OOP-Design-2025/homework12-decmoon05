#pragma once // 헤더 중복 방지
#include <iostream>
#include <fstream>
#include <mutex>
#include <thread>
#include <string>
#include <memory>

class Logger {
private:
    static std::unique_ptr<Logger> instance;
    static std::mutex init_mtx;
    static std::mutex write_mtx;
    std::ofstream logFile;

    // 생성자: private으로 설정하여 외부 생성 차단
    Logger() {
        // Test 폴더가 없으면 에러가 날 수 있으나, 과제 조건에 맞춰 경로 지정
        logFile.open("Test/output2.txt", std::ios::trunc); 
        if (logFile.is_open()) {
            logFile << "[Init] Logger started." << std::endl;
        }
    }

public:
    // 소멸자
    ~Logger() {
        if (logFile.is_open()) {
            logFile << "[Shutdown] Logger closed." << std::endl;
            logFile.close();
        }
    }

    // Singleton Instance 반환
    static Logger* getInstance() {
        std::lock_guard<std::mutex> lock(init_mtx);
        if (instance == nullptr) {
            // unique_ptr의 생성자는 explicit이므로 new를 사용하여 초기화
            instance = std::unique_ptr<Logger>(new Logger());
        }
        return instance.get();
    }

    // 로그 기록
    void log(const std::string& message) {
        std::lock_guard<std::mutex> lock(write_mtx);
        if (logFile.is_open()) {
            logFile << message << std::endl;
        }
    }
};

// Static 멤버 변수 정의
std::unique_ptr<Logger> Logger::instance;
std::mutex Logger::init_mtx;
std::mutex Logger::write_mtx;