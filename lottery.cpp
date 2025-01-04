#include <iostream>
#include <vector>
#include <algorithm> // shuffle, sort
#include <random>    // mt19937
#include <chrono>    // time_based seed

using namespace std; // std 네임스페이스 사용

int main() {
    // 1. 복권 숫자 범위 설정 (예: 1부터 20까지)
    int min_number = 1;   // 최소 숫자
    int max_number = 15;  // 최대 숫자
    int selection_count = 8; // 뽑을 숫자의 개수 (최대 10개)

    // 1.1. 유효성 검사: 뽑는 개수가 범위 내에 있는지 확인
    if (selection_count > (max_number - min_number + 1)) {
        cerr << "오류: 뽑는 개수가 숫자 범위를 초과했습니다.\n";
        return 1;
    }

    // 2. 숫자 벡터 초기화
    vector<int> numbers;
    for (int i = min_number; i <= max_number; ++i) {
        numbers.push_back(i);
    }

    // 3. 난수 생성기 초기화
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    mt19937 gen(seed);

    // 4. 벡터 섞기
    shuffle(numbers.begin(), numbers.end(), gen);

    // 5. 원하는 개수만큼 선택
    vector<int> selected_numbers(numbers.begin(), numbers.begin() + selection_count);

    // 6. 순서를 나타내는 한국어 어휘 (열 번째까지 확장)
    vector<string> ordinals = {
        "첫 번째", "두 번째", "세 번째", "네 번째", "다섯 번째",
        "여섯 번째", "일곱 번째", "여덟 번째", "아홉 번째", "열 번째"
    };

    // 7. 선택 개수가 ordinals 배열 크기를 초과하지 않는지 확인
    if (selection_count > ordinals.size()) {
        cerr << "오류: ordinals 배열의 크기를 초과했습니다.\n";
        return 1;
    }

    // 8. 안내 메시지 출력 (숫자 범위와 뽑는 개수 포함)
    cout << "꿈아 복권 추첨 시작하겠습니다!! "
        << "(숫자 범위 : " << min_number << "~" << max_number << ") / "
        << "(뽑는 개수 : " << selection_count << "개)\n";

    // 9. 각 숫자를 순차적으로 출력 (사용자가 Enter 키를 누를 때마다)
    for (int i = 0; i < selection_count; ++i) {
        cin.get(); // Enter 키 입력 대기
        cout << ordinals[i] << " 숫자 : " << selected_numbers[i] << '\n';
    }

    // 10. 선택된 숫자들을 오름차순으로 정렬
    vector<int> sorted_numbers = selected_numbers; // 원본 보존을 위해 복사
    sort(sorted_numbers.begin(), sorted_numbers.end());

    // 11. 최종 번호 출력
    cout << "\n최종 번호 : ";
    for (auto num : sorted_numbers) {
        cout << num << ' ';
    }
    cout << '\n';

    return 0;
}
