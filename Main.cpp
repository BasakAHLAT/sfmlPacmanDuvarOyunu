// Ba?ak AHLAT & G?lfidan BALTACI - 2020

#include <SFML/Graphics.hpp>
#include <time.h>
#include<iostream>

using namespace sf;

const int SATIR = 25;
const int SUTUN = 40;

int cerceve[SATIR][SUTUN] = { 0 };
int karoBoyutu = 18;  //karo.png den sadece mavi k覺sm覺 almas覺 i癟in 18 olarak ayarland覺

struct Hayalet
{
    int x, y, dx, dy;

    Hayalet()
    {
        x = y = 300;
        dx = 4 - rand() % 8;
        dy = 4 - rand() % 8;
    }

    void hayaletHareket()
    {
        x += dx; if (cerceve[y / karoBoyutu][x / karoBoyutu] == 1) { dx = -dx; x += dx; }
        y += dy; if (cerceve[y / karoBoyutu][x / karoBoyutu] == 1) { dy = -dy; y += dy; }
    }
};

void drop(int y, int x)
{
    if (cerceve[y][x] == 0) cerceve[y][x] = -1;
    if (cerceve[y - 1][x] == 0) drop(y - 1, x);
    if (cerceve[y + 1][x] == 0) drop(y + 1, x);
    if (cerceve[y][x - 1] == 0) drop(y, x - 1);
    if (cerceve[y][x + 1] == 0) drop(y, x + 1);
   

}

int main()
{
    srand(time(0));

    RenderWindow window(VideoMode(SUTUN * karoBoyutu, SATIR * karoBoyutu), "PACMAN");
    window.setFramerateLimit(60);

    Texture KARO, GAMEOVER, KIRMIZIHAYALET, PEMBEHAYALET, MAV襤HAYALET, SARIHAYALET;
    KARO.loadFromFile("tiles.png");
    GAMEOVER.loadFromFile("gameover.png");
    KIRMIZIHAYALET.loadFromFile("kirmizihayalet.png");
    //PEMBEHAYALET.loadFromFile("pembehayalet.png");
    //MAV襤HAYALET.loadFromFile("mavihayalet.png");
    //SARIHAYALET.loadFromFile("sarihayalet.png");

    Sprite sKaro(KARO), sGameover(GAMEOVER), sHayalet1(KIRMIZIHAYALET), sHayalet2(PEMBEHAYALET);
    sGameover.setPosition(115, 50);
    sHayalet1.setOrigin(20, 20);
    //sHayalet2.setOrigin(50, 50);

    int hayaletSayisi = 4;
    Hayalet a[10];
    
    bool Oyun = true;
    int x = 0, y = 0, dx = 0, dy = 0;  //ba??lang覺癟 noktalar覺
    float kronometre = 0, gecikme = 0.07; //tu??a bast覺ktan sonra pacman覺n hareket etme h覺z覺
    Clock clock;

    for (int i = 0; i < SATIR; i++)
        for (int j = 0; j < SUTUN; j++)
            if (i == 0 || j == 0 || i == SATIR - 1 || j == SUTUN - 1)  cerceve[i][j] = 1;
    
    while (window.isOpen())
    {
        float s羹re = clock.getElapsedTime().asSeconds();
        clock.restart();
        kronometre += s羹re;

        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();

            if (e.type == Event::KeyPressed)
                if (e.key.code == Keyboard::Escape)
                {
                    for (int i = 1; i < SATIR - 1; i++)
                        for (int j = 1; j < SUTUN - 1; j++)
                        {
                            cerceve[i][j] = 0;
                            
                        }
                    x = 10; y = 0;
                    Oyun = true;
                }
        }

        if ((Keyboard::isKeyPressed(Keyboard::Left)) || (Keyboard::isKeyPressed(Keyboard::A))) { dx = -1; dy = 0; }; //Sola giderken -x y繹n羹nde hareket eder
        if ((Keyboard::isKeyPressed(Keyboard::Right)) || (Keyboard::isKeyPressed(Keyboard::D))) { dx = 1; dy = 0; }; //Sa??a giderken +x y繹n羹nde hareket eder
        if ((Keyboard::isKeyPressed(Keyboard::Up)) || (Keyboard::isKeyPressed(Keyboard::W))) { dx = 0; dy = -1; }; //Yukar覺 giderken +y y繹n羹nde hareket eder
        if ((Keyboard::isKeyPressed(Keyboard::Down)) || (Keyboard::isKeyPressed(Keyboard::S))) { dx = 0; dy = 1; }; //A??a??覺 giderken -y y繹n羹nde hareket eder

        if (!Oyun) continue;

        if (kronometre > gecikme)
        {
            x += dx;
            y += dy;

            if (x < 0) x = 0; if (x > SUTUN - 1) x = SUTUN - 1;
            if (y < 0) y = 0; if (y > SATIR - 1) y = SATIR - 1;

            if (cerceve[y][x] == 2) Oyun = false;
            if (cerceve[y][x] == 0) cerceve[y][x] = 2;
            kronometre = 0;
        }

        for (int i = 0; i < hayaletSayisi; i++) a[i].hayaletHareket();

        if (cerceve[y][x] == 1)
        {
            dx = dy = 0;

            for (int i = 0; i < hayaletSayisi; i++)
                drop(a[i].y / karoBoyutu, a[i].x / karoBoyutu);

            for (int i = 0; i < SATIR; i++)
                for (int j = 0; j < SUTUN; j++)
                    if (cerceve[i][j] == -1) cerceve[i][j] = 0;
                    else cerceve[i][j] = 1;
        }

        for (int i = 0; i < hayaletSayisi; i++)
            if (cerceve[a[i].y / karoBoyutu][a[i].x / karoBoyutu] == 2) Oyun = false;

        /////////癟izim//////////
        window.clear();

        for (int i = 0; i < SATIR; i++)
            for (int j = 0; j < SUTUN; j++)
            {
                if (cerceve[i][j] == 0) continue;
                if (cerceve[i][j] == 1) sKaro.setTextureRect(IntRect(0, 0, karoBoyutu, karoBoyutu));
                if (cerceve[i][j] == 2) sKaro.setTextureRect(IntRect(54, 0, karoBoyutu, karoBoyutu));
                sKaro.setPosition(j * karoBoyutu, i * karoBoyutu);
                window.draw(sKaro);
            }

        sKaro.setTextureRect(IntRect(36, 0, karoBoyutu, karoBoyutu));
        sKaro.setPosition(x * karoBoyutu, y * karoBoyutu);
        window.draw(sKaro);

        //sHayalet.rotate(10);
        for (int i = 0; i < hayaletSayisi; i++)
        {
            sHayalet1.setPosition(a[i].x, a[i].y);
            window.draw(sHayalet1);
            sHayalet2.setPosition(a[i].x, a[i].y);
            window.draw(sHayalet2);
        }

        if (!Oyun) window.draw(sGameover);

        window.display();
    }

    return 0;
}
