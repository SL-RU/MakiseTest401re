#include "list_test.h"

MButton butt[4];
MCanvas canv[2];
MLable  labls[2];
MTextField tf[2];
MSList   list[2];


char* sample_string = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";


MakiseStyle button_style =
{
    MC_White,
    &F_Arial24,
    0,
    //bg       font     border   double_border
    {MC_Black, MC_Gray, MC_Gray, 0},  //unactive
    {MC_Black, MC_White, MC_White, 0},//normal
    {MC_White, MC_Black, MC_White, 0}, //focused
    {MC_Green, MC_White, MC_White, 0}, //active
};
MakiseStyle canvas_style =
{
    MC_White,
    &F_Arial24,
    0,
    //bg       font     border   double_border
    {MC_Gray, MC_Gray, MC_Gray,    0},  //unactive
    {MC_Black, MC_White, MC_White, 0},  //normal
    {MC_Green, MC_Red, MC_White,   0},  //focused
    {MC_Black, MC_White, MC_White, 0},  //active
};
MakiseStyle lable_style =
{
    MC_White,
    &F_Arial15,
    0,
    //bg       font     border   double_border
    {MC_Gray, MC_Gray, MC_Gray, 0},  //unactive
    {MC_Black, MC_White, MC_Black, 0},//normal
    {MC_White, MC_Blue, MC_White, 0}, //focused
    {MC_Black, MC_Gray, MC_Black, 0}, //active
};
MakiseStyle text_style =
{
    MC_White,
    &F_Arial15,
    3,
    //bg       font     border   double_border
    {MC_Black, MC_White, MC_Gray, 0},  //unactive
    {MC_Black, MC_White, MC_Green, 0},  //unactive
    {0, 0, 0, 0}, //focused
    {0, 0, 0, 0}, //active
};

char *t_ok = "OK",
    *t_canc = "Cancel",
    *t_add = "Add",
    *t_remove = "Remove";


char *t_list[] = {
    "Hello",
    "����",//({210, 229, 241, 242, 0}),
    "string",
    "method",
    "������� �����?",
    "GPS",
    "SD card",
    "Camera",
    "insert",
    "���!"
};
MSList_Item l_source[10] = {{0}};
MSList_Item l_dest[1024] = {{0}};

uint32_t s_i = 0;
void b_add(MButton *b)
{
    l_dest[s_i].id = s_i;
    l_dest[s_i].text = list[0].selected->text;
    m_slist_add(&list[1], &l_dest[s_i]);
    s_i ++;
}
void b_rem(MButton *b)
{
    if(list[1].selected)
	m_slist_remove(&list[1], list[1].selected);
}
void l_add(MSList *l, MSList_Item *i)
{
    l_dest[s_i].id = s_i;
    l_dest[s_i].text = i->text;
    m_slist_add(&list[1], &l_dest[s_i]);
    s_i ++;
}
void l_rem(MSList *l, MSList_Item *i)
{
    if(list[1].selected)
	m_slist_remove(l, i);
}
void l_onselection(MSList *l, MSList_Item *i)
{
}

void at_list_init(MakiseGUI *gui, MHost *host)
{
    m_create_slist(&list[0], host->host, 3, 10, 156, 145, "lol", &l_onselection, &l_add, &canvas_style, &lable_style);

    m_create_slist(&list[1], host->host, 160, 10, 156, 145, "lol", &l_onselection, &l_rem, &canvas_style, &lable_style);

    m_create_button(&butt[0], host->host, 10, 163, 100, 35, t_add, &b_add, 0, 0, &button_style);
    m_create_button(&butt[1], host->host, 115, 163, 100, 35, t_remove, &b_rem, 0, 0, &button_style);

    m_create_text_field(&tf[0], host->host, 5, 200, 310, 35, sample_string, &text_style);


    for (uint32_t i = 0; i < 10; i++) {
	l_source[i].text = t_list[i];
    }
    m_slist_set_array(list, l_source, 10);
    m_slist_set_list(&list[1], 0);

    makise_g_focus(&list[0].el, M_G_FOCUS_GET);
}





