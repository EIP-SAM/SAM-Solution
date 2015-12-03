#include "AStatisticTab.hpp"

AStatisticTab::AStatisticTab()
{
}

AStatisticTab::~AStatisticTab()
{
}

void AStatisticTab::setTabX(List<Float> tab)
{
  _TabX = tab;
}

void AStatisticTab::setTabY(List<Float> tab)
{
  _TabY = tab;
}

List<Float> AStatisticTab::getTabX()
{
  return (_TabX);
}


List<Float> AStatisticTab::getTabY()
{
  return (_TabY);
}
