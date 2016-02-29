#include "main.h"
#include "cell.h"
#include "map.h"
#include "decoration.h"
#include "unit.h"

#include "warrior.h"
#include "weapon.h"
#include "fraction.h"


Cell* cell = new Cell[MAX_CELLS];
CellProt* prot_cell = new CellProt[MAX_CELLSPROT];
Decoration* decor = new Decoration[MAX_DECORATION];
DecorationProt* prot_dec = new DecorationProt[MAX_DECPROT];
Map* gamemap = new Map;

Font* font_main = new Font;
Text* text_dev_param_warrior = new Text;

Texture* texture_cell = new Texture[MAX_TEXTURES];
Texture* tex_dev_unit = new Texture;
Texture* tex_hud_order = new Texture;
Texture* tex_weapon = new Texture[MAX_TEX_WEAPONS];

Sprite* sprite_cell = new Sprite[MAX_SPRITE_CELL];
Sprite* sprite_dev_warrior = new Sprite; //dev
Sprite* sprite_hud_order = new Sprite; //отрисовка пути войнов

Color* color_red_fraction = new Color(c_color_red_fraction[0], c_color_red_fraction[1], c_color_red_fraction[2]);
Color* color_blue_fraction = new Color(c_color_blue_fraction[0], c_color_blue_fraction[1], c_color_blue_fraction[2]);
Color* color_green_fraction = new Color(c_color_green_fraction[0], c_color_green_fraction[1], c_color_green_fraction[2]);
Color* color_yellow_fraction = new Color(c_color_yellow_fraction[0], c_color_yellow_fraction[1], c_color_yellow_fraction[2]);

View* camera = new View;

Warrior* warrior = new Warrior[MAX_WARRIOR];

Fraction* fraction = new Fraction[MAX_FRACTION];

CircleShape* shape_selected = new CircleShape(cf_size_warrior / 2.0 + 8.0);
CircleShape* shape_move_order = new CircleShape(cf_size_warrior / 2.0 + 8.0);
Vertex* line_order = new Vertex[2];
RectangleShape* dark_shape = new RectangleShape;

WeaponProt* weapon_prot = new WeaponProt[MAX_WEAPONS_PROT]; //меч

Weapon* weapon = new Weapon[MAX_WEAPONS];

int random(unsigned int min, unsigned int max)
{
    max++;
    return min + rand() % (max - min);
}
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

Vector2i GetPosition(const Vector2f _vector)
{
    float x = _vector.x;
    float y = _vector.y;
    x = x / cd_cell_size;
    y = y / cd_cell_size;
    return Vector2i((int)x, (int)y);
}

void DrawInventory(RenderWindow* window)
{
        //отрисовка инвентаря и параметров
    for(int i(0); i < MAX_WARRIOR; i++)
    {
        if(warrior[i].is_alive && warrior[i].is_selected)
        {
            dark_shape->setPosition(warrior[i].GetRealPosition());
            window->draw(*dark_shape);
            char text[128];
            sprintf(text, "Health = %d|%d\nStamina = %d|%d\nPA = %d|%d\nDMG = %.2f\nACC = %d\nDDG = %d\nCRIT = %.2f%\n",
                    warrior[i].GetHealth(CURRENT), warrior[i].GetHealth(MAX),
                    warrior[i].GetStamina(CURRENT), warrior[i].GetStamina(MAX),
                    warrior[i].GetPointAction(CURRENT), warrior[i].GetPointAction(MAX), warrior[i].GetDamage(),
                    warrior[i].GetAccuracy(), warrior[i].GetDodge(), warrior[i].GetCritProc());
            text_dev_param_warrior->setString(text);
            text_dev_param_warrior->setPosition(warrior[i].GetRealPosition());
            window->draw(*text_dev_param_warrior);
            if(warrior[i].weapon != NULL)
            {
                warrior[i].weapon->weapon_prot->sprite.setPosition(warrior[i].GetRealPosition() + Vector2f(120.f, 120.f));
                window->draw(warrior[i].weapon->weapon_prot->sprite);
            }
        }
    }
}

void DrawWarriors(RenderWindow* window)
{
    for(int i(0); i < MAX_WARRIOR; i++)
    {
        if(warrior[i].is_alive)
        {
            warrior[i].sprite.setPosition(Vector2f(warrior[i].GetRealPosition()));
            window->draw(warrior[i].sprite);
            if(warrior[i].is_selected)
            {
                shape_selected->setPosition(Vector2f(warrior[i].GetRealPosition()));
                window->draw(*shape_selected);

                if(warrior[i].is_move_order)
                {

                    sprite_hud_order->setTextureRect(IntRect(0, 0, 64, 64));//отрисовка приказа
                    sprite_hud_order->setOrigin(Vector2f(cd_cell_size / 2.0, cd_cell_size / 2.0));
                    sprite_hud_order->setColor(Color(0, 255, 0));
                    sprite_hud_order->setPosition(GetRealPosition(warrior[i].GetMoveOrder(), true));
                    window->draw(*sprite_hud_order);

                    Vector2i pointer = warrior[i].GetPosition();
                    sprite_hud_order->setTextureRect(IntRect(64, 0, 64, 64));
                    for(int j(0 + warrior[i].current_step); j < MAX_STEPS; j++)//отрисовка пути
                    {
                        if(warrior[i].step[j].pos == Vector2i(0, 0))
                        {
                            break;
                        }


                        sprite_hud_order->setPosition(GetRealPosition(pointer,true));
                        if(warrior[i].step[j].pos.x == 1 && warrior[i].step[j].pos.y == 1)
                        {
                            sprite_hud_order->setRotation(45.0f);
                        }
                        else if(warrior[i].step[j].pos.x == 0 && warrior[i].step[j].pos.y == 1)
                        {
                            sprite_hud_order->setRotation(90.0f);
                        }
                        else if(warrior[i].step[j].pos.x == -1 && warrior[i].step[j].pos.y == 1)
                        {
                            sprite_hud_order->setRotation(135.0f);
                        }
                        else if(warrior[i].step[j].pos.x == -1 && warrior[i].step[j].pos.y == 0)
                        {
                            sprite_hud_order->setRotation(180.0f);
                        }
                        else if(warrior[i].step[j].pos.x == -1 && warrior[i].step[j].pos.y == -1)
                        {
                            sprite_hud_order->setRotation(225.0f);
                        }
                        else if(warrior[i].step[j].pos.x == 0 && warrior[i].step[j].pos.y == -1)
                        {
                            sprite_hud_order->setRotation(270.0f);
                        }
                        else if(warrior[i].step[j].pos.x == 1 && warrior[i].step[j].pos.y == -1)
                        {
                            sprite_hud_order->setRotation(315.0f);
                        }
                        else if(warrior[i].step[j].pos.x == 1 && warrior[i].step[j].pos.y == 0)
                        {
                            sprite_hud_order->setRotation(0.0f);
                        }
                        else
                        {

                        }
                        pointer += warrior[i].step[j].pos;
                        window->draw(*sprite_hud_order);
                    }
                }
            }
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
// Отрисовка декораций
void DrawDecorations(RenderWindow *window)
{

    for(int i(0); i < MAX_DECORATION; i++)
    {
        if(decor[i].is_active)
        {
            decor[i].dec_prot->sprite.setPosition(decor[i].GetRealPosition());
            window->draw(decor[i].dec_prot->sprite);
        }
        else
        {
            break;
        }
    }
}

bool CheckFordable(Vector2i _vector)
{
    if(_vector.x < 0) return false;
    if(_vector.y < 0) return false;
    for(int i(0); i < MAX_WARRIOR; i++)
    {
        if(warrior[i].is_alive)
        {
            if(_vector == warrior[i].GetPosition()) return false;
        }
    }
    for(int i(0); i < MAX_DECORATION; i++)
    {
        if(decor[i].is_active)
        {
            if(_vector == decor[i].GetPosition())
            {
                if(decor[i].dec_prot->fordable == 0.0) return false;
            }
        }
    }
    return true;
}

/*void WarriorBuildWay(Warrior* _warrior, Vector2i _vector) // постройка пути (не используется)
{
    if(CheckFordable(_vector))
    {
        for(int i(0); i < MAX_STEPS; i++)
        {
            _warrior->step[i].fordable = true; //"очистка" шагов
        }
        _warrior->SetMoveOrder(_vector);
        Vector2i pointer;
        pointer.x = _warrior->GetPosition().x;
        pointer.y = _warrior->GetPosition().y;
        cout << "start p = " <<  pointer.x << ", " << pointer.y << endl;
        bool wrongway = false;
        for(int i(0); i < MAX_STEPS; i++)
        {
            //поиск ближнего пути
            if(pointer.x - _warrior->GetMoveOrder().x < 0) _warrior->step[i].pos.x = 1;
            else if(pointer.x - _warrior->GetMoveOrder().x == 0) _warrior->step[i].pos.x = 0;
            else _warrior->step[i].pos.x = -1;
            if(pointer.y - _warrior->GetMoveOrder().y < 0) _warrior->step[i].pos.y = 1;
            else if(pointer.y - _warrior->GetMoveOrder().y == 0) _warrior->step[i].pos.y = 0;
            else _warrior->step[i].pos.y = -1;

            //препятсвия на ближнем пути
            /*if(!wrongway)
            {
                wrongway = !CheckObstacles(pointer + _warrior->step[i].pos);
            }
            else _warrior->step[i].fordable = false;*//*
            int counter(0);
            while(!CheckFordable(pointer + _warrior->step[i].pos) || counter > 10)
            {
                cout << "E6ok" << endl;
                //Поиск пути
                if(_warrior->step[i].pos.x == 1 && _warrior->step[i].pos.y == 1)
                {
                    _warrior->step[i].pos.x = 0;
                    counter++;
                    continue;
                }
                else if(_warrior->step[i].pos.x == 0 && _warrior->step[i].pos.y == 1)
                {
                    _warrior->step[i].pos.x = -1;
                    counter++;
                    continue;
                }
                else if(_warrior->step[i].pos.x == -1 && _warrior->step[i].pos.y == 1)
                {
                    _warrior->step[i].pos.y = 0;
                    counter++;
                    continue;
                }
                else if(_warrior->step[i].pos.x == -1 && _warrior->step[i].pos.y == 0)
                {
                    _warrior->step[i].pos.y = -1;
                    counter++;
                    continue;
                }
                else if(_warrior->step[i].pos.x == -1 && _warrior->step[i].pos.y == -1)
                {
                    _warrior->step[i].pos.x = 0;
                    counter++;
                    continue;
                }
                else if(_warrior->step[i].pos.x == 0 && _warrior->step[i].pos.y == -1)
                {
                    _warrior->step[i].pos.x = 1;
                    counter++;
                    continue;
                }
                else if(_warrior->step[i].pos.x == 1 && _warrior->step[i].pos.y == -1)
                {
                    _warrior->step[i].pos.y = 0;
                    counter++;
                    continue;
                }
                else if(_warrior->step[i].pos.x == 1 && _warrior->step[i].pos.y == 0)
                {
                    _warrior->step[i].pos.y = 1;
                    counter++;
                    continue;
                }
                else
                {
                    cout << "PIZDOS" << endl;
                    break;
                }
                if(counter == 10)
                {
                    cout << "ZAVIS" << endl;
                }
            }
            _warrior->step[i].fordable = false;
            pointer += _warrior->step[i].pos;
            cout << "step[" << i << "] = " <<  _warrior->step[i].pos.x << ", " << _warrior->step[i].pos.y << endl;
            cout << "p = " <<  pointer.x << ", " << pointer.y << endl;
            if(_warrior->step[i].pos.x == 0 && _warrior->step[i].pos.y == 0) break;
        }
    }
    else
    {
        cout << "nope" << endl;
    }
}*/

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
            cout << c_error << c_could_not_open << "scripts/decoration.s" << endl;
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
                                    cout << c_error << "Too many mines in decoration " << prot_dec[i].name << endl;
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
                            cout << c_error <<"File decoration.s is corrupt" << endl;
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
        //Загрузка текстур, шрифтов и звуков
        for(int i(0); i < MAX_CELLSPROT; i++)
        {
            if(prot_cell[i].is_active)
            {
                char dir[64];
                strclear(dir);
                strcat(dir,"sprites/");
                strcat(dir, prot_cell[i].sprite_name);
                if(!texture_cell[i].loadFromFile(dir)) cout << c_error << "Can't load texture: " << dir << endl;
                else
                {
                    cout << c_loading <<  "texture " << dir << endl;
                    prot_cell[i].sprite.setTexture(texture_cell[i]);
                    prot_cell[i].sprite.setTextureRect(IntRect(0, 0, 64, 64));
                }
            }
        }
        if(!font_main->loadFromFile(c_main_font))
        {
            cout << c_error << "Could't not open font file" << c_main_font << endl;
            getchar();
            return 0;
        }
        else
        {
            cout << c_loading << "font " << c_main_font << endl;
            text_dev_param_warrior->setFont(*font_main);
            text_dev_param_warrior->setCharacterSize(18);
            text_dev_param_warrior->setColor(Color(190, 190, 190));

        }

        if(!tex_weapon[WPP_SWORD].loadFromFile("sprites/sword.png"))
        {
            cout << c_error << "Can't load texture: sprites/sword.png" << endl;
            getchar();
            return 0;
        }
        else
        {
            weapon_prot[WPP_SWORD].sprite.setTexture(tex_weapon[0]);
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
                cout << c_error << "Cannot open this map" << endl;
                continue;
            }
            mapfile.read((char*)gamemap, sizeof *gamemap);
            mapfile.close();
            break;
        }
        if(strcmp(cmd, "generate") == 0)
        {
            ofstream mapfile(arg, ios_base::binary | ios_base::out);
            gamemap->GenerateRandom(25,25, 25, 10);
            mapfile.write((char*)gamemap, sizeof *gamemap);
            mapfile.close();
            cout << "Generate complete" << endl;
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

    //Оружие

    weapon_prot[WPP_SWORD].Set("Sword", Damage(30, 60, 5, 10), 1000, false, 0.0f);

    //переборка бойцев
    for(int i(0); i < MAX_WARRIOR; i++)
    {
        warrior[i].sprite.setTexture(*tex_dev_unit);
        warrior[i].sprite.setOrigin(Vector2f(cf_size_warrior / 2.0, cf_size_warrior / 2.0));
    }

    fraction[0].SetColor(color_red_fraction);
    fraction[1].SetColor(color_blue_fraction);
    fraction[2].SetColor(color_green_fraction);
    fraction[3].SetColor(color_yellow_fraction);

    warrior[0].Spawn(3, 3, &fraction[2], 5, 4, 4, 7, 1);
    warrior[1].Spawn(4, 8, &fraction[3], 6, 3, 3, 4, 3);
    warrior[2].Spawn(6, 6, &fraction[0], 3, 7, 6, 10, 3);
    warrior[5].Spawn(7, 7, &fraction[0], 5, 5, 5, 4, 2);
    warrior[3].Spawn(10, 11, &fraction[1], 6, 5, 7, 5, 5);

    weapon[0].Spawn(Vector2i(0, 0), &weapon_prot[WPP_SWORD]);
    warrior[0].SetWeapon(&weapon[0]);

    camera->setCenter(Vector2f(0.0, 0.0));
    camera->setSize(Vector2f(960.0, 540.0));

    //графические данные

    if(!tex_hud_order->loadFromFile(c_dir_hud_order))
    {
        cout << c_error << "Could not load texture: " << c_dir_hud_order << endl;
        getchar();
        return 0;
    }
    sprite_hud_order->setTexture(*tex_hud_order);

    shape_selected->setFillColor(Color(0, 0, 0, 0));
    shape_selected->setOutlineColor(Color(0, 255, 0));
    shape_selected->setOutlineThickness(4.0);
    shape_selected->setOrigin(cf_size_warrior / 2.0 + 8.0, cf_size_warrior / 2.0 + 8.0);
    shape_move_order->setFillColor(Color(0, 0, 0, 0));
    shape_move_order->setOutlineColor(Color(0, 0, 255));
    shape_move_order->setOutlineThickness(4.0);
    shape_move_order->setOrigin(cf_size_warrior / 2.0 + 8.0, cf_size_warrior / 2.0 + 8.0);

    dark_shape->setSize(Vector2f(250.0f, 300.0f));
    dark_shape->setFillColor(Color(0, 0, 0, 90));
    dark_shape->setOutlineColor(Color(190, 190, 190));
    dark_shape->setOutlineThickness(2.0f);
/*
    line_order[0].color.r = 0;
    line_order[0].color.g = 255;
    line_order[0].color.b = 0;
    line_order[1].color.r = 0;
    line_order[1].color.g = 0;
    line_order[1].color.b = 255;
*/
    bool move = false; //ход
    bool end_move = false;//конец хода

    //.................................................................
    RenderWindow window(sf::VideoMode(DEFAULT_SCREEN_W, DEFAULT_SCREEN_H), name_game);
    window.setFramerateLimit(FPS_LIMIT);
    Event window_event;

    bool mouse_lb_released[2] = {false, false};
    bool mouse_rb_released[2] = {false, false};
    bool space_released[2] = {false, false};
    bool i_released[2] = {false, false};
    bool order_move = false;
    Vector2i order_pointer(-1, -1);
    unsigned int counter_order = 0;

    Clock move_timer;

    bool is_inventory = false;


    //./////////////////////////////////////////////////ГЛАВНЫЙ ЦИКЛ//////////////////////////////////////////////
    while(window.isOpen())
    {
        while(window.pollEvent(window_event)) if(window_event.type == sf::Event::Closed) window.close();



        //Обработка клавиатуры и мыши

        if(Keyboard::isKeyPressed(Keyboard::W))
        {
            camera->move(Vector2f(0.0, -cf_camera_speed));
        }
        if(Keyboard::isKeyPressed(Keyboard::S))
        {
            camera->move(Vector2f(0.0, cf_camera_speed));
        }
        if(Keyboard::isKeyPressed(Keyboard::D))
        {
            camera->move(Vector2f(cf_camera_speed, 0.0));
        }
        if(Keyboard::isKeyPressed(Keyboard::A))
        {
            camera->move(Vector2f(-cf_camera_speed, 0.0));
        }
        if(Keyboard::isKeyPressed(Keyboard::Space))
        {
            space_released[0] = true;
            space_released[1] = true;
        }
        else
        {
            space_released[0] = false;
        }
        if(space_released[1] && !space_released[0]) //триггер нажатия пробела
        {
            space_released[1] = false;
            if(!move) move = true;
            move_timer.restart();
        }
        if(Keyboard::isKeyPressed(Keyboard::I))
        {
            i_released[0] = true;
            i_released[1] = true;
        }
        else
        {
            i_released[0] = false;
        }
        if(i_released[1] && !i_released[0]) //триггер нажатия i
        {
            i_released[1] = false;
            if(!is_inventory) is_inventory = true;
            else is_inventory = false;
        }


        //Работа с мышью
        Vector2i mouse_pos = Mouse::getPosition(window);
        Vector2f mouse_world_pos = window.mapPixelToCoords(mouse_pos);
        Vector2i mouse_gameworld_pos = GetPosition(mouse_world_pos);

        if(Mouse::isButtonPressed(Mouse::Left))//Триггер нажатия левой кнопки мыши
        {
            mouse_lb_released[0] = true;
            mouse_lb_released[1] = true;
        }
        else
        {
            mouse_lb_released[0] = false;
        }
        if(Mouse::isButtonPressed(Mouse::Right)) //Триггер нажатия правой кнопки мыши
        {
            mouse_rb_released[0] = true;
            mouse_rb_released[1] = true;
            if(!move && counter_order < MAX_STEPS - 1)
            {
                for(int i(0); i < MAX_WARRIOR; i++)
                {
                    if(warrior[i].is_alive)
                    {
                        if(warrior[i].is_selected)
                        {
                            if(mouse_gameworld_pos == warrior[i].GetPosition())
                            {
                                if(!order_move)
                                {
                                    order_move = true;
                                    cout << "ordermove = true" << endl;
                                }
                                if(order_pointer == Vector2i(-1, -1));
                                {
                                    order_pointer = warrior[i].GetPosition();
                                }
                            }
                            if(mouse_gameworld_pos == warrior[i].GetMoveOrder() && !order_move)
                            {
                                order_move = true;
                                order_pointer = warrior[i].GetMoveOrder();
                                for(int j(0); j < MAX_STEPS; j++)
                                {
                                    if(warrior[i].step[j].pos != Vector2i(0, 0)) counter_order++;
                                    else break;
                                }
                            }
                            if(order_pointer != mouse_gameworld_pos && order_move)
                            {
                                if(CheckFordable(mouse_gameworld_pos))// проверка препятствия
                                {
                                    if(mouse_world_pos.x >= GetRealPosition(mouse_gameworld_pos, false).x + cf_offset_move_order // уменьшение граней ячеек для более простого перемещения по диагонали
                                            && mouse_world_pos.x < GetRealPosition(mouse_gameworld_pos, false).x + cd_cell_size - cf_offset_move_order
                                            && mouse_world_pos.y >= GetRealPosition(mouse_gameworld_pos, false).y + cf_offset_move_order
                                            && mouse_world_pos.y < GetRealPosition(mouse_gameworld_pos, false).y + cd_cell_size - cf_offset_move_order)
                                    {
                                        Vector2i mo = mouse_gameworld_pos - order_pointer; //антибаг с "прыжками"
                                        if(mo.x >= -1 && mo.x <= 1 && mo.y >= -1 && mo.y <= 1)
                                        {
                                            warrior[i].step[counter_order].pos = mouse_gameworld_pos - order_pointer;
                                            cout << "S[" << counter_order << "](" << warrior[i].step[counter_order].pos.x << ", " << warrior[i].step[counter_order].pos.y << ")" << endl;
                                            order_pointer += warrior[i].step[counter_order].pos;
                                            counter_order++;
                                            warrior[i].SetMoveOrder(mouse_gameworld_pos);
                                        }
                                    }
                                }
                                else
                                {
                                    order_move = false;
                                    counter_order = 0;
                                    order_pointer = Vector2i(-1, -1);
                                }
                            }
                        }
                    }
                }
            }
        }
        else
        {
            mouse_rb_released[0] = false;
        }
        if(mouse_lb_released[1] && !mouse_lb_released[0]) // Триггер отжатия левой кнопки мыши
        {
            mouse_lb_released[1] = false;
            cout << "LB RELEASED" << endl;
            for(int i(0); i < MAX_WARRIOR; i++) // выделение бойца
            {
                if(     mouse_world_pos.x > warrior[i].GetRealPosition().x - cf_size_warrior / 2.0 &&
                        mouse_world_pos.x < warrior[i].GetRealPosition().x + cf_size_warrior / 2.0 &&
                        mouse_world_pos.y > warrior[i].GetRealPosition().y - cf_size_warrior / 2.0 &&
                        mouse_world_pos.y < warrior[i].GetRealPosition().y + cf_size_warrior / 2.0)
                {
                    if(!warrior[i].is_selected)
                    {

                        for(int j(0); j < MAX_WARRIOR; j++) warrior[j].is_selected = false;
                        warrior[i].is_selected = true;
                        cout << "WARRIOR " << i << " IS SELECTED" << endl;
                        break;
                    }
                }
            }
        }
        if(mouse_rb_released[1] && !mouse_rb_released[0]) // Триггер отжатия правой кнопки мыши
        {
            mouse_rb_released[1] = false;
            cout << "RB RELEASED" << endl;
            counter_order = 0;
            order_pointer = Vector2i(-1, -1);
            if(!move && !order_move)
            {        
                for(int i(0); i < MAX_WARRIOR; i++)
                {
                   if(warrior[i].is_alive)
                   {
                       if(warrior[i].is_selected)
                       {
                           if(mouse_gameworld_pos != warrior[i].GetMoveOrder())
                           {
                               warrior[i].ClearOrder();
                           }
                       }
                   }
                }
            }
            order_move = false;
        }

        if(move && move_timer.getElapsedTime().asMilliseconds() > ci_move_ms) // Ход
        {
            move_timer.restart();
            cout << "MOVE!" << endl;
            end_move = true;
            for(int i(0); i < MAX_WARRIOR; i++)
            {
                if(warrior[i].is_move_order)
                {
                    if(warrior[i].MoveOrder())
                    {
                        end_move = false;
                    }
                }
            }
            if(end_move)
            {
                cout << "END MOVE" << endl;
                move = false;
            }
        }

        //КАДР////////////////////////////////////////////////
        window.clear(Color(100, 100, 100));
        window.setView(*camera);
        DrawCells(&window);
        DrawDecorations(&window);
        DrawWarriors(&window);
        if(is_inventory) DrawInventory(&window);
        window.display();
    }

    delete[] cell;
    delete[] prot_cell;
    delete[] decor;
    delete[] prot_dec;
    delete gamemap;

    return 0;
}

