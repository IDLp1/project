#include "main.h"
#include "cell.h"

Cell* cell = new Cell[MAX_CELLS];
CellProt* prot_cell = new CellProt[MAX_CELLSPROT];
Map* gamemap = new Map;

Texture* texture = new Texture[MAX_TEXTURES];
Sprite* sprite_cell = new Sprite[MAX_SPRITE_CELL];

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
                    cell[i].sprite->setPosition((double)cell[i].GetRealPosition().x, (double)cell[i].GetRealPosition().y);
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
                                cell[i].sprite->setPosition(cell[i].GetRealPosition().x + cd_cell_size, cell[i].GetRealPosition().y + cd_cell_size);
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
                                cell[i].sprite->setPosition(cell[i].GetRealPosition().x, cell[i].GetRealPosition().y);
                                window->draw(*cell[i].sprite);
                                cell[i].sprite->setRotation(0.0);
                            }
                        }
                        //нижняя
                        if(cell[i].GetMapPosition().y < gamemap->GetSizeH() - 1)
                        {
                            if(cell[i].cellprot->id != cell[i + gamemap->GetSizeW()].cellprot->id)
                            {
                                cell[i].sprite->setPosition((double)cell[i].GetRealPosition().x, (double)cell[i].GetRealPosition().y + cd_cell_size);
                                window->draw(*cell[i].sprite);
                            }
                        }
                        //верхняя
                        if(cell[i].GetMapPosition().y > 0)
                        {
                            if(cell[i].cellprot->id != cell[i - gamemap->GetSizeW()].cellprot->id)
                            {
                                cell[i].sprite->setPosition(cell[i].GetRealPosition().x + cd_cell_size, cell[i].GetRealPosition().y);
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
                                cell[i].sprite->setPosition(cell[i].GetRealPosition().x + cd_cell_size, cell[i].GetRealPosition().y);
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
                                cell[i].sprite->setPosition(cell[i].GetRealPosition().x + cd_cell_size, cell[i].GetRealPosition().y + cd_cell_size);
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
                                cell[i].sprite->setPosition(cell[i].GetRealPosition().x, cell[i].GetRealPosition().y + cd_cell_size);
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
                                cell[i].sprite->setPosition(cell[i].GetRealPosition().x, cell[i].GetRealPosition().y);
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
//
int main()
{
    srand(time(NULL));
    char cmd[32], arg[32];
    FILE* fs;
    fs = fopen("scripts/cells.s", "r");
    if(fs == NULL)
    {
        cout << "Error: Could't open scripts/cells.s" << endl;
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

        //Загрузка текстур и звуков
        for(int i(0); i < MAX_CELLSPROT; i++)
        {
            if(prot_cell[i].is_active)
            {
                char dir[64];
                strclear(dir);
                strcat(dir,"sprites/");
                strcat(dir, prot_cell[i].sprite_name);
                if(!texture[i].loadFromFile(dir)) cout << "Error: Can't load texture: " << dir << endl;
                else
                {
                    cout << "Loading: texture " << dir << endl;
                    prot_cell[i].sprite.setTexture(texture[i]);
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
            gamemap->SetSize(random(8, 32),(random(8, 32)));
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
    //....................................................................
    //генерация ячеек
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

    RenderWindow window(sf::VideoMode(DEFAULT_SCREEN_W, DEFAULT_SCREEN_H), name_game);
    window.setFramerateLimit(FPS_LIMIT);
    Event window_event;
    while(window.isOpen())
    {
        while(window.pollEvent(window_event)) if(window_event.type == sf::Event::Closed) window.close();

        //КАДР////////////////////////////////////////////////
        window.clear(Color(100, 100, 100));
        DrawCells(&window);
        window.display();
    }

    delete[] cell;
    delete[] prot_cell;
    delete gamemap;

    return 0;
}

