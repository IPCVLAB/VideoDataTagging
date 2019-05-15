# VideoDataTagging
비디오 데이터 테깅 예시 프로그램

# 현재 프로그램은 GPU가 없을 시 작동하지 않음

# 필요 파일 
- 파이썬 3.6 버젼 이상
- CUDA 9.0
- Visual Studio 2015 이상
- chromedriver

# 실행 방법
- pip install selenium 을 통해 selenium 설치
- https://drive.google.com/file/d/1U0AFevO3MvEbLDzJVJ3ag-IlsEftCF0Y/view?usp=sharing 에서 필요한 dll 및 lib 다운
- https://drive.google.com/file/d/1eGGTXGOJZYhWJh0K2lR5l9BEXH-y2Izk/view?usp=sharing 에서 딥러닝 모델 및 웨이트 파일 다운
- dll_lib, yolo 폴더 안에 있는 모든 파일을 /VideoDataTagging/basicVideoPlayer에 복사
- /VideoDataTagging/basicVideoPlayer 폴더에 result 폴더 생성
- VideoDataTagging 폴더 안에 basicVideoPlayer.sln 선택 후 release 모드 / x64 솔루션 플랫폼으로 빌드
- 빌드 후 VideoDataTagging/x64/Release 모드에 crawling.py, GoogleImageSearch.py, chromedriver 복사
- basicVideoPlayer.sln 에서 디버그하지 않고 시작(ctrl + f5)
- Text 박스에 검색  Frame 수를 입력하고 Open 버튼을 눌려 원하는 동영상을 클릭
