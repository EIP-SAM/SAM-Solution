#include "AStatisticGraph.hpp"

AStatisticGraph::AStatisticGraph()
{
}

AStatisticGraph::~AStatisticGraph()
{
}

void AStatisticGraph::SetNameX(QString nameX)
{
  Parameter	*parameter;
  QByteArray	convertedValue;

  convertedValue = nameX.toUtf8();

  parameter = this->createParameter();
  parameter->setSize(convertedValue.size());
  parameter->setRawData(convertedValue);
}

void AStatisticGraph::SetNameY(QString nameY)
{
  Parameter	*parameter;
  QByteArray	convertedValue;

  convertedValue = nameY.toUtf8();

  parameter = this->createParameter();
  parameter->setSize(convertedValue.size());
  parameter->setRawData(convertedValue);
}

void AStatisticGraph::SetData(std::vector<uint8_t> data)
{

  Parameter	*parameter;
  QByteArray	convertedValue;

  convertedValue = new QByteArray(reinterpret_cast<const char*>(data.data()), data.size());

  parameter = this->createParameter();
  parameter->setSize(convertedValue.size());
  parameter->setRawData(convertedValue);
}
