#ifndef ASTATISTICGRAPH_HPP_
# define ASTATISTICGRAPH_HPP_

#include "AStatisticData.hpp"

class AStatisticGraph : AStatisticData
{
protected:
  void setNameX();
  void setNameY();
  void setData();
public:
  AStatisticGraph();
  ~AStatisticGraph();
}
