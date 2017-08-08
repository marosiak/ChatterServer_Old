# History
As first I wanted to make console communicator client-client (Like the communicator from first few minuts of polish movie called "Haker") like p2p, then I changed my mind to make client-server. I but 
at some point I decided to make GUI instand of console interface

# Config
The config is generated automaticly in serverDir/config/config.json
**The config doesn't work at this moment as the application is under development, but you're going to see it in next commit**
```json
{
  "port": "4400",
  "timeout": "5",
  "maxSearchResult": "20"
}
```
--**port** - port of the server on which the server is going to work.
--**timeout** - time after which client will be kicked if he will not send "updateToken" request, it's for safety and to avoid overloading, minimum is **1 min**, and max is **10 mins**
--**maxSearchResult** - When client is calling **getSearchResult** to find some friends, he could crash the server if there would be for example 10000000 of users, and he would do it like 10 times, so basicly the varible specify how many responds you can recive from the method

# Documentation
## Creating an account
```json
{
  "type": "register",
  "vales": [
    "login",
    "password"
  ]
}
```
## Loging into an account
```json
{
  "type": "login",
  "vales": [
    "login",
    "password"
  ]
}
```
### example response
```json
{
  "type": "message",
  "vales": [
    "Access Granted"
  ]
}
```
```json
{
  "type": "tokenTransfer",
  "vales": [
    "your token gonna be here"
  ]
}
```
**^ Remember to keep the token in your client, that's important.**


## Keeping connection
 You have to send token to tell server that you're still using the client, by default you have to do it every 3 mins, but you can set  it in config of the server.
```json
{
  "type": "updateToken",
  "vales": [
    "the token"
  ]
}
```
## Log-off
```json
{
  "type": "logOff",
  "vales": [
    "the token"
  ]
}
```
## Add friend
```json
{
  "type": "addFriend",
  "vales": [
    "the token"
  ]
}
```
## Remove friend
```json
{
  "type": "removeFriend",
  "vales": [
    "the token"
  ]
}
```
## Get friends list
```json
{
  "type": "removeFriend",
  "vales": [
    "the token"
  ]
}
```
### example response
```json
{
  "type": "friendsListRespond",
  "vales": [
    "friend1",
    "friend2",
    "friend3"
  ]
}
```
## Finding friends
```json
{
  "type": "getSearchResult",
  "vales": [
    "friend"
  ]
}
```
### example response
```json
{
  "type": "searchResult",
  "vales": [
    "friend12",
    "friend1244",
    "friend231"
  ]
}
```
## Searching in friends
Actually the same as finding friends, but this return your friends from part of these names
```json
{
  "type": "getFriendsResult",
  "vales": [
    "friend"
  ]
}
```
### example response
```json
{
  "type": "friendsListRespond",
  "vales": [
    "friend12",
    "friend1244",
    "friend231"
  ]
}
```
## Getting user status
```json
{
  "type": "getStatus",
  "vales": [
    "user1",
    "user2",
    "user3"
  ]
}
```
### example response
```json
{
  "type": "statusRespond",
  "values": [
    "true",
    "true",
    "false"
  ]
}
```
