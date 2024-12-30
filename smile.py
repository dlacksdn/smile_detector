import cv2
from PIL import Image, ImageDraw, ImageFont
import numpy as np

# Haar Cascade 파일 경로
face_cascade_path = 'haarcascade_frontalface_default.xml'
smile_cascade_path = 'haarcascade_smile.xml'

# Cascade 분류기 로드
face_cascade = cv2.CascadeClassifier(face_cascade_path)
smile_cascade = cv2.CascadeClassifier(smile_cascade_path)

# 웹캠 열기 (기본 카메라)
cap = cv2.VideoCapture(0)

if not cap.isOpened():
    print("웹캠을 열 수 없습니다.")
    exit()

# 한글 글꼴 설정 (글꼴 파일 경로를 지정하세요)
font_path = 'HMKMMAG.TTF'  # 글꼴 파일 이름 또는 전체 경로
font_size = 32

# 폰트 객체 생성
font = ImageFont.truetype(font_path, font_size)

while True:
    # 프레임 읽기
    ret, frame = cap.read()
    if not ret:
        print("프레임을 읽을 수 없습니다.")
        break

    # 그레이스케일로 변환
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    # 얼굴 검출
    faces = face_cascade.detectMultiScale(
        gray,
        scaleFactor=1.3,
        minNeighbors=5,
        minSize=(60, 60)
    )

    smile_detected = False

    for (x, y, w, h) in faces:
        # 얼굴 영역에 사각형 그리기
        cv2.rectangle(frame, (x, y), (x + w, y + h), (255, 0, 0), 2)

        # 얼굴 영역 추출
        roi_gray = gray[y:y + h, x:x + w]
        roi_color = frame[y:y + h, x:x + w]

        # 미소 검출
        smiles = smile_cascade.detectMultiScale(
            roi_gray,
            scaleFactor=1.7,
            minNeighbors=22,
            minSize=(25, 25)
        )

        if len(smiles) > 0:
            smile_detected = True
            # 첫 번째 미소에 사각형 그리기
            for (sx, sy, sw, sh) in smiles:
                cv2.rectangle(roi_color, (sx, sy), (sx + sw, sy + sh), (0, 255, 0), 2)
                break  # 하나만 표시

    # 메시지 설정
    if smile_detected:
        message = "당신은 미소천사!"
        color = (0, 255, 0)  # 초록색
    else:
        message = "다시 한번 미소를 지어볼까요?"
        color = (0, 0, 255)  # 빨간색

    # OpenCV 이미지를 PIL 이미지로 변환
    pil_img = Image.fromarray(cv2.cvtColor(frame, cv2.COLOR_BGR2RGB))
    draw = ImageDraw.Draw(pil_img)

    # 메시지 위치 설정
    text_position = (10, 10)  # (x, y) 좌표

    # 텍스트 그리기
    draw.text(text_position, message, font=font, fill=color)

    # PIL 이미지를 다시 OpenCV 이미지로 변환
    frame = cv2.cvtColor(np.array(pil_img), cv2.COLOR_RGB2BGR)

    # 결과 프레임 표시
    cv2.imshow('Smile Detector', frame)

    # 'q' 키를 누르면 종료
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# 자원 해제
cap.release()
cv2.destroyAllWindows()
