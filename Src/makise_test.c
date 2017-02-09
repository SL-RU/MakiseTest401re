#include "makise_test.h"
#include "controls_595.h"
#include <stdio.h>
#include <string.h>
MakiseGUI* mGui;
MHost *host;
MakiseGUI    Gu;
MakiseBuffer Bu;
MakiseDriver Dr;
MHost hs;
MContainer co;
uint32_t sb[3920] = {0};


void HAL_SPI_TxHalfCpltCallback(SPI_HandleTypeDef *hspi)
{
    if(hspi == &ILI9340_SPI)
	ili9340_spi_txhalfcplt(mGui->driver);
}
void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
    if(hspi == &ILI9340_SPI)
	ili9340_spi_txcplt(mGui->driver);
}

MButton butt[4];
MCanvas canv[2];
MLable  labls[2];
MTextField tf[2];
MSList   list[2];

MSList_Item l_itms[222] = {{0}};

void mt_predraw(MakiseGUI * g)
{
    canv[0].el.position.x = (canv[0].el.position.x+1) %150;
    makise_g_host_call(host, M_G_CALL_PREDRAW);

}

controls_595_ButtonState buttons[] = {
    {1, 1, GPIOC, GPIO_PIN_0, 7, 0, 0, 0},
    {1, 2, GPIOC, GPIO_PIN_0, 6, 0, 0, 0},
    {1, 3, GPIOC, GPIO_PIN_0, 5, 0, 0, 0},
    {1, 4, GPIOC, GPIO_PIN_0, 4, 0, 0, 0},

    {1, 11, GPIOC, GPIO_PIN_1, 7, 0, 0, 0},
    {1, 12, GPIOC, GPIO_PIN_1, 6, 0, 0, 0},
    {1, 13, GPIOC, GPIO_PIN_1, 5, 0, 0, 0},
    {1, 14, GPIOC, GPIO_PIN_1, 4, 0, 0, 0},

};

controls_595_OutputState outs[] = {
    {1, 5, 0, 1},
    {1, 6, 1, 0},
    {1, 7, 2, 0},
    {1, 8, 3, 1},
};
void but_h(
			   uint32_t id,
			   uint8_t event,
			   uint32_t time)
{
    if(event & CONTROLS_ALL_CLICK)
    {
	/* if(id == 3) */
	/*     butt[2].el.position.y --; */
	/* if(id == 1) */
	/*     butt[2].el.position.y ++; */
	/* if(id == 4) */
	/*     butt[2].el.position.x ++; */
	/* if(id == 2) */
	/*     butt[2].el.position.x --; */

	if(id == 11)
	    //m_element_focus(&(butt[1].el), M_G_FOCUS_GET);
//	    makise_g_focus(&(butt[1].el), M_G_FOCUS_GET);
	    makise_g_cont_focus_prev(host->host);
	if(id == 12)
	    makise_g_cont_focus_next(host->host);
	if(id == 3)
	    makise_g_host_input(host, (MInputData){M_KEY_UP, M_INPUT_CLICK, time, 0});
	if(id == 1)
	    makise_g_host_input(host, (MInputData){M_KEY_DOWN, M_INPUT_CLICK, time, 0});
	if(id == 4)
	    makise_g_host_input(host, (MInputData){M_KEY_RIGHT, M_INPUT_CLICK, time, 0});
	if(id == 2) 
	    makise_g_host_input(host, (MInputData){M_KEY_LEFT, M_INPUT_CLICK, time, 0});
	if(id == 14)
	    makise_g_host_input(host, (MInputData){M_KEY_OK, M_INPUT_CLICK, time, 0});

    }
//	    makise_g_focus(&(butt[0].el), M_G_FOCUS_GET);
	//m_element_focus(&(butt[0].el), M_G_FOCUS_GET);
//	if(id == 13)
//	    makise_g_focus(&(butt[2].el), M_G_FOCUS_GET);
//	    m_element_focus(&(butt[2].el), M_G_FOCUS_GET);
	
    if(event & CONTROLS_ALL_PRESSING)
    {
	if(id == 3)
	    makise_g_host_input(host, (MInputData){M_KEY_UP, M_INPUT_PRESSING, time, 0});
	if(id == 1)
	    makise_g_host_input(host, (MInputData){M_KEY_DOWN, M_INPUT_PRESSING, time, 0});
	if(id == 4)
	    makise_g_host_input(host, (MInputData){M_KEY_RIGHT, M_INPUT_PRESSING, time, 0});
	if(id == 2) 
	    makise_g_host_input(host, (MInputData){M_KEY_LEFT, M_INPUT_PRESSING, time, 0});
//	printf("click %d\n", id);
    }
}


char t0[] = "dsf";
char t1[] = "CANC    ";//{208, 204, 255};
char t2[] = "OK";
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
    {0, 0, 0, 0}, //active
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


void b_ok_cl(MButton *b)
{
    snprintf(t1, 8, "%dlol\n", list[0].selected->id);
}
void b_ca_cl(MButton *b)
{
    list[0].selected = &l_itms[0];
}
void onselection(MSList *l, MSList_Item selected)
{
    tf[0].text = selected.text;
}


uint32_t bb[9600] = {0};
MakiseGUI* mt_start()
{
    //malloc structures
    MakiseGUI    * gu = &Gu;//malloc(sizeof(MakiseGUI));
    MakiseBuffer * bu = &Bu;//malloc(sizeof(MakiseBuffer));
    MakiseDriver * dr = &Dr;//malloc(sizeof(MakiseDriver));
    host = &hs;//malloc(sizeof(MHost));
    host->host = &co;//malloc(sizeof(MContainer));
    host->host->gui = gu;

    //init driver structure
    ili9340_driver(dr);
    //malloc small buffer
    dr->buffer = sb;//malloc(dr->size);
    printf("%d\n", (uint32_t)(dr->size));
    //init gui struct

    uint32_t sz = makise_init(gu, dr, bu);
    //malloc big buffer
    bu->buffer = bb;//malloc(sz);
    memset(bu->buffer, 0, sz);
    printf("%d\n", (uint32_t)(sz));

//    m_create_canvas(&canv[0], host->host, 20, 100, 200, 60, &canvas_style);
    
//    m_create_button(&butt[0], &(canv[0].cont), 10, 10,  100, 30, t0, 0, 0, 0, &button_style);
    m_create_button(&butt[1], host->host, 240, 190, 80, 40, t1, &b_ca_cl, 0, 0, &button_style);
    m_create_button(&butt[2], host->host, 240, 150, 80, 40, t2, &b_ok_cl, 0, 0, &button_style);
//    m_create_button(&butt[3], &(canv[0].cont), 50, 70, 50,  20, t2, 0, 0, 0, &button_style);

    m_create_lable(&labls[0], host->host, 5, 150, 50, 28, t2, &lable_style);
    m_create_text_field(&tf[0], host->host, 55, 150, 180, 100, sample_string, &text_style);
    m_create_slist(&list[0], host->host, 10, 10, 200, 138, "lol", &onselection, 0, &canvas_style, &lable_style);

    for (uint32_t i = 0; i < 222; i++) {
	l_itms[i].text = sample_string + i*2;
    }
    
    m_slist_set_array(&list[0], l_itms, 222);
    
    mGui = gu;
    ili9340_init(gu);
    makise_start(gu);

    mGui->predraw = &mt_predraw;

    makise_g_focus(&(butt[0].el), M_G_FOCUS_GET);
    controls_595_init(buttons, 8, outs, 4, &but_h);
   
    return mGui;
}
