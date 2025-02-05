### 과제 내용


![image](https://github.com/user-attachments/assets/57e0beb8-0861-46ed-90aa-44f687ddb689) <br>

![image](https://github.com/user-attachments/assets/62731df9-8dea-4180-a2da-b5ef7006a2c9) <br>
---

### 과제 풀이

1. 서로 다른 두 개의 클래스 구현
   - AMovingActor, RotatingActor
   - 각각 '이동'과 '회전'을 담당하고 있음.
2. Tick 함수 기반 동적 Transform 변경 구현
   - DeltaTime 변수를 활용하여 프레임 독립적으로 구현
   - MoveSpeed, MaxRange 등의 변수를 활용하여 일정 범위 내에서 이동을 반복하는 오브젝트 구현.
   - 추가로 발생한 오버슈팅 문제에 대해 클램핑을 활용하여 문제 해결
3. 리플렉션 적용
   - 변수를 UPROPERTY로 선언하여 에디터 상에서 즉각적인 수정이 가능하게끔 구현
   - 편의를 위해 EditAnywhere / BluePrintReadWrite 접근 지정자를 적극적으로 활용함


![image](https://github.com/user-attachments/assets/e23e512c-fc1b-4bb4-aae7-99c44c3b5beb)
