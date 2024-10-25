#pragma once

#include "components/simple_scene.h"

#define MAX_MAP 10
#define MAX_TTL 7

namespace m1 {
    class Tema1 : public gfxc::SimpleScene {
    public:
        struct ViewportSpace {
            ViewportSpace() : x(0), y(0), width(1), height(1) {}

            ViewportSpace(int x, int y, int width, int height)
                    : x(x), y(y), width(width), height(height) {}

            int x;
            int y;
            int width;
            int height;
        };

        struct LogicSpace {
            LogicSpace() : x(0), y(0), width(1), height(1) {}

            LogicSpace(float x, float y, float width, float height)
                    : x(x), y(y), width(width), height(height) {}

            float x;
            float y;
            float width;
            float height;
        };

    public:
        Tema1();

        ~Tema1();

        void Init() override;


    private:

        void FrameStart() override;

        void Update(float deltaTimeSeconds) override;

        void FrameEnd() override;

        void DrawScene(glm::mat3 visMatrix);

        glm::mat3 VisualizationTransf2DUnif(const LogicSpace &logicSpace, const ViewportSpace &viewSpace);

        bool IsBallBallCollision(float ball1x, float ball1Y, float radius1, float ball2x, float ball2Y, float radius2);

        bool IsBallSquareCollision(float ballx, float ballY, float radius, float squareX, float squareY, float sizeX,
                                   float sizeY);

        void SetViewportArea(const ViewportSpace &viewSpace, glm::vec3 colorColor = glm::vec3(0), bool clear = true);

        void Delay(float secs);

        void OnInputUpdate(float deltaTime, int mods) override;

        void OnKeyPress(int key, int mods) override;

        void OnKeyRelease(int key, int mods) override;

        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;

        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;

        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;

        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;

        void OnWindowResize(int width, int height) override;

    protected:
        float cx, cy;
        glm::mat3 modelMatrix, righteye, lefteye, body;
        float translateX, translateY;
        float scaleX, scaleY;
        float angularStep;

        // TODO(student): If you need any other class variables, define them here.
        glm::ivec2 resolution1;
        float x, y, x1, y1;
        float radiusCircle;
        float objX, objY;
        int nr_obj;
        struct Point {
            float x{};
            float y{};
            float scaleX{};
            float scaleY{};
        };

        struct Bullet {
            float x{};
            float y{};
            bool remove;
            float alpha{};
            float ttl;

        };

        struct Enemy {
            float x{};
            float y{};
            float alpha{};
            bool remove{};
            float speed{};
        };
        struct PickUp {
            float x{};
            float y{};
            bool remove{};

        };
        std::vector<Enemy> enemies;
        std::vector<PickUp> pickUps;
        std::vector<Point> objects;
        std::vector<Bullet> bullets;
        float enemyTime;
        float offset_body, offset_healthBar, radiusBullet;
        float healthLvlX, healthLvlY, healthBarX, healthBarY, scaleY_healthLvl;
        float pickUpRadius, pickUpsTime;
        int score;
        float speed;
        float eyeX, eyeY, offset_eye;

        float timer;
        ViewportSpace viewSpace;
        LogicSpace logicSpace;
        glm::mat3 visMatrix;


    };
}   // namespace m1
