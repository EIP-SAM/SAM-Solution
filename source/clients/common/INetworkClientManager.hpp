class			INetworkClientManager
{
public:
  virtual void		connected() = 0;
  virtual bool		send() = 0;
  virtual std::string	receive() = 0;
  virtual void		disconnect() = 0;
};
