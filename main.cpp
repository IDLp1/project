#include "main.h"
#include "cell.h"
#include "map.h"
#include "decoration.h"
#include "unit.h"
#include "warrior.h"
#include "fraction.h"
#include "camera.h"

Cell* cell = new Cell[MAX_CELLS];
CellProt* prot_cell = new CellProt[MAX_CELLSPROT];
Decoration* decor = new Decoration[MAX_DECORATION];
DecorationProt* prot_dec = new DecorationProt[MAX_DECPROT];
Map* gamemap = new Map;

Camera* camera = new Camera;

Texture* texture_cell = new Texture[MAX_TEXTURES];
Texture* tex_dev_unit = new Texture;

Sprite* sprite_cell = new Sprite[MAX_SPRITE_CELL];
Sprite* sprite_dev_warrior = new Sprite; //dev

Color* color_red_fraction = new Color(c_color_red_fraction[0], c_color_red_fraction[1], c_color_red_fraction[2]);
Color* color_blue_fraction = new Color(c_color_blue_fraction[0], c_color_blue_fraction[1], c_color_blue_fraction[2]);
Color* color_green_fraction = new Color(c_color_green_fraction[0], c_color_green_fraction[1], c_color_green_fraction[2]);
Color* color_yellow_fraction = new Color(c_color_yellow_fraction[0], c_color_yellow_fraction[1], c_color_yellow_fraction[2]);

Warrior* warrior = new Warrior[MAX_WARRIOR];

Fraction* fraction = new Fraction[MAX_FRACTION];

int random(int min, int max)
{
    max++;
    return min + rand() % (max - min);
}

double random(double min, double max)
{
    double f = (double)rand() / RAND_MAX;
    return min + f * (max - min);
}

void strclear(char *str)
{
    for(int i(0); i < sizeof(str); i++)
    {
        str[i] = '\0';
    }
}
void DrawWarriors(RenderWindow* window)
{
    for(int i(0); i < MAX_WARRIOR; i++)
    {
        if(warrior[i].is_alive)
        {
            warrior[i].sprite.setPosition(Vector2f(warrior[i].GetRealPosition(camera)));
            window->draw(warrior[i].sprite);
        }
    }
}

void DrawCells(RenderWindow* window)
{
    int level = 0;
    while(level < 5)
    {
        for(int i(0); i < MAX_CELLS; i++)
        {
            if(cell[i].is_active)
            {
                if(cell[i].cellprot->level == level)
                {
                    //основа
                    cell[i].sprite->setPosition((double)cell[i].GetRealPosition(camera).x, (double)cell[i].GetRealPosition(camera).y);
                    cell[i].sprite->setTextureRect(IntRect(ci_cell_size * cell[i].rand_sprite, 0, ci_cell_size, ci_cell_size));
                    window->draw(*cell[i].sprite);
                    if(cell->cellprot->edge)
                    {
                        cell[i].sprite->setTextureRect(IntRect(cell[i].cellprot->rand_sprite * cd_cell_size, 0, cd_cell_size, cd_cell_size));
                        //правое
                        if(cell[i].GetMapPosition().x < gamemap->GetSizeW() - 1)
                        {
                            if(cell[i].cellprot->id != cell[i + 1].cellprot->id)
                            {
                                cell[i].sprite->setRotation(-90.0);
                                cell[i].sprite->setPosition(cell[i].GetRealPosition(camera).x + cd_cell_size, cell[i].GetRealPosition(camera).y + cd_cell_size);
                                window->draw(*cell[i].sprite);
                                cell[i].sprite->setRotation(0.0);
                            }
                        }
                        //левая
                        if(cell[i].GetMapPosition().x > 0)
                        {
                            if(cell[i].cellprot->id != cell[i - 1].cellprot->id)
                            {
                                cell[i].sprite->setRotation(90.0);
                                cell[i].sprite->setPosition(cell[i].GetRealPosition(camera).x, cell[i].GetRealPosition(camera).y);
                                window->draw(*cell[i].sprite);
                                cell[i].sprite->setRotation(0.0);
                            }
                        }
                        //нижняя
                        if(cell[i].GetMapPosition().y < gamemap->GetSizeH() - 1)
                        {
                            if(cell[i].cellprot->id != cell[i + gamemap->GetSizeW()].cellprot->id)
                            {
                                cell[i].sprite->setPosition((double)cell[i].GetRealPosition(camera).x, (double)cell[i].GetRealPosition(camera).y + cd_cell_size);
                                window->draw(*cell[i].sprite);
                            }
                        }
                        //верхняя
                        if(cell[i].GetMapPosition().y > 0)
                        {
                            if(cell[i].cellprot->id != cell[i - gamemap->GetSizeW()].cellprot->id)
                            {
                                cell[i].sprite->setPosition(cell[i].GetRealPosition(camera).x + cd_cell_size, cell[i].GetRealPosition(camera).y);
                                cell[i].sprite->setRotation(180.0);
                                window->draw(*cell[i].sprite);
                                cell[i].sprite->setRotation(0.0);
                            }
                        }
                        //уголки
                        //правый верхний
                        cell[i].sprite->setTextureRect(IntRect(cell[i].cellprot->rand_sprite * cd_cell_size + cd_cell_size, 0, cd_cell_size, cd_cell_size));
                        if(cell[i].GetMapPosition().x < gamemap->GetSizeW() - 1 && cell[i].GetMapPosition().y > 0)
                        {
                            if(cell[i].cellprot->id != cell[i + 1].cellprot->id
                                    && cell[i].cellprot->id != cell[i - gamemap->GetSizeW()].cellprot->id
                                    && cell[i].cellprot->id != cell[i + 1 - gamemap->GetSizeW()].cellprot->id)
                            {
                                cell[i].sprite->setRotation(-90.0);
                                cell[i].sprite->setPosition(cell[i].GetRealPosition(camera).x + cd_cell_size, cell[i].GetRealPosition(camera).y);
                                window->draw(*cell[i].sprite);
                                cell[i].sprite->setRotation(0.0);
                            }
                        }
                        //правый нижний
                        if(cell[i].GetMapPosition().x < gamemap->GetSizeW() - 1 && cell[i].GetMapPosition().y < gamemap->GetSizeH() - 1)
                        {
                            if(cell[i].cellprot->id != cell[i + 1].cellprot->id
                                    && cell[i].cellprot->id != cell[i + gamemap->GetSizeW()].cellprot->id
                                    && cell[i].cellprot->id != cell[i + 1 + gamemap->GetSizeW()].cellprot->id)
                            {
                                cell[i].sprite->setPosition(cell[i].GetRealPosition(camera).x + cd_cell_size, cell[i].GetRealPosition(camera).y + cd_cell_size);
                                window->draw(*cell[i].sprite);
                                cell[i].sprite->setRotation(0.0);
                            }
                        }
                        //левый нижний
                        if(cell[i].GetMapPosition().x > 0 && cell[i].GetMapPosition().y < gamemap->GetSizeH() - 1)
                        {
                            if(cell[i].cellprot->id != cell[i - 1].cellprot->id
                                    && cell[i].cellprot->id != cell[i + gamemap->GetSizeW()].cellprot->id
                                    && cell[i].cellprot->id != cell[i - 1 + gamemap->GetSizeW()].cellprot->id)
                            {
                                cell[i].sprite->setRotation(90.0);
                                cell[i].sprite->setPosition(cell[i].GetRealPosition(camera).x, cell[i].GetRealPosition(camera).y + cd_cell_size);
                                window->draw(*cell[i].sprite);
                                cell[i].sprite->setRotation(0.0);
                            }
                        }
                        //левый верхний
                        if(cell[i].GetMapPosition().x > 0 && cell[i].GetMapPosition().y > 0)
                        {
                            if(cell[i].cellprot->id != cell[i - 1].cellprot->id
                                    && cell[i].cellprot->id != cell[i - gamemap->GetSizeW()].cellprot->id
                                    && cell[i].cellprot->id != cell[i - 1 - gamemap->GetSizeW()].cellprot->id)
                            {
                                cell[i].sprite->setRotation(180.0);
                                cell[i].sprite->setPosition(cell[i].GetRealPosition(camera).x, cell[i].GetRealPosition(camera).y);
                                window->draw(*cell[i].sprite);
                                cell[i].sprite->setRotation(0.0);
                            }
                        }
                    }
                }
            }
            else
            {
                break;
            }
        }
        level++;
    }
}
// Отрисовка декораций
void DrawDecorations(RenderWindow *window)
{

    for(int i(0); i < MAX_DECORATION; i++)
    {
        if(decor[i].is_active)
        {
            decor[i].dec_prot->sprite.setPosition(decor[i].GetRealPosition(camera));
            window->draw(decor[i].dec_prot->sprite);
        }
        else
        {
            break;
        }
    }
}

int main()
{
    srand(time(NULL));
    char cmd[32], arg[32];

    FILE* fs;
    //Считывание файла ячеек

    fs = fopen("scripts/cells.s", "r");
    if(fs == NULL)
    {
        cout << "Error: Could't open scripts/cells.s" << endl;
        getchar();
        return 0;
    }
    else
    {
        for(int i(0); i < MAX_CELLSPROT; i++)
        {
            if(!feof(fs))
            {
                fscanf(fs, "%d %s %s %d %d %d %lg %d",
                       &prot_cell[i].id,
                       &prot_cell[i].name,
                       &prot_cell[i].sprite_name,
                       &prot_cell[i].edge,
                       &prot_cell[i].rand_sprite,
                       &prot_cell[i].level,
                       &prot_cell[i].fordable,
                       &prot_cell[i].dismorale);
                prot_cell[i].is_active = true;
            }
            else
            {
                fclose(fs);
                break;
            }
        }

        //вывод прототипов ячеек
        for(int i(0); i < MAX_CELLSPROT; i++)
        {
            if(prot_cell[i].is_active)
            {
                cout << prot_cell[i].id << "\t" << prot_cell[i].name << "\t" << prot_cell[i].sprite_name << "\t" << prot_cell[i].edge << "\t" << prot_cell[i].rand_sprite << "\t" <<
                        prot_cell[i].level << "\t" <<
                        prot_cell[i].fordable << "\t" << prot_cell[i].dismorale << "\t" << endl;
            }
        }

        //Считывание файла декораций

        fs = fopen("scripts/decoration.s", "r");
        if(fs == NULL)
        {
            cout << "Error: Could't open scripts/decoration.s" << endl;
            getchar();
            return 0;
        }
        else
        {
            char name[64];
            while(!feof(fs))
            {
                for(int i(0); i < MAX_DECPROT; i++)
                {
                    while(true)
                    {
                        fscanf(fs, "%s", name);
                        if(strcmp(name, "id") == 0)
                        {
                            char arg[8];
                            fscanf(fs, "%s", arg);
                            prot_dec[i].id = atoi(arg);
                        }
                        else if(strcmp(name, "name") == 0)
                        {
                            char arg[64];
                            fscanf(fs, "%s", arg);
                            strcpy(prot_dec[i].name, arg);
                            cout << "i = " << i << " name = " << arg << endl;
                            prot_dec[i].is_active = true;
                            continue;
                        }
                        else if(strcmp(name, "sprite") == 0)
                        {
                            char dir[64], arg[64];
                            strclear(dir);
                            strcat(dir, "sprites/");
                            fscanf(fs, "%s", arg);
                            if(!prot_dec[i].texture.loadFromFile(strcat(dir, arg)))
                            {
                                cout << "ERROR: Can't load texture: " << dir << endl;
                                getchar();
                                return 0;
                            }
                            else
                            {
                                prot_dec[i].sprite.setTexture(prot_dec[i].texture);
                                continue;
                            }
                        }
                        else if(strcmp(name, "size") == 0)
                        {
                            char arg1[8], arg2[8];
                            fscanf(fs, "%s %s", arg1, arg2);
                            prot_dec[i].size[_W] = atoi(arg1);
                            prot_dec[i].size[_H] = atoi(arg2);
                            continue;
                        }
                        else if(strcmp(name, "is_minning") == 0)
                        {
                            char arg[8];
                            fscanf(fs, "%s", arg);
                            prot_dec[i].is_minning = atoi(arg);
                            continue;
                        }
                        else if(strcmp(name, "transparency") == 0)
                        {
                            char arg[8];
                            fscanf(fs, "%s", arg);
                            prot_dec[i].transparency = atof(arg);
                        }
                        else if(strcmp(name, "fordable") == 0)
                        {
                            char arg[8];
                            fscanf(fs, "%s", arg);
                            prot_dec[i].fordable = atof(arg);
                        }
                        else if(strcmp(name, "mine") == 0)
                        {
                            char arg1[8], arg2[8];
                            fscanf(fs, "%s %s", arg1, arg2);
                            if(prot_dec[i].is_minning)
                            {
                                bool success = false;
                                for(int j(0); j < MAX_MINECELLS; j++)
                                {
                                    if(prot_dec[i].mine[j].GetID() == 0)
                                    {
                                        prot_dec[i].mine[j].Set(atoi(arg1), atoi(arg2));
                                        success = true;
                                    }
                                }
                                if(!success)
                                {
                                    cout << "ERROR: Too many mines in decoration " << prot_dec[i].name << endl;
                                    getchar();
                                    return 0;
                                }
                            }
                        }
                        else if(strcmp(name, "end") == 0)
                        {
                            break;
                        }
                        else
                        {
                            cout << "ERROR: File decoration.s is corrupt" << endl;
                            getchar();
                            return 0;
                        }
                    }
                }
            }
            fclose(fs);
        }
        //дебаг для декораций
        for(int i(0); i < MAX_DECPROT; i++)
        {
            if(prot_dec[i].is_active)
            {
                cout << "DECORATION[" << i << "] " << endl << "NAME:" << prot_dec[i].name << endl
                     << "SIZE_W = " << prot_dec[i].size[_W] << endl
                     << "SIZE_H = " << prot_dec[i].size[_H] << endl
                     << "TR = " << prot_dec[i].transparency << endl
                     << "FR = " << prot_dec[i].fordable << endl;
            }
        }
        //Загрузка текстур и звуков
        for(int i(0); i < MAX_CELLSPROT; i++)
        {
            if(prot_cell[i].is_active)
            {
                char dir[64];
                strclear(dir);
                strcat(dir,"sprites/");
                strcat(dir, prot_cell[i].sprite_name);
                if(!texture_cell[i].loadFromFile(dir)) cout << "ERROR: Can't load texture: " << dir << endl;
                else
                {
                    cout << "Loading: texture " << dir << endl;
                    prot_cell[i].sprite.setTexture(texture_cell[i]);
                    prot_cell[i].sprite.setTextureRect(IntRect(0, 0, 64, 64));
                }
            }
        }
    }
    //КОНСОЛЬ.....................................................
    while(true)
    {
        printf("=>");
        scanf("%s %s", &cmd, &arg);
        if(strcmp(cmd, "exit") == 0)
        {
            return 0;
        }
        if(strcmp(cmd, "map") == 0)
        {
            ifstream mapfile(arg, ios_base::binary | ios_base::in);
            if(!mapfile.is_open())
            {
                cout << "ERROR: Cannot open this map" << endl;
                continue;
            }
            mapfile.read((char*)gamemap, sizeof *gamemap);
            mapfile.close();
            break;
        }
        if(strcmp(cmd, "generate") == 0)
        {
            ofstream mapfile(arg, ios_base::binary | ios_base::out);
            gamemap->SetSize(random(32, 64),(random(32, 64)));
            gamemap->GenerateRandom(0,3);
            mapfile.write((char*)gamemap, sizeof *gamemap);
            mapfile.close();
        }
        if(strcmp(cmd, "mapinfo") == 0)
        {
            ifstream mapfile(arg, ios_base::binary | ios_base::in);
            mapfile.read((char*)gamemap, sizeof *gamemap);
            mapfile.close();
            cout << "MAP SIZE = " << gamemap->GetMaxSize() << " W = " << gamemap->GetSizeW() << " H = " << gamemap->GetSizeH() << endl;
        }
    }
    gamemap->decoration[2] = 1;
    gamemap->decoration[7] = 1;
    gamemap->decoration[24] = 1;
    //....................................................................
    //генерация ячеек
    {
        unsigned int x[2], y[2];
        x[MAX] = gamemap->GetSizeW() - 1;
        y[MAX] = gamemap->GetSizeH() - 1;
        x[CURRENT] = 0;
        y[CURRENT] = 0;
        for(int i(0); i < gamemap->GetMaxSize(); i++)
        {
            cell[i].SetOfCellProt(&prot_cell[gamemap->cell[i]]);
            if(x[CURRENT] >= x[MAX])
            {
                cell[i].SetPosition(x[CURRENT], y[CURRENT]);
                cell[i].is_active = true;
                //cout << "id = " << i << "X = " << cell[i].GetMapPosition().x << "Y = " << cell[i].GetMapPosition().y << endl;
                x[CURRENT] = 0;
                y[CURRENT]++;
            }
            else
            {
                cell[i].SetPosition(x[CURRENT], y[CURRENT]);
                cell[i].is_active = true;
                x[CURRENT]++;
            }
        }
    }
    //генерация декораций
    {
        cout << "load decorations..." << endl;
        for(int i(0); i < gamemap->GetMaxSize(); i++)
        {
            if(gamemap->decoration[i] != 0)
            {
                for(int j(0); j < MAX_DECPROT; j++)
                {
                    if(prot_dec[j].id == gamemap->decoration[i])
                    {
                        cout << "== ";
                        for(int k(0); k < MAX_DECORATION; k++)
                        {
                            if(!decor[k].is_active)
                            {
                                decor[k].SetProt(&prot_dec[j]);
                                decor[k].is_active = true;
                                decor[k].SetPosition(gamemap->GetPosition(i));
                                cout << "DEC[i]:" << i << " X = " << gamemap->GetPosition(i).x << " Y = " << gamemap->GetPosition(i).y << endl;
                                break;
                            }
                        }
                        break;
                    }
                }
            }
        }
    }

    //игровые данные..........................................

    if(!tex_dev_unit->loadFromFile(c_tex_dev_unit))
    {
        cout << "Could not load texture: " << c_tex_dev_unit << endl;
        getchar();
        return 0;
    }
    for(int i(0); i < MAX_WARRIOR; i++)
    {
        warrior[i].sprite.setTexture(*tex_dev_unit);
    }

    fraction[0].SetColor(color_red_fraction);
    fraction[1].SetColor(color_blue_fraction);
    fraction[2].SetColor(color_green_fraction);
    fraction[3].SetColor(color_yellow_fraction);

    warrior[0].Spawn(3, 3, &fraction[2]);
    warrior[1].Spawn(4, 8, &fraction[3]);
    warrior[2].Spawn(6, 6, &fraction[0]);
    warrior[3].Spawn(10, 11, &fraction[1]);



    //.................................................................
    RenderWindow window(sf::VideoMode(DEFAULT_SCREEN_W, DEFAULT_SCREEN_H), name_game);
    window.setFramerateLimit(FPS_LIMIT);
    Event window_event;

    //./////////////////////////////////////////////////ГЛАВНЫЙ ЦИКЛ//////////////////////////////////////////////
    while(window.isOpen())
    {
        while(window.pollEvent(window_event)) if(window_event.type == sf::Event::Closed) window.close();

        //Обработка клавиатуры и мыши

        if(Keyboard::isKeyPressed(Keyboard::W))
        {
            camera->Move(0.0, -cf_camera_speed);
        }
        if(Keyboard::isKeyPressed(Keyboard::S))
        {
            camera->Move(0.0, cf_camera_speed);
        }
        if(Keyboard::isKeyPressed(Keyboard::D))
        {
            camera->Move(cf_camera_speed, 0.0);
        }
        if(Keyboard::isKeyPressed(Keyboard::A))
        {
            camera->Move(-cf_camera_speed, 0.0);
        }

        //КАДР////////////////////////////////////////////////
        window.clear(Color(100, 100, 100));
        DrawCells(&window);
        DrawDecorations(&window);
        DrawWarriors(&window);
        window.display();
    }

    delete[] cell;
    delete[] prot_cell;
    delete[] decor;
    delete[] prot_dec;
    delete gamemap;

    return 0;
}

