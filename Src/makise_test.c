#include "makise_test.h"

MakiseGUI* mGui;
MHost *host;

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

MButton butt[3];
void mt_predraw(MakiseGUI * g)
{
    butt[1].el.position.x = (butt[1].el.position.x+1) %150;
    makise_g_host_call(host, M_G_CALL_PREDRAW);
}

char t0[] = "dsf";
char t1[] = {208, 204, 255};
char t2[] = "GAD";

MakiseGUI    Gu;
MakiseBuffer Bu;
MakiseDriver Dr;
MHost hs;
MContainer co;
uint32_t sb[7680/4] = {0};
uint32_t bb[19200/4] = {0};
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

    m_button_create(&butt[0], host->host, 50, 50, 100, 70, t0, 0, 2, 1);
    m_button_create(&butt[1], host->host, 50, 150, 100, 50, t1, 1, 0, 1);
    m_button_create(&butt[2], host->host, 50, 220, 70, 50, t2, 2, 1, 0);

    
    mGui = gu;
    ili9340_init(gu);
    makise_start(gu);

    mGui->predraw = &mt_predraw;
    return mGui;
}
