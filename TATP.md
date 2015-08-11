# Introduction #

Task Automation Transfer Protocol (TATP) is a text-based protocol, in which a sender communicates with a receiver by issuing command strings and supplying necessary data over a reliable ordered data stream channel, typically a Transmission Control Protocol (TCP) connection.

An TATP session consists of commands originated by an client (the initiating agent, sender, or transmitter) and corresponding responses from the TATP server (the listening agent, or receiver) so that the session is opened, and session datas are exchanged.

During the communication session, only the basic character set is used. The basic character set consists 94 characters: 3 control characters: space (`<SPACE>`), carriage return (`<CR>`), line feed (`<LF>`) and the 91 graphic characters below.
```
abcdefghijklmnopqrstuvwxyz
ABCDEFGHIJKLMNOPQRSTUVWXYZ
0123456789
_{ }[]#()<>%:;.?*+-/ˆ&| ̃!=,\"’
```
# Command string #
Normally each line ends with `<CR><LF>`is a complete command string, except the commands requiring multi-line data.

```
<CR>: '\r' = 0x0D
<LF>: '\n' = 0x0A
```

The command string is formatted. There are two formats, one is that from client to server, the other is that from server to client.

## Command string from client to server ##
```
command-name<SPACE>string-data<CR><LF>
```
## Command string from server to client ##
```
result-code-number<SPACE>string-data<CR><LF>
```

## multi-line command data ##
For some commands, they require multi-line data. As long as the data transformation is started, the `<CR><LF>` will not be treated as the notion of the complete of the command string until the data transformation is finished.


# TATP transport example #
For illustration purposes here (not part of protocol), the protocol exchanges are prefixed for the server (S:) and the client (C:).

Every line ends with `<CR><LF>`. They are omitted for the sake of brevity.

## Client send data to server ##
Client sends the connection request, and server accepts it. Then
```
C: HELLO my client id
S: 250 WELCOME v2.54
C: DATA
S: 250 DATA End data with <CR><LF>.<CR><LF>
C: <action>
C:    <parameter> ... </parameter>
C:    <parameter> ... </parameter>
C: </action>
C: .
S: 250 ok: queued as 12345
C: QUIT
S: 221 Bye
```
## Invalid command ##
Client sends the connection request, and server accepts it. Then
```
C: GUESS who am I?
S: 337 Invalid command line
C: QUIT
S: 221 Bye
```