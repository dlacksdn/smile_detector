#include <iostream>
#include <vector>
#include <algorithm> // shuffle, sort
#include <random>    // mt19937
#include <chrono>    // time_based seed

using namespace std; // std ���ӽ����̽� ���

int main() {
    // 1. ���� ���� ���� ���� (��: 1���� 20����)
    int min_number = 1;   // �ּ� ����
    int max_number = 15;  // �ִ� ����
    int selection_count = 8; // ���� ������ ���� (�ִ� 10��)

    // 1.1. ��ȿ�� �˻�: �̴� ������ ���� ���� �ִ��� Ȯ��
    if (selection_count > (max_number - min_number + 1)) {
        cerr << "����: �̴� ������ ���� ������ �ʰ��߽��ϴ�.\n";
        return 1;
    }

    // 2. ���� ���� �ʱ�ȭ
    vector<int> numbers;
    for (int i = min_number; i <= max_number; ++i) {
        numbers.push_back(i);
    }

    // 3. ���� ������ �ʱ�ȭ
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    mt19937 gen(seed);

    // 4. ���� ����
    shuffle(numbers.begin(), numbers.end(), gen);

    // 5. ���ϴ� ������ŭ ����
    vector<int> selected_numbers(numbers.begin(), numbers.begin() + selection_count);

    // 6. ������ ��Ÿ���� �ѱ��� ���� (�� ��°���� Ȯ��)
    vector<string> ordinals = {
        "ù ��°", "�� ��°", "�� ��°", "�� ��°", "�ټ� ��°",
        "���� ��°", "�ϰ� ��°", "���� ��°", "��ȩ ��°", "�� ��°"
    };

    // 7. ���� ������ ordinals �迭 ũ�⸦ �ʰ����� �ʴ��� Ȯ��
    if (selection_count > ordinals.size()) {
        cerr << "����: ordinals �迭�� ũ�⸦ �ʰ��߽��ϴ�.\n";
        return 1;
    }

    // 8. �ȳ� �޽��� ��� (���� ������ �̴� ���� ����)
    cout << "�޾� ���� ��÷ �����ϰڽ��ϴ�!! "
        << "(���� ���� : " << min_number << "~" << max_number << ") / "
        << "(�̴� ���� : " << selection_count << "��)\n";

    // 9. �� ���ڸ� ���������� ��� (����ڰ� Enter Ű�� ���� ������)
    for (int i = 0; i < selection_count; ++i) {
        cin.get(); // Enter Ű �Է� ���
        cout << ordinals[i] << " ���� : " << selected_numbers[i] << '\n';
    }

    // 10. ���õ� ���ڵ��� ������������ ����
    vector<int> sorted_numbers = selected_numbers; // ���� ������ ���� ����
    sort(sorted_numbers.begin(), sorted_numbers.end());

    // 11. ���� ��ȣ ���
    cout << "\n���� ��ȣ : ";
    for (auto num : sorted_numbers) {
        cout << num << ' ';
    }
    cout << '\n';

    return 0;
}
