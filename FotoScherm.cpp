/*
 * FotoScherm.cpp
 *
 *  Created on: 3 mrt. 2012
 *      Author: Niek Zuure
 */

#include "FotoScherm.h"

//globale variabelen voor breedte en hoogte van het scherm
int screenWidth, screenHeight;

FotoScherm::FotoScherm()
{
	//bepalen van de grootte van het scherm
	MAExtent screenSize = maGetScrSize();
	screenWidth = EXTENT_X( screenSize );
	screenHeight = EXTENT_Y( screenSize );

	//het aanmaken van het optiescherm
	this->optieScherm = new OptieScherm(this);

	//standaard font en grafisch uiterlijk (uit de resource file res.lst)
	Font* font = new MAUI::Font(RES_FONT);
	WidgetSkin* skin = new WidgetSkin(RES_SELECTED, RES_UNSELECTED, 16, 32, 16,	32, false, false);

	//maak een label die andere widgets straks bevat, en een achtergrondkleur heeft
	this->achtergrondLabel = new Label(0, 0, screenWidth, screenHeight, NULL);

	//maak een plaatje (laden uit de resource file res.lst) en voeg label als parent toe
	this->image = new Image(screenWidth / 4, screenHeight / 4, screenWidth / 2, screenHeight / 2, this->achtergrondLabel, false, false, RES_IMAGE);

	//maak tekst bij het plaatje met een label
	this->imageTekst = new Label(screenWidth / 4, screenHeight - screenHeight / 4, screenWidth / 2, 32, this->achtergrondLabel, "Naam plaatje", 0xFF0000, font);
	this->imageTekst->setSkin(skin);

	//stel dit scherm in als het main scherm, met achtergrondlabel als de basis widget
	this->setMain(this->achtergrondLabel);
}

//show() override de show() van de super klasse (Screen), omdat we bij showen eerst opties willen ophalen
void FotoScherm::show()
{
	//roep de show() van de superklasse (Screen) aan
	this->Screen::show();

	//haal informatie achtergrondkleur op van optiescherm
	this->achtergrondLabel->setBackgroundColor(	this->optieScherm->getAchtergrondOptie());

	//haal informatie imagetekst op van optiescherm
	this->imageTekst->setCaption(this->optieScherm->getImagetekst());
	this->image->setWidth(this->optieScherm->getImageGrootte());
	this->image->setHeight(this->optieScherm->getImageGrootte());
}

//afvangen invoer
void FotoScherm::keyPressEvent(int keyCode, int nativeCode)
{
	//bij indrukken van de MAK_FIRE toets, laat optiescherm zien
	if (keyCode == MAK_FIRE)
	{
		this->optieScherm->show();
	}
}

void FotoScherm::pointerPressEvent(MAPoint2d point)
{
	this->optieScherm->show();
}

FotoScherm::~FotoScherm() {}
