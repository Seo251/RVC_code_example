//[ObstacleSensor클래스를 만들지 않을 때]//

#include <iostream>
#include <vector>

// enum class를 사용하여 위치를 명확하게 표현
enum class Location {
    FRONT,
    REAR,
    LEFT,
    RIGHT
};

// 센서 데이터 구조체
struct SensorData {
    Location location;
    bool isBlocked;
};

// 컨버터 클래스
class SensorDataConverter {
private:
    int frontPin;
    int leftPin;
    int rightPin;

    // 판단 기준값 내부 고정
    const int obstacleDistanceThreshold = 100;

    // 하드웨어 통신 전용 함수 (시뮬레이션 변수 제거)
    int getSensorValue(int pin) {
        // 실제 하드웨어의 센서 읽기 API 호출
        // 예시: return analogRead(pin);

        return 0; // 컴파일을 위한 임시 반환값
    }

public:
    // 생성자: 연결된 핀 번호만 주입받음
    SensorDataConverter(int fPin, int lPin, int rPin)
        : frontPin(fPin), leftPin(lPin), rightPin(rPin) {
    }

    // 하드웨어 값을 읽어와 구조체로 포장하는 핵심 기능
    std::vector<SensorData> formatData() {
        std::vector<SensorData> dataList;

        dataList.push_back({ Location::FRONT, readHardware(frontPin) < obstacleDistanceThreshold });
        dataList.push_back({ Location::LEFT,  readHardware(leftPin) < obstacleDistanceThreshold });
        dataList.push_back({ Location::RIGHT, readHardware(rightPin) < obstacleDistanceThreshold });

        return dataList;
    }
};

int main() {
    // 1. 시스템 초기화 시 센서 핀 번호 할당
    SensorDataConverter converter(1, 2, 3);

    // 2. 실시간 데이터 변환
    std::vector<SensorData> results = converter.formatData();

    return 0;
}