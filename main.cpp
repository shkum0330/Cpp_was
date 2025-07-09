#include <iostream>
#include <map>
#include <atomic>
#include <string>
#include "httplib.h"
#include "nlohmann/json.hpp"
using namespace std;

using json = nlohmann::json;

struct Post {
    int id;
    string title;
    string content;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Post, id, title, content);

// 인메모리 데이터베이스
map<int, Post> posts_db;
// id auto increment
atomic<int> next_post_id = 1;

int main() {
    // httplib 서버 객체 생성
    httplib::Server svr;

    // 새 게시글 생성 API
    svr.Post("/posts", [](const httplib::Request& req, httplib::Response& res) {
        try {
            // 요청 본문을 JSON으로 파싱
            json j = json::parse(req.body);

            // 새 Post 객체 생성
            Post new_post;
            new_post.id = next_post_id++; // id 자동 할당

            // title과 content를 JSON에서 가져와 할당
            new_post.title = j["title"].get<string>();
            new_post.content = j["content"].get<string>();

            // DB에 저장
            posts_db[new_post.id] = new_post;

            cout << "Post created: " << new_post.title << " (ID: " << new_post.id << ")" << endl;

            // 응답 설정
            res.status = 201; // 201 Created
            res.set_content(json(new_post).dump(), "application/json");

        } catch (const exception& e) {
            res.status = 400; // 400 Bad Request
            res.set_content(R"({"error": "Invalid JSON format or missing 'title'/'content' fields"})", "application/json");
        }
    });

    // 모든 게시글 조회
    svr.Get("/posts", [](const httplib::Request& req, httplib::Response& res) {
        json j = json::array();
        for (const auto& pair : posts_db) {
            j.push_back(pair.second);
        }

        cout << "Fetched all " << posts_db.size() << " posts." << endl;

        // 응답 설정
        res.set_content(j.dump(), "application/json");
    });


    cout << "Server started at http://localhost:8080" << endl;
    svr.listen("0.0.0.0", 8080);

    return 0;
}