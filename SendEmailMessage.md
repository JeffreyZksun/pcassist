Call Blat.exe to send out the email message by SMTP.

The command line format is as:
```
blat.exe TA.txt -to target@gmail.com -server smtp.163.com -f user@163.com -u user@163.com -pw userpwd
```
Output
```
Blat v2.7.5 w/GSS encryption (build : Aug 16 2011 23:04:23)

Sending TA.txt to target@gmail.com
Login name is user@163.com
```

Blat Home Page: [http://www.blat.net/](http://www.blat.net/)

Blat is a small, efficent SMTP command line mailer for Windows. It is the SMTP **sending** part of an eMail User Agent (MUA) or eMail client. As such, Blat sends eMail via SMTP (or internet eMail) from the command line, or CGI, ...