# C++ 기반 RESTful API 서버

- `cpp-httplib`와 `nlohmann/json` 라이브러리를 사용하여 C++로 구현한 간단한 RESTful API 서버
- 인메모리 데이터베이스를 사용하여 게시글을 생성하고 조회하는 기능을 제공

## 주요 기능

- **게시글 생성**: HTTP POST 요청을 통해 새로운 게시글 생성
- **게시글 조회**: HTTP GET 요청을 통해 저장된 모든 게시글 목록 조회
- **JSON 형식 지원**: 요청과 응답의 본문(body)은 JSON 형식 사용

## 사용된 라이브러리

 CMake의 `FetchContent` 기능을 통해 다음 라이브러리들을 자동으로 다운로드하고 빌드

- **nlohmann/json (v3.11.2)**: C++을 위한 JSON 라이브러리
- **cpp-httplib (v0.15.3)**: C++11 기반의 단일 헤더 파일로 구성된 크로스 플랫폼 HTTP/HTTPS 라이브러리

## API 사용법

### 1. 새 게시글 생성

`curl`을 사용하여 `POST /posts` 엔드포인트에 요청을 보내 새로운 게시글 생성

**응답 예시 (상태 코드: 201 Created)**

```json
{
  "id": 1,
  "title": "제목",
  "content": "내용"
}
```

### 2. 모든 게시글 조회

`GET /posts` 엔드포인트로 요청을 보내면 현재까지 생성된 모든 게시글의 목록 조회

**응답 예시**

```json
[
  {
    "id": 1,
    "title": "제목1",
    "content": "내용1"
  },
  {
    "id": 2,
    "title": "제목2",
    "content": "내용2"
  }
]
```
