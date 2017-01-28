#include "makise_test.h"
#include "controls_595.h"
MakiseGUI* mGui;
MHost *host;
MakiseGUI    Gu;
MakiseBuffer Bu;
MakiseDriver Dr;
MHost hs;
MContainer co;
uint32_t sb[1920] = {0};


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
char t1[] = {208, 204, 255};
char t2[] = "GAD";

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

    m_canvas_create(&canv[0], host->host, 20, 100, 200, 160, MC_Lime, 1);
    
    m_button_create(&butt[0], &(canv[0].cont), 10, 10,  100, 30, t0,  1, 2, MC_Navy);
    m_button_create(&butt[1], host->host, 50, 250, 100, 50, t1,  1, 2, 1);
    m_button_create(&butt[2], host->host, 50, 220, 70,  50, t2,  1, MC_Red, 1);
    m_button_create(&butt[3], &(canv[0].cont), 50, 70, 50,  20, t2,  MC_Cyan, 2, 1);

   
    
    mGui = gu;
    ili9340_init(gu);
    makise_start(gu);

    mGui->predraw = &mt_predraw;

    makise_g_focus(&(butt[0].el), M_G_FOCUS_GET);
    controls_595_init(buttons, 8, outs, 4, &but_h);
   
    return mGui;
}
