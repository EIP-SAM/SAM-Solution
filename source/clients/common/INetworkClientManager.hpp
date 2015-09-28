class			INetworkClientManager
{
public:
  virtual void		connected() = 0;
  virtual bool		sendtest() = 0;
  virtual std::string	receive() = 0;
  virtual void		disconnect() = 0;
};
