#include "lab_m1/tema1/tema1.h"

#include <vector>
#include <iostream>

#include "lab_m1/tema1/transform2D_t1.h"
#include "lab_m1/tema1/object2D_t1.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}

bool Tema1::IsBallSquareCollision(float ballx, float ballY, float radius, float squareX, float squareY, float sizeX, float sizeY)
{
    if (!((ballY - radius < squareY || ballY - 3 * radius > squareY + sizeY) ||
        ((ballY - radius > squareY && ballY - 3 * radius < squareY + sizeY) &&
            (ballx - radius < squareX ||
                ballx - 3 * radius > squareX + sizeX)) ||
        ((ballx - radius < squareX || ballx - 3 * radius > squareX + sizeX) ||
            ((ballx - radius > squareX && ballx - 3 * radius < squareX + sizeX) &&
                (ballY - radius < squareY ||
                    ballY - 3 * radius > squareY + sizeY)))))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Tema1::IsBallBallCollision(float ball1x, float ball1Y, float radius1, float ball2x, float ball2Y, float radius2)
{
    float dx = (ball1x)-(ball2x);
    float dy = (ball1Y)-(ball2Y);
    float distance = sqrt(dx * dx + dy * dy);
    if (distance < radius1 + radius2)
    {

        return true;
    }
    else
    {
        return false;
    }
}


void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    radiusCircle = 0.25f;
    timer = 0;
    enemyTime = 0;
    pickUpsTime = 0;


    speed = 0.2f;

    logicSpace.width = 4;   // logic width
    logicSpace.height = 4;  // logic height
    logicSpace.x = MAX_MAP / 2 - logicSpace.width / 2;       // logic x
    logicSpace.y = MAX_MAP / 2 - logicSpace.height / 2;       // logic y


    cx = radiusCircle / 2;
    cy = radiusCircle / 2;

    glm::vec3 cornerCircle = glm::vec3(-cx, -cy, 0);
    glm::vec3 cornerSquare = glm::vec3(0, 0, 0);

    // Initialize tx and ty (the translation steps)
    translateX = MAX_MAP / 2;
    translateY = MAX_MAP / 2;


    // Initialize angularStep
    angularStep = 0;


    shoot = false;

    radiusBullet = 0.05f;
    offset_healthBar = 0.1f;
    offset_body = radiusCircle / 2;

    pickUpRadius = 0.05f;

    offset_eye = radiusCircle / 2;


    x = 0.4f;
    y = 0.4f;
    nr_obj = 10 + rand() % 10;
    for (int i = 0; i < nr_obj; i++) {


        scaleX = 1 + rand() % 5;
        scaleY = 1 + rand() % 5;

        objX = rand() % (MAX_MAP - 1);
        objY = rand() % (MAX_MAP - 1);

        // pp ca si obstacolele sunt niste cercuri pentru a ne asigura ca nu se genereaza in zona centrala
        while (IsBallBallCollision(translateX, translateY, radiusCircle, objX + x * scaleX, objY + y * scaleY, max(x * scaleX, y * scaleY)))
        {
            objX = rand() % (MAX_MAP - 1);
            objY = rand() % (MAX_MAP - 1);

        }


        Point p;
        p.x = objX;
        p.y = objY;
        p.scaleX = scaleX;
        p.scaleY = scaleY;
        objects.push_back(p);

    }


    healthBarX = 0.5f;
    healthBarY = 1;
    healthLvlX = 0.5f;
    healthLvlY = 1;
    scaleY_healthLvl = 1;

    score = 0;
    cout << "START\n";
    cout << "Score: " << score << " \n";


    Mesh* bullet = object2D::CreateCircle("bullet", cornerCircle, radiusBullet, glm::vec3(0, 0, 0), 360, true);
    AddMeshToList(bullet);
    Mesh* square2 = object2D::CreateSquare("square2", cornerSquare, x, y, glm::vec3(0.2, 0.5, 1), true);
    AddMeshToList(square2);
    Mesh* square1 = object2D::CreateSquare("square1", cornerSquare, MAX_MAP, MAX_MAP, glm::vec3(0.7, 0.6, 0.9), true);
    AddMeshToList(square1);


    Mesh* pupil = object2D::CreateCircle("pupil", cornerCircle, 0.05f, glm::vec3(0.7, 0.3, 1), 360, true);
    AddMeshToList(pupil);
    Mesh* iris = object2D::CreateCircle("iris", cornerCircle, 0.09f, glm::vec3(0.2, 0.6, 0.8), 360, true);
    AddMeshToList(iris);
    Mesh* eyes_contur = object2D::CreateCircle("eyes_contur", cornerCircle, 0.1f, glm::vec3(0.3, 0.3, 1), 360, false);
    AddMeshToList(eyes_contur);
    Mesh* body = object2D::CreateCircle("body", cornerCircle, radiusCircle, glm::vec3(0.3, 1, 0.4), 360, true);
    AddMeshToList(body);


    Mesh* enemy_iris = object2D::CreateCircle("enemy_iris", cornerCircle, 0.05f, glm::vec3(1, 0, 0.1), 360, true);
    AddMeshToList(enemy_iris);
    Mesh* enemy_pupil = object2D::CreateCircle("enemy_pupil", cornerCircle, 0.025f, glm::vec3(0, 0, 0), 360, true);
    AddMeshToList(enemy_pupil);
    Mesh* enemy_eye = object2D::CreateCircle("enemy_eye", cornerCircle, 0.1f, glm::vec3(1, 0.5, 0.2), 360, true);
    AddMeshToList(enemy_eye);
    Mesh* enemy_body = object2D::CreateCircle("enemy_body", cornerCircle, radiusCircle, glm::vec3(1, 1, 1), 360, true);
    AddMeshToList(enemy_body);

    Mesh* pick_up = object2D::CreateCircle("pick_up", cornerCircle, pickUpRadius, glm::vec3(0.9, 1, 0), 360, true);
    AddMeshToList(pick_up);
    Mesh* pick_up1 = object2D::CreateCircle("pick_up1", cornerCircle, pickUpRadius, glm::vec3(1, 0, 0), 360, true);
    AddMeshToList(pick_up1);



    Mesh* healthBar = object2D::CreateSquare("healthBar", cornerSquare, healthBarX, healthBarY, glm::vec3(1, 0, 0), false);
    AddMeshToList(healthBar);

    Mesh* healthLvl = object2D::CreateSquare("healthLvl", cornerSquare, healthLvlX, healthLvlY, glm::vec3(0.1, 0.9, 0), true);
    AddMeshToList(healthLvl);


}

glm::mat3 Tema1::VisualizationTransf2DUnif(const LogicSpace& logicSpace, const ViewportSpace& viewSpace)
{
    float sx, sy, tx, ty, smin;
    sx = viewSpace.width / logicSpace.width;
    sy = viewSpace.height / logicSpace.height;
    if (sx < sy)
        smin = sx;
    else
        smin = sy;
    tx = viewSpace.x - smin * logicSpace.x + (viewSpace.width - smin * logicSpace.width) / 2;
    ty = viewSpace.y - smin * logicSpace.y + (viewSpace.height - smin * logicSpace.height) / 2;

    return glm::transpose(glm::mat3(
        smin, 0.0f, tx,
        0.0f, smin, ty,
        0.0f, 0.0f, 1.0f));
}


void Tema1::SetViewportArea(const ViewportSpace& viewSpace, glm::vec3 colorColor, bool clear)
{
    glViewport(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    glEnable(GL_SCISSOR_TEST);
    glScissor(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    glClearColor(colorColor.r, colorColor.g, colorColor.b, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);

    GetSceneCamera()->SetOrthographic((float)viewSpace.x, (float)(viewSpace.x + viewSpace.width), (float)viewSpace.y, (float)(viewSpace.y + viewSpace.height), 0.1f, 400);
    GetSceneCamera()->Update();
}


void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema1::Update(float deltaTimeSeconds)
{
    viewSpace = ViewportSpace(0, 0, resolution1.x, resolution1.y);

    SetViewportArea(viewSpace, glm::vec3(0), true);

    visMatrix = glm::mat3(1);
    visMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);
    enemyTime -= deltaTimeSeconds;
    pickUpsTime -= deltaTimeSeconds;
    timer -= deltaTimeSeconds;
    if (pickUpsTime < 0)
    {
        PickUp p;
        p.x = 0.5f + rand() % (MAX_MAP - 1);
        p.y = 0.5f + rand() % (MAX_MAP - 1);
        p.remove = false;
        for (int i = 0; i < objects.size(); i++)
        {
            while (IsBallSquareCollision(p.x - pickUpRadius, p.y - pickUpRadius, pickUpRadius, objects[i].x, objects[i].y, x * objects[i].scaleX, y * objects[i].scaleY)) {
                p.x = 0.5f + rand() % (MAX_MAP - 1);
                p.y = 0.5f + rand() % (MAX_MAP - 1);
            }
        }
        pickUps.push_back(p);
        pickUpsTime = 6;
    }

    if (enemyTime < 0) {
        Enemy e;
        e.x = 0.5f + rand() % (MAX_MAP - 1);
        e.y = 0.5f + rand() % (MAX_MAP - 1);
        while (IsBallBallCollision(e.x, e.y, radiusCircle, translateX, translateY, radiusCircle))
        {
            e.x = 0.5f + rand() % (MAX_MAP - 1);
            e.y = 0.5f + rand() % (MAX_MAP - 1);

        }
        e.speed = 0.2f + (rand()) / (RAND_MAX / (1 - 0.2f));
        e.remove = false;
        x1 = e.x - translateX;
        y1 = e.y - translateY;
        e.alpha = (float)atan2(y1, x1) - (float)M_PI / 2;
        enemyTime = 3;
        enemys.push_back(e);
    }

    DrawScene(visMatrix);
}

void Tema1::DrawScene(glm::mat3 visMatrix)
{
    modelMatrix = glm::mat3(1);
    modelMatrix = visMatrix * transform2D::Translate(translateX + 3 * logicSpace.width / 4 - offset_healthBar, translateY - logicSpace.width / 2 + offset_healthBar);
    RenderMesh2D(meshes["healthBar"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix = visMatrix * transform2D::Translate(translateX + 3 * logicSpace.width / 4 - offset_healthBar, translateY - logicSpace.width / 2 + offset_healthBar);
    modelMatrix *= transform2D::Scale(1, scaleY_healthLvl);
    RenderMesh2D(meshes["healthLvl"], shaders["VertexColor"], modelMatrix);


    righteye = glm::mat3(1);
    righteye *= visMatrix * transform2D::Translate(translateX - offset_eye, translateY - offset_eye);
    righteye *= transform2D::Rotate(angularStep + M_PI / 2);
    RenderMesh2D(meshes["pupil"], shaders["VertexColor"], righteye);

    lefteye = glm::mat3(1);
    lefteye *= visMatrix * transform2D::Translate(translateX - offset_eye, translateY - offset_eye);
    lefteye *= transform2D::Rotate(angularStep);
    RenderMesh2D(meshes["pupil"], shaders["VertexColor"], lefteye);

    RenderMesh2D(meshes["iris"], shaders["VertexColor"], righteye);
    RenderMesh2D(meshes["iris"], shaders["VertexColor"], lefteye);
    RenderMesh2D(meshes["eyes_contur"], shaders["VertexColor"], righteye);
    RenderMesh2D(meshes["eyes_contur"], shaders["VertexColor"], lefteye);


    body = glm::mat3(1);
    body *= visMatrix * transform2D::Translate(translateX, translateY);
    RenderMesh2D(meshes["body"], shaders["VertexColor"], body);


    for (int i = 0; i < enemys.size(); i++) {
        if (enemys[i].remove == false)
        {
            righteye = glm::mat3(1);
            righteye *= visMatrix * transform2D::Translate(enemys[i].x - offset_eye, enemys[i].y - offset_eye);
            righteye *= transform2D::Rotate(enemys[i].alpha + M_PI / 2);
            RenderMesh2D(meshes["enemy_pupil"], shaders["VertexColor"], righteye);



            lefteye = glm::mat3(1);
            lefteye *= visMatrix * transform2D::Translate(enemys[i].x - offset_eye, enemys[i].y - offset_eye);
            lefteye *= transform2D::Rotate(enemys[i].alpha);
            RenderMesh2D(meshes["enemy_pupil"], shaders["VertexColor"], lefteye);

            righteye = glm::mat3(1);
            righteye *= visMatrix * transform2D::Translate(enemys[i].x - offset_eye, enemys[i].y - offset_eye);
            righteye *= transform2D::Rotate(enemys[i].alpha + M_PI / 2);
            RenderMesh2D(meshes["enemy_iris"], shaders["VertexColor"], righteye);



            lefteye = glm::mat3(1);
            lefteye *= visMatrix * transform2D::Translate(enemys[i].x - offset_eye, enemys[i].y - offset_eye);
            lefteye *= transform2D::Rotate(enemys[i].alpha);
            RenderMesh2D(meshes["enemy_iris"], shaders["VertexColor"], lefteye);

            righteye = glm::mat3(1);
            righteye *= visMatrix * transform2D::Translate(enemys[i].x - offset_eye, enemys[i].y - offset_eye);
            righteye *= transform2D::Rotate(enemys[i].alpha + M_PI / 2);
            RenderMesh2D(meshes["enemy_eye"], shaders["VertexColor"], righteye);


            lefteye = glm::mat3(1);
            lefteye *= visMatrix * transform2D::Translate(enemys[i].x - offset_eye, enemys[i].y - offset_eye);
            lefteye *= transform2D::Rotate(enemys[i].alpha);
            RenderMesh2D(meshes["enemy_eye"], shaders["VertexColor"], lefteye);


            modelMatrix = glm::mat3(1);
            modelMatrix = visMatrix * transform2D::Translate(enemys[i].x, enemys[i].y);
            RenderMesh2D(meshes["enemy_body"], shaders["VertexColor"], modelMatrix);
        }
    }

    for (int i = 0; i < nr_obj; i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= visMatrix * transform2D::Translate(objects[i].x, objects[i].y);
        modelMatrix *= transform2D::Scale(objects[i].scaleX, objects[i].scaleY);
        RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
    }

    for (int i = 0; i < bullets.size(); i++)
    {
        if (bullets[i].remove == false)
        {
            modelMatrix = glm::mat3(1);
            modelMatrix = visMatrix * transform2D::Translate(bullets[i].x, bullets[i].y);
            RenderMesh2D(meshes["bullet"], shaders["VertexColor"], modelMatrix);
        }

    }

    for (int i = 0; i < pickUps.size(); i++)
    {
        if (pickUps[i].remove == false)
        {
            modelMatrix = glm::mat3(1);
            modelMatrix = visMatrix * transform2D::Translate(pickUps[i].x, pickUps[i].y);
            RenderMesh2D(meshes["pick_up"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat3(1);
            modelMatrix = visMatrix * transform2D::Translate(pickUps[i].x + 0.05f, pickUps[i].y + 0.05f);
            RenderMesh2D(meshes["pick_up1"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat3(1);
            modelMatrix = visMatrix * transform2D::Translate(pickUps[i].x + 0.05f, pickUps[i].y - 0.05f);
            RenderMesh2D(meshes["pick_up1"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat3(1);
            modelMatrix = visMatrix * transform2D::Translate(pickUps[i].x - 0.05f, pickUps[i].y + 0.05f);
            RenderMesh2D(meshes["pick_up1"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat3(1);
            modelMatrix = visMatrix * transform2D::Translate(pickUps[i].x - 0.05f, pickUps[i].y - 0.05f);
            RenderMesh2D(meshes["pick_up1"], shaders["VertexColor"], modelMatrix);
        }

    }

    modelMatrix = glm::mat3(1);
    modelMatrix = visMatrix * transform2D::Translate(0, 0);
    RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);
}


void Tema1::FrameEnd()
{
    DrawCoordinateSystem();
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
    int ok_bulletX = 0;
    int ok_bulletY = 0;
    int ok_A = 0;
    int ok_S = 0;
    int ok_D = 0;
    int ok_W = 0;
    float dist = deltaTime;

    float player_speed = 1;
    bool bullet_enemy_collision = true;


    if (window->KeyHold(GLFW_KEY_A)) {
        if (translateX - radiusCircle - offset_body >= 0)
        {
            for (int i = 0; i < nr_obj; i++) {

                if ((translateY + offset_body <= objects[i].y ||
                    translateY - radiusCircle - offset_body >= objects[i].y + y * objects[i].scaleY) ||
                    ((translateY + offset_body >= objects[i].y &&
                        translateY - radiusCircle - offset_body <= objects[i].y + y * objects[i].scaleY) &&
                        (translateX - dist + offset_body <= objects[i].x ||
                            translateX - dist - radiusCircle - offset_body >= objects[i].x + x * objects[i].scaleX)))

                {
                    ok_A++;
                }
            }
            if (ok_A == nr_obj)
            {
                translateX -= player_speed * deltaTime;
                ok_A = 0;
                logicSpace.x -= player_speed * deltaTime;

            }
        }

    }
    if (window->KeyHold(GLFW_KEY_D)) {
        if (translateX + offset_body <= MAX_MAP)
        {
            for (int i = 0; i < nr_obj; i++) {

                if ((translateY + offset_body <= objects[i].y ||
                    translateY - radiusCircle - offset_body >= objects[i].y + y * objects[i].scaleY) ||
                    ((translateY + offset_body >= objects[i].y &&
                        translateY - radiusCircle - offset_body <= objects[i].y + y * objects[i].scaleY) &&
                        (translateX + dist + offset_body <= objects[i].x ||
                            translateX + dist - radiusCircle - offset_body >= objects[i].x + x * objects[i].scaleX)))
                {
                    ok_D++;

                }


            }
            if (ok_D == nr_obj)
            {
                translateX += player_speed * deltaTime;
                ok_D = 0;
                logicSpace.x += player_speed * deltaTime;



            }
        }
    }
    if (window->KeyHold(GLFW_KEY_W)) {
        if (translateY + offset_body <= MAX_MAP) {
            for (int i = 0; i < nr_obj; i++) {

                if ((translateX + offset_body <= objects[i].x ||
                    translateX - radiusCircle - offset_body >= objects[i].x + x * objects[i].scaleX) ||
                    ((translateX + offset_body >= objects[i].x &&
                        translateX - radiusCircle - offset_body <= objects[i].x + x * objects[i].scaleX) &&
                        (translateY + dist + offset_body <= objects[i].y ||
                            translateY + dist - radiusCircle - offset_body >= objects[i].y + y * objects[i].scaleY)))
                {
                    ok_W++;
                }

            }
            if (ok_W == nr_obj)
            {
                translateY += player_speed * deltaTime;
                logicSpace.y += player_speed * deltaTime;
                ok_W = 0;



            }
        }
    }
    if (window->KeyHold(GLFW_KEY_S)) {
        if (translateY - radiusCircle - offset_body >= 0) {
            for (int i = 0; i < nr_obj; i++) {


                if ((translateX + offset_body <= objects[i].x ||
                    translateX - radiusCircle - offset_body >= objects[i].x + x * objects[i].scaleX) ||
                    ((translateX + offset_body >= objects[i].x &&
                        translateX - radiusCircle - offset_body <= objects[i].x + x * objects[i].scaleX) &&
                        (translateY - dist + offset_body <= objects[i].y ||
                            translateY - dist - radiusCircle - offset_body >= objects[i].y + y * objects[i].scaleY)))

                {
                    ok_S++;
                }

            }
            if (ok_S == nr_obj)
            {
                translateY -= player_speed * deltaTime;
                ok_S = 0;
                logicSpace.y -= player_speed * deltaTime;



            }
        }
    }

    if (window->KeyHold(GLFW_KEY_Z)) {
        logicSpace.height -= deltaTime;
        logicSpace.width -= deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_X)) {
        logicSpace.height += deltaTime;
        logicSpace.width += deltaTime;
    }

    for (int j = 0; j < enemys.size(); j++)
    {
        x1 = enemys[j].x - translateX;
        y1 = enemys[j].y - translateY;
        enemys[j].alpha = (float)atan2(y1, x1) - M_PI / 2;
        enemys[j].x -= (float)deltaTime * enemys[j].speed * (float)cos(enemys[j].alpha + M_PI / 2);
        enemys[j].y -= (float)deltaTime * enemys[j].speed * (float)sin(enemys[j].alpha + M_PI / 2);
    }

    for (int i = 0; i < pickUps.size(); i++)
    {
        if (pickUps[i].remove == false)
        {
            if (IsBallBallCollision(pickUps[i].x, pickUps[i].y, pickUpRadius,
                translateX, translateY, radiusCircle))
            {
                pickUps[i].remove = true;
                if (scaleY_healthLvl < 1.0f)
                {
                    scaleY_healthLvl += 0.2f;
                }
            }
        }
    }


    //coliziune inamci - player
    for (int i = 0; i < enemys.size(); i++) {
        if (enemys[i].remove == false)
        {
            if (IsBallBallCollision(enemys[i].x, enemys[i].y, radiusCircle, translateX, translateY, radiusCircle))
            {
                enemys[i].remove = true;
                scaleY_healthLvl -= 0.2f;
                if (scaleY_healthLvl <= 0.01f)
                {
                    cout << "!!GAME OVER!!\n";
                    score = 0;
                    cout << "START\n";
                    cout << "Score: " << score << "\n";
                    //jocul o ia de la inceput
                    scaleY_healthLvl = 1;
                    translateX = MAX_MAP / 2;
                    translateY = MAX_MAP / 2;
                    logicSpace.x = MAX_MAP / 2 - logicSpace.width / 2;       // logic x
                    logicSpace.y = MAX_MAP / 2 - logicSpace.height / 2;       // logic y
                    enemys.clear();
                    bullets.clear();
                    pickUps.clear();

                }

            }
        }

    }
    // inamic - perete
    for (int i = 0; i < enemys.size(); i++) {
        if (enemys[i].remove == false)
        {
            if (0 >= enemys[i].x - (float)radiusCircle - offset_body ||
                enemys[i].x + offset_body >= MAX_MAP ||
                0 >= enemys[i].y - radiusCircle - (float)offset_body ||
                enemys[i].y + offset_body >= MAX_MAP)
            {
                enemys[i].remove = true;
            }
        }

    }

    //coliziune inamic - proiectil
    // proiectil - harta
    // proiectil - obstacole
    for (int k = 0; k < bullets.size(); k++)
    {
        if (bullets[k].remove == false)
        {
            if (bullets[k].ttl > MAX_TTL)
            {
                bullets[k].remove = true;

            }
            else
            {
                if ((bullets[k].x - 4 * radiusBullet > 0 && bullets[k].x < MAX_MAP) &&
                    (bullets[k].y - 4 * radiusBullet > 0 && bullets[k].y < MAX_MAP))
                {
                    for (int i = 0; i < nr_obj; i++) {

                        if (!IsBallSquareCollision(bullets[k].x, bullets[k].y, radiusBullet, objects[i].x,
                            objects[i].y, x * objects[i].scaleX, y * objects[i].scaleY))

                        {

                            for (int a = 0; a < enemys.size(); a++)
                            {
                                if (enemys[a].remove == false)
                                {

                                    if (IsBallBallCollision(bullets[k].x, bullets[k].y, radiusCircle,
                                        enemys[a].x, enemys[a].y, radiusBullet))
                                    {
                                        score += 10;
                                        cout << "Score: " << score << "\n";
                                        bullets[k].remove = true;
                                        enemys[a].remove = true;
                                    }
                                }

                            }

                            bullets[k].x += deltaTime * speed * cos(bullets[k].alpha);
                            bullets[k].y += deltaTime * speed * sin(bullets[k].alpha);
                            bullets[k].ttl += deltaTime;


                        }
                        else
                        {
                            bullets[k].remove = true;
                        }
                    }

                }
                else
                {
                    bullets[k].remove = true;
                }
            }
        }
    }


}


void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
    /*if (key == GLFW_KEY_SPACE)
    {
        switch (polygonMode)
        {
        case GL_POINT:
            polygonMode = GL_FILL;
            break;
        case GL_LINE:
            polygonMode = GL_POINT;
            break;
        default:
            polygonMode = GL_LINE;
            break;
        }
    }*/
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
    x1 = (float)mouseX - resolution1.x / 2;
    y1 = resolution1.y / 2 - (float)mouseY;
    angularStep = (float)atan2(y1, x1) + M_PI / 2;
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
    if (timer <= 0)
    {
        if (window->MouseHold(GLFW_MOUSE_BUTTON_LEFT))
        {


            Bullet b;
            b.remove = false;
            b.ttl = 0;

            x1 = (float)mouseX - resolution1.x / 2;
            y1 = resolution1.y / 2 - (float)mouseY;
            b.x = translateX;
            b.y = translateY;
            b.alpha = (float)atan2(y1, x1);
            bullets.push_back(b);
            //delay pt bullets
            timer = 0.6f;
        }
    }

}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}
