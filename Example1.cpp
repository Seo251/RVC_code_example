//[ObstacleSensor클래스를 만들지 않을 때]//

#include <iostream>
#include <vector>

// enum class를 사용하여 위치를 명확하게 표현
enum class Location {
    FORWARD,
    REAR,
    LEFT,
    RIGHT
};

// 센서 데이터 구조체
struct SensorData {
    Location location;
    bool isBlocked;
};

// 장애물 센서 클래스 (하드웨어 인터페이스 역할)
class ObstacleSensor {
private:
    int pinNumber;
    int value; // 실제 하드웨어에서 읽어온 거리 값이라고 가정

public:
    ObstacleSensor(int pin, int initialValue = 0)
        : pinNumber(pin), value(initialValue) {
    }

    // 센서 값을 읽어오는 오퍼레이션
    int getSensorValue() {
        // 실제 로봇 청소기 환경이라면 여기에 하드웨어 I/O 통신 코드가 들어감
        // 현재는 내부 변수 값을 반환하는 것으로 시뮬레이션함
        return value;
    }
};

// 센서 데이터 변환 클래스
class SensorDataConverter {
private:
    // 집합 관계(Aggregation, ◇): 센서의 생명 주기를 관리하지 않고 참조만 하도록 포인터 사용
    ObstacleSensor* frontSensor;
    ObstacleSensor* leftSensor;
    ObstacleSensor* rightSensor;

    // 판단 기준 상수
    const int OBSTACLE_DISTANCE_THRESHOLD = 100;

public:

    // 생성자 (외부에서 생성된 센서 객체들의 주소를 받음)
    SensorDataConverter(ObstacleSensor* front, ObstacleSensor* left, ObstacleSensor* right)
        : frontSensor(front), leftSensor(left), rightSensor(right) {
    }

    // 장애물센서 객체들의 값을 모아 구조체 배열(vector)로 변환
    std::vector<SensorData> formatData() {
        std::vector<SensorData> dataList;

        // 각 센서가 연결되어 있는지(nullptr가 아닌지) 확인 후 데이터 추출 및 구조체 생성
        // 컨버터가 각 센서 객체의 물리적 위치(Location)를 매핑해줌
        if (frontSensor) {
            dataList.push_back({ Location::FORWARD, frontSensor->getSensorValue() < OBSTACLE_DISTANCE_THRESHOLD });
        }
        if (leftSensor) {
            dataList.push_back({ Location::LEFT, leftSensor->getSensorValue() < OBSTACLE_DISTANCE_THRESHOLD });
        }
        if (rightSensor) {
            dataList.push_back({ Location::RIGHT, rightSensor->getSensorValue() < OBSTACLE_DISTANCE_THRESHOLD });
        }

        return dataList;
    }
};

int main() {
    // 로봇 청소기 기판의 1번, 2번, 3번 핀에 센서를 꽂았다고 가정
    ObstacleSensor sensorA(1); // front sensor
    ObstacleSensor sensorB(2); // left sensor
    ObstacleSensor sensorC(3); // right sensor

    // Step 2: 컨버터에 조립 (의미 부여)
    // 1번 핀(sensorA)을 정면으로, 2번(sensorB)을 좌측으로, 3번(sensorC)을 우측으로 매핑
    SensorDataConverter converter(&sensorA, &sensorB, &sensorC);

    // Step 3: 컨트롤러가 사용할 규격화된 데이터로 변환 (핵심 로직)
    std::vector<SensorData> results = converter.formatData();

}
