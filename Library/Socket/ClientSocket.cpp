// Implementation of the ClientSocket class

#include "ClientSocket.h"
#include "SocketException.h"



ClientSocket::ClientSocket ( std::string host, int port )
{
  if ( ! Socket::create() )
    {
      throw SocketCreationException();
    }

  if ( ! Socket::connect ( host, port ) )
    {
      throw SocketBindException();
    }

}


const ClientSocket& ClientSocket::operator << ( const std::string& s ) const
{
  if ( ! Socket::send ( s ) )
    {
      throw SocketWriteException();
    }

  return *this;

}


const ClientSocket& ClientSocket::operator >> ( std::string& s ) const
{
  if ( ! Socket::recv ( s ) )
    {
      throw SocketReadException();
    }

  return *this;
}
