#ifndef ASTATISTICTAB_HPP_
# define ASTATISTICTAB_HPP_

class AStatisticTab : public AStatisticData
{
public:
  AStatisticTab();
  ~AStatisticTab();
  void setTabX(List<Float>);
  void setTabY(List<Float>);
  List<Float> getTabX() const;
  List<Float> getTabY() const;
private:
  List<Float> TabX;
  List<Float> TabY
};

#endif // !ASTATISTICTAB_HPP_
