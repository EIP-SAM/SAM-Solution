#include "AStatisticTab.hpp"
#include "AInstructionParameter.hpp"

AStatisticTab::AStatisticTab()
{
}

AStatisticTab::~AStatisticTab()
{
}

void AStatisticTab::setTabX(vector<float> tab)
{
  Parameter *param;
  QByteArray* ins = new QByteArray(reinterpret_cast<const char*>(tab.data()), tab.size());

  param = this->createParameter(tab.size);
  param->setRawData(&ins);
}

void AStatisticTab::setTabY(vector<float> tab)
{
  Parameter *param;
  QByteArray* ins = new QByteArray(reinterpret_cast<const char*>(tab.data()), tab.size());

  param = this->createParameter(tab.size);
  param->setRawData(&ins);
}

vector<float> AStatisticTab::getTabX()
{
  return (_TabX);
}

vector<float> AStatisticTab::getTabY()
{
  return (_TabY);
}
