#include "DebugDisplay.h"
#include "GraphicsBuffer.h"
#include "DebugContent.h"
#include "GameApp.h"
#include <GraphicsSystem.h>
#include <Font.h>
#include <FontManager.h>

using namespace std;

DebugDisplay::DebugDisplay( const Vector2D& pos, DebugContent* pContent )
	:mPos(pos)
	,mpContent(pContent)
{
}

DebugDisplay::~DebugDisplay()
{
	delete mpContent;
}

void DebugDisplay::draw( GraphicsBuffer* pTarget )
{
	string toDisplay = mpContent->getDebugString();
	gpGame->getGraphicsSystem()->writeText(*pTarget, mPos, *gpGame->getFontManager()->getFont(COUR_20_FONT_ID), RED_COLOR, toDisplay);

}
