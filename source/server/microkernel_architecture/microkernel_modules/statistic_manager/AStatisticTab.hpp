#ifndef ASTATISTICTAB_HPP_
# define ASTATISTICTAB_HPP_

# include "AStatisticData.hpp"

class AStatisticTab : public AStatisticData
{
public:
  AStatisticTab();
  ~AStatisticTab();
  void setTabX(vector<float>);
  void setTabY(vector<float>);
  vector<float> getTabX() const;
  vector<float> getTabY() const;

private:
  vector<float> _TabX;
  vector<float> _TabY
};

#endif // !ASTATISTICTAB_HPP_
