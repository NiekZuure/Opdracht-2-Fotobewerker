/*
 * OptieScherm.cpp
 *
 *  Created on: 3 mrt. 2012
 *      Author: Niek Zuure
 */

#include "OptieScherm.h"

extern int screenWidth, screenHeight;

OptieScherm::OptieScherm(Screen* parent)
{
	//sla parent scherm op (FotoScherm) om de show() te kunnen aanroepen, zodat dit optiescherm weer gesloten wordt
	this->parent = parent;

	//bepaal grootte van het scherm

	//standaard font en grafisch uiterlijk (uit de resource file res.lst)
	Font* font = new MAUI::Font(RES_FONT);
	WidgetSkin* skin = new WidgetSkin(RES_SELECTED, RES_UNSELECTED, 16, 32, 16, 32, false, false);

	//maak een label die andere widgets straks bevat, en een achtergrondkleur heeft
	Layout* mainLayout = new Layout(0, 0, screenWidth, screenHeight, NULL, 1, 1);

	//stel achtergrondkleur in
	this->achtergrondKleur = 0x00FF00;

	this->listbox = new ListBox(0, 0, screenWidth, screenHeight, mainLayout, ListBox::LBO_VERTICAL, ListBox::LBA_LINEAR, true);

	listbox->setBackgroundColor(0x00FF00);
	listbox->setDrawBackground(true);

	//maak rode knop
	this->roodLabel = new Label(0, 0, screenWidth, 50, listbox, "Rood", 0xFF0000, font);
	roodLabel->setSkin(skin);
	this->kleurLabels.add(roodLabel); //voeg toe aan vector

	//maak groene knop
	this->groenLabel = new Label(0, 0, screenWidth, 50, listbox, "Groen", 0x00FF00, font);
	groenLabel->setSkin(skin);
	kleurLabels.add(groenLabel); //voeg toe aan vector

	//maak blauwe knop
	this->blauwLabel = new Label(0, 0, screenWidth, 50, listbox, "Blauw", 0x0000FF, font);
	blauwLabel->setSkin(skin);
	kleurLabels.add(blauwLabel); //voeg toe aan vector

	//stel grootte plaatje in m.b.v. editbox
	char buffer[128];
	itoa(screenWidth / 2, buffer, 10);


	// grootte van het plaatje
	this->editBoxGrootte = new EditBox(0, 0, screenWidth, 50, listbox, buffer, 0x000000, font, true, false, 50, EditBox::IM_NUMBERS);
	editBoxGrootte->setSkin(skin);

	//tekst van het plaatje
	this->editBoxNaam = new EditBox(0, 0, screenWidth, 50, listbox, "Text", 0x000000, font, true, false, 50, EditBox::IM_QWERTY);
	editBoxNaam->setSkin(skin);


	// het toepaslabel
	this->toepasLabel = new Label(0, 0, screenWidth, 50, listbox, "Toepassen", 0x0000FF, font);
	toepasLabel->setSkin(skin);

	this->setMain(mainLayout);
}

void OptieScherm::show()
{
//	lprintfln("Showing");
	this->Screen::show();
}

//geef ingestelde achtergrondkleur terug
int OptieScherm::getAchtergrondOptie()
{
	//return achtergrond kleur
	return this->achtergrondKleur;
}

//geef ingestelde imagetekst van de editbox terug
const BasicString<char> OptieScherm::getImagetekst()
{
	//verander editBox naar jouw editboxs
	return this->editBoxNaam->getCaption(); //caption is de text in een editbox
}

int OptieScherm::getImageGrootte()
{
	return atoi(this->editBoxGrootte->getCaption().c_str());
}

void OptieScherm::keyPressEvent(int keyCode, int nativeCode)
{
	//laat bij MAK_FIRE knop indrukken de parent (FotoScherm dus) weer zien
	if (keyCode == MAK_FIRE)
	{
		this->parent->show();
	}
	else if (keyCode == MAK_UP)
	{
		this->listbox->selectPreviousItem();
	}
	else if (keyCode == MAK_DOWN)
	{
		this->listbox->selectNextItem();
	}
}

void OptieScherm::pointerPressEvent(MAPoint2d point) {
	Point p = *new Point(point.x, point.y);

	//doorloop alle kleurlabels om selectie in te stellen
	for (int i = 0; i < this->kleurLabels.size(); i++)
	{
		Label* label = this->kleurLabels[i];
		bool selected = label->contains(p);
		label->setSelected(selected);

		if (selected)
		{
			if (label == this->roodLabel)
			{
				this->achtergrondKleur = 0xFF0000;
			} else if (label == this->groenLabel)
			{
				this->achtergrondKleur = 0x00FF00;
			} else if (label == this->blauwLabel)
			{
				this->achtergrondKleur = 0x0000FF;
			}
		}
	}

	this->editBoxGrootte->setSelected(this->editBoxGrootte->contains(p));
	this->editBoxNaam->setSelected(this->editBoxNaam->contains(p));
	this->toepasLabel->setSelected(this->toepasLabel->contains(p));

	if (this->toepasLabel->contains(p))
	{
		this->parent->show();
	}
}

OptieScherm::~OptieScherm() {}
