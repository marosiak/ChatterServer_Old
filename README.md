# ChatterServer
This is server for chat

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
^ Remember to keep the token in your client, that's important.


## Keeping connection
### You have to send token to tell server that you're still using the client, by default you have to do it every 3 mins, but you can set ### it in config of the server.
```json
{
  "type": "updateToken",
  "vales": [
    "the token"
  ]
}
```
