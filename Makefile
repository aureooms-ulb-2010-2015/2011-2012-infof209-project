all: clear Projet_server Projet_client Chat_Client_Alone

co = Compression/

#Partie Serveur
#--------------------------------

Projet_server: server common library Chat_Server
	g++ -pthread -lm -o ./Projet_server $(serverS) $(commonS) $(libraryS) $(Chat_Server)

Projet_client: client common library
	g++ -pthread -lm -o ./Projet_client $(clientS) $(commonS) $(libraryS)

server:$(co)server_main.o $(co)server_Server.o $(co)server_Client.o $(co)server_Player.o $(co)server_GameInstance.o $(co)server_ServerGame.o $(co)server_Ranking.o
serverS=$(co)server_main.o $(co)server_Server.o $(co)server_Client.o $(co)server_Player.o $(co)server_GameInstance.o $(co)server_ServerGame.o $(co)server_Ranking.o

$(co)server_Server.o: Server/Server.cpp
	g++ -pthread -lm -o $(co)server_Server.o -c Server/Server.cpp -W -Wall -pedantic

$(co)server_ServerGame.o: Server/ServerGame.cpp
	g++ -pthread -lm -o $(co)server_ServerGame.o -c Server/ServerGame.cpp -W -Wall -pedantic

$(co)server_main.o: Server/main.cpp
	g++ -pthread -lm -o $(co)server_main.o -c Server/main.cpp -W -Wall -pedantic

$(co)server_Client.o: Server/Client.cpp
	g++ -pthread -lm -o $(co)server_Client.o -c Server/Client.cpp -W -Wall -pedantic

$(co)server_Player.o: Server/Player.cpp
	g++ -pthread -lm -o $(co)server_Player.o -c Server/Player.cpp -W -Wall -pedantic

$(co)server_GameInstance.o: Server/GameInstance.cpp
	g++ -pthread -lm -o $(co)server_GameInstance.o -c Server/GameInstance.cpp -W -Wall -pedantic

#Ranking

$(co)server_Ranking.o: Server/Ranking.cpp
	g++ -pthread -lm -o $(co)server_Ranking.o -c Server/Ranking.cpp -W -Wall -pedantic

#Partie Client

client:$(co)client_Server.o $(co)client_main.o $(co)client_GameServer.o games $(co)client_Menu.o $(co)client_ListenerServer.o bet
clientS=$(co)client_Server.o $(co)client_main.o $(co)client_GameServer.o $(games) $(co)client_Menu.o $(co)client_ListenerServer.o $(bet)

$(co)client_Server.o: Client/Server.cpp
	g++ -pthread -lm -o $(co)client_Server.o -c Client/Server.cpp -W -Wall -pedantic

$(co)client_GameServer.o: Client/GameServer.cpp
	g++ -pthread -lm -o $(co)client_GameServer.o -c Client/GameServer.cpp -W -Wall -pedantic

$(co)client_ListenerServer.o: Client/ListenerServer.cpp
	g++ -pthread -lm -o $(co)client_ListenerServer.o -c Client/ListenerServer.cpp -W -Wall -pedantic


$(co)client_main.o: console_client.cpp
	g++ -pthread -lm -o $(co)client_main.o -c console_client.cpp -W -Wall -pedantic

$(co)client_Menu.o: Client/Menu.cpp
	g++ -pthread -lm -o $(co)client_Menu.o -c Client/Menu.cpp -W -Wall -pedantic

#jeux
#-------------------------------------------------------------------
gd = Client/Games/

games : gametools reversi backgammon checkers ludo
games = $(gametools) $(reversi) $(backgammon) $(checkers) $(ludo)

###########
#GAMETOOLS#
###########

gametools: $(co)games_Game.o $(co)games_DiceGame.o $(co)games_Board.o $(co)games_Piece.o $(co)games_Player.o
gametools = $(co)games_Game.o $(co)games_DiceGame.o $(co)games_Board.o $(co)games_Piece.o $(co)games_Player.o

$(co)games_Game.o: $(gd)Game.cpp
	g++ -pthread -lm -o $(co)games_Game.o -c $(gd)Game.cpp -W -Wall -pedantic

$(co)games_DiceGame.o: $(gd)DiceGame.cpp
	g++ -pthread -lm -o $(co)games_DiceGame.o -c $(gd)DiceGame.cpp -W -Wall -pedantic

$(co)games_Board.o: $(gd)Board.cpp
	g++ -pthread -lm -o $(co)games_Board.o -c $(gd)Board.cpp -W -Wall -pedantic

$(co)games_Piece.o: $(gd)Piece.cpp
	g++ -pthread -lm -o $(co)games_Piece.o -c $(gd)Piece.cpp -W -Wall -pedantic

$(co)games_Player.o: $(gd)GamePlayer.cpp
	g++ -pthread -lm -o $(co)games_Player.o -c $(gd)GamePlayer.cpp -W -Wall -pedantic

#########
#REVERSI#
#########

reversi: $(co)Reversi.o $(co)Direction.o $(co)HorizontalDirection.o $(co)VerticalDirection.o $(co)ReversiPlayer.o $(co)ReversiBlackPlayer.o $(co)ReversiWhitePlayer.o $(co)ReversiBoard.o $(co)ReversiPiece.o $(co)TrinaryState.o $(co)ReversiMove.o

reversi = $(co)Reversi.o $(co)Direction.o $(co)HorizontalDirection.o $(co)VerticalDirection.o $(co)ReversiPlayer.o $(co)ReversiBlackPlayer.o $(co)ReversiWhitePlayer.o $(co)ReversiBoard.o $(co)ReversiPiece.o $(co)TrinaryState.o $(co)ReversiMove.o

$(co)Reversi.o: $(gd)Reversi/cpp/Reversi.cpp
	g++ -o $(co)Reversi.o -c $(gd)Reversi/cpp/Reversi.cpp

$(co)Direction.o: $(gd)Reversi/cpp/Direction.cpp
	g++ -o $(co)Direction.o -c $(gd)Reversi/cpp/Direction.cpp

$(co)HorizontalDirection.o: $(gd)Reversi/cpp/HorizontalDirection.cpp
	g++ -o $(co)HorizontalDirection.o -c $(gd)Reversi/cpp/HorizontalDirection.cpp

$(co)VerticalDirection.o: $(gd)Reversi/cpp/VerticalDirection.cpp
	g++ -o $(co)VerticalDirection.o -c $(gd)Reversi/cpp/VerticalDirection.cpp

$(co)ReversiPlayer.o: $(gd)Reversi/cpp/ReversiPlayer.cpp
	g++ -o $(co)ReversiPlayer.o -c $(gd)Reversi/cpp/ReversiPlayer.cpp

$(co)ReversiBlackPlayer.o: $(gd)Reversi/cpp/ReversiBlackPlayer.cpp
	g++ -o $(co)ReversiBlackPlayer.o -c $(gd)Reversi/cpp/ReversiBlackPlayer.cpp

$(co)ReversiWhitePlayer.o: $(gd)Reversi/cpp/ReversiWhitePlayer.cpp
	g++ -o $(co)ReversiWhitePlayer.o -c $(gd)Reversi/cpp/ReversiWhitePlayer.cpp

$(co)ReversiBoard.o: $(gd)Reversi/cpp/ReversiBoard.cpp
	g++ -o $(co)ReversiBoard.o -c $(gd)Reversi/cpp/ReversiBoard.cpp

$(co)ReversiPiece.o: $(gd)Reversi/cpp/ReversiPiece.cpp
	g++ -o $(co)ReversiPiece.o -c $(gd)Reversi/cpp/ReversiPiece.cpp

$(co)TrinaryState.o: $(gd)Reversi/cpp/TrinaryState.cpp
	g++ -o $(co)TrinaryState.o -c $(gd)Reversi/cpp/TrinaryState.cpp


$(co)ReversiMove.o: $(gd)Reversi/cpp/ReversiMove.cpp
	g++ -o $(co)ReversiMove.o -c $(gd)Reversi/cpp/ReversiMove.cpp

############
#BACKGAMMON#
############
backgammon: $(co)games_Backgammon.o $(co)games_BackgammonPiece.o $(co)games_BackgammonBoard.o $(co)games_BackgammonPlayer.o $(co)games_BackgammonMove.o

backgammon = $(co)games_Backgammon.o $(co)games_BackgammonPiece.o $(co)games_BackgammonBoard.o $(co)games_BackgammonPlayer.o $(co)games_BackgammonMove.o

$(co)games_Backgammon.o: $(gd)Backgammon/Backgammon.cpp
	g++ -pthread -lm -o $(co)games_Backgammon.o -c $(gd)Backgammon/Backgammon.cpp -W -Wall -pedantic

$(co)games_BackgammonPiece.o: $(gd)Backgammon/BackgammonPiece.cpp
	g++ -pthread -lm -o $(co)games_BackgammonPiece.o -c $(gd)Backgammon/BackgammonPiece.cpp -W -Wall -pedantic

$(co)games_BackgammonBoard.o: $(gd)Backgammon/BackgammonBoard.cpp
	g++ -pthread -lm -o $(co)games_BackgammonBoard.o -c $(gd)Backgammon/BackgammonBoard.cpp -W -Wall -pedantic

$(co)games_BackgammonPlayer.o: $(gd)Backgammon/BackgammonPlayer.cpp
	g++ -pthread -lm -o $(co)games_BackgammonPlayer.o -c $(gd)Backgammon/BackgammonPlayer.cpp -W -Wall -pedantic

$(co)games_BackgammonMove.o: $(gd)Backgammon/BackgammonMove.cpp
	g++ -pthread -lm -o $(co)games_BackgammonMove.o -c $(gd)Backgammon/BackgammonMove.cpp -W -Wall -pedantic
##########
#CHECKERS#
##########

checkers: $(co)games_CheckersGame.o  $(co)games_CheckersPiece.o $(co)games_CheckersBoard.o $(co)games_CheckersPlayer.o $(co)games_CheckersMove.o
checkers = $(co)games_CheckersGame.o  $(co)games_CheckersPiece.o $(co)games_CheckersBoard.o $(co)games_CheckersPlayer.o $(co)games_CheckersMove.o

$(co)games_CheckersGame.o: $(gd)Checkers/CheckersGame.cpp
	g++ -pthread -lm -o $(co)games_CheckersGame.o -c $(gd)Checkers/CheckersGame.cpp -W -Wall -pedantic

$(co)games_CheckersPiece.o: $(gd)Checkers/CheckersPiece.cpp
	g++ -pthread -lm -o $(co)games_CheckersPiece.o -c $(gd)Checkers/CheckersPiece.cpp -W -Wall -pedantic

$(co)games_CheckersBoard.o: $(gd)Checkers/CheckersBoard.cpp
	g++ -pthread -lm -o $(co)games_CheckersBoard.o -c $(gd)Checkers/CheckersBoard.cpp -W -Wall -pedantic

$(co)games_CheckersPlayer.o: $(gd)Checkers/CheckersPlayer.cpp
	g++ -pthread -lm -o $(co)games_CheckersPlayer.o -c $(gd)Checkers/CheckersPlayer.cpp -W -Wall -pedantic

$(co)games_CheckersMove.o: $(gd)Checkers/CheckersMove.cpp
	g++ -pthread -lm -o $(co)games_CheckersMove.o -c $(gd)Checkers/CheckersMove.cpp -W -Wall -pedantic



######
#LUDO#
######

ludo : $(co)games_Ludo.o $(co)games_LudoBoard.o $(co)games_LudoPlayer.o $(co)games_LudoPiece.o $(co)games_LudoMove.o
ludo = $(co)games_Ludo.o $(co)games_LudoBoard.o $(co)games_LudoPlayer.o $(co)games_LudoPiece.o $(co)games_LudoMove.o
$(co)games_Ludo.o: $(gd)Ludo/LudoClass/Ludo.cpp
	g++ -pthread -lm -o $(co)games_Ludo.o -c $(gd)Ludo/LudoClass/Ludo.cpp -W -Wall -pedantic

$(co)games_LudoBoard.o: $(gd)Ludo/LudoClass/LudoBoard.cpp 
	g++ -pthread -lm -o $(co)games_LudoBoard.o -c $(gd)Ludo/LudoClass/LudoBoard.cpp -W -Wall -pedantic

$(co)games_LudoPlayer.o: $(gd)Ludo/LudoClass/LudoPlayer.cpp
	g++ -pthread -lm -o $(co)games_LudoPlayer.o -c $(gd)Ludo/LudoClass/LudoPlayer.cpp -W -Wall -pedantic

$(co)games_LudoPiece.o: $(gd)Ludo/LudoClass/LudoPiece.cpp
	g++ -pthread -lm -o $(co)games_LudoPiece.o -c $(gd)Ludo/LudoClass/LudoPiece.cpp -W -Wall -pedantic

$(co)games_LudoMove.o: $(gd)Ludo/LudoClass/LudoMove.cpp
	g++ -pthread -lm -o $(co)games_LudoMove.o -c $(gd)Ludo/LudoClass/LudoMove.cpp -W -Wall -pedantic

#------------------------------------------------------------------------------------------------------
######
#CHAT#
######

cs = Chat/cpp/
Chat_Server = $(co)Chat_server.o $(co)Chat_channel.o $(co)Chat_channel_state.o $(co)Feed.o $(co)Chat_message.o $(co)Chat_notification.o $(co)Chat_client_manager.o $(co)Chat_server_message_receiver.o $(co)Chat_server_message_sender.o

Chat_Server: $(Chat_Server)

	
$(co)Chat_server.o: $(cs)Chat_server.cpp
	g++ -pthread  -o $(co)Chat_server.o -c $(cs)Chat_server.cpp 
	
$(co)Chat_channel.o: $(cs)Chat_channel.cpp
	g++ -pthread  -o $(co)Chat_channel.o -c $(cs)Chat_channel.cpp 

$(co)Chat_channel_state.o: $(cs)Chat_channel_state.cpp
	g++ -pthread  -o $(co)Chat_channel_state.o -c $(cs)Chat_channel_state.cpp 

$(co)Feed.o: $(cs)Feed.cpp
	g++ -pthread  -o $(co)Feed.o -c $(cs)Feed.cpp 	

$(co)Chat_message.o: $(cs)Chat_message.cpp
	g++ -pthread  -o $(co)Chat_message.o -c $(cs)Chat_message.cpp

$(co)Chat_notification.o: $(cs)Chat_notification.cpp
	g++ -pthread  -o $(co)Chat_notification.o -c $(cs)Chat_notification.cpp 

$(co)Chat_client_manager.o: $(cs)Chat_client_manager.cpp
	g++ -pthread  -o $(co)Chat_client_manager.o -c $(cs)Chat_client_manager.cpp 
	
$(co)Chat_server_message_receiver.o: $(cs)Chat_server_message_receiver.cpp
	g++ -pthread  -o $(co)Chat_server_message_receiver.o -c $(cs)Chat_server_message_receiver.cpp 
	
$(co)Chat_server_message_sender.o: $(cs)Chat_server_message_sender.cpp
	g++ -pthread  -o $(co)Chat_server_message_sender.o -c $(cs)Chat_server_message_sender.cpp 


Chat_Client_Alone = $(co)Chat_main.o $(co)Chat_client.o $(co)Chat_client_message_receiver.o $(co)Chat_client_message_sender.o $(co)Feed.o $(co)Chat_message.o $(co)Chat_notification.o

Chat_Client_Alone: $(co)Chat_main.o $(co)Chat_client.o $(co)Chat_client_message_receiver.o $(co)Chat_client_message_sender.o $(co)Feed.o $(co)Chat_message.o $(co)Chat_notification.o library
	g++ -pthread  -o Chat_Client_Alone $(Chat_Client_Alone) $(libraryS)

$(co)Chat_main.o:$(cs)main.cpp
	g++ -pthread  -o $(co)Chat_main.o -c $(cs)main.cpp 

$(co)Chat_client.o: $(cs)Chat_client.cpp
	g++ -pthread  -o $(co)Chat_client.o -c $(cs)Chat_client.cpp 
	
$(co)Chat_client_message_receiver.o: $(cs)Chat_client_message_receiver.cpp
	g++ -pthread  -o $(co)Chat_client_message_receiver.o -c $(cs)Chat_client_message_receiver.cpp 

$(co)Chat_client_message_sender.o: $(cs)Chat_client_message_sender.cpp
	g++ -pthread  -o $(co)Chat_client_message_sender.o -c $(cs)Chat_client_message_sender.cpp 

#------------------------------------------------------------------------------------------------

#######
##BET##
#######

bet = $(co)bet.o
bet: $(co)bet.o
	
	
	
$(co)bet.o: Client/Bet/Bet.cpp
	g++ -pthread  -o $(co)bet.o -c Client/Bet/Bet.cpp
	
#Partie commune

commonS=$(co)GenericServer.o $(co)GenericCommunicator.o $(co)Request.o
common:$(co)GenericServer.o $(co)GenericCommunicator.o $(co)Request.o

$(co)GenericServer.o: Common/GenericServer.cpp
	g++ -pthread -lm -o $(co)GenericServer.o -c Common/GenericServer.cpp -W -Wall -pedantic

$(co)Request.o: Common/Request.cpp
	g++ -pthread -lm -o $(co)Request.o -c Common/Request.cpp -W -Wall -pedantic

$(co)GenericCommunicator.o: Common/GenericCommunicator.cpp
	g++ -pthread -lm -o $(co)GenericCommunicator.o -c Common/GenericCommunicator.cpp -W -Wall -pedantic

#Partie librarie
#------------------------------------
libraryS=$(co)lib_Exception.o $(co)lib_Thread.o $(co)Socket.o $(co)ClientSocket.o $(co)ServerSocket.o $(co)Chat_communication.o
library:$(co)lib_Exception.o $(co)lib_Thread.o $(co)Socket.o $(co)ClientSocket.o $(co)ServerSocket.o $(co)Chat_communication.o

$(co)lib_Exception.o: Library/Exception/Exception.cpp
	g++ -pthread -lm -o $(co)lib_Exception.o -c Library/Exception/Exception.cpp -W -Wall -pedantic

$(co)lib_Thread.o: Library/Thread/Thread.cpp
	g++ -pthread -lm -o $(co)lib_Thread.o -c Library/Thread/Thread.cpp -W -Wall -pedantic

$(co)Socket.o: Library/Socket/Socket.cpp
	g++ -pthread  -o $(co)Socket.o -c Library/Socket/Socket.cpp 

$(co)ClientSocket.o: Library/Socket/ClientSocket.cpp
	g++ -pthread  -o $(co)ClientSocket.o -c Library/Socket/ClientSocket.cpp
 
$(co)ServerSocket.o: Library/Socket/ServerSocket.cpp
	g++ -pthread  -o $(co)ServerSocket.o -c Library/Socket/ServerSocket.cpp

$(co)Chat_communication.o: $(cs)communication_library.cpp
	g++ -pthread  -o $(co)Chat_communication.o -c $(cs)communication_library.cpp

#accesoires
#-------------------------------------

clean:
	rm -f $(co)*.o

mrproper: clean
	rm Projet_server

clear:
	clear